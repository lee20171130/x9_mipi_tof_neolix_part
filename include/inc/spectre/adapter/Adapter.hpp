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

#include <processing/processingInternal.hpp>

#include <spectre/SpectreFormatData.hpp>
#include <spectre/adapter/AdapterStatus.hpp>
#include <spectre/element/data/DataReference.hpp>


namespace spectre
{

    namespace element
    {
        namespace container
        {
            class Container;
            class Calibration;
            class Parameter;
            class Input;
            class Output;
        }
    }

    namespace adapter
    {
        /**
        *  Base converter type class used for data conversion from c++ api level to ansiC processing
        */
        class Adapter
        {
        protected:

            SpectreIO *m_io;                                        //< Input/Output interface between the c++ api and ansi-c processing level.
            element::container::Calibration *m_calib;               //< Linker handle to the processing calibration data container
            element::container::Parameter *m_param;                 //< Linker handle to the processing parameter data container
            element::container::Input *m_input;                     //< Linker handle to the processing input data container
            element::container::Output *m_output;                   //< Linker handle to the processing output data container

            std::map<element::Element *, void **> m_assigneeMap;    //< Default map, which comprises the


        public:

            /**
            *   Default Ctr of the base adapter class
            */
            Adapter();

            /**
            *   Constructor of the base adapter class
            *
            *   @param p_io Input/Output interface between the c++ api and ansi-c processing level.
            */
            Adapter (SpectreIO *io,
                     element::container::Calibration *calib,
                     element::container::Parameter *param,
                     element::container::Input *input,
                     element::container::Output *output);


            /**
            *   Destructor of the adapter class.
            */
            virtual ~Adapter();

            /**
            * To be called from DataReference element when new external reference was set.
            *
            * @param assignee Element assigned to carry new external reference handle.
            * @return TRUE if operation was successfull.
            */
            template<typename T>
            bool onNewReference (element::data::DataReference<T> *assignee, T *reference);

            /**
            *   Run spectre interface adaptation.
            *
            *   @return Adaptation process status message.
            */
            virtual AdapterStatus run() = 0;

            /**
            *   Link calibration data container with the adapter class
            */
            AdapterStatus linkContainer (element::container::Calibration *calib);

            /**
            *   Link calibration data container with the adapter class
            */
            AdapterStatus linkContainer (element::container::Parameter *param);

            /**
            *   Link calibration data container with the adapter class
            */
            AdapterStatus linkContainer (element::container::Input *input);

            /**
            *   Link calibration data container with the adapter class
            */
            AdapterStatus linkContainer (element::container::Output *output);

            /**
            * Add DataReference ass assignee to map.
            *
            * @param container Container element to retrieve data reference element from.
            * @param dataPath Path of element within the container structure.
            * @return TRUE if operation was successfull.
            */
            template<typename T>
            bool registerReference (element::container::Container *container,
                                    const std::vector<std::string> &dataPath,
                                    void **client);

            /**
            * Remove assignee Eleemnt from registry.
            *
            * @param assignee Element assigned to carry new external reference handle.
            * @return TRUE if operation was successfull.
            */
            template<typename T>
            bool deRegisterReference (element::data::DataReference<T> *assignee);

        protected:

            template<typename T>
            T *queryValueHandleFromContainer (element::container::Container *container,
                                              const std::vector<std::string> &dataPath);

            template<typename T>
            size_t queryValueSizeFromContainer (spectre::element::container::Container *container,
                                                const std::vector<std::string> &dataPath);

            size_t querySizeFromContainer (element::container::Container *container,
                                           const std::vector<std::string> &dataPath);

            virtual AdapterStatus adaptInput() = 0;

            virtual AdapterStatus adaptCalibration() = 0;

            virtual AdapterStatus adaptParamter() = 0;


            virtual AdapterStatus adaptOutput() = 0;

        };
    }
}
