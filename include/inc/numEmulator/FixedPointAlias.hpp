/****************************************************************************\
* Copyright (C) 2015 pmdtechnologies gmbh
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#ifndef FIXEDALIAS_H
#define FIXEDALIAS_H

#include <numEmulator/FixedPoint.hpp>

namespace spectre
{
    namespace numEmulator
    {

        /** \brief class extension of FixedPoint that holds an alias pointer
        *
        * This class has a member of any built-in data type pointer (e.g. int*, float*, double*).
        * This type is determined by an additional template parameter called AType.
        * Its value is currently beeing updated by the updateAlias() member function each time
        * the fixed point value has changed.
        */

        template<unsigned frac_bits, typename FpType, typename AType>
        class FixedPointAlias : public  FixedPoint<frac_bits, FpType>
        {
            using FixedPoint<frac_bits, FpType>::operator=;

        public:

            template<unsigned fb, typename fty>
            friend class FixedPoint;

            template<unsigned fb, typename fty, typename aty>
            friend class FixedPointAlias;

            /** \brief default constructor
             */

            FixedPointAlias() : m_ptr (nullptr)
            {
            }

            /** \brief constructor to determine the alias pointer
             *
             * \param ptr pointer to be taken as an alias type for the appropiate fixed point value
             */

            explicit FixedPointAlias (AType *ptr) : m_ptr (ptr)
            {
                (ptr == nullptr ? FixedPoint<frac_bits, FpType>() : *this = *ptr);
            }

            /** \brief copy constructor
             *
             * this constructor calls the appropiate overloaded assignment operator
             *
             * \param x value of the same FixedPointAlias type
             * \sa operator=(const FixedPoint<frac_bits, FpType> &other), operator=(const FixedPointAlias &other), operator=(const FixedPoint<other_fb, fty> &other), operator=(const FixedPointAlias<other_fb, fty, aty> &other)
             */

            template<unsigned fb, typename fty, typename aty>
            explicit FixedPointAlias (const FixedPointAlias<fb, fty, aty> &x) : m_ptr (x.m_ptr)
            {
                *this = x;
            }

            /** \brief constructor to pass over a fixed point value
             *
             * this constructor is needed due to the internal fixed point arithmetic operators whose return types are fixed point values.
             *
             * \param x fixed point value to be assigned
             */

            template<unsigned fb, typename fty>
            explicit FixedPointAlias (const FixedPoint<fb, fty> &x) : FixedPoint<fb, fty> (x)
            {
            }

            /** \brief overloaded assignment operator for matching fixed point data types
             *
             * this function calls the assignment operator below
             *
             * \param other fixed point value to be assigned
             * \sa operator=(const FixedPointAlias &other)
             */

            FixedPoint<frac_bits, FpType>  &operator= (const FixedPoint<frac_bits, FpType> &other)
            {
                return operator= (FixedPointAlias (other));
            }

            /** \brief assignment operator for matching FixedPointAlias data types
             *
             * \param other FixedPointAlias data type value to be assigned
             */

            FixedPointAlias &operator= (const FixedPointAlias &other)
            {
                if (this != &other)
                {
                    this->m_value = other.m_value;
                    if (m_ptr == nullptr)
                    {
                        m_ptr = other.m_ptr;
                    }
                }
                if (m_ptr != nullptr)
                {
                    updateAlias();
                }
                return *this;
            }

            /** \brief overloaded assignment operator for differing FixedPoint data types
             *
             * this function calls the assignment operator below
             *
             * \param other fixed point value to be assigned
             * \sa operator=(const FixedPointAlias<other_fb, fty, aty> &other)
             */

            template<unsigned other_fb, typename fty, typename aty>
            FixedPoint<frac_bits, FpType> &operator= (const FixedPoint<other_fb, fty> &other)
            {
                return operator= (FixedPointAlias<other_fb, fty, aty> (other));
            }

            /** \brief assignment operator for differing FixedPointAlias data types
             *
             * \param other FixedPointAlias data type value to be assigned
             */

            template<unsigned other_fb, typename fty, typename aty>
            FixedPointAlias &operator= (const FixedPointAlias<other_fb, fty, aty> &other)
            {
                this->m_value = other_fb > frac_bits ? (other.m_value >> abst (other_fb - frac_bits)) : (other.m_value << abst (frac_bits - other_fb));
                if (m_ptr == nullptr)
                {
                    m_ptr = other.m_ptr;
                }
                if (m_ptr != nullptr)
                {
                    updateAlias();
                }
                return *this;
            }

            /** \brief updates the alias pointer regarding to the currently fixed point value
             */

            void updateAlias()
            {
                *m_ptr = (AType) FixedPoint<frac_bits, FpType>::template to<AType>();
            }

        protected:

            AType *m_ptr; ///< member value that stores the alias pointer
        };

    }
}

#endif
