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
    enum class AdapterStatus
    {
        SUCCESS = 0,                        //!< Indicates that the adapatation between the ansi-c and c++ interface is successfull.
        ADAPTER_ERRROR = 1,                 //!< Adapation failed for unspecific reasons.
        UNSUPPORTED_DATATYPE = 2,           //!< This data type is currently not supported.
        CONTAINER_DATA_QUERRY_FAILED = 3,   //!< Data querry from container failed.
        INVALID_ELEMENT_VALUE = 4,          //!< A element dat value is incompliant with expectation.
        INVALID_CONTAINER_TYPE = 5,         //!< Invalid container type definition.
        INVALID_CONTAINER_VARIANT = 6       //!< Invalid container varianrt definition.
    };
}
