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

namespace spectre
{
    /*!
    *  This is an enum class, which defines all current pmd frame set types currently supported by spectre.
    *
    *  The number of types may increase over time and the corresponding enumeration class will be expanded correspondingly.
    */
    enum class SpectreTypeFrameSet
    {
        UNDEFINED = 0,      ///< Undefined frame set type
        I1 = 1,             ///< Frame set type for intensity based on one frame set
        P4 = 2              ///< Frame set type for depth probing based on four frame set with different phase illumination config
    };

    using TFS = SpectreTypeFrameSet;
    using FrameSetCompositon = std::vector<TFS>;

}
