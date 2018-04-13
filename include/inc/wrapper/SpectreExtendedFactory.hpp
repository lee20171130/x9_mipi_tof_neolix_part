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

#include <spectre/SpectreFactory.hpp>
#include <wrapper/SpectreExtended.hpp>


namespace spectre
{
    namespace wrapper
    {

        /**
        *  Main Factory Class for Spectre TOF data processing
        */
        class SpectreExtendedFactory : public SpectreFactory
        {
        public:
            /**
             * Ctor
             * Constructs a factory for the specific version
             *
             *
             * @param version requested spectre version
             */
            explicit SpectreExtendedFactory (SpectreVersion version = SpectreVersion::ASTON);

            /**
            *   Destructor of the spectre main factory class
            */
            virtual ~SpectreExtendedFactory();

            /*  Retrieves extended Spectre Processing initialized with binary files.
            *   The input, output and intermediate data will be initialized with
            *   values according to the calibration and input source file definition.
            *   The input, output, parameter and intermediate data container
            *   instantiated in a default configuration.
            *
            *   @param calibSource Binary container with preset calibration data definition.
            *   @param activationCode Necessary to activate specific access level.
            *   @return Spectre processing. Nullptr if the composition is invalid.
            */
            std::unique_ptr<SpectreExtended> getSpectreExtended (const std::vector<uint8_t> &calibSource,
                    const std::vector<uint8_t> &inputSource,
                    const std::string &activationCode = "") const;

            /*  Retrieves Spectre Processing initialized with container data.
            *   The output and intermediate data will be initialized with
            *   values according to the calibration and input source file definition.
            *   The input, output, parameter and intermediate data container
            *   instantiated in a default configuration.
            *
            *   @param calibSource Binary container with preset calibration data definition.
            *   @param activationCode Necessary to activate specific access level.
            *   @return Spectre processing. Nullptr if the composition is invalid.
            */
            std::unique_ptr<SpectreExtended> getSpectreExtended (const spectre::element::container::Calibration &calibSource,
                    const spectre::element::container::Input &inputSource,
                    const std::string &activationCode = "") const;


        };

    }
}
