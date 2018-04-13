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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
*   Probe specific calibration data
*/
struct SpectreCalibrationWiggling
{
    uint8_t size;                   ///< Total number of wiggling correction terms.
    float *pv_amplitude;            ///< Wiggling corretion amplitude value of a specific harmonic ( d0:size )
    uint32_t *pv_harmonic;          ///< Wiggling corretion order values of the harmonics ( d0:size )
    float *pv_phase;                ///< Wiggling corretion amplitude value of a specific harmonic ( d0:size )
    float offset;                   ///< Wiggling corretion offset value used for data adaptation
};


/**
*   Probe specific calibration data
*/
struct SpectreCalibrationProbeData
{
    // fppn correction
    uint32_t frequency;             ///< Specific frequency the calibration data is intended for.
    float *pm_fppn;                 ///< calibration values used for "Fixed-Pattern-Phase-Noise" suppression ( d0:numColumns*numRows )

    // TemperatureCompensation
    uint8_t sizeTempCompensation;   ///< number of entry values for temperature compensation
    float *pv_tempCompensation;     ///< Container for temperature compensation values ( d0:numColumns*numRows )

    // Noise cancellation
    uint8_t sizeNoiseParamter;      ///< number of entry values for noise parametrization
    float *pv_noiseParameter;       ///< Noise parameter used for the noise calcultaion

    // Wiggling correction
    struct SpectreCalibrationWiggling ps_phaseWiggling;           // Wiggling corretion information for phase wiggling compensation.
    struct SpectreCalibrationWiggling ps_amplitudeWiggling;       // Wiggling corretion information for amplitude wiggling compensation.
};

/**
*   Hardware and calibration related sensor information
*/
struct SpectreCalibration
{
    /// Version of the calibration structure
    // 1: ASTON
    uint16_t version;
    /// Type of the underlying calibration data (corresponds to the enum spectre_CalibrationType)
    uint16_t type;                          ///< Calibration data type, value corresponds to SpectreTypeCalibration definition

    char *pc_date;                          ///< Date of generation ( d0:19 )
    char *pc_serial;                        ///< Serial number of the device ( d0:9 )
    char *pc_sensorSerial;                  ///< Serial number of the specific sensor ( d0:19 )

    uint32_t *pv_calibrationROI;            ///< Storage location of the calibration data absolute sensor coordinates [startColum startRow ColumWidth ColumnHeight]

    float *pm3d_directions;                 ///< Array of vectorinformation used for depth data transformation  ( d0:calibrationROI[2]*calibrationROI[3]*3 )

    uint8_t sizeLensParam;                  ///< total number of lensparameter entry values.
    float *pv_lensparam;                    ///< Parameters of the lensdata ( d0:sizeLensParam )
    uint8_t *pm_mask;                       ///< Mask of invalid image areas ( d0:calibrationROI[2]*calibrationROI[3] )
    float *pm_fpn;                          ///< ps_calib->ation values used for "Fixed-Pattern-Noise" suppression ( d0:calibrationROI[2]*calibrationROI[3] )

    /**
     *  Size of the per frequency data
     *
     *  At the moment this should correspondend to the values of the SpectreTypeCalibration enum
     */
    uint8_t sizeProbeData;
    struct SpectreCalibrationProbeData *pns_probeData;      ///< Container for frequency specific ps_calib->ation data ( d0:sizeProbeData )
};

#ifdef __cplusplus
}
#endif
