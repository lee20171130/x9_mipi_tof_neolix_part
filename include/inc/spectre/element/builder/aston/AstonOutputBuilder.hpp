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

#include <spectre/element/builder/OutputBuilder.hpp>
#include <set>

namespace spectre
{
    namespace element
    {
        namespace builder
        {
            namespace aston
            {

                /**
                *  Builder class for aston output data container
                */
                class AstonOutputBuilder : public OutputBuilder
                {

                protected:

                    std::vector<SpectreTypeOutput> m_types;       ///< List of supported output data types.


                public:

                    /**
                    *   Protected Constructor of the aston output data builder class
                    *
                    *   @param activationCode Necessary to activate specific access level
                    */
                    explicit AstonOutputBuilder (const std::string &activationCode = "");

                    /**
                    *   Destructor of the output data builder version 1 class
                    */
                    virtual ~AstonOutputBuilder();

                    virtual spectre::SpectreStatus getContainer (const std::vector<uint8_t> &input,
                            container::Output &destination) override;

                    virtual spectre::SpectreStatus getContainer (SizeProperty containerDim,
                            spectre::SpectreTypeOutput type,
                            container::Output &destination) override;

                    virtual std::vector<SpectreTypeOutput> getSupportedTypeList() const override;

                private:
                    /// List of supported intermediate data types.
                    static const std::set<SpectreTypeOutput> S_TYPES;

                };
            }

        }
    }
}
