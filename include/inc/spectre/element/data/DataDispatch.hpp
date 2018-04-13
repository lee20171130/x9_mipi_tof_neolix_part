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

#include <spectre/element/Element.hpp>
#include <spectre/element/data/Data.hpp>

namespace spectre
{
    namespace element
    {
        namespace data
        {

            /// Template which holds a list of types (typelist)
            template<typename HEAD, typename... Tail>
            struct tlist
            {
                typedef HEAD head;

                bool last() const
                {
                    return false;
                }

                tlist<Tail...> next() const
                {
                    return tlist<Tail...>();
                }
            };

            /// Typelist specialization for last entry
            template<typename HEAD>
            struct tlist<HEAD>
            {
                typedef HEAD head;

                bool last() const
                {
                    return true;
                }

                tlist<HEAD> next() const
                {
                    return *this;
                }
            };

            /// All valid instantiations of Element<T>
            using DataDataTypes = tlist<Data<char>, Data<int8_t>, Data<int>,
                                        Data<uint8_t>, Data<uint16_t>,
                                        Data<uint32_t>, Data<float> >;

            /**
             * Tries to dispatch a Data<T>* (passed as Data*) instance to an appropriate
             * instanantiation of the operator<T>(std::shared_ptr<Data<T> >) member of the
             * provided functor.
             *
             * The function tries a dynamic_cast for all entries in the passed typelist
             * types. If an appropriate type for dynamic_cast is found the recursion stops.
             *
             * @param handle handle to element
             * @param func functor which is called if the dispatch is successful
             * @param typelist list of possible types for T
             *
             * @return true if a successful dispatch was performed, false otherwise
             */
            template<typename FUNCTOR, typename TYPES = DataDataTypes>
            bool dispatchDataToFunctor (std::shared_ptr<spectre::element::Element> handle,
                                        const FUNCTOR &func,
                                        const TYPES &types = TYPES())
            {
                auto elementPtr =
                    std::dynamic_pointer_cast<spectre::element::data::Data<typename TYPES::head> > (handle);
                if (elementPtr)
                {
                    func (elementPtr);
                    return true;
                }

                return types.last() ? false : dispatchDataToFunctor (handle, func, types.next());
            }

            
            /**
             * Tries to dispatch a Data<T>* (passed as Data*) instance to an appropriate
             * instanantiation of the operator<T>(std::shared_ptr<Data<T> >) member of the
             * provided functor.
             *
             * The function tries a dynamic_cast for all entries in the passed typelist
             * types. If an appropriate type for dynamic_cast is found the recursion stops.
             *
             * @param handle handle to element
             * @param func functor which is called if the dispatch is successful
             * @param typelist list of possible types for T
             *
             * @return true if a successful dispatch was performed, false otherwise
             */
            template<typename FUNCTOR, typename TYPES = DataDataTypes>
            bool dispatchElementToFunctor (std::shared_ptr<spectre::element::Element> handle,
                                           FUNCTOR &func,
                                           const TYPES &types = TYPES())
            {
                auto elementPtr = std::dynamic_pointer_cast<typename TYPES::head> (handle);
                if (elementPtr)
                {
                    func (elementPtr);
                    return true;
                }

                return types.last() ? false : dispatchElementToFunctor (handle, func, types.next());
            }
        }  // element
    }  // data
}  // spectre
