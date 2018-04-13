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
#include <spectre/element/container/Output.hpp>
#include <spectre/SpectreTypeOutput.hpp>

namespace spectre
{
    namespace element
    {
        namespace builder
        {

            /**
            * Base builder class for output data container
            */
            class OutputBuilder : public Builder
            {
            public:
                using BuildType = container::Output;
                /**
                * Constructor for the output data builder base class
                *
                * @param activationCode Necessary to activate specific access level
                */
                explicit OutputBuilder (const std::string &activationCode);

                /**
                * Destructor of the output data builder base class
                */
                virtual ~OutputBuilder();

                /**
                * Retrieves output data from source data.
                *
                * @param source Source output data container to be reconstructed.
                * @param destination Destination output data container to be reconstructed.
                */
                virtual spectre::SpectreStatus getContainer (const std::vector<uint8_t> &input, container::Output &destination) = 0;

                /**
                * Retrieves parameter data instantiated with default values.
                *
                * @param containerDim Dimensional properties of the container.
                * @param type Output data type ID.
                * @param destination Destination data container.
                */
                virtual spectre::SpectreStatus getContainer (SizeProperty containerDim, spectre::SpectreTypeOutput type, container::Output &destination) = 0;

                /**
                * Retrieves the for the current version supported types of output data.
                *
                * @return List of supported output data types.
                */
                virtual std::vector<SpectreTypeOutput> getSupportedTypeList() const = 0;

            };
        }
    }
}
