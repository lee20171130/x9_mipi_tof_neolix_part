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
#include <string>
#include <test/common/TesterConfig.hpp>
#include <test/common/NameCreator.hpp>

class PmdEnvironment;

class PmdMultiTester
{
public:
    PmdMultiTester (int argc, char **argv);
    ~PmdMultiTester() = default;
    int runAllTestSuits();
    void addGlobalTestEnvironment (PmdEnvironment *env);

private:
    int runTestSuits (const std::vector<std::string> &suitPaths);
    void printTestSuite (const std::string &testString);
    void instantiateTestSuit (const std::string &path);

    TesterConfig m_config;
    NameCreator m_namer;
    std::vector<PmdEnvironment *> m_enviros;
};
