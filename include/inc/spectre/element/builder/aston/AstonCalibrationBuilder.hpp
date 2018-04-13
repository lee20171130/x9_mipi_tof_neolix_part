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

#include <spectre/element/builder/CalibrationBuilder.hpp>
#include <spectre/element/data/DataDirections.hpp>

#include <set>
#include <vector>
#include <string>

namespace spectre
{
    namespace element
    {
        namespace builder
        {
            namespace aston
            {

                /**
                *  Builder class for aston calibration data container
                */
                class AstonCalibrationBuilder : public CalibrationBuilder
                {
                public:

                    /**
                    *   Constructor of the aston calibration data builder class
                    *
                    *   @param activationCode Necessary to activate specific access level
                    */
                    explicit AstonCalibrationBuilder (const std::string &activationCode = "");

                    /**
                    *   Destructor of the calibration data builder aston class
                    */
                    virtual ~AstonCalibrationBuilder();

                    virtual spectre::SpectreStatus getContainer (const std::vector<uint8_t> &input,
                            container::Calibration &destination) const override;

                    virtual spectre::SpectreStatus getContainer (SizeProperty containerDim,
                            spectre::SpectreTypeCalibration type,
                            container::Calibration &destination) const override;

                    virtual std::vector<SpectreTypeCalibration> getSupportedTypeList() override;

                    virtual spectre::SpectreStatus getProcessingCalibration (const spectre::element::container::Calibration &systemCalibration, const spectre::element::container::Input &input,
                            spectre::element::container::Calibration &destination) override;

                private:
                    /// List of supported calibration data types.
                    static const std::set<SpectreTypeCalibration> S_TYPES;

                };
            }
        }
    }
}
