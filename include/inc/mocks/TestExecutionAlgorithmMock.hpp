/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/
#include <gmock/gmock.h>
#include <system/TestExecutionAlgorithm.hpp>

#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif //__APPLE_

/** \brief Mock implementation of TestExecutionAlgorithm for testing purposes
 */
class TestExecutionAlgorithmMock: public TestExecutionAlgorithm {
    public:
    MOCK_METHOD0(run, void());
    MOCK_METHOD1(initFuncMock, void(size_t));
    MOCK_METHOD1(testFuncMock, void(size_t));
    MOCK_METHOD0(getTestTypeName, std::string());

    //this construct is necessary because currently gmock does not allow
    //non copyable objects as return value. To mock cloneEmpty use
    //EXPECT_CALL or ON_CALL with cloneEmptyRaw
    virtual TestExecutionAlgorithmPtr cloneEmpty() override {
        return TestExecutionAlgorithmPtr(cloneEmptyRaw());
    }
    MOCK_METHOD0(cloneEmptyRaw, TestExecutionAlgorithm*());

    void connectTestFuncToMock() {
        setTestFunction ([this] (size_t index) {this->testFuncMock(index);});
    }

    void connectInitFuncToMock() {
        setInitTestSeries ([this] (size_t index) {this->initFuncMock(index);});
    }

    void runTestFake() {
        for (size_t i = 0; i < initCalls; ++i) {
            initTestSeries(testRunsPerInitCall);
            for (size_t j=0; j<testRunsPerInitCall; ++j) {
                runTest(j);
            }
        }
    }

    void enableRunMethodFake () {
        ON_CALL(*this, run())
                .WillByDefault(::testing::Invoke(this, &TestExecutionAlgorithmMock::runTestFake));
    }

    size_t initCalls = 1;
    size_t testRunsPerInitCall = 1;
};

class DynFunctionMock {
    public:
    void connectMock(TestExecutionAlgorithm& algorithm) {
        algorithm.setTestFunction ([this] (size_t index) {this->testFuncMock(index);});
        algorithm.setInitTestSeries ([this] (size_t index) {this->initFuncMock(index);});
    }

    MOCK_METHOD1(initFuncMock, void(size_t));
    MOCK_METHOD1(testFuncMock, void(size_t));
};

#ifdef __APPLE__
#pragma clang diagnostic pop
#endif //__APPLE_