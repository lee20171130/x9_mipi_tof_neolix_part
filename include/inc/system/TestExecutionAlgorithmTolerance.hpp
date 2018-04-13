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

/** \brief Implementation of a TestExecutionAlgorithm that just runs the tested method once.
 */
class TestExecutionAlgorithmTolerance : public TestExecutionAlgorithm
{
public:
    /** \brief A default constructor.
     *
     *
     */
    TestExecutionAlgorithmTolerance() = default;

    /** \brief The method runs initTestSeries() and runTest() just once
     *
     */
    virtual void run() override;

    /** \brief method clones the object without copying the functors
     *
     * \return TestExecutionAlgorithmPtr a clone of the object without the functors
     *
     */
    virtual TestExecutionAlgorithmPtr cloneEmpty() override;

    /** \brief method returns the type name "TestExecutionAlgorithmTolerance"
     *
     * \return the type name "TestExecutionAlgorithmTolerance" as string
     *
     */
    virtual std::string getTestTypeName() override;
};
