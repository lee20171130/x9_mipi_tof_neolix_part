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

#include <memory>
#include <vector>
#include <spectre/SpectreVersion.hpp>
#include <spectre/SpectreStatus.hpp>

struct SpectreCalibration;

namespace spectre
{
    class Spectre;

    namespace element
    {
        namespace builder
        {
            class CalibrationBuilder;
            class InputBuilder;
            class OutputBuilder;
            class ParameterBuilder;
        }

        namespace container
        {
            class Calibration;
            class Input;
            class Output;
            class Parameter;
        }
    }

    /**
    *  Main Factory Class for Spectre TOF data processing
    */
    class SpectreFactory
    {
    public:
        using SpectreReturnPair = std::pair<std::unique_ptr<spectre::Spectre>, spectre::SpectreStatus>;


        /**
         * Ctor
         * Constructs a factory for the specific version
         *
         *
         * @param version requested spectre version
         */
        explicit SpectreFactory (SpectreVersion version = SpectreVersion::ASTON);

        /**
        *   Destructor of the spectre main factory class
        */
        virtual ~SpectreFactory();

        /*   @deprecated Container serialization will be removed, this function only supports the ASTON format
         *
         *   Retrieves Spectre Processing initialized with binary files.
         *   The input and output data will be initialized with
         *   values according to the calibration and input source file definition.
         *   The input, output, and parameter data container
         *   instantiated in a default configuration.
         *
         *   @param calibSource Binary container with preset calibration data definition.
         *   @param inputSource Binary container with preset input data definition
         *   @param activationCode Necessary to activate specific access level.
         *   @return Spectre processing (nullptr on an error), and a status code.
         */
        SpectreReturnPair getSpectre (const std::vector<uint8_t> &calibSource,
                                      const std::vector<uint8_t> &inputSource,
                                      const std::string &activationCode = "") const;

        /*   @deprecated Calibration handling will be moved to libcalibration
         *
         *   Retrieves Spectre Processing initialized with container data.
         *   The output data will be initialized with
         *   values according to the calibration and input source file definition.
         *   The input, output, and parameter data container
         *   instantiated in a default configuration.
         *
         *   @param calibSource Binary container with preset calibration data definition.
         *   @param activationCode Necessary to activate specific access level.
         *   @return Spectre processing (nullptr on an error), and a status code
         */
        SpectreReturnPair getSpectre (const spectre::element::container::Calibration &calibSource,
                                      const spectre::element::container::Input &inputSource,
                                      const std::string &activationCode = "") const;

        /**
         * Retrieves Spectre processing initialized with a binary calibration stream, and an
         * appropriate input container.
         *
         *   The output data will be initialized with
         *   values according to the calibration and input source file definition.
         *   The input, output, and parameter data container instantiated in a default configuration.
         *
         * @param calibSource calibration binary source
         * @param inputSource input container
         * @param activationCode activation code
         *
         * @return Spectre processing (nullptr on an error), and a status code
         */
        SpectreReturnPair getSpectre (const std::vector<uint8_t> &calibSource,
                                      const spectre::element::container::Input &inputSource,
                                      const std::string &activationCode = "");

        SpectreFactory::SpectreReturnPair getSpectre (struct SpectreCalibration *calib,
                const spectre::element::container::Input &inputSource,
                const std::string &activationCode);

        /*   @deprecated Calibration handling will be moved to libcalibration
         *
         *   Retrieves Spectre calibration data builder according to the stated version definition.
         *   As Default latest spectre calibration builder is returned.
         *
         *   @param version Version defintion for backwards compatibility.
         *   @param activationCode Necessary to activate specific access level.
         *   @return Handle to the spectre Processing. Nullptr if the stated version is not supported.
         */
        std::unique_ptr<spectre::element::builder::CalibrationBuilder> getCalibrationBuilder (const std::string &activationCode = "") const;

        /*  Retrieves Spectre output data builder according to the stated version definition.
        *   As Default latest spectre output builder is returned.
        *
        *   @param version Version definition for backwards compatibility.
        *   @param activationCode Necessary to activate specific access level.
        *   @return Handle to the spectre output builder. Nullptr if the stated version is not supported.
        */
        std::unique_ptr<spectre::element::builder::OutputBuilder> getOutputBuilder (const std::string &activationCode = "") const;

        /*  Retrieves Spectre input data builder according to the stated version definition.
        *   As Default latest spectre input builder is returned.
        *
        *   @param version Version definition for backwards compatibility.
        *   @param activationCode Necessary to activate specific access level.
        *   @return Handle to the spectre input builder. Nullptr if the stated version is not supported.
        */
        std::unique_ptr<spectre::element::builder::InputBuilder> getInputBuilder (const std::string &activationCode = "") const;

        /*  Retrieves Spectre parameter data builder according to the stated version definition.
        *   As Default latest spectre parameter builder is returned.
        *
        *   @param version Version definition for backwards compatibility.
        *   @param activationCode Necessary to activate specific access level.
        *   @return Handle to the spectre parameter builder. Nullptr if the stated version is not supported.
        */
        std::unique_ptr<spectre::element::builder::ParameterBuilder> getParameterBuilder (const std::string &activationCode = "") const;

        template <typename Builder>
        std::unique_ptr<Builder> getBuilder (const std::string &activationCode = "") const;

    private:
        SpectreReturnPair getErrorReturn (spectre::SpectreStatus errorCode) const;

    private:
        SpectreVersion m_version;       //< Current Spectre build version
    };

}
