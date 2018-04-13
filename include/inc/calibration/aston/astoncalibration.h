/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __ASTONCALIBRATION_H__
#define __ASTONCALIBRATION_H__

#include <stdint.h>
#include <calibration/aston/common.h>

/// Contents of the container header
struct spectre_astonHeader
{
    /**
     * Version of the used container
     * 
     * Values:
     * 0: UNDEFINED
     * 1: ASTON
     */
    uint16_t version;
    /**
     * Submodule type of container
     *
     * Values for calibration:
     * 0: UNDEFINED
     * 1: ASTON_ONE_FREQ
     * 2: ASTON_TWO_FREQ
     */
    uint16_t type;
    /// Width of image
    uint32_t width;
    /// Height of image
    uint32_t height;
};


#endif /*__ASTONCALIBRATION_H__*/
