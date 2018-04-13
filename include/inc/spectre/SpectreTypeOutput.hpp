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
    *  This is an enum class, which defines all current pmd intermediate data types currently supported by spectre.
    *
    *  The number of types may increase over time and the corresponding enumeration class will be expanded correspondingly.
    */
    enum class SpectreTypeOutput
    {
        UNDEFINED = 0,      ///< Undefined input information type
        ASTON_I1P4 = 1,     ///< Output configuration for an image frame set of 4 Phasse + 1 Intensity Image
        ASTON_I1P4P4 = 2    ///< Output configuration for an image frame set of 4 Phasse + 4 Phasse + 1 Intensity Image
    };
}