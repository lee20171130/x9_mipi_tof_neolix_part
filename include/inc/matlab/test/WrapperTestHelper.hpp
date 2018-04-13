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

#include <stdint.h>
#include <vector>
#include <memory>

#include <gtest/gtest.h>

#include <spectre/test/AstonBuilderTestUtils.hpp>
#include <spectre/SpectreTypeCalibration.hpp>

// ****************************************************************
// "Glue code" so that the automatically generated files
// included in maspectre.i can be used inside unit tests
template<typename T>
class MatlabWrapperMarker
{
public:
    virtual ~MatlabWrapperMarker() {
    }

    inline void setType (T type)
    {
        m_type = type;
    }

    inline T getType()
    {
        return m_type;
    }

    inline uint16_t getVariant() const
    {
            return m_variant;
    }
    
    inline void setVariant(uint16_t variant)
    {
            m_variant = variant;
    }
    
private:
    T m_type;
    uint16_t m_variant;
};

template<typename T>
struct matlab_matrix
{
    size_t rows, columns;
    T *a;
    std::shared_ptr<T> aHolder;

    matlab_matrix (size_t aRows, size_t aColumns, T *aA)
        : rows (aRows), columns (aColumns), a (aA), aHolder(a, std::default_delete<T[]>()) {}

    matlab_matrix (size_t aRows, size_t aColumns, const std::vector<T> &values)
        :rows(aRows), columns(aColumns), a(nullptr)
        {
            assert(aRows * aColumns == values.size());
            a = new T[values.size()];
            aHolder = std::shared_ptr<T>(a, std::default_delete<T[]>());
            memcpy(a, values.data(), values.size() * sizeof(T));
        }
    
    matlab_matrix()
        : matlab_matrix (0, 0, nullptr)
    {}

    bool isValid()
    {
        return rows > 0 && columns > 0 && a != nullptr;
    }
};

template<typename T>
matlab_matrix<T> makeMatrix (size_t rows, size_t columns, T *a)
{
    return matlab_matrix<T> (rows, columns, a);
}

inline void mexWarnMsgIdAndTxt (const char *, const char *) {}
inline void mexPrintf (const char *, ...) {}
// ****************************************************************

/// Compare functor for the Matlab wrapper setter tests
/**
 * The functor compares the values of Data<T> with the values contained inside RttiVariant.
 * The variant is expected to contain a std::string (for T = char) or a matlab_matrix<T> in all
 * other cases, which is subsequently unwrapped.
 */
struct WrapperSetterCmp : public DataBaseCmp
{
    template<typename T>
    void operator() (const std::shared_ptr<spectre::element::data::Data<T> > &handle) const
    {
        std::vector<T> values;
        ASSERT_SUCCESS(handle->getValues(values, accessCodeInternal));
        check(values, handle->getDataDescriptor().precision);
    }

    void check (const std::vector<char> &values, char) const
    {
        std::string str(values.begin(), values.end());
        auto compareData = dynamic_cast<RttiVariant<std::string>*>(compareVariant);
        ASSERT_TRUE(compareData != nullptr);
        ASSERT_EQ(compareData->value, str);
    }

    template<typename T>
    void check (const std::vector<T> &values, T prec) const
    {
        auto compareData = dynamic_cast<RttiVariant<matlab_matrix<T> >*>(compareVariant);
        ASSERT_TRUE(compareData != nullptr);
        size_t elements = compareData->value.rows * compareData->value.columns;
        ASSERT_EQ(elements, values.size());

        std::vector<T> refValues(elements);
        memcpy(refValues.data(), compareData->value.a, sizeof(T) * elements);

        compare(refValues, values, prec);
    }

    RttiVoid *compareVariant;
};


