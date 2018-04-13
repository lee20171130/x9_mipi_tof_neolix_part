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

#include "system/SystemIO.hpp"
#include <gmock/gmock.h>
#include <string>
#include <memory>

#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif //__APPLE_

class SystemIOMock: public SystemIO
{
public:
    SystemIOMock() = default;
    virtual ~SystemIOMock() = default;

    MOCK_METHOD2 (popen, FILE * (const char *command, const char *mode));
    MOCK_METHOD1 (pclose, int (FILE *stream));
    MOCK_METHOD3 (fgets, char * (char *buffer, int bufferSize, FILE *stream));
    MOCK_METHOD1 (reachedEof, int (FILE *stream));
    MOCK_METHOD0 (getOwnExePath, std::string());
};
using SystemIOMockPtr = std::unique_ptr<SystemIOMock>;

#ifdef __APPLE__
#pragma clang diagnostic pop
#endif //__APPLE_
