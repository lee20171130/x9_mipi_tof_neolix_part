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
    enum class SpectreTypeElement
    {
        UNDEFINED = 0,
        CONTAINER_CUSTOM = 1,
        CONTAINER_INPUT = 2,
        CONTAINER_OUTPUT = 3,
        CONTAINER_PARAMETER = 4,
        CONTAINER_CALIBRATION = 5,
        CONTAINER_INTERMEDIATE = 6,
        DATA = 7,
        DATA_SCALAR = 8,
        DATA_REFERENCE = 9,
        DATA_DYNSIZE = 10,
        DATA_VARDEF = 11,
        DATA_DIRECTIONS = 12,
        DATA_BASE = 13
    };
}
