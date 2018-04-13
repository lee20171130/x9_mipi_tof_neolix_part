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

#include <string>
#include <vector>
#include <stdint.h>
#include <spectre/SpectreFactory.hpp>

namespace spectre
{
    namespace utils
    {
        template <typename BuilderType>
        typename BuilderType::BuildType loadContainer (const std::vector<uint8_t> &serialData, const std::string &activationCode)
        {
            using BuildType =  typename BuilderType::BuildType;
            BuildType container {};
            spectre::SpectreFactory fac {};
            auto pBuilder = fac.getBuilder<BuilderType> (activationCode);
            auto result = pBuilder->getContainer (serialData, container);
            if (isFailure (result))
            {
                throw result;
            }
            return container;
        }

    }
}
