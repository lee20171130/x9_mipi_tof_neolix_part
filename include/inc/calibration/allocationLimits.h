/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __ALLOCATIONLIMITS_H__
#define __ALLOCATIONLIMITS_H__

// ********************************************************************************
// These values are sensible defaults for allocating the calibration structure
// Usually, it is not necessary to change them
// However, it is possible to create valid calibration files which exceed these
// limits. These files cannot be loaded, and the spectre_calibrationHandler
// should return SPECTRE_STATUS_MAXIMUM_SIZE_EXCEEDED

/// Maximum number of calibrated frequencies
#define MAX_NUM_FREQS 3
/// Maximum number of harmonic terms in the phase wiggling correction
#define MAX_NUM_PHASE_WIGGLES 5
/// Maximum number of harmonic terms in the amplitude wiggling correction
#define MAX_NUM_AMPLITUDE_WIGGLES 5
/// Maximum number of characters in the string (excluding terminating \0)
#define MAX_NUM_CHARS 32
// Be aware: Changing these is likely to affect the processing code, too.
/// Maximum number of lens parameter
#define MAX_NUM_LENS_PARAMETERS 9
/// Maximum number of temperature correction terms
#define MAX_NUM_TEMPERATURE_CORRECTION 4
/// Maximum number of noise parameters
#define MAX_NUM_NOISE_PARAMETERS 4
// ********************************************************************************

#endif /*__ALLOCATIONLIMITS_H__*/
