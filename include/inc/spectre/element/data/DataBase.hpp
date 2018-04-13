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

#include <spectre/element/Element.hpp>
#include <spectre/SpectreFormatData.hpp>


namespace spectre
{
    namespace element
    {
        namespace data
        {
            enum class SpectreEndian
            {
                ENDIANESS_LITTLE = 0,
                ENDIANESS_BIG = 1
            };

            /**
            *  Data type class acting as a storage for a set numeric values.
            */
            class DataBase : public Element
            {
            public:
                virtual ~DataBase()
                {
                }

                /**
                * Retrieves spectre data format type.
                *
                * @return format type
                */
                SpectreFormatData getFormat () const;

                /**
                * Retrieves spectre data format type.
                *
                * @return format type
                */
                SpectreEndian getEndianes() const;

                /**
                * Compares this data base element configuration with another.
                * Returns true if both container equal in version, format
                * and endianess.
                *
                * @param cmp Data to be compared against.
                *
                * @return true if container are identical.
                */
                virtual bool equalCfg (const Element &cmp) const override;

                virtual SpectreTypeElement  getElementType() const override;

            protected:

                /**
                * Protected constructor of the data base element.
                *
                * @param activationCode Necessary to activate specific access level.
                * @param identification parameter as clear string name tag.
                */
                DataBase (const std::string &strId, const std::string &activationCode = "");

                virtual SpectreStatus serialize (std::vector<uint8_t> &output) const override = 0;

                virtual SpectreStatus deSerialize (const std::vector<uint8_t> &input, size_t &idx) override = 0;

                virtual Element *clone() const override = 0;

                virtual bool setHeader (std::vector<uint8_t> &output) const override = 0;

                virtual SpectreStatus readHeader (const std::vector<uint8_t> &input,
                                                  size_t &idx) override = 0;

            protected:
                SpectreFormatData m_format;                 //< Native data format type of the data element
                SpectreEndian m_endianness;                 //< Endianness of the data element

                friend class container::Container;
            };
        }
    }
}
