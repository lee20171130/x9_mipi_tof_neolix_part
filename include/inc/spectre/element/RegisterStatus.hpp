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
        enum class RegisterStatus
        {
            SUCCESS                     = 0,    //!< Indicates that there isn't an error.
            REGISTER_ERRROR             = 1,    //!< Registration failed.
            OUT_OF_SCOPE                = 2,    //!< Register out of of scope.
            EMPTY_ELEMENT               = 3,    //!< Empty data element.
            ALREADY_REGISTERED          = 4,    //!< Data element is already registered.
            CONTAINER_MISSMATCH         = 5,    //!< Root and leaf container must be of equal type.
            ROOT_CONTAINER_UNREGISTERED = 6,    //!< Root container element is unregistered.
            ROOT_CONTAINER_MISSING      = 7,    //!< Root container element is missing.
            ROOT_ID_OUT_OF_BOUNDS       = 8,    //!< Root container id larger than regisytry size.
            DATA_MISSMATCH              = 9,    //!< Data and registry entry do not match.
            ASSIGN_ID_FAILED            = 10,   //!< ID assignment failed.
            INVALID_CONTAINER_TYPE      = 11,   //!< Container type is not valid for the operation
            DATA_ID_OUT_OF_BOUNDS       = 12    //!< Data id is out of registry range
        };
    }
}
