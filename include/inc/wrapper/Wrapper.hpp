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

#include <wrapper/SpectreExtended.hpp>

#include <list>
#include <functional>

namespace spectre
{
    namespace wrapper
    {

        class Wrapper
        {
            using ModulePointer = void (Wrapper::*) ();
            using ModulePointerPair = std::pair<std::string, ModulePointer>;
            using ModulePointerMap = std::vector<ModulePointerPair>;

        public:

            Wrapper (element::container::Calibration &calibration,
                     element::container::Input &input,
                     std::string &activationCode);

            virtual ~Wrapper();

            SpectreStatus verify() const;

            SpectreStatus getComposition (SpectreComposition &composition) const;

            SpectreStatus getLensParameter (LensParameter &lensParameter) const;

            SpectreStatus getLensModel (SpectreLensModel &typeLens) const;

            SpectreStatus getCalibrationROI (ROI calibrationROI) const;

            virtual SpectreVersion getVersion() const;

            SpectreStatus getIO (element::container::Input &input,
                                 element::container::Output &output,
                                 element::container::Parameter &parameter,
                                 element::container::Calibration &calibration,
                                 element::container::Intermediate &intermediate) const;

            virtual SpectreStatus setIO (element::container::Input &input,
                                         element::container::Output &output,
                                         element::container::Parameter &parameter,
                                         element::container::Calibration &calibration,
                                         element::container::Intermediate &intermediate);

            bool run (std::string moduleName = "all", uint8_t probeIdx = 0);

            // Methods

            virtual void runFlagMask() = 0;

            virtual void runFlagSaturation() = 0;

            virtual void runUnscrambleReIm() = 0;

            virtual void runUnscrambleIntensity() = 0;

            virtual void runCalcAmplitude() = 0;

            virtual void runCalcPhase() = 0;

            virtual void runFlagAmplitudeThreshold() = 0;

            virtual void runFlagAsymmetry() = 0;

            virtual void runCalcAmplitudeNoise() = 0;

            virtual void runCalcPhaseNoise() = 0;

            virtual void runCorrectAmplitudeWiggling() = 0;

            virtual void runCorrectPhaseWiggling() = 0;

            virtual void runCalcPhase2Distance() = 0;

            virtual void runCorrectTemperature() = 0;

            virtual void runCorrectFPPN() = 0;

            virtual void runCalcNFreq() = 0;

            virtual void runFilterNFreq() = 0;

            virtual void runFilterAdaptiveNoise() = 0;

            virtual void runFlagMPIAmp() = 0;

            virtual void runFlagMPICalc() = 0;

            virtual void runFlagMPIDist() = 0;

            virtual void runFlagNoise() = 0;

            virtual void runCalcCartesianCoordinates() = 0;

            virtual void runFlagFlyingPixel() = 0;

            virtual void runCalcGrayscale() = 0;

            virtual void runCalcAutoExposure() = 0;

            virtual void runValidImage() = 0;


        protected:

            std::unique_ptr<SpectreExtended> m_spectreEx;
            const std::string m_activationCode;

            ModulePointerMap m_modulePointerMap;

            uint8_t m_sizeProbeData;
            uint8_t m_probeIdx;

            uint8_t m_calcPixelStartIdx;
            uint8_t m_calcPixelEndIdx;

        };
    }
}
