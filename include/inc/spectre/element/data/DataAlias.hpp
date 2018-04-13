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

#include <spectre/element/data/Data.hpp>
#include <spectre/element/data/TransformStatus.hpp>

namespace spectre
{
    namespace element
    {
        namespace data
        {

            template <typename T, typename T1>
            class TransformFunctor;

            /**
            *  Scalar data element used for alias data transformation
            */
            template < typename T, class Alias >
            class DataAlias : public Data<  T >
            {
            public:

                DataAlias (std::shared_ptr<Alias> alias,
                           const std::string& strId,
                           const std::string& activationCode)
                    : Data<T> (std::vector<float>(), strId, activationCode, DataDescriptor<T>()), m_alias (alias)
                {  }

                virtual ~DataAlias()
                { }

                /**
                *   Retrieve alias element
                */
                std::shared_ptr<Alias> getAlias()
                {
                    return m_alias;
                }

                virtual SpectreStatus serialize (std::vector<uint8_t> &output) const override
                {
                    return Data<T>::serialize (output);
                }

            protected:
                std::shared_ptr<Alias> m_alias;
                std::shared_ptr<TransformFunctor < Data< T >, Alias >> m_forward;
                std::shared_ptr<TransformFunctor < Alias, Data< T > >> m_revert;
            };
        }
    }
}
