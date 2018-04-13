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

#include <stdint.h>
#include <limits>
#include <cmath>
#include <type_traits>
#include <typeinfo>
#include <string>

namespace spectre
{
    namespace element
    {
        namespace data
        {

            /**
            *   Data descriptor to describe minimum bit size for data storage.
            *
            *   Used for data compression according to scale and offset
            *   http://www.unidata.ucar.edu/blogs/developer/entry/compression_by_scaling_and_offfset
            *
            *   UF = scale * P + offset
            *
            *   where:
            *   F is the original floating point number
            *   P is an integer of n bits (packed value)
            *   UF is the reconstructed floating point number (unpacked value)
            */
            template < typename T >
            class DataDescriptor
            {

            public:
                T minValue;                         //< Minimum permissable value
                T maxValue;                         //< Maximum permissable value
                T scale;                            //< Scaling factor for data conversion: scale = (maxValue - minValue) / (2^n - 1)
                T precision;                        //< Initial Precision requirement of the stored data value
                uint32_t bitSize;                   //< Size of the a single value in bit: : bitSize = ceil( log2(1 + ceil( (maxValue - minValue) / (2 * precision))))
                bool defaultType;                   //< Save data as default data type, without compression

                DataDescriptor (T aMinValue = std::numeric_limits<T>::lowest(),
                                T aMaxValue = std::numeric_limits<T>::max(), T aPrecision = 0);

                /**
                * Returns true if Descriptor composition is of default type.
                *
                */
                inline bool isDefault() const
                {
                    return defaultType;
                }

                /**
                * Returns true if Descriptor comparison is identical with
                * respect to minValue, maxValue, scale, precision, bitSize
                * and defaultType.
                *
                * @return Status of comparison
                */
                bool operator== (const DataDescriptor<T> &cmp) const;

                /**
                * Returns true if Descriptor comparison is not identical with
                * respect to minValue, maxValue, scale, precision, bitSize
                * and defaultType.
                *
                * @return Status of comparison
                */
                bool operator!= (const DataDescriptor<T> &cmp) const;

            private:

                /**
                * Returns false if Descriptor composition is of default type.
                *
                * @return Returns true if Descriptor composition is of default type.
                */
                void computeScale();

            };
        }
    }
}
