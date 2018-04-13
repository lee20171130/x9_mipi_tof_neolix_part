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
#include "processing/processing.hpp"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef FLT_MAX
#define FLT_MAX 3.402823466e+38F
#endif // FLT_MAX

#ifndef FLT_MIN
#define FLT_MIN 1.175494351e-38F
#endif // FLT_MIN

#define FLAG_MPI_SORT_UNROLL
#define FLAG_MPI_MEDIAN_UNROLL

#define ATAN_LUT

// Constants
#define PMD_INVALID 0;

static const float PMD_MIN = 0.00000000010f;
static const float PMD_MAX = 10000000000.0f;

static const float PMD_TOLMOD = 0.5f;
static const float PMD_PI = 3.14159265359f;
static const float PMD_HALF_PI = PMD_PI / 2.0f;
static const float PMD_TWOPI = 2.0f * PMD_PI;
static const float PMD_TWOPI_INV = 1.0f / (2.0f * PMD_PI);
static const float PMD_SQRTOF2 = 1.414213562373095f;
static const float PMD_SQRTOF2_INV = (1 / PMD_SQRTOF2);

static const float PMD_SOL = 299792458.0f / 1.000293f;

static const uint8_t PMD_ARM_AMPLITUDE_WIGGLING_LUT_SIZE = 128u;

/// Size of LUT for wiggling correction
static const uint8_t PMD_ARM_PHASE_WIGGLING_LUT_SIZE = 128u;
/// Step size of LUT for wiggling correction
static const float PMD_ARM_PHASE_WIGGLING_STEP_SIZE = PMD_TWOPI / (PMD_ARM_PHASE_WIGGLING_LUT_SIZE - 1);
/// Inverse step size of LUT for wiggling correction
static const float PMD_ARM_PHASE_WIGGLING_INV_STEP_SIZE = (PMD_ARM_PHASE_WIGGLING_LUT_SIZE - 1) / PMD_TWOPI;

static const uint32_t PMD_FILTER_ADAPTIVENOISE_LUTSIZE = 16384;
static const float PMD_FILTER_ADAPTIVENOISE_LUT_PRECISION = 1024.0f;

static const uint32_t PMD_AMPLITUDE_WIGGLING_LUT_SIZE = 16384;
static const float PMD_RAD_TO_LUT_AW = ( (PMD_AMPLITUDE_WIGGLING_LUT_SIZE - 1) * (1.0f / (2.0f * PMD_PI)));
static const float PMD_PHI_SPACING_AW = ( ( (2.0f * PMD_PI) / (PMD_AMPLITUDE_WIGGLING_LUT_SIZE - 1)));

static const uint32_t PMD_PHASE_WIGGLING_LUT_SIZE = 16384;
static const float PMD_RAD_TO_LUT_PW = ( ( (PMD_PHASE_WIGGLING_LUT_SIZE - 1) * (1.0f / (2.0f * PMD_PI))));
static const float PMD_PHI_SPACING_PW = ( (2.0f * PMD_PI) / (PMD_PHASE_WIGGLING_LUT_SIZE - 1));
static const float PMD_PHI_SPACING_INV_PW = 1.0f / PMD_PHI_SPACING_PW;

static const uint32_t PMD_FILTER_ADAPTIVENOISE_MAX_KERNELTYPE = 2;
static const uint32_t PMD_FILTER_ADAPTIVENOISE_MAX_KERNELWIDTH = (2 * PMD_FILTER_ADAPTIVENOISE_MAX_KERNELTYPE + 1);
static const uint32_t PMD_FILTER_ADAPTIVENOISE_MAX_KERNELSIZE = (PMD_FILTER_ADAPTIVENOISE_MAX_KERNELWIDTH *PMD_FILTER_ADAPTIVENOISE_MAX_KERNELWIDTH);
static const uint32_t PMD_FILTER_ADAPTIVENOISE_SIGMA = 2;
static const float PMD_FILTER_ADAPTIVENOISE_SIGMANORM = (2 * PMD_FILTER_ADAPTIVENOISE_SIGMA *PMD_FILTER_ADAPTIVENOISE_SIGMA);
static const float PMD_FILTER_ADAPTIVENOISE_SCALE = 2.5f;

static const uint32_t PMD_MEDIAN_KERNELTYPE = 1;
static const uint32_t PMD_MEDIAN_KERNELWIDTH = (2 * PMD_MEDIAN_KERNELTYPE + 1);
static const uint32_t PMD_MEDIAN_KERNELSIZE = (PMD_MEDIAN_KERNELWIDTH *PMD_MEDIAN_KERNELWIDTH);

/// Size of LUT for atan implemention
static const uint32_t PMD_ATAN_LUT_SIZE = 32;
#ifndef SWIG
static_assert (! (PMD_ATAN_LUT_SIZE & (PMD_ATAN_LUT_SIZE - 1)),
               "PMD_ATAN_LUT_SIZE should be a power of two.");
#endif
/// Last argument calculated for LUT
static const uint32_t PMD_ATAN_MAX_ARG = 1;
#ifndef SWIG
static_assert (! (PMD_ATAN_MAX_ARG & (PMD_ATAN_MAX_ARG - 1)),
               "PMD_ATAN_MAX_ARG should be a power of two.");
#endif
/// Maximum index of atan LUT
static const uint32_t PMD_ATAN_MAX_IDX = PMD_ATAN_LUT_SIZE - 1;
/// Equidistant step size of atan LUT
static const float PMD_ATAN_LUT_STEP_SIZE = (float) PMD_ATAN_MAX_ARG / (float) (PMD_ATAN_LUT_SIZE - 1);

// ld(e)
static const float PMD_LD_E = 1.44269502162933349609375f;

// Processing Data Structures
/**
*   Container of arrays for processing phase related information at a specific frequency
*/
struct SpectreIntermediateProbeData
{
    float *pm_re;                       ///< Real part of the phase  ( d0:ImageSize )
    float *pm_im;                       ///< Imaginary part of the phase  ( d0:ImageSize )
    float *pm_asym;                     ///< asymmetry between real and imaginary part of the phase  ( d0:ImageSize )
    float *pm_amplitudeNorm;            ///< Normalized Amplitude = Amplitude Noise / integrationTime  ( d0:ImageSize )
    float *pm_amplitudeNoiseNorm;       ///< Normalized Amplitude Noise =  Amplitude Noise / integrationTime  ( d0:ImageSize )
    float range;                        ///< Maxmimum ambigous range of the frame set

    uint32_t *pv_armPhaseWigglingScale;        ///< Phase wiggling correction scale factor ( d0:2 ) - neon implementation only, not represented in Aston intermediate container - to be resolved in Bentley
    uint32_t *pv_armAmplitudeWigglingScale;    ///< Amplitude wiggling correction scale factor ( d0:2 ) - neon implementation only, not represented in Aston intermediate container  - to be resolved in Bentley

    int8_t *plut_armPhaseWiggling;         ///< Look-Up-Table used for "Wiggling Correction" ( d0:phaseWiggllingSize ) - neon implementation only, not represented in Aston intermediate container
    int8_t *plut_armAmplitudeWiggling;     ///< Look-Up-Table used for "Amplitude Wiggling Correction" ( d0:phaseAmplitudeSize ) - neon implementation only, not represented in Aston intermediate container

    uint16_t phaseWiggllingSize;        ///< Size of the Look-Up-Table used for "Adaptive Noise Filter". (PMD_PHASE_WIGGLING_LUT_SIZE)
    float *plut_phaseWiggling;          ///< Look-Up-Table used for "Wiggling Correction" ( d0:phaseWiggllingSize )
    uint16_t amplitudeWigglingSize;     ///< Size of the Look-Up-Table used for "Adaptive Noise Filter". (PMD_AMPLITUDE_WIGGLING_LUT_SIZE)
    float *plut_amplitudeWiggling;      ///< Look-Up-Table used for "Amplitude Wiggling Correction" ( d0:phaseAmplitudeSize )
} ;


/**
*   Necessary parameteres for auto exposure processing
*/
struct SpectreIntermediateAutoExposure
{
    uint8_t *pm_mask;       ///< Map information for auto exposure value calculation ( d0:ImageSize )
    uint32_t binSize;       ///< Size of value container
    float *pv_bin;          ///< Value container for auto exposure quantile evaluation ( d0:binSize )
    uint32_t quantilePos;   ///< Quantile limit position of the value container
} ;

/**
*   General processing Container comprises scalars, arrays and additional data container grouping subelements
*/
struct SpectreIntermediate
{
    uint16_t version;                   ///< Spectre processing version
    uint16_t type;                      ///< Intermediate data type, value corresponds to SpectreTypeIntermediate definition
    uint32_t imageSize;                 ///< Size of array containers

    uint8_t resetFlag;                  ///< reset flag inidicator, when true spectreAstonInit() is run

    float *pm_intensity;                ///< Intensity information of the superframe (numColumns*numRows)
    float *pm_relNoise;                 ///< Relative Noise information ( d0:imageSize )
    float *pm_phase;                    ///< Containe for processing the phase information ( d0:imageSize )
    float *pm_phaseNoise;               ///< Container for processing the phase noise information ( d0:imageSize )
    float *pm_distFilter;               ///< Container for processing the filter operations on distance ( d0:imageSize )
    float *pm_ampFlagLevel;             ///< Data container of the amplitude flag level ( d0:imageSize )
    float *pm_deltaDistance;            ///< Data container of the the delta distance information ( d0:imageSize )
    float *pm_floatTemp;                ///< Temporary container for intermediate float point value computation ( d0:imageSize )

    uint8_t sizeProbeData;              ///< total number of frame sets used for depth probing
    uint8_t *pv_posProbeData;           ///< Position of the depth probe frame set with respect to the input data [n:=sizeProbeData]
    struct SpectreIntermediateProbeData *pns_probeData;     ///< Subdata container for frequency relted data information [n:=sizeProbeData]
    struct SpectreIntermediateAutoExposure autoExposure;    ///< Subdata container for auto exposure calculation

    float anfGaussPrecision;            ///< Preset precision value for Look-Up-Table adaptation.
    uint16_t anfGaussSize;              ///< Size of the Look-Up-Table used for "Adaptive Noise Filter". (PMD_FILTER_ADAPTIVENOISE_LUTSIZE)
    float *plut_anfGauss;               ///< Look-Up-Table used for "Adaptive Noise Filter" approximating the related exponential function ( d0:anfGaussSize )

    uint32_t *pm_maskedFlagsTemplate;   ///< Contains a pm_flags template where the mask has been already applied
};


#ifdef __cplusplus
}
#endif
