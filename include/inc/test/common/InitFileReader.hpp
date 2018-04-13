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
#include <memory>
#include <vector>
#include <string>


class InitFileReader
{
public:
    InitFileReader() = default;
    virtual ~InitFileReader() = default;

    virtual bool readInitFile (std::string file, std::vector<std::string> &testDataDirs) const;
};

using InitFileReaderPtr = std::unique_ptr<InitFileReader>;

