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
#include "test/powerTest/EnergyMeter.hpp"
#include "system/ICommandExecutor.hpp"
#include <chrono>
#include <string>


/** \brief Implementation of EnergyMeter using Trepn.
 */
class TrepnEnergyMeter: public EnergyMeter
{
public:

    /** \brief Creates an EnergyMeter with default values.
     */
    TrepnEnergyMeter();

    /** \brief Creates an EnergyMeter with the given executor and wait period.
     *
     * \param executor CommandExecutor that will be used to execute the Intents send to Trepn
     * \param waitPeriod milliseconds to wait after sending the start command to trepn
     * before sending the next command. Default is 2 seconds.
     */
    TrepnEnergyMeter (ICommandExecutorShr executor, const std::chrono::milliseconds &waitPeriod);
    virtual ~TrepnEnergyMeter() = default;

    /** \brief loads the config into Trepn
     *
     * \param filename The name of the config file. The
     * config must be stored under /sdcard/trepn/saved_preferences.
     *
     */
    virtual void loadConfig (const std::string &filename) override;

    /** \brief starts the measurement
     *
     * \param namePrefix A prefix to the name under which
     * the measurement will be stored. It will be extended by
     * adding a time stamp to the prefix to ensure
     * that each measurement will have a unique name. The full
     * name will be <namePrefixe>_yymmddhhmmss.
     *
     * Starts a new measurement. If a measurement is currently
     * running it will be stoped before the new measurment is started.
     *
     */
    virtual void startMeasurement (const std::string &namePrefix) override;

    /** \brief stops the measurement
     *
     * Stops the currently running measurement. If no measurement is
     * ongoing, it will do nothing.
     *
     */
    virtual void stopMeasurement() override;

    /** \brief starts a sub measurement
     *
     * \param name A name for this sub measurement. The method will
     * not ensure that it is unique.
     *
     * Starts a new sub measurement. It will not call stopSubMeasurement()
     * before starting a new sub measurement.
     *
     */
    virtual void startSubMeasurement (const std::string &name) override;

    /** \brief continues the sub measurement
     *
     * Continues the last stopped sub measurement. If no previous sub+
     * measurement exists, it will do nothing.
     *
     */
    virtual void continueSubMeasurement() override;

    /** \brief stops the sub measurement
     *
     * Stops the currently running sub measurement. If no sub measurement is
     * ongoing, it will do nothing.
     *
     */
    virtual void stopSubMeasurement() override;

    /** \brief saves the measurement results as CSV file
     *
     * The csv file will be stored under /sdcard/trepn
     * and have the name of the measurement with ".csv"
     * added to the name. The full path be:
     * "/sdcard/trepn/<namePrefix>_<yymmddhhmmss>.csv"
     *
     */
    virtual std::string saveAsCsv() override;

    /** \brief return the full name of last started test
     *
     */
    virtual std::string getTestName() const override;

private:
    void startService();
    std::string createFilename (const std::string &namePrefix);
    std::string getTimestamp() const;

    ICommandExecutorShr m_exec; //! The CommandExecutor
    std::chrono::milliseconds m_waitPeriod{2000}; //! The wait time after sending start request to Trepn
    std::string m_filename; //! Full name of the measurement
    bool m_measRunning{false}; //! flag if a measurement is currently running
    uint32_t m_subMeasureCounter{}; //! counter of sub measurements
    std::string m_subMeasureName{}; //! name of current sub measurement
};
