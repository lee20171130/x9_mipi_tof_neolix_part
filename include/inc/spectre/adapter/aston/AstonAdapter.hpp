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

#include <processing/processingInternal.hpp>
#include <common/calibration.hpp>

#include <spectre/adapter/Adapter.hpp>

namespace spectre
{
    namespace adapter
    {
        namespace aston
        {
            /**
            *  Adapter type class variant 1 used for data conversion from c++ api level to ansiC processing
            */
            class AstonAdapter : public Adapter
            {
            private:
                struct SpectreInput         procInput;
                struct SpectreOutput        procOutput;
                struct SpectreCalibration   procCalib;
                struct SpectreParameter     procParam;

            public:

                /**
                 * Default ctor
                 */
                AstonAdapter();

                /**
                 * @deprecated Direct calibration handling through the C++ API will be removed soon
                 *
                 * Creates a new AstonAdapter
                 *
                 * @param io target structure for adaption
                 * @param calib calibration container
                 * @param param parameter container
                 * @param input input container
                 * @param output output container
                 */
                AstonAdapter (SpectreIO *io,
                              element::container::Calibration *calib,
                              element::container::Parameter *param,
                              element::container::Input *input,
                              element::container::Output *output);

                /**
                 * Ctor
                 *
                 * Creates a new AstonAdapter
                 *
                 * @param io target structure for adaption
                 * @param calib ready-to-use SpectreCalibration structure
                 * @param param parameter container
                 * @param inter intermediate container
                 * @param input input container
                 * @param output output container
                 *
                 */
                AstonAdapter (SpectreIO *io,
                              struct SpectreCalibration *calib,
                              element::container::Parameter *param,
                              element::container::Input *input,
                              element::container::Output *output);

                virtual ~AstonAdapter();

                /**
                 * Runs the adapter
                 *
                 *
                 * @return status of operation
                 */
                virtual AdapterStatus run() override;

            protected:

                virtual AdapterStatus adaptInput() override;

                virtual AdapterStatus adaptCalibration() override;

                virtual AdapterStatus adaptParamter() override;

                virtual AdapterStatus adaptOutput() override;

                virtual void initInput();

                virtual void initCalibration();

                virtual void initParameter();

                virtual void initOutput();

                virtual AdapterStatus freeInput();

                virtual AdapterStatus freeCalibration();

                virtual AdapterStatus freeParamter();

                virtual AdapterStatus freeOutput();

            };
        }
    }
}
