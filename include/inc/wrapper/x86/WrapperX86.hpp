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

#include <wrapper/ref/WrapperReference.hpp>

#include <processing/aston/astonProcessing.hpp>

namespace spectre
{
    namespace wrapper
    {
        class WrapperX86 : public WrapperReference
        {

        public:
            WrapperX86 (element::container::Calibration &calibration,
                            element::container::Input &input,
                            std::string &activationCode);

            virtual ~WrapperX86();

            virtual SpectreStatus setIO (element::container::Input &input,
                                         element::container::Output &output,
                                         element::container::Parameter &parameter,
                                         element::container::Calibration &calibration,
                                         element::container::Intermediate &intermediate) override;

            virtual void runFlagMask() override;

            virtual void runFlagSaturation() override;

            virtual void runUnscrambleReIm() override;

            virtual void runUnscrambleIntensity() override;

            virtual void runCalcAmplitude() override;

            virtual void runCalcPhase() override;

            virtual void runFlagAmplitudeThreshold() override;

            virtual void runFlagAsymmetry() override;

            virtual void runCalcAmplitudeNoise() override;

            virtual void runCalcPhaseNoise() override;

            virtual void runCorrectAmplitudeWiggling() override;

            virtual void runCorrectPhaseWiggling() override;

            virtual void runCalcPhase2Distance() override;

            virtual void runCorrectTemperature() override;

            virtual void runCorrectFPPN() override;

            virtual void runCalcNFreq() override;

            virtual void runFilterNFreq() override;

            virtual void runFilterAdaptiveNoise() override;

            virtual void runFlagMPICalc() override;

            virtual void runFlagMPIAmp() override;

            virtual void runFlagMPIDist() override;

            virtual void runFlagNoise() override;

            virtual void runCalcCartesianCoordinates() override;

            virtual void runFlagFlyingPixel() override;

            virtual void runCalcGrayscale() override;

            virtual void runCalcAutoExposure() override;

            virtual void runValidImage() override;

        protected:

            virtual bool initialize();

        };
    }
}
