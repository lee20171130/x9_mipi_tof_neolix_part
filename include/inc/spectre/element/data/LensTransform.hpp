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

#include <spectre/element/data/TransformFunctor.hpp>
#include <spectre/SpectreCommon.hpp>
#include <spectre/SpectreLensModel.hpp>
#include <memory>

namespace spectre
{
    namespace element
    {
        namespace data
        {

            /**
            *  Transformation functor for lens data to directions conversion
            */
            class LensTransform : public TransformFunctor < Data<float>, Data<float>>
            {
            public:
                /**
                *   Constructor of the lens transform element
                */
                LensTransform (SpectreLensModel lensModell, std::shared_ptr<Data<uint32_t>> subROI);

                /**
                *   Destructor of the lens transform element
                */
                ~LensTransform();

                /**
                *  transformation from Lensparameter to directions
                */
                virtual TransformStatus transform (Data<float> *source, Data<float> *destination) override;

                /*  Lens modell used to determine directions for depth transformation into cartesian coordinates.
                *
                *   @return PMD specific calibration lenstype.
                */
                SpectreLensModel getLensModel();


            private:
                std::shared_ptr<Data<uint32_t>> m_subROI;
                SpectreLensModel m_lensModell;

            private:
                /// Number of iterations used for the computation of the directions
                static const uint32_t S_ITERATIONS;
            };


        }
    }
}
