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
    AbstractSensorManager(SystemConnectionMemo* memo, QObject *parent =nullptr);

    /*public*/ int getXMLOrder()const override;
    /*public*/ char typeLetter() const  override;
    /*public*/ Sensor* provideSensor(QString name) override;
    /*public*/ Sensor* getSensor(QString name) const override;
    /*public*/ NamedBean* getBySystemName(QString key) const override;
    /*public*/ NamedBean* getByUserName(QString key) const override;
    /**
     * Requests status of all layout sensors under this Sensor Manager.
     * This method may be invoked whenever the status of sensors needs to be updated from
     *		the layout, for example, when an XML configuration file is read in.
     * Note that this NULL implementation only needs be implemented in system-specific
     *		Sensor Managers where readout of sensor status from the layout is possible.
     */
    /*public*/ void updateAll()const override;
    /**
     * A method that determines if it is possible to add a range of sensors in numerical
     * order eg 10 to 30, primarily used to enable/disable the add range box in the add sensor panel
     **/

     /*public*/ bool allowMultipleAdditions(QString systemName) override;

    /*public*/ QString createSystemName(QString curAddress, QString prefix)const throw (JmriException) override;
    /*public*/ Sensor* newSensor(QString sysName, QString userName) override;
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ QString getNextValidAddress(QString curAddress, QString prefix) override;
    /*public*/ long getDefaultSensorDebounceGoingActive() override;
    /*public*/ long getDefaultSensorDebounceGoingInActive() override;
    /*public*/ void setDefaultSensorDebounceGoingActive(long timer) override;
    /*public*/ void setDefaultSensorDebounceGoingInActive(long timer) override;
//    /*static*/ /*final java.util.regex.Matcher*/ QRegExp numberMatcher("\\d++");// = java.util.regex.Pattern.compile("\\d++").matcher("");

signals:
    //void newSensorCreated(AbstractSensorManager*, Sensor* s);
    void propertyChange(PropertyChangeEvent *e) override;

public slots:
private:
    bool isNumber(QString s) const;
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
    /*protected*/ QString normalizeSystemName(QString sysName)const  override;
//QMap<QString, Sensor*> sensorMap; // key = systemName!
    friend class PropertyChangeSupport;
};
//QRegExp AbstractSensorManager::numberMatcher;
#endif // ABSTRACTSENSORMANAGER_H
