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

#include <vector>
#include <memory>
#include <map>

#include <spectre/element/Element.hpp>
#include <spectre/SpectreCommon.hpp>

namespace spectre
{

    namespace adapter
    {
        class Adapter;
    }


    namespace element
    {

        class ElementRegister;

        namespace container
        {

            /**
            *  Base container data type class
            */
            class Container : public Element
            {
                friend class Calibration;
                friend class spectre::adapter::Adapter;
                friend class element::ElementRegister;

            public:
                /**
                * Constructor of the base container data element
                */
                Container (const std::string &strId = "",
                           const std::string &activationCode = "",
                           std::vector<std::shared_ptr<Element>> dataList = std::vector<std::shared_ptr<Element>>());

                /**
                * Destructor of the base container data element
                */
                virtual ~Container();

                virtual SpectreStatus serialize (std::vector<uint8_t> &output) const override;

                /**
                * Retrieves related spectre version number.
                *
                * @return Spectre version id.
                */
                SpectreVersion getVersion() const;

                /**
                * Retrieves a copy of the list of sub data elements.
                * If the return value is != SpectreStatus::SUCCESS the dataList
                * is empty.
                *
                * @param elements list of sub data elements.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return SUCCESS if element is found, otherwise an error indicator
                */
                SpectreStatus getElements (std::vector<std::shared_ptr<Element>> &elements,
                                           const std::string &activationCode = "") const;

                /**
                 * Queries a data element in the container or in its hierarchy
                 * If the return value is != SpectreStatus::SUCCESS the value of dataHandle
                 * is undefined.
                 *
                 * @param elementPath path of element
                 * @param elementHandle reference where a handle to the element is stored
                 * @param acvitvationCode Overwrites inherent data activation code.
                 *
                 * @return SUCCESS if element is found, otherwise an error indicator
                 */
                SpectreStatus queryElement (const std::vector<std::string> &elementPath,
                                            std::shared_ptr<Element> &elementHandle,
                                            const std::string &activationCode = "") const;

                /**
                * Queries the type defintion of the internal stored data.
                * element in the container or in its hierarchy.
                * If the query is unsuccessfull the return value is a nullptr.
                *
                * @param dataPath path of element
                * @param typeData Type of the internally stored data element.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return Status of Operation
                */
                SpectreStatus queryTypeElement (const std::vector<std::string> &dataPath,
                                                SpectreTypeElement &typeData,
                                                const std::string &activationCode = "") const;

                /**
                * Queries the value from internal data element in the
                * container or in its hierarchy. If the query is unsuccessfull
                * the returned data vector is empty.
                *
                * @param dataPath path of element
                * @param values Return values as copy of the internally stored values.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return Status of Operation
                */
                template<typename T>
                SpectreStatus queryDataValues (const std::vector<std::string> &dataPath,
                                               std::vector<T> &values,
                                               const std::string &activationCode = "") const;

                /**
                * Return a constant reference the values from a data element in the
                * container or in its hierarchy.
                * If the query is unsuccessful the value of the reference is empty.
                *
                * If the container or the udnerlying Data<T> instance is altered
                * the data to might change or the reference itself might become invalid.
                *
                * @param dataPath path of element
                * @param status status of operation
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return reference to values
                */
                template<typename T>
                const std::vector<T> &queryDataValuesRef (const std::vector<std::string> &dataPath,
                        SpectreStatus &status,
                        const std::string &activationCode = "") const;



                /**
                * Queries a scalar value from internal data element at a specific index
                * in the container or in its hierarchy. If the query is unsuccessfull
                * the returned scalar is zero.
                *
                * @param dataPath path of element
                * @param value Return value as copy of the internally stored values.
                * @param acvitvationCode Overwrites inherent data activation code.
                * @param index Position of query operation of internaly stored data.
                *
                * @return Status of Operation
                */
                template<typename T>
                SpectreStatus queryDataValue (const std::vector<std::string> &dataPath,
                                              T &value,
                                              const std::string &activationCode = "",
                                              uint32_t index = 0) const;

                /**
                * Sets the value in an internal data element in the
                * container or in its hierarchy. If the query is unsuccessfull
                * the returned data vector is subsequent Status message is returned.
                *
                * @param dataPath path of element
                * @value values Return values as copy of the internally stored values.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return Status of Operation
                */
                template<typename T>
                SpectreStatus setDataValues (const std::vector<std::string> &dataPath,
                                             const std::vector<T> &values,
                                             const std::string &activationCode = "");


                /**
                * Sets the value in an internal data element at a specific index
                * in the container or in its hierarchy. If the query is unsuccessfull
                * the returned data vector is subsequent Status message is returned.
                *
                * @param dataPath path of element
                * @value value Return value as copy of the internally stored values.
                * @param acvitvationCode Overwrites inherent data activation code.
                * @param index Position of set operation of internaly stored data.
                *
                * @return Status of Operation
                */
                template<typename T>
                SpectreStatus setDataValue (const std::vector<std::string> &dataPath,
                                            T value,
                                            const std::string &activationCode = "",
                                            uint32_t index =  0);

                /**
                * Sets a handle to the reference data element
                *
                * @param dataPath path of element
                * @param handle Data handle to the externally managed data area.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return SUCCESS if element is found, otherwise an error indicator
                */
                template<typename T>
                SpectreStatus setDataHandle (const std::vector<std::string> &dataPath,
                                             T *handle,
                                             const std::string &activationCode = "");

                /**
                 * Gets the number of children of this container
                 *
                 * @return number of children
                 */
                virtual size_t getNumberOfChildren() const;

                /**
                * Gets the element type specifier of this container
                *
                * @return type specifier
                */
                virtual SpectreTypeElement  getElementType () const override;

                virtual Element *clone() const override;

                /**
                 * Removes a given element from the container
                 *
                 * @param dataPath data path of element to remove
                 *
                 * @return status of operation
                 */
                SpectreStatus removeElement (const std::vector<std::string> &dataPath);

                /**
                * Retrieves variant specifier from container data type
                * Variant indicate that the content of a specific container
                * corresponds to the default set, but the internal data
                * representation differs.
                * The specific variant value is set during the registration
                * process. The default variant is 0.
                *
                */
                uint16_t getVariant() const;

            protected:

                /**
                * Retrieves a copy of the list of sub data elements.
                * If the return value is != SpectreStatus::SUCCESS the dataList
                * is empty.
                *
                * @return list of sub data elements.
                */
                std::vector<std::shared_ptr<Element>> getElements() const;

                /**
                 * Recursivly queries an element by traversing the container hierarchy along the
                 * given dataPath
                 *
                 * @param elementPath path to follow
                 * @param idx index of current path element
                 *
                 * @return handle to specified element, may be empty if element does not exist
                 */
                std::shared_ptr<Element> queryElementRec (const std::vector<std::string> &elementPath,
                        size_t idx) const;

                /**
                 * Finds a data in this container
                 *
                 * @param id id of element
                 *
                 * @return handle to element, may be empty if element does not exist
                 */
                std::shared_ptr<Element> findElement (const std::string &id) const;


                virtual SpectreStatus deSerialize (const std::vector<uint8_t> &input, size_t &idx) override;

                /**
                * Queries a handle to the internal data from a specific data
                * element in the container or in its hierarchy.
                * If the query is unsuccessfull the return value is a nullptr.
                *
                * @param dataPath path of element
                * @return Handle to the internal data of a specific data elemnt
                */
                template<typename T>
                T *queryValueHandle (const std::vector<std::string> &dataPath);

                /**
                * Queries the size handle to the internal data from a specific
                * data element in the container or in its hierarchy.
                * If the query is unsuccessfull invalid the return value is zero.
                *
                * @param dataPath path of element
                * @return Handle to the internal data of a specific data elemnt
                */
                template<typename T>
                size_t queryValueSize (const std::vector<std::string> &dataPath);

                /**
                * Sets the identification value.
                *
                * @param id Registered identification number.
                * @return True if operation was successfull.
                */
                virtual bool setId (size_t id) override;

                virtual bool setHeader (std::vector<uint8_t> &output) const override;

                virtual SpectreStatus readHeader (const std::vector<uint8_t> &input,
                                                  size_t &idx) override;

                /**
                * Add data element to the container.
                *
                * @param dataElement Data element to be added to the container
                * @return Status of Operation
                */
                SpectreStatus pushBack (std::shared_ptr<Element> dataElement);

                SpectreStatus deSerializeCustom (const std::vector<uint8_t> &input,
                                                 size_t &idx) const;

                /**
                * Compares this container configuration with another.
                * Returns true if both container equal in version and variant.
                *
                * @param cmp Container to be compared against.
                *
                * @return true if container are identical.
                */
                virtual bool equalCfg (const Element &cmp) const override;

            protected:
                std::vector<std::shared_ptr<Element> > m_elementList;   //< List of composed sub elements.
                uint16_t m_variant;                                     //< variant specifier

                Container *queryParent (const std::vector<std::string> &dataPath, size_t idx);
                const Container *queryParent (const std::vector<std::string> &dataPath, size_t idx) const;

            };
        }
    }
}
