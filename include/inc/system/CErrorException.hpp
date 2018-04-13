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

#include <exception>
#include <string>
#include "system/definitions.hpp"

class CErrorException: public std::exception
{
public:
    CErrorException (int error);
    CErrorException (int error, const std::string &message);
    virtual ~CErrorException() = default;

    int getErrorId() const;
    virtual const char *what() const NOEXCEPT;

private:
    int m_error {};
    std::string m_message {};
};
