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

#include <gmock/gmock.h>
#include "system/ICommandExecutor.hpp"

#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif //__APPLE_

class CommandExecutorMock: public ICommandExecutor
{
public:
    CommandExecutorMock() = default;
    virtual ~CommandExecutorMock() = default;

    // ICommandExecutor interface
public:
    MOCK_METHOD1 (run, CommandResult (const std::string &command));
};

using CommandExecutorMockPtr = std::unique_ptr<CommandExecutorMock>;
using CommandExecutorMockShr = std::shared_ptr<CommandExecutorMock>;

#ifdef __APPLE__
#pragma clang diagnostic pop
#endif //__APPLE_
