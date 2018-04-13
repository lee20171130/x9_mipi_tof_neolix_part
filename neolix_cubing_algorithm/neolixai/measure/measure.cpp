#include"measure.h"
#include"../common/DepthRender.hpp"
#include"../imagepro/Utils.h"
//#define TUNING
namespace neolix
{
  extern cv::Mat g_rect_para;
  extern cv::Mat g_plane_para_least;
  extern cv::Mat g_plane_ransca;
  extern cv::Mat g_cammer_intrinic;
  extern cv::Mat g_plane_rect;
  extern short g_fix_length ;
  extern short g_fix_width ;
  extern short g_fix_height;

  static DepthRender render ;
  static cv::vector<cv::Point2f> points(10);
  static float pixLength, pix_width;
  static double paddis,confidence;
  static unsigned short boxDistance;
  static cv::Point2f objCenter;
NEOLIX_STATUS_LIST measureBox(IN_ const cv::Mat depthImage,
				IN_ const double  planePar[3],
				OUT_ float &length,
				OUT_ float &width,
				OUT_ float &height,
                OUT_ float &minDepth_,
                IN_ bool flage,
				IN_  bool  visual,
				IN_  bool  useRect)
{
	cv::Mat depthRoi, colorRoi;
	cv::vector<cv::Point> contours;
	if(true == useRect)
    {
        cv::Rect rects;
        if(true == flage)//先建立好平面模型，在测量,use measureVol()
        {
            rects  = cv::Rect(g_rect_para.at<long>(0,0), g_rect_para.at<long>(1,0),
            g_rect_para.at<long>(2,0), g_rect_para.at<long>(3,0));

        }else{//use measureVol2()
            rects  = cv::Rect(g_plane_rect.at<long>(0,0), g_plane_rect.at<long>(1,0),
            g_plane_rect.at<long>(2,0), g_plane_rect.at<long>(3,0));
        }
        depthRoi = depthImage(rects);
    }else depthRoi = depthImage;
	colorRoi = depthRoi.clone();
	colorRoi = render.Compute(colorRoi);
	if(true == visual)
    {
        cv::imshow("measureDisplayRect",colorRoi);
        cv::Mat colorFull ;
        colorFull = render.Compute(depthImage);
        cv::imshow("measureDisplayFull",colorFull);

    }
	points.clear();
	NEOLIX_STATUS_LIST status = PopRang(colorRoi,contours,pixLength,pix_width,points);
	if(NEOLIX_CANOT_FIND_CONTOURS == status) return NEOLIX_CANOT_FIND_CONTOURS;
	if(NEOLIX_FALSE == status) return NEOLIX_FALSE;

	calCoutousCenter(contours, objCenter);
	points.push_back(objCenter);
	Getavepaddis(points,planePar,paddis);
    unsigned short minDepth = 9999;//set a bigger number
    boxDistance = calculateDepthFromDepthImagInRangeCountour(depthRoi,contours,confidence,minDepth);
	Getxyz2(points, boxDistance,length,width);
    height = static_cast<float>(paddis - minDepth);
    minDepth_ = minDepth;
    if(minDepth > 8000) return NEOLIX_FALSE;

#ifdef TUNING
    g_fix_width = -2.5246e-5*pow(minDepth,2)+0.0701*minDepth -40.6427;
    g_fix_length  = -3.7039e-5*pow(minDepth,2)+0.0954*minDepth-52.6244;
    g_fix_height = -2.9454e-5*pow(minDepth,2)+0.0655*minDepth-45.1611;
    std::cout<<"minDepth:"<<minDepth<<std::endl;
    std::cout<<"g_fix_height"<<g_fix_width<<std::endl;
    std::cout<<"g_fix_length"<<g_fix_length<<std::endl;
    std::cout<<"g_fix_height"<<g_fix_height<<std::endl;
#endif


	return NEOLIX_SUCCESS;
}

}
