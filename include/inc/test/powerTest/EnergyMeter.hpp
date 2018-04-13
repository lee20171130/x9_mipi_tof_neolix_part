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


/** \brief Interface for EnergyMeters.
 *
 * EnergyMeter provides an interface for classes that implement
 * a measurement of power consumption.
 */
class EnergyMeter
{
public:
    EnergyMeter() = default;
    virtual ~EnergyMeter() = default;

    /** \brief loads the config of the EnergyMeter
     *
     * \param filename The name of the file where the config is stored
     *
     */
    virtual void loadConfig (const std::string &filename) = 0;

    /** \brief starts the measurement
     *
     * \param namePrefix A prefix to the name under which
     * the measurement will be stored. It will be extended by
     * the energy meter in a way that makes it unique to ensure
     * that each measurement will have a unique name.
     *
     * Starts a new measurement. If a measurement is currently
     * running it will be stoped before the new measurment is started.
     *
     */
    virtual void startMeasurement (const std::string &namePrefix) = 0;

    /** \brief stops the measurement
     *
     * Stops the currently running measurement. If no measurement is
     * ongoing, it will do nothing.
     *
     */
    virtual void stopMeasurement() = 0;

    /** \brief starts a sub measurement
     *
     * \param name A name for this submeasurement. The method will
     * not ensure that it is unique.
     *
     * Starts a new sub measurement. The method does not have to check if
     * an other sub measurement is underway.
     *
     */
    virtual void startSubMeasurement (const std::string &name) = 0;

    /** \brief continues the sub measurement
     *
     * Continues the last stopped sub measurement. If no previous sub+
     * measurement exists, it will do nothing.
     *
     */
    virtual void continueSubMeasurement() = 0;

    /** \brief stops the sub measurement
     *
     * Stops the currently running sub measurement. If no sub measurement is
     * ongoing, it will do nothing.
     *
     */
    virtual void stopSubMeasurement() = 0;

    /** \brief saves the measurement results as CSV file
     *
     */
    virtual std::string saveAsCsv() = 0;

    /** \brief return the full name of last started test
     *
     */
    virtual std::string getTestName() const = 0;

};
