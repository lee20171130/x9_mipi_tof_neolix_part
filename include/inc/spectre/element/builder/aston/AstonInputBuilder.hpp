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

#include <spectre/element/builder/InputBuilder.hpp>
#include <set>
#include <map>

namespace spectre
{
    namespace element
    {
        namespace builder
        {
            namespace aston
            {

                /**
                *  Builder class for aston input data container
                */
                class AstonInputBuilder : public InputBuilder
                {

                protected:

                    std::vector<SpectreTypeInput> m_type;         ///< List of supported input data types.


                public:

                    /**
                    *   Protected Constructor of the aston input data builder class.
                    *
                    *   @param activationCode Necessary to activate specific access level.
                    */
                    explicit AstonInputBuilder (const std::string &activationCode = "");

                    /**
                    *   Destructor of the input data builder aston class.
                    */
                    virtual ~AstonInputBuilder();

                    virtual spectre::SpectreStatus getContainer (const std::vector<uint8_t> &input,
                            container::Input &destination) const override;

                    virtual spectre::SpectreStatus getContainer (SizeProperty containerDim,
                            spectre::SpectreTypeInput type,
                            container::Input &destination) const override;

                    virtual spectre::SpectreStatus getContainer (SizeProperty containerDim,
                            spectre::SpectreTypeInput type,
                            FrameSetCompositon frameSetComposition,
                            container::Input &destination) const override;



                    virtual std::vector<SpectreTypeInput> getSupportedTypeList() const override;

                    /**
                     * Gets the frameset composition associated to the passed variant
                     * If the variant is unknown, an empty composition is returned
                     *
                     * @param type submodule type
                     * @param variant variant
                     *
                     * @return associated frameset composition
                     */
                    virtual FrameSetCompositon forVariant (SpectreTypeInput type, uint16_t variant) const override;

                private:
                    static const std::set<SpectreTypeInput> S_TYPES;

                    static const std::map<FrameSetCompositon, uint16_t> S_I1P4_VARIANTS;
                    static const std::map<FrameSetCompositon, uint16_t> S_I1P4P4_VARIANTS;

                    /**
                    * Validates if two FrameSetDefinitions are equal.
                    *
                    * @param a First FrameSetDefinition
                    * @param b Second FrameSetDefinition
                    *
                    * @return true if FrameSetDefinitions are identical, else false.
                    */
                    bool validateFrameComposition (const FrameSetCompositon &a, const FrameSetCompositon &b) const;

                    /**
                    * Retrieves FrameSetComposition from serialized data binary container.
                    *
                    * @param source Source input data container to be retrieve FrameSetComposition.
                    * @param inputType Type of input container.
                    */
                    FrameSetCompositon deSerializeFrameSetComposition (const std::vector<uint8_t> &input, spectre::SpectreTypeInput type) const;

                };
            }
        }
    }
}
