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
    /// Template which holds a list of types (typelist)
    template<typename HEAD, typename... Tail>
    struct tlist
    {
        typedef HEAD head;

        bool last() const
        {
            return false;
        }

        tlist<Tail...> next() const
        {
            return tlist<Tail...>();
        }
    };

    /// Typelist specialization for last entry
    template<typename HEAD>
    struct tlist<HEAD>
    {
        typedef HEAD head;

        bool last() const
        {
            return true;
        }

        tlist<HEAD> next() const
        {
            return *this;
        }
    };
}
