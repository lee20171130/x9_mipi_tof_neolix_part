/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __DATADESCRIPTOR_H__
#define __DATADESCRIPTOR_H__

#include <stdint.h>
#include <calibration/aston/common.h>

/**
 * Information for decompressing Data<T>
 * 
 * Correspondens to DataDescript<T> where std::integral<T> is true 
 */
struct spectre_astonIntegralDescriptor
{
    /// Scaling factor used
    uint32_t scale;
    /// Precision (maximum error in fixed-point representation)
    uint32_t precision;
    /// Bits required for representation
    uint32_t bitsize;
    /// Minimum value
    int32_t min;
    /// Maximum value
    int32_t max;
};


/**
 * Information for decompressing Data<float>
 * 
 * Correspondens to DataDescript<float>
 */
struct spectre_astonFloatDescriptor
{
    /// Scaling factor used
    float scale;
    /// Precision (maximum error in fixed-point representation)
    float precision;
    /// Bits required for representation
    uint32_t bitsize;
    /// Minimum value
    float min;
    /// Maximum value
    float max;
};


/** 
 * Fills a spectre_astonIntegralDescriptor structure for an integral type
 *
 * 
 * @param min minimum value
 * @param max maximum value
 * @param precision precision
 * @param desc descriptor to fill
 * 
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_fillAstonIntegralDescriptor (uint32_t min, uint32_t max, uint32_t precision,
                                       struct spectre_astonIntegralDescriptor *desc);

/** 
 * Fills a spectre_astonFloatDescriptor structure from the stream
 * 
 * The stream data is expected to be the in format written by a DataVarDef<float> node
 * 
 * @param desc descriptor to fill
 * @param stream binary stream
 * @param idx index where DataVarDef<float> starts (updated during operation)
 * @param streamSize size of stream
 * 
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_fillAstonFloatDescriptorFromStream (struct spectre_astonFloatDescriptor *desc, const uint8_t* stream,
                                              long *idx, long streamSize);

#endif /*__DATADESCRIPTOR_H__*/


