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

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <stddef.h>
#include <float.h>
#include <processing/SpectreProcessingStatus.hpp>
#include <common/defines.h>
#include "common/version.hpp"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef FLT_MAX
#define FLT_MAX 3.402823466e+38F
#endif // FLT_MAX

#ifndef FLT_MIN
#define FLT_MIN 1.175494351e-38F
#endif // FLT_MIN

// Constants
#define PMD_INVALID 0;
/// invalid flag
static const uint32_t PMD_FLAG_INVALID = 0x00000001u;
/// saturation flag
static const uint32_t PMD_FLAG_SATURATED = 0x00000002u;
/// inconsistency flag
static const uint32_t PMD_FLAG_INCONSISTENT = 0x00000004u;
/// low signal flag
static const uint32_t PMD_FLAG_LOW_SIGNAL = 0x00000008u;
/// flying pixel flag
static const uint32_t PMD_FLAG_FLYINGPIXEL = 0x00000010u;
/// Masked flag
static const uint32_t PMD_FLAG_MASKED = 0x00000020u;
/// mpi amplitude
static const uint32_t PMD_FLAG_MPI_DIST = 0x00000040u;
/// mpi distance
static const uint32_t PMD_FLAG_MPI_AMP = 0x00000080u;
/// mask
static const uint32_t PMD_MASK_ILLUMINATION = 0x00000001u;
static const uint32_t PMD_COMBINED_FLAG_INVALID_MPI_AMP = PMD_FLAG_INVALID | PMD_FLAG_MPI_AMP;
static const uint32_t PMD_COMBINED_FLAG_INVALID_MPI_DIST = PMD_FLAG_INVALID | PMD_FLAG_MPI_DIST;
static const uint32_t PMD_COMBINED_FLAG_INVALID_INCONSISTENT = PMD_FLAG_INVALID | PMD_FLAG_INCONSISTENT;
static const uint32_t PMD_COMBINED_FLAG_INVALID_LOWSIGNAL = PMD_FLAG_INVALID | PMD_FLAG_LOW_SIGNAL;
static const uint32_t PMD_COMBINED_FLAG_INVALID_MASKED = PMD_FLAG_INVALID | PMD_FLAG_MASKED;
static const uint32_t PMD_COMBINED_FLAG_INVALID_SATURATED = PMD_FLAG_INVALID | PMD_FLAG_SATURATED;
static const uint32_t PMD_COMBINED_FLAG_INVALID_FLYINGPIXEL = PMD_FLAG_INVALID | PMD_FLAG_FLYINGPIXEL;

/**
*   Container of input values for depth data calculation
*/
struct SpectreInput
{
    uint16_t version;                   ///< Spectre processing version
    uint16_t type;                      ///< Input data type, value corresponds to SpectreTypeInput definition

    uint8_t *pv_FrameSetComposition;    ///< Composition of the frame set as list of frame types.
    float *p_temperature;               ///< Handle to the measured temperature value for systematic error compensation ( d0:1 )
    uint32_t *pv_sensorROI;             ///< Size and positional information of the input frame with respect too absolute sensor coordinates [startColum startRow ColumWidth ColumnHeight]
    uint32_t *pv_subROI;                ///< Image area to be processed within the input raw frames in relative coordinates with respect to the previous SensorROI definition [startColum startRow ColumWidth ColumnHeight]
    uint8_t numFrameSets;               ///< Number of raw frame sets
    uint8_t *pv_numFrames;              ///< Number of frames per raw frame set ( do:numFrameSets )
    uint16_t ** *pnnm_rawData;          ///< Array of pointers to superframe and the subsequent subframe sets ( do:numFrameSets | d1:pv_numFrames[n0] | d2=sensorROI[2]*sensorROI[3] )
    uint16_t **pnv_phases;              ///< Number of processed phases ( do:numFrameSets | d1:pv_numFrames[d0] )
    uint32_t *pv_exposureTimesIn;       ///< Processed exposure time ( do:numFrameSets )
    uint32_t *pv_frequencies;           ///< List of frequencies for each frame set ( do:numFrameSets )
    uint8_t *pv_illuminationModes;      ///< Operation Mode of the illumination, relates to the applied duty cycle ( do:numFrameSets )
    int8_t *pv_imagerModes;             ///< Operation Mode of the Imager, relates to current gate read out state ( do:numFrameSets )
    uint32_t *pv_exposureLimits;        ///< Holds the permittable exposure limits as [minExposure, maxExposure]
};

/**
*   Container of output values of the depth data calculation related to the prove data evaluation
*   Deprecated: Will not be supported in future releases, matrices will be stored within the intermediate data instead.
*/
struct SpectreOutputProbeData
{
    float *pm_distance;                 ///< Distance information retrieved from the phase information  ( d0:numColumns*numRows )
    float *pm_distanceNoise;            ///< Noise values related to the distance information  ( d0:numColumns*numRows )
    float *pm_amplitude;                ///< Amplitude information of the processed frame set  ( d0:numColumns*numRows )
    float *pm_amplitudeNoise;           ///< Noise values related to the amplitude image  ( d0:numColumns*numRows )
};

/**
*   Container of output values of the depth data calculation
*/
struct SpectreOutput
{
    uint16_t version;                           ///< Spectre processing version
    uint16_t type;                              ///< Output data type, value corresponds to SpectreTypeOutput definition

    uint16_t numColumns;                        ///< Total number of columns of output data
    uint16_t numRows;                           ///< Total number of rows of output data

    float *pm_distance;                         ///< Distance information of the output data ( d0:numColumns*numRows )
    float *pm_distanceNoise;                    ///< Noise value related to the distance calculation ( d0:numColumns*numRows )
    float *pm_amplitude;                        ///< Image data of the recorded amplitude ( d0:numColumns*numRows )
    float *pm3d_coord;                          ///< Distance informationo transformed into cartesian corrdinate space ( d0:numColumns*numRows*4 )
    uint32_t sizeCoords;                   ///< Size of pm3d_coords
    float *pm_intensity;                        ///< Image data of the recorded intensity ( d0:numColumns*numRows )

    uint8_t sizeProbeData;                          ///< total number of frame sets used for depth probing
    struct SpectreOutputProbeData *pns_probeData;   ///< Subdata container for frequency relted data information

    uint32_t *pm_flags;                         ///< Flag status information of the processed pixel ( d0:numColumns*numRows )
    uint8_t numFrameSets;                       ///< Number of raw frame sets
    uint32_t *pv_exposureTimesOut;              ///< Proposed integration by auto exposure calculation ( d0:numFrameSets )
};

/**
*   Flying pixel detection parametrization
*/
struct SpectreParameterFlyingPixel
{
    float f0;            ///< Linear scale value of first order for flying pixel removal
    float f1;            ///< Linear scale value of second order for flying pixel removal
    float farDist;       ///< Maximum validity check parameter for flying pixel removal
    float nearDist;      ///< Minimum validity check parameter for flying pixel removal
};

/**
*   Saturation detection parametrization
*/
struct SpectreParameterSaturationThreshold
{
    uint16_t lower;     ///< Lower limit for saturation flag verification
    uint16_t upper;     ///< Upper limit for saturation flag verification
};

/**
*   MPI processing parametrization
*/
struct SpectreParameterMPI
{
    float amplitudeThreshold;       ///< Amplitude level threshold for MPI calculation
    float distanceThreshold;        ///< Distance level threshold for MPI calculation
    float noiseDistance;            ///< Noise Distance
};

/**
*   Processing configuration parameters
*/
struct SpectreParameterConfiguration
{
    uint8_t useAdaptiveNoiseFilter;     ///< Activate auto exposure
    uint8_t useCalcIntensities;         ///< Activate unscramble intensity
    uint8_t useAutoExposure;            ///< Activate auto exposure
    uint8_t useRemoveFlyingPixel;       ///< Activate FlyingPixel flag
    uint8_t useMPIFlagAverage;          ///< Activate spatial averaging MPI value before thresholding
    uint8_t useMPIFlagAmplitude;        ///< Activates MPI-amplitude flag calculation
    uint8_t useMPIFlagDistance;         ///< Activates MPI-distance flag calculation
    uint8_t useValidateImage;           ///< Activates output image validation
    uint8_t useSparsePointCloud;        ///< Activates the output of sparse point cloud
};

/**
*   Use case dependent constant processing parameters
*/
struct SpectreParameter
{
    uint16_t version;                           ///< Spectre processing version
    uint16_t type;                              ///< Parameter data type, value corresponds to SpectreTypeParameter definition

    float amplitudeThreshold;                   ///< Upper limit values for amplitude value flags
    float consistencyTolerance;                 ///< Consistency limit for asymmetry validation
    float noiseThreshold;                       ///< Upper limit value for noise flag verification
    int adaptiveNoiseFilterType;                ///< Kerneltype value of the adaptive noise filter
    float exposureReferenceAmplitude;           ///< Reference amplitude for the auto exposure estimate

    struct SpectreParameterFlyingPixel flyingPixel;                     //< Flying pixel detection parametrization
    struct SpectreParameterMPI mpi;                                     //< MPI processing parametrization
    struct SpectreParameterSaturationThreshold saturationThreshold;     //< Saturation detection parametrization
    struct SpectreParameterConfiguration config;                        //< Processing configuration parameters

};


// Processing Data Structures
/**
* Structure represeneting Central Input/Output interface between the c++ api and ansi-c processing level.
*/
struct SpectreIO
{
    uint16_t version;
    void *p_input;
    void *p_calib;
    void *p_param;
    void *p_inter;
    void *p_output;
};

#ifndef PMD_WRAPPER
/**
* Processing of depth data and addtitional information for pmd sensors
*/
PMDDCLSPEC bool spectreRun (const struct SpectreIO *io);

PMDDCLSPEC bool spectreAstonRun (const struct SpectreInput *ps_input,
                                 const  void *ps_calib,
                                 struct SpectreParameter *ps_param,
                                 void *ps_inter,
                                 struct SpectreOutput *ps_output);

/**
 * Initializes the processing
 * This method needs to be called once before calling the processing with a specific use case (1-Freq/2-Freq mode),
 * and calibration. It initializes the internal SpectreIntermediate data structure. Ownership of the structure is
 * transferred to the caller.
 *
 *
 * @param input input structure
 * @param calib calibration structure
 * @param intermediate internal processing working structures
 *
 * @return status of operation
 */
PMDDCLSPEC SpectreProcessingStatus spectreAstonInit (const struct SpectreInput *input,
        struct SpectreCalibration *calib,
        struct SpectreIntermediate **intermediate);

/**
 * Frees the SpectreIntermediate structure
 *
 * The passed pointer must be allocated with the spectreAstonInit function. If the pointer
 * is null, no action is performed.
 *
 *
 * @param intermediate intermediate structure
 *
 */
PMDDCLSPEC void spectreAstonFree (struct SpectreIntermediate *intermediate);

#endif // PMD_WRAPPER

#ifdef __cplusplus
}
#endif
