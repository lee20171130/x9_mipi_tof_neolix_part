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

#include <spectre/SpectreTypeInput.hpp>
#include <spectre/SpectreTypeFrameSet.hpp>
#include <spectre/SpectreTypeFrameSet.hpp>
#include <spectre/element/container/Container.hpp>
#include <spectre/element/container/RootContainerCommon.hpp>

namespace spectre
{
    namespace element
    {
        namespace container
        {

            /**
            *  Input data container class
            */
            class Input : public Container
            {

            public:
                using InputHeader = RootContainerHeader<SpectreTypeInput>;
                using FramesType = SpectreTypeInput;

                /**
                * Ctor for construction of an empty input container
                *
                * @param activationCode activation code
                */
                explicit Input (const std::string &activationCode = "");

                /**
                *   Destructor of the input data container.
                */
                virtual ~Input();

                /**
                * Constructor of the input data container.
                *
                * @param version Chosen spectre version.
                * @param inputType Type of input.
                * @param containerDim Dimensional properties of the input container.
                * @param dataList List of composed sub data elements.
                * @parma strId Element identifaction tag as clear string value.
                * @param activationCode Specific activation code to enable user access.
                */
                Input (SpectreVersion version,
                       SpectreTypeInput inputType,
                       const SizeProperty &containerDim,
                       const std::string &strId,
                       const std::string &activationCode,
                       const std::vector<std::shared_ptr<Element>> &dataList
                      );

                /**
                *   Returns input data type id.
                *
                *   @param Type id.
                */
                SpectreTypeInput getType() const;

                /**
                * Gets the dimensional properties of this container
                *
                * @return dimensional properties
                */
                SizeProperty getContainerDim() const;

                virtual SpectreStatus deSerialize (const std::vector<uint8_t> &input, size_t &idx) override;
                virtual SpectreStatus serialize (std::vector<uint8_t> &output) const override;

                virtual SpectreTypeElement  getElementType () const override;

                /**
                * Retrieves handle to the reference data element
                *
                * @param dataPath path of element
                * @param handle Data handle to the externally managed data area.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return SUCCESS if element is found, otherwise an error indicator
                */
                template<typename T>
                SpectreStatus getDataHandle (const std::vector<std::string> &dataPath, T **handle, const std::string &activationCode);


                /**
                * Retrieves sensor ROI information from the input data container
                *
                */
                ROI getSensorROI() const;

                /**
                * Retrieves sensor sub ROI information from the input data container
                *
                */
                ROI getSubROI() const;

                /**
                * Retrieves frame set composition from the input data container
                *
                */
                FrameSetCompositon getFrameSetComposition() const;

                virtual Element *clone() const override;

                SpectreStatus queryHeader (const ::std::vector<uint8_t> &data,
                                           size_t idx, InputHeader &header) const;

                /**
                * Compares this input Container with another. Returns true if
                * both container equal in dimensions, version, type and variant.
                *
                * @param cmp Input container to be compared against.
                *
                * @return true if container are identical.
                */
                bool equalCfg (const Element &cmp) const override;

            protected:
                virtual bool setHeader (std::vector<uint8_t> &output) const override;
                virtual SpectreStatus readHeader (const std::vector<uint8_t> &header,
                                                  size_t &idx) override;

            private:
                SpectreTypeInput m_type;                    //< Spectre input data type id.
                SizeProperty m_containerDim;                //< Dimensional properties of the container element
                SpectreTypeFrameSet frameSetComposition;    //< Defines the frame order configuration.

                static const std::string S_MAGIC_WORD;
            };

        }
    }
}
