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

class NameCreator
{
public:
    NameCreator() = default;

    std::string createName (const std::string& testDataPath);

private:
    void eraseTrailingSlash (std::string &path);
    std::string getLastPathEntry (const std::string &path);
    void removeLeadingDots (std::string &path);
    void replaceBackslashes (std::string &path);
    std::string createNormalizedNameFromDir (const std::string &path);
    std::string createNormalizedNameFromFile (const std::string &path);
    void removeSuffix (std::string &path);

};
