/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __PROCESSINGINIT_HPP__
#define __PROCESSINGINIT_HPP__

#include <processing/SpectreProcessingStatus.hpp>

#ifdef __cplusplus
extern "C" {
#endif

struct SpectreIntermediate;
struct SpectreInput;

/**
 * Initializes a new SpectreIntermediate structure
 *
 * The created SpectreIntermediate structure newly matches the type of the passed SpectreInput structure
 * w.r.t. to image dimensions, probe frequencies, and so on.
 *
 *
 * @param ps_input input structure
 * @param ps_inter intermediate structure
 *
 * @return status of operation
 */
SpectreProcessingStatus spectreIntermediateInit (const struct SpectreInput *ps_input, struct SpectreIntermediate **ps_inter);

/**
 * Sets the probe data posititions depending on the imager modes
 *
 * Based on the input's imager modes the position of probe data in the intermediate structure (pv_posProbeData)
 * is adjusted to match the actual positions in the phase measurements
 *
 * @param ps_input input structure
 * @param ps_inter intermediate to adjust
 *
 */
void spectreSetProPos (const struct SpectreInput *ps_input,
                       struct SpectreIntermediate *ps_inter);
/**
 * Frees the SpectreIntermediate structure
 *
 * @param inter pointer to intermediate structure
 */
void spectreIntermediateFree (struct SpectreIntermediate *inter);

/**
 * Adapts the given calibration structure, so that it matches with the given input
 * That is, it swaps the modulation frequency depenendent data in the calibration, so that they
 * match the modulation order specified by the input structure.
 *
 * @param input input structure
 * @param calib calibration
 *
 * @return status code of operation
 */
SpectreProcessingStatus adaptCalibration (const struct SpectreInput *input, struct SpectreCalibration *calib);
#ifdef __cplusplus
}
#endif

#endif /*__PROCESSINGINIT_HPP__*/
