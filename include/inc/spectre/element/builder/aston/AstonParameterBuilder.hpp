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

#include <spectre/element/builder/ParameterBuilder.hpp>
#include <set>

namespace spectre
{
    namespace element
    {
        namespace builder
        {
            namespace aston
            {
                /**
                *  Builder class for the aston parameter data container
                */
                class AstonParameterBuilder : public ParameterBuilder
                {
                public:
                    /**
                    *   Constructor of the aston parameter data builder base class
                    *
                    *   @param activationCode Necessary to activate specific access level
                    */
                    explicit AstonParameterBuilder (const std::string &activationCode = "");

                    /**
                    *   Destructor of the calibration data builder aston class
                    */
                    virtual ~AstonParameterBuilder();

                    virtual spectre::SpectreStatus getContainer (const std::vector<uint8_t> &input,
                            container::Parameter &destination) override;

                    virtual spectre::SpectreStatus getContainer (SizeProperty containerDim,
                            SpectreTypeParameter type,
                            container::Parameter &destination) override;

                    virtual std::vector<SpectreTypeParameter> getSupportedTypeList() const override;

                private:
                    /// List of supported parameter data types.
                    static const std::set<SpectreTypeParameter> S_TYPES;
                };
            }
        }
    }
}
