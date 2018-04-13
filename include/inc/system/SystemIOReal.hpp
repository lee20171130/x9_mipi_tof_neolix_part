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
#include <system/SystemIO.hpp>



/** \brief class to handle system specific io operations
 *
 * This class uses several system specific cpp files to
 * implement the SystemIO Interface on each system.
 */
class SystemIOReal : public SystemIO
{
public:
    SystemIOReal() = default;
    virtual ~SystemIOReal() = default;

    /** \brief runs a system command and opens a pipe to either stdin or stdout of the command.
     *
     * \param command the complete command
     * \param mode if set to "r" the pipe will be bound to stdout of the command.
     * If set to "w" the pipe will be bound to stdin.
     * \return A FILE object. This will be somewhat implementation specific.
     *
     * Implementations of this function should follow the Posix definition of this
     * method.
     * \sa <a href="http://linux.die.net/man/3/popen">popen documentation</a>
     */
    virtual FILE *popen (const char *command, const char *mode);

    /** \brief closes a FILE object opened by popen
     *
     * \param stream to close
     * \return -1 in case of an error
     *
     * \sa <a href="http://linux.die.net/man/3/pclose">pclose documentation</a>
     */
    virtual int pclose (FILE *stream);

    /** \brief read data from a file into a buffer,
     *
     * \param buffer pointer to a buffer
     * \param bufferSize size of the given buffer
     * \param stream pointer to the file object
     * \return on success returns buffer. In case of a failure or
     * eof a nullptr is returned
     *
     * \sa <a href="http://www.cplusplus.com/reference/cstdio/fgets/">fgets documentation</a>
     */
    virtual char *fgets (char *buffer, int bufferSize, FILE *stream);

    /** \brief Checks whether the end-of-File indicator associated with stream is set, returning a value different from zero if it is.
     *
     * \param stream pointer to a file object
     * \return non-zero if eof is set for this stream. Otherwise zero is returned.
     *
     * \sa <a href="http://www.cplusplus.com/reference/cstdio/feof/</a>
     */
    virtual int reachedEof (FILE *stream);

    /** \brief returns the full path to the executable
     *
     * \return std::string the full path of the executable
     * or an empty string if the path can not be determined.
     *
     */
    virtual std::string getOwnExePath();
};
