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

#if defined(_WIN32)
#include <direct.h>
#else
//#include "sysstat.h"
#include <sys/stat.h>
#include <sys/types.h>
#endif

#define __STDC_LIMIT_MACROS
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>

#include <string.h>

#include <processing/common/commonMethods.hpp>

#include <system/toolsTimer.hpp>

#ifndef INT16_MAX
#define INT16_MAX 32767
#endif

#define char_CAST( param ) reinterpret_cast<char *> ( param )

#ifdef PMD_EXTERN_HELP_MOD
#define EXTERN_HELP
#else
#define EXTERN_HELP extern
#endif

EXTERN_HELP std::string workingDir_e;      // global variable

#ifdef PMD_EXTERN_DUMP_MOD
#define PMD_EXTERN_DUMP
#else
#define PMD_EXTERN_DUMP extern
#endif

using ofstreamPtr = std::shared_ptr<std::ofstream>;

struct MapEntry
{
    ofstreamPtr file{};
    uint32_t counter{};
};

using FileMap = std::map <std::string, MapEntry>;
using TimerMap = std::map <std::string, Timer> ;

struct PMD_DumpInfo
{
    bool doDump;
    FileMap fileMap;
    TimerMap timerMap;
    std::string prefix;
    std::string projectDir;
    std::string algoName;
    std::string userString;
    uint32_t imgWidth;
    uint32_t imgHeight;
};

PMD_EXTERN_DUMP PMD_DumpInfo di_e;

inline int  pmd_mkdir (const char *dirName)
{
#if defined(_WIN32)
    return _mkdir (dirName);
#else
    return mkdir (dirName, 0777);
#endif
}

// fopen
#if defined(_WIN32)

#define pmd_fopen( file, filename, mode ) \
fopen_s( &file, filename, mode );
#else

#define pmd_fopen( file, filename, mode ) \
file = fopen ( filename, mode )
#endif

template <typename T>
std::string pmd_numberToString (T Number)
{
    std::stringstream ss;

    if ( (typeid (T) != typeid (char)) && (typeid (T) != typeid (uint8_t)))
    {
        ss << Number;
    }
    else
    {
        ss << static_cast<uint32_t> (Number);
    }

    return ss.str();
}

template<typename T> void pmd_saveImage (const std::string &fileName, const uint32_t numPixel, T *data)
{
    if (di_e.doDump)
    {

        FILE *pFile;

        T min = data[0];
        T max = data[0];
        uint32_t width = di_e.imgWidth;
        uint32_t height = numPixel / width;

        for (uint32_t idx = 0; idx < numPixel; ++idx)
        {
            if (data[idx] < min)
            {
                min = data[idx];
            }

            if (data[idx] > max)
            {
                max = data[idx];
            }
        }

        std::string dirTree = di_e.projectDir + "/" + di_e.prefix + di_e.algoName;
        std::string fullName = dirTree + "/" + fileName + di_e.userString + ".ppm";

        pmd_mkdir (dirTree.c_str());
        pmd_fopen (pFile, fullName.c_str(), "wb");
        std::string strImgWidth = pmd_numberToString (di_e.imgWidth);
        std::string strImgHeight = pmd_numberToString (height);
        std::string header = "P6\n" + strImgWidth + " " + strImgHeight + "\n255\n";
        fclose (pFile);

        pmd_fopen (pFile, fullName.c_str(), "ab");
        fwrite (header.c_str(), sizeof (char), header.size(), pFile);

        for (uint32_t idx = 0; idx < numPixel; ++idx)
        {
            uint8_t pixel[3];
            float value;
            value = ( (float) data[idx] - (float) min) / (float) max;

            pixel[0] = 255 * static_cast<uint8_t> (pmd_round (value));
            pixel[1] = 255 * static_cast<uint8_t> (pmd_round (value));
            pixel[2] = 255 * static_cast<uint8_t> (pmd_round (value));
            fwrite (pixel, sizeof (uint8_t), 3, pFile);
        }

        fclose (pFile);
    }
}

template<typename T> bool pmd_saveArrayToStream (std::ofstream &stream, size_t size, T *data)
{

    if (!stream.good())
    {
        return false;
    }
    auto byteSize = sizeof (T) * size;
    auto bytePtr = reinterpret_cast<const char *> (data);
    stream.write (bytePtr, byteSize);
    return stream.good();
}

template<typename T> bool pmd_saveArrayToFile (const std::string &fullfileName, size_t size, const T *data, const std::string &fileType = "bin", std::ios_base::openmode mode = std::ofstream::out | std::ofstream::binary | std::ofstream::trunc)
{
    std::string fullName = fullfileName + "." + fileType;
    std::ofstream stream (fullName, mode);
    return pmd_saveArrayToStream (stream, size, data);
}

template<typename T> bool pmd_saveArray (const std::string &fileName, size_t size, T *data, const std::string &fileType, std::ios_base::openmode mode)
{
    if (!di_e.doDump)
    {
        return true;
    }
    std::string dirTree = di_e.projectDir + "/" + di_e.prefix + di_e.algoName;
    if(pmd_mkdir (dirTree.c_str()) > 0)
    {
        return false;
    }
    std::string fullName = dirTree + "/" + fileName + di_e.userString;
    return pmd_saveArrayToFile (fullName, size, data, fileType, mode);
}

template<typename T> bool pmd_saveArray (const std::string &fileName, size_t size, T *data, const std::string &fileType = "bin")
{
    return pmd_saveArray (fileName, size, data, fileType, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
}

template<typename T> bool pmd_saveArrayAdd (const std::string &fileName,  size_t size, T *data, const std::string &fileType = "bin")
{
    return pmd_saveArray (fileName, size, data, fileType, std::ofstream::out | std::ofstream::binary | std::ofstream::app);
}


template<typename T> bool pmd_saveArraySingle (const std::string &fileName, T data, const std::string &fileType = "bin")
{
    bool isGood = true;
    if (di_e.doDump)
    {
        const uint32_t numPixel = di_e.imgHeight * di_e.imgWidth;
        std::string dirTree = di_e.projectDir + "/" + di_e.prefix + di_e.algoName;
        std::string fullName = dirTree + "/" + fileName + di_e.userString + "." + fileType;
        MapEntry &fileEntry = di_e.fileMap[fullName];

        if (!fileEntry.file)
        {
            pmd_mkdir (dirTree.c_str());
            fileEntry.file = std::make_shared<std::ofstream> (fullName, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
        }
        isGood = fileEntry.file->good();
        if (isGood)
        {
            auto byteSize = sizeof (T);
            auto bytePtr = reinterpret_cast<const char *> (&data);
            fileEntry.file->write (bytePtr, byteSize);
            isGood = fileEntry.file->good();
        }
        if (isGood)
        {
            ++fileEntry.counter;
        }
        if (!isGood || fileEntry.counter >= numPixel)
        {
            fileEntry.file->close();
        }
    }
    return isGood;

}

template<typename T> bool pmd_saveVector (const std::string &filename, std::vector<T> &data, const std::string &fileType = "bin")
{
    return pmd_saveArray (filename, data.size(), data.data(), fileType);
}

inline size_t getStreamSize (std::istream &stream)
{
    std::streampos failure (-1);
    auto curpos = stream.tellg();
    if (curpos == failure)
    {
        return 0;
    }
    stream.seekg (0, stream.beg);
    auto startpos = stream.tellg();
    stream.seekg (0, stream.end);
    auto endpos = stream.tellg();
    stream.seekg (curpos, stream.beg);
    if (startpos == failure || endpos == failure)
    {
        return 0;
    }
    return static_cast<size_t> (endpos - startpos);
}

inline size_t getFileSize (const std::string &filename)
{
    std::ifstream file (filename);
    if (file.good())
    {
        return getStreamSize (file);
    }
    return 0;
}

template<typename T> bool pmd_loadVector (const std::string &filename, std::vector<T> &data)
{
    std::ifstream file (filename, std::fstream::binary  | std::fstream::in);
    if (!file.good())
    {
        return false;
    }
    auto size = getStreamSize (file);
    if (!file.good() || size == 0)
    {
        return false;
    }
    auto elements = size;
    if (size != 1)
    {
        elements = size / sizeof (T);
    }
    data.resize (elements);
    //reset size if size is not a multiple of sizeof(T)
    size = elements * sizeof (T);
    auto byteptr = reinterpret_cast<char *> (data.data());
    file.read (byteptr, size);
    if (!file)
    {
        return false;
    }
    return true;
}

template<typename T> bool pmd_loadFile (const std::string &filename, std::vector<T> &data)
{
    auto result = pmd_loadVector (filename, data);

    for (uint32_t i = 0; i < data.size(); ++i)
    {
        if (pmd_isNaNOrInfinity (static_cast<float> (data[i])))
        {
            data[i] = T {};
        }
    }

    return result;
}

template<typename T> size_t pmd_loadArray (const std::string &filename, T **data)
{
    *data = nullptr;
    std::ifstream file (filename, std::fstream::binary  | std::fstream::in);
    if (!file.good())
    {
        return 0;
    }
    auto byteSize = getStreamSize (file);
    if (!file.good() || byteSize == 0)
    {
        return 0;
    }
    auto elements = byteSize;
    if (byteSize != 1)
    {
        elements = byteSize / sizeof (T);
    }
    //reset byteSize if size is not a multiple of sizeof(T)
    byteSize = elements * sizeof (T);
    if (typeid (T) != typeid (char))
    {
        *data = reinterpret_cast<T *> (malloc (byteSize));
        if (*data)
        {
            memset (*data, 0, byteSize);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        *data = reinterpret_cast<T *> (malloc (byteSize + 1));
        if (*data)
        {
            memset (*data, 0, byteSize + 1);
        }
        else
        {
            return 0;
        }
    }
    auto byteptr = reinterpret_cast<char *> (*data);
    file.read (byteptr, byteSize);
    if (!file)
    {
        return 0;
    }
    return elements;
}

template<typename T> bool pmd_loadScalar (std::string filename, T *data)
{
    std::ifstream file (filename, std::fstream::binary  | std::fstream::in);
    if (!file.good())
    {
        return false;
    }
    auto size = getStreamSize (file);
    if (!file.good() || size != sizeof (T))
    {
        return false;
    }
    auto byteptr = reinterpret_cast<char *> (data);
    file.read (byteptr, size);
    if (!file)
    {
        return false;
    }
    return true;
}

/** \brief returns parent directory of the given path
 *
 * \param path a relative or absolute file or directory path
 * \return the parent part of the given path. if the path
 * contains no parent part "./" is returned
 *
 */
inline std::string pmd_getDirectory (const std::string &path)
{
#if defined(_WIN32)
    const char pasep = '\\';
#else
    const char pasep = '/';
#endif

    auto pos = path.find_last_of (pasep);

    if (pos != 0 && pos == path.size() - 1)
    {
        pos = path.find_last_of (pasep, pos - 1);
    }

    if (pos != std::string::npos)
    {
        return path.substr (0, pos + 1);
    }

    return std::string (".") + pasep;
}

/**
 * Loads a binary file into a vector
 * Throws const char* if loading the file failed
 *
 * @param filepath file
 *
 * @return vector with binary data
 */
std::vector<uint8_t> loadData (const std::string &file);
