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

#include <system/CpuFreqHandler.hpp>

class SystemIO;
using SystemIOPtr = std::unique_ptr<SystemIO>;


/** \brief class to get and set algorithms that manage cpu frequencies on Linux and Android

 * This class can be used to get and set governors
 * LinuxCpuFreqHandler uses the script gov.sh
 * to get and set the governors. The class expects the scripts to
 * be in the same directory as the executable.Available governors depend
 * on the kernel version. The governors supported by the script are
 * currently:
 *     # ondemand
 *     # performance
 *     # powersave
 *     # conservative
 *     # interactive
 */
class LinuxCpuFreqHandler: public CpuFreqHandler
{
public:
    /** \brief initializes the handler with a user chosen SystemIO object
     *
     * \param SystemIOPtr sysIo the SystemIO object that the handler should use
     *
     */
    explicit LinuxCpuFreqHandler (SystemIOPtr sysIo);

    /** \brief initializes the handler with a SystemIo object of class SystemIOReal
     *
     */
    LinuxCpuFreqHandler();

    /** \brief returns the currently active governor.
     *
     * \return FreqAlgResult if valid contains the name of the
     * currently active governor.
     *
     */
    virtual FreqAlgResult getAlgorithm() const override;

    /** \brief tries to set a new governor.
     *
     * \param newGovernor the name of the governor to set.
     * \return the name of the currently running governor.
     *
     * The method tries to to set another governor. The call was successful
     * if the return value is valid and the returned governor name equals
     * the requested governor name.
     *
     */
    virtual FreqAlgResult setAlgorithm (const std::string &newGovernor) override;

private:

    /** \brief runs the script to get or set the governors of all cpus
     *
     * \param const std::string &govToSet The name of the governor that should be set.
     * If this is empty the method just gets the active governors
     * \return A list with the currently active governor for each cpu.
     *
     */
    FreqAlgResult runGovernorSkript (const std::string &govToSet = "") const;

    /** \brief extract the first governor from a list of governors
     *
     * \param const std::string &governors a space separated list of governors
     * \return the first governor in the list.
     *
     */
    std::string extractGovernor (const std::string &governors) const;

    /** \brief evaluate the status value return by pclose.
     *
     * \param int status a status value as returned by SystemIO::pclose
     * \return # -1  if pclose detected an error
     *         # -2  if the OS killed the script
     *         # >=0 return code of script
     *
     */
    int evaluateStatus (int status) const;

    /** \brief determines path of gov.sh and sets the appropriate command string
     *
     */
    void setCommand();

    SystemIOPtr sysIo;          //!< The SystemIO object that is used to call popen, pclose, etc.
    std::string shellCommand;   //!< The shellcomand thats called via popen
};
