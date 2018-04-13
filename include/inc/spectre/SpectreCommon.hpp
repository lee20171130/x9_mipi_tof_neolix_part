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
#include <vector>
#include <array>
#include <string>
#include <map>
#include <cmath>
#include <memory>

#ifdef NDEBUG
#define SPECTRE_CHECK_SUCCESS(x) x
#else
#define SPECTRE_CHECK_SUCCESS(x) assert(x == spectre::SpectreStatus::SUCCESS)
#endif

#ifdef __ANDROID__
#include <string>
#include <sstream>

namespace std
{
    template <typename T>
    std::string to_string (T value)
    {
        std::ostringstream os;
        os << value;
        return os.str();
    }

    inline std::string to_string (uint8_t value)
    {
        std::ostringstream os;
        os << (unsigned) value;
        return os.str();
    }

    inline std::string to_string (int8_t value)
    {
        std::ostringstream os;
        os << (int) value;
        return os.str();
    }

}
#endif //__ANDROID__



namespace spectre
{

    /*
    *   Region of Interest, correspond to the read out properties of a frame.
    *   Dimensional information with respect to [startColumn, startRow, numColumns, numRows]
    *   in Pixel. Position information can either be relative with respect parent frame definitions,
    *   or absolute with respect to the sensor coordinates.
    */
    using ROI = std::array<uint32_t, 4>;

    /*
    * Read out properties of an areasize, with respect to it's
    * Dimensional information [width, height] in pixel.
    */
    using SizeProperty = std::array<uint32_t, 2>;

    /*
    * Lensparameter defintion, single value  specification according to string pair.
    * ["fx", "fy", "cx", "cy", "k1", "k2", "p1", "p2", "k3", ["k4", ... , "kn"]]
    */
    using LensParameter = std::map<std::string, float>;

    /**
    * Determines if system byte order corresponds to little or big endian.
    *
    * @return True if system is little endian.
    */
    inline bool isLittleEndian()
    {
        static int32_t test = 1;
        return *reinterpret_cast<int8_t *> (&test) == 1;
    };


    template <typename T>
    inline double log2 (T value)
    {
        using namespace std;
        return log (value) / log (2);
    }

    inline long double log2 (long double value)
    {
        using namespace std;
        return log (value) / log (2);
    }

    inline float log2 (float value)
    {
        using namespace std;
        return log (value) / log (2.0f);
    }

    inline float log2f (float value)
    {
        using namespace std;
        return log2 (value);
    }

    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique (Args &&...args)
    {
        return std::unique_ptr<T> (new T (std::forward<Args> (args)...));
    }
}


