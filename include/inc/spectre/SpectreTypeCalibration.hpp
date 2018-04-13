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

    /*!
    *  This is an enum class, which defines all current pmd calibration data types currently supported by spectre.
    *
    *  The number of types may increase over time and the corresponding enumeration class will be expanded correspondingly.
    *   At the moment the calibration supports:
    *    - "Temperature" compensation
    *    - "Noise Parameter" definition
    *    - "Fixed Pattern Noise" (FPN) correction
    *    - "Fixed Pattern Phase Noise" correction
    *    - "Lensparameter" defintion comprising directions definition
    *    - "Amplitude Wiggling" correction
    *    - "Phase Wiggling" correction

    The Corresponding unit types are applied, which are related to physical and technical basic units

    | Calibration Type | Temperature | Noise Parameter | Lensparameter | FPN | FPPN | Amplitude Wiggling | Phase Wiggling |
    | :--------------: | :---------: | :-------------: | :-----------: | :-: | :--: | :----------------: | :------------: |
    | P4I1             | Yes         | Yes             | Yes           | Yes | Yes  | Yes                | Yes            |

    *
    */
    enum class SpectreTypeCalibration
    {
        UNDEFINED       = 0,        ///< Undefined calibration information type
        ASTON_ONE_FREQ  = 1,        ///< Calibration information for an image frame set of 4 Phasse + 1 Intensity Image
        ASTON_TWO_FREQ  = 2,        ///< Calibration information for an image frame set of 4 Phasse + 4 Phasse + 1 Intensity Image
        ASTON_THREE_FREQ = 3        ///< Calibration information for an image frame set of 4 Phasse + 4 Phasse + 1 Intensity Image (two different pairs)

    };

    inline std::ostream &operator<< (std::ostream &os, const SpectreTypeCalibration &type)
    {
        std::string s;
#define PROCESS_VAL(p) case(p): s = #p; break;
        switch (type)
        {
                PROCESS_VAL (SpectreTypeCalibration::ASTON_ONE_FREQ);
                PROCESS_VAL (SpectreTypeCalibration::ASTON_TWO_FREQ);
                PROCESS_VAL (SpectreTypeCalibration::UNDEFINED);
            default:
                s = "Status value not defined in SpectreTypeCalibration output operator!";
                break;
        }
#undef PROCESS_VAL

        return os << s;
    }

}
