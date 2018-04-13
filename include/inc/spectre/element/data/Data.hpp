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
#include <memory>
#include <spectre/element/data/DataBase.hpp>

namespace spectre
{
    namespace element
    {
        namespace data
        {

            template<typename T>
            class DataDescriptor;

            /**
            *  Data type class acting as a storage for a set numeric values.
            */
            template < typename T >
            class Data : public DataBase
            {
            public:
                virtual ~Data();

                Data (std::vector<T> values, const std::string &strId, const std::string &activationCode = "");

                Data (std::vector<T> values, const std::string &strId, const std::string &activationCode,
                      const DataDescriptor<T> &dataDescriptor);

                Data (const Data<T> &other);

                virtual SpectreStatus serialize (std::vector<uint8_t> &output) const override;

                virtual SpectreStatus deSerialize (const std::vector<uint8_t> &input, size_t &idx) override;

                using Element::deSerialize;

                /*  Returns stored data element values by value.
                *
                * @param values Return values as copy of the internally stored values.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return Status of operation.
                */
                virtual SpectreStatus getValues (std::vector<T> &values,
                                                 const std::string &activationCode = "") const;

                /*  Returns stored data element values at a specific index.
                *
                * @param value Return values as copy of the internally stored values.
                * @param acvitvationCode Overwrites inherent data activation code.
                * @param index Position of set operation of internaly stored data.
                *
                * @return Status of operation.
                */
                virtual SpectreStatus getValue (T &value,
                                                const std::string &activationCode = "",
                                                uint32_t index = 0) const;

                /**
                 * Gets the stored data element values as a constant reference
                 * If the Data is altered the contents of the reference might change, or
                 * the reference itself might be invalidated.
                 *
                 * If the operation fails a reference to an empty vector is returned.
                 *
                 * @param status status of operation
                 * @param activationCode activation code
                 *
                 * @return constant reference to values
                 */
                virtual const std::vector<T> &getValuesRef (SpectreStatus &status,
                        const std::string &activationCode = "") const;

                /*  Set data element values.
                *
                * @param Data vector to be stored. Must be of equal type and size as the stored element.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return Status of operation.
                */
                virtual SpectreStatus setValues (const std::vector<T> &values,
                                                 const std::string &activationCode = "");

                /*  Set data element values at a specififc index.
                *
                * @param Data value to be stored. Must be of equal type as the stored element.
                * @param acvitvationCode Overwrites inherent data activation code.
                * @param index Position of set operation of internaly stored data.
                *
                * @return Status of operation.
                */
                virtual SpectreStatus setValue (const T value,
                                                const std::string &activationCode = "",
                                                uint32_t index = 0);

                /*  Returns minimum data limits. Copied by value.
                *
                * @param minValue Minimum permittable data value.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return Status of operation.
                */
                virtual SpectreStatus getMinLimit (T &minValue, const std::string &activationCode = "");

                /*  Returns maximum data limits. Copied by value.
                *
                * @param maxValue Maximum permittable data value.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return Status of operation.
                */
                virtual SpectreStatus getMaxLimit (T &maxValue, const std::string &activationCode = "");

                /*  Returns Data precision used for storage efficiency. Copied by value.
                *
                * @param precision Precision value used to determine storage efficiency.
                * @param acvitvationCode Overwrites inherent data activation code.
                *
                * @return Status of operation.
                */
                virtual SpectreStatus getPrecision (T &precision, const std::string &activationCode = "");

                /**
                 * Gets the size of the value list
                 *
                 * @return size of value list
                 */
                size_t size() const;

                virtual SpectreTypeElement  getElementType () const override;

                /**
                * Gets a copy of the data descriptor used
                *
                * @return data descriptor
                */
                const DataDescriptor<T> &getDataDescriptor() const;

                virtual Element *clone() const override;

                /**
                * Compares this data element configuration with another.
                * Returns true if both container equal in version, format,
                * DataDescriptor, endianess and number of the internaly
                * stored data values.
                *
                * @param cmp Data to be compared against.
                *
                * @return true if container are identical.
                */
                virtual bool equalCfg (const Element &cmp) const override;

            protected:
                /**
                * Return handle to the data element
                *
                * @return Handle to the first stored element in the linear data memory scope.
                */
                virtual T *getDataHandle();

                /**
                * Determines if given values complies with the stated minimum and maximum precision limits.
                *
                * @return True if values do comply, else false.
                */
                virtual bool verifyValues (const std::vector<T> &value);

                /**
                * Binarizes values, by the means of native data temporary data type of equal size.
                *
                * @return Status of operation.
                */
                template<typename U>
                SpectreStatus binarize (std::vector<uint8_t> &output, const std::vector<T> &values) const;

                /**
                * Debinarizes values, by the means of native data temporary data type of equal size.
                *
                * @param output Output data of the binraization process.
                * @param values Handle to bthe values data to binraize from.
                * @return Status of operation.
                */
                template<typename U> SpectreStatus deBinarize (const std::vector<uint8_t> &input, size_t &idx);

                /**
                * Serializes the data element and retrieves the binary descriptor from the data element.
                *
                * @param input Input data to read from
                * @param values Handle to the values data container the debinatized data is written on.
                * @return True if header file was set correctly. else returns false.
                */
                virtual bool setHeader (std::vector<uint8_t> &output) const override;

                virtual SpectreStatus readHeader (const std::vector<uint8_t> &input,
                                                  size_t &idx) override;

                /**
                 * Serializes the type descriptor of this element
                 *
                 * @param output output for serialization
                 */
                void serializeTypeDescriptor (std::vector<uint8_t> &output) const;


                /**
                 * Reads the type descriptor from the serialized stream
                 *
                 * @param input input stream
                 * @param idx index in stream
                 *
                 * @return status
                 */
                SpectreStatus readTypeDescriptor (const std::vector<uint8_t> &input, size_t &idx);

            protected:
                /// Data descriptor to describe minimum bit size for data storage.
                std::unique_ptr<DataDescriptor<T>> m_dataDescriptor;
                /// Value data container used to store data in linear order.
                std::vector<T> m_values;
                friend class container::Container;
            };
        }
    }
}
