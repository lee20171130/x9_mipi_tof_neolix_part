/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __DATACOMMON_H__
#define __DATACOMMON_H__

#include <stdint.h>
#include <calibration/aston/common.h>

typedef enum { UNDEFINED_FORMAT = 0, CHAR_FORMAT = 1, INT8_FORMAT = 2, INT16_FORMAT = 3, INT32_FORMAT = 4,
               INT64_FORMAT = 5, UINT8_FORMAT = 6, UINT16_FORMAT = 7, UINT32_FORMAT = 8, UINT64_FORMAT = 9,
               FLOAT_FORMAT = 10, DOUBLE_FORMAT = 11
             } spectre_astonFormat;


/** 
 * Checks if a Data<> corresponds to an expected format
 * 
 * @param exFormat expected format
 * @param stream binary stream
 * @param idx start index of Data<> (is incremented)
 * @param streamSize size of stream
 * 
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_checkAstonDataFormat (const spectre_astonFormat exFormat, const uint8_t *stream, long *idx, long streamSize);

#endif /*__DATACOMMON_H__*/
