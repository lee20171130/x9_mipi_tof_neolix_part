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
#define _CRT_SECURE_NO_WARNINGS

#include <sample/spectreSample.hpp>

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <thread>
#ifndef SPECTRESAMPLECALC_H
#define SPECTRESAMPLECALC_H


#include <system/toolsTimer.hpp>
#include <system/toolsIO.hpp>
#include <system/BoundaryConditionsManager.hpp>
#include <system/SystemIOReal.hpp>
#include <common/version.hpp>

#ifdef __cplusplus
extern "C" {
#include <processing/processingInternal.hpp>
#include <processing/tools/astonTools.hpp>
}
#endif

#define char_CAST( param ) reinterpret_cast<char *> ( param )

namespace spectre
{
    namespace sample
    {

        std::string getDefaultDataPath();

        struct Data
        {
            struct SpectreCalibration *ps_calib;
            struct SpectreParameter *ps_param;
            struct SpectreInput *ps_input;
            struct SpectreOutput *ps_output;
            struct SpectreIntermediate *ps_inter;

            std::string workingDir = getDefaultDataPath();

            float meanDistance = 0.0f;
            int numValidPixels = 0;
            float meanTime = 0.0f;
            std::vector<double> vfps;
        };

        void initMemory (struct Data &data);

        void freeMemory (struct Data &data);

        void runProcessing (struct Data &data);

        void calcMeanDistanceAndValidPixels (uint32_t numPixels, float *distances, uint32_t *flags, struct Data &data);

        void calcMeanTimeAndFps (struct Data &data, bool noStop);

        void printMeanDistanceAndValidPixels (struct Data &data);

        void printMeanTimeAndFps (struct Data &data);
    }
}

#endif
