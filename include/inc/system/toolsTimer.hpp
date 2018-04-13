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

#include <ctime>
#include <ratio>
#include <chrono>
#include <vector>

typedef std::chrono::duration<float, std::ratio<1>> flSeconds;
typedef std::chrono::duration<float, std::milli> flMilliseconds;
typedef std::chrono::duration<float, std::micro> flMicroseconds;
typedef std::chrono::duration<float, std::nano> flNanoseconds;

class Timer
{
    typedef std::chrono::steady_clock Time;
    typedef std::chrono::duration<float, Time::duration::period> floatDuration;
    typedef std::vector<Time::duration> Durations;

private:
    Time::time_point tStart;
    Durations vtDurations;

public:

    Time::duration getLastDur() const
    {
        if (vtDurations.empty())
        {
            return Time::duration::zero();
        }
        else
        {
            return vtDurations.back();
        }
    }

    Timer()
    {
        static_assert (Time::is_steady, "Time is not a steady clock");
        tStart = Time::now();
    }

    void start()
    {
        tStart = Time::now();
    }

    void stop()
    {
        vtDurations.emplace_back (Time::now() - tStart);
    }

    floatDuration getMeanTime() const
    {
        Time::duration mean = Time::duration::zero();
        for (auto &cur : vtDurations)
        {
            mean += cur;
        }
        floatDuration tDuration = std::chrono::duration_cast<floatDuration> (mean) / static_cast<float> (vtDurations.size());
        return tDuration;
    }

    float getElapsedTimeMicroSec() const
    {
        return std::chrono::duration_cast<flMicroseconds> (getLastDur()).count();
    }


    float getElapsedTimeMilliSec() const
    {
        return std::chrono::duration_cast<flMilliseconds> (getLastDur()).count();
    }

    float getElapsedTimeSec() const
    {
        return std::chrono::duration_cast<flSeconds> (getLastDur()).count();
    }

    const Durations &getDurations() const
    {
        return vtDurations;
    }

};
