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
#include <memory>

#include <spectre/element/container/Container.hpp>
#include <spectre/element/container/RootContainerCommon.hpp>
#include <spectre/SpectreTypeOutput.hpp>

namespace spectre
{
    namespace element
    {
        namespace container
        {

            /**
            *  Output data container class
            */
            class Output : public Container
            {

            public:
                using OutputHeader = RootContainerHeader<SpectreTypeOutput>;
                using FramesType = SpectreTypeOutput;

                /**
                * Ctor for construction of an empty output container
                *
                * @param activationCode activation code
                */
                explicit Output (const std::string &activationCode = "");

                /**
                *   Destructor of the output data container.
                */
                virtual ~Output();

                /**
                * Constructor of the output data container.
                *
                * @param version Chosen spectre version.
                * @param outputType Type of output
                * @param containerDim Dimensional properties of the output container.
                * @param dataList List of composed sub data elements.
                * @parma strId Element identifaction tag as clear string value.
                * @param activationCode Specific activation code to enable user access.
                */
                Output (SpectreVersion version,
                        SpectreTypeOutput outputType,
                        const SizeProperty &containerDim,
                        const std::string &strId,
                        const std::string &activationCode,
                        const std::vector<std::shared_ptr<Element>> &dataList
                       );

                /**
                *   Returns output data type id.
                *
                *   @param Type id.
                */
                SpectreTypeOutput getType() const;

                /**
                * Gets the dimensional properties of this container
                *
                * @return dimensional properties
                */
                SizeProperty getContainerDim() const;

                virtual SpectreStatus deSerialize (const std::vector<uint8_t> &binaryData, size_t &idx) override;
                virtual SpectreStatus serialize (std::vector<uint8_t> &output) const override;

                virtual SpectreTypeElement  getElementType () const override;

                virtual Element *clone() const override;

                SpectreStatus queryHeader (const ::std::vector<uint8_t> &data, size_t idx, OutputHeader &header) const;

                /**
                * Compares this output Container with another. Returns true if
                * both container equal in dimensions, version, type and variant.
                *
                * @param cmp Output container to be compared against.
                *
                * @return true if container are identical.
                */
                bool equalCfg (const Element &cmp) const override;

            protected:
                virtual bool setHeader (std::vector<uint8_t> &output) const override;
                virtual SpectreStatus readHeader (const std::vector<uint8_t> &data, size_t &idx) override;

            private:
                SpectreTypeOutput m_type;       //< Spectre output data type id.
                SizeProperty m_containerDim;    //< Dimensional properties of the container element

                static const std::string S_MAGIC_WORD;
            };
        }
    }
}
