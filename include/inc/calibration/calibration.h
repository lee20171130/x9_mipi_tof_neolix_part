/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/
#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__

#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <common/defines.h>

/// Uncompressed calibration suitable for the processing
struct SpectreCalibration;

/// Calibration format
enum spectre_CalibrationType {
    /// Unsupported format
    SPECTRE_TYPE_UNSUPPORTED,
    /// Legacy PMD TAR format
    SPECTRE_TYPE_LEGACY,
    /// ASTON (Spectre) calibration format
    SPECTRE_TYPE_ASTON
};

/// Status of operations in libcalibration
enum spectre_CalibrationStatus {
    /// The requested field is unknown to libcalibration
    SPECTRE_STATUS_UNKNOWN_FIELD = INT_MIN,
    /// The requested field is not supported for the given calibration type
    SPECTRE_STATUS_UNSUPPORTED_FIELD,
    /// The calibration blob is in an unsupported format
    SPECTRE_STATUS_UNSUPPORTED_FORMAT,
    /// The calibration blob ended unexpectedly
    SPECTRE_STATUS_UNEXPECTED_END,
    /// Invalid arguments where passed to the callee,
    SPECTRE_STATUS_INVALID_ARGUMENTS,
    /// A dynamic field in the calibration is bigger the defined maximum size
    SPECTRE_STATUS_MAXIMUM_SIZE_EXCEEDED,
    /// The calibration data is corrupt
    SPECTRE_STATUS_DATA_CORRUPT,
    /// An unknown error occurred
    SPECTRE_STATUS_UNKNOWN_ERROR,
    /**
     *  The parsing of the calibration was successful, but some data is missing.
     *
     *  Missing data has been replaced by default values.
     *  Quality of the depth data processing might be degraded due to this fact.
     */
    SPECTRE_STATUS_SUCCESS_INCOMPLETE,
    /// The operation succeeded
    SPECTRE_STATUS_SUCCESS = 0
};

/// Publicly exposed calibration fields
enum spectre_CalibrationField {
    /// Lensparameters (of type float)
    SPECTRE_FIELD_LENSPARAMETERS,
    /// Imager serial (of type char)
    SPECTRE_FIELD_SERIAL,
    /// Sensor serial (of type char)
    SPECTRE_FIELD_SENSOR_SERIAL,
    /// Calibration ROI (of type uint32_t)
    SPECTRE_FIELD_CALIBRATION_ROI
};

/**
 * Tries to determine the type of a calibration blob
 * Users should use this function to determine if a given calibration blob is in a
 * format supported by libcalibration.
 *
 * @param calibBlob pointer to calibration blob
 * @param size size of blob
 *
 * @return type of the calibration or UNSUPPORTED
 */
PMDDCLSPEC enum spectre_CalibrationType spectre_getCalibrationType(const uint8_t* calibBlob, size_t size);

/**
 * Tries to determine the type of a calibration handle. The caller is responsible for the given calibration to be allocated.
 *
 * @param calib given calibration
 *
 * @return type of the calibration or UNSUPPORTED
 */
PMDDCLSPEC enum spectre_CalibrationType spectre_getCalibrationTypeFromHandle(const struct SpectreCalibration * calib);

/**
 * Deallocates the given spectre_Calibration
 * If calib is (spectre_Calibration*)0 no operation is performed.
 *
 * @param calib pointer to calibration
 */
PMDDCLSPEC void spectre_freeCalibration(struct SpectreCalibration* calib);

/**
 * Reads the given calibration blob, allocates a new spectre_Calibration, and fills it with the
 * calibration data contained in calibBlob. If an error occurred calib remains unchanged.
 *
 * The caller is the owner of the new spectre_Calibration object, and responsible to free it through
 * spectre_freeCalibration if the object is no longer needed.
 *
 * @param calibBlob pointer to the calibration blob
 * @param size size of calibBlob
 * @param calib pointer to pointer of spectre_Calibration
 *
 * @return status of operation
 */
PMDDCLSPEC enum spectre_CalibrationStatus spectre_readCalibration(const uint8_t *calibBlob, size_t size,
                                                                  struct SpectreCalibration **calib);

/**
 * Gets the number of bytes of public calibration field for a given calibration.
 *
 * If the returned value is < 0 an error occurred. The function spectre_getStatusFromCode
 * can be used to derive a spectre_CalibrationStatus from the returned error code.
 *
 * @param field requested field
 * @param calib given calibration
 *
 * @return number of bytes (>= 0), or an error code (<0)
 */
PMDDCLSPEC int spectre_getFieldSize(enum spectre_CalibrationField field, const struct SpectreCalibration *calib);

/**
 * Copies all array elements of a given public calibration field to the given buffer.
 * The caller is responsible for allocating the necessary amount of memory for dest, which should
 * be at least spectre_getFieldSize(field, calib). Ownership of the
 * passed buffer is retained by the caller.
 *
 * @param field requested field
 * @param calib given calibration
 * @param dest destination buffer
 *
 * @return status of operation
 */
PMDDCLSPEC enum spectre_CalibrationStatus spectre_getField(enum spectre_CalibrationField field,
                                                const struct SpectreCalibration *calib,
                                                void *dest);

/**
 * Gets the version of libcalibration
 *
 * @return libcalibration version
 */
PMDDCLSPEC const char* spectre_getVersion();

/**
 * Converts an error code to the corresponding spectre_CalibrationStatus value
 *
 * @param code error code
 *
 * @return corresponding value
 */
PMDDCLSPEC enum spectre_CalibrationStatus spectre_getStatusFromCode(int code);


// *********************************************************************************************************************
// Extended interface (possibly in another non-public header)
// *********************************************************************************************************************
/**
 * Gets the total amount of dynamic memory which will be allocated for the final
 * spectre_Calibration which contains the calibration after parsing and
 * uncompressing done by libcalibration.
 *
 * It is not guaranteed that this function is supported for all calibration types.
 * If the return value is < 0 an error occurred. Use the function spectre_spectre_getStatusFromCode
 * to convert the error code to a spectre_CalibrationStatus.
 *
 * @param calibBlob pointer to calibration blob
 * @param size size of blob
 *
 * @return number of bytes to be allocated (>= 0), or an error code (< 0)
 */
PMDDCLSPEC int spectre_getCalibrationSize(const uint8_t *calibBlob, size_t size);

/**
 * Gets the amount of dynamic memory which will be allocated during parsing and
 * uncompressing the given calibration blob.
 *
 * It is not guaranteed that this function is supported for all calibration types.
 * If the return value is < 0 an error occurred. Use the function spectre_spectre_getStatusFromCode
 * to convert the error code to a spectre_CalibrationStatus.
 *
 *
 * @param calibBlob pointer to calibration blob
 * @param size size of blob
 *
 * @return number of bytes to be allocated (>= 0), or an error code (< 0)
 */
PMDDCLSPEC int spectre_getTemporaryMemorySize(const uint8_t *calibBlob, size_t size);

#endif /*__CALIBRATION_H__*/
