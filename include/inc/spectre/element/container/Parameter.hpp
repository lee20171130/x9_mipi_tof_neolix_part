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
#include <spectre/SpectreTypeParameter.hpp>

namespace spectre
{
    namespace element
    {
        namespace container
        {

            /**
            *  Parameter data container class
            */
            class Parameter : public Container
            {

            public:
                using ParameterHeader = RootContainerHeader<SpectreTypeParameter>;
                using FramesType = SpectreTypeParameter;

                /**
                * Ctor for construction of an empty parameter container
                *
                * @param activationCode activation code
                */
                explicit Parameter (const std::string &activationCode = "");

                /**
                *   Destructor of the parameter data container.
                */
                virtual ~Parameter();

                /**
                * Constructor of the parameter data container.
                *
                * @param version Chosen spectre version.
                * @param parameterType Type of parameter
                * @param containerDim Dimensional properties of the parameter container.
                * @param dataList List of composed sub data elements.
                * @parma strId Element identifaction tag as clear string value.
                * @param activationCode Specific activation code to enable user access.
                */
                Parameter (SpectreVersion version,
                           SpectreTypeParameter parameterType,
                           const SizeProperty &containerDim,
                           const std::string &strId,
                           const std::string &activationCode,
                           const std::vector<std::shared_ptr<Element>> &dataList
                          );


                /**
                *   Returns parameter data type id.
                *
                *   @param Type id.
                */
                SpectreTypeParameter getType() const;

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

                SpectreStatus queryHeader (const ::std::vector<uint8_t> &data, size_t idx, ParameterHeader &header) const;

                /**
                * Compares this parameter Container with another. Returns true if
                * both container equal in dimensions, version, type and variant.
                *
                * @param Cmp Parameter container to be compared against.
                *
                * @return true if container are identical.
                */
                bool equalCfg (const Element &cmp) const override;

            protected:
                virtual bool setHeader (std::vector<uint8_t> &output) const override;
                virtual SpectreStatus readHeader (const std::vector<uint8_t> &data, size_t &idx) override;


            private:
                SpectreTypeParameter m_type;    //< Spectre parameter data type id.
                SizeProperty m_containerDim;    //< Dimensional properties of the container element

                static const std::string S_MAGIC_WORD;
            };
        }
    }
}
