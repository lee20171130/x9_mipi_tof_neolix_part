/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __SPECTREPROCESSINGSTATUS_HPP__
#define __SPECTREPROCESSINGSTATUS_HPP__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/// Result of the called processing operation
enum SpectreProcessingStatus
{
    /// The processing run was successful
    SPECTRE_PROCESSING_SUCCESS,
    /// The passed calibration structure was invalid
    SPECTRE_PROCESSING_INVALID_CALIBRATION,
    /// Calibration probeData does not match with input
    SPECTRE_PROCESSING_PROBEDATA_MISMATCH
};

#ifdef __cplusplus
}
#endif

#endif /*__SPECTREPROCESSINGSTATUS_HPP__*/
