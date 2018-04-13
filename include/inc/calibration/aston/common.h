/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stdio.h>
#include <calibration/aston/astoncalibration.h>
#include <calibration/calibration.h>

#ifndef DEBUG_TRACE
#define DEBUG_TRACE 0
#endif

#define SPECTRE_NULLPTR (void*)0;
#define SPECTRE_TRACE(x) do { if (DEBUG_TRACE) spectre_printfAston x; } while (0);
#define SPECTRE_TRACE_UINT32S(MSG, ARRAY, SIZE) do { if (DEBUG_TRACE) spectre_printfAstonUint32s(MSG, ARRAY, SIZE); } while(0);
#define SPECTRE_TRACE_UINT8S(MSG, ARRAY, SIZE) do { if (DEBUG_TRACE) spectre_printfAstonUint8s(MSG, ARRAY, SIZE); } while(0);
#define SPECTRE_TRACE_FLOATS(MSG, ARRAY, SIZE) do { if (DEBUG_TRACE) spectre_printfAstonFloats(MSG, ARRAY, SIZE); } while(0);
/// Number of array values to print during trace
#define SPECTRE_TRACE_MAX_VALUES 32

/**
 * Prints a message to the stderr
 *
 * @param fmt format string
 */
void spectre_printfAston (const char *fmt, ...);

/**
 * Prints an array to stderr
 *
 * @param str message to sprint before
 * @param array array
 * @param size size of array
 */
void spectre_printfAstonUint32s (const char *str, const uint32_t *array, long size);

/**
 * Prints an array to stderr
 *
 * @param str message to print before array
 * @param array array
 * @param size size of array
 */
void spectre_printfAstonUint8s (const char *str, const uint8_t *array, long size);

/**
 * Prints an array to stderr
 *
 * @param str message to print before array
 * @param array array
 * @param size size of array
 */
void spectre_printfAstonFloats (const char *str, const float *array, long size);

#endif /*__COMMON_H__*/
