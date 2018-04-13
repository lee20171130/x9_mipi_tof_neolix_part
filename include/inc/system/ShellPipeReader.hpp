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

#include<string>
#include <system/SystemIO.hpp>

/** \brief RAII class that runs a command via popen.
 */
class ShellPipeReader
{
public:

    /** \brief creates a ShellPipeReader object that executes command
     *
     * \param command the command to be executed.
     *
     * \throws CErrorException if pipeline produces an error.
     *
     */
    explicit ShellPipeReader (const std::string &command);

    /** \brief creates a ShellPipeReader object that executes command
     *
     * \param command the command to be executed.string with the command output
     * \param sysIo SystemIo object that should be used to execute the
     * system calls like popen, etc.
     *
     * \throws CErrorException if pipeline produces an error.
     *
     */
    ShellPipeReader (const std::string &command, SystemIOPtr sysIo);

    /** \brief If close was not called before it will be called here.
     *
     * \throws CErrorException if pipeline produces an error.
     *
     */
    ~ShellPipeReader();

    /** \brief closes the pipe to the command and returns the exit code
     *
     * \return exit code of the executed command
     *
     * \throws CErrorException if pipeline produces an error.
     *
     */
    int close();

    /** \brief reads until the next line break or the end of file is reached.
     *
     *
     * \return string with the next output line
     *
     * \throws CErrorException if pipeline produces an error.
     *
     */
    std::string readLine();

    /** \brief reads the whole output of the executed command
     *
     *
     * \return string with the command output
     *
     * \throws CErrorException if pipeline produces an error.
     *
     */
    std::string readAll();

    /** \brief checks if the pipe returns end of file alias all command output read
     *
     *
     * \return true if the pipe reached end of file, false otherwise.
     *
     * \throws CErrorException if pipeline produces an error.
     *
     */
    bool reachedEof();

private:
    void openPipe (const std::string &command);
    void checkValidity();
    bool isEol (char token);
    bool handleNullptr();

    SystemIOPtr m_sysIo; //! The SystemIo object that is used for system calls
    FILE *m_pipe {}; //! The pipe that is connected to the executed command
    bool m_valid = true; //! flag that show if pipe is open and valid.
};
