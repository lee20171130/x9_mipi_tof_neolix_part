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

namespace spectre
{
    namespace element
    {
        namespace data
        {
            enum class TransformStatus
            {
                SUCCESS = 0,                    //!< Indicates that there isn't an error
                ERROR = 1,                      //!< Transformation unsuccessfull, please check data consistency
                INVALID_TARGET = 2,             //!< Invalid source or destination target
                INVALID_ROI = 3,                //!< Invalud sensor ROI
                INVALID_LENSPARAMETER = 4       //!< Invalud sensor ROI
            };
        }
    }
}
