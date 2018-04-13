/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __LEGACYCALIBRATIONEXCEPTION_HPP__
#define __LEGACYCALIBRATIONEXCEPTION_HPP__

#include <calibration/calibration.h>
#include <string>

namespace spectre
{
    namespace calibration
    {
        namespace legacy
        {

            class LegacyCalibrationException
            {
            public:
                LegacyCalibrationException (spectre_CalibrationStatus status, const std::string &reason)
                    : m_status (status), m_reason (reason)
                {}

                std::string getReason() const
                {
                    return m_reason;
                }

                spectre_CalibrationStatus getErrorCode() const
                {
                    return m_status;
                }

            private:
                spectre_CalibrationStatus m_status;
                std::string m_reason;

            };

        }
    }
}
#endif /*__LEGACYCALIBRATIONEXCEPTION_HPP__*/
