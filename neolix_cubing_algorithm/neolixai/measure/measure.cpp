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

///*
void GetCenterDepthInfo(IN_ const cv::Mat depthImage,
			OUT_ float &fMax,
			OUT_ float &fMin,
			OUT_ float &fDiff)
{
	int nW = depthImage.cols;
	int nH = depthImage.rows;

	short nMax = 0;
	short nMin = 10000;
	short nVal = 0;
	const int nBand = 1;
	for (int row = nH/2-nBand; row <= nH/2+nBand; row++)
	{
		auto rowPtr = depthImage.ptr<short>(row);
		for (int col =nW/2-nBand; col <= nW/2 + nBand; col++)
		{

			nVal = rowPtr[col];
			nMax = nMax > nVal?nMax : nVal;
			nMin = nMin < nVal?nMin : nVal;
		}
	}
	fMax = nMax * 1.00;
	fMin = nMin * 1.00;
	fDiff = (nMax - nMin) * 1.00;
}
//*/

double GetMinDepthInROI_Plane(IN_ const cv::Mat depthImage, IN_ cv::Rect rec, const double a[], OUT_ float &minDepth)
{
	int nW = depthImage.cols;
	int nH = depthImage.rows;
	short nMin = 10000;
	float fMin = 10000.00;
	short nVal = 0;
	const int nBand = 1;

	int left_x = g_rect_para.at<int>(0, 0);
    	int left_y = g_rect_para.at<int>(1, 0);
	double fa = a[0],fb = a[1],fc=-1.0000, fd = 100000000; 

/*
	int nYStart = nH/2-5;
	int nYEnd = nH/2 + 11;
	int nXStart = nW/2-5;
	int nXEnd = nW/2 + 11;
*/
///*	
	int nYStart = nH/4;
	int nYEnd = nH/4 + nH/2;
	int nXStart = nW/4;
	int nXEnd = nW/4 + nW/2;
//*/
///*
	short nX_Loc = -1;
	short nY_Loc = -1;
	short nZ_Loc = 1000000;

	double  dd = 1000000;
	int nSum = 0;

	for (int row = nYStart; row <= nYEnd; row++)
	{
		auto rowPtr = depthImage.ptr<short>(row);
		for (int col = nXStart; col <= nXEnd; col++)
		{
			nVal = rowPtr[col];
			if ((nVal > 10) && (nVal < 80000))
			{
				if(nZ_Loc > nVal)
				{
					nX_Loc = col;
					nY_Loc = row;
					nZ_Loc = nVal;
				}

			fd = -(fc * nZ_Loc + fa * (nX_Loc + left_x) + fb * (nY_Loc+ left_y));
			dd = dd < fd ? dd : fd;
			}
		}
	}

	minDepth = dd;
	return abs(dd - a[2])/sqrt(fa * fa + fb * fb + 1);
}



/*
Function: Find the min depth in roi
*/
void GetMinDepthInROI(IN_ const cv::Mat depthImage, IN_ cv::Rect rec, const double a[], OUT_ float &minDepth)
{
	int nW = depthImage.cols;
	int nH = depthImage.rows;

	short nMin = 10000;
	float fMin = 10000.00;
	short nVal = 0;
	const int nBand = 1;

	int nYStart = nH/4;
	int nYEnd = nH/4 + nH/2;
	int nXStart = nW/4;
	int nXEnd = nW/4 + nW/2;

///*
 //-----水平

	for (int row = nYStart; row <= nYEnd; row++)
	{
		auto rowPtr = depthImage.ptr<short>(row);
		for (int col = nXStart; col <= nXEnd; col++)
		{
			nVal = rowPtr[col];
			if ((nVal > 10) && (nVal < 80000))
				nMin = nMin < nVal?nMin : nVal;
		}
	}

	minDepth = nMin*1.00;
//*/

/**
	*ÆœÃæ·œ³Ì z = x*a[0] + y *a[1] + a[2]
	*/

   /*	int left_x = g_rect_para.at<int>(0, 0);
    	int left_y = g_rect_para.at<int>(1, 0);


	double high;
	double dist_origin = abs(a[2])/sqrt(a[0]*a[0]+1 + a[1]*a[0]);

	for (int row = nYStart; row <= nYEnd; row++)
	{
		auto rowPtr = depthImage.ptr<short>(row);
		for (int col = nXStart; col <= nXEnd; col++)
		{
			high = a[0]*(col + left_x)+a[1]*(row + left_y)+a[2];
			if ((high > 10.00) && (high < 8000.00))
				fMin = fMin < high?fMin : high;

		}
	}


	minDepth = fMin;
*/
}

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
#define DEBUG_ERRORCODE

	cv::Mat depthRoi, colorRoi;
	cv::vector<cv::Point> contours;

	cv::Rect rects;

	if(true == useRect)
   	{
       		//cv::Rect rects;
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
	if(NEOLIX_CANOT_FIND_CONTOURS == status)
	{ 
#ifdef DEBUG_ERRORCODE
		length = 99999.11111;
		width =  99999.11111;
		height = 99999.11111;
		return NEOLIX_SUCCESS;
#else
		return NEOLIX_CANOT_FIND_CONTOURS;
#endif
	}
	if(NEOLIX_FALSE == status)
	{
#ifdef DEBUG_ERRORCODE
		length = 99999.22222;
		width =  99999.22222;
		height = 99999.22222;
		return NEOLIX_SUCCESS;
#else
	 	return NEOLIX_FALSE;
		
#endif
	}
	calCoutousCenter(contours, objCenter);
	points.push_back(objCenter);

	Getavepaddis(points,planePar, paddis);

	unsigned short minDepth = 9999;//set a bigger number
    	boxDistance = calculateDepthFromDepthImagInRangeCountour(depthRoi,contours,confidence,minDepth);

	Getxyz2(points, boxDistance,length,width);
	height = static_cast<float>(paddis - minDepth);

//#define DEBUGINFO_ZC

#ifndef DEBUGINFO_ZC
	float fMin = 0.00;
	medianBlur(depthImage , depthImage , 5); 	
	GetMinDepthInROI(depthImage, rects, planePar, fMin);
	//double tt = GetMinDepthInROI_Plane(depthImage, rects, planePar, fMin);
	height = static_cast<float>(paddis - fMin);
	//height = static_cast<float>(tt);
#else
	//***Debug Start***//

	double fRatio = 0.00000, fDsit = 0.00000;
	double fa = planePar[0];
	double fb = planePar[1];
	double fc = -1.00000;
	double fd = planePar[2];
	fRatio = 1.00000/sqrt(fa*fa+fb*fb+fc*fc);

	double fRation_New = acos(fRatio) * 180.00/3.1415926;
	
	medianBlur(depthImage , depthImage , 5); //边缘噪声的存在，用中值滤波器滤掉（在70cm左右合适）
	
	float fMin = 0.00, ffMin = 0.00;	
	GetMinDepthInROI(depthImage, rects, planePar, fMin);

	double tt = GetMinDepthInROI_Plane(depthImage, rects, planePar, ffMin);
	
	//GetCenterDepthInfo(depthImage, fMax, fMin, fDiff);

	//length = fa;//paddis;//fRatio;//acos(fRatio)*180.00/3.1415926;//base  26
	//width = paddis - fMin;//fb;//
	height = tt;//static_cast<float>(paddis - fMin);//tt;//static_cast<float>(paddis - ffMin/*fMin*/);
	
	//****Debug End***//
#endif
   
   	minDepth_ = minDepth;
	if(minDepth > 8000)
	{
#ifdef DEBUG_ERRORCODE
		length = 99999.33333;
		width =  99999.33333;		
		height = 99999.33333;
		return NEOLIX_SUCCESS;
#else
		return NEOLIX_FALSE;
#endif	
	}

#ifdef TUNING
    g_fix_width = -2.5246e-5*pow(minDepth,2)+0.0701*minDepth -40.6427;
    g_fix_length = -3.7039e-5*pow(minDepth,2)+0.0954*minDepth-52.6244;
    g_fix_height = -2.9454e-5*pow(minDepth,2)+0.0655*minDepth-45.1611;
    std::cout<<"minDepth:"<<minDepth<<std::endl;
    std::cout<<"g_fix_height"<<g_fix_width<<std::endl;
    std::cout<<"g_fix_length"<<g_fix_length<<std::endl;
    std::cout<<"g_fix_height"<<g_fix_height<<std::endl;
#endif


	return NEOLIX_SUCCESS;
}

}
