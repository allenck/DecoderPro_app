#include "sensorgroupconditional.h"
#include "sensor.h"
#include "abstractsensor.h"
#include "instancemanager.h"
#include "proxysensormanager.h"
#include "conditionalaction.h"
//SensorGroupConditional::SensorGroupConditional(QObject *parent) :
//    DefaultConditional(parent)
//{
//}
/**
 * Conditional.java
 *
 * A Conditional type to provide runtime support for Densor Groups.
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * @author			Pete Cressman Copyright (C) 2009
 * @version			$Revision 1.0 $
 */


///*public*/ class SensorGroupConditional extends DefaultConditional
//    implements java.io.Serializable {

/*public*/ SensorGroupConditional::SensorGroupConditional(QString systemName, QString userName, QObject *parent) : DefaultConditional(systemName, userName, parent){
   // super(systemName, userName);
    log = new Logger("SensorGroupConditional");
}

//@SuppressWarnings("NULL")
/*public*/ int SensorGroupConditional::calculate (bool enabled, PropertyChangeEvent* evt) {
    int currentState = DefaultConditional::calculate(false, evt);
    if (!enabled || evt == NULL) {
        return currentState;
    }
    QString listener = ((AbstractSensor*)evt->getSource())->getSystemName();
    log->debug("SGConditional \""+getUserName()+"\" ("+getSystemName()+") has event from \""+listener+"\"");
    if (Sensor::INACTIVE == evt->getNewValue().toInt()) {
        return currentState;
    }
    for (int i = 0; i < _actionList->size(); i++) {
        ConditionalAction* action = _actionList->at(i);
        Sensor* sn = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(action->getDeviceName());
        if (sn == NULL) {
            log->error("invalid sensor name in action - "+action->getDeviceName());
        }
        if (listener!=(action->getDeviceName())) // don't change who triggered the action
        {   // find the old one and reset it
            if (((AbstractSensor*)sn)->getState() != action->getActionData())

                try {
                    ((AbstractSensor*)sn)->setKnownState(action->getActionData());
                }
                catch (JmriException* e) {
                    log->warn("Exception setting sensor "+action->getDeviceName()+" in action");
                }
        }
    }
    log->debug("SGConditional \""+getUserName()+"\" ("+getSystemName()+"), state= "+currentState+
              "has set the group actions for "+listener);
    return currentState;
}
