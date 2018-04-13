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

#define _CRT_SECURE_NO_WARNINGS
#include <gmock/gmock.h>

#include <processing/processingInternal.hpp>

#include <system/TestExecutionAlgorithm.hpp>

#include <spectre/access/intern/AccessCode.hpp>
#include <spectre/SpectreFactory.hpp>
#include <spectre/adapter/aston/AstonAdapter.hpp>
#include <spectre/element/builder/InputBuilder.hpp>
#include <spectre/element/data/DataReference.hpp>
#include <spectre/element/container/Output.hpp>
#include <spectre/element/container/Calibration.hpp>
#include <spectre/element/builder/CalibrationBuilder.hpp>
#include <spectre/element/builder/InputBuilder.hpp>
#include <spectre/element/builder/OutputBuilder.hpp>
#include <spectre/element/builder/ParameterBuilder.hpp>

#include <spectre/element/builder/aston/AstonParameterBuilder.hpp>
#include <spectre/element/builder/aston/AstonOutputBuilder.hpp>
#include <spectre/Spectre.hpp>

class Test_pmdTest : public testing::Test
{
protected:

    std::string m_activationCode = accessCodeInternal;

    SpectreIntermediate *ps_inter;
    SpectreCalibration *ps_calib;
    SpectreParameter *ps_param;
    SpectreInput *ps_input;
    SpectreOutput *ps_output;

    TestExecutionAlgorithmPtr algo;

    spectre::SpectreFactory m_fac {};
    SpectreIO *m_io;
    spectre::element::container::Input m_input {};
    spectre::element::container::Parameter m_param {};
    spectre::element::container::Calibration m_procCalib {};
    spectre::element::container::Calibration m_sysCalib {};
    spectre::element::container::Output m_output {};

    std::unique_ptr<spectre::Spectre> m_processing;

    const std::string m_globalDir;
    const std::string m_calibDir;
    const std::string m_paramDir;
    const std::string m_inputDir;

protected:

    Test_pmdTest();

    virtual ~Test_pmdTest();

    virtual void SetUp();

    virtual void TearDown();

    spectre::SizeProperty loadInputDim();

    uint16_t loadInputNumFrameSets();

    template<typename typ>
    void loadAndCheckScalar (spectre::element::container::Container &container, const std::string &path, const std::vector<std::string> &valName);

    template<typename typ>
    void loadAndCheckVector (spectre::element::container::Container &container, const std::string &path, const std::vector<std::string> &valName);

    template<typename srctyp, typename dsttyp>
    void loadCastAndCheckScalar (spectre::element::container::Parameter &param, const std::string &path, const std::vector<std::string> &valName);

    void loadAndCheckConfigFlag (spectre::element::container::Parameter &param, const std::string &path, const std::vector<std::string> &valName);

    void loadNewParameter (spectre::element::container::Parameter &param);

    void loadNewInput (spectre::element::container::Input &input);

    void loadCalibration (std::string filename, spectre::element::container::Calibration &container);

    void loadInput (std::string filename, spectre::element::container::Input &container);

    void loadOutput (std::string filename, spectre::element::container::Output &container);

    void loadParameter (std::string filename, spectre::element::container::Parameter &container);

    void saveInput (std::string filename, spectre::element::container::Input &container);

    void saveOutput (std::string filename, spectre::element::container::Output &container);

    void saveParameter (std::string filename, spectre::element::container::Parameter &parameter);

    void saveCalibration (std::string filename, spectre::element::container::Calibration &container);

};
