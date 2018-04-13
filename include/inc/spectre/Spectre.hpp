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

#include <spectre/SpectreCommon.hpp>
#include <spectre/SpectreStatus.hpp>
#include <spectre/SpectreVersion.hpp>

struct SpectreIO;
struct SpectreCalibration;

namespace spectre
{
    enum class SpectreLensModel;

    namespace adapter
    {
        class Adapter;
    }

    namespace element
    {
        namespace container
        {
            class Calibration;
            class Input;
            class Output;
            class Parameter;
        }
    }

    /**
    *  The Spectre class is the base class wrapper for the reference c main processing function.
    */
    class Spectre
    {
    public:
        /**
         *   @deprecated Calibration handling through containers will be removed in future versions
         *
         *   Constructor of the base processing wrapper, automaticall calls the processing initialization function initProcessings method
         *
         *   @param calib Calibration data used for intrinsic error compensation.
         *   @param param Parameter data used for runtime processing configuration.
         *   @param input Input data comprises raw data, temperature data as well as the imager configuration settings.
         *   @param output Input data of pmd Time-Of-Flight depth data processing.
         */
        Spectre (const element::container::Calibration &calib,
                 const element::container::Parameter &param,
                 const element::container::Input &input,
                 const element::container::Output &output);

        /**
         * Constructs a base processing wrapper.
         *
         * All
         *
         * @param calib ready to use calibration structure, ownership transferred to callee
         * @param param Parameter data used for runtime processing configuration.
         * @param input Input data comprises raw data, temperature data as well as the imager configuration settings.
         * @param output Input data of pmd Time-Of-Flight depth data processing.
         */
        Spectre (struct SpectreCalibration *calib,
                 const element::container::Parameter &param,
                 const element::container::Input &input,
                 const element::container::Output &output);

        Spectre (const Spectre &spec) = delete;

        Spectre (Spectre &&spec) = delete;

        /**
        *   Destructor of the spectre processing wrapper, automatically calls the processing deinitialization functions.
        */
        virtual ~Spectre();

        // ----------------------------------------------------------------------------------------------
        // Level 1: Standard users
        // ----------------------------------------------------------------------------------------------

        /**
        *   LEVEL 1
        *   On execution the depth data is processed
        */
        SpectreStatus run();

        /**
        *   LEVEL 1
        *   Retrieves spectre version id.
        *
        *   @return Version id tag.
        */
        SpectreVersion getVersion() const;

        /**
         *
         *   LEVEL 1
         *   Verifies the composition of the sub modules.
         *
         *   @return Success if internal composition enables successfull processing. Else INCORRECT_COMPOSITION is returned.
         */
        SpectreStatus verify() const;

        /**
         *   LEVEL 1
         *   Retrieves lensparameter from the calibration data.
         *
         *   @param lensParameter Lens distortion data.
         *   @return Status of operation.
         */
        SpectreStatus getLensParameter (LensParameter &lensParameter) const;

        /**
        *   LEVEL 1
        *   Retrieves lens modell type from the calibration data.
        *
        *   @param lentype Lens distortion modell.
        *   @return Status of operation.
        */
        SpectreStatus getLensModel (SpectreLensModel &typeLens) const;

        /**
        *   LEVEL 1
        *   Retrieves the position inforamtion of calibration data stored on the device
        *   specified with respect to the absolute sensor coordinates.
        *
        *   @param  Calibration sensor region.
        *   @return Status of operation.
        */
        SpectreStatus getCalibrationROI (ROI calibrationROI) const;

        /**
        *   LEVEL 1
        *   Retrieves input data from spectre processing  as copy by value.
        *
        *   @param Input data container to be returned.
        *   @return Status of operation.
        */
        SpectreStatus getInput (element::container::Input &valueOut);

        /**
        *   LEVEL 1
        *   Gets the spectre processing input data as a binary description file.
        *
        *   @param binaryout Input data container in binary description format.
        *   @return Status of operation.
        */
        SpectreStatus getInput (std::vector<uint8_t> &binaryOut) const;

        /**
        *   LEVEL 1
        *   Retrieves output data from spectre processing as copy by value.
        *
        *   @param Output data container to be returned.
        *   @return Status of operation.
        */
        SpectreStatus getOutput (element::container::Output &valueOut) const;

        /**
        *   LEVEL 1
        *   Gets the spectre processing output data as a binary description file.
        *
        *   @param binaryout Output data container in binary description format.
        *   @return Status of operation.
        */
        SpectreStatus getOutput (std::vector<uint8_t> &binaryOut) const;

        /**
        *   LEVEL 1
        *   Retrieves the processing parameter data from spectre.
        *
        *   @param Parameter data container to be returned.
        *   @return Status of operation.
        */
        SpectreStatus getParameter (element::container::Parameter &valueOut) const;

        /**
        *   LEVEL 1
        *   Gets the spectre processing parameter data as a binary description file.
        *
        *   @param binaryout Parameter data container in binary description format.
        *   @return Status of operation.
        */
        SpectreStatus getParameter (std::vector<uint8_t> &binaryOut) const;

        /**
        *   LEVEL 1
        *   Sets the processing parameter data for spectre.
        *
        *   @param Parameter data container to be set.
        *   @return Status of operation.
        */
        SpectreStatus setParameter (element::container::Parameter &valueIn);

        /**
         *  @deprecated Calibration handling will be moved out of Spectre, does only work for ASTON calibration filled in by the legacy interface
         *
         *   LEVEL 1
         *   Gets the spectre processing calibration data as a binary description file.
         *
         *   @param binaryout Calibration data container in binary description format.
         *   @return Status of operation.
         */
        SpectreStatus getCalibration (std::vector<uint8_t> &binaryOut) const;

        // ----------------------------------------------------------------------------------------------
        // Level 2: Binary Integration
        // ----------------------------------------------------------------------------------------------

        /**
        *   LEVEL 2
        *   Retrieves handle to the input data from spectre.
        *
        *   @param Output data container to be returned.
        *   @param acvitvationCode Enable user access.
        *   @return Status of operation.
        */
        SpectreStatus getInputHandle (element::container::Input **pInput, const std::string &activationCode = "");

        /**
        *   LEVEL 2
        *   Retrieves handle to the output data from spectre.
        *
        *   @param Output data container to be returned.
        *   @param acvitvationCode Enable user access.
        *   @return Status of operation.
        */
        SpectreStatus getOutputHandle (element::container::Output **pOutput, const std::string &activationCode = "");

        /**
        *   LEVEL 2
        *   Retrieves handle to the parameter data from spectre.
        *
        *   @param Parameter data container to be returned.
        *   @param acvitvationCode Enable user access.
        *   @return Status of operation.
        */
        SpectreStatus getParameterHandle (element::container::Parameter **pParameter, const std::string &activationCode = "");

        // ----------------------------------------------------------------------------------------------
        // Level 3: Source Access
        // ----------------------------------------------------------------------------------------------

        /**
        *   @deprecated Calibration handling will be moved out of Spectre, does only work for ASTON calibration filled in by the deprecated interfaces
        *   LEVEL 3
        *   Retrieves handle to the parameter data from spectre processing.
        *
        *   @param Parameter data container to be returned.
        *   @param acvitvationCode Enable user access.
        *   @return Status of operation.
        */
        SpectreStatus getCalibration (element::container::Calibration &valueOut, const std::string &activationCode = "") const;


        /**
         * LEVEL 3
         * Gets the underlying SpectreIO structure
         * SpectreIO is the composition of all data structures used of the underlying C processing kernel
         *
         * Note: This function provides access to a pointer which represents the internal state of this class
         * Its contents are implemention defined, and any change to the structure might lead to undefined behavior. The
         * pointer is owned by the callee, is valid as long the callee is not destructed.
         *
         * @param io pointer where a pointer to the C processing structure is stored
         * @param activationCode activation code
         *
         * @return Status of operation
         */
        SpectreStatus getSpectreIO (SpectreIO **io, const std::string &activationCode = "");

        /**
         * Gets an opaque pointer handle to the current loaded calibration
         * This handle can be used with libspectre_calibration.
         *
         *
         * @return opaque handle to calibration, or nullptr if Spectre was not initialized properly
         */
        const struct SpectreCalibration *getCalibrationHandle() const;

        /**
         * Releases the calibration which held by this Spectre instance
         *
         * If the released calibration is modified or free'd, calling any function on the Spectre
         * instance is undefined.
         *
         * @return opaque handle to calibration, or nullptr if Spectre was not initialized properly
         */
        struct SpectreCalibration *releaseCalibration();

    protected:
        std::unique_ptr<element::container::Parameter> m_param;
        std::unique_ptr<element::container::Input> m_input;
        std::unique_ptr<element::container::Output> m_output;
        std::unique_ptr<adapter::Adapter> m_adapter;
        std::unique_ptr<SpectreIO> m_io;
        std::unique_ptr<struct SpectreCalibration, void (*) (struct SpectreCalibration *) > m_calib;
        std::unique_ptr<element::container::Calibration> m_procCalib;

    private:
        /**
         * Initializes this spectre instance
         *
         * @param calib calibration (container or opaque pointer to struct SpectreCalibration)
         * @param param parameter container
         * @param input input container
         * @param output output container
         */
        template<typename T>
        void initSpectre (T calib, const element::container::Parameter &param,
                          const element::container::Input &input,
                          const element::container::Output &output);
        /**
         * Copies the given calibration field to a given vector.
         * The given field number must convert to the SPECTRE_CALIBRATION_FIELD enum in libspectre_calibration
         * which defines the public calibration fields.
         *
         * @param calibrationField field to copy
         * @param target target vector (will be resized)
         *
         * @return status code
         */
        template<typename T>
        spectre::SpectreStatus copyCalibrationField (int calibrationField, std::vector<T> &target) const;

    };
}
