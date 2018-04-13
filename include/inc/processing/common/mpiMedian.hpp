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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * Applies a 3x3 Median filter on the passed image
 * The implemention uses the method described in
 * "Efficient 3x3 Median Filter Computations" by Kopp and Purgathofer
 *
 * @param numColumns number of columns
 * @param numRows number of rows
 * @param image image
 * @param tmp temporary space (of numColumns*numRows size)
 */
void pmd_mpiFastMedian (uint32_t numColumns, uint32_t numRows,
                        float *image, float *tmp);


#ifdef __cplusplus
}
#endif

