/****************************************************************************\
* Copyright (C) 2015 pmdtechnologies gmbh
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#ifndef FIXED_H
#define FIXED_H

#include <stdint.h>
#include <math.h>
#include <type_traits>
#include <typeinfo>
#include <limits>
#include <iostream>

namespace spectre
{
    namespace numEmulator
    {

        template<bool isUnsigned>
        struct abs_t
        {
            template<typename Type>
            static Type val (Type number)
            {
                return number;
            }
        };

        template<>
        struct abs_t<false>
        {
            template<typename Type>
            static Type val (Type number)
            {
                return static_cast<Type> (llabs (number));
            }
        };

        template<typename Type>
        Type abst (Type number)
        {
            return abs_t<std::is_unsigned<Type>::value >::val (number);
        }

        /** \brief class implementaion of the fixed point data type
         *
         * The fixed point class is implemented as a template class. The mantissa of the respective floating
         * point value is saved in a member variable of a specific integer data type which is determined
         * by the second template parameter. The first template parameter determines the number of bits to
         * be reserved for the fractional part. Integer overflow is handled using saturation by default.
         * This can be switched off though for evaluation purposes, in that case an exception will be thrown.
         */

        template<unsigned frac_bits, typename FpType>
        class FixedPoint
        {

        public:

            template<unsigned fb, typename nT>
            friend class FixedPoint; //different values of frac_bits will define different classes

            /** \brief default constructor
             */

            FixedPoint()
            {
                m_value = 0;
            }

            /** \brief copy constructor for saturation flag
             *
             * \param m_sFlag saturation flag setting
             */

            explicit FixedPoint (bool m_sFlag)
            {
                m_value = 0;
                m_saturationSet = m_sFlag;
            }

            /** \brief copy constructor for different data types
             *
             * this function calls the appropiate overloaded assignment operator to prevent redundance
             *
             * \param x value that can be of type double, float, specific int or any fixed point data type
             *
             * \sa operator=(const int x), operator=(const unsigned int x), operator=(const float x), operator=(const double x), operator=(const FixedPoint &other), operator=(const FixedPoint<other_fb, nT> &other)
             */

            template<typename stdT>
            explicit FixedPoint (stdT x)
            {
                *this = x;
            }

            /** \brief copy constructor for different data types and saturation flag setting
             *
             * \param x value that can be of type double, float, specific int or any fixed point data type
             * \param m_sFlag saturaion flag setting
             */
            template<typename stdT>
            FixedPoint (stdT x, bool m_sFlag)
            {
                m_saturationSet = m_sFlag;
                *this = x;
            }

            /** \brief destructor
             */

            virtual ~FixedPoint()
            {
            }

            /** \brief compares two fixed point values and returns true if the represented values are identical
             *
             * \param x fixed point value to compare this class object with
             * \return true if represented values are identical independent of the number of fractional bits and/or the basic integer datatype
             */

            static void setSaturationFlag (bool bs)
            {
                m_saturationSet = bs;
            }

            static bool getSaturationFlag()
            {
                return m_saturationSet;
            }

            bool isSaturated()
            {
                if (!m_saturationSet)
                {
                    m_isSaturated = false;
                }
                return m_isSaturated;
            }

            template<unsigned fb, typename nT>
            bool operator== (const FixedPoint<fb, nT> &x) const
            {
                typename std::conditional<sizeof (FpType) >= sizeof (nT), FpType, nT >::type refValue = m_value;
                typename std::conditional<sizeof (FpType) >= sizeof (nT), FpType, nT >::type refValue_x = x.m_value;

                return fb >= frac_bits ? (refValue << abst (fb - frac_bits)) == refValue_x : refValue == (refValue_x << abst (frac_bits - fb));
            }

            /** \brief compares two fixed point values in regard to their represented sizes
             *
             * \param x fixed point value to compare this class object with
             * \return returns true if the passed over fixed point value is smaller than this one. A fixed point value is considered smaller then the other
             * one if its represented rational number is smaller then the other's.
             */

            template<unsigned fb, typename nT>
            bool operator> (const FixedPoint<fb, nT> &x) const
            {
                typename std::conditional<sizeof (FpType) >= sizeof (nT), FpType, nT >::type refValue = m_value;
                typename std::conditional<sizeof (FpType) >= sizeof (nT), FpType, nT >::type refValue_x = x.m_value;

                return fb >= frac_bits ? (refValue << abst (fb - frac_bits)) > refValue_x : refValue > (refValue_x << abst (frac_bits - fb));
            }

            /** \brief adds the passed over fixed point value
             *
             * \param rfp fixed point value that shall be added
             * \return returns updated fixed point object after adding the passed over fixed point value
             */

            template<unsigned rfb, typename nT>
            FixedPoint &operator+= (const FixedPoint<rfb, nT> &rfp)
            {
                if (IntOverflow ( (m_value >> frac_bits) + (rfp.m_value >> rfb), (frac_bits >= rfb ? rfb : frac_bits)))
                {
                    saturateOrThrow ( (m_value >> frac_bits) + (rfp.m_value >> rfb));
                }
                else
                {
                    m_value = m_value + (frac_bits >= rfb ? (rfp.m_value << abst (frac_bits - rfb)) : (rfp.m_value >> abst (rfb - frac_bits)));
                }
                return *this;
            }

            /** \brief subtracts the passed over fixed point value
             *
             * \param rfp fixed point value that shall be subtracted
             * \return returns updated fixed point object after subtracting the passed over fixed point value
             */

            template<unsigned rfb, typename nT>
            FixedPoint &operator-= (const FixedPoint<rfb, nT> &rfp)
            {
                if (IntOverflow (abst ( (m_value >> frac_bits) - (rfp.m_value >> rfb)), (frac_bits >= rfb ? rfb : frac_bits)))
                {
                    saturateOrThrow ( (m_value >> frac_bits) - (rfp.m_value >> rfb));
                }
                else
                {
                    m_value = m_value - (frac_bits >= rfb ? (rfp.m_value << abst (frac_bits - rfb)) : (rfp.m_value >> abst (rfb - frac_bits)));
                }
                return *this;
            }

            /** \brief multiplies this by the passed over fixed point value
             *
             * \param rfp fixed point value that shall be multiplied by this fixed point value
             * \return returns updated fixed point object after multiplying it by the passed over fixed point value
             */

            template<unsigned rfb, typename nT>
            FixedPoint &operator*= (const FixedPoint<rfb, nT> &rfp)
            {
                if (IntOverflow (abst ( (m_value >> frac_bits) * (rfp.m_value >> rfb)), (frac_bits + rfb + 1)))
                {
                    saturateOrThrow ( (m_value >> frac_bits) * (rfp.m_value >> rfb));
                }
                else
                {
                    m_value = ( ( (m_value * rfp.m_value) >> (rfb - 1)) + 1) >> 1; //to avoid loss in accuracy the last bit is rounded
                }
                return *this;
            }

            /** \brief divides this by the passed over fixed point value
             *
             * \param rfp fixed point value this fixed point value shall be divided by
             * \return returns updated fixed point object after dividing it by the passed over fixed point value
             */

            template<unsigned rfb, typename nT>
            FixedPoint &operator/= (const FixedPoint<rfb, nT> &rfp)
            {
                if (rfp.m_value == 0) //division by zero
                {
                    saturateOrThrow (rfp.m_value);
                    return *this;
                }

                if (IntOverflow (abst (m_value), rfb))
                {
                    saturateOrThrow ( (m_value >> frac_bits) / (rfp.m_value >> rfb));
                }
                else
                {
                    m_value = (m_value << rfb) / rfp.m_value;
                }
                return *this;
            }

            /** \brief converts this fixed point value to any suitable standard built-in datatype (e.g. float, double, int)
             *
             * \return returns the converted fixed point value.
             */

            template<typename RetType>
            RetType to()
            {
                if (typeid (RetType) == typeid (float) || (typeid (RetType) == typeid (double)))
                {
                    RetType res = static_cast<RetType> (m_value);
                    return static_cast<RetType> (res / (one << frac_bits));
                }
                else
                {
                    int64_t res = static_cast<int64_t> (m_value >> frac_bits);
                    if ( (res < static_cast<int64_t> (std::numeric_limits<RetType>::min())) || (res > static_cast<int64_t> (std::numeric_limits<RetType>::max())))
                    {
                        if (m_saturationSet)
                        {
                            res = static_cast<int64_t> (res < std::numeric_limits<RetType>::min() ? std::numeric_limits<RetType>::min() : std::numeric_limits<RetType>::max());
                            m_isSaturated = true;
                        }
                        else
                        {
                            throw "information loss during convertion";
                        }
                    }
                    return static_cast<RetType> (res);
                }
            }

            /** \brief assignment operator for matching fixed point data types
             *
             * \param other value of the same fixed point data type
             */

            virtual FixedPoint &operator= (const FixedPoint &other)
            {
                m_value = other.m_value;
                m_isSaturated = other.m_isSaturated;
                return *this;
            }

            /** \brief assignment operator for differing fixed point data types
             *
             * \param other value of any fixed point data type
             */

            template<unsigned other_fb, typename nT>
            FixedPoint &operator= (const FixedPoint<other_fb, nT> &other)
            {
                //using abst in if-statements, otherwise this will issue a warning:
                m_value = other_fb > frac_bits ? (other.m_value >> abst (other_fb - frac_bits)) : (other.m_value << abst (frac_bits - other_fb));
                m_isSaturated = other.m_isSaturated;
                return *this;
            }

            /** \brief assignment operator for integer data type
             *
             * \param x value of integer data type
             */

            virtual FixedPoint &operator= (const int x) //TODO: remove redundancy!
            {
                if ( (std::is_unsigned<FpType>::value) && (x < 0))
                {
                    saturateOrThrow (x);
                    return *this;
                }

                if (IntOverflow (x, frac_bits))
                {
                    saturateOrThrow (x);
                }
                else
                {
                    m_value = static_cast<FpType> (x * (one << frac_bits));
                }
                return *this;
            }

            /** \brief assignment operator for unsigned integer data type
            *
            * \param x value of unsigned integer data type
            */

            FixedPoint &operator= (const unsigned int x)
            {
                if (IntOverflow (x, frac_bits))
                {
                    saturateOrThrow (x);
                }
                else
                {
                    m_value = static_cast<FpType> (x * (one << frac_bits));
                }
                return *this;
            }

            /** \brief assignment operator for int64 data type
            *
            * \param x value of int64 data type
            */

            FixedPoint &operator= (const int64_t x)
            {
                if ( (std::is_unsigned<FpType>::value) && (x < 0))
                {
                    saturateOrThrow (x);
                    return *this;
                }

                if (IntOverflow (x, frac_bits))
                {
                    saturateOrThrow (x);
                }
                else
                {
                    m_value = static_cast<FpType> (x * (one << frac_bits));
                }
                return *this;
            }

            /** \brief assignment operator for uint64 data type
            *
            * \param x value of uint64 data type
            */

            FixedPoint &operator= (const uint64_t x)
            {
                if (IntOverflow (x, frac_bits))
                {
                    saturateOrThrow (x);
                }
                else
                {
                    m_value = static_cast<FpType> (x * (one << frac_bits));
                }
                return *this;
            }

            /** \brief assignment operator for float data type
            *
            * \param x value of float data type
            */

            FixedPoint &operator= (const float x)
            {
                if ( (std::is_unsigned<FpType>::value) && (x < 0))
                {
                    saturateOrThrow (x);
                    return *this;
                }

                if (IntOverflow (x, frac_bits))
                {
                    saturateOrThrow (x);
                }
                else
                {
                    m_value = (x >= 0 ? static_cast<FpType> (x * (one << frac_bits) + .5) : static_cast<FpType> (x * (one << frac_bits) - .5)); //rounding
                }
                return *this;
            }

            /** \brief assignment operator for double data type
            *
            * \param x value of double data type
            */

            FixedPoint &operator= (const double x)
            {
                if ( (std::is_unsigned<FpType>::value) && (x < 0))
                {
                    saturateOrThrow (x);
                    return *this;
                }

                if (IntOverflow (x, frac_bits))
                {
                    saturateOrThrow (x);
                }
                else
                {
                    m_value = (x >= 0 ? static_cast<FpType> (x * (one << frac_bits) + .5) : static_cast<FpType> (x * (one << frac_bits) - .5)); //rounding
                }
                return *this;
            }

        protected:

            /** \brief either saturates m_value or throws an exception
             *
             * \param x value that would be assigned
             * \sa m_value
             */

            template<typename nT>
            void saturateOrThrow (const nT x)
            {
                if (m_saturationSet)
                {
                    m_value = (x >= 0 ? std::numeric_limits<FpType>::max() : std::numeric_limits<FpType>::min());
                    m_isSaturated = true;
                }
                else
                {
                    throw "number of decimal places is bigger then the number of all bits";
                }
            }

            /** \brief verifies if the passed over value would cause an integer overflow if it was assigned
             *
             * \param x value that would be assigned
             * \param available_fb number of available bits for the fractional part
             * \return returns true if the passed over value would cause an integer overflow when assigned
             */

            template<typename nT>
            bool IntOverflow (const nT x, unsigned available_fb)
            {
                return (sizeof (FpType) * 8 < available_fb + sign_bit) ||
                       ( (x < 0) && (x < - (one << (sizeof (FpType) * 8 - available_fb - sign_bit)))) ||
                       ( (x >= 0) && (x >= (one << (sizeof (FpType) * 8 - available_fb - sign_bit))));
            }

        protected:
            static const long long one = 1;                                         ///< auxiliary member to prevent integer overflow within operations of the kind: 1 << frac_bits
            static const bool sign_bit = (std::is_signed<FpType>::value ? 1 : 0);   ///< sign bit that either exists or not dependening on wether FpType is a signed or unsigned datatype

            FpType m_value;                                                         ///< mantissa of the respective floating point value that is represented in fixed point
            static_assert (frac_bits <= (sizeof (FpType) * 8 - sign_bit), "number of decimal places is bigger then the number of all bits"); //checking during compile time


            static bool m_saturationSet;                                            ///< saturation flag
            bool m_isSaturated = false;                                             ///< states if the fixed point value has been saturated
        };

        template<unsigned frac_bits, typename FpType>
        bool FixedPoint<frac_bits, FpType>::m_saturationSet = true;

        /** \brief compares two fixed point values in regard to their represented sizes and returns the maximum of them
         *
         * \param lfp left handed fixed point value to be compared with the right hand side
         * \param rfp right handed fixed point value to be compared with the left hand side
         * \return returns the maximum of the two passed over fixed point values. A fixed point value is considered larger then the other
         * one if its represented rational number is larger then the other's.
         */

        template<unsigned fb, typename nT>
        FixedPoint<fb, nT> fp_max (const FixedPoint<fb, nT> lfp,
                                   const FixedPoint<fb, nT> rfp)
        {
            return (lfp > rfp ? lfp : rfp);
        }

        /** \brief overloaded != operator for fixed point values
         *
         * \param lfp left handed fixed point value of the != operator
         * \param rfp right handed fixed point value of the != operator
         * \return returns true if the two passed over fixed point values have non-identical representations as a rational number
         * independent of the number of fractional bits and/or the basic integer datatype
         *
         * \sa operator== (const FixedPoint<fb, nT> &x)
         */

        template<unsigned lfb, unsigned rfb, typename lnT, typename rnT>
        bool operator!= (const FixedPoint<lfb, lnT> &lfp, const FixedPoint<rfb, rnT> &rfp)
        {
            return ! (lfp == rfp);
        }

        /** \brief overloaded + operator for fixed point values
         *
         * \param lfp left handed fixed point value of the + operator
         * \param rfp right handed fixed point value of the + operator
         * \return returns the resulting fixed point value that represents the sum of the two passed over fixed point values.
         * The number of fractional bits in the resulting value is the minimum of the fractional bits of the passed over values
         * (if one would take the maximum of them two the loss in precision would lead to a higher error than the actual loss in accuracy)
         */

        template<unsigned lfb, unsigned rfb, typename nT>
        typename std::conditional < lfb <= rfb, FixedPoint<lfb, nT>, FixedPoint<rfb, nT> >::type operator+ (
            const FixedPoint<lfb, nT> lfp,
            const FixedPoint<rfb, nT> &rfp)
        {
            auto res = typename std::conditional < lfb <= rfb, FixedPoint<lfb, nT>, FixedPoint<rfb, nT> >::type (lfp);
            res.setSaturationFlag (lfb <= rfb ? lfp.getSaturationFlag() : rfp.getSaturationFlag());
            res += rfp;
            return res;
        }

        /** \brief overloaded - operator for fixed point values
         *
         * \param lfp left handed fixed point value of the - operator
         * \param rfp right handed fixed point value of the - operator
         * \return returns the resulting fixed point value that represents the subtraction of the two passed over fixed point values.
         * The number of fractional bits in the resulting value is the minimum of the fractional bits of the passed over values
         * (if one would take the maximum of them two the loss in precision would lead to a higher error than the actual loss in accuracy)
         */

        template<unsigned lfb, unsigned rfb, typename nT>
        typename std::conditional < lfb <= rfb, FixedPoint<lfb, nT>, FixedPoint<rfb, nT> >::type operator- (
            const FixedPoint<lfb, nT> lfp,
            const FixedPoint<rfb, nT> &rfp)
        {
            auto res = typename std::conditional < lfb <= rfb, FixedPoint<lfb, nT>, FixedPoint<rfb, nT> >::type (lfp);
            res.setSaturationFlag (lfb <= rfb ? lfp.getSaturationFlag() : rfp.getSaturationFlag());
            res -= rfp;
            return res;
        }

        /** \brief overloaded * operator for fixed point values
         *
         * Since the overflow query needs both original fractional bits of the parameters, this function is splitted in two using enable_if.
         *
         * \param lfp left handed fixed point value of the * operator
         * \param rfp right handed fixed point value of the * operator
         * \return returns the resulting fixed point value that represents the product of the two passed over fixed point values.
         * The number of fractional bits in the resulting value is the maximum of the fractional bits of the parameters
         * (more accurate, no loss in precision).
         */

        template<unsigned lfb, unsigned rfb, typename nT>
        typename std::enable_if < (lfb >= rfb), FixedPoint<lfb, nT >>::type  operator* (
                    const FixedPoint<lfb, nT> lfp,
                    const FixedPoint<rfb, nT> &rfp)
        {
            auto res = FixedPoint<lfb, nT> (lfp);
            res.setSaturationFlag (lfp.getSaturationFlag());
            res *= rfp;
            return res;
        }

        template<unsigned lfb, unsigned rfb, typename nT>
        typename std::enable_if < (rfb > lfb), FixedPoint<rfb, nT >>::type  operator* (
                    const FixedPoint<lfb, nT> &lfp,
                    const FixedPoint<rfb, nT> rfp)
        {
            auto res = FixedPoint<rfb, nT> (rfp);
            res.setSaturationFlag (rfp.getSaturationFlag());
            res *= lfp;
            return res;
        }

        /** \brief overloaded / operator for fixed point values
         *
         * \param lfp left handed fixed point value of the / operator
         * \param rfp right handed fixed point value of the / operator
         * \return returns the resulting fixed point value that represents the quotient of the two passed over fixed point values.
         * The number of fractional bits in the resulting value is the maximum of the fractional bits of the passed over values
         * (more accurate, no loss in precision).
         */

        template<unsigned lfb, unsigned rfb, typename nT>
        typename std::conditional< lfb >= rfb, FixedPoint<lfb, nT>, FixedPoint<rfb, nT> >::type  operator/ (
            const FixedPoint<lfb, nT> lfp,
            const FixedPoint<rfb, nT> &rfp)
        {
            auto res = typename std::conditional < lfb >= rfb, FixedPoint<lfb, nT>, FixedPoint<rfb, nT> >::type (lfp);
            res.setSaturationFlag (lfb >= rfb ? lfp.getSaturationFlag() : rfp.getSaturationFlag());
            res /= rfp;
            return res;
        }
    }
}

#endif
