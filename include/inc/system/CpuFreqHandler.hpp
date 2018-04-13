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


/** \brief the cpu frequency algorithm
 *
 * This is a std::pair
 * \param first parameter is an int that indicates whether the second parameter
 * is valid or not. =0 means valid, !=0 means invalid. Different values can
 * mark different failures, but the meaning of the values is implementation specific.
 * \param second parameter is a string that holds the name of the algorithm. Valid
 * algorithm names are implementation specific.
 *
 */
using FreqAlgResult = std::pair<int, std::string>;


/** \brief interface to get and set algorithms that manage cpu frequencies

 * This interface can be used to get and set cpu frequency algorithms
 * like the cpu governor on Linux.
 */
class CpuFreqHandler
{
public:
    virtual ~CpuFreqHandler() {}

    /** \brief returns the currently active frequency algorithm.
     *
     * \return FreqAlgResult if valid contains the name of the
     * currently active frequency algorithm.
     *
     */
    virtual FreqAlgResult getAlgorithm() const = 0;

    /** \brief tries to set a new frequency algorithm.
     *
     * \param newGovernor the name of frequency algorithm to set.
     * \return the name of the currently running frequency algorithm.
     *
     * The method tries to to set another frequency algorithm. Possible
     * algorithms are implementation specific. The call was successful
     * if the return value is valid and the returned algorithm name equals
     * the requested algorithm name.
     *
     */
    virtual FreqAlgResult setAlgorithm (const std::string &newGovernor) = 0;
};
using CpuFreqHandlerPtr = std::unique_ptr<CpuFreqHandler>;
