/****************************************************************************\
 * Copyright (C) 2013 pmdtechnologies ag
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
#include <list>
#include <memory>
#include <cstdint>

/**
   This class intention is to load and save calibration data as well as organizing calibration data during runtime.

   Calibration data is linked to a identity string, which can be used by custom functions to access the data.

   The calibration data owns no specified header. It is saved as raw binary data into a tar file. Currently there is
   no export method implemented, so a system call is done to archive seperate temporal calibration files. After
   archieving, those files are deleted. If working with Windows, make sure the executable "bsdtar" with its dlls
   is located in the execution folder.
*/
namespace spectre
{
    namespace calibration
    {
        namespace legacy
        {
            class TarCalibrationContainerPrivate;

            class TarCalibrationContainer
            {
            public:
                TarCalibrationContainer();
                TarCalibrationContainer (const TarCalibrationContainer &c);
                void operator = (const TarCalibrationContainer &c);
                ~TarCalibrationContainer();

                // /** push new data, internal buffer will be created, if no appropriate buffer exists */
                void feed (const std::string &ident, const void *data, size_t size);

                /** push new data (tar file). If pointer or size is 0, silent return. */
                void feed (const void *data, size_t size, bool decrypt = true);

                /** frees all internal buffers if string empty, otherwise only sqecified data */
                void reset (const std::string &ident = "");

                /** copies the data block of a calibration data identity
                    @return true if ok, false if no data found (identity not found or empty data block) */
                bool get (const std::string &ident, std::vector<uint8_t> &data) const;

                /** get pointer to data block of a calibration data identity. Data size is returned with third parameter.
                    @return true if ok, false if no data found (identity not found or empty data block) */
                bool get (const std::string &ident, void **data, size_t *size) const;

                /** get all names of existing calibration data.*/
                void getall (std::list <std::string> &idents) const;

                /** checks, if calib data of specified type is available */
                bool have (const std::string &ident) const;

                /** did the last feed operation load new data? */
                bool changed() const;

                void setEncryptionKey (const std::string &key);

                bool loaded() const;
                unsigned int size() const;

                const char *data() const;

            private:

                void simpleCrypt (char *data, size_t size, const char *key, size_t keylen);

                void cipher (char *data, size_t len, const char  *key) const;

            protected:
                /** saves the calibration data to according filename of data identity
                    if ident not found, skip silently */
                void save (const std::string &ident) const;
            private:
                TarCalibrationContainerPrivate *p;
            };

            typedef std::shared_ptr <TarCalibrationContainer> PTarCalibrationContainer;

        }
    }
}
