#ifndef SWINGCONFIGURATORINTERFACE_H
#define SWINGCONFIGURATORINTERFACE_H
#include "jpanel.h"
#include "base.h"
#include "basemanager.h"
#include "malesocket.h"
#include "jcomponent.h"

class SwingConfiguratorInterface
{
  //Q_OBJECT
 public:
  //SwingConfiguratorInterface();
  /*public*/ virtual QString getExecuteEvaluateMenuText()=0;

  /**
   * Execute or evaluate an item that this object configures.
   * @param object the object to execute or evaluate
   */
  /*public*/ virtual void executeEvaluate(/*@Nonnull*/ Base* object)=0;

  /**
   * Get the manager that handles the beans for the new object.
   * This is used for validation of the system name for the bean that this
   * class creates.
   *
   * @return the manager
   */
  /*public*/virtual  BaseManager/*<? extends NamedBean>*/* getManager()=0;

  /**
   * Get a configuration panel when a new object is to be created and we don't
   * have it yet.
   * This method initializes the panel with an empty configuration.
   *
   * @param buttonPanel panel with the buttons
   * @return a panel that configures this object
   * @throws IllegalArgumentException if this class does not support the class
   * with the name given in parameter 'className'
   */
  /*public*/ virtual JPanel* getConfigPanel(JPanel* buttonPanel) /*throws IllegalArgumentException*/=0;

  /**
   * Get a configuration panel for an object.
   * This method initializes the panel with the configuration of the object.
   *
   * @param object the object for which to return a configuration panel
   * @param buttonPanel panel with the buttons
   * @return a panel that configures this object
   */
  /*public*/ virtual JPanel* getConfigPanel(/*@Nonnull*/ Base* object, JPanel* buttonPanel) /*throws IllegalArgumentException*/=0;

  /**
   * Validate the form.
   * <P>
   * The parameter errorMessage is used to give the error message in case of
   * an error. If there are errors, the error messages is added to the list
   * errorMessage.
   *
   * @param errorMessages the error messages in case of an error
   * @return true if data in the form is valid, false otherwise
   */
  /*public*/ virtual bool validate(/*@Nonnull */QList<QString>* errorMessages)=0;

  /**
   * Get an example of a system name
   * @return the system name
   */
  /*public*/ virtual QString getExampleSystemName()=0;

  /**
   * Create a new system name.
   * @return a new system name
   */
  /*public*/ virtual QString getAutoSystemName()=0;

  /**
  * Create a new object with the data entered.This method must also register the object in its manager.
  *
  * @param systemName system name
  * @param userName user name
  * @return a male socket for the new object
  */
 /*public*/virtual  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)
         /*throws BadUserNameException, BadSystemNameException*/=0;

 /**
  * Updates the object with the data in the form.
  *
  * @param object the object to update
  */
 /*public*/virtual  void updateObject(/*@Nonnull*/ Base* object)=0;

 /**
  * Returns the name of the class that this class configures.
  *
  * @return the name of the class this class configures.
  */
 //@Override
 /*public*/ virtual  QString toString()=0;

 /**
  * Dispose the panel and remove all the listeners that this class may have
  * registered.
  */
 /*public*/ virtual void dispose()=0;

  /*public*/  static QList<JComponent*> parseMessage(QString message, QList<JComponent*> components) ;

  virtual QObject* sself() =0;
};

Q_DECLARE_INTERFACE(SwingConfiguratorInterface, "SwingConfiguratorInterface")
#endif // SWINGCONFIGURATORINTERFACE_H
