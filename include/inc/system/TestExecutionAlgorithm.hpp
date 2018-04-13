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

#include <memory>
#include <functional>
#include <string>
#include "system/definitions.hpp"

class TestExecutionAlgorithm;
using TestExecutionAlgorithmPtr = std::unique_ptr<TestExecutionAlgorithm>;


/** \brief base class for TestExecutionAlgorithms
 *
 * This class is the base of each TestExecutionAlgorithm and provides the
 * common functions of TestExecutionAlgorithms.
 * The idea behind TestExecutionAlgorithm is to provide a common interface
 * for the kind of tests that we do on the processing algorithms.
 * An specific implementation of an TestExecutionAlgorithm must call initTestSeries(noOfTests)
 * to set up everything for noOfTest consecutive calls of runTest(). Afterwards an implementation
 * must call runTest() maximal noOfTests times. This call sequence can be arbitrarily repeated.
 *
 * To use a TestExecutionAlgorithm in a test case get a TestExecutionAlgorithm instance
 * via TestExecutionAlgorithmFabric. if necessary assign an appropriate init function via
 * setInitTestSeries(). Assign the actual call that should be tested via setTestFunction().
 * run the actual test by calling run(). Afterwards you can check your input and output values
 * as necessary.
 */
class TestExecutionAlgorithm
{
public:
    /** \brief default constructor
     *
     *
     */
    TestExecutionAlgorithm() = default;

    /** \brief default destructor
     *
     *
     */
    virtual ~TestExecutionAlgorithm() = default;

    using initSeriesType = std::function<void (size_t noOfTests) >; //! type of the init function
    using testFunctionType = std::function<void (size_t testIndex) >; //! type of the test function

    /** \brief starts the actual execution
     *
     * \return virtual void
     *
     */
    virtual void run() = 0;

    /** \brief method clones the object without copying the functors
     *
     * \return TestExecutionAlgorithmPtr a clone of the object without the functors
     *
     */
    virtual TestExecutionAlgorithmPtr cloneEmpty() = 0;


    /** \brief method returns the type name of the underlying TestExecutionAlgorithm implementation
     *
     * \return the type name of the underlying TestExecutionAlgorithm implementation as string
     *
     */
    virtual std::string getTestTypeName() = 0;

    /** \brief set the function for initializing the test data
     *
     * \param initTestSeries the functor of the actual init function
     *
     */
    void setInitTestSeries (initSeriesType initTestSeries);

    /** \brief method to get the init functions of the algorithm
     *
     * \return initSeriesType A functor to the actual init function.
     * If no function is set, a nullptr functor is returned.
     *
     */
    initSeriesType getInitTestSeries() const;


    /** \brief set the function that runs the actual call to test
     *
     * \param testFunction the functor of the actual call to test
     *
     */
    void setTestFunction (testFunctionType testFunction);

    /** \brief method to get the test functor of the algorithm
     *
     * \return testFunctionType A functor to the actual test function.
     * If no function is set, a nullptr functor is returned.
     *
     */
    testFunctionType getTestFunction() const;

    /** \brief sets the name of the current test
     *
     * \param name The name of the test.
     *
     * Sets the name of the Test that should be executed. This can be used by the
     * TestExecutionAlgorithm in output or messages.
     */
    void setTestName (const std::string &name);

    /** \brief returns the name of test
     *
     * \return std::string the name of the test as set by setTestName().
     * Returns an empty string if no name is set.
     *
     */
    std::string getTestName() const;

protected:
    /** \brief method encapsulates the call of initTestSeriesFunc
     *
     * \param size_t noOfTests no of consecutive runTest() calls
     *
     */
    inline void initTestSeries (size_t noOfTests)
    {
        if (m_initTestSeriesFunc)
        {
            m_initTestSeriesFunc (noOfTests);
        }
    }

    /** method encapsulates the call of testFunction
     *
     * \param size_t testIndex index of of nth consecutive call.
     *
     */
    inline void runTest (size_t testIndex)
    {
        m_testFunction (testIndex);
    }

private:
    initSeriesType m_initTestSeriesFunc; //! functor of the initTestSeries function.
    testFunctionType m_testFunction; //! functor of the actual test function.
    std::string m_TestName = ""; //! the name of the test.
};

struct TestNameEmpty: public std::exception
{
    virtual const char* what() const NOEXCEPT override
    {
        return "Test name is empty.";
    }
};
