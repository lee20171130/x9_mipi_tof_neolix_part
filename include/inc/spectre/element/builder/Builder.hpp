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

#include <spectre/SpectreVersion.hpp>
#include <spectre/access/AccessLevel.hpp>
#include <spectre/element/data/Data.hpp>
#include <spectre/SpectreStatus.hpp>

namespace spectre
{
    namespace element
    {
        namespace builder
        {

            /**
            *  Container builder base class
            */
            class Builder
            {
            public:
                /**
                *   Destructor of the input data container
                */
                virtual ~Builder();

                /**
                *   Validate the activation Code and return appropriate access level.
                *
                *   @return User interface access level.
                */
                spectre::access::AccessLevel getAccessLevel();

                /**
                *   Resets the access code and returns the related user access level.
                *
                *   @return User interface access level.
                */
                spectre::access::AccessLevel setAccessCode();

                /**
                *   Retrieves the related spectre version type id.
                *
                *   @return Spectre version id.
                */
                spectre::SpectreVersion getVersion();

            protected:
                /**
                *   Constructor for the builder base class
                *
                *   @param activationCode Necessary to activate specific access level.
                */
                explicit Builder (const std::string &activationCode = "");


            protected:
                const std::string m_AC;     //< Access Code
                SpectreVersion m_version;   //< Current builder version id
            };

        }
    }
}
