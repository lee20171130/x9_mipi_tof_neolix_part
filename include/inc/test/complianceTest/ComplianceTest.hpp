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

#include <system/TestExecutionAlgorithm.hpp>

#include <spectre/access/intern/AccessCode.hpp>
#include <spectre/adapter/aston/AstonAdapter.hpp>
#include <spectre/element/builder/InputBuilder.hpp>
#include <spectre/element/container/Input.hpp>
#include <spectre/element/container/Output.hpp>
#include <spectre/element/container/Container.hpp>
#include <spectre/element/container/Calibration.hpp>
#include <spectre/element/container/Intermediate.hpp>
#include <spectre/element/container/Parameter.hpp>
#include <spectre/element/builder/CalibrationBuilder.hpp>
#include <spectre/element/builder/IntermediateBuilder.hpp>
#include <spectre/element/builder/InputBuilder.hpp>
#include <spectre/element/builder/OutputBuilder.hpp>
#include <spectre/element/builder/ParameterBuilder.hpp>

#include <wrapper/Wrapper.hpp>
#include <wrapper/SpectreExtendedFactory.hpp>
#include <wrapper/factory/WrapperFactory.hpp>

#include <processing/processing.hpp>

static const uint32_t PMD_FLAG_ALL = 0x00000000u;

class Test_complianceTest : public testing::Test
{
protected:

    std::string m_activationCode = accessCodeInternal;

    TestExecutionAlgorithmPtr algo;

    spectre::wrapper::SpectreExtendedFactory m_fac {};

    spectre::element::container::Input m_inputReference {};
    spectre::element::container::Parameter m_paramReference{};
    spectre::element::container::Calibration m_calibReference{};
    spectre::element::container::Intermediate m_interReference{};
    spectre::element::container::Output m_outputReference{};

    spectre::element::container::Input m_inputPrototype{};
    spectre::element::container::Parameter m_paramPrototype{};
    spectre::element::container::Calibration m_calibPrototype{};
    spectre::element::container::Intermediate m_interPrototype{};
    spectre::element::container::Output m_outputPrototype{};

    std::shared_ptr<spectre::wrapper::Wrapper> m_Reference;
    std::shared_ptr<spectre::wrapper::Wrapper> m_Prototype;

    const std::string m_globalDir;
    const std::string m_calibDir;
    const std::string m_paramDir;
    const std::string m_inputDir;

protected:

    Test_complianceTest();

    virtual ~Test_complianceTest();

    virtual void SetUp();

    virtual void SetUpSystem();

    virtual void TearDown();

    std::vector<uint8_t> loadData (const std::string &filepath);

    template <typename BuilderType>
    typename BuilderType::BuildType loadContainer (const std::string &filepath, const std::string &activationCode);
    template <typename BuilderType>
    typename BuilderType::BuildType initContainer (const spectre::element::container::Input &input, const std::string &activationCode);

    template <typename ContainerType>
    bool check (const std::vector<std::string> &path,
                const std::string &singleThresh = "",
                const std::string &averageThresh = "",
                uint32_t limit = 0,
                bool useFlags = false);

    template<typename T>
    bool checkData (std::shared_ptr <spectre::element::data::DataBase> reference,
                    std::shared_ptr <spectre::element::data::DataBase> prototype,
                    const std::vector<std::string> &path,
                    const std::string &singleThresh = "",
                    const std::string &averageThresh = "",
                    uint32_t limit = 0,
                    uint32_t *flags = nullptr);

    bool checkFlags (uint32_t flag = PMD_FLAG_ALL, uint32_t limit = 0);

    bool checkCoordinates (const float singleThresh = 0.0f,
                           const float averageThresh = 0.0f,
                           uint32_t limit = 0u,
                           bool useFlags = false);

    template <typename T>
    T stringToNumber (const std::string &Text);

    template <typename T>
    std::string numberToString (T Number);

};

TEST_F (Test_complianceTest, flagMask)
{
    checkFlags (PMD_MASK_ILLUMINATION);
}


TEST_F (Test_complianceTest, flagSaturation)
{
    checkFlags (PMD_FLAG_SATURATED);
}

TEST_F (Test_complianceTest, unscrambleReIm)
{
    using namespace spectre;
    using namespace spectre::element::container;

    switch (m_inputReference.getType())
    {
        case SpectreTypeInput::ASTON_I1P4P4:
            {
                check <Intermediate> ({ "ProbeData", "ProbeData_1", "Re" });
                check <Intermediate> ({ "ProbeData", "ProbeData_1", "Im" });
                check <Intermediate> ({ "ProbeData", "ProbeData_1", "Asym" });
            }
        case SpectreTypeInput::ASTON_I1P4:
            {
                check <Intermediate> ({ "ProbeData", "ProbeData_0", "Re" });
                check <Intermediate> ({ "ProbeData", "ProbeData_0", "Im" });
                check <Intermediate> ({ "ProbeData", "ProbeData_0", "Asym" });
                break;
            }
        default:
            ASSERT_TRUE (false);
            break;
    }
}

TEST_F (Test_complianceTest, unscrambleIntensity)
{
    using namespace spectre::element::container;
    check <Output> ({ "Intensity" }, "0.01", "0.001");
}

TEST_F (Test_complianceTest, calcAmplitude)
{
    using namespace spectre;
    using namespace spectre::element::container;

    switch (m_inputReference.getType())
    {
        case SpectreTypeInput::ASTON_I1P4P4:
            {
                check <Output> ({ "ProbeData", "ProbeData_1", "Amplitude" }, "0.1", "0.01");
            }
        case SpectreTypeInput::ASTON_I1P4:
            {
                check <Output> ({ "ProbeData", "ProbeData_0", "Amplitude" }, "0.1", "0.01");
                break;
            }
        default:
            ASSERT_TRUE (false);
            break;
    }
}

TEST_F (Test_complianceTest, calcPhase)
{
    using namespace spectre::element::container;
    check <Intermediate> ({ "Phase" }, "0.002", "0.002");
}

TEST_F (Test_complianceTest, flagAmplitudeThreshold)
{
    checkFlags (PMD_FLAG_LOW_SIGNAL, 10u);
}

TEST_F (Test_complianceTest, flagAsymmetry)
{
    checkFlags (PMD_FLAG_INCONSISTENT, 10u);
}

TEST_F (Test_complianceTest, calcAmplitudeNoise)
{
    using namespace spectre;
    using namespace spectre::element::container;

    switch (m_inputReference.getType())
    {
        case SpectreTypeInput::ASTON_I1P4P4:
            {
                check <Output> ({ "ProbeData", "ProbeData_1", "AmplitudeNoise" }, "0.01", "0.001");
            }
        case SpectreTypeInput::ASTON_I1P4:
            {
                check <Output> ({ "ProbeData", "ProbeData_0", "AmplitudeNoise" }, "0.01", "0.001");
                break;
            }
        default:
            ASSERT_TRUE (false);
            break;
    }
}

TEST_F (Test_complianceTest, calcPhaseNoise)
{
    using namespace spectre::element::container;
    check <Intermediate> ({ "PhaseNoise" }, "0.001", "0.0001");
}

TEST_F (Test_complianceTest, correctAmplitudeWiggling)
{
    using namespace spectre;
    using namespace spectre::element::container;

    switch (m_inputReference.getType())
    {
        case SpectreTypeInput::ASTON_I1P4P4:
            {
                check <Intermediate> ({ "ProbeData", "ProbeData_1", "AmplitudeNorm" }, "0.001", "0.0001");
                check <Intermediate> ({ "ProbeData", "ProbeData_1", "AmplitudeNoiseNorm" }, "0.0001", "0.00001");
            }
        case SpectreTypeInput::ASTON_I1P4:
            {
                check <Intermediate> ({ "ProbeData", "ProbeData_0", "AmplitudeNorm" }, "0.001", "0.0001");
                check <Intermediate> ({ "ProbeData", "ProbeData_0", "AmplitudeNoiseNorm" }, "0.0001", "0.00001");
                break;
            }
        default:
            ASSERT_TRUE (false);
            break;
    }
}

TEST_F (Test_complianceTest, correctPhaseWiggling)
{
    using namespace spectre::element::container;
    check <Intermediate> ({ "Phase" }, "0.002", "0.0002");
}

TEST_F (Test_complianceTest, calcPhase2Distance)
{
    using namespace spectre::element::container;
    check <Output> ({ "Distance" }, "0.0001", "0.00001");
}

TEST_F (Test_complianceTest, correctTemperature)
{
    using namespace spectre::element::container;
    check <Output> ({ "Distance" }, "0.0001", "0.00001");
}

TEST_F (Test_complianceTest, correctFPPN)
{
    using namespace spectre::element::container;
    check <Output> ({ "Distance" }, "0.0001", "0.00001");
}

TEST_F (Test_complianceTest, calcNFreq)
{
    using namespace spectre::element::container;
    check <Output> ({ "Distance" }, "0.0001", "0.00001");
    check <Output> ({ "DistanceNoise" }, "0.0001", "0.00001");
    check <Intermediate> ({ "DeltaDistance" }, "0.0001", "0.00001");
}

TEST_F (Test_complianceTest, filterNFreq)
{
    using namespace spectre::element::container;
    check <Output> ({ "Distance" }, "0.0001", "0.00001");
}

TEST_F (Test_complianceTest, filterAdaptiveNoise)
{
    using namespace spectre::element::container;
    check <Output> ({ "Distance" }, "0.0001", "0.00001");
}

TEST_F (Test_complianceTest, flagMPICalc)
{
    using namespace spectre;
    using namespace spectre::element::container;

    check <Intermediate> ({ "AmpFlagLevel" }, "0.000001", "0.0005", 0, true);
    check <Intermediate> ({ "RelNoise" }, "0.000001", "0.0001", 0, true);
}

TEST_F (Test_complianceTest, flagMPIAmp)
{
    checkFlags (PMD_FLAG_MPI_AMP, 10u);
}

TEST_F (Test_complianceTest, flagMPIDist)
{
    checkFlags (PMD_FLAG_MPI_DIST, 10u);

}

TEST_F (Test_complianceTest, flagNoise)
{
    checkFlags (PMD_FLAG_LOW_SIGNAL, 10u);
}

TEST_F (Test_complianceTest, calcCartesianCoordinates)
{
    using namespace spectre::element::container;
    checkCoordinates (0.001f, 0.0001f, 50u, true);
}

TEST_F (Test_complianceTest, flagFlyingPixel)
{
    checkFlags (PMD_FLAG_FLYINGPIXEL, 50u);
}

TEST_F (Test_complianceTest, calcAutoExposure)
{
    using namespace spectre::element::container;
    check <Output> ({ "ExposureTimes" });
}

TEST_F (Test_complianceTest, validImage)
{
    using namespace spectre::element::container;
    check <Output> ({ "Distance" }, "0.001f", "0.0001f", 50u, true);
    check <Output> ({ "DistanceNoise" }, "0.001f", "0.001", 50u, true);
    checkCoordinates (0.001f, 0.001f, 50u, true);
    checkFlags (PMD_FLAG_ALL, 50u);
}

TEST_F (Test_complianceTest, all)
{
    using namespace spectre::element::container;
    check <Output> ({ "Distance" }, "0.001f", "0.0001f", 50u, true);
    check <Output> ({ "DistanceNoise" }, "0.001f", "0.001", 50u, true);
    check <Output> ({ "Amplitude" }, "0.1f", "0.01f", 50u, true);
    check <Output> ({ "Intensity" }, "0.1f", "0.01", 50u, true);
    checkCoordinates (0.001f, 0.0001f, 50u, true);
    checkFlags (PMD_FLAG_ALL, 50u);
}
