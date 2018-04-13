/*******************                size_t getSize();*********************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once


#include <spectre/element/data/Data.hpp>

namespace spectre
{
    namespace element
    {
        namespace data
        {

            /**
            *  Elementary data type class
            */
            template < typename T >
            class DataVarDef : public Data<T>
            {
            public:

                virtual ~DataVarDef()
                {
                };

                DataVarDef (std::vector<T> values, const std::string& strId,
                            const std::string &activationCode = "",
                            const DataDescriptor<T>& dataDescriptor = DataDescriptor<T>());
                /**
                 * Sets the element descriptor
                 *
                 * @param descriptor descriptor to set
                 *
                 * @return SpectreStatus::SUCCESS or an error code
                 */
                SpectreStatus setDataDescriptor(const DataDescriptor<T> &descriptor,
                                                const std::string& activationCode);

                virtual SpectreTypeElement  getElementType () const override;

                virtual Element *clone() const override;

            protected:
                virtual bool setHeader (std::vector<uint8_t> &output) const override;
                virtual SpectreStatus readHeader (const std::vector<uint8_t> &input, size_t &idx) override;
            };
        }
    }
}
