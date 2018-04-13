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

#include <map>
#include <sstream>
#include <system/toolsTimer.hpp>

class TimerMapHandler
{
public:
    TimerMapHandler() {}

    void printTimings()
    {
        cellSeperator = "|";
        lineSeperator = '-';
        lineStartEnd = "|";
        printHeaders (std::cout);
        printSeperatorLine (std::cout);
        printData (std::cout);

    }

private:

    void printHeaders (std::ostream &out)
    {
        if (di_e.timerMap.empty())
        {
            out << "No timings recorded!\n";
            return;
        }
        std::stringstream buf;
        size_t noOfTimings = di_e.timerMap.begin()->second.getDurations().size();
        out << std::setiosflags (std::ios::left);
        out << lineStartEnd << std::setw (32) << "algorithm name" << cellSeperator;
        out << std::resetiosflags (std::ios::left);
        for (size_t i = 0; i < noOfTimings; ++i)
        {
            buf << "time" << i + 1;
            out << std::setw (14) << buf.str() << cellSeperator;
            buf.str ("");
            buf << "time" << i + 1 << " per run";
            out << std::setw (14) << buf.str() << cellSeperator;
            buf.str ("");
        }
        out << std::setw (12) << "mean" << cellSeperator;
        out << std::setw (12) << "mean per run" << lineStartEnd << std::endl;
    }



    void printSeperatorLine (std::ostream &out)
    {
        if (di_e.timerMap.empty())
        {
            out << "No timings recorded!\n";
            return;
        }
        size_t noOfTimings = di_e.timerMap.begin()->second.getDurations().size();
        char lastfill = out.fill();
        out.fill (lineSeperator);
        out << lineStartEnd << std::setw (32) << lineSeperator << cellSeperator;
        out << std::resetiosflags (std::ios::left);
        for (size_t i = 0; i < noOfTimings; ++i)
        {
            out << std::setw (14) << lineSeperator << cellSeperator;
            out << std::setw (14) << lineSeperator << cellSeperator;
        }
        out << std::setw (12) << lineSeperator << cellSeperator;
        out << std::setw (12) << lineSeperator << lineStartEnd << std::endl;
        out.fill (lastfill);
    }

    void printData (std::ostream &out)
    {
        for (auto &curTimer : di_e.timerMap)
        {
            out << std::setiosflags (std::ios::left) << lineStartEnd << std::setw (32) << curTimer.first << std::resetiosflags (std::ios::left) << cellSeperator;
            writeTimings (cellSeperator, out, curTimer.second);
            auto mean = curTimer.second.getMeanTime();
            float iterations = PMD_TEST_ITERATIONS;
            out << std::setw (12) << std::chrono::duration_cast<flMilliseconds> (mean).count() << cellSeperator;
            out << std::setw (12) << std::chrono::duration_cast<flMilliseconds> (mean / iterations).count() << lineStartEnd << std::endl;
        }
    }

    void writeTimings (const std::string &cellSeperator, std::ostream &out, const Timer &watch)
    {
        float iterations = PMD_TEST_ITERATIONS;
        for (auto time : watch.getDurations())
        {
            out << std::setw (14) << std::chrono::duration_cast<flMilliseconds> (time).count() << cellSeperator;
            out << std::setw (14) << std::chrono::duration_cast<flMilliseconds> (time / iterations).count() << cellSeperator;
        }
    }

    std::string cellSeperator;
    std::string lineStartEnd;
    char lineSeperator;
};
