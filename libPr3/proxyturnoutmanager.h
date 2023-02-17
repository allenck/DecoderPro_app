#ifndef PROXYTURNOUTMANAGER_H
#define PROXYTURNOUTMANAGER_H
#include "abstractprovidingproxymanager.h"
#include "turnoutmanager.h"
#include "internalturnoutmanager.h"
#include "exceptions.h"

class QCompleter;
class LIBPR3SHARED_EXPORT ProxyTurnoutManager : public AbstractProvidingProxyManager, public TurnoutManager
{
  Q_OBJECT
  Q_INTERFACES(TurnoutManager)
public:
 ProxyTurnoutManager(QObject* parent = 0);
 /**
  * Revise superclass behavior: support TurnoutOperations
  */
 /*public*/ void addManager(AbstractManager* m) override;
 /**
  * Locate via user name, then system name if needed.
  *
  * @param name
  * @return Null if nothing by that name exists
  */
 /*public*/ Turnout* getTurnout(QString name) override;
#if 0
 /**
  * Locate an instance based on a system name.  Returns null if no
  * instance already exists.
  * @return requested Turnout object or null if none exists
  */
 /*public*/ Turnout* getBySystemName(QString systemName) const;
 /**
  * Locate an instance based on a user name.  Returns null if no
  * instance already exists.
  * @return requested Turnout object or null if none exists
  */
 /*public*/ Turnout* getByUserName(QString userName) const;
#endif
 /**
  * Return an instance with the specified system and user names.
  * Note that two calls with the same arguments will get the same instance;
  * there is only one Sensor object representing a given physical turnout
  * and therefore only one with a specific system or user name.
  *<P>
  * This will always return a valid object reference for a valid request;
  * a new object will be
  * created if necessary. In that case:
  *<UL>
  *<LI>If a null reference is given for user name, no user name will be associated
  *    with the Turnout object created; a valid system name must be provided
  *<LI>If a null reference is given for the system name, a system name
  *    will _somehow_ be inferred from the user name.  How this is done
  *    is system specific.  Note: a future extension of this interface
  *    will add an exception to signal that this was not possible.
  *<LI>If both names are provided, the system name defines the
  *    hardware access of the desired turnout, and the user address
  *    is associated with it.
  *</UL>
  * Note that it is possible to make an inconsistent request if both
  * addresses are provided, but the given values are associated with
  * different objects.  This is a problem, and we don't have a
  * good solution except to issue warnings.
  * This will mostly happen if you're creating Sensors when you should
  * be looking them up.
  * @return requested Sensor object (never null)
  */
 /*public*/ Turnout* newTurnout(QString systemName, QString userName) override;
 /**
  * Get text to be used for the Turnout.CLOSED state in user communication.
  * Allows text other than "CLOSED" to be use with certain hardware system
  * to represent the Turnout.CLOSED state.
  * Defaults to the primary manager.  This means that the primary manager sets the terminology
  * used.  Note: the primary manager need not override the method in AbstractTurnoutManager if
  * "CLOSED" is the desired terminology.
  */
 /*public*/ QString getClosedText() override;
 /**
  * Get text to be used for the Turnout.THROWN state in user communication.
  * Allows text other than "THROWN" to be use with certain hardware system
  * to represent the Turnout.THROWN state.
  * Defaults to the primary manager.  This means that the primary manager sets the terminology
  * used.  Note: the primary manager need not override the method in AbstractTurnoutManager if
  * "THROWN" is the desired terminology.
  */
 /*public*/ QString getThrownText() override;
 /**
  * Get from the user, the number of addressed bits used to control a turnout.
  * Normally this is 1, and the default routine returns 1 automatically.
  * Turnout Managers for systems that can handle multiple control bits
  * should override this method with one which asks the user to specify the
  * number of control bits.
  * If the user specifies more than one control bit, this method should
  * check if the additional bits are available (not assigned to another object).
  * If the bits are not available, this method should return 0 for number of
  * control bits, after informing the user of the problem.
  */
  /*public*/ int askNumControlBits(QString systemName) override;
 /**
  * Get from the user, the type of output to be used bits to control a turnout.
  * Normally this is 0 for 'steady state' control, and the default routine
  * returns 0 automatically.
  * Turnout Managers for systems that can handle pulsed control as well as
  * steady state control should override this method with one which asks
  * the user to specify the type of control to be used.  The routine should
  * return 0 for 'steady state' control, or n for 'pulsed' control, where n
  * specifies the duration of the pulse (normally in seconds).
  */
 /*public*/ int askControlType(QString systemName) override;
 /*public*/ bool isControlTypeSupported(QString systemName) override;
 /*public*/ bool isNumControlBitsSupported(QString systemName) override;
 /**
  * TurnoutOperation support. Return a list which is just the concatenation of
  * all the valid operation types
  */
 /*public*/ QStringList getValidOperationTypes() override;
 /*public*/ bool allowMultipleAdditions(QString systemName) override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix) /*throw (JmriException)*/ override;
 /*public*/ QString getNextValidAddress(QString curAddress, QString prefix) /*throw (JmriException)*/ override;
 /*public*/ QString getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, bool ignoreInitialExisting) /*throws jmri.JmriException*/override;
 /*public*/ void setDefaultClosedSpeed(QString speed) /*throw (JmriException)*/ override;
 /*public*/ void setDefaultThrownSpeed(QString speed) /*throw (JmriException)*/ override;
 /*public*/ QString getDefaultThrownSpeed()const override;
 /*public*/ QString getDefaultClosedSpeed()const override;
 /*public*/ int getXMLOrder() const  override;
 QCompleter* getCompleter(QString text);
 /*public*/ Turnout* provideTurnout(QString name)  override;
 /*public*/ Turnout* provide(QString name)  /*throw (IllegalArgumentException)*/ override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Turnout";
 }
 /*public*/ QString toString()override {return "ProxyTurnoutManager";}

 /*public*/ SystemConnectionMemo* getMemo() override {return AbstractProxyManager::getMemo();}
 /*public*/ QSet<NamedBean*> getNamedBeanSet() override {return AbstractProxyManager::getNamedBeanSet();}
 /*public*/ NamedBean* getBySystemName(QString name) const override {
  if(AbstractProxyManager::getBySystemName(name))
   return AbstractProxyManager::getBySystemName(name);
  else return nullptr;
 }
 /*public*/ NamedBean* getByUserName(QString name) const override {
  if(AbstractProxyManager::getBySystemName(name))
   return AbstractProxyManager::getByUserName(name);
  else return nullptr;
 }
 /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractProxyManager::addPropertyChangeListener(l); }
 /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override {AbstractProxyManager::removePropertyChangeListener(l); }

 QObject* mself() override {return (QObject*)this;}
 QObject* vself() override {return (QObject*)this;}
 QObject* pself() override {return (QObject*)this;}

public slots:


signals:
 void propertyChange(PropertyChangeEvent *e)override;
private:
 Logger log;
 /*private*/ QString defaultClosedSpeed = "Normal";
 /*private*/ QString defaultThrownSpeed = "Restricted";

protected:
 virtual /*protected*/ AbstractManager* makeInternalManager()  const override;
 /*protected*/ Turnout* makeBean(AbstractManager/*<Turnout>*/* manager, QString systemName, QString userName) /*throws IllegalArgumentException*/ override;
 ///*public*/ NamedBean* newNamedBean(QString systemName, QString userName);

 friend class AbstractProxyManager;
};

#endif // PROXYTURNOUTMANAGER_H
