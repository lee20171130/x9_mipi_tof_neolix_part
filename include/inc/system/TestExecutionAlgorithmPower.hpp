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
#include "system/TestExecutionAlgorithm.hpp"
#include "system/toolsTimer.hpp"
#include <chrono>
#include <ostream>

class EnergyMeter;


/** \brief Implementation of a TestExecutionAlgorithm to measure the power consumption of the tested method.
 */
class TestExecutionAlgorithmPower : public TestExecutionAlgorithm
{
public:
    /** \brief initializes the Algorithm with necessary parameter
     *
     * \param meter the EnergyMeter object to take the measurements.
     * \param initialExecutions the number of initial executions of the tested
     *    method to estimate the iterations necessary to run the method as long
     *    as  minMeasurmentPeriod
     * \param minMeasurementPeriod The minimum duration the tested method should run to ensure
     *    valid results.
     *
     * \attention The class holds only a reference to the EnergyMeter,
     *  so the caller has to assure that the EnergyMeter is valid during lifetime
     *  of the constructed object.
     *
     */
    TestExecutionAlgorithmPower (EnergyMeter &meter, std::ostream &iterationsLog, size_t initialExecutions, const std::chrono::milliseconds &minMeasurementPeriod);

    /** \brief This method measures the power consumption of the tested function.
     *
     * This method measures the power consumption of the tested function.
     * First it initializes and runs the tested method to run the as many iterations
     * as requested in the constructor by paramter initialExecutions. It measures the
     * duration of this run. The durations is used to estimate the number of
     * iterations necessary to run at least minMeasurementPeriod.
     *
     */
    virtual void run() override;

    /** \brief method clones the object without copying the functors
     *
     * \return TestExecutionAlgorithmPtr a clone of the object without the functors
     *
     */
    virtual TestExecutionAlgorithmPtr cloneEmpty() override;

    /** \brief method returns the type name "TestExecutionAlgorithmPower"
     *
     * \return the type name "TestExecutionAlgorithmPower" as string
     *
     */
    virtual std::string getTestTypeName() override;


    /** \brief method returns a reference to the used EnergyMeter
     *
     * \return reference to the used EnergyMeter
     *
     */
    EnergyMeter &getMeter() const;

    /** \brief method returns the number of iterations used
     * in the initial calibration loop
     *
     * \return number of calibration iterations
     *
     */
    size_t getInitialExecutions() const;

    /** \brief method returns the minimal duration of the
     * measurement loop in millisceonds
     *
     * \return minimal measuremnt duration in milliseconds
     *
     */
    std::chrono::milliseconds getMinMeasurementPeriod() const;

    /** \brief method returns the runtime of the initial
     * calibration loop, or zero if the calbration loop
     * has not yet run
     *
     * \return runtime of the initial calibration loop
     *
     */
    std::chrono::microseconds getCalibrationRuntime() const;

    /** \brief method return the number of iterations
     * that will be used to run the tested method during
     * the measurement loop. If the number of iterations
     * was not set by calling setIterations or not estimated
     * by the calibration loop beforehand, it will return 0.
     *
     * \return number of iterations of the measurment loop.
     *
     */
    size_t getIterations() const;

    /** \brief method sets the number of iterations used in the measurement loop.
     *
     * \param iterations number of measurment loop iterations
     *
     * The method sets the number of iterations that will be used to run the
     * measurment loop. It will also lock this number. This means: Each following
     * call to run will not estimate a new number of iterations, but will use the
     * number set by setIterations. To let the object estimate the iterations again,
     * call resetIterations.
     *
     */
    void setIterations (size_t iterations);

    /** \brief method resets iterations that were set by setIterations.
     *
     * The method resets the number of iterations to be estimated again in the
     * calibration loop after a call to setIterations();
     *
     */
    void resetIterations();

    /** \brief method sets the maximum number of iterations in one run of the measurement loop.
     *
     * \param maximum number of iterations in one run
     *
     * The method sets the maximum number of iterations in one run
     * of the measurement loop. If the calculated number of iterations
     * exceeds maxIterations, the test is initialized for maxIterations,
     * the measurement runs maxIterations, stops, is again initialialized
     * for up to maxIterations, the measurement continues and so on
     * until the calculated iterations are reached.
     *
     */
    void setMaxIterationsBlock (size_t maxIterations);

    /** \brief method returns the maximum number of iterations in one run of the measurement loop.
     *
     * The method returns the maximum number of iterations in one run
     * of the measurement loop.
     *
     */
    size_t getMaxIterationsBlock() const;

private:
    void calibrateRuntime();
    void calcIterations();
    void logIterations();
    void doTest();
    void runAtOnce();
    void runParted();
    std::chrono::microseconds runTestLoop (size_t iterations);

    EnergyMeter &m_meter; //! The EnergyMeter used to take the measurements
    std::ostream &m_iterLog; //!The stream where testnamed and iteraions are logged
    size_t m_initialExecutions; //! number of iterations in the calibration loop
    std::chrono::milliseconds m_minMeasurementPeriod; //! The minimal runtime of the measurement loop
    std::chrono::microseconds m_calibrationRuntime; //! runtime of the calibration loop
    size_t m_iterations{}; //! number of iterations in the measurement loop
    Timer m_timer{}; //! Timer used to measure the runtime of the calibration loop
    bool m_calcIterations = true; //! flag to memorize if the iterations should be estimated or not.
    size_t m_maxIterations = 5000;
};

