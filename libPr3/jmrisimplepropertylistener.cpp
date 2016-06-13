#include "jmrisimplepropertylistener.h"
#include "conditional.h"
#include "namedbeanhandle.h"
#include "defaultconditional.h"

//JmriSimplePropertyListener::JmriSimplePropertyListener(QObject *parent) :
//    PropertyChangeListener(parent)
//{
//}
/**
 * A service base class for monitoring a bound property
 * in one of the JMRI Named beans
 * (Turnout, Sensor, etc).
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

///*public*/ class JmriSimplePropertyListener implements PropertyChangeListener
//{


JmriSimplePropertyListener::JmriSimplePropertyListener(QString propName, int type, QString varName, int varType, Conditional* client, QObject *parent) : PropertyChangeListener()
{
 _namedBean = NULL;
 _propertyName = propName;
 _type = type;
 _varName = varName;
 _varType = varType;
 _clients = new QList<Conditional*>();
 _clients->append(client);
 _enabled = true;
}
//template <class T>
JmriSimplePropertyListener::JmriSimplePropertyListener(QString propName, int type, NamedBeanHandle<NamedBean*>* namedBean, int varType, Conditional* client, QObject *parent) : PropertyChangeListener()
{
 _propertyName = propName;
 _type = type;
 _namedBean = namedBean;
 _varType = varType;
 _clients = new QList<Conditional*>();
 _clients->append(client);
 _enabled = true;
}

NamedBeanHandle<NamedBean*>* JmriSimplePropertyListener::getNamedBean(){
    return _namedBean;
}

/*public*/ int JmriSimplePropertyListener::getType() {
    return _type;
}

/*public*/ QString JmriSimplePropertyListener::getPropertyName() {
    return _propertyName;
}

/*public*/ int JmriSimplePropertyListener::getVarType() {
    return _varType;
}

/*public*/ QString JmriSimplePropertyListener::getDevName()
{
 if(_namedBean!=NULL)
 {
  return _namedBean->getName();
 }
 return _varName;
}

/*public*/ void JmriSimplePropertyListener::addConditional(Conditional* client) {
    _clients->append(client);
}

/*public*/ void JmriSimplePropertyListener::setEnabled(bool state) {
    _enabled = state;
}

/*public*/ void JmriSimplePropertyListener::calculateClient(int idx, PropertyChangeEvent* evt) {
    ((DefaultConditional*) _clients->at(idx))->calculate(_enabled, evt);
}

/**
* When _enabled is false, Conditional.calculate will compute the state of the conditional,
* but will not trigger its actions. When _enabled is true, Conditional.calculates its
* state and trigger its actions if its state has changed.
*/
/*public*/ void JmriSimplePropertyListener::propertyChange(PropertyChangeEvent* evt)
{
 //log.debug("\""+_varName+"\" sent PropertyChangeEvent "+evt.getPropertyName()+
 //    ", old value =\""+evt.getOldValue()+"\", new value =\""+evt.getNewValue()+
 //    ", enabled = "+_enabled);
 QVariant newValue = evt->getNewValue();
 if (newValue!=QVariant() && newValue==(evt->getOldValue()))
 {
  return;
 }
 for (int i=0; i<_clients->size(); i++)
 {
  ((DefaultConditional*) _clients->at(i))->calculate(_enabled, evt);
 }
}
