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

#include <vector>

#include <spectre/SpectreCommon.hpp>
#include <spectre/SpectreVersion.hpp>
#include <spectre/SpectreStatus.hpp>
#include <spectre/element/container/RootContainerCommon.hpp>

namespace spectre
{
    namespace element
    {
        namespace container
        {
            /**
             * Structure which holds all information necessary to define a header of a root container
             *
             * @param T container format type
             */
            template<typename T>
            struct HeaderDefinition
            {
                /**
                 * Ctor
                 *
                 * @param aContainerDim dimension of container
                 * @param aType container format type
                 * @param aVersion spectre version
                 * @param aMagicWord magic word for container serialization
                 */
                HeaderDefinition (SizeProperty aContainerDim, T aType, SpectreVersion aVersion,
                                  const std::string &aMagicWord);

                SizeProperty containerDim;
                T type;
                SpectreVersion version;
                std::string magicWord;
            };

            /**
             * Utility function to create a HeaderDefinition<T>
             *
             * @param aContainerDim dimension of container
             * @param aType container format type
             * @param aVersion spectre version
             * @param aMagicWord magic word for container serialization
             */
            template<typename T>
            HeaderDefinition<T> makeHeaderDefinition (SizeProperty aContainerDim, T aType, SpectreVersion aVersion,
                    const std::string &aMagicWord);


            /**
             * Sets the header for a root container
             * This function should be called **after** the serialization of the tree is finished.
             * The header is added at the front of the byte stream
             *
             * @param headerDef header definition describing the header
             * @param output serialized output stream
             */
            template<typename T>
            void setRootContainerHeader (const HeaderDefinition<T> &headerDef, std::vector<uint8_t> &output);

            /**
             * Reads the header of a root container
             * The header should be set with the setRootContainerHeader function
             * The passed idx is updated during reading.
             *
             *
             * @param containerMagicWord magic word of the container
             * @param data serialized stream
             * @param idx index where the header begins inside the stream
             * @param header object which will hold the header
             *
             * @return status of operation
             */
            template<typename T>
            spectre::SpectreStatus readRootContainerHeader (const std::string &containerMagicWord,
                    const std::vector<uint8_t> &data, size_t &idx,
                    RootContainerHeader<T> &header);
        }
    }
}

