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

#include<numEmulator/FixedPointPtr.hpp>
#include <processing/processing.hpp>

using namespace spectre::numEmulator;

/** \brief fixed point implementation of the appropiate spectreOutputAutoExposure struct
 */

struct SpectreFPOutputProbeData
{
    typedef int32_t FixPType;

    //constructor
    SpectreFPOutputProbeData (const SpectreOutput *output, uint8_t idx) :
        m_distance (FixedPointPtr<1, FixPType, float> (output->pns_probeData[idx].pm_distance, output->numColumns * output->numRows)),
        m_distanceNoise (FixedPointPtr<1, FixPType, float> (output->pns_probeData[idx].pm_distanceNoise, output->numColumns * output->numRows)),
        m_amplitude (FixedPointPtr<14, FixPType, float> (output->pns_probeData[idx].pm_amplitude, output->numColumns * output->numRows)),
        m_amplitudeNoise (FixedPointPtr<14, FixPType, float> (output->pns_probeData[idx].pm_amplitudeNoise, output->numColumns * output->numRows))
    {

    }

    //fixed point values
    FixedPointPtr<1, FixPType, float> m_distance;
    FixedPointPtr<1, FixPType, float> m_distanceNoise;
    FixedPointPtr<14, FixPType, float> m_amplitude;
    FixedPointPtr<14, FixPType, float> m_amplitudeNoise;
};

/** \brief fixed point implementation of the appropiate spectreOutput struct
 */

struct SpectreFPOutput
{
    typedef int32_t FixPType;

    //default-constructor
    SpectreFPOutput() :
        m_version (0),
        m_type (0),

        m_numColumns (0),
        m_numRows (0),

        m_distance (FixedPointPtr<1, FixPType, float>()),
        m_distanceNoise (FixedPointPtr<1, FixPType, float>()),
        m_amplitude (FixedPointPtr<1, FixPType, float>()),
        m_3d_coord (FixedPointPtr<1, FixPType, float>()),
        m_intensity (FixedPointPtr<19, FixPType, float>()),

        m_flags (FixedPointPtr<1, FixPType, uint32_t>()),
        m_numFrameSets (0),
        m_exposureTimesOut (FixedPointPtr<1, FixPType, uint32_t>())
    {}

    //constructor
    SpectreFPOutput (const SpectreOutput *output) :
        m_version (output->version) ,
        m_type (output->type),

        m_numColumns (output->numColumns),
        m_numRows (output->numRows) ,

        m_distance (FixedPointPtr<1, FixPType, float> (output->pm_distance, m_numColumns * m_numRows)),
        m_distanceNoise (FixedPointPtr<1, FixPType, float> (output->pm_distanceNoise, m_numColumns * m_numRows)),
        m_amplitude (FixedPointPtr<1, FixPType, float> (output->pm_amplitude, m_numColumns * m_numRows)),
        m_3d_coord (FixedPointPtr<1, FixPType, float> (output->pm3d_coord, m_numColumns * m_numRows * 3)),
        m_intensity (FixedPointPtr<19, FixPType, float> (output->pm_intensity, m_numColumns * m_numRows)),

        m_flags (FixedPointPtr<1, FixPType, uint32_t> (output->pm_flags, m_numColumns * m_numRows)),
        m_numFrameSets (output->numFrameSets),
        m_exposureTimesOut (FixedPointPtr<1, FixPType, uint32_t> (output->pv_exposureTimesOut, m_numFrameSets))
    {
        mv_probeData.clear();
        for (uint8_t idx = 0; idx < output->sizeProbeData; idx++)
        {
            mv_probeData.push_back (SpectreFPOutputProbeData (output, idx));
        }
    }

    //fixed point values
    uint16_t m_version;
    uint16_t m_type;

    uint16_t m_numColumns;
    uint16_t m_numRows;

    FixedPointPtr<1, FixPType, float> m_distance;
    FixedPointPtr<1, FixPType, float> m_distanceNoise;
    FixedPointPtr<1, FixPType, float> m_amplitude;
    FixedPointPtr<1, FixPType, float> m_3d_coord;
    FixedPointPtr<19, FixPType, float> m_intensity;

    std::vector<SpectreFPOutputProbeData> mv_probeData;

    FixedPointPtr<1, FixPType, uint32_t> m_flags;
    uint8_t m_numFrameSets;
    FixedPointPtr<1, FixPType, uint32_t> m_exposureTimesOut;
};

