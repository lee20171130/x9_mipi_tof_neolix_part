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
#include <string>

class PmdEnvironment: public ::testing::Environment
{
public:
    virtual ~PmdEnvironment() = default;

    void setTestSuiteName (const std::string &name);
    std::string getTestSuiteName() const;

private:
    std::string m_suiteName;
};

