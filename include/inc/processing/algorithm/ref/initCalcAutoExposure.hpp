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

#include <processing/common/commonMethods.hpp>

/*
* Retrieves the bin size to be allocated for the autoexposure calculation
*
* @param numColumns Image width
* @param numColumns Image height
* @param binSize Dimensional properties of the binning container
*
* @return Status of Operation
*/
void initCalcAutoExposureGetMaxBinSize (uint32_t numColumns,
                                        uint32_t numRows,
                                        uint32_t *binSize);


/*
* Defines the auto-exposure mask and quantile threshold position
*
* @param autoExposure Reference to the spectre auto exposure data structure
* @param calib Reference to the spectre calibration data structure
* @param numColumns Number of image columns
* @param numRows Number of image rows
*
*/
void initCalcAutoExposure (struct SpectreIntermediateAutoExposure *autoExposure,
                           const struct SpectreCalibration *calib,
                           uint32_t numColumns,
                           uint32_t numRows);
#ifdef __cplusplus
}
#endif // __cplusplus
