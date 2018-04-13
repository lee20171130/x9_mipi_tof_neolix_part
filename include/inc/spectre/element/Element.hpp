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
#include <cstdint>

#include <spectre/SpectreVersion.hpp>
#include <spectre/SpectreStatus.hpp>
#include <spectre/SpectreTypeElement.hpp>
#include <spectre/access/AccessLevel.hpp>

namespace spectre
{
    namespace element
    {
        namespace container
        {
            class Container;
        }


        /**
        *  Base elementary data type class
        */
        class Element
        {
            friend class container::Container;
            friend class ElementRegister;

        public:
            /**
            * Destructor of the base data element
            */
            virtual ~Element();

            /**
            * Serializes the data element and retrieves the binary descriptor from the data element.
            *
            * @param output Comprises the compressed element data from the serialization
            * @return Status of Operation.
            */
            virtual SpectreStatus serialize (std::vector<uint8_t> &output) const = 0;

            /**
            * Deserialization
            * The parameter idx is used as start index for deserialization. After a successful
            * operation idx is updated to point after the current Element.
            *
            * @param input Comprises the compressed element data to be deserialized.
            * @param idx Index of the first element in input for deserialization
            * @return Status of Operation.
            */
            virtual SpectreStatus deSerialize (const std::vector<uint8_t> &input, size_t &idx) = 0;

            /**
            * Retrieves activation code from the data element.
            *
            * @return Activation code to set the appropriate access level.
            */
            std::string getActivationCode() const;

            /**
            * Retrieves activation code from the data element.
            *
            * @param activationCode Determines the appropriate access level.
            */
            void setActivationCode (const std::string &activationCode);

            /**
            * Retrieves registration status of the data element.
            *
            * @return True if data element is registred.
            */
            bool isRegistered() const;

            /**
            * Retrieves the data type id.
            *
            * @return Status of Operation
            */
            virtual SpectreTypeElement  getElementType () const = 0;

            /**
            * Retrieves the ID name as std::string value.
            *
            * @return ID name as std::string value.
            */
            std::string getStrId() const;

            void setStrId (const std::string &strId);

            /**
            * Creates a copy of the current Element
            *
            * @return Copied element
            */
            virtual Element *clone() const = 0;

            /**
            * Compares this data element configuration with another.
            * Returns true if both container equal in version and string id.
            *
            * @param cmp Data to be compared against.
            *
            * @return true if container are identical.
            */
            virtual bool equalCfg (const Element &cmp) const;

        protected:
            /**
            * Protected constructor of the base data element.
            *
            * @param activationCode Necessary to activate specific access level.
            * @param identification parameter as clear string name tag.
            */
            Element (const std::string &strId, const std::string &activationCode = "");

            /**
            * Validate the activation Code and return appropriate access level.
            *
            * @return The test results
            */
            spectre::access::AccessLevel getAccessLevel() const;

            /**
            * Sets the data element binarization header.
            *
            * @param output Comprises the compressed element data from the serialization
            * @return True if operation was successful.
            */
            virtual bool setHeader (std::vector<uint8_t> &output) const = 0;

            /**
            *   Reads the header and returns the index of the first data entry
            *   After a successful operation idx is adjusted to point to the first element after the
            *   header
            *
            *   @param input Comprises the compressed element data from the serialization including the header
            *   @param idx index of the first header entry
            *   @return operation result
            */
            virtual SpectreStatus readHeader (const std::vector<uint8_t> &input,
                                              size_t &idx) = 0;

            /**
            * Sets the identification value.
            *
            * @param id Registered identification number.
            * @return True if operation was successfull.
            */
            virtual bool setId (size_t id);


            /**
             * choose the most meaningful activation code available
             *
             * @param activationCode local activation code of the calling function.
             * @return the most meaningful activation code available
             *
             */
            std::string chooseActivationCode (const std::string &activationCode) const;


        protected:
            size_t m_id;                            //< Identifaction value within the registry.
            SpectreVersion m_version;               //< Spectre version id.
            std::string m_strId;                    //< Element identifaction tag as clear string value.
            std::string m_activationCode;           //< Element specific activation code to enable user access.
            std::string m_docId;                    //< Documentation tag ID.
        };

    }
}
