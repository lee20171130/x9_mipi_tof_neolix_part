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
#include <queue>
#include "system/CommandExecutor.hpp"

class IIntent;
using IIntentPtr = std::unique_ptr<IIntent>;

/** \brief Interface of Intents.
 *
 * Intent provides an partial interface analog to the the java class Intent in the android
 * API.
 * \sa <a href="https://developer.android.com/reference/android/content/Intent.html">Intent java documentation</a>
 */
class IIntent
{
public:

    /** \brief virtual destructor of an Intent
     *
     */
    virtual ~IIntent() = default;

    /** \brief Retrieve the general action to be performed
     *
     *  \return The action of this intent or the empty string if none is specified.
     *
     */
    virtual std::string getAction() const = 0;

    /** \brief Set the general action to be performed
     *
     * \param action An action name.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &setAction (const std::string &action) = 0;


    /** \brief Retrieve the concrete component associated with the intent.
     *
     *  \return The name of the application component to handle the intent.
     *
     */
    virtual std::string getComponent() const = 0;

    /** \brief Explicitly set the component to handle the intent.
     *
     * \param component The name of the application component to handle the intent.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &setComponent (const std::string &component) = 0;

    /** \brief Convenience for calling setComponent(component) with an explicit application package name and class name.
     *
     * \param packageName The name of the package implementing the desired component.
     * \param className  The name of a class inside of the application package that will be used as the component for this Intent.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &setClassName (const std::string &packageName, const std::string &className) = 0;


    /** \brief Add extended data to the intent.
     *
     * \param name The name of the extra data, with package prefix.
     * \param value The string data value.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &putExtra (const std::string &name, const std::string &value) = 0;

    /** \brief Add extended data to the intent.
     *
     * \param name The name of the extra data, with package prefix.
     * \param value The int data value.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &putExtra (const std::string &name, int value) = 0;

    /** \brief Retrieve extended data from the intent.
     *
     * \param name The name of the desired item.
     * \return The value of an item that previously added with putExtra()
     * or the empty string if no String value was found.
     *
     */
    virtual std::string getStringExtra (const std::string &name) const = 0;

    /** \brief Retrieve extended data from the intent.
     *
     * \param name The name of the desired item.
     * \param defaultValue The value to be returned if no value of the
     * desired type is stored with the given name.
     * \return The value of an item that previously added with putExtra()
     * or the default value if none was found.
     *
     */
    virtual int getIntExtra (const std::string &name, int defaultValue) const = 0;


    /** \brief Broadcast the given intent to all interested BroadcastReceivers. No results are propagated from receivers.
     *
     */
    virtual void sendBroadcast() = 0;

    /** \brief Request that a given application service be started.
     *
     * Request that a given application service be started. The Intent should contain either
     * contain the complete class name of a specific service implementation to start or a
     * specific package name to target.
     *
     */
    virtual void startService() = 0;


    /** \brief Static factory method to create an Intent.
     *
     * \param action An action name.
     * \param runner Pointer to a CommandExecutor that will be used to execute the Intents.
     * \return A pointer to an Intent object.
     *
     * The method willl create a new Intent with the given action and the given CommandExecutor if s_intents is
     * empty. If s_intents contains an Intent object, it will be popped from s_intents and returned. In this
     * case the given CommandExecutor will be ignored.
     *
     */
    static IIntentPtr createIntent (const std::string &action, ICommandExecutorShr runner = std::make_shared<CommandExecutor>());

    /** \brief Static factory method to create an Intent.
     *
     * \param runner Pointer to a CommandExecutor that will be used to execute the Intents.
     * \return A pointer to an Intent object.
     *
     * The method willl create a new Intent with the given CommandExecutor if s_intents is
     * empty. If s_intents contains an Intent object, it will be popped from s_intents and returned. In this
     * case the given CommandExecutor will be ignored.
     *
     */
    static IIntentPtr createIntent (ICommandExecutorShr runner = std::make_shared<CommandExecutor>());

    static std::queue<IIntentPtr> s_intents; //! static queue that can buffer returnable Intents

};
