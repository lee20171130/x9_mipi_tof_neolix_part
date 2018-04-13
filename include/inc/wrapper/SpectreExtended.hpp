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

#include <memory>

#include <spectre/Spectre.hpp>

struct SpectreIO;

namespace spectre
{
    namespace wrapper
    {


        /**
        * The SpectreExtende class is an subclass of the Spectre processing.
        * Currentl it is in used for the Wrapper structure only
        */
        class SpectreExtended : public spectre::Spectre
        {
        public:

            /**
            *   Constructor of SpectreExtended, automaticall calls the processing initialization function initProcessings method
            *
            *   @param calib Calibration data used for intrinsic error compensation.
            *   @param param Parameter data used for runtime processing configuration.
            *   @param inter Intermediate data used to store and handle intermediate processing data.
            *   @param input Input data comprises raw data, temperature data as well as the imager configuration settings.
            *   @param output Input data of pmd Time-Of-Flight depth data processing.
            */
            SpectreExtended (const element::container::Calibration &calib,
                             const element::container::Parameter &param,
                             const element::container::Intermediate &inter,
                             const element::container::Input &input,
                             const element::container::Output &output);

            /**
            *   Destructor of SpectreExtended , automatically calls the processing deinitialization functions.
            */
            virtual ~SpectreExtended();

            /**
            *   LEVEL 3
            *   Sets the processing input data for spectre.
            *
            *   @param valueIn data container to be set.
            *   @return Status of operation.
            */
            SpectreStatus setInput (element::container::Input &valueIn, const std::string &activationCode);
            /**
            *   LEVEL 3
            *   Sets the processing output data for spectre.
            *
            *   @param valueIn data container to be set.
            *   @return Status of operation.
            */
            SpectreStatus setOutput (element::container::Output &valueIn, const std::string &activationCode);

            /**
            *   LEVEL 3
            *   Sets the processing Calibration data for spectre.
            *
            *   @param valueIn data container to be set.
            *   @return Status of operation.
            */
            SpectreStatus setCalibration (element::container::Calibration &valueIn, const std::string &activationCode);

            /**
            *   LEVEL 3
            *   Sets the processing Intermediate data for spectre.
            *
            *   @param valueIn data container to be set.
            *   @return Status of operation.
            */
            SpectreStatus setIntermediate (element::container::Intermediate &valueIn, const std::string &activationCode);

            /**
            *   LEVEL 3
            *   Retrieves the Spectre Input, Output, Parmaeter,
            *   Calibration and Intermediate data for spectre.
            *
            *   @param input Input data container to be retrieved.
            *   @param output Output data container to be retrieved.
            *   @param parmeter Parameter data container to be retrieved.
            *   @param calibration Calibration data container to be retrieved.
            *   @param intermediate Intermediate data container to be retrieved.
            *   @return Status of operation.
            */
            SpectreStatus getIO (element::container::Input &input,
                                 element::container::Output &output,
                                 element::container::Parameter &parameter,
                                 element::container::Calibration &calibration,
                                 element::container::Intermediate &intermediate,
                                 const std::string &activationCode) const;

            /**
            *   LEVEL 3
            *   Sets the Spectre Input, Output, Parmaeter,
            *   Calibration and Intermediate data for spectre.
            *
            *   @param input Input data container to be set.
            *   @param output Output data container to be set.
            *   @param parmeter Parameter data container to be set.
            *   @param calibration Calibration data container to be set.
            *   @param intermediate Intermediate data container to be set.
            *   @return Status of operation.
            */
            SpectreStatus setIO (element::container::Input &input,
                                 element::container::Output &output,
                                 element::container::Parameter &parameter,
                                 element::container::Calibration &calibration,
                                 element::container::Intermediate &intermediate,
                                 const std::string &activationCode);

        };
    }
}
