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

namespace spectre
{
    /*!
    *  This is an enum class, which defines all current pmd parameter data types currently supported by spectre.
    *
    *  The number of types may increase over time and the corresponding enumeration class will be expanded correspondingly.
    */
    enum class SpectreTypeSystem
    {
        UNDEFINED = 0,      ///< Undefined input information type
        REFERENCE = 1,      ///< Ansi-C processing reference implementation
		X86 = 2,            ///< Optimized for x86 processing platform supporting LUTs
        ARM = 3             ///< Processing optimization for arm processing architectures supporting neon
    };
}
