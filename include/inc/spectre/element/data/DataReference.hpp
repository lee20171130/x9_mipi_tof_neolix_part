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

#include <spectre/element/data/Data.hpp>

namespace spectre
{
    namespace adapter
    {
        class Adapter;
    }

    namespace element
    {
        namespace data
        {

            /**
            *  Elementary data type class
            */
            template < typename T >
            class DataReference : public Data<T>
            {
            public:

                virtual ~DataReference();

                DataReference (std::vector<T> values, std::string strId,
                               const std::string &activationCode = "",
                               const DataDescriptor<T> &dataDescriptor = DataDescriptor<T>());

                virtual SpectreStatus serialize (std::vector<uint8_t> &output) const override;

                virtual SpectreStatus deSerialize (const std::vector<uint8_t> &input, size_t &idx) override;

                virtual SpectreStatus getValues (std::vector<T> &values, const std::string &activationCode = "") const override;

                virtual SpectreStatus setValues (const std::vector<T> &values, const std::string &activationCode = "") override;

                /*
                * Sets a specific Adapter class as a local observer to forward reference changes.
                *
                * @param observer Reference changes are forward to the preset observer.
                * @return Status of operation.
                */
                virtual SpectreStatus setObserver (adapter::Adapter *observer);

                /*
                * Removes a specific Adapter class as a local observer.
                *
                * @param observer Reference changes are forward to the preset observer.
                * @return Status of operation.
                */
                virtual SpectreStatus removeObserver ();

                // ----------------------------------------------------------------------------------------------
                // Level 2: Binary Integration
                // ----------------------------------------------------------------------------------------------

                /**
                *   Return handle to the reference data element
                *
                *   @param Handle to the first stored element in the linear data memory scope.
                *   @param acvitvationCode Overwrites inherent data activation code.
                *   @return Status of operation.
                */
                virtual SpectreStatus queryDataHandle (T **handle, const std::string &activationCode = "");

                /**
                *   Sets the data handle of the respective element.
                *
                *   The caller is repsonsible to verify that the memory assigned to
                *   the handle is properly managed. The pointer and the assigned
                *   memory scope muste be valid during runtime, otherwise the system
                *   behaviour is undefined. In case of inproper usage pmdtechnologies gmbh
                *   does not make any warranties of any kind.
                *
                *   @param handle Data handle to the externally managed data area.
                *   @param acvitvationCode Overwrites inherent data activation code.
                *   @return Status of operation.
                */
                virtual SpectreStatus setDataHandle (T *handle, const std::string &activationCode = "");

                /**
                *   Syncronizes the internal data value container with the reference handle.
                */
                void sync();

                virtual SpectreTypeElement  getElementType () const override;

                virtual Element *clone() const override;

            protected:

                virtual T *getDataHandle() override;

                T *m_ref;                       //< Rerence external data value handle.
                adapter::Adapter *m_observer;   //< Handle to the external observer class, which registers reference changes

            };
        }
    }
}
