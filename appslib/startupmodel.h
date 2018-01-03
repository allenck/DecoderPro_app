#ifndef STARTUPMODEL_H
#define STARTUPMODEL_H
#include <QObject>
#include "exceptions.h"

/**
 * Startup object models all need to implement this interface. This allows the
 * {@link apps.StartupActionsManager} to handle lists of different model
 * classes.
 *
 * @author Randall Wood (C) 2015
 */
/*public*/ /*interface*/ class StartupModel : public  QObject
{
 Q_OBJECT
public:
 StartupModel(QObject* parent = 0) : QObject(parent) {}
 /**
  * Return the name of of the model or its controlled object.
  *
  * @return the name, an empty string, or null
  */
 //@CheckForNull
 /*public*/ virtual QString getName() {return "";}

 /**
  * Set the name of the model.
  *
  * @param name the name, an empty string, or null
  */
 /*public*/ virtual void setName(/*@Nullable*/ QString /*name*/) {}

 /**
  * Test is model is a valid model. Invalid models will not be shown or saved
  * by {@link apps.startup.StartupActionsPreferencesPanel}.
  *
  * @return true if valid; false otherwise
  */
 /*public*/ virtual bool isValid() {return false;}

 /**
  * Perform the startup action.
  *
  * @throws jmri.JmriException if there is an exception thrown initializing
  *                            the startup item
  */
 /*public*/ virtual void performAction() throw (JmriException) {}

 /**
  * Get the exceptions thrown by the startup model.
  *
  * @return the list of exceptions thrown during startup in order or an empty
  *         list if no exceptions were thrown
  */
 //@Override
 /*public*/ virtual QList<Exception>* getExceptions() { return NULL;}

 /**
  * Add an exception to the list of exceptions thrown when loading the model
  * or performing the action.
  *
  * @param exception the exception to retain with the model
  */
 /*public*/ virtual void addException(/*@Override*/ Exception /*exception*/) {}

 /*public*/ virtual QString toString() {return QString(this->metaObject()->className());}

 /*public*/ virtual QString getDescription() {return "";} // ACK added

};
#endif // STARTUPMODEL_H
