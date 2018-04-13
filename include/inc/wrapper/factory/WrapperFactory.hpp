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

#include <spectre/SpectreTypeSystem.hpp>

#include <wrapper/Wrapper.hpp>
#include <wrapper/WrapperException.hpp>
#include <wrapper/ref/WrapperReference.hpp>
#include <wrapper/x86/WrapperX86.hpp>
#include <wrapper/arm/WrapperArm.hpp>

namespace spectre
{
    namespace wrapper
    {

        class WrapperFactory
        {

        public:

            static std::shared_ptr<Wrapper> getWrapper (spectre::SpectreTypeSystem systemType,
                    element::container::Calibration &calibration,
                    element::container::Input &input,
                    std::string &activationCode)
            {

                switch (systemType)
                {
                    case spectre::SpectreTypeSystem::REFERENCE:
                        return std::shared_ptr<WrapperReference> (new WrapperReference (calibration, input, activationCode));
#ifdef PMD_SYSTEM_TARGET_X86
                    case spectre::SpectreTypeSystem::X86:
                        return std::shared_ptr<WrapperX86> (new WrapperX86 (calibration, input, activationCode));
#endif //PMD_SYSTEM_TARGET_X86
#ifdef PMD_SYSTEM_TARGET_ARM
                    case spectre::SpectreTypeSystem::ARM:
                        return std::shared_ptr<WrapperArm> (new WrapperArm (calibration, input, activationCode));
#endif //PMD_SYSTEM_TARGET_ARM
                    default:
                        throw WrapperException ("Spectre system type not supported!");
                }
            }

        private:

            WrapperFactory()
            {
            }

        };
    }
}
