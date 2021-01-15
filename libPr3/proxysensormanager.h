#ifndef PROXYSENSORMANAGER_H
#define PROXYSENSORMANAGER_H
#include "abstractproxysensormanager.h"
#include <QString>
#include "exceptions.h"
//#include "internalsensormanager.h"
//#include <QDebug>
#include <QCompleter>

class ProxySensorManager : public AbstractProxySensorManager/*, public SensorManager*/
{
 Q_OBJECT
public:
 ProxySensorManager(QObject* parent = nullptr);
 /*public*/ Sensor* getSensor(QString name) const override;
 /*public*/ Sensor* provideSensor(QString sName) override;
 /**
  * Locate an instance based on a system name.  Returns null if no
  * instance already exists.
  * @return requested Turnout object or null if none exists
  */
// /*public*/ Sensor* getBySystemName(QString sName) const;
 /**
  * Locate an instance based on a user name.  Returns null if no
  * instance already exists.
  * @return requested Turnout object or null if none exists
  */
// /*public*/ Sensor* getByUserName(QString userName) const;
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
 /*public*/ Sensor* newSensor(QString systemName, QString userName);
 // null implementation to satisfy the SensorManager interface
 /*public*/ void updateAll()const override;
 /*public*/ bool allowMultipleAdditions(QString systemName) override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix)const throw (JmriException) override;
 /*public*/ QString getNextValidAddress(QString curAddress, QString prefix) throw (JmriException) override;
 /*public*/ long getDefaultSensorDebounceGoingActive() override;
 /*public*/ long getDefaultSensorDebounceGoingInActive() override;
 /*public*/ void setDefaultSensorDebounceGoingActive(long timer) override;
 /*public*/ void setDefaultSensorDebounceGoingInActive(long timer) override;
 /*public*/ int getXMLOrder()const override;
 QCompleter* getCompleter(QString text);
 /*public*/ QString getNamedBeanClass()const override {
     return "Sensor";
 }
 /*public*/ QString getEntryToolTip() override;
 /*public*/ bool isPullResistanceConfigurable() override;
/*public*/ QString toString() {return "ProxySensorManager";}
signals:
 void propertyChange(PropertyChangeEvent *e);
 //void newSensorCreated(AbstractSensorManager*,Sensor*);

private:
 Logger log;

protected:
 ///*private*/ AbstractManager* getInternal();
 virtual /*protected*/ Manager* makeInternalManager() const;
 virtual /*protected*/ Sensor* makeBean(int i, QString systemName, QString userName);
 // /*public*/ NamedBean* newNamedBean(QString systemName, QString userName);
 // /*protected*/ NamedBean* provideNamedBean(QString name);

 friend class AbstractProxyManager;
};

#endif // PROXYSENSORMANAGER_H
