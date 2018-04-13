/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __DATACOMPRESSED_H__
#define __DATACOMPRESSED_H__

#include <stdint.h>
#include <calibration/aston/common.h>
#include <calibration/aston/datadescriptor.h>

/** 
 * Reads a compressed array of uint32_t
 *
 * The array should be written by a registered Data<uint8_t> with a non-default DataDescriptor.
 * 
 * @param dest destination
 * @param size number of values
 * @param workingMem working memory (at least sizeof(uint32_t) * size)
 * @param desc data descriptor
 * @param stream binary stream
 * @param idx offset where Data<uint32_t> starts
 * @param streamSize size of stream
 * 
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readAstonCompressedDataUint32 (uint32_t *dest, uint32_t size, uint32_t *workingMem,
                                         const struct spectre_astonIntegralDescriptor *desc,
                                         const uint8_t *stream, long *idx, long streamSize);

/** 
 * Reads a compressed array of uint8_t
 *
 * The array should be written by a registered Data<uint8_t> with a non-default DataDescriptor.
 * 
 * @param dest destination
 * @param size number of values
 * @param workingMem working memory (at least sizeof(uint32_t) * size)
 * @param desc data descriptor
 * @param stream binary stream
 * @param idx offset where the Data<uint8_t> starts
 * @param streamSize size of stream
 * 
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readAstonCompressedDataUint8 (uint8_t *dest, uint32_t size, uint32_t *workingMem,
                                        const struct spectre_astonIntegralDescriptor *desc,
                                        const uint8_t *stream, long *idx, long streamSize);

enum spectre_CalibrationStatus spectre_readAstonCompressedDataFloat (float *dest, uint32_t size, uint32_t *workingMem,
                                        const struct spectre_astonFloatDescriptor *desc,
                                        const uint8_t *stream, long *idx, long streamSize);

#endif /*__DATACOMPRESSED_H__*/
