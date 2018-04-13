#pragma once

#include <cstdint>

namespace spectre
{
    namespace element
    {
        /**
        *   Determines if system byte order corresponds to little or big endian.
        *
        *   @return True if system is little endian.
        */
        inline bool isLittleEndian()
        {
            static std::int32_t test = 1;
            return *reinterpret_cast<std::int8_t *> (&test) == 1;
        };
    }
}
