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

#include <cstdio>
#include <utility>

/** \brief forwards all parameters to printf
 *
 * \param format printf like format string
 * \param args div parameters for printf
 * \return the printf return value
 *
 * \sa <a href="http://www.cplusplus.com/reference/cstdio/printf/">printf documentation</a>
 *
 */
template<class... Args >
inline int pmd_printf (const char *format, Args &&... args)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
    return printf (format, std::forward<Args> (args)...);
#pragma GCC diagnostic pop
}

/** \brief empty standard implementation does nothing
 */
struct OutRedirector
{
};

/** \brief returns a OutRedirector
 *
 * \return OutRedirector
 *
 */
inline OutRedirector redirectStdOutIfNecessary()
{
    return OutRedirector();
};
