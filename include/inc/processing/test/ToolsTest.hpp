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
#include <random>
#include <limits>
#include <cmath>

#include <processing/test/ToolsTestPath.hpp>
#include <processing/aston/astonTools.hpp>

enum inputType
{
    IN_I1P4,
    IN_I1P4P4
};

enum inputVariant
{
    FC_I1P4,
    FC_P4I1,
    FC_I1P4P4,
    FC_P4I1P4,
    FC_P4P4I1
};

enum calibType
{
    ONE_FREQ,
    TWO_FREQ
};

enum paramType
{
    PA_I1P4,
    PA_I1P4P4
};

/**
*  The ToolsTest checks the specte ansi-c binary format save and load
*  methods to store ansi-c spectre input, calibration and parameter
*  data structures.
*  This unit tets follows the general set of pmd test instructions
*  (please read the documentation for further indtructions) to determine
*  the working directory.
*/
class ToolsTest : public testing::Test
{
public:

    ToolsTest() :
        m_numPixel (224 * 168),
        m_inTest (nullptr),
        m_calibTest (nullptr),
        m_paramTest (nullptr),
        m_inRef (nullptr),
        m_calibRef (nullptr),
        m_paramRef (nullptr),
        m_workingDir (""),
        m_inputDir ("Process_Input"),
        m_paramDir ("Process_Param"),
        m_calibDir ("Process_Calib")
    {}

    virtual ~ToolsTest()
    {}

protected:
    virtual void SetUp();

    virtual void TearDown();

    /**
    * Check if two linear data arrays a and b are
    * equal.
    *
    * @param size Data size of the array
    *
    * @return true if arrays are of identical value, else false.
    */
    template <typename T>
    void cmpArr (const T *a, const T *b, uint32_t size);

    /**
    * Returns a random integer data value of type t.
    *
    * @return random data value
    */
    template<typename T>
    T initRndValInt();

    /**
    * Returns a random data value of type t.
    *
    * @return random data value
    */
    template<typename T>
    T initRndVal();

    /**
    * Returns a random binary (0 or 1) data value of type t.
    *
    * @return random data value
    */
    template<typename T>
    T initRndBoolVal();

    /**
    * Allocates a linear integer data array of type t, predefined size and
    * filled with random data values.
    *
    * @param size Total data size to be allocated
    *
    * @return handle to the allocated data memory area
    */
    template<typename T>
    T *initRndArrInt (uint32_t size);

    /**
    * Allocates a linear data array of type t, predefined size and
    * filled with random data values.
    *
    * @param size Total data size to be allocated
    *
    * @return handle to the allocated data memory area
    */
    template<typename T>
    T *initRndArr (uint32_t size);

    /**
    * Allocates a linear integer data array of type t, predefined size and
    * filled with random binary (0 or 1) data values.
    *
    * @param size Total data size to be allocated
    *
    * @return handle to the allocated data memory area
    */
    template<typename T>
    T *initRndBoolArrInt (uint32_t size);

    /**
    * Allocates a linear data array of type t, predefined size and
    * filled with random binary (0 or 1) data values.
    *
    * @param size Total data size to be allocated
    *
    * @return handle to the allocated data memory area
    */
    template<typename T>
    T *initRndBoolArr (uint32_t size);

    /**
    * Allocates a 3d random coordinate directions data, with limited entropy
    * for lossless data compression and decompression in compliance
    * with the deprecated pmd '.cal' tar container data format.
    *
    * @param size Total data size to be allocated
    *
    * @return handle to the allocated data memory area
    */
    float *initRndDirections (uint32_t size);

    /**
    * Allocates a lens parameter data, with limited entropy
    * for lossless data compression and decompression in compliance
    * with the deprecated pmd '.cal' tar container data format.
    *
    * @param size Total data size to be allocated
    *
    * @return handle to the allocated data memory area
    */
    float *initRndLensParameter (uint32_t size);

    /**
    * Initializes a spectre input raw data container with
    * random values according to the spectre input container
    * frameSet definition.
    *
    * @param dst Ansi-C spectre input destination data structure
    */
    void initRndRawData (struct SpectreInput **dst);

    /**
    * Initializes a spectre input phase order container with
    * random values according to the spectre input container
    * frameSet definition.
    *
    * @param dst Ansi-C spectre input destination data structure
    */
    void initRndPhaseOrder (struct SpectreInput **dst);

    /**
    * Compares the raw data within two spectre input data structures
    * and checks if they are equal in value.
    *
    * @param ref Ansi-C spectre input reference data structure
    * @param test Ansi-C spectre input calculus data structure
    */
    void cmpRawData (const struct SpectreInput *ref, const struct SpectreInput *test);

    /**
    * Compares the phase order within two spectre input data structures
    * and checks if they are equal in value.
    *
    * @param ref Ansi-C spectre input reference data structure
    * @param test Ansi-C spectre input calculus data structure
    */
    void cmpPhaseOrder (const struct SpectreInput *ref, const struct SpectreInput *test);

    /**
    * Initialize a spectre calibration probe data structure with
    * random data values according to the spectre spectre calibration
    * size probe data definition.
    *
    * @param dst Ansi-C spectre calibration destination data structure
    */
    void initRndCalibProbeData (struct SpectreCalibration **dst);

    /**
    * Compares the probe data within two spectre calibration data structures
    * and checks if they are equal in value.
    *
    * @param ref Ansi-C spectre calibration reference data structure
    * @param test Ansi-C spectre calibration calculus data structure
    */
    void cmpCalibProbeData (const struct SpectreCalibration *ref, const struct SpectreCalibration *test);

    /**
    * Initializes a spectreInput data structure with random data.
    * The internal sub structure configuration is defined via the
    * inputType, inputVariant, definition, as well ass the total
    * number of raw data pixel.
    *
    * @param numPixel Defines the size of linear memory allocated
    *                 for image maps (designation `pm_`)
    * @param type Test specific designation, which should coincide
    *                  with the aston c++ api input container type
    *                  definition.
    * @param variant Variant type definition, in compliance with
    *                the spectre c++ api frames set composition
    *                variance.
    *
    * @return name spectre input Ansi-C data struct.
    */
    struct SpectreInput *initRndInput (uint32_t numPixel, enum inputType type, enum inputVariant variant);

    /**
    * Initializes a spectre calibration data structure with random data.
    * The internal sub structure configuration is defined via the
    * inputType, definition, as well ass the total number of pixels
    * within the calibrated area.
    *
    * @param numPixel Defines the size of linear memory allocated
    *                 for image maps (designation `pm_`)
    * @param type Test specific designation, which should coincide
    *                  with the aston c++ api input container type
    *                  definition.
    *
    * @return name spectre calibration Ansi-C data struct.
    */
    struct SpectreCalibration *initRndCalib (uint32_t numPixel, enum calibType type);

    /**
    * Initializes a spectre parameter data structure with random data.
    * The internal sub structure configuration is defined via the
    * inputType, definition.
    *
    * @param type Test specific designation, which should coincide
    *                  with the aston c++ api input container type
    *                  definition.
    *
    * @return name spectre calibration Ansi-C data struct.
    */
    struct SpectreParameter *initRndParam (enum paramType type);

    /**
    * Compares two spectre input data structure and checks if they are equal.
    * in value.
    *
    * @param ref Ansi-C spectre input reference data structure
    * @param test Ansi-C spectre input calculus data structure
    */
    void cmpInput (const struct SpectreInput *ref, const struct SpectreInput *test);

    /**
    * Compares two spectre calibration data structure and checks if they are equal.
    * in value.
    *
    * @param ref Ansi-C spectre calibration reference data structure
    * @param test Ansi-C spectre calibration calculus data structure
    */
    void cmpCalib (const struct SpectreCalibration *ref, const struct SpectreCalibration *test);

    /**
    * Compares two spectre paramter data structure and checks if they are equal.
    * in value.
    *
    * @param ref Ansi-C spectre parameter reference data structure
    * @param test Ansi-C spectre parameter calculus data structure
    */
    void cmpParam (const struct SpectreParameter *ref, const struct SpectreParameter *test);

protected:

    const uint32_t m_numPixel;

    struct SpectreInput *m_inTest;
    struct SpectreCalibration *m_calibTest;
    struct SpectreParameter *m_paramTest;

    struct SpectreInput *m_inRef;
    struct SpectreCalibration *m_calibRef;
    struct SpectreParameter *m_paramRef;

    std::string m_workingDir;
    const std::string m_inputDir;
    const std::string m_paramDir;
    const std::string m_calibDir;

    std::default_random_engine m_rndGen;

};
