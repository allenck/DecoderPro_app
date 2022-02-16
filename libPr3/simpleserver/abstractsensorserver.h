#ifndef ABSTRACTSENSORSERVER_H
#define ABSTRACTSENSORSERVER_H

#include <QObject>
#include "propertychangelistener.h"
#include "exceptions.h"

class SSSensorListener;
class Sensor;
class Logger;
class AbstractSensorServer : public QObject
{
 Q_OBJECT
public:
 explicit AbstractSensorServer(QObject *parent = nullptr);
 /*abstract*/ virtual /*public*/ void sendStatus(QString sensor, int Status) /*throw (IOException)*/ {}

 /*abstract*/ virtual /*public*/ void sendErrorStatus(QString sensor) /*throw (IOException)*/ {}

 /*abstract*/ virtual /*public*/ void parseStatus(QString statusString) /*throw (JmriException, IOException)*/ {}
 /*public*/ Sensor* initSensor(QString sensorName) /*throw (IllegalArgumentException)*/;
 /*public*/ void setSensorActive(QString sensorName);
 /*public*/ void setSensorInactive(QString sensorName);
 /*public*/ void dispose();

signals:

public slots:
private:
 /*private*/ /*final*/ QMap<QString, SSSensorListener*> sensors;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(AbstractSensorServer.class);

protected:
 /*synchronized*/ /*protected*/ void addSensorToList(QString sensorName);
 /*synchronized*/ /*protected*/ void removeSensorFromList(QString sensorName);
friend class SSSensorListener;
};

class SSSensorListener : public QObject,public PropertyChangeListener
{
Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 QString name;// = null;
 Sensor* sensor = nullptr;
 AbstractSensorServer *abstractSensorServer;
 public:

    SSSensorListener(QString sensorName, AbstractSensorServer *abstractSensorServer) ;
    QObject* self() override{return (QObject*)this;}
 public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};
#endif // ABSTRACTSENSORSERVER_H
