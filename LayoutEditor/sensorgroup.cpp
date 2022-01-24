#include "sensorgroup.h"
#include "route.h"
#include "routemanager.h"
#include "instancemanager.h"
#include "defaultroute.h"

//SensorGroup::SensorGroup(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Object for representing, creating and editing sensor groups.
 * <P>
 * Sensor groups are implemented by (groups) of Routes, not by any other object.
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @version	$Revision: 28746 $
 */
///*public*/ class SensorGroup {

/**
 * Nobody can build an anonymous object
 */
///*private*/ SensorGroup() {
//}
/*private*/ /*final*/ /*static*/ QString SensorGroup::namePrefix = "SENSOR GROUP:";  // should be upper case
/*private*/ /*final*/ /*static*/ QString SensorGroup::nameDivider = ":";


/**
 * Create one, looking up an existing one if present
 */
SensorGroup::SensorGroup(QString name,QObject *parent) :
  QObject(parent)
{
 log = new Logger("SensorGroup");
 this->name = name;
 // find suitable
 RouteManager* rm = (RouteManager*)InstanceManager::getDefault("RouteManager");
 QString group = name.toUpper();
 QStringList l = rm->getSystemNameList();
 QString prefix = (namePrefix + group + nameDivider).toUpper();

 sensorList = QStringList();
 for (int i = 0; i < l.size(); i++) {
     QString routeName = l.at(i);
     if (routeName.startsWith(prefix)) {
         QString sensor = routeName.mid(prefix.length());
         // remember that sensor
         sensorList.append(sensor);
     }
 }
}

void SensorGroup::addPressed() {
    log->debug("start with " + QString::number(sensorList.size()) + " lines");
    RouteManager* rm = (RouteManager*)InstanceManager::getDefault("RouteManager");
    QString group = name.toUpper();

    // remove the old routes
    QStringList l = rm->getSystemNameList();
    QString prefix = (namePrefix + group + nameDivider).toUpper();

    for (int i = 0; i < l.size(); i++) {
        QString routeName = l.at(i);
        if (routeName.startsWith(prefix)) {
            // OK, kill this one
            Route* r = (Route*)rm->getBySystemName(l.at(i));
            r->deActivateRoute();
            rm->deleteRoute(r);
        }
    }

    // add the new routes
    for (int i = 0; i < sensorList.size(); i++) {
        QString sensor = sensorList.at(i);
        QString routeName = namePrefix + group + nameDivider + sensor;
        Route* r = new DefaultRoute(routeName);
        // add the control sensor
        r->addSensorToRoute(sensor, Route::ONACTIVE);
        // add the output sensors
        for (int j = 0; j < sensorList.size(); j++) {
            QString outSensor = sensorList.at(j);
            int mode = Sensor::INACTIVE;
            if (i == j) {
                mode = Sensor::ACTIVE;
            }
            r->addOutputSensor(outSensor, mode);
        }
        // make it persistant & activate
        r->activateRoute();
        rm->Register((NamedBean*)r);
    }
}
