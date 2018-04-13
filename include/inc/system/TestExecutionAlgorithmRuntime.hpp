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

#include <system/TestExecutionAlgorithm.hpp>
#include <system/toolsIO.hpp>

/** \brief Implementation of a TestExecutionAlgorithm to measure the runtime of the tested method.
 */
class TestExecutionAlgorithmRuntime : public TestExecutionAlgorithm
{
public:

    /** \brief initializes the Algorithm with necessary parameter
     *
     * \param repetitions the number of measurement repetitions.
     * \param runLength the number of test function call that are used to
     *        average the runtjme of the test function
     * \param timers The TimerMap where the results are stored.
     *
     * \attention The class holds only a reference to the TimerMap,
     *  so the caller has to assure that the TimerMap is valid during the lifetime
     *  of object.
     *
     */
    TestExecutionAlgorithmRuntime (size_t repetitions, size_t runLength, TimerMap &timers);

    /** \brief This method measures the runtime of the tested function.
     *
     * This method measures the runtime of the tested function. It uses 2
     * nested for loops. The outer loop repeats the initializing of the test and time
     * measurement. The inner loops repeats the actual test function.
     *
     */
    virtual void run() override;

    /** \brief method clones the object without copying the functors
     *
     * \return TestExecutionAlgorithmPtr a clone of the object without the functors
     *
     */
    virtual TestExecutionAlgorithmPtr cloneEmpty() override;

    /** \brief method returns the type name "TestExecutionAlgorithmRuntime"
     *
     * \return the type name "TestExecutionAlgorithmRuntime" as string
     *
     */
    virtual std::string getTestTypeName() override;

private:
    size_t mRepetitions; //! The number of measurement repetitions.
    size_t mRunLength; //! The number of testCalls per measurement
    TimerMap &mTimers; //! TimerMap to store the measurements.
};
