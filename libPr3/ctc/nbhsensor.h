#ifndef NBHSENSOR_H
#define NBHSENSOR_H

#include <QObject>
#include "namedbeanhandle.h"
#include "sensor.h"
#include "propertychangelistener.h"
#include "ctcexception.h"

class NBHSensor : public QObject
{
  Q_OBJECT
 public:
  NBHSensor( QObject* parent= nullptr) : QObject(parent) {}
  /*public*/ NBHSensor(QString module, QString userIdentifier, QString parameter, QString sensor, bool optional,  QObject* parent= nullptr);
  /*public*/ NBHSensor(QString module, QString userIdentifier, QString parameter, QString sensorName, QObject* parent= nullptr);

  /*public*/ static /*final*/ int DEFAULT_SENSOR_STATE_RV;// = Sensor.INACTIVE;
  /*public*/ Sensor* getBean();
  /*public*/ NamedBeanHandle<NamedBean*>* getBeanHandle();
  /*public*/ NBHSensor(NamedBeanHandle<Sensor*>* namedBeanHandleSensor);
  /*public*/ bool matchSensor(Sensor* sensor);
  /*public*/ bool valid();
  /*public*/ int getKnownState();
  /*public*/ void setKnownState(int newState);
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* propertyChangeListener);
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* propertyChangeListener);
  /*public*/ QString getHandleName();
  /*public*/ int testingGetCountOfPropertyChangeListenersRegistered();

 signals:

 public slots:

 private:
  /*private*/ NamedBeanHandle<Sensor*>* _mNamedBeanHandleSensor = nullptr;
  /*private*/ /*final*/ QString _mUserIdentifier;
  /*private*/ /*final*/ QString _mParameter;
  /*private*/ /*final*/ bool _mOptional = false;
  /*private*/ /*final*/ QList<PropertyChangeListener*> _mArrayListOfPropertyChangeListeners = QList<PropertyChangeListener*>();
  void registerSensor(QString sensorName);
  /*private*/ static Sensor* getSafeExistingJMRISensor(QString module, QString userIdentifier, QString parameter, QString sensor);
  /*private*/ static Sensor* getSafeOptionalJMRISensor(QString module, QString userIdentifier, QString parameter, QString sensor);
  /*private*/ static Sensor* getSafeInternalSensor(QString module, QString userIdentifier, QString parameter, QString sensor);
  /*private*/ static Sensor* getExistingJMRISensor(QString module, QString userIdentifier, QString parameter, QString sensor) throw (CTCException);
  /*private*/ static Sensor* getOptionalJMRISensor(QString module, QString userIdentifier, QString parameter, QString sensor) throw (CTCException);
  /*private*/ static Sensor* getInternalSensor(QString module, QString userIdentifier, QString parameter, QString sensor) throw (CTCException);

};

#endif // NBHSENSOR_H
