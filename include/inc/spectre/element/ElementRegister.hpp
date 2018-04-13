
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

#include <map>
#include <vector>
#include <memory>
#include <limits>
#include <set>

#include <spectre/element/container/Container.hpp>
#include <spectre/element/RegisterStatus.hpp>

namespace spectre
{
    namespace element
    {

        struct ContainerKey;
        struct RegisterEntry;

        /**
        *  Librarian class to manage fundamental element type library.
        *  Corresponds to the singelton design pattern.
        */
        class ElementRegister
        {
        public:

            /**
            *   Retrieves instance to the library singleton instance handler.
            *
            *   @return Return handle.
            */
            static ElementRegister &getInstance();


            /**
            *   Verifies the validity of the acces code for a specific data element.
            *
            *   @param dataElement pointer to the data element
            *   @param accessCode to be verified
            *   @return true if accessCode is valid
            */
            bool verifyAccess (const Element *data, const std::string &activationCode) const;

            /**
            *   Verifies that the stated code corresponds to the level two access level.
            *
            *   @param accessCode to be verified
            *   @return true if accessCode is valid
            */
            bool verifyAccessLevelTwo (const std::string &activationCode) const;


            /**
            *   Verifies that the stated code corresponds to the level three access level.
            *
            *   @param accessCode to be verified
            *   @return true if accessCode is valid
            */
            bool verifyAccessLevelThree (const std::string &activationCode) const;


            /**
            *   Retrieves access level from the registration data base.
            *
            *   @param dataElement pointer to the data element.
            *   @return True if the accessCode is in compliance with the registered access level.
            */
            access::AccessLevel getAccessLevel (std::string activationCode) const;


            /**
            *   Retrieves Root Id value from register stack.
            *
            *   @param data Registered data element.
            *   @param strId If element is registered the corresponding string Id value is returned, else an empty string is returned.
            *   @return Status of registration.
            */
            RegisterStatus getId (const Element *data, std::string &strId) const;

            /**
            *   Verifies if data element is already registered.
            *
            *   @param data Element to be verified
            *   @param rootId Id of the parent element, UINT32_MAX if element is already root.
            *   @return Status of registration.
            */
            RegisterStatus getRoot (const Element *data, size_t *rootId) const;

            /**
            *   Verifies if data element is already registered.
            *
            *   @param rootId Id of the parent element.
            *   @return Vector list of leaf element Ids.
            */
            std::vector<size_t> getLeafId (size_t rootId) const;


            /**
             * Registers a new container in the registry
             *
             * Only certain containers are feasible for registration in the ElementRegister:
             * spectre::container::Calibration
             * spectre::container::Intermediate
             * spectre::container::Input
             * spectre::container::Output
             * spectre::container::Parameter
             *
             *
             * @param container container to register
             * @param version version
             * @param accessLevel access level
             * @param variant variant
             *
             * @return operation result
             */
            RegisterStatus registerContainer (container::Container *container,
                                              SpectreVersion version,
                                              access::AccessLevel accessLevel,
                                              uint16_t variant = 0
                                             );

            /// Element id which is used to indicate that an element is not registered
            static const size_t S_NOT_REGISTERED;

        private:
            ElementRegister();
            ElementRegister (const ElementRegister &) = delete;
            ElementRegister &operator= (const ElementRegister &) = delete;
            ElementRegister (ElementRegister &&) = delete;

            /**
            *   Verifies if data element is already registered.
            *
            *   @param data Element to be verified
            *   @return True if data element corresponds with registry entry value
            */
            bool verifyData (const Element *data) const;

            /**
             * Checks if the passed container is of a valid type for registerContainer
             *
             * @param container container
             * @param types valid types
             *
             * @return true if the container has a valid type, false otherwise
             */
            template<typename T>
            bool isValidContainer (const container::Container *container, const T &types) const;

            /**
             * Gets the subtype of a valid container
             *
             * @param container container
             * @param types valid types
             *
             * @return subtype of container
             */
            template<typename T>
            uint16_t getSubType (const container::Container *container, const T &types) const;

            /**
             * Marks a Element as registered
             *
             * @param element element
             * @param id assigned id
             */
            void markRegistered (Element &element, size_t id) const;

            /**
             * Registers the children of newly added root container type
             *
             * @param currentNode current node for recursion
             * @param rootId id of root container
             * @param accessLevel access level
             */
            void registerNewChildren (container::Container &currentNode, size_t rootId,
                                      access::AccessLevel accessLevel);

            /**
             * Registers the children of a root container of an already registered type
             *
             * @param currentNode current node for recursion
             * @param currentId current element id for recursion
             * @param rootId id of root container
             * @param accessLevel access level
             *
             * @return registration status
             */
            RegisterStatus reRegisterChildrenRec (container::Container &currentNode, size_t &currentId,
                                                  size_t rootId, access::AccessLevel accessLevel) const;
            /**
             * Registers the children of a root container of an already registered type
             *
             * @param currentNode current node for recursion
             * @param rootId id of root container
             * @param accessLevel access level
             *
             * @return registration status
             */
            RegisterStatus reRegisterChildren (container::Container &currentNode,
                                               size_t rootId, access::AccessLevel accessLevel) const;

            /**
             * Verifies that a given activationCode is suitable for a given access level
             * An activationCode is suitable for a level, if it grants access to this level or any
             * higher level
             *
             * @param level level to check
             * @param activationCode activation code
             *
             * @return true if code is suitable, false other
             */
            bool verifyLevelAccess (access::AccessLevel level, const std::string &activationCode) const;

        private:
            std::unique_ptr<std::set<ContainerKey> > m_registeredContainer;
            std::unique_ptr<std::vector<RegisterEntry> > m_library;

        private:
            static std::unique_ptr<ElementRegister> S_INSTANCE;
        };
    }
}
