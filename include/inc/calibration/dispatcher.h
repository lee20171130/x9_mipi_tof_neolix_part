/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/
#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include <stdint.h>
#include <stddef.h>

#include <calibration/calibration.h>

struct SpectreCalibration;

/**
 * Pointer to function which determines whether a given calibration blob is supported by the calibration handler
 *
 * Expected signature:
 * int fn(const uint8_t *blob, size_t sizeOfBlob);
 *
 * Should return 0 if the passed calibration blob cannot be handled, any other value otherwise.
 *
 */
typedef int (*supportsCalibrationFn) (const uint8_t*, size_t);

/**
 * Pointer to a function which reads a given calibration blob
 *
 * Expected signature:
 * enum spectre_CalibrationStatus fn(const uint8_t *calibBlob, size_t size, SpectreCalibration *calib);
 *
 * Should return SPECTRE_STATUS_SUCCESS if the calibration was read successfully, otherwise an
 * appropriate error code. If the operation succeeded calib should be filled with the read data, otherwise
 * the state of calib is undefined. Note that calib is owned by the caller.
 */
typedef enum spectre_CalibrationStatus (*readCalibrationFn) (const uint8_t *,
                                                           size_t, struct SpectreCalibration *);

/**
 * Pointer to a function which returns the calibration type supported by this handler
 *
 * Expected signature:
 * enum spectre_CalibrationType fn()
 *
 * Returns the supported calibration type.
 *
 */
typedef enum spectre_CalibrationType (*getCalibrationTypeFn) ();

/**
 * Pointer to a function which returns the number of pixels contained in this calibration blob.
 *
 * Expected signature:
 * int fn(const uint8_t *calibBlob, size_t size)
 *
 * The function should return the number of pixels in the picture, or an error code defined by
 * enum spectre_calibrationStatus
 */
typedef int (*getNumPixelsFn) (const uint8_t *, size_t);

/// Structure which describes a calibration type
struct spectre_calibrationHandler {
    /// Function to determine if a calibration blob is supported by the handler
    supportsCalibrationFn supportsCalibration;

    /// Function to a read a calibration blob
    readCalibrationFn readCalibration;

    /// Function to get the supported calibration type
    getCalibrationTypeFn getCalibrationType;

    /// Function to get the number of pixels in a calibration blob
    getNumPixelsFn getNumPixels;
};

/**
 * Registers a new calibration handler
 *
 * @param handler handler to register
 *
 * @return 0 if an error occurred, 1 otherwise
 */
int spectre_registerCalibrationHandler(struct spectre_calibrationHandler handler);

/**
 * Clears the list of registered calibration handlers.
 */
void spectre_clearCalibrationHandlers();

/**
 * Returns if the given calibration blob is supported
 *
 * The check is performed by calling all registered calibration handlers until one claims to support
 * the format, or no handler is left. The order in which the handlers are called is arbitrary.
 *
 * @param calibBlob calibration blob
 * @param size size of blob
 *
 * @return type of the format or SPECTRE_TYPE_UNSUPPORTED
 */
enum spectre_CalibrationType spectre_dispatchGetCalibrationType(const uint8_t *calibBlob, size_t size);

/**
 * Reads the given calibration, and provides a spectre_Calibration structure for further operation
 *
 * This function first determines a valid calibration handler for the given blob, and uses the first
 * handler found to read the calibration. If the operation was successful SPECTRE_STATUS_SUCCESS is returned,
 * and calib contains to the read calibration. In case of an error, the state of calib is undefined. Calib is
 * owned by the caller.
 *
 * @param calibBlob calibration blob
 * @param size size of blob
 * @param calib pointer to parsed calibration
 *
 * @return status of operations
 */
enum spectre_CalibrationStatus spectre_dispatchReadCalibration (const uint8_t *calibBlob, size_t size,
                                                                struct SpectreCalibration *calib);
/**
 * Returns the number of pixels in a calibration blob
 *
 * @param calibBlob calibration blob
 * @param size size of the blob
 *
 * @return the number of pixels in the picture (> 0), or an error code (< 0)
 */
int spectre_dispatchGetNumPixels (const uint8_t *calibBlob, size_t size);

#endif /*__DISPATCHER_H__*/
