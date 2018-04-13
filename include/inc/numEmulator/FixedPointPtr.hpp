/****************************************************************************\
* Copyright (C) 2015 pmdtechnologies gmbh
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#ifndef FIXEDPTR_H
#define FIXEDPTR_H

#include <numEmulator/FixedPointAlias.hpp>
#include <vector>

namespace spectre
{
    namespace numEmulator
    {

        /** \brief class that emulates the behaviour of a C array of fixed point pointers
        *
        * This class implementation provides numerous pointer arithmetic that behaves as if
        * one was operating on a C array of fixed point pointers. Internally there are member values
        * to store the size of that array, the current index position and a FixedPointAlias vector which is
        * a mirror image of some built-in data type array of pointers which is passed over by the
        * constructor. This data type is determined by the third template parameter whereas the
        * first and second ones are refering to the appropiate fixed point template parameters that are
        * needed.
        */

        template<unsigned frac_bits, typename FpType, typename AType>
        class FixedPointPtr
        {

            template<unsigned fb, typename fty, typename aty>
            friend class FixedPointPtr; //different template parameters will define different classes

        public:

            /** \brief standard constructor
             */

            FixedPointPtr() : m_ptr (nullptr), m_size (0), m_idx (static_cast<int64_t> (0)), m_invalid (false),
                m_FPaliVec (m_size, FixedPointAlias<frac_bits, FpType, AType>())
            {
            }

            /** \brief copy constructor
             *
             * \param other FixedPointPtr value to be copied
             */

            template<unsigned other_fb, typename fty, typename aty>
            explicit FixedPointPtr (const FixedPointPtr<other_fb, fty, aty> &other) : m_ptr (other.m_ptr), m_size (other.m_size), m_idx (other.m_idx) //, m_FPaliVec (other.m_FPaliVec)
            {
                for (size_t i = 0; i < m_size; i++)
                {
                    m_FPaliVec.push_back (FixedPointAlias<frac_bits, FpType, AType> (other.m_FPaliVec[i]));
                }
            }

            /** \brief constructor to determine the array of pointers that is supposed to be mirrored
             *
             * \param ptr first pointer that belongs to an array of pointers
             * \param size size of the pointer array
             * \param idx current index position within the pointer array
             */

            explicit FixedPointPtr (AType *const ptr, const uint32_t size, uint32_t idx = 0) //throw exception if idx beneath 0 or larger than size?
                : m_ptr (ptr), m_size (size), m_idx (idx), m_invalid (false)
            {
                for (size_t i = 0; i < size; i++)
                {
                    m_FPaliVec.push_back (FixedPointAlias<frac_bits, FpType, AType> (ptr + i));
                }
            }

            /** \brief assignment operator for matching FixedPointPtr types
             *
             * \param fpPtr FixedPointPtr value to be assigned
             */

            FixedPointPtr<frac_bits, FpType, AType> &operator= (const FixedPointPtr<frac_bits, FpType, AType> &fpPtr)
            {
                if (this != &fpPtr)
                {
                    m_ptr = fpPtr.m_ptr;
                    m_size = fpPtr.m_size;
                    m_idx = fpPtr.m_idx;
                    m_FPaliVec.resize (m_size);
                    for (size_t i = 0; i < m_size; i++)
                    {
                        m_FPaliVec[i] = fpPtr.m_FPaliVec[i];
                    }
                }
                return *this;
            }

            /** \brief assignment operator for differing FixedPointPtr types
             *
             * NOTE: the third template parameter is not allowed to differ since the pointer sizes have to remain constant
             *
             * \param fpPtr FixedPointPtr value to be assigned
             */

            template<unsigned other_fb, typename fty, typename aty>
            FixedPointPtr &operator= (const FixedPointPtr<other_fb, fty, aty> &fpPtr)
            {
                m_ptr = fpPtr.m_ptr;
                m_size = fpPtr.m_size;
                m_idx = fpPtr.m_idx;
                m_FPaliVec.resize (m_size);
                for (size_t i = 0; i < m_size; i++)
                {
                    m_FPaliVec[i] = fpPtr.m_FPaliVec[i];
                }
                return *this;
            }

            /** \brief overloaded == operator for FixedPointPtr types
             *
             * \param x FixedPointPtr value to compare this with
             * \return returns true if the passed over FixedPointPtr value equals this one
             */

            template<unsigned fb, typename fty, typename aty>
            bool operator== (const FixedPointPtr<fb, fty, aty> &x) const
            {
                if (m_size != x.m_size)
                {
                    return false;
                }
                bool btmp = true;
                for (size_t i = 0; (i < m_size) && btmp; i++)
                {
                    btmp = btmp && (m_FPaliVec[i] == x.m_FPaliVec[i]);
                }
                return (m_ptr == x.m_ptr) && (m_idx == x.m_idx) && btmp;
            }

            /** \brief overloaded != operator for FixedPointPtr types
             *
             * \param x FixedPointPtr value to compare this with
             * \return returns true if the passed over FixedPointPtr value does not equal this one
             *
             * \sa operator== (const FixedPointPtr<fb, fty, aty> &x)
             */

            template<unsigned fb, typename fty, typename aty>
            bool operator!= (const FixedPointPtr<fb, fty, aty> &x) const
            {
                return ! (*this == x);
            }

            /** \brief overloaded [] operator for FixedPointPtr types
             *
             * \param i requested index position
             * \return returns FixedPointAlias value at requested index position of the mirrored pointer array
             */

            FixedPointAlias<frac_bits, FpType, AType> &operator[] (size_t i) const
            {
                return m_FPaliVec.at (i);
            }

            /** \brief overloaded * operator (dereference) for FixedPointPtr types
             *
             * \return FixedPointAlias value at current pointer array position
             */

            FixedPointAlias<frac_bits, FpType, AType> &operator* ()
            {
                if (m_invalid)
                {
                    throw "Pointer invalidated. Requested index is not valid.";
                }
                return m_FPaliVec.at (m_idx);
            }

            /** \brief overloaded + operator (pointer arithmetic) for FixedPointPtr types
             *
             * \param arg number of index positions to go forward within the pointer array
             */

            FixedPointPtr<frac_bits, FpType, AType> &operator+ (uint32_t arg)
            {
                m_idx += arg;
                return *this;
            }

            /** \brief overloaded prefix increment operator (pointer arithmetic) for FixedPointPtr types
             */

            void operator++ ()
            {
                m_idx++;
                m_invalid = m_invalid || m_idx >= m_size;
            }

            /** \brief overloaded prefix decrement operator (pointer arithmetic) for FixedPointPtr types
             */

            void operator-- ()
            {
                m_invalid = m_invalid || m_idx == 0;
                m_idx--;
            }

            /** \brief overloaded postix increment operator (pointer arithmetic) for FixedPointPtr types
             */

            void operator++ (int)
            {
                m_idx++;
                m_invalid = m_invalid || m_idx >= m_size;
            }

            /** \brief overloaded postfix decrement operator (pointer arithmetic) for FixedPointPtr types
             */

            void operator-- (int)
            {
                m_invalid = m_invalid || m_idx == 0;
                m_idx--;
            }

            /** \brief returns alias pointer of FixedPointAlias value that is currently beeing pointed at
             *
             * \return appropiate alias pointer the FixedPointPtr is currently pointing at
             */

            const AType *getPtr() const
            {
                return m_ptr + m_idx;
            }

        protected:
            using FPaliVec_t = std::vector<FixedPointAlias<frac_bits, FpType, AType>>;
            using VecSize_t = typename std::vector<FixedPointAlias<frac_bits, FpType, AType>>::size_type;

            AType *m_ptr;           ///>  first pointer that belongs to an array of pointers that is beeing emulated by the FixedPointPtr class
            VecSize_t m_size;       ///>  size of the pointer array
            VecSize_t m_idx;        ///>  current index position of the pointer array
            bool m_invalid;         ///>  auxiliary member to determine if the current index position is valid

            FPaliVec_t m_FPaliVec;  ///>  FixedPointAlias vector to emulate a C array of fixed point pointers
        };
    }
}

#endif
