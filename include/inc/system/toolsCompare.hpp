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

#define VNAME(x) #x

#include <gmock/gmock.h>
#include <climits>
#include <float.h>
#include <limits>
#include <system/toolsIO.hpp>

#include <processing/common/commonMethods.hpp>

/**
 * Calculates the combined unique range
 *
 * The combined unique range is defined as min(ur1, ur2) + ur1*n2 / (2*n1*n2)
 * where n1 and n2 are the proportion between the least common multiple of the frequencies
 * and the respective frequency.
 *
 *
 * @param modulationFrequency1 first modulation frequency
 * @param modulationFrequency2 second modulation frequency
 *
 * @return const ur_c
 */
float calculateCombinedUniqueRange (int modulationFrequency1 , int modulationFrequency2);

/**
 * Calculates the maximum absolute allowed distance deviation for a given pixel
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference noise
 *
 * @return limit in m
 */
float calculateLimit (float refDist, float calDist, float refDistNoise);

/**
 * Checks if a calculated distance is within the acceptable limit to a reference distance
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference distance noise
 * @param urc combined unambigious range (0.0 for one frequency)
 *
 * @return true if the distance is within the definied limits
 */
bool checkDistance (float refDist, float calDist, float refDistNoise, float urc);

/**
 * Compares an array of calculated distances to an array of reference distance
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference distance noise
 * @param size size of arrays
 * @param urc combined unambigous range
 *
 * @return number of mismatches
 */
uint32_t compareDistance (const float *refDist,
                          const float *calDist,
                          const float *refDistNoise,
                          uint32_t size,
                          float urc);

/**
 * Compares an array of calculated distances to an array of reference distances
 * Convenience method for two frequencies
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference distance noise
 * @param size size of arrays
 * @param modulationFrequency1 first frequency
 * @param modulationFrequency2 second frequency
 *
 * @return number of mismatches
 */
uint32_t compareDistance (const float *refDist,
                          const float *calDist,
                          const float *refDistNoise,
                          uint32_t size,
                          uint32_t modulationFrequency1,
                          uint32_t modulationFrequency2);
/**
 * Compares an array of calculated distances to an array of reference distances
 * Convenience method for one frequency
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference distance noise
 * @param size size of arrays
 *
 * @return number of mismatches
 */
uint32_t compareDistance (const float *refDist,
                          const float *calDist,
                          const float *refDistNoise,
                          uint32_t size);

/// Functor to calculate the absolute difference between two types
/**
 * The generic version of this functor always throws.
 * It needs to be specialized for each supported type.
 */
template<typename T>
struct AbsDiff
{
    /// return type of functor
    using return_t = T;

    /**
     * Calculates the absolute difference between the arguments
     *
     * @return absolute difference
     */
    return_t operator() (T, T) const
    {
        throw "Please specialize this template!";
    }
};


template<>
struct AbsDiff<uint32_t>
{
    using return_t = uint64_t;

    return_t operator() (uint32_t rhs, uint32_t lhs) const
    {
        auto ret = static_cast<int64_t> (rhs) - static_cast<int64_t> (lhs);
        ret = ret > 0 ? ret : -ret;
        return static_cast<uint64_t> (ret);
    }
};


template<>
struct AbsDiff<float>
{
    using return_t = double;

    return_t operator() (float rhs, float lhs) const
    {
        return fabs (static_cast<double> (rhs) - static_cast<double> (lhs));
    }
};



/**
* Compares an array of equal length and two data types
* if absolute difference between each value is within
* the below a predefined single threshold value.
* Furthermore the total average error is calculated
* and verified with respect to a predefined threshold limit.
* If necessary a limit value can be defined to allow for a certain
* number of missmatches.
* Additionally a flag map can be provided, which needs to be of equal
* size as the arrays to be compared with. In this case, the compare
* operation ignores the flagged data values for the verification
* process.
*
* @param name Name definition assigned to the test message notification
* @param size Size of the array element to be processed
* @param refData Data used as referernce to be compared against
* @param calData Data calculated in a previous step to validated
* @param singleThresh Threshold value for single data comparison
* @param averageThresh Threshold value for average error comparison
* @param limit Number of allowed missmatches
* @param flags Flag map to be provided, used as a specific ignore list.
*
* @return True if comparison criteria are met, else false.
*/
template <typename T>
inline bool compare (const std::string name,
                     const uint32_t size,
                     const T *refData,
                     const T *calData,
                     const T singleThresh = 0,
                     const T averageThresh = 0,
                     uint32_t limit = 0,
                     uint32_t *flags = nullptr)
{
    uint32_t flagCount = 0;

    T *newRefData = new T[size];
    T *newCalData = new T[size];

    memcpy (newRefData, refData, size * sizeof (T));
    memcpy (newCalData, calData, size * sizeof (T));

    uint32_t suppressSinglePixelErrors = 1;
    uint32_t total = 0;
    uint32_t nanCounts = 0;
    uint32_t mismatchCount = 0;

    using diff_t = typename AbsDiff<T>::return_t;
    auto maxMismatch = std::numeric_limits<diff_t>::lowest();
    auto minMismatch = std::numeric_limits<diff_t>::max();
    diff_t averageErr = 0;

    uint32_t maxPosition = 0;
    uint32_t minPosition = 0;

    if (flags != nullptr)
    {
        for (uint32_t idx = 0; idx < size; ++idx)
        {
            if (flags[idx])
            {
                flagCount++;
                newRefData[idx] = 0;
                newCalData[idx] = 0;
            }
        }
    }

    for (uint32_t i = 0; i < size; ++i)
    {
        AbsDiff<T> diff;
        total++;

        if ( (pmd_isNaNOrInfinity (newRefData[i]) && pmd_isNaNOrInfinity (newCalData[i])) ||
                (std::numeric_limits<float>::infinity() == newRefData[i] && (std::numeric_limits<float>::infinity() == newCalData[i] ||
                        -1.f * std::numeric_limits<float>::infinity() == newCalData[i])))
        {
            nanCounts++;
        }
        else
        {
            if (!suppressSinglePixelErrors)
            {
                EXPECT_NEAR ( (double) newCalData[i], (double) newRefData[i], (double) singleThresh);
            }
            auto misMatch = diff (newCalData[i], newRefData[i]);

            if (misMatch > singleThresh)
            {
                mismatchCount++;

                if (misMatch > maxMismatch)
                {
                    maxMismatch = misMatch;
                    maxPosition = i;
                }

                if (misMatch < minMismatch)
                {
                    minMismatch = misMatch;
                    minPosition = i;
                }
            }
            averageErr += misMatch;
        }
    }

    averageErr = (T) (fabsf ( (float) averageErr) / (float) size);


    if (mismatchCount > limit)
    {
        std::cout << std::endl;
        std::cout << "Variable: " << name.c_str() << std::endl;
        if (flags != nullptr)
        {
            std::cout << "Flagged values:" << flagCount << std::endl;
        }
        std::cout << "Mismatch count: " << mismatchCount << std::endl;
        std::cout << "Average error: " << averageErr << std::endl;
        std::cout << "NaN count: " << nanCounts << std::endl;
        std::cout << "Max mismatch: " << maxMismatch << " | Position: " << maxPosition << " | Ref. Value: " << refData[maxPosition] << " | Cal. Value: " << calData[maxPosition] << std::endl;
        std::cout << "Min mismatch: " << minMismatch << " | Position: " << minPosition << " | Ref. Value: " << refData[minPosition] << " | Cal. Value: " << calData[minPosition] << std::endl;
        if (averageThresh != 0)
        {
            EXPECT_LE (averageErr, averageThresh);
        }
        EXPECT_LE (mismatchCount, 0u);
        std::cout << std::endl;
    }

    delete[] newRefData;
    delete[] newCalData;

    return mismatchCount <= limit;
}


/**
* Merges a set of two flag maps into a
* combined one. The flag state for the combined
* flag map is set either to 1 := flag set or
* 0:= flag unset. If the validate flag is set also
* the flag values of the input map is set
* either to 0 or 1.
*
* @param flagsMapOne first flag map used for merge
* @param flagsMapTwo second flag map used for merge
* @param flagsMapMerged resulting flag map with reduced flag state
* @param numPixel common size of the flag maps
* @param validate
*/
inline void mergeAndUnifyFlags (uint32_t *flagsMapOne,
                                uint32_t *flagsMapTwo,
                                uint32_t *flagsMapMerged,
                                size_t numPixel,
                                uint8_t validate = 0)
{
    for (uint32_t idx = 0; idx < numPixel; ++idx)
    {
        if (flagsMapOne[idx] != 0 || flagsMapTwo[idx] != 0)
        {
            flagsMapMerged[idx] = 1;
        }
        else
        {
            flagsMapMerged[idx] = 0;
        }

        if (validate != 0)
        {
            if (flagsMapOne[idx] != 0)
            {
                flagsMapOne[idx] = 1;
            }

            if (flagsMapTwo[idx] != 0)
            {
                flagsMapTwo[idx] = 1;
            }
        }
    }
}

/**
 * Splits a given coordinate array with the layout [x1,y1,z1,c1,x2,y2,z2,c2,...,xn,yn,zn,cn] into a tuple of vectors where all x_i
 * are in the first member of the tuple, all y_i in the second member, and so on.
 *
 * @param coordinates coordinate vector
 *
 * @return tuple of vectors
 */
std::tuple<std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float> > splitCoordinates (std::vector<float> coordinates);
