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

#include <math.h>
#ifdef WIN32
#include <float.h>
#endif

#include <stdlib.h>

#include <processing/processingInternal.hpp>

#ifdef __cplusplus
extern "C" {
#endif

#define pmd_isNaNOrInfinity(data) ( \
    ((data * 0.0) != 0.0) \
)

/**
 * Implemention of floorf(3) function
 * The result is undefined if the result execeeds the range representable by an standard integer (int)
 *
 * @param x float
 *
 * @return floored float
 */
inline float pmd_floor (const float x)
{
    float i = (float) ( (int) (x));
    if (i > x)
    {
        i--;
    }
    return i;
}

/**
* Compares the input argument a and b and returns
* the larger value as result.
*
* @param a argument
* @param b argument
*
* @return maximum of two values a or b
*/
inline float pmd_max (float a, float b)
{
    return (b > a) ? b : a;
}

/**
* Compares the input argument a and b and returns
* the lesser value as result.
*
* @param a argument
* @param b argument
*
* @return minimum of two values a or b
*/
inline float pmd_min (float a, float b)
{
    return a < b ? a : b;
}

inline float pmd_mod (const float x, const float y)
{
    return (x - y * floorf (x / y));
}

inline float pmd_modInv (const float x, const float y, const float y_inv)
{
    return (x - y * pmd_floor (x * y_inv));
}

/**
 * Implemention of roundf(3) function
 *
 * This function is inexact in some cases (e.g., pmd_round(nextafterf(0.5f, 0.0f)) == 1.0f, instead of 0.0f).
 * The result is undefined if the result exceeds the range representable by an standard integer (int)
 *
 * @param number float
 *
 * @return rounded float
 */
inline float pmd_round (const float number)
{
    return (number < 0.0f ? ceilf (number - 0.5f) : pmd_floor (number + 0.5f));
}

inline uint32_t pmd_maxElement (uint32_t *arr, uint32_t num)
{
    uint32_t res = 0;
    uint32_t max = arr[0];
    uint32_t i;
    for (i = 1; i < num; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            res = i;
        }
    }
    return res;
}

inline uint32_t pmd_extendedGCD (const uint32_t a, const uint32_t b, int *u, int *v)
{
    if (a % b == 0)
    {
        *u = 0;
        *v = 1;
        return b;
    }

    int newu, newv;
    const uint32_t ret = pmd_extendedGCD (b, a % b, &newu, &newv);

    *u = newv;
    *v = newu - newv * (a / b);
    return ret;
}

inline uint32_t pmd_extendedLCM (const uint32_t a, const uint32_t b, int *u, int *v)
{
    return a / pmd_extendedGCD (a, b, u, v) * b;
}

inline int pmd_gcd (const uint32_t a, const uint32_t b)
{
    if (a % b == 0)
    {
        return b;
    }

    return pmd_gcd (b, a % b);
}

inline int pmd_lcm (const uint32_t a, const uint32_t b)
{
    return a / pmd_gcd (a, b) * b;
}

static float pmd_median_kernel[PMD_MEDIAN_KERNELSIZE];

#define PMD_SORT_ASC(temp, valOne, valTwo) \
{ \
    if(valOne>valTwo) \
    { \
        temp = valOne; \
        valOne = valTwo; \
        valTwo = temp; \
    } \
}

#define PMD_SORT_DESC(temp, valOne, valTwo) \
{ \
if (valOne<valTwo) \
{ \
    temp = valOne; \
    valOne = valTwo; \
    valTwo = temp; \
} \
}

inline void pmd_quicksort (float *values, int lIndex, int rIndex) // ascending order
{
    if (rIndex > lIndex)
    {
        int i = lIndex, j = rIndex;
        float pivot = values[ (lIndex + rIndex) >> 1 ];
        float tmp;

        while (i <= j)
        {
            while (values[i] < pivot)
            {
                ++i;
            }
            while (pivot < values[j])
            {
                --j;
            }

            if (i <= j)
            {
                tmp = values[i];
                values[i] = values[j];
                values[j] = tmp;

                ++i;
                --j;
            }
        }

        if (lIndex < j)
        {
            pmd_quicksort (values, lIndex, j);
        }

        if (i < rIndex)

        {
            pmd_quicksort (values, i, rIndex);
        }
    }

}

#ifdef FLAG_MPI_SORT_UNROLL

inline float pmd_medianUnroll (float *values)
{

    float temp;
    // ------------------------------------------
    PMD_SORT_ASC (temp, values[0], values[1]);
    PMD_SORT_ASC (temp, values[2], values[3]);
    PMD_SORT_ASC (temp, values[0], values[2]);
    PMD_SORT_ASC (temp, values[2], values[3]);
    PMD_SORT_ASC (temp, values[1], values[2]);
    PMD_SORT_ASC (temp, values[2], values[3]);

    PMD_SORT_ASC (temp, values[4], values[5]);
    PMD_SORT_ASC (temp, values[4], values[6]);
    PMD_SORT_ASC (temp, values[4], values[7]);

    PMD_SORT_ASC (temp, values[0], values[4]);

    // ------------------------------------------
    PMD_SORT_ASC (temp, values[4], values[5]);
    PMD_SORT_ASC (temp, values[4], values[6]);
    PMD_SORT_ASC (temp, values[4], values[7]);

    PMD_SORT_ASC (temp, values[1], values[4]);

    // ------------------------------------------
    PMD_SORT_ASC (temp, values[4], values[5]);
    PMD_SORT_ASC (temp, values[4], values[6]);
    PMD_SORT_ASC (temp, values[4], values[7]);

    PMD_SORT_ASC (temp, values[2], values[4]);

    // ------------------------------------------
    PMD_SORT_ASC (temp, values[4], values[5]);
    PMD_SORT_ASC (temp, values[4], values[6]);
    PMD_SORT_ASC (temp, values[4], values[7]);

    PMD_SORT_ASC (temp, values[3], values[4]);

    // ------------------------------------------
    PMD_SORT_ASC (temp, values[4], values[5]);
    PMD_SORT_ASC (temp, values[4], values[6]);
    PMD_SORT_ASC (temp, values[4], values[7]);

    if (values[8] > values[4])
    {
        return values[4];
    }
    else
    {
        if (values[8] > values[3])
        {
            return values[8];
        }
        else
        {
            return values[3];
        }

    }
}

#endif

inline float pmd_median (float *values, int size)
{
#ifdef FLAG_MPI_SORT_UNROLL
    return pmd_medianUnroll (values);
#else
    pmd_quicksort (values, 0 , size - 1);
    return pmd_median_kernel[4];
#endif

}

#ifdef FLAG_MPI_MEDIAN_UNROLL

inline float pmd_mpiMedian (const float *image, const uint32_t index, const uint32_t numColumns)
{
    pmd_median_kernel[0] = image[index - numColumns - 1];
    pmd_median_kernel[1] = image[index - numColumns];
    pmd_median_kernel[2] = image[index - numColumns + 1];
    pmd_median_kernel[3] = image[index - 1];
    pmd_median_kernel[4] = image[index];
    pmd_median_kernel[5] = image[index + 1];
    pmd_median_kernel[6] = image[index + numColumns - 1];
    pmd_median_kernel[7] = image[index + numColumns];
    pmd_median_kernel[8] = image[index + numColumns + 1];

    return pmd_median (pmd_median_kernel, PMD_MEDIAN_KERNELSIZE);

}

#else

inline float pmd_mpiMedian (const float *image, const uint32_t index, const uint32_t numColumns)
{
    uint32_t idx;
    for (int i = -1; i < 2; ++i)
    {
        idx = (i + 1) * PMD_KERNELWIDTH;

        for (int j = -1; j < 2; ++j, ++idx)
        {
            pmd_median_kernel[idx] = image[index + numColumns * i + j];
        }
    }

    return pmd_median (pmd_median_kernel, PMD_KERNELSIZE);

}
#endif

typedef bool (*PMD_CompareHandler) (float *, float *);


inline bool pmd_compareDesc (float *first, float *second)
{
    if (*first < *second)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool pmd_compareAsc (float *first, float *second)
{
    if (*first > *second)
    {
        return true;
    }
    else
    {
        return false;
    }
}



inline void pmd_pushHeap (float *first, int64_t holeIndex, const int64_t topIndex, float value, PMD_CompareHandler compare)
{
    int64_t parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && compare (first + parent, &value))
    {
        * (first + holeIndex) = * (first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    * (first + holeIndex) = value;
}

inline void pmd_adjustHeap (float *first, int64_t holeIndex,
                            int64_t length, float value, PMD_CompareHandler compare)
{
    const int64_t topIndex = holeIndex;
    int64_t subIndex = holeIndex;
    while (subIndex < (length - 1) / 2)
    {
        subIndex = 2 * (subIndex + 1);
        if (compare (first + subIndex,
                     first + (subIndex - 1)))
        {
            subIndex--;
        }
        * (first + holeIndex) = * (first + subIndex);
        holeIndex = subIndex;
    }
    if ( (length & 1) == 0 && subIndex == (length - 2) / 2)
    {
        subIndex = 2 * (subIndex + 1);
        * (first + holeIndex) = * (first + (subIndex - 1));
        holeIndex = subIndex - 1;
    }
    pmd_pushHeap (first, holeIndex, topIndex, value, compare);
}

inline void pmd_popHeap (float *first, float *last,
                         float *result, PMD_CompareHandler compare)
{
    float value = *result;
    *result = *first;
    pmd_adjustHeap (first,
                    0,
                    (int64_t) (last - first),
                    value, compare);
}

inline void pmd_makeHeap (float *first, float *last, PMD_CompareHandler compare)
{
    if (last - first < 2)
    {
        return;
    }

    int64_t length = (int64_t) (last - first);
    int64_t parent = (length - 2) / 2;
    while (true)
    {
        float value = * (first + parent);
        pmd_adjustHeap (first, parent, length, value, compare);
        if (parent == 0)
        {
            return;
        }
        parent--;
    }
}

inline void pmd_heap_select (float *first, float *middle, float *last, PMD_CompareHandler compare)
{
    pmd_makeHeap (first, middle, compare);

    float *idx = NULL;
    for (idx = middle; idx < last; ++idx)
    {
        if (compare (idx, first))
        {
            pmd_popHeap (first, middle, idx, compare);
        }
    }
}

inline void pmd_swap (float *a, float *b)
{
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

inline void pmd_medianSwap (float *result, float *a, float *b, float *c, PMD_CompareHandler compare)
{
    if (compare (a, b))
    {
        if (compare (b, c))
        {
            pmd_swap (result, b);
        }
        else if (compare (a, c))
        {
            pmd_swap (result, c);
        }
        else
        {
            pmd_swap (result, a);
        }
    }
    else if (compare (a, c))
    {
        pmd_swap (result, a);
    }
    else if (compare (b, c))
    {
        pmd_swap (result, c);
    }
    else
    {
        pmd_swap (result, b);
    }
}

inline float *pmd_partition (float *first,
                             float *last,
                             float *pivot,
                             PMD_CompareHandler compare)
{
    while (true)
    {
        while (compare (first, pivot))
        {
            ++first;
        }
        --last;
        while (compare (pivot, last))
        {
            --last;
        }
        if (! (first < last))
        {
            return first;
        }
        pmd_swap (first, last);
        ++first;
    }
}

inline float *pmd_pivot (float *first, float *last, PMD_CompareHandler compare)
{
    float *middle = first + (last - first) / 2;
    pmd_medianSwap (first, first + 1, middle, last - 1, compare);
    return pmd_partition (first + 1, last, first, compare);
}

inline void pmd_move_backward (float *first,
                               float *last,
                               float *d_last)
{
    while (first != last)
    {
        * (--d_last) = * (--last);
    }
}

inline void pmd_insert (float *last, PMD_CompareHandler compare)
{
    float value = *last;
    float *next = last;
    --next;
    while (compare (&value, next))
    {
        *last = *next;
        last = next;
        --next;
    }
    *last = value;
}

inline void pmd_insertionSort (float *first,
                               float *last,
                               PMD_CompareHandler compare)
{
    if (first == last)
    {
        return;
    }

    float *idx = NULL;
    for (idx = first + 1; idx != last; ++idx)
    {
        if (compare (idx, first))
        {
            float value = *idx;
            pmd_move_backward (first, idx, idx + 1);
            *first = value;
        }
        else
        {
            pmd_insert (idx, compare);
        }
    }
}

inline void pmd_introSelect (float *first, float *nth, float *last, int64_t limit, PMD_CompareHandler compare)
{
    while (last - first > 3)
    {
        if (limit == 0)
        {
            pmd_heap_select (first, nth + 1, last, compare);
            pmd_swap (nth, first);
            return;
        }
        --limit;
        float *cut = pmd_pivot (first, last, compare);
        if (cut <= nth)
        {
            first = cut;
        }
        else
        {
            last = cut;
        }
    }
    pmd_insertionSort (first, last, compare);
}

inline float pmd_nth_element (float *first, float *nth, float *last, PMD_CompareHandler compare)
{
    if (first == last || nth == last)
    {
        return -1.0f;
    }

    pmd_introSelect (first, nth, last, (int64_t) (last - first), compare);

    return *nth;
}


#ifdef ATAN_LUT
/**
* Initializes the lookup-table for the atan implementation
* The lookup-table covers the interval [0, PMD_ATAN_MAX_ARG]
* and contains PMD_ATAN_LUT_SIZE equal spaced points. The
* PMD_ATAN_LUT_SIZE + 1 entry contains the point for PMD_ATAN_MAX_ARG
*
* @return lookup table
*/
inline float *pmd_initAtanLut()
{
    float *lut = (float *) malloc (sizeof (float) * PMD_ATAN_LUT_SIZE);
    for (uint32_t i = 0; i < PMD_ATAN_LUT_SIZE; i++)
    {
        lut[i] = atanf ( ( (float) i) * PMD_ATAN_LUT_STEP_SIZE);
    }

    return lut;
}

/**
* Calculates the atan function using the lookup-table implementation
* and a linear interpolation
*
* It uses the argument reductions:
* atan(-x) = -atan(x)
* atan(x) = sgn(x)*PI/2 - atan(1/x) if |x| >= 1
*
*
* @param x argument
*
* @return atan(x)
*/
inline float pmd_atanf (float x)
{
    float x_abs;
    float z;
    float atan_z;
    float sgn;
    static const float *lut = pmd_initAtanLut();
    sgn = x > 0.0f ? 1.0f : -1.0f;

    // Reduction if |x| >= 1.0
    x_abs = fabsf (x);
    z = x_abs >= 1.0 ? 1.0f / x_abs : x_abs;
    if (x_abs >= 1.0)
    {
        z = 1.0f / x_abs;
    }

    // Calculate atan(x) for 0 <= |x| < 1
    {
        uint32_t y1_idx, y2_idx;
        float x1, y1, y2, m;
        y1_idx = (uint32_t) (z / PMD_ATAN_LUT_STEP_SIZE);
        y1_idx = y1_idx < PMD_ATAN_LUT_SIZE ? y1_idx : PMD_ATAN_MAX_IDX;
        y2_idx = y1_idx < PMD_ATAN_MAX_IDX ? y1_idx + 1 : y1_idx;

        x1 = ( (float) y1_idx) * PMD_ATAN_LUT_STEP_SIZE;
        y1 = lut[y1_idx];
        y2 = lut[y2_idx];
        m = (y2 - y1) / PMD_ATAN_LUT_STEP_SIZE;
        atan_z = sgn * (m * (z - x1) + y1);
    }

    // Backsub. if |x| >= 1.0
    if (x_abs >= 1.0)
    {
        atan_z = sgn * PMD_HALF_PI - atan_z;
    }

    return atan_z;
}

#else
inline float pmd_atanf (float x)
{
    return atanf (x);
}
#endif

/**
* Calculates the atan2f function
*
* pmd_atanf(y/x), if x > 0
* pmd_atanf(y/x) + copysign(PI, y), x < 0
* copysign(PI/2, y), x = 0, y != 0
* 0, x = y =9
*
* @param x x-coordinate
* @param y y-coordinate
*
* @return angle between positive x-axis and (x,y)
*/
inline float pmd_atan2f (float y, float x)
{
    const float eps = 1e-30f;

    if (fabsf (x) < eps)
    {
        if (fabsf (y) < eps)
        {
            return 0.0;
        }
        return copysignf (PMD_HALF_PI, y);
    }

    if (x > 0)
    {
        return pmd_atanf (y / x);
    }

    return pmd_atanf (y / x) + copysignf (PMD_PI, y);
}

/**
* Calculates an approximation for the exponential function
* which be accurate to approx. 1.2*10e-4.
*
* The approximation is only valid for -85 <= x <= 0.
*
* @param x argument
*
* @return approximation for exp(x)
*/
inline float pmd_expf (float x)
{
    x = pmd_max (x * PMD_LD_E, -127.0f);
    int truncx = (int) x;
    float err = x - (float) truncx + 1.0f;
    union
    {
        uint32_t i;
        float f;
    } res;
    res.i = (uint32_t) (8388608 * (x + 127.00247609615325927734375f +
                                   err * (-0.3489532172679901123046875f +
                                          err * 0.344001114368438720703125f)));
    return res.f;
}


#ifdef __cplusplus
}
#endif
