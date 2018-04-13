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
#include <spectre/element/container/Parameter.hpp>
#include <spectre/SpectreTypeParameter.hpp>

namespace spectre
{
    namespace element
    {
        namespace builder
        {

            /**
            * Base builder class for parameter data container
            */
            class ParameterBuilder : public Builder
            {
            public:
                using BuildType = container::Parameter;
                /**
                * Constructor for the parameter data builder base class.
                *
                * @param activationCode Necessary to activate specific access level.
                */
                explicit ParameterBuilder (const std::string &activationCode = "");

                /**
                * Destructor of the parameter data builder base class.
                */
                virtual ~ParameterBuilder();

                /**
                * Retrieves parameter data from source data.
                *
                * @param source Source parameter data container to be reconstructed.
                * @param destination Destination parameter data container to be reconstructed.
                * @return System status of operation.
                */
                virtual spectre::SpectreStatus getContainer (const std::vector<uint8_t> &input, container::Parameter &destination) = 0;

                /**
                * Retrieves parameter data instantiated with default values.
                *
                * @param containerDim Dimensional properties of the container.
                * @param type Parameter data type ID.
                * @param destination Destination data container.
                */
                virtual spectre::SpectreStatus getContainer (SizeProperty containerDim, spectre::SpectreTypeParameter type, container::Parameter &destination) = 0;

                /**
                * Retrieves the for the current version supported types of parameter data.
                *
                * @return List of supported parameter types.
                */
                virtual std::vector<SpectreTypeParameter> getSupportedTypeList() const = 0;

            };
        }
    }
}
