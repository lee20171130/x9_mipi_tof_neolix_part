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

#include <gmock/gmock.h>

#include <spectre/SpectreCommon.hpp>
#include <spectre/element/Element.hpp>
#include <spectre/element/data/DataDescriptor.hpp>
#include <spectre/element/data/Data.hpp>
#include <spectre/element/data/DataDynSize.hpp>
#include <spectre/element/data/DataVarDef.hpp>
#include <spectre/element/container/Container.hpp>
#include <spectre/SpectreTypeFrameSet.hpp>
#include <spectre/SpectreStatus.hpp>
#include <memory>
#include <limits>
#include <spectre/access/intern/AccessCode.hpp>
#include <type_traits>
#include <spectre/DataPath.hpp>

namespace spectre
{
    namespace element
    {
        namespace container
        {
            class Container;
        }
    }
}

/**
 * Asserts that the parameter is SpectreStatus::SUCCESS
 *
 * @param x SpectreStatus
 */
#define ASSERT_SUCCESS(x) ASSERT_EQ(spectre::SpectreStatus::SUCCESS, (x))

/// Vector of elements
using ElementVec = std::vector<std::shared_ptr<spectre::element::Element> >;
/// Handle to a element
using DataHandle = std::shared_ptr<spectre::element::Element>;

/// Base class to emulate void* with RTTI
class RttiVoid
{
public:
    virtual ~RttiVoid() {}
};

/// Different data types
enum class DataType { STD, DYN, VAR, CNST, OTHER };

/// Helper class to store information about Data<T> and its subclasses
template<typename T>
class DataInfo : public RttiVoid
{
public:
    DataInfo (DataType aType, size_t aSize,
              DataPath aPath,
              spectre::element::data::DataDescriptor<T> aDescriptor)
        : path (aPath), type (aType), size (aSize),
          descriptor (aDescriptor)
    {}

    virtual ~DataInfo() {}

    DataPath path;
    DataType type;
    size_t size;
    spectre::element::data::DataDescriptor<T> descriptor;
};

/// Helper class which can hold (unrelated) different data types
template<typename T>
class RttiVariant : public RttiVoid
{
public:
    explicit RttiVariant (const T &aValue)
        : value (aValue)
    {}
    virtual ~RttiVariant() {}

    T value;
};


/**
 * Recursivley asserts that the container contains no other than
 * the ones in paths
 *
 * @param paths known paths
 * @param container container to check
 */
void checkUnknownPathsRec (std::vector<DataPath> paths,
                           const spectre::element::container::Container &container);

/// Functor to test if a handle to a Data<T> corresponds to a stored DataInfo structure
/**
 * This functor can be used together with the dispatchElementToFunctor utility function.
 */
struct TypeTester
{
    explicit TypeTester (RttiVoid *aDataInfo)
        : dataInfo (aDataInfo)
    {}

    template<typename T>
    void operator() (const std::shared_ptr<spectre::element::data::Data<T> > &element) const
    {
        DataInfo<T> *info = dynamic_cast<DataInfo<T>*> (dataInfo);
        ASSERT_TRUE (info != nullptr);

        switch (info->type)
        {
            case DataType::DYN:
                ASSERT_TRUE (std::dynamic_pointer_cast<spectre::element::data::DataDynSize<T> > (element).get() != nullptr);
                break;
            case DataType::VAR:
                ASSERT_TRUE (std::dynamic_pointer_cast<spectre::element::data::DataVarDef<T> > (element).get() != nullptr);
            case DataType::STD:
                ASSERT_EQ (info->size, element->size());
                break;
            case DataType::CNST:
                break;
            case DataType::OTHER:
                break;
            default:
                FAIL();
        }

    }

    RttiVoid *dataInfo;
};

/// Holds a vector<T>
template<typename T>
class ValuesHolder : public RttiVoid
{
public:
    ValuesHolder (const std::vector<T> &aValues)
        : values (aValues)
    {}

    virtual ~ValuesHolder() {}

    std::vector<T> values;
};

// ****************************************************************
// Utility methods to create a vector with random values based on a DataInfo<T> object
// call createRandomData(DataInfo<T>) -> it dispatches to the correct instance automatically
template<typename T>
std::vector<T> createRandomIntData (const DataInfo<T> &info)
{
    typename std::make_unsigned<T>::type range  =
        info.descriptor.maxValue - info.descriptor.minValue;
    std::vector<T> values;

    for (size_t i = 0; i < info.size; i++)
    {
        values.push_back (info.descriptor.minValue + (rand() % range));
    }
    return values;
}

inline std::vector<float> createRandomData (const DataInfo<float> &info)
{
    auto range = 300.f;
    auto minValue = 0.0f;

    if (!info.descriptor.isDefault())
    {
        range = info.descriptor.maxValue - info.descriptor.minValue - info.descriptor.precision;
        minValue = info.descriptor.minValue;
    }

    std::vector<float> values;
    for (size_t i = 0; i < info.size; i++)
    {
        values.push_back (minValue + ( ( (float) rand()) / ( (float) RAND_MAX / range)));
    }
    return values;
}

inline std::vector<uint16_t> createRandomData (const DataInfo<uint16_t> &info)
{
    return createRandomIntData (info);
}


inline std::vector<uint32_t> createRandomData (const DataInfo<uint32_t> &info)
{
    return createRandomIntData (info);
}

inline std::vector<uint8_t> createRandomData (const DataInfo<uint8_t> &info)
{
    return createRandomIntData (info);
}

inline std::vector<int8_t> createRandomData (const DataInfo<int8_t> &info)
{
    return createRandomIntData (info);
}


inline std::vector<char> createRandomData (const DataInfo<char> &info)
{
    static const char lut[] = "ABCDEFGHIKLMNOPQRSTUVWXYZabcdefghiklmnopqrstuvwxyz0123456789_-,.";
    std::vector<char> values;
    for (size_t i = 0; i < info.size; i++)
    {
        values.push_back (lut[rand() % (sizeof (lut) - 1)]);
    }
    return values;
}

inline std::vector<int> createRandomData (const DataInfo<int> &info)
{
    return createRandomIntData (info);
}

template<typename T>
std::vector<T> createRandomData (const DataInfo<T> &info)
{
    ADD_FAILURE();
    return std::vector<T>();
}
// ****************************************************************

/// Fills a Data<T> with random data
/**
 * This functor can be used together with the dispatchElementToFunctor utility function.
 */
struct RandomDataSetter
{
    RandomDataSetter (spectre::element::container::Container &aContainer, unsigned seed)
        : container (aContainer)
    {
        srand (seed);
    }

    template<typename T>
    void operator() (const std::shared_ptr<spectre::element::data::Data<T> > &element)
    {
        DataInfo<T> *info = dynamic_cast<DataInfo<T>*> (fieldInfo);
        if (info->type != DataType::CNST)
        {
            auto strId = element->getStrId();
            ASSERT_TRUE (info != nullptr) << " Error at " << element->getStrId();

            std::vector<T> values (createRandomData (*info));
            ASSERT_SUCCESS (container.setDataValues (info->path, values)) << " Error at " << info->path;
            ASSERT_TRUE (testData.find (info->path) == testData.end());
            testData[info->path] = std::make_shared<ValuesHolder<T> > (values);
        }
    }

    RttiVoid *fieldInfo;
    spectre::element::container::Container &container;

    std::map<DataPath, std::shared_ptr<RttiVoid> > testData;
};

/// Base class for comparison functors
struct DataBaseCmp
{
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4244 )
#endif
    template <typename T> inline void compareFP (const std::vector<T> &ref, const std::vector<T> &data, T prec) const
    {
        for (size_t i = 0; i < ref.size(); ++i)
        {
            ASSERT_NEAR (ref[i], data[i], prec);
        }
    }
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    template <typename T> inline void compareI (const std::vector<T> &ref, const std::vector<T> &data, T prec) const
    {
        auto precdo = static_cast<double> (prec);
        for (size_t i = 0; i < ref.size(); ++i)
        {
            auto refdo = static_cast<double> (ref[i]);
            auto datado = static_cast<double> (data[i]);
            ASSERT_NEAR (refdo, datado, precdo);
        }
    }

    template<typename T>
    inline void compare (const std::vector<T> &ref, const std::vector<T> &data, T prec) const
    {
        if (std::is_floating_point<T>::value)
        {
            compareFP (ref, data, prec);
        }
        else
        {
            compareI (ref, data, prec);
        }
    }
};

/// Compares Data<T> for equality
/**
 * This functor can be used together with the dispatchElementToFunctor utility function.
 */
struct DataCmp : public DataBaseCmp
{
    template<typename T>
    void operator() (const std::shared_ptr<spectre::element::data::Data<T> > &data)
    {
        // Tested separately
        if (data->getStrId() == "Directions")
        {
            return;
        }

        ValuesHolder<T> *values = dynamic_cast<ValuesHolder<T>*> (storedValues);
        ASSERT_TRUE (values != nullptr);
        auto desc (data->getDataDescriptor());

        std::vector<T> elementValues;
        ASSERT_SUCCESS (data->getValues (elementValues, accessCodeInternal));
        ASSERT_EQ (values->values.size(), elementValues.size());

        compare (values->values, elementValues, desc.precision);
    }

    RttiVoid *storedValues;
};

/// Compares a Data<T> with a reference Data<T>
/**
 * Can be used with dispatchElementToFunctor to compare
 * an Element to a reference Element instance
 */
struct ElementCmp
{
    ElementCmp (spectre::element::Element *a_refElement)
        : refElement (a_refElement)
    {}

    template<typename T>
    void operator() (const std::shared_ptr<spectre::element::data::Data<T> > &data) const
    {
        std::vector<T> values, refValues;
        ASSERT_SUCCESS (data->getValues (values));

        auto *refData = dynamic_cast<spectre::element::data::Data<T>*> (refElement);
        ASSERT_NE (nullptr, refData);
        ASSERT_SUCCESS (refData->getValues (refValues));

        ASSERT_EQ (refValues, values);
    }

    spectre::element::Element *refElement;
};


std::string getPathString (const DataPath &path);

using BuilderInfoMap = std::map<DataPath, std::shared_ptr<RttiVoid> >;
/**
 * Gets a builder info map describing the Aston one frequency format
 *
 * @param containerDim dimensional properties of the data container
 *
 * @return builder info map
 */
BuilderInfoMap getAstonCalibration1FreqMap (spectre::SizeProperty containerDim);
/**
 * Gets a builder info map describing the Aston two frequency format
 *
 * @param containerDim dimensional properties of the data container
 *
 * @return builder info map
 */
BuilderInfoMap getAstonCalibration2FreqMap (spectre::SizeProperty containerDim);

/**
 * Gets a builder info map describing the Aston three frequency format
 *
 * @param containerDim dimensional properties of the data container
 *
 * @return builder info map
 */
BuilderInfoMap getAstonCalibration3FreqMap (spectre::SizeProperty containerDim);

template<typename T>
void addToMap (BuilderInfoMap &infoMap,
               const std::string &id, DataType type, size_t size, DataPath path,
               const spectre::element::data::DataDescriptor<T> &descriptor);


template<typename T>
inline void addToMap (BuilderInfoMap &infoMap,
                      const std::string &id, DataType type, size_t size, DataPath path = DataPath())
{
    spectre::element::data::DataDescriptor<T> descriptor;
    addToMap (infoMap, id, type, size, path, descriptor);
}

/**
 * Gets the builder info map describing the Aston one frequency format
 *
 * @param containerDim dimensional properties of the data container
 *
 * @return builder info map
 */
BuilderInfoMap getAstonParameter1FreqMap (spectre::SizeProperty containerDim);

BuilderInfoMap getAstonInput1FreqMap (spectre::SizeProperty containerDim, const spectre::FrameSetCompositon &comp);
BuilderInfoMap getAstonOutput1FreqMap (spectre::SizeProperty containerDim);
BuilderInfoMap getAstonIntermediate1FreqMap (spectre::SizeProperty containerDim);

/**
 * Gets the builder info map describing the Aston two frequency format
 *
 * @param containerDim dimensional properties of the data container
 *
 * @return builder info map
 */
BuilderInfoMap getAstonParameter2FreqMap (spectre::SizeProperty containerDim);

BuilderInfoMap getAstonInput2FreqMap (spectre::SizeProperty containerDim, const spectre::FrameSetCompositon &comp);

BuilderInfoMap getAstonOutput2FreqMap (spectre::SizeProperty containerDim);

BuilderInfoMap getAstonIntermediate2FreqMap (spectre::SizeProperty containerDim);
