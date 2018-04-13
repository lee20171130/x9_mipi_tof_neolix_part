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

void initCorrectAmplitudeWiggling_cross (const uint8_t numWiggles,
        const uint32_t *pv_amplitudeWigglingHarm,
        const float *pv_amplitudeWigglingPhase,
        const float *pv_amplitudeWigglingAmp,
        const float amplitudeWigglingOffset,
        float *plut_amplitudeWiggling);

#ifdef __cplusplus
}
#endif
