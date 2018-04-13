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

#include <string>
#include <ostream>

namespace spectre
{
    enum class SpectreStatus
    {
        ///  Indicates that there isn't an error.
        SUCCESS = 0,
        ///  Undefined error.
        UNDEFINED_ERROR = 1,
        ///  Operation denied due to insufficient acces rights, please check the activation code.
        ACCESS_DENIED = 2,
        ///  Registration failed, probably because object with identical properties already exists.
        REGISTER_ERROR = 3,
        ///  Serialization failed.
        SERIALIZE_ERROR = 4,
        ///  This data type is currently not supported.
        UNSUPPORTED_DATATYPE = 5,
        ///  This version type is currently not supported.
        UNSUPPORTED_VERSION = 6,
        ///  Alias Transformation was unsuccessfull.
        TRANSFORMATION_ERROR = 7,
        ///  Elemenent data is out of predefined boundaries.
        VALUES_OUT_OF_BOUNDS = 8,
        ///  Reference value type is incompliant with defined value type.
        INCORRECT_SET_ELEMENT_VALUES = 9,
        ///  Container initialization failure.
        CONTAINER_INITIALIZE_FAILURE = 11,
        ///  Binarize memory allocation failure.
        BINARIZE_MEMORY_ALLOCATION_FAILED = 12,
        ///  No data exists for the requested path.
        CONTAINER_PATH_NOT_FOUND = 13,
        ///  Illegal arguments were passed to a function call.
        ILLEGAL_ARGUMENTS = 14,
        ///  Processing of Time-Of-Flight data failed.
        PROCESSING_FAILED = 16,
        /// Initialization of the processing failed
        PROCESSING_INIT_FAILED = 17,
        ///  Insuffiecient number of lensparmater defined.
        INSUFFICIENT_LENSPARAMETER = 19,
        ///  Lens modell is undefined
        INSUFFICIENT_LENSTYPE = 20,
        ///  The requested type is invalid for this operation (e.g., does not match with the stored type)
        INVALID_TYPE_REQUESTED = 21,
        ///  Within the data reference element the exterenal data handle oberver update failed
        DATAREFERENCE_OBSERVER_FAILED = 22,
        ///  Expected data, but the stream ended prematurly
        DESERIALIZE_UNEXPECTED_END = 23,
        ///  Spectre data query failed, due to multiple different reasons (wrong data type, wrong data path, etc.)
        DATA_QUERY_ERROR = 24,
        ///  Spectre processing adpater failed.
        ADAPTER_FAILED = 25,
        ///  An unknown file format was encountered
        DESERIALIZE_UNKNOWN_FILE = 26,
        ///  The passed buffer does not have the length saved inside the file
        DESERIALIZE_INVALID_LENGTH = 27,
        ///  The called operation is not supported
        OPERATION_NOT_SUPPORTED = 28,
        /// Assignment of processing calibrartion information unsuccessfull.
        ASSIGN_CALIBRAION_FAILED = 29,
        /// Conversion of calibration failed
        CALIBRATION_CONVERSION_FAILED = 30,
        /// Invalid frame set composition with respect to the current spectre imput type.
        INVALID_FRAME_SET_COMPOSITION = 31,
        /// The alias definition made, is not in compliance with the
        INVALID_ALIAS_DEFINITION = 32

    };

    inline bool isSuccess (SpectreStatus success)
    {
        return success == SpectreStatus::SUCCESS;
    }

    inline bool isFailure (SpectreStatus success)
    {
        return success != SpectreStatus::SUCCESS;
    }

    inline SpectreStatus operator&& (const SpectreStatus &lhs, const SpectreStatus &rhs)
    {
        if (lhs != SpectreStatus::SUCCESS)
        {
            return lhs;
        }
        if (rhs != SpectreStatus::SUCCESS)
        {
            return rhs;
        }
        return SpectreStatus::SUCCESS;
    }

    inline std::ostream &operator<< (std::ostream &os, const SpectreStatus &stat)
    {
        std::string s;
#define PROCESS_VAL(p) case(p): s = #p; break;
        switch (stat)
        {
                PROCESS_VAL (SpectreStatus::SUCCESS);
                PROCESS_VAL (SpectreStatus::UNDEFINED_ERROR);
                PROCESS_VAL (SpectreStatus::ACCESS_DENIED);
                PROCESS_VAL (SpectreStatus::REGISTER_ERROR);
                PROCESS_VAL (SpectreStatus::SERIALIZE_ERROR);
                PROCESS_VAL (SpectreStatus::UNSUPPORTED_DATATYPE);
                PROCESS_VAL (SpectreStatus::UNSUPPORTED_VERSION);
                PROCESS_VAL (SpectreStatus::TRANSFORMATION_ERROR);
                PROCESS_VAL (SpectreStatus::VALUES_OUT_OF_BOUNDS);
                PROCESS_VAL (SpectreStatus::INCORRECT_SET_ELEMENT_VALUES);
                PROCESS_VAL (SpectreStatus::CONTAINER_INITIALIZE_FAILURE);
                PROCESS_VAL (SpectreStatus::BINARIZE_MEMORY_ALLOCATION_FAILED);
                PROCESS_VAL (SpectreStatus::CONTAINER_PATH_NOT_FOUND);
                PROCESS_VAL (SpectreStatus::ILLEGAL_ARGUMENTS);
                PROCESS_VAL (SpectreStatus::PROCESSING_FAILED);
                PROCESS_VAL (SpectreStatus::PROCESSING_INIT_FAILED);
                PROCESS_VAL (SpectreStatus::INSUFFICIENT_LENSPARAMETER);
                PROCESS_VAL (SpectreStatus::INSUFFICIENT_LENSTYPE);
                PROCESS_VAL (SpectreStatus::INVALID_TYPE_REQUESTED);
                PROCESS_VAL (SpectreStatus::DATAREFERENCE_OBSERVER_FAILED);
                PROCESS_VAL (SpectreStatus::DESERIALIZE_UNEXPECTED_END);
                PROCESS_VAL (SpectreStatus::DATA_QUERY_ERROR);
                PROCESS_VAL (SpectreStatus::ADAPTER_FAILED);
                PROCESS_VAL (SpectreStatus::DESERIALIZE_UNKNOWN_FILE);
                PROCESS_VAL (SpectreStatus::DESERIALIZE_INVALID_LENGTH);
                PROCESS_VAL (SpectreStatus::OPERATION_NOT_SUPPORTED);
                PROCESS_VAL (SpectreStatus::ASSIGN_CALIBRAION_FAILED);
                PROCESS_VAL (SpectreStatus::CALIBRATION_CONVERSION_FAILED);
            default:
                s = "Status value not defined in SpectreStatus output operator!";
                break;
        }
#undef PROCESS_VAL

        return os << s;
    }
}
