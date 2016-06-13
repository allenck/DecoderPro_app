#include "jmrimultistatepropertylistener.h"

//JmriMultiStatePropertyListener::JmriMultiStatePropertyListener(QObject *parent) :
//    JmriSimplePropertyListener(parent)
//{
//}
/**
 * A service base class for monitoring a bound property
 * in one of the JMRI Named beans
 * (Turnout, Sensor, etc).
 * For use with properties that may have more than two states
 * where the states are represented by numbers than can be cast to integers.
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
 * @since           2.5.1
 */

///*public*/ class JmriMultiStatePropertyListener extends JmriSimplePropertyListener
//{

JmriMultiStatePropertyListener::JmriMultiStatePropertyListener(QString propName, int type, QString name, int varType,
                          Conditional* client, int state, QObject *parent) : JmriSimplePropertyListener(propName, type, name, varType, client, parent)
{
    //super(propName, type, name, varType, client);
    log = new Logger("JmriMultiStatePropertyListener");
    _states = new QList<int>();
    _states->append((state));
}

/*public*/ void JmriMultiStatePropertyListener::setState(int state) {
    _states->append((state));
}

/*public*/ void JmriMultiStatePropertyListener::propertyChange(PropertyChangeEvent* evt) {
    log->debug("\""+_varName+"\" sent PropertyChangeEvent "+evt->getPropertyName()+
        ", old value =\""+evt->getOldValue().toString()+"\", new value =\""+evt->getNewValue().toString()+
        ", enabled = "+_enabled);
    if ( getPropertyName()==(evt->getPropertyName()) ) {
        int newState = ( evt->getNewValue()).toInt();
        int oldState = ( evt->getOldValue()).toInt();
        if (newState != oldState)  {
            for (int i=0; i<_states->size(); i++)
            {
                int state = _states->at(i);
                if (oldState == state || newState == state) {
                    calculateClient(i, evt);
                }
            }
        }
    }
}
