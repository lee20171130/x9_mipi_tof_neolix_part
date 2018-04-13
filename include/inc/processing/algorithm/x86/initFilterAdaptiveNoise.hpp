/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <processing/common/commonMethods.hpp>

void initFilterAdaptiveNoise_x86 (float *plut_anfGauss,
                                  uint32_t anfGaussSize,
                                  float precision);

#ifdef __cplusplus
}
#endif

