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

#include <spectre/element/builder/Builder.hpp>
#include <spectre/element/container/Calibration.hpp>
#include <spectre/element/container/Input.hpp>
#include <spectre/SpectreTypeCalibration.hpp>

namespace spectre
{
    namespace element
    {
        namespace builder
        {

            /**
            * Base builder class for calibration data container
            */
            class CalibrationBuilder : public spectre::element::builder::Builder
            {
            public:
                using BuildType = container::Calibration;
                /**
                * Constructor for the calibration data builder base class.
                *
                * @param activationCode Necessary to activate specific access level.
                */
                explicit CalibrationBuilder (const std::string &activationCode = "");

                /**
                * Destructor of the calibration data builder base class
                */
                virtual ~CalibrationBuilder();

                /**
                * Retrieves calibration data from source data.
                *
                * @param source Source calibration data container to be reconstructed.
                * @param destination Destination calibration data container to be reconstructed.
                */
                virtual spectre::SpectreStatus getContainer (const std::vector<uint8_t> &input,
                        container::Calibration &destination) const = 0;

                /**
                * Retrieves Calibration instantiated with default values.
                *
                * @param containerDim Dimensional properties of the container.
                * @param type Calibration data type ID.
                * @param destination Destination data container.
                */
                virtual spectre::SpectreStatus getContainer (SizeProperty containerDim,
                        spectre::SpectreTypeCalibration type,
                        container::Calibration &destination) const = 0;

                /**
                 * Retrieves calibration adequate for processing data from source szstem calibration
                 * data information, with respect to the input data definition.
                 *
                 * If the passed list is empty, the original calibration contained in the byte
                 * stream is returned.
                 *
                 * @param systemCalibration calibration source data stored on the system.
                 * @param input input data definition for the subsequent processing.
                 * @param destination Calibration data used for subsequent processing.
                 *
                 * @return status of operation
                 */
                virtual spectre::SpectreStatus getProcessingCalibration (const spectre::element::container::Calibration &systemCalibration, const spectre::element::container::Input &input,
                        spectre::element::container::Calibration &destination) = 0;

                /**
                * Retrieves the for the current version supported types of calibration data.
                *
                * @return List of supported calibration data types.
                */
                virtual std::vector<SpectreTypeCalibration> getSupportedTypeList() = 0;

            protected:
                /**
                * Copy values from source data container to destination according to path specifier.
                *
                * @param source calibration source data.
                * @param destination calibration source data.
                * @param path query path specifier.
                */
                template<typename T>
                void copyValues (const container::Calibration &source, container::Calibration &destination, const std::vector<std::string>& sourcePath, const std::vector<std::string>& destPath);

            };

        }
    }
}
