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
#include <map>
#include <string.h>
#include <memory>

#include <calibration/legacy/Tardefines.hpp>

namespace spectre
{
    namespace calibration
    {
        namespace legacy
        {
            /**
               @brief Import and export of tar files.

               The maximum filesize included in the tarball is 2^31 (max of int) ans is limited by the getFileSize method.

               Class for handling archive data in tar format - uncompressed as well es gzipped.
            */
            class TarGz
            {
            public:
                TarGz();

                TarGz (const void *data, size_t len);

                /** feed the internal importer
                    Whether to unzip the file is decided based on the magic header field.
                    @param data whole data block
                    @param len size of data block
                */
                void setTarData (const void *data, size_t len);

                /** get all filesname inside the tarball
                    @return list of files
                */
                std::list <std::string> getFileNames() const;

                /** get the size of a file inside the tarball
                    @param filename the filename inside the tarball.
                    @return size of data block, -1 if file does not exist
                */
                int getFileSize (const std::string &filename) const;

                /** returns a const pointer to the file data inside the tarball
                    Caution: Ensure, that the TarGz object is alive, as long as the returned pointer is in use!
                    @param filename file inside the tarball
                    @return const pointer to data block. Size can be retrieved invoking getFileSize(..)
                */
                const void *getFilePtr (const std::string &filename) const;

                /** add data block to the current internal state and the associated filename
                    @param filename corresponding filename of the data block
                    @param data data block
                    @param len length of the data block
                */
                void addFile (const std::string &filename, const void *data, size_t len);

                /** returns a copy of the data vector.
                    But: It is not very efficient to copy memory from one point in memory space to the other just for fun!
                    Use the copy method instead!
                    @param filename file inside the tarball
                    @return copy of data vector
                */
                std::vector <char> getFile (const std::string &filename) const;

                /** copies file to destination buffer
                    Throws pmd::ResourceError exception, if size does not match real filesize.
                    @param filename file inside tarball
                    @param dst custom destination buffer
                    @param size size of destination buffer
                */
                void copy (const std::string &filename, void *dst, size_t size) const;

                /** retrieves the tarball
                    @param dst reference to destination. The vector is being resized internally.
                */
                void getTarball (std::vector <char> &dst) const;

                /** resets the file
                 */
                void reset();

            protected:
                typedef struct tag_RuntimeData
                {
                    tag_RuntimeData()
                    {
                        memset (&header, 0, sizeof (ustar_header));
                    }
                    tag_RuntimeData (const ustar_header &h, const void *d, size_t len)
                    {
                        header = h;
                        data.resize (len);
                        memcpy (&data[0], d, len);
                    }
                    ustar_header header;
                    std::vector <char> data;
                } RuntimeData;
                typedef std::shared_ptr<RuntimeData> PRuntimeData;

            private:
                std::map <std::string, PRuntimeData> m_files;
            };

        }
    }
}
