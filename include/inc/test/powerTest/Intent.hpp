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

#include "test/powerTest/IIntent.hpp"
#include <string>
#include <unordered_map>
#include "system/CommandExecutor.hpp"
#include <sstream>

class ExtraValue;
using ExtraValuePtr = std::unique_ptr<ExtraValue>;

using ExtraMap = std::unordered_map<std::string, ExtraValuePtr>;

/** \brief Implementation of Intents interface.
 *
 * Intent provides an partial interface analog to the the java class Intent in the android
 * API.
 * \sa <a href="https://developer.android.com/reference/android/content/Intent.html">Intent java documentation</a>
 */
class Intent: public IIntent
{
public:
    /** \brief create an empty Intent.
     *
     * \param runner Pointer to a CommandExecutor that will be used to execute the Intents.
     */
    Intent (ICommandExecutorShr runner = std::make_shared<CommandExecutor>());

    /** \brief create an Intent with a given action.
     *
     * \param action An action name.
     * \param runner Pointer to a CommandExecutor that will be used to execute the Intents.
     */
    Intent (const std::string &action, ICommandExecutorShr runner = std::make_shared<CommandExecutor>());

    /** \brief virtual destructor of an Intent
     *
     */
    virtual ~Intent();


    /** \brief Retrieve the general action to be performed
     *
     *  \return The action of this intent or the empty string if none is specified.
     *
     */
    virtual std::string getAction() const override;

    /** \brief Set the general action to be performed
     *
     * \param action An action name.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &setAction (const std::string &action) override;

    /** \brief Retrieve the concrete component associated with the intent.
     *
     *  \return The name of the application component to handle the intent.
     *
     */
    virtual std::string getComponent() const override;

    /** \brief Explicitly set the component to handle the intent.
     *
     * \param component The name of the application component to handle the intent.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &setComponent (const std::string &component) override;

    /** \brief Convenience for calling setComponent(component) with an explicit application package name and class name.
     *
     * \param packageName The name of the package implementing the desired component.
     * \param className  The name of a class inside of the application package that will be used as the component for this Intent.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &setClassName (const std::string &packageName, const std::string &className) override;


    /** \brief Add extended data to the intent.
     *
     * \param name The name of the extra data, with package prefix.
     * \param value The string data value.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &putExtra (const std::string &name, const std::string &value) override;

    /** \brief Add extended data to the intent.
     *
     * \param name The name of the extra data, with package prefix.
     * \param value The int data value.
     * \return Returns a reference to the same Intent object, for chaining multiple
     * calls into a single statement.
     *
     */
    virtual IIntent &putExtra (const std::string &name, int value) override;

    /** \brief Retrieve extended data from the intent.
     *
     * \param name The name of the desired item.
     * \return The value of an item that previously added with putExtra()
     * or the empty string if no String value was found.
     *
     */
    virtual std::string getStringExtra (const std::string &name) const override;

    /** \brief Retrieve extended data from the intent.
     *
     * \param name The name of the desired item.
     * \param defaultValue The value to be returned if no value of the
     * desired type is stored with the given name.
     * \return The value of an item that previously added with putExtra()
     * or the default value if none was found.
     *
     */
    virtual int getIntExtra (const std::string &name, int defaultValue) const override;


    /** \brief Broadcast the given intent to all interested BroadcastReceivers. No results are propagated from receivers.
     *
     */
    virtual void sendBroadcast() override;

    /** \brief Request that a given application service be started.
     *
     * Request that a given application service be started. The Intent should contain either
     * contain the complete class name of a specific service implementation to start or a
     * specific package name to target.
     *
     */
    virtual void startService() override;

private:
    void addIntent (std::stringstream &command);
    void addAction (std::stringstream &command);
    void addExtras (std::stringstream &command);
    void addComponent (std::stringstream &command);

    std::string m_action; //! The general action of the intent.
    std::string m_component; //! The concrete component of this intent
    ExtraMap m_extras; //! Map that holds all extended data item of this intent
    ICommandExecutorShr m_runner; //! CommandExecutor that is used to execute the intent.
};
