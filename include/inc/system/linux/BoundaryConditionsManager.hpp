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
#include <system/toolsLog.hpp>
#include <system/OptimizationGoal.hpp>
#include "LinuxCpuFreqHandler.hpp"



/** \brief  manages necessary changes of boundary conditions
 *
 * The class manages changes to boundary conditions that are necessary
 * to achieve reproducible test results or to redirect outputs.
 * This Linux implementation does the following:
 *   -# calls ::redirectStdOutIfNecessary and hold the OutRedirector during object lifetime
 *   -# if goal == OptimizationGoal::Runtime it tries to change the cpu govenor
 *      on all cpus to performance.
 * The class implements the RAII pattern. All changes are made during construction
 * and reverted during destruction.
 *
 */
class BoundaryConditionsManager
{
public:

    /** \brief makes all changes to boundary conditions
     *
     * \param goal the goal for which the boundary conditions should be optimized
     *
     * This Linux implementation does the following:
     *   -# calls ::redirectStdOutIfNecessary and hold the OutRedirector during object lifetime
     *   -# initializes freqHandler with an instance of LinuxCpuFreqHandler.
     *   -# initializes output with std::cout.
     *   -# if goal == OptimizationGoal::Runtime it tries to change the cpu governor
     *      on all cpus to performance.
     *
     */
    explicit BoundaryConditionsManager (OptimizationGoal goal);



    /** \brief makes all changes to boundary conditions
     *
     * \param goal the goal for which the boundary conditions should be optimized
     * \param freqHandler the frequencyHandler that will be used to set CPU frequency algorithms
     *
     * This Linux implementation does the following:
     *   -# calls ::redirectStdOutIfNecessary and hold the OutRedirector during object lifetime
     *   -# initializes freqHandler with freqHandler.
     *   -# initializes output with the given output stream.
     *   -# if goal == OptimizationGoal::Runtime it tries to change the cpu governor
     *      on all cpus to performance.
     *
     */
    BoundaryConditionsManager (OptimizationGoal goal, CpuFreqHandlerPtr freqHandler, std::ostream &output);

    /** \brief sets all boundary conditions back to there original values.
     *
     *
     */
    ~BoundaryConditionsManager();

private:

    /** \brief tries to set a new governor
     *
     * \param goal the goal for which the boundary conditions should be optimized
     *
     */
    void setFreqAlgorithm (OptimizationGoal goal);


    /** \brief checks if CpuFreqHandler::getAlgorithm returned a valid algorithm result.
     *
     * \param algo The FreqAlgResult to check
     * \return true if algo is valid, false otherwise.
     *
     */
    bool getReturnedNoError (const FreqAlgResult &algo);

    /** \brief sets governor to performance if curAlgo != performance
     *
     * \param curAlgo the currently active frequency algorithm
     *
     */
    void setNewAlgorithmIfNeccessary (OptimizationGoal goal, const std::string &curAlgo);

    /** \brief checks if CpuFreqHandler::setAlgorithm returned a valid algorithm result.
     *
     * \param goal the goal for which the boundary conditions should be optimized
     * \param algo The FreqAlgResult to check
     * \return true if algo is valid, false otherwise.
     *
     */
    bool setReturnedNoError (const FreqAlgResult &algo, const std::string &expAlgo);

    /** \brief sets the frequency algorithm back to the old value
     *     *
     */
    void setBackFreqAlgorithm();

    /** \brief sets the frequency algorithm back to the old value
    *     *
    * \param goal the goal for which the boundary conditions should be optimized
    * \return The name of the frequency algorithm that should be set.
    */
    std::string getRequestedAlgo (OptimizationGoal goal);

    OutRedirector outRedirector;        //!< The OutDirector for this platform
    CpuFreqHandlerPtr freq;             //!< The CpuFreqHandler to get and set cpu frequency algorithms.
    std::ostream &outStream;            //!< The output stream for error messages
    std::string oldAlgorithm = "";      //!< buffer variable to remember the old frequency algorithm
};

using BoundaryConditionsManagerPtr = std::unique_ptr<BoundaryConditionsManager>;
