/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#pragma once


#ifdef __cplusplus
extern "C" {
#endif


#include <arm_neon.h>
#include <stdint.h>
#include <math.h>

#include "processing/common/commonMethods.hpp"

/**
* Neon intrinsic implementatin of the pmd_expf method.
* Calculates an approximation for the exponential function
* which be accurate to approx. 1.2*10e-4.
*
* The approximation is only valid for -85 <= x <= 0.
*
* @param nv_x argument vector
* @param nv_res result vector (exp of nv_x)
*
*/
#define PMD_ARM_EXPF(nv_x, nv_res) {                                                                           \
        const float32x4_t nv_pmd_expf_cnst0 = vdupq_n_f32 ((float) PMD_LD_E);                                   \
        const float32x4_t nv_pmd_expf_cnst1 = vdupq_n_f32 (-127.0f);                                            \
        const float32x4_t nv_pmd_expf_cnst2 = vdupq_n_f32 (1.0f);                                               \
        const float32x4_t nv_pmd_expf_cnst3 = vdupq_n_f32 (8388608.0f);                                         \
        const float32x4_t nv_pmd_expf_cnst4 = vdupq_n_f32 (127.00247609615325927734375f);                       \
        const float32x4_t nv_pmd_expf_cnst5 = vdupq_n_f32 (-0.3489532172679901123046875f);                      \
        const float32x4_t nv_pmd_expf_cnst6 = vdupq_n_f32 (0.344001114368438720703125f);                        \
        float32x4_t nv_xMax = vmaxq_f32( vmulq_f32(nv_x, nv_pmd_expf_cnst0), nv_pmd_expf_cnst1);                \
        int32x4_t nv_truncX = vcvtq_s32_f32(nv_xMax);                                                           \
        float32x4_t nv_err = vaddq_f32(vsubq_f32(nv_xMax, vcvtq_f32_s32(nv_truncX)), nv_pmd_expf_cnst2);        \
        nv_res = vreinterpretq_f32_u32(                                                                         \
                 vcvtq_u32_f32(vmulq_f32(nv_pmd_expf_cnst3,                                                     \
                 vaddq_f32(nv_xMax,vaddq_f32 (nv_pmd_expf_cnst4,                                                \
                 vmulq_f32(nv_err,vaddq_f32(nv_pmd_expf_cnst5,                                                  \
                 vmulq_f32(nv_err,nv_pmd_expf_cnst6))))))));                                                    \
}

/**
* Calculates the square root by using the approximate reciprocal square root, performing two
* additional Newton raphson steps to increase accuracy and multiplying with the argument to obtain
* the square root.
*
* @param d_nv argument vector
* @param res_nv result vector (square root of d_nv)
*/
#define PMD_ARM_SQRT(d_nv, res_nv) {                \
        float32x4_t xn_nv, xnsqr_nv, xn1_nv, tmp_nv; \
        xn_nv = vrsqrteq_f32 (d_nv);                 \
        xnsqr_nv = vmulq_f32 (xn_nv, xn_nv);         \
        tmp_nv = vrsqrtsq_f32 (d_nv, xnsqr_nv);      \
        xn1_nv = vmulq_f32 (tmp_nv, xn_nv);          \
        xnsqr_nv = vmulq_f32 (xn1_nv, xn1_nv);       \
        tmp_nv = vrsqrtsq_f32 (d_nv, xnsqr_nv);      \
        xn_nv = vmulq_f32 (xn1_nv, tmp_nv);          \
        res_nv = vmulq_f32 (xn_nv, d_nv);            \
    }


/**
* Calculates the reciprocal by using the approximate reciprocal and performing two additional
* Newton raphson steps to increase accuracy
*
* @param d_nv argument vector
* @param rec_nv result vector (reciprocal of d_nv)
*/

#define PMD_ARM_REC(d_nv, rec_nv) {                \
        float32x4_t xn_nv, tmp_nv, xn1_nv;          \
        xn_nv = vrecpeq_f32 (d_nv);                 \
        tmp_nv = vrecpsq_f32 (d_nv, xn_nv);         \
        xn1_nv = vmulq_f32 (xn_nv, tmp_nv);         \
        tmp_nv = vrecpsq_f32 (d_nv, xn1_nv);        \
        rec_nv = vmulq_f32 (tmp_nv, xn1_nv);        \
    }

#ifdef __aarch64__
/**
 * Rounds a value to the nearest integral value away from zero
 *
 * @param n_rnd vector to round
 * @param n_res result vector
 *
 */
#define PMD_ARM_ROUND(n_rnd, n_res) n_res = vrndaq_f32(n_rnd);
#else
/**
* Rounds a value to the nearest integral value away from zero
*
*
* @param n_rnd vector to round
* @param n_res result vector
*/
#define PMD_ARM_ROUND(n_rnd, n_res) {                                  \
        float32x4_t zero = vdupq_n_f32(0.0f);                           \
        float32x4_t half = vdupq_n_f32(0.5f);                           \
        float32x4_t negHalf = vdupq_n_f32(-0.5f);                       \
        uint32x4_t select = vcgeq_f32(n_rnd, zero);                     \
        n_res = vbslq_f32(select, half, negHalf);                       \
        n_res = vaddq_f32(n_rnd, n_res);                                \
        n_res = vcvtq_f32_s32(vcvtq_s32_f32(n_res));                    \
}
#endif

#ifdef __aarch64__
/**
 * Calculates floorf(x) for a given integer
 * Implemented as round towards infinity
 *
 * @param n_floor value to floor
 * @param n_result floored value
 */
#define PMD_ARM_FLOOR(n_floor, n_result) {     \
        n_result = vrndmq_f32 (n_floor);        \
    }
#else
/**
 * Calculates floorf(x) for a given integer
 *
 * Undefined if the result is not representable by a 32-Bit signed
 * integer.
 *
 * @param n_floor value to floor
 * @param n_result floored value
 */
#define PMD_ARM_FLOOR(n_floor, n_result) {                             \
        int32x4_t n_iFloored = vcvtq_s32_f32(n_floor);                  \
        float32x4_t n_fFloored = vcvtq_f32_s32(n_iFloored);             \
        float32x4_t n_zero = vdupq_n_f32(0.0f);                         \
        float32x4_t n_one = vdupq_n_f32(1.0f);                          \
        uint32x4_t n_selectNeg = vcgeq_f32(n_floor, n_zero);            \
        uint32x4_t n_selectInt = vceqq_f32(n_fFloored, n_floor);        \
        uint32x4_t n_select = vorrq_u32(n_selectNeg, n_selectInt);      \
        n_result = vbslq_f32 (n_select, n_fFloored, vsubq_f32(n_fFloored, n_one)); \
    }
#endif

/**
 * Calculates pmd_mod(x,y) on NEON
 * This version assumes that y is a scalar value
 *
 * @param n_x_ vector of xs
 * @param s_y_ scalar value of y
 * @param s_y_inv_ scalar value of 1.0f/y
 * @param n_res_ result vector
 */
#define PMD_ARM_N_MOD(n_x_, s_y_, s_y_inv_, n_res_) {                  \
        float32x4_t n_tmp1_ = vmulq_n_f32 (n_x_, s_y_inv_);             \
        float32x4_t n_floored_;                                         \
        PMD_ARM_FLOOR (n_tmp1_, n_floored_);                           \
        float32x4_t n_tmp2_ = vdupq_n_f32 (s_y_);                       \
        n_res_ = vfmsq_f32 (n_x_, n_floored_, n_tmp2_);                 \
    }

/**
* Finds a scaling factor for a floating-point array which
* can be used to represent the values as integers with
* the specified numbers of bits.
*
* @param lut array of floating-point numbers
* @param size size of lut
* @param bits number of bits for presentation
* @param sign indicates whether a sign is required
* @param scalingFactor scaling factor (always a power of two)
*/
inline void findScale (const float *lut, const uint32_t size,
                       const uint8_t bits, bool *sign,
                       uint32_t *scalingFactor)
{
    float a = FLT_MAX;
    float b = -a;
    uint8_t rbits;

    for (uint32_t i = 0; i < size; ++i)
    {
        a = pmd_min (lut[i], a);
        b = pmd_max (lut[i], b);
    }
    a = nextafterf (a, -INFINITY);
    b = nextafterf (b, INFINITY);

    *sign = a < 0.0;
    rbits = *sign ? (uint8_t) (bits - 1) : bits;

    a = pmd_max (fabsf (a), fabsf (b));
    uint32_t max = (1 << rbits) - 1;
    uint32_t factor = (uint32_t) ( (float) max / a);

    factor--;
    factor |= factor >> 1;
    factor |= factor >> 2;
    factor |= factor >> 4;
    factor |= factor >> 8;
    factor |= factor >> 16;
    factor = factor - (factor >> 1);

    *scalingFactor = factor;
}

/**
* Scales a float value on the range [0, 255] of to int8_t
*
* @param x value to scale
* @param scale scaling factor
*
* @return scaled value
*/
inline int8_t scaleTo8 (const float x, const uint32_t *scale)
{
    return (int8_t) (x * (float) * scale);
}

/**
* Unscales a scaled value from uint8_t to float
*
* @param x scaled value
* @param scale scale used
*
* @return unscaled value
*/
inline float scaleFrom8 (int8_t x, const uint32_t *scale)
{
    return ( (float) x) / ( (float) * scale);
}

/**
* Rescales a scaled uint8_t to uint16_t on a new scale.
* This function assumes that oldScale <= newScale and both are powers of two
*
* @param x scaled value
* @param oldScale uint8_t scale used
* @param newScale scale for uint16_t
*
* @return scaled value
*/
inline int16_t rescaleFrom8ToU16 (const int8_t x, const uint32_t *oldScale,
                                  const uint32_t *newScale)
{

    return (int16_t) (x * (*newScale / *oldScale));
}

/**
* Scales a float value to uint16_t
*
* @param x value to scale
* @param scale scale to use
*
* @return scaled value
*/
inline int16_t scaleTo16 (const float x, const uint32_t *scale)
{
    return (int16_t) (x * (float) * scale);
}

/**
* Unscales a uint16_t value
*
* @param x scaled value
* @param scale scale used
*
* @return unscaled value
*/
inline float scaleFrom16 (uint16_t x, const uint32_t *scale)
{
    return ( (float) x) / (float) * scale;
}


#ifdef __cplusplus
}
#endif
