#ifndef __MEASURE_H__
#define __MEASURE_H__
#include<opencv2/core/core.hpp>
#include"../driverdecorate/base.h"
#include"measure3D.h"
namespace neolix
{
#define IN_
#define OUT_
NEOLIX_STATUS_LIST measureBox(IN_ const cv::Mat depthImage,
				IN_  const double  planePar[3],
				OUT_ float &length,
				OUT_ float &width,
				OUT_ float &height,
               			OUT_ float &minDepth_,
                IN_ bool flage,// 用来标记是用实时的平面建模测量，还提前把平面模型建立好在测量，结果就是测量的范围会不同，先建模后测量的范围会大一写
				IN_  bool  visual = false,
				IN_  bool  useRect = true);
}
#endif
