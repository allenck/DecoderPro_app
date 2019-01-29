#ifndef ABSTRACTSENSORMANAGER_H
#define ABSTRACTSENSORMANAGER_H
#include "sensormanager.h"
//#include "sensor.h"
#include <QRegExp>
#include "exceptions.h"
#include "logger.h"

//class AbstractManager;
class Sensor;
class LIBPR3SHARED_EXPORT AbstractSensorManager : public SensorManager
{
    Q_OBJECT
public:
    AbstractSensorManager(QObject *parent = 0);
    /*public*/ virtual int getXMLOrder();
    /*public*/ virtual char typeLetter() ;
    /*public*/ Sensor* provideSensor(QString name);
    /*public*/ Sensor* getSensor(QString name);
    /*public*/ Sensor* getBySystemName(QString key);
    /*public*/ Sensor* getByUserName(QString key);
    /**
     * Requests status of all layout sensors under this Sensor Manager.
     * This method may be invoked whenever the status of sensors needs to be updated from
     *		the layout, for example, when an XML configuration file is read in.
     * Note that this NULL implementation only needs be implemented in system-specific
     *		Sensor Managers where readout of sensor status from the layout is possible.
     */
    /*public*/ void updateAll();
    /**
     * A method that determines if it is possible to add a range of sensors in numerical
     * order eg 10 to 30, primarily used to enable/disable the add range box in the add sensor panel
     **/

     /*public*/ bool allowMultipleAdditions(QString systemName);

    /*public*/ QString createSystemName(QString curAddress, QString prefix) throw (JmriException);
    /*public*/ Sensor* newSensor(QString sysName, QString userName);
    /*public*/ QString getNextValidAddress(QString curAddress, QString prefix);
    /*public*/ long getDefaultSensorDebounceGoingActive();
    /*public*/ long getDefaultSensorDebounceGoingInActive();
    /*public*/ void setDefaultSensorDebounceGoingActive(long timer);
    /*public*/ void setDefaultSensorDebounceGoingInActive(long timer);
//    /*static*/ /*final java.util.regex.Matcher*/ QRegExp numberMatcher("\\d++");// = java.util.regex.Pattern.compile("\\d++").matcher("");

signals:
    //void newSensorCreated(AbstractSensorManager*, Sensor* s);
    void propertyChange(PropertyChangeEvent *e);

public slots:
private:
    bool isNumber(QString s);
    Logger* log;
protected:
    /*protected*/ QObject* getInstanceBySystemName(QString systemName);
    /**
     * Internal method to invoke the factory, after all the
     * logic for returning an existing method has been invoked.
     * @return new NULL
     */
    virtual /*abstract protected*/ Sensor* createNewSensor(QString /*systemName*/, QString /*userName*/) {return NULL;}

    /*protected*/ long sensorDebounceGoingActive/* = 0L*/;
    /*protected*/ long sensorDebounceGoingInActive/* = 0L*/;
    /*protected*/ QString normalizeSystemName(QString sysName);
//QMap<QString, Sensor*> sensorMap; // key = systemName!
    friend class PropertyChangeSupport;
};
//QRegExp AbstractSensorManager::numberMatcher;
#endif // ABSTRACTSENSORMANAGER_H
