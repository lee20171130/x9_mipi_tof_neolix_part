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
    namespace element
    {
        namespace data
        {

            /**
            *  Element scalar data type class. Stores and handles only scalar data types
            */
            template < typename T >
            class DataScalar : public Data<T>
            {
            public:
                virtual ~DataScalar()
                {
                };

                DataScalar (T value, const std::string& strId, const std::string& activationCode = "",
                            DataDescriptor<T> dataDescriptor = DataDescriptor<T>())
                    : Data<T> (std::vector<T> (1, value), strId, activationCode, dataDescriptor)
                {
                };

                /*  Returns stored data element values by value.
                *
                *   @param values Return values as copy of the internally stored values.
                *   @return Status of operation.
                */
                SpectreStatus getValue (T &value,
                                        const std::string &activationCode = "") const;
                using Data<T>::getValue;

                /*  Returns stored data element values.
                *
                *   @param Data vector to be stored. Must be of equal type and size as the stored element.
                *   @param acvitvationCode Overwrites inherent data activation code.
                *   @return Status of operation.
                */
                SpectreStatus setValue (const T value, const std::string &activationCode = "");
                using Data<T>::setValue;


                virtual SpectreTypeElement  getElementType () const override;

                virtual Element *clone() const override;

            protected:
                /**
                *   Determines if given values complies with the stated minimum and maximum precision limits.
                *
                *   @return True if values do comply, else false.
                */
                virtual bool verifyValue (const T &value) const;

            private:
                virtual SpectreStatus getValues (std::vector<T> &values, const std::string &activationCode = "") const override;
                virtual SpectreStatus setValues (const std::vector<T> &values, const std::string &activationCode = "") override;
            };
        }
    }
}
