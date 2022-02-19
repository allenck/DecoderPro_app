#ifndef LNSENSORMANAGER_H
#define LNSENSORMANAGER_H
#include "abstractsensormanager.h"
#include "lntrafficcontroller.h"
#include "sensor.h"
#include "exceptions.h"
//#include "instancemanager.h"
#include "lnpacketizer.h"

/**
 * Manage the LocoNet-specific Sensor implementation.
 *
 * System names are "LSnnn", where nnn is the sensor number without padding.
 *
 * @author			Bob Jacobsen Copyright (C) 2001
 * @version			$Revision: 18178 $
 */
//class AbstractSensorManager;
class LIBPR3SHARED_EXPORT LnSensorManager : public AbstractSensorManager, public LocoNetListener
{
    Q_OBJECT
  Q_INTERFACES(LocoNetListener)
public:
//    LnSensorManager(LnTrafficController* tc, QString prefix, QObject *parent = 0);
    /*public*/ LnSensorManager(LocoNetSystemConnectionMemo* memo, QObject *parent = 0);

    virtual QString getSystemPrefix();
    // to free resources when no longer used
    virtual void dispose();
    // LocoNet-specific methods
    virtual Sensor* createNewSensor(QString systemName, QString userName);
    // listen for sensors, creating them as needed
//    void message(LocoNetMessage* l);
    /**
     * Requests status updates from all layout sensors.
     */
    void updateAll();
    /**
     * Method to set Route busy when commands are being issued to
     *   Route turnouts
     */
    void setUpdateBusy();
    /**
     * Method to set Route not busy when all commands have been
     *   issued to Route turnouts
     */
    void setUpdateNotBusy();
    bool allowMultipleAdditions(QString systemName);

    QString createSystemName(QString curAddress, QString prefix); // throws JmriException
    QString getNextValidAddress(QString curAddress, QString prefix);
    /*public*/ void setDefaultSensorState(QString state);
    /*public*/ QString getNamedBeanClass()const override {
        return "LnSensor";
    }
    /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}
    ///*public*/ QSet<NamedBean*> getNamedBeanSet() override {return AbstractManager::getNamedBeanSet();}
    /*public*/ Sensor* getBySystemName(QString name) override {return (Sensor*)AbstractManager::getBySystemName(name);}
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::addPropertyChangeListener(l);}
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::removePropertyChangeListener(l);}

    QObject* vself() override { return (QObject*)this;}
signals:
    
public slots:
 void message(LocoNetMessage* l);

private:
 LnTrafficController* tc;
 QString prefix;
 int address(int a1, int a2);
 bool busy;
Logger log;
int iName;
int defaultSensorState;// = Sensor.UNKNOWN;

};

#endif // LNSENSORMANAGER_H
