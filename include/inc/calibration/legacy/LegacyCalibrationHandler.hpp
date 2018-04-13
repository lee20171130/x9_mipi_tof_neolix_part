/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __LEGACYCALIBRATIONHANDLER_HPP__
#define __LEGACYCALIBRATIONHANDLER_HPP__

#include <calibration/dispatcher.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets the calibration handler for legacy calibration formats (in TAR/GZ) format
 *
 *
 * @return legacy calibration handler
 */
struct spectre_calibrationHandler spectre_getLegacyCalibrationHandler();

#ifdef __cplusplus
}
#endif

#endif /*__LEGACYCALIBRATIONHANDLER_HPP__*/
