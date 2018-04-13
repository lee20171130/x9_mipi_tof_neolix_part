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

#include <processing/common/commonMethods.hpp>

void initCorrectPhaseWiggling_cross (const uint8_t numWiggles,
                                     const uint32_t *pv_PWiggleHarm,
                                     const float *pv_PWigglePhase,
                                     const float *pv_PWiggleAmp,
                                     float *plut_phaseWiggling);

#ifdef __cplusplus
}
#endif
