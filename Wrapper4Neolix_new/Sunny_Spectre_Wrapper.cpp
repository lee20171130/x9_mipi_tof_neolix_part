#include "Sunny_Spectre_Wrapper.h"
#include "spectre4neolix.h" //包含tof的底层接口和spectre的接口
#include <SDM450RDIHALInterface.h>

#define TOF_RESOLUTION_WIDGTH 224
#define TOF_RESOLUTION_HEIGHT 172     //tof得到的RAW就是224*173的.
extern SDM450RDIHALInterface *pTof4Sunny;

namespace sunny {


//global variable
DeviceInfo_t *deviceinfo = NULL;                //mars04 dev class object
FrameData_t* frame_data = NULL;		   			//指向存储深度数据的缓存,注意它的深度数据是点云的.
FrameDataRgb_t* frame_data_Rgb = NULL;  		//指向存储彩图数据的缓存

sunnySpectrePCL_t * pSunnySpectrePCLData = NULL;         //指向sunny_spectre吐出的点云数据,单位:m
DepthPixel_t * pNeolixDepthData = NULL;         //新石器算法需要的深度数据格式.
short * video_data = NULL;                      //获取相机的YUV数据    
tofSensorAllData_t tof_sensor_all_data;                //包含Mars04设备中所有有效数据(灰度,彩色,深度).
SDM450RDIHALInterface *tofObj = NULL;
int exposure_time;  

//下边是获取深度图的线程所用
BOOL IS_Running=FALSE;                          //开始/停止获取深度数据
BOOL thread_exit=FALSE;                         //退出获取深度数据的线程
pthread_t pth_get_data;
//others
unsigned char	 *PColorbuffer_s = NULL;
int DEPTHMAP_W;
int DEPTHMAP_H;
int DEPTHVIDEO_W;
int DEPTHVIDEO_H;
int DEPTHVIDEO_FRAME_SIZE;
int sensorIdx = X9_TOF_HAL_ID;
BOOL IS_RGBD;
BOOL IS_RGB;

getDepthFunc_t g_getDepthCallback = NULL;       //指向JNI层获取深度数据的func
const tofModeOption_t tofModeOption[5] = {
{false, 1200},
{false, 650},
{true, 850},
{true, 380},
{true, 250},
}; 
const tofUseScene_t curTofUseScene = MODE0_5FPS_1200US;

#define LOG_TAG "sunnySpectreWrapperLog"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
void* process_mipitof_data(void* param);
int sunny_raw2pcl_produce(void);
/*
	author:zhangw
	date:2018年3月6日
	dscr:
	param:
	ret: void
*/
void registerJNIGetDepthCB(getDepthFunc_t getDepthCallback)
{
	LOGI("registerJNIGetDepthCB\n");
	if (getDepthCallback != NULL)
		g_getDepthCallback = getDepthCallback;
	else 
		LOGI("registerJNIGetDepthCB:fail callback is nullptr!!!\n");
}
/*
	author:zhangw
	date:2018年3月6日
	dscr:
	param:
	ret: 0-right other-error
*/
int connect_mipitof(DeviceInfo_t &devInfo)
{
	LOGI("=============in %s\n", __func__);
	int ret = 0;
	//wrapper运行环境设置
	memset(&tof_sensor_all_data, 0, sizeof(tofSensorAllData_t));
	//打开底层camera,连接相机，初始化相机
	LOGI("=============just test SUNNY Spectre SDK & SIMT tof hal interface!!!!!!\n");
	tofObj = new SDM450RDIHALInterface(sensorIdx);
	if (NULL == tofObj) {
		LOGI("[%d], new SDM450RDIHALInterface failed!!!\n", __LINE__);
		return -1;
	}
	pTof4Sunny = tofObj;
	LOGI("invoke simt cam hal interface[%s] start\n", "get_num_cameras");
	ret = tofObj->get_num_cameras();
	printf("zhangw add:get camera num is %d\n",ret);
	LOGI("invoke simt cam hal interface[%s] end, ret=[%d]\n", "get_num_cameras", ret);
	
	LOGI("invoke simt cam hal interface[%s] start\n", "camera_open");
	LOGI("zhangw:open camera id:%d\n", sensorIdx);
	ret = tofObj->camera_open(sensorIdx);
	LOGI("invoke simt cam hal interface[%s] end, ret=[%d]\n", "camera_open", ret);
	if (ret) {
		LOGI("%s[%d]:%s,errno[%d]\n", __func__, __LINE__, "open camera failed!!", ret);
		return ret;
	}
	LOGI("invoke simt cam hal interface[%s] start\n", "setTOF_FPS_Mode");
	LOGI("zhangw:setTOF_FPS_Mode:%d\n", curTofUseScene);
	ret = tofObj->setTOF_FPS_Mode(curTofUseScene);
	LOGI("invoke simt cam hal interface[%s] end, ret=[%d]\n", "setTOF_FPS_Mode", ret);
	

	
	//获取当前TOF模组的信息,如:分辨率,标定信息
	deviceinfo = new DeviceInfo_t;
    memset(deviceinfo, 0, sizeof(DeviceInfo_t));
    {
		//目前只能将数据写死
		deviceinfo->DepthFrameWidth = TOF_RESOLUTION_WIDGTH;
		deviceinfo->DepthFrameHeight = TOF_RESOLUTION_HEIGHT+1;
		deviceinfo->VisibleFrameWidth = 1280;
        deviceinfo->VisibleFrameHeight = 720;
    }
	memcpy(&devInfo,deviceinfo, sizeof(DeviceInfo_t));
     	DEPTHMAP_W = deviceinfo->DepthFrameWidth;
        DEPTHMAP_H = deviceinfo->DepthFrameHeight-1;//减去一行头长度
        DEPTHVIDEO_W = deviceinfo->VisibleFrameWidth;
        DEPTHVIDEO_H = deviceinfo->VisibleFrameHeight;
		//出来的数据是I420
        DEPTHVIDEO_FRAME_SIZE = ROUND_UP(DEPTHVIDEO_W*DEPTHVIDEO_H*3/2+DEPTHVIDEO_W,1024);//尾部带一行帧信息
#ifdef NATIVE_WRAPPER_DEBUG
	LOGI("Depth Data:w-%d h-%d \nvisiableData:w-%d h-%d \n"
            ,DEPTHMAP_W,DEPTHMAP_H,DEPTHVIDEO_W,DEPTHVIDEO_H);
#endif
    //使用默认参数配置tof模组
   
	//构造spectre运行环境
#if 1
	exposure_time = tofModeOption[curTofUseScene].expourseTime;
	//spectre_use_single_frame(tofModeOption[curTofUseScene].isMonoFreq);
	//spectre_init(exposure_time);
#endif
	//启动获取数据的线程
	thread_exit = FALSE;
	IS_Running = FALSE;
    //创建取数据线程
   	pthread_create(&pth_get_data,NULL,process_mipitof_data,NULL);
	LOGI("get depth data thread is running!!!\n");
	LOGI("=============off %s\n", __func__);
	return ret;
}
int disconnect_mipitof()
{
	int ret = 0;
	//等待线程关闭
	LOGI("=============in disconnect_mipitof\n");
		//断开设备连接，释放内存
		IS_Running=FALSE;
		thread_exit = TRUE;
		pthread_join(pth_get_data, NULL);
		LOGI("thread exit success!!\n");
	//关闭算法环境
	//spectre_deinit();
	//关闭底层camera
	LOGI("invoke simt cam hal interface[%s] start\n", "camera_close");
	ret = tofObj->camera_close();
	//delete tofObj;
    LOGI("invoke simt cam hal interface[%s] end, ret=[%d]\n", "camera_close", ret);
	//释放分配的内存
	
	LOGI("=============off disconnect_mipitof\n");
	return ret;
}
typedef enum usecase {
	PLAY,
} usecase_t;
/*TOF_ErrorCode_t setMars04UseCase(CameraUseCase_e ucase)
{
	LOGI("setMars04UseCase\n");
	TOF_ErrorCode_t rv = LTOF_SUCCESS;
	rv = libtof->LibTOF_SetUseCase(ucase);
	return rv;
}
*/
int set_mipitof_usecase(usecase_t ucase)
{
	int ret = 0;
	return ret;
}
int genE2promFile(void)
{
	int ret = 0;
	//产生eeprom文件
	LOGI("invoke simt cam hal interface[%s] start\n", "tof_eeprom_enable");
	ret = tofObj->tof_eeprom_enable();
    LOGI("invoke simt cam hal interface[%s] end, ret=[%d]\n", "tof_eeprom_enable", ret);
	return ret;
}
int getTofLensParam(double *pLensParam)
{
	int ret = 0;
	static float LensParam[9];
	//获得tof的内参
	LOGI("invoke spectreGetTofLensParam\n");
    ret = spectreGetTofLensParam(LensParam);
	LOGI("invoke spectreGetTofLensParam end, ret=[%d]\n",ret);
	if (ret) {
		for (int i = 0; i < 9; i++) {
			pLensParam[i] = (double)LensParam[i];
			LOGI("pLensParam[%d] = %d\n", i, pLensParam[i]);
		}
	}
	return ret;
}

void* process_mipitof_data(void* param)
{
	 while (!thread_exit)
    {
        if (!IS_Running)
        {
            usleep(100);
            continue;
        }
		sunny_raw2pcl_produce();
#if 0
		float tmp = tofObj->get_tof_temp();
		LOGI("tofObj->get_tof_temp() %f\n", tmp);
#endif
	 }
	 return NULL;

}

int sunny_raw2pcl_produce(void)
{
	int ret = 0;
	//为sunny点云数据分配缓存,包含点云和depth数据.
	if (pSunnySpectrePCLData == NULL) {
		LOGI("%s: malloc for sunny spectre pcl data\n", __func__);
		pSunnySpectrePCLData=(sunnySpectrePCL_t*)malloc(sizeof(sunnySpectrePCL_t)*DEPTHMAP_W*DEPTHMAP_H);
		if (NULL == pSunnySpectrePCLData) {
			LOGI("%s: malloc sunny spectre pcl data fail\n", __func__);
			return LTOF_ERROR_NO_MEM;
		}
		LOGI("[frame_data]w:%d, h:%d, size:%d sum:%d\n", DEPTHMAP_W,DEPTHMAP_H,sizeof(sunnySpectrePCL_t), DEPTHMAP_W*DEPTHMAP_H*sizeof(sunnySpectrePCL_t));
		LOGI("[frame_data]addr:%p, size:%d\n", pSunnySpectrePCLData, sizeof(sunnySpectrePCL_t)*DEPTHMAP_W*DEPTHMAP_H);
	}
    memset(pSunnySpectrePCLData,0,sizeof(sunnySpectrePCL_t)*DEPTHMAP_W*DEPTHMAP_H);
	//为neolix深度数据分配缓存
	if (pNeolixDepthData == NULL) {
		LOGI("%s: malloc for neolixdepth data\n", __func__);
		pNeolixDepthData=(DepthPixel_t*)malloc(sizeof(DepthPixel_t)*DEPTHMAP_W*DEPTHMAP_H);
		if (NULL == pNeolixDepthData) {
			LOGI("%s: malloc pNeolixDepthData fail\n",__func__);
			return LTOF_ERROR_NO_MEM;
		}
		LOGI("[neolix depth data] addr:%p, size:%d\n", pNeolixDepthData, sizeof(DepthPixel_t)*DEPTHMAP_W*DEPTHMAP_H);
	} 
	memset(pNeolixDepthData,0,sizeof(DepthPixel_t)*DEPTHMAP_W*DEPTHMAP_H); 
	//调用sunny_spectre
	spectre_produce4neolix(exposure_time, pSunnySpectrePCLData, DEPTHMAP_W*DEPTHMAP_H*sizeof(sunnySpectrePCL_t));
	//spectre_init(exposure_time);
	//spectre_produce(pSunnySpectrePCLData, DEPTHMAP_W*DEPTHMAP_H*sizeof(sunnySpectrePCL_t)); 
	//spectre_deinit();
	//转换为新石器需要的深度数据
	 static int i,j;
	//按x,y,z顺序保存深度数据
            for (i = 0; i<172;i++)
            {
                for(j = 0; j<224;j++)
                {
				
					if (pNeolixDepthData != NULL)  { 
						pNeolixDepthData[i*224+j] = (DepthPixel_t)((pSunnySpectrePCLData[i*224+j].z)*1000);  //原生的数据是m,最好转换为mm
					}	
               }
           }
     

	//对数据统计
		tof_sensor_all_data.pPCL = pSunnySpectrePCLData;
		tof_sensor_all_data.pcl_data_size = sizeof(sunnySpectrePCL_t)*DEPTHMAP_W*DEPTHMAP_H;
		tof_sensor_all_data.pDepthData = pNeolixDepthData;
		tof_sensor_all_data.depth_data_size = sizeof(DepthPixel_t)*DEPTHMAP_W*DEPTHMAP_H;
		tof_sensor_all_data.pVideoData = video_data;
		tof_sensor_all_data.video_data_size = DEPTHVIDEO_FRAME_SIZE;
		LOGI("mipitof_data_info:\n");
		LOGI("pDepthData:%p depth_data_size:%d pVideoData:%p video_data_size:%d\n", 
			tof_sensor_all_data.pDepthData,
			tof_sensor_all_data.depth_data_size,
			tof_sensor_all_data.pVideoData,
			tof_sensor_all_data.video_data_size
			);
		if (g_getDepthCallback != NULL)
			g_getDepthCallback(tof_sensor_all_data);
	return ret;
}


void setPreviewStatus(PREVIEW_STATUS sta)
{
	IS_Running = (sta == PREVIEW_START ? true : false); 
}

}








