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
#include <memory>
#include <system/OptimizationGoal.hpp>

/** \brief  manages necessary changes of boundary conditions
 *
 * The class manages changes to boundary conditions that are necessary
 * to achieve reproducible test results or to redirect outputs.
 * This standard implementation just redirects the standard out on
 * platforms that need this to push the output into a log.
 * The class implements the RAII pattern. All changes are made during construction
 * and reverted during destruction.
 *
 */
class BoundaryConditionsManager
{
public:

    /** \brief makes all changes to boundary conditions
     *
     * \param OptimizationGoal the goal for which the boundary conditions should be optimized
     *
     * This standard implementation only redirects the standard out where necessary.
     * The value of OptimizationGoal has no effects in this implementation
     *
     */
    explicit BoundaryConditionsManager (OptimizationGoal) : outRedirector (redirectStdOutIfNecessary()) {}

private:

    OutRedirector outRedirector;
};

using BoundaryConditionsManagerPtr = std::unique_ptr<BoundaryConditionsManager>;
