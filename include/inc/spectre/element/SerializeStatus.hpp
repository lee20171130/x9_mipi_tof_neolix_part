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
    namespace data
    {
        enum class SpectreStatus
        {
            SUCCESS							= 0,    //!< Indicates that there isn't an error
            DESERIALIZE_ERRROR				= 1,    //!< Deserialization failed
			FORWARD_TRANSFORM_ERROR			= 2,	//!< Alias forward transformation failed
			REVERSE_TRANSFORM_ERROR			= 3     //!< Alias reverse transformation failed
        };
    }
}