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
#include <processing/tools/astonTools.hpp>
#include <spectre/test/FixedPointContainerTestDataPath.hpp>

class FixedPointContainerTest : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
        // initializiation of floating point sructs
        m_status = spectreAstonInputLoad (&ps_input, m_workingDir + "/" + m_inputDir) && m_status;
        ASSERT_TRUE (m_status) << "Failure: could not load and/or initialize data of fixed point structs";
        m_status = spectreAstonParameterLoad (&ps_param, m_workingDir + "/" + m_paramDir) && m_status;
        ASSERT_TRUE (m_status) << "Failure: could not load and/or initialize data of fixed point structs";
        m_status = spectreAstonCalibrationLoad (&ps_calib, ps_input, m_workingDir + "/" + m_calibDir) && m_status;
        ASSERT_TRUE (m_status) << "Failure: could not load and/or initialize data of fixed point structs";
        m_status = spectreAstonOutputInit (&ps_output, ps_input, ps_calib) && m_status;
        ASSERT_TRUE (m_status) << "Failure: could not load and/or initialize data of fixed point structs";
        m_status = spectreAstonIntermediateInit (&ps_inter, ps_input) && m_status;
        ASSERT_TRUE (m_status) << "Failure: could not load and/or initialize data of fixed point structs";
    };

    virtual void TearDown()
    {
        spectreAstonIntermediateFree (ps_inter);
        m_status = spectreAstonCalibrationFree (ps_calib) && m_status;
        ASSERT_TRUE (m_status) << "Failure: could not free data of fixed point structs";
        m_status = spectreAstonParameterFree (ps_param) && m_status;
        ASSERT_TRUE (m_status) << "Failure: could not free data of fixed point structs";
        m_status = spectreAstonOutputFree (ps_output) && m_status;
        ASSERT_TRUE (m_status) << "Failure: could not free data of fixed point structs";
        m_status = spectreAstonInputFree (ps_input) && m_status;
        ASSERT_TRUE (m_status) << "Failure: could not free data of fixed point structs";
    };

    template<typename t>
    void cmpArray (const t *a, const t *b, uint32_t size)
    {
        for (uint32_t idx = 0; idx < size; ++idx, ++a, ++b)
        {
            EXPECT_EQ (*a, *b);
        }
    }

    bool getStatus()
    {
        return m_status;
    }

protected:
    bool m_status = true;

    const std::string m_workingDir = DATA_PATH;

    const std::string m_calibDir = "Process_Calib";
    const std::string m_paramDir = "Process_Param";
    const std::string m_inputDir = "Process_Input";

    // float structs
    SpectreCalibration *ps_calib;
    SpectreParameter *ps_param;
    SpectreInput *ps_input;
    SpectreOutput *ps_output;
    SpectreIntermediate *ps_inter;

};
