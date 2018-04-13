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
    enum class SpectreFormatData
    {
        UNDEFINED_FORMAT = 0,
        CHAR_FORMAT = 1,
        INT8_FORMAT = 2,
        INT16_FORMAT = 3,
        INT32_FORMAT = 4,
        INT64_FORMAT = 5,
        UINT8_FORMAT = 6,
        UINT16_FORMAT = 7,
        UINT32_FORMAT = 8,
        UINT64_FORMAT = 9,
        FLOAT_FORMAT = 10,
        DOUBLE_FORMAT = 11
    };
}