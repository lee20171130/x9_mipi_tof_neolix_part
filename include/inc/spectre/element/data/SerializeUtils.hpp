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
#include <cstdint>
#include <string>
#include <cstring>
#include <stdexcept>

#include <spectre/SpectreStatus.hpp>

namespace spectre
{

    namespace element
    {
        namespace data
        {
            void addToVec (uint32_t val, std::vector<uint8_t> &vec,
                           std::vector<uint8_t>::iterator pos);

            void addToVec (uint16_t val, std::vector<uint8_t> &vec,
                           const std::vector<uint8_t>::iterator &pos);

            void addToVec (uint8_t val, std::vector<uint8_t> &vec,
                           const std::vector<uint8_t>::iterator &pos);

            void addToVec (const std::string &val, std::vector<uint8_t> &vec,
                           const std::vector<uint8_t>::iterator &pos);
            
            inline void addToVec (uint16_t val, std::vector<uint8_t> &vec)
            {
                addToVec (val, vec, vec.end());
            }

            inline void addToVec (uint32_t val, std::vector<uint8_t> &vec)
            {
                addToVec (val, vec, vec.end());
            }

            inline void addToVec(uint8_t val, std::vector<uint8_t> &vec)
            {
                addToVec(val, vec, vec.end());
            }

            template<typename T>
            SpectreStatus readFromVec (const std::vector<uint8_t> &vec,
                                       std::size_t &idx,
                                       T &target)
            {
                int vecSize (sizeof (T) / sizeof (uint8_t));
                if (idx + vecSize <= vec.size())
                {
                    target = 0;
                    for (int shift = (vecSize - 1) * 8; shift >= 0; shift -= 8)
                    {
                        target += (vec[idx++] << shift);
                    }
                    return SpectreStatus::SUCCESS;
                }

                return SpectreStatus::DESERIALIZE_UNEXPECTED_END;
            }

            SpectreStatus readFromVec (const std::vector<uint8_t> &vec,
                                       std::size_t &idx,
                                       std::string &target,
                                       std::size_t length);


            /**
             * converts sizeof(resType) bytes to a resType value
             *
             *   reads sizeof(resType) bytes from the array and returns them as a value of resType.
             *   If array is a null pointer function will throw an std::invalid_argument exception.
             *   If sizeof(resType) > arraySize function will throw a std::out_of_range exception.
             *
             *
             * @param array pointer to the first array element
             * @param arraySize array size in bytes
             * @param activationCode activation code
             * @exception std::invalid_argument if array is a null pointer.
             * @exception std::out_of_range if arraySize < sizeof(resType)
             * @return the resType value
             */
            template<typename resType> resType readBytesAs(const uint8_t* array, size_t arraySize)
            {

                if (array == nullptr)
                {
                    throw std::invalid_argument("array is a mullptr");
                }
                if (arraySize < sizeof(resType))
                {
                    throw std::out_of_range("arraySize is to small");
                }
                resType result;
                memcpy(&result, array, sizeof(resType));
                return result;
            }
        }
    }
}
