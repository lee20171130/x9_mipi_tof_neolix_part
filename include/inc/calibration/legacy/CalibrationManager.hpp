/****************************************************************************\
 * Copyright (C) 2013 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/
#pragma once

#include <vector>
#include <string>
#include <cstdint>

#include <calibration/legacy/TarCalibrationContainer.hpp>

namespace spectre
{
    namespace calibration
    {
        namespace legacy
        {
            /**
             * Class which does all the calibration data handling.
             */
            class CalibrationManager
            {
            public:
                CalibrationManager();

                /**
                 * \brief Sets the calibration data.
                 *
                 * Sets the calibration data from a given array.
                 * @param calibrationData Array with calibration data
                 */
                void setCalibrationData (const std::vector<uint8_t> &calibrationData);

                /**
                 * Returns a const reference to the currently stored calibration information.
                 */
                const std::vector<uint8_t> &getCalibrationData() const;

                /**
                 * Checks if calibration data is set.
                 * @return True, if calibration data is set.
                 */
                bool hasCalibrationData() const;

                /**
                 * \brief Retrieves the number and value of the supported calibration data.
                 *
                 * @param frequencies Frequencies supported by the current calibration.
                 */
                void getSupportedFrequencies (std::vector<uint32_t> &frequencies);

                /**
                 * \brief Retrieves data from the calibration.
                 *
                 * Retrieves data from the calibration file. The vector is automatically resized
                 * to match the retrieved data. If the data query is not successful a "CalibrationDataNotFound"
                 * exception is thrown and the vector is returned empty.
                 * @param ident Name of data
                 * @param[out] data Output array
                 */
                void getData (const std::string &ident, std::vector<uint8_t> &data) const;

                /**
                 * \brief Retrieves data from calibration based on the modulation frequency.
                 *
                 * Retrieves a set of data from the calibration file based on the given modulation
                 * frequency. The vector is automatically resized to match the retrieved data.
                 * @param item Name of the data
                 * @param frequency Modulation frequency
                 * @param[out] data Output array
                 */
                void getDataForFrequency (const std::string &item, const uint32_t frequency, std::vector<uint8_t> &data) const;

                /**
                 * \brief Retrieves the directions from calibration.
                 *
                 * Retrieves the directions from the calibration file and converts them to float.
                 * @param[out] output Output array
                 */
                void getDirectionsAsFloat (std::vector<float> &output);

            private:
                /**
                 * \brief Get the name of frequency dependent data.
                 *
                 * Returns the name of the item for the specified modulation frequency.
                 * @param item Name of the data
                 * @param frequency Modulation frequency
                 * @return Data name
                 */
                std::string getCalibrationItemName (const std::string &item, const uint32_t frequency) const;

                std::string m_calibrationItemNameDelimiter;
                std::string m_calibrationItemNameExtensionFrq;

                TarCalibrationContainer m_calibrationContainer;

                // Calibration manager will keep a copy of the loaded calibration data
                std::vector<uint8_t> m_calibrationData;
            };

        }
    }
}
