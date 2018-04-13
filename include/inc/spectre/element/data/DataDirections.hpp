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

#include<spectre/element/data/DataAlias.hpp>
#include <spectre/SpectreCommon.hpp>

namespace spectre
{

    class Spectre;
    enum class SpectreLensModel;


    namespace element
    {
        namespace data
        {

            class LensTransform;

            ///**
            //*  Scalar data element used for alias data transformation
            //*/
            class DataDirections : public DataAlias< float, Data<float> >
            {
                friend class spectre::Spectre;
                friend class spectre::element::data::LensTransform;

            public:

                DataDirections (std::shared_ptr<Data<float>> alias,
                                std::string strId,
                                const std::string &activationCode,
                                std::shared_ptr<LensTransform> lensTransform);

                virtual ~DataDirections();

				/**
				*  Serialization
				*/
				virtual SpectreStatus serialize(std::vector<uint8_t> &output) const override;

                /**
                *   Deserialization
                */
                virtual SpectreStatus deSerialize (const std::vector<uint8_t> &input, size_t &idx) override;

                /*  Returns the Lens modell used to determine directions
                *   from the lensparameters.
                *
                *   @param lensParameter Lens distortion data.
                *   @param acvitvationCode Overwrites inherent data activation code.
                *   @return Status of operation.
                */
                SpectreStatus getLensParameter (LensParameter &lensParameter,
                                                const std::string &activationCode = "") const;

                /*  Returns Data precision used for storage efficiency. Copied by value.
                *
                *   @return Spectre specific calibration lenstype defintion.
                *   @param acvitvationCode Overwrites inherent data activation code.
                *   @return Status of operation.
                */
                SpectreStatus getLensModel (SpectreLensModel &lensType,
                                            const std::string &activationCode = "") const;

                /*  Returns stored data element values by value.
                *
                *   @param values Return values as copy of the internally stored values.
                *   @return Status of operation.
                */
                virtual SpectreStatus getValues (std::vector<float> &values,
                                                 const std::string &activationCode = "") const override;

                virtual SpectreTypeElement  getElementType () const override;


                virtual float *getDataHandle() override;

                virtual Element *clone() const override;

            private:
                virtual bool setHeader (std::vector<uint8_t> &output) const override;

                virtual SpectreStatus readHeader (const std::vector<uint8_t> &input, size_t &idx) override;

                virtual SpectreStatus setValues (const std::vector<float> &values,
                                                 const std::string &activationCode = "") override;

                /**
                *   Retrieves lensparameter from the calibration data.
                *
                *   @param activationCode activation code
                *   @return Lens distortion data.
                */
                LensParameter getLensParameter (const std::string &activationCode) const;
            };
        }
    }
}
