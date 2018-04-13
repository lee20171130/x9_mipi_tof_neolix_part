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

#include "system/ICommandExecutor.hpp"


/** \brief class to run shell commands.
 *
 *
 */
class CommandExecutor : public ICommandExecutor
{
public:
    /** \brief default constructor
     *
     */
    CommandExecutor();

    /** \brief runs a shell command and return exit code and standard output as CommandResult
     *
     * \param command The command to be executed
     *
     */
    virtual CommandResult run (const std::string &command) override;
};
