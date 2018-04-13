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
#include <exception>
#include "system/definitions.hpp"
#include "test/common/InitFileReader.hpp"


class TesterConfig
{
public:
    TesterConfig();
    explicit TesterConfig (InitFileReaderPtr reader);
    void setTestDataDirectories (const std::vector<std::string> &directories);
    std::vector<std::string> getTestDataDirectories() const;
    void parseCommandline (int argc, char **argv);

private:
    std::vector<std::string> parseInitFile (const std::string &dir
                                            , const std::string &fileName);
    std::vector<std::string> m_dataDirectories;
    InitFileReaderPtr m_reader;
};

class TesterConfigException: public std::exception
{
public:
    explicit TesterConfigException (const std::string &message) :
        m_message (message)
    {
    }

    virtual ~TesterConfigException() = default;

    virtual const char *what() const NOEXCEPT
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

