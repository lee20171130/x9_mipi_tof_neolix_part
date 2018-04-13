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
#include <system/TestExecutionAlgorithm.hpp>

class TestExecutionAlgorithmFactory;
using TestExecutionAlgorithmFactoryPtr = std::shared_ptr<TestExecutionAlgorithmFactory>;

/** \brief Factory to create TestExecutionAlgorithms.
 *
 * The factory should be used by the test cases to generate a suitable TestExecutionAlgorithm.
 * The factory provides methods to set a algorithm that should be created. This enables the
 * selection of a TestExecutionAlgorithm during initialization of the test suite.
 * The class is a non copyable, non movable singleton.
 */
class TestExecutionAlgorithmFactory
{
public:
    TestExecutionAlgorithmFactory (const TestExecutionAlgorithmFactory &other) = delete; // non construction-copyable
    TestExecutionAlgorithmFactory &operator= (const TestExecutionAlgorithmFactory &) = delete; // non copyable
    TestExecutionAlgorithmFactory (const TestExecutionAlgorithmFactory &&other) = delete; // non construction-moveable
    TestExecutionAlgorithmFactory &operator= (const TestExecutionAlgorithmFactory &&) = delete; // non moveable

    /** \brief allows setting of the TestExecutionAlgorithm that should be created.
     *
     * \param algorithm to create. The given object is used as prototype.
     *
     */
    void setAlgorithmPrototype (TestExecutionAlgorithmPtr algorithm);

    /** \brief The method creates a new TestExecutionAlgorithm.
     *
     * \return TestExecutionAlgorithmPtr a unique_ptr to a TestExecutionAlgorithmPtr.
     *
     */
    TestExecutionAlgorithmPtr createTEA();

    static TestExecutionAlgorithmFactoryPtr getFactory();
    static void resetFactory();
    static TestExecutionAlgorithmPtr createTestAlgorithm();

private:
    /** \brief The constructor initializes the factory.
     *
     *  The constructor initializes the factory to create TestExecutionAlgorithmRuntime objects.
     *  This can be changed by calling setAlgorithmPrototype.
     */
    TestExecutionAlgorithmFactory();

    TestExecutionAlgorithmPtr m_Algorithm; //! the prototype object
    static TestExecutionAlgorithmFactoryPtr s_Factory; //! static variable that holds the singleton.
};
