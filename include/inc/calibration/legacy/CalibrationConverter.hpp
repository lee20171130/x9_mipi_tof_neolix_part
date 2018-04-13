/****************************************************************************\
 * Copyright (C) 2014 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#pragma once

#include <map>
#include <algorithm>
#include <vector>
#include <stdint.h>

#include <calibration/legacy/CalibrationManager.hpp>
#include <calibration/calibration.h>

struct SpectreCalibration;

namespace spectre
{
    namespace calibration
    {
        namespace legacy
        {

            /**
             * Calibration converter for legacy PMD/Tar calibration
             *
             */
            class CalibrationConverter
            {
            public:
                /**
                *   Constructor of the legacy converter
                */
                CalibrationConverter();


                spectre_CalibrationStatus setCalibrationData (const std::vector<uint8_t> &legacyCalibData);

                int getNumPixel (const std::vector<uint8_t> &legacyCalibData);

                /**
                 * Converts the legacy calibration, and writes it to the given calibration struct
                 *
                 * @param calibrationData calibration stream
                 * @param calibration destination structure
                 *
                 * @return status of operation
                 */
                spectre_CalibrationStatus convertCalibration (const std::vector<uint8_t> &data, struct SpectreCalibration *calibration);

            private:
                bool isEvalBoardRoi() const;

                /**
                 * Loads an calibration item to a given array
                 * If the calibration item contains more entries than size, a LeagcyCalibrationException with the error code
                 * SPECTRE_STATUS_MAXIMUM_SIZE_EXCEEDED is thrown
                 *
                 * @param itemName item name
                 * @param modFreq modulation frequency
                 * @param destination destination array
                 * @param size size of array
                 *
                 * @return number of copied entries
                 */
                template<typename T>
                size_t loadToArray (const std::string &itemName, uint32_t modFreq,
                                    T *destination, size_t size);

                /**
                 * Loads a char calibration item to a given array
                 * If the calibration item contains more characters than size, a LegacyCalibrationException with the error
                 * code SPECTRE_STATUS_MAXIMUM_SIZE_EXCEEDED is thrown
                 *
                 * This function terminates destionation always with '\0'. Therefore, destination needs to be allocated
                 * with at least sizeof(char) * (size + 1) bytes
                 *
                 * @param itemName item to retrieve
                 * @param destination destination buffer
                 * @param size size of maximum characters (excluding '\0')
                 */
                void loadToArray (const std::string &itemName, char *destination, size_t size);

                /**
                 * Loads an array, and cuts it to the subROI (removing pseudo-data line)
                 * This function loads the data into an array, and subsequently calls cutToSubROI. The cut
                 * data is copied to destination. Apart from that it behaves such as loadToArray
                 *
                 * @param itemName item to retrieve
                 * @param modFreq modulation frequency
                 * @param sensorROI sensorROI
                 * @param subROI subROI
                 * @param destination destination array
                 * @param size size of destination
                 *
                 * @return number of copied entries
                 */
                template<typename T>
                size_t loadToArrayAndCut (const std::string &itemName, uint32_t modFreq,
                                          const uint32_t *sensorROI, const uint32_t *subROI,
                                          T *destination, size_t size);


                /**
                * Function which transforms arrays according to the give sub region of interest.
                *
                * @param inputArray Reference to the internal array
                * @param sensorROI Array (x,y,width,height) which defines the ROI with which the calibration was recorded
                * @param subROI Array (x,y,width,height) which defines to which ROI the data should be transformed
                */
                template <typename T> void cutToSubROI (std::vector<T> &inputArray,
                                                        const uint32_t *sensorROI, const uint32_t *subROI);

                /**
                 * Reads the ROIs from the current set calibration file
                 *
                 * It fills the arrays m_legacySensorROI and m_legacySubROI, and throws an exception in case of an error.
                 *
                 */
                void readROIs();

                CalibrationManager m_calibrationManager;
                std::unique_ptr<uint32_t[]> m_legacySensorROI;
                std::unique_ptr<uint32_t[]> m_legacySubROI;
            };
        }
    }
}
