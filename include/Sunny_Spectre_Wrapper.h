#pragma once 
#include "libTof.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <android/log.h>

#define NATIVE_WRAPPER_DEBUG
/** 16-bit unsigned integer. */ 
typedef	unsigned short		UInt16_t;
typedef UInt16_t DepthPixel_t;
typedef int BOOL;
#define FALSE 0
#define TRUE 1
#define ROUND_UP(x, align) (x+(align-1))&(~(align-1))
//typedef void (*getDepthFunc_t)(void *, int);
typedef struct  {
	float x;
	float y;
	float z;
	float noise;
} sunnySpectrePCL_t;
typedef struct {
	bool isMonoFreq;
	int expourseTime;
} tofModeOption_t;
typedef enum {
	MODE0_5FPS_1200US = 0,
	MODE1_10FPS_650US,
	MODE2_15FPS_850US,
	MODE3_30FPS_380US,
	MODE4_45FPS_250US,
	
} tofUseScene_t;
typedef struct {
	sunnySpectrePCL_t *pPCL;
	unsigned int pcl_data_size;
	DepthPixel_t * pDepthData;
	unsigned int  depth_data_size;
	short * pVideoData;
	unsigned int  video_data_size;
	FrameDataRgb_t *pGrayData;
	unsigned int  gray_data_size;
} tofSensorAllData_t;

typedef enum {
	PREVIEW_START = 0,
	PREVIEW_STOP
} PREVIEW_STATUS;
typedef void (*getDepthFunc_t)(tofSensorAllData_t&);


namespace sunny {
	void setPreviewStatus(PREVIEW_STATUS sta);
	int genE2promFile(void);
	int getTofLensParam(double *pLensParam);
	void registerJNIGetDepthCB(getDepthFunc_t getDepth);
	int connect_mipitof(DeviceInfo_t &devInfo);
	int disconnect_mipitof();
}

