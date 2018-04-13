/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#include <stdint.h>
#include <calibration/aston/common.h>

enum spectre_CalibrationStatus spectre_readAstonHeaderString (char *dest, long length, const uint8_t *stream, long *idx, long streamSize);

enum spectre_CalibrationStatus spectre_readAstonHeaderChar (char *c, const uint8_t *stream, long *idx, long streamSize);

enum spectre_CalibrationStatus spectre_readAstonHeaderUint16 (uint16_t *dest, const uint8_t *stream, long *idx, long streamSize);

enum spectre_CalibrationStatus spectre_readAstonHeaderUint32 (uint32_t *dest, const uint8_t *stream, long *idx, long streamSize);
