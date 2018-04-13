/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/
#ifndef __LEGACYCALIBRATIONDATANOTFOUNDEXCEPTION_HPP__
#define __LEGACYCALIBRATIONDATANOTFOUNDEXCEPTION_HPP__

#include <calibration/calibration.h>
#include <string>

namespace spectre
{
    namespace calibration
    {
        namespace legacy
        {

            class LegacyCalibrationDataNotFoundException
            {
            public:
                LegacyCalibrationDataNotFoundException (const std::string &reason)
                    : m_reason (reason)
                {}

                std::string getReason() const
                {
                    return m_reason;
                }

            private:
                std::string m_reason;
            };

        }
    }
}

#endif /*__LEGACYCALIBRATIONDATANOTFOUNDEXCEPTION_HPP__*/
