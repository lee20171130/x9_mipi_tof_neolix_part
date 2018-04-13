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

#include <spectre/element/data/TransformStatus.hpp>
#include <spectre/element/data/Data.hpp>

namespace spectre
{
    namespace element
    {
        namespace data
        {

            /**
            *  Transformation functor for conversion of various data elements
            */
            template < class srcType, class dstType>
            class TransformFunctor
            {

            public:
                /**
                *   Constructor of the base data element
                */
                TransformFunctor () {}

                /**
                *   Destructor of the base data element
                */
                virtual ~TransformFunctor() {}

                /**
                *  transformation of to data target element to destination element
                */
                virtual TransformStatus transform(srcType *source, dstType *destination) = 0;

            };


        }
    }
}
