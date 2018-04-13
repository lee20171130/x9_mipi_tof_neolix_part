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

/** \brief enumeration with goals for which BoundaryConditions should optimize.
 *
 * The enumeration has two goals:
 *  -# Runtime: optimize the system for short runtimes.
 *  -# LowPower: optimize the system for low power consumption.
 */
enum class OptimizationGoal
{
    Runtime, LowPower, NoChange
};
