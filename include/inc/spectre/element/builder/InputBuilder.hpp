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
#include <spectre/element/container/Input.hpp>
#include <spectre/SpectreTypeInput.hpp>
#include <spectre/SpectreTypeFrameSet.hpp>

namespace spectre
{
    namespace element
    {
        namespace builder
        {

            /**
             * Base builder class for input data container
             */
            class InputBuilder : public Builder
            {
            public:
                using BuildType = container::Input;
                /**
                 * Constructor for the input data builder base class
                 *
                 * @param activationCode Necessary to activate specific access level
                 */
                explicit InputBuilder (const std::string &activationCode = "");

                /**
                 * Destructor of the input data builder base class
                 */
                virtual ~InputBuilder();

                /**
                 * Retrieves input data from source data.
                 *
                 * @param source Source input data container to be reconstructed.
                 * @param destination Destination input data container to be reconstructed.
                 */
                virtual spectre::SpectreStatus getContainer (const std::vector<uint8_t> &input, container::Input &destination) const = 0;

                /**
                 * Retrieves input data instantiated with default values.
                 *
                 * @param containerDim Dimensional properties of the container.
                 * @param type Input data type ID.
                 * @param destination Destination data container.
                 */
                virtual spectre::SpectreStatus getContainer (SizeProperty containerDim, spectre::SpectreTypeInput type, container::Input &destination) const = 0;

                /**
                 * Retrieves input data instantiated with default values and a specific frame order definition.
                 *
                 * @param containerDim Dimensional properties of the container.
                 * @param type Input data type ID.
                 * @param FrameSetComposition Used to define a non default frame order configuration.
                 * @param destination Destination data container.
                 */
                virtual spectre::SpectreStatus getContainer (SizeProperty containerDim,
                        spectre::SpectreTypeInput type,
                        FrameSetCompositon frameSetComposition,
                        container::Input &destination) const = 0;

                /**
                 * Retrieves the for the current version supported types of input data.
                 *
                 * @return List of supported input data types.
                 */
                virtual std::vector<SpectreTypeInput> getSupportedTypeList() const = 0;

                /**
                 * Gets the frameset composition associated to the passed variant
                 * If the variant is unknown, an empty composition is returned
                 *
                 * @param type submodule type
                 * @param variant variant
                 *
                 * @return associated frameset composition
                 */
                virtual FrameSetCompositon forVariant (SpectreTypeInput type, uint16_t variant) const = 0;


            };

        }
    }
}
