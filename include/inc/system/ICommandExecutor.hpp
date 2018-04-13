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
#include <iostream>


/** \brief container class to bundle the return values of ICommandExecutor::run
 * *
 */
struct CommandResult
{
    CommandResult() = default;

    /** \brief creates a Command Result
     *
     * \param returnValue The exit code of the command.
     *
     * \param output standard out of the command
     *
     */
    CommandResult (int returnValue, const std::string &output) :
        returnValue (returnValue),
        output (output)
    {}

    int returnValue{}; //! The exit code of the command.
    std::string output{}; //! The standard output of the command.
};

inline ::std::ostream &operator<< (::std::ostream &os, const CommandResult &result)
{
    os << "returnValue = " << result.returnValue << ", output = \"" <<  result.output << "\"";
    return os;
}


/** \brief interface for a method that runs a shell command
 *
 *
 */
class ICommandExecutor
{
public:
    ICommandExecutor() = default;
    virtual ~ICommandExecutor() = default;


    /** \brief runs a shell command and return exit code and standard output as CommandResult
     *
     * \param command The command to be executed
     *
     */
    virtual CommandResult run (const std::string &command) = 0;
};

using ICommandExecutorPtr = std::unique_ptr<ICommandExecutor>;
using ICommandExecutorShr = std::shared_ptr<ICommandExecutor>;
