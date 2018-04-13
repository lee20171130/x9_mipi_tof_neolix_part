/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <stdint.h>
#include <calibration/aston/common.h>
#include <calibration/aston/astoncalibration.h>
#include <calibration/calibration.h>

/**
 * Reads the header of the root container
 *
 * @param header header structure to be filled
 * @param magicWord expected magic word (PMDSCL for calibration)
 * @param stream array containing the binary data
 * @param idx current reading index (updated by this method)
 * @param streamSize size of stream
 *
 * @return status code of the operation
 */
enum spectre_CalibrationStatus spectre_readAstonRootContainerHeader (struct spectre_astonHeader *header, const char *magicWord, const uint8_t *stream, long *idx, long streamSize);

/**
 * Reads the header of the container
 *
 * @param stream array containing the binary data
 * @param idx current reading index (updated by this method)
 * @param streamSize size of stream
 *
 * @return status code of the operation
 */
enum spectre_CalibrationStatus spectre_readAstonContainerHeader(const uint8_t *stream, long *idx, long streamSize);


/**
 * Reads the footer of the container
 *
 * @param stream array containing the binary data
 * @param idx current reading index (updated by this method)
 * @param streamSize size of stream
 *
 * @return status code of the operation
 */
enum spectre_CalibrationStatus spectre_readAstonContainerFooter(const uint8_t *stream, long *idx, long streamSize);


#endif /*__CONTAINER_H__*/
