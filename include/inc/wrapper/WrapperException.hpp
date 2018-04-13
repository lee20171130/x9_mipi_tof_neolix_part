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

#include <string>
#include <exception>

namespace spectre
{
    namespace wrapper
    {

        class WrapperException : public std::exception
        {

        public:

            WrapperException() : std::exception(), m_message ("")
            {
            };

            WrapperException (std::string message) : std::exception(), m_message (message)
            {
            }

        public:

            std::string m_message;

        };
    }
}
