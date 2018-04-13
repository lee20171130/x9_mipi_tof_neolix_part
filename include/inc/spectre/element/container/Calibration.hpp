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

#include <vector>
#include <memory>

#include <spectre/element/container/Container.hpp>
#include <spectre/element/container/RootContainerCommon.hpp>
#include <spectre/SpectreTypeCalibration.hpp>

namespace spectre
{
    namespace element
    {
        namespace container
        {

            /**
            *  Calibration data container class
            */
            class Calibration : public Container
            {
            public:
                using CalibrationHeader = RootContainerHeader<SpectreTypeCalibration>;
                using FramesType = SpectreTypeCalibration;

                /**
                * Ctor for construction of an empty calibration container
                *
                * @param activationCode activation code
                */
                explicit Calibration (const std::string &activationCode = "");

                /**
                *   Destructor of the calibration data container.
                */
                virtual ~Calibration();

                /**
                * Constructor of the calibration data container.
                *
                * @param version Chosen spectre version.
                * @param calibrationType Type of calibration
                * @param containerDim Dimensional properties of the calibration container.
                * @parma strId Element identifaction tag as clear string value.
                * @param activationCode Specific activation code to enable user access.
                * @param dataList List of composed sub data elements.
                */
                Calibration (SpectreVersion version,
                             SpectreTypeCalibration calibrationType,
                             const SizeProperty &containerDim,
                             const std::string &strId,
                             const std::string &activationCode,
                             const std::vector<std::shared_ptr<Element>> &dataList
                            );

                /**
                *   Returns calibration data type id.
                *
                *   @param Type id.
                */
                SpectreTypeCalibration getType () const;

                /**
                * Gets the dimensional properties of this container
                *
                * @return dimensional properties
                */
                SizeProperty getContainerDim() const;

                virtual SpectreStatus deSerialize (const std::vector<uint8_t> &binaryData, size_t &idx) override;

                virtual SpectreStatus serialize (std::vector<uint8_t> &output) const override;

                /**
                 * Reads the header of the calibration from a serialized data stream
                 *
                 * @param data serialized container
                 * @param idx offset where the calibration data starts
                 * @param dim result
                 *
                 * @return result status of operation
                 */
                SpectreStatus queryHeader (const::std::vector<uint8_t> &data,
                                           size_t idx, CalibrationHeader &header) const;

                /**
                * Retrieves calibration ROI information from the input data container
                *
                */
                ROI getCalibrationROI() const;

                virtual SpectreTypeElement  getElementType () const override;

                virtual Element *clone() const override;

                /**
                 * Sets the type of the calibration
                 *
                 * Usually, the calibration type is set automatically during deSerialization
                 * and, it is not necessary to alter it.
                 * Be careful: Setting a wrong calibration type leads to undefined behavior.
                 *
                 *
                 * @param typeCalibration new calibration type
                 */
                void setType (SpectreTypeCalibration typeCalibration);

                /**
                * Compares this calibration Container with another. Returns true if
                * both container equal in dimensions, version, type and variant.
                *
                * @param cmp Calibration container to be compared against.
                *
                * @return true if container are identical.
                */
                bool equalCfg (const Element &cmp) const override;

            protected:
                virtual bool setHeader (std::vector<uint8_t> &output) const override;

                virtual SpectreStatus readHeader (const std::vector<uint8_t> &header,
                                                  size_t &idx) override;


            private:
                SpectreTypeCalibration m_type;      //< Spectre calibration data type id.
                SizeProperty m_containerDim;        //< Dimensional properties of the container element

                static const std::string S_MAGIC_WORD;
            };

        }
    }
}
