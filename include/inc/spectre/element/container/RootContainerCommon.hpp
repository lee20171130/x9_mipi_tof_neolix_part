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

#include <tuple>
#include <spectre/SpectreCommon.hpp>
#include <spectre/SpectreVersion.hpp>

namespace spectre
{
    namespace element
    {
        namespace container
        {
            template<typename T>
            using RootContainerHeader = std::tuple<T, SpectreVersion, SizeProperty>;
        }
    }
}
