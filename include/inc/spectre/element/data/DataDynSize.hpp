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
            class DataDynSize : public Data<T>
            {
            public:
                virtual ~DataDynSize();

                DataDynSize (std::vector<T> values, const std::string& strId,
                             const std::string &activationCode = "",
                             DataDescriptor<T> dataDescriptor = DataDescriptor<T>());

                /*  Sets the size of the data element independently of the previously made data definition.
                *
                *   @param values Return values as copy of the internally stored values.
                *   @return Status of operation.
                */
                virtual SpectreStatus setValues (const std::vector<T> &values, const std::string &activationCode = "") override;

                virtual SpectreTypeElement  getElementType () const override;

                virtual Element *clone() const override;

            protected:

                virtual bool setHeader (std::vector<uint8_t> &output) const override;
                virtual SpectreStatus readHeader (const std::vector<uint8_t> &input, size_t &idx) override;
            };
        }
    }
}
