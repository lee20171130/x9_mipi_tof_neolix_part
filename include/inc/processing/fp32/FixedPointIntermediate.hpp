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

#include <stdint.h>
#include <numEmulator/FixedPointPtr.hpp>
#include <processing/processingInternal.hpp>

using namespace spectre::numEmulator;

/** \brief fixed point implementation of the appropiate spectreIntermediateProbeData struct
 */

struct SpectreFPIntermediateProbeData
{
    typedef int32_t FixPType;

    //constructor
    SpectreFPIntermediateProbeData (const SpectreIntermediate *inter, uint8_t idx) :

        m_re (FixedPointPtr<1, FixPType, float> (inter->pns_probeData[idx].pm_re, inter->imageSize)),
        m_im (FixedPointPtr<1, FixPType, float> (inter->pns_probeData[idx].pm_im, inter->imageSize)),
        m_asym (FixedPointPtr<1, FixPType, float> (inter->pns_probeData[idx].pm_asym, inter->imageSize)),
        m_amplitudeNorm (FixedPointPtr<1, FixPType, float> (inter->pns_probeData[idx].pm_amplitudeNorm, inter->imageSize)),
        m_amplitudeNoiseNorm (FixedPointPtr<1, FixPType, float> (inter->pns_probeData[idx].pm_amplitudeNoiseNorm, inter->imageSize)),
        m_range (FixedPoint<1, FixPType> (inter->pns_probeData[idx].range))
    {

    }

    //fixed point values
    FixedPointPtr<1, FixPType, float> m_re;
    FixedPointPtr<1, FixPType, float> m_im;
    FixedPointPtr<1, FixPType, float> m_asym;
    FixedPointPtr<1, FixPType, float> m_amplitudeNorm;
    FixedPointPtr<1, FixPType, float> m_amplitudeNoiseNorm;
    FixedPoint<1, FixPType> m_range;
};

/** \brief fixed point implementation of the appropiate spectreIntermediateAutoExposure struct
 */

struct SpectreFPIntermediateAutoExposure
{
    typedef int32_t FixPType;

    //default-constructor
    SpectreFPIntermediateAutoExposure() :
        m_mask (FixedPointPtr<1, FixPType, uint8_t>()),
        m_binSize (0),
        m_bin (FixedPointPtr<1, FixPType, float>()),
        m_quantilePos (0)
    {}

    //constructor
    SpectreFPIntermediateAutoExposure (const SpectreIntermediate *inter) :
        m_mask (FixedPointPtr<1, FixPType, uint8_t> (inter->autoExposure.pm_mask, inter->imageSize)),
        m_binSize (inter->autoExposure.binSize),
        m_bin (FixedPointPtr<1, FixPType, float> (inter->autoExposure.pv_bin, m_binSize)),
        m_quantilePos (inter->autoExposure.quantilePos)
    {
    }

    //fixed point values
    FixedPointPtr<1, FixPType, uint8_t> m_mask;
    uint32_t m_binSize;
    FixedPointPtr<1, FixPType, float> m_bin;
    uint32_t m_quantilePos;
};

/** \brief fixed point implementation of the appropiate spectreIntermediate struct
 */

struct SpectreFPIntermediate
{
    typedef int32_t FixPType;

    //default-constructor
    SpectreFPIntermediate() :
        m_intensity (FixedPointPtr<19, FixPType, float>()),
        m_relNoise (FixedPointPtr<1, FixPType, float>()),
        m_phase (FixedPointPtr<1, FixPType, float>()),
        m_phaseNoise (FixedPointPtr<14, FixPType, float>()),
        m_distFilter (FixedPointPtr<1, FixPType, float>()),
        m_ampFlagLevel (FixedPointPtr<1, FixPType, float>()),
        m_deltaDistance (FixedPointPtr<1, FixPType, float>()),
        m_floatTemp (FixedPointPtr<1, FixPType, float>()),

        m_posProbeData (FixedPointPtr<1, FixPType, uint8_t>()),
        m_autoExposure (SpectreFPIntermediateAutoExposure()),

        m_anfGaussPrecision (FixedPoint<1, FixPType>()),
        m_anfGaussSize (FixedPoint<1, FixPType>())
    {
    }

    //constructor
    SpectreFPIntermediate (const SpectreIntermediate *inter) :
        m_intensity (FixedPointPtr<19, FixPType, float> (inter->pm_intensity, inter->imageSize)) ,
        m_relNoise (FixedPointPtr<1, FixPType, float> (inter->pm_relNoise, inter->imageSize)),
        m_phase (FixedPointPtr<1, FixPType, float> (inter->pm_phase, inter->imageSize)),
        m_phaseNoise (FixedPointPtr<14, FixPType, float> (inter->pm_phaseNoise, inter->imageSize)),
        m_distFilter (FixedPointPtr<1, FixPType, float> (inter->pm_distFilter, inter->imageSize)),
        m_ampFlagLevel (FixedPointPtr<1, FixPType, float> (inter->pm_ampFlagLevel, inter->imageSize)),
        m_deltaDistance (FixedPointPtr<1, FixPType, float> (inter->pm_deltaDistance, inter->imageSize)),
        m_floatTemp (FixedPointPtr<1, FixPType, float> (inter->pm_floatTemp, inter->imageSize)) ,

        m_posProbeData (FixedPointPtr<1, FixPType, uint8_t> (inter->pv_posProbeData, inter->sizeProbeData)) ,
        m_autoExposure (SpectreFPIntermediateAutoExposure (inter)),

        m_anfGaussPrecision (FixedPoint<1, FixPType> (inter->anfGaussPrecision)),
        m_anfGaussSize (FixedPoint<1, FixPType> (inter->anfGaussSize))
    {
        mv_probeData.clear();
        for (uint8_t idx = 0; idx < inter->sizeProbeData; idx++)
        {
            mv_probeData.push_back (SpectreFPIntermediateProbeData (inter, idx));
        }
    };

    //fixed point values
    FixedPointPtr<19, FixPType, float> m_intensity;
    FixedPointPtr<1, FixPType, float> m_relNoise;
    FixedPointPtr<1, FixPType, float> m_phase;
    FixedPointPtr<14, FixPType, float> m_phaseNoise;
    FixedPointPtr<1, FixPType, float> m_distFilter;
    FixedPointPtr<1, FixPType, float> m_ampFlagLevel;
    FixedPointPtr<1, FixPType, float> m_deltaDistance;
    FixedPointPtr<1, FixPType, float> m_floatTemp;

    FixedPointPtr<1, FixPType, uint8_t> m_posProbeData;
    std::vector<SpectreFPIntermediateProbeData> mv_probeData;
    SpectreFPIntermediateAutoExposure m_autoExposure;

    FixedPoint<1, FixPType> m_anfGaussPrecision;
    FixedPoint<1, FixPType> m_anfGaussSize;
};
