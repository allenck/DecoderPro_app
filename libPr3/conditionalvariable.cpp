#include "conditionalvariable.h"
#include "conditional.h"
#include "namedbeanhandle.h"
#include "sensor.h"
#include "instancemanager.h"
#include "proxysensormanager.h"
#include "turnout.h"
#include "proxyturnoutmanager.h"
#include "namedbeanhandlemanager.h"
#include "abstractmemorymanager.h"
#include "light.h"
#include "abstractlightmanager.h"
#include "signalhead.h"
#include "abstractsignalheadmanager.h"
#include "signalmast.h"
#include "defaultsignalmastmanager.h"
#include "namedbean.h"
#include "conditionalmanager.h"
#include "../Tables/logixtableaction.h"
#include "warrantmanager.h"
#include "oblockmanager.h"
#include "entryexitpairs.h"
#include "warrant.h"
#include "oblock.h"
#include "loggerfactory.h"
#include "proxylightmanager.h"

ConditionalVariable::ConditionalVariable(QObject *parent) :
    QObject(parent)
{
    common();
}
/**
 * ConditionalVariable.java
 *
 * The variable used in the antecedent (the 'if' part) of the Conditional::
 * proposition.  The states of ConditionalVariables and logic expression 
 * of the antecedent determine the state of the Conditional::
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


///*public*/ class ConditionalVariable {

//	static final ResourceBundle rbx = ResourceBundle.getBundle("jmri.jmrit.beantable.LogixTableBundle");
//	static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.NamedBeanBundle");

    


//    /*public*/ ConditionalVariable() {
//    }
void ConditionalVariable::common()
{
 _not = false;
 // Not a variable attribute, but retained as an artifact of previous releases.  This will be used
 // as the default operator immediately to the left of this variable in the antecedent statement. 
 // It may be over written by the antecedent statement in the Conditional to which this variable 
 // belongs.
 _opern = Conditional::OPERATOR_NONE;
 _type   = Conditional::TYPE_NONE;
 _name = "";
 _dataString = "";
 _num1 = 0;
 _num2 = 0;
 _guiName = "";       // Contains the user name of the referenced conditional
 setObjectName("ConditionalVariable");

 _namedBean = nullptr;
 nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
//private NamedBeanHandle<Sensor> _namedSensorBean = nullptr;
 _triggersActions = true;
 _state = Conditional::UNKNOWN;        // tri-state

}

/*public*/ ConditionalVariable::ConditionalVariable(bool _not, int opern, int type, QString name, bool trigger, QObject *parent) :     QObject(parent)
{
 common();
 this->_not = _not;
 _opern = opern;
 _type = type;
 _name = name;
 _triggersActions = trigger;
 try {
        
 int itemType = Conditional::TEST_TO_ITEM.at(type);
 switch (itemType)
 {
  case Conditional::ITEM_TYPE_SENSOR:
  {
   Sensor* sn = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(_name);
   if (sn == nullptr) {
       log->error("invalid sensor name= \""+_name+"\" in state variable");
       return;
   }
   _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, sn);
   break;
  }
  case Conditional::ITEM_TYPE_TURNOUT:
  {
        Turnout* tn = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(_name);
        if (tn == nullptr) {
            log->error("invalid turnout name= \""+_name+"\" in state variable");
            return;
        }
        _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, tn);
        break;
  }
  case Conditional::ITEM_TYPE_MEMORY:
  {
        Memory* my = ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->provideMemory(_name);
        if (my == nullptr) {
            log->error("invalid memory name= \""+_name+"\" in state variable");
            return;
        }
        _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, my);
        break;
  }
  case Conditional::ITEM_TYPE_LIGHT:
  {
        Light* l = (Light*)((AbstractLightManager*)InstanceManager::lightManagerInstance())->getLight(_name);
        if (l == nullptr) {
            log->error("invalid light name= \""+_name+"\" in state variable");
            return;
        }
        _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, l);
        break;
  }
  case Conditional::ITEM_TYPE_SIGNALHEAD:
  {
        SignalHead* s = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(_name);
        if (s == nullptr) {
            log->error("invalid signalhead name= \""+_name+"\" in state variable");
            return;
        }
        _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, s);
        break;
  }
  case Conditional::ITEM_TYPE_SIGNALMAST:
  {
   SignalMast* sm = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(_name);
   if (sm == nullptr) {
       log->error("invalid signalmast name= \""+_name+"\" in state variable");
       return;
   }
   _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, sm);
   break;
  }
  case Conditional::ITEM_TYPE_ENTRYEXIT:
  {
    NamedBean* nb = (NamedBean*)((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->getBySystemName(_name);
    if(nb == nullptr){
        log->error("invalid entry exit name= \""+_name+"\" in state variable");
        return;
    }
    _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, nb);
    break;
  }
  case Conditional::ITEM_TYPE_CONDITIONAL:
  {
   Conditional* c = ((ConditionalManager*)((ConditionalManager*)InstanceManager::getDefault("ConditionalManager")))->getConditional(_name);
   if(c == nullptr){
       log->error("invalid conditiona; name= \""+_name+"\" in state variable");
       return;
   }
   _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, c);
   break;
  }
  case Conditional::ITEM_TYPE_WARRANT:
  {
   Warrant* w = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant(_name);
   if(w == nullptr){
       log->error("invalid warrant name= \""+_name+"\" in state variable");
       return;
   }
   _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, w);
   break;
  }
  case Conditional::ITEM_TYPE_OBLOCK:
  {
   OBlock* b = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(_name);
   if(b == nullptr)
   {
    log->error("invalid block name= \""+_name+"\" in state variable");
    return;
   }
   _namedBean = (NamedBeanHandle<NamedBean*>*)nbhm->getNamedBeanHandle(_name, b);
   break;
  }
  default :
   break;
  }
 }
 catch (NumberFormatException ex)
 {
     //Can be Considered Normal where the logix is loaded prior to any other beans
 }
}

/*public*/ bool ConditionalVariable::isNegated() {
    return _not;
}

/*public*/ void ConditionalVariable::setNegation(bool _not) {
    this->_not = _not;
}

/*public*/ int ConditionalVariable::getOpern() {
    return _opern;
}

/*public*/ void ConditionalVariable::setOpern(int opern) {
    if (opern == Conditional::OPERATOR_AND_NOT) {
        _opern = Conditional::OPERATOR_AND;
        _not = true;
    } else if (opern == Conditional::OPERATOR_NOT) {
        _opern = Conditional::OPERATOR_NONE;
        _not = true;
    } else {
        _opern = opern;
    }
}

/*public*/ int ConditionalVariable::getType() {
    return _type;
}

/*public*/ void ConditionalVariable::setType(int type) {
    _type = type;
}

/*public*/ QString ConditionalVariable::getName() {
    if (_namedBean!=nullptr){
        return _namedBean->getName();
    }
    /* As we have a trigger for something using the variable, then hopefully
    all the managers have been loaded and we can get the bean, which prevented
    the bean from being loaded in the first place */
    setName(_name);
    return _name;
}

/*public*/ void ConditionalVariable::setName(QString name)
{
 _name = name;
 NamedBean* bean = nullptr;
 int itemType = Conditional::TEST_TO_ITEM[_type];

 switch (itemType)
 {
 case Conditional::TYPE_NONE:
     break;
 case Conditional::ITEM_TYPE_CLOCK:
     break;	/* no beans for these, at least that I know of */
 case Conditional::ITEM_TYPE_SENSOR:
     bean = (NamedBean*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(_name);
     break;
 case Conditional::ITEM_TYPE_TURNOUT:
     bean = (NamedBean*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(_name);
     break;
 case Conditional::ITEM_TYPE_LIGHT:
     bean = (NamedBean*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getLight(_name);
     break;
 case Conditional::ITEM_TYPE_MEMORY:
     bean = (NamedBean*)((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->provideMemory(_name);
     break;
 case Conditional::ITEM_TYPE_SIGNALMAST:
     bean = (NamedBean*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(_name);
     break;
 case Conditional::ITEM_TYPE_SIGNALHEAD:
     bean = (NamedBean*)((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(_name);
     break;
 case Conditional::ITEM_TYPE_CONDITIONAL:
  bean = (NamedBean*)((ConditionalManager*)((ConditionalManager*)InstanceManager::getDefault("ConditionalManager")))->getConditional(_name);
  break;
 case Conditional::ITEM_TYPE_WARRANT:
  bean = (NamedBean*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant(_name);
  break;
 case Conditional::ITEM_TYPE_OBLOCK:
  bean =(NamedBean*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(_name);
  break;
 case Conditional::ITEM_TYPE_ENTRYEXIT:
  bean = (NamedBean*)((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->getBySystemName(_name);
  break;
 default : log->error("Type "+QString::number(itemType)+" not set for " + _name);
 }

 //Once all refactored, we should probably register an error if the bean is returned nullptr.
 if (bean!=nullptr)
 {
  _namedBean = nbhm->getNamedBeanHandle(_name, bean);
 }
 else
 {
  _namedBean = nullptr;
 }
}

/*public*/ NamedBeanHandle<NamedBean*>* ConditionalVariable::getNamedBean(){
    return _namedBean;
}

/*public*/ NamedBean* ConditionalVariable::getBean(){
    if (_namedBean!=nullptr){
        return (NamedBean*) _namedBean->getBean();
    } 
    setName(_name); //ReApply name as that will create namedBean, save replicating it here
    if(_namedBean!=nullptr)
        return (NamedBean*) _namedBean->getBean();
    return nullptr;
}

/*public*/ QString ConditionalVariable::getDataString() {
    return _dataString;
}

/*public*/ void ConditionalVariable::setDataString(QString data) {
 _dataString = data;
 if (data != ""
         && Conditional::TEST_TO_ITEM[_type] == Conditional::ITEM_TYPE_MEMORY) {
     NamedBean* bean = InstanceManager::memoryManagerInstance()->getMemory(data);
     if (bean != nullptr) {
         _namedBeanData = nbhm->getNamedBeanHandle(data, bean);
     }
 }
}

/*public*/ NamedBean* ConditionalVariable::getNamedBeanData() {
    if (_namedBeanData != nullptr) {
        return _namedBeanData->getBean();
    }
    return nullptr;
}

/*public*/ int ConditionalVariable::getNum1() {
    return _num1;
}

/*public*/ void ConditionalVariable::setNum1(int num) {
    _num1 = num;
}

/*public*/ int ConditionalVariable::getNum2() {
    return _num2;
}

/*public*/ void ConditionalVariable::setNum2(int num) {
    _num2 = num;
}
/**
 * @since 4.7.4
 * @return the GUI name for the referenced conditional.
 */
/*public*/ QString ConditionalVariable::getGuiName() {
    return _guiName;
}

/**
 * Set the GUI name for the conditional state variable.
 * @since 4.7.4
 * @param guiName The referenced Conditional user name.
 */
/*public*/ void ConditionalVariable::setGuiName(QString guiName) {
    _guiName = guiName;
}
/**
* If change of state of this object causes a change of state of the Conditional,
* should any actions be executed.
*/
/*public*/ bool ConditionalVariable::doTriggerActions() {
    return _triggersActions;
}

/*public*/ void ConditionalVariable::setTriggerActions(bool trigger) {
    _triggersActions = trigger;
}

/*public*/ int ConditionalVariable::getState() {
    return _state;
}

/*public*/ void ConditionalVariable::setState(int state) {
    _state = state;
}

/*public*/ void ConditionalVariable::setState(bool state) {
    if (state)
    {
        _state = Conditional::_TRUE;
    }
    else
    {
        _state = Conditional::_FALSE;
    }
}

/*public*/ QString ConditionalVariable::getTestTypeString() {
    return getTestTypeString(_type);
}

/*public*/ QString ConditionalVariable::getOpernString() {
    switch (_opern) {
        case Conditional::OPERATOR_AND:
            return tr("AND");
        case Conditional::OPERATOR_NOT:
            return tr("NOT");
        case Conditional::OPERATOR_AND_NOT:
            return tr("AND");
        case Conditional::OPERATOR_NONE:
            return "";
        case Conditional::OPERATOR_OR:
            return tr("OR");
        default : return "";
    }
}

/**
*  Evaluates this State Variable
*  <P>
*  Returns true if variable evaluates true, otherwise false. 
*/
//@SuppressWarnings("deprecation")        // Date.getMinutes, Date.getHours
/*public*/ bool ConditionalVariable::evaluate() {
    bool result = true;
    // evaluate according to state variable type
    int itemType = Conditional::TEST_TO_ITEM[_type];
    if (log->isDebugEnabled()) log->debug("evaluate: \""+getName()+"\" type= "+QString::number(_type)+" itemType= "+QString::number(itemType));
    switch (itemType)
    {
     case Conditional::ITEM_TYPE_SENSOR:
     {
      //Sensor sn = InstanceManager::sensorManagerInstance().provideSensor(getName());
      Sensor* sn = (Sensor*) getBean();
      if (sn == nullptr) {
        log->error("invalid sensor name= \""+getName()+"\" in state variable");
        return (false);
      }
      if (_type == Conditional::TYPE_SENSOR_ACTIVE) {
        if (sn->getState() == Sensor::ACTIVE) result = true;
        else result = false;
      } else {
        if (sn->getState() == Sensor::INACTIVE) result = true;
        else result = false;
     }
     break;
    }
    case Conditional::ITEM_TYPE_TURNOUT:
    {
            Turnout* t = (Turnout*) getBean();
            if (t == nullptr) {
                log->error("invalid turnout name= \""+getName()+"\" in state variable");
                return (false);
            }
            if (_type == Conditional::TYPE_TURNOUT_THROWN) {
                if (t->getKnownState() == Turnout::THROWN) result = true;
                else result = false;
            } else {
                if (t->getKnownState() == Turnout::CLOSED) result = true;
                else result = false;
            }
            break;
    }
    case Conditional::ITEM_TYPE_LIGHT:
    {
            Light* lgt = (Light*) getBean();
            if (lgt == nullptr) {
                log->error("invalid light name= \""+getName()+"\" in state variable");
                return (false);
            }
            if (_type == Conditional::TYPE_LIGHT_ON) {
                if (lgt->getState() == Light::ON) result = true;
                else result = false;
            } else {
                if (lgt->getState() == Light::OFF) result = true;
                else result = false;
            }
            break;
    }
    case Conditional::ITEM_TYPE_SIGNALMAST:
    {
            SignalMast* f = (SignalMast*) getBean();
            if (f == nullptr) {
                log->error("invalid signal mast name= \""+getName()+"\" in state variable");
                return (false);
            }
            switch ((_type)) {
                case Conditional::TYPE_SIGNAL_MAST_LIT:
                    result = f->getLit();
                    break;
                case Conditional::TYPE_SIGNAL_MAST_HELD:
                    result = f->getHeld();
                    break;
                case Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS:
                    if (f->getAspect() == nullptr) result = false;
                    else if (f->getAspect()==(_dataString)) result = true;
                    else result = false; 
            }
            break;
    }
    case Conditional::ITEM_TYPE_SIGNALHEAD:
    {
            SignalHead* h = (SignalHead*) getBean();
            if (h == nullptr) {
                log->error("invalid signal head name= \""+getName()+"\" in state variable");
                return (false);
            }
            switch (_type)
            {
                case Conditional::TYPE_SIGNAL_HEAD_RED:
                    if (h->getAppearance() == SignalHead::RED) result = true;
                    else result = false; 
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_YELLOW:
                    if (h->getAppearance() == SignalHead::YELLOW) result = true;
                    else result = false; 
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_GREEN:
                    if (h->getAppearance() == SignalHead::GREEN) result = true;
                    else result = false; 
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_DARK:
                    if (h->getAppearance() == SignalHead::DARK) result = true;
                    else result = false; 
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_FLASHRED:
                    if (h->getAppearance() == SignalHead::FLASHRED) result = true;
                    else result = false; 
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW:
                    if (h->getAppearance() == SignalHead::FLASHYELLOW) result = true;
                    else result = false; 
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN:
                    if (h->getAppearance() == SignalHead::FLASHGREEN) result = true;
                    else result = false; 
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_LUNAR:
                    if (h->getAppearance() == SignalHead::LUNAR) result = true;
                    else result = false; 
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_FLASHLUNAR:
                    if (h->getAppearance() == SignalHead::FLASHLUNAR) result = true;
                    else result = false; 
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_LIT:
                    result = h->getLit();
                    break;
                case Conditional::TYPE_SIGNAL_HEAD_HELD:
                    result = h->getHeld();
                    break;
                default:
                    result = false;
            }
            break;
    }
    case Conditional::ITEM_TYPE_MEMORY:
    {
            Memory* m = (Memory*) getBean();
            if (m == nullptr) {
                log->error("invalid memory name= \""+getName()+"\" in state variable");
                return (false);
            }
            QString value1 = nullptr;
            QString value2 = nullptr;
            if (m->getValue()!=QVariant()) {
                value1 = m->getValue().toString();
            }
            bool caseInsensitive = ((_type == Conditional::TYPE_MEMORY_EQUALS_INSENSITIVE) ||
                                        (_type == Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE));
            if ((_type == Conditional::TYPE_MEMORY_COMPARE) ||
                    (_type == Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE)) {
                Memory* m2 = InstanceManager::memoryManagerInstance()->provideMemory(_dataString);
                if (m2 == nullptr) {
                    log->error("invalid data memory name= \""+_dataString+"\" in state variable");
                    return (false);
                }
                if (m2->getValue()!=QVariant()) {
                    value2 = m2->getValue().toString();
                }
            } else {
                value2 = _dataString;
            }
            result = compare(value1,  value2, caseInsensitive);
            break;
    }
        case Conditional::ITEM_TYPE_CONDITIONAL:
    {
            Conditional* c = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getBySystemName(getName());
            if (c ==nullptr) {
                c = ((ConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getByUserName(getName());
                if (c == nullptr) {
                    log->error("invalid conditional name= \""+getName()+"\" in state variable");
                    return (false);
                }
            }
            if (_type == Conditional::TYPE_CONDITIONAL_TRUE) {
                if (c->getState() == Conditional::_TRUE) result = true;
                else result = false;
            } else {
                if (c->getState() == Conditional::_FALSE) result = true;
                else result = false;
            }
            break;
    }

        case Conditional::ITEM_TYPE_WARRANT:
    {
     Warrant* w = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant(getName());
            if (w == nullptr) {
                log->error("invalid Warrant name= \""+getName()+"\" in state variable");
                return (false);
            }
            switch (_type)
            {
                case Conditional::TYPE_ROUTE_FREE:
                    result = w->routeIsFree();
                    break;
                case Conditional::TYPE_ROUTE_OCCUPIED:
                    result = w->routeIsOccupied();
                    break;
                case Conditional::TYPE_ROUTE_ALLOCATED:
                    result = w->isAllocated();
                    break;
                case Conditional::TYPE_ROUTE_SET:
                    result = w->hasRouteSet();
                    break;
                case Conditional::TYPE_TRAIN_RUNNING:
                    // not in either RUN or LEARN state
                    result = !(w->getRunMode() == Warrant::MODE_NONE);
                    break;
                default:
                    result = false;
            }
            break;
    }
        case Conditional::ITEM_TYPE_CLOCK:
    {
            Timebase* fastClock = static_cast<Timebase*>(InstanceManager::getDefault("Timebase"));
            QDateTime currentTime = fastClock->getTime();
            int currentMinutes = (currentTime.time().hour()*60) + currentTime.time().minute();
            int beginTime = fixMidnight(_num1);
            int endTime = fixMidnight(_num2);
            // check if current time is within range specified
            if (beginTime<=endTime) {
                // range is entirely within one day
                if ( (beginTime<=currentMinutes)&&(currentMinutes<=endTime) ) result = true;
                else result = false;
            }
            else {
                // range includes midnight
                if (beginTime<=currentMinutes || currentMinutes<=endTime) result = true;
                else result = false;
            }
            break;
    }

        case Conditional::ITEM_TYPE_OBLOCK:
    {
     OBlock* b = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(getName());
            if (b == nullptr) {
                log->error("invalid OBlock name= \""+getName()+"\" in state variable");
                return (false);
            }
            result = b->statusIs(_dataString);
            break;
    }
        case Conditional::ITEM_TYPE_ENTRYEXIT:
    {
            NamedBean* e = getBean();
            if (_type == Conditional::TYPE_ENTRYEXIT_ACTIVE) {
                if (e->getState() == 0x02) result = true;
                else result = false;
            } else {
                if (e->getState()==0x04) result = true;
                else result = false;
            }
            break;
  }
  default : break;
 }
 // apply NOT if specified
 if ( _not )
 {
  result = !result;
 }
 if (result)
     setState(Conditional::_TRUE);
 else
     setState(Conditional::_FALSE);
 return (result);
}

bool ConditionalVariable::compare(QString value1, QString value2, bool caseInsensitive) {
    if (value1==nullptr) {
        if (value2==nullptr) return true;
        else return false;
    } else {
        if (value2==nullptr) return false;
        value1 = value1.trimmed();
        value2 = value2.trimmed();
    }
    try {
        int n1 = (value1.toInt());
        try {
            int n2 = value2.toInt();
            if (_num1 == 0) { // for former code
                if (n1 == n2) return true;
                else return false;
            }
            if (log->isDebugEnabled()) log->debug("Compare numbers: n1= "+QString::number(n1)+", to n2= "+n2);
            switch (_num1)  // both are numbers
            {
                case LESS_THAN:
                    return (n1 < n2);
                case LESS_THAN_OR_EQUAL:
                    return (n1 <= n2);
                case EQUAL:
                    return (n1 == n2);
                case GREATER_THAN_OR_EQUAL:
                    return (n1 >= n2);
                case GREATER_THAN:
                    return (n1 > n2);
            }
        } catch (NumberFormatException nfe) {
            return false;   // n1 is a number, n2 is not
        }
        log->error("Compare 'numbers': value1= "+value1+", to value2= "+value2);
    } catch (NumberFormatException nfe) { 
        try {
            value2.toInt();
            return false;     // n1 is not a number, n2 is
        } catch (NumberFormatException ex) { // OK neither a number
        }
    }
    if (log->isDebugEnabled()) log->debug("Compare Strings: value1= "+value1+", to value2= "+value2);
    int compare = 0;
    if (caseInsensitive) {
        compare = value1.toLower().compare(value2.toLower());
    } else {
        compare = value1.compare(value2);
    }
    if (_num1 == 0) { // for former code
        if (compare == 0) return true;
        else return false;
    }
    switch (_num1)
    {   // fall through
        case LESS_THAN:
            if (compare < 0) return true;
            break;
        case LESS_THAN_OR_EQUAL:
            if (compare <= 0) return true;
            break;
        case EQUAL:
            if (compare == 0) return true;
            break;
        case GREATER_THAN_OR_EQUAL:
            if (compare >= 0) return true;
            break;
        case GREATER_THAN:
            if (compare > 0) return true;
            break;
    }
    return false;
}

/*private*/ int ConditionalVariable::fixMidnight(int time) {
    if (time>24*60)
        time -= 24*60;
    return time;
}

/**
 * Convert Variable Type to Text String
 */
/*public*/ /*static*/ QString ConditionalVariable::getItemTypeString(int t) {
    switch (t) {
        case Conditional::ITEM_TYPE_SENSOR:
            return (tr("Sensor"));
        case Conditional::ITEM_TYPE_TURNOUT:
            return (tr("Turnout"));
        case Conditional::ITEM_TYPE_LIGHT:
            return (tr("Light"));
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            return (tr("SignalHead"));
        case Conditional::ITEM_TYPE_SIGNALMAST:
            return (tr("SignalMast"));
        case Conditional::ITEM_TYPE_MEMORY:
            return (tr("Memory"));
        case Conditional::ITEM_TYPE_CONDITIONAL:
            return (tr("Conditional"));
        case Conditional::ITEM_TYPE_WARRANT:
            return (tr("Warrant"));
        case Conditional::ITEM_TYPE_CLOCK:
            return (tr("FastClock"));
        case Conditional::ITEM_TYPE_OBLOCK:
            return (tr("OBlock"));
        case Conditional::ITEM_TYPE_ENTRYEXIT:
            return (tr("EntryExit"));
    }
    return "";
}
/**
 * Get state name from Variable Test Type
 *
 * @param t the state
 * @return the localized description
 */
/*public*/ /*static*/ QString ConditionalVariable::describeState(int t) {
    switch (t) {
        case Conditional::TYPE_NONE:
            return ""; // NOI18N
        case Conditional::TYPE_SENSOR_ACTIVE:
            return tr("Active"); // NOI18N
        case Conditional::TYPE_SENSOR_INACTIVE:
            return tr("Inactive"); // NOI18N
        case Conditional::TYPE_TURNOUT_THROWN:
            return tr("Thrown"); // NOI18N
        case Conditional::TYPE_TURNOUT_CLOSED:
            return tr("Closed"); // NOI18N
        case Conditional::TYPE_CONDITIONAL_TRUE:
            return tr("True"); // NOI18N
        case Conditional::TYPE_CONDITIONAL_FALSE:
            return tr("False"); // NOI18N
        case Conditional::TYPE_LIGHT_ON:
            return tr("LightOn"); // NOI18N
        case Conditional::TYPE_LIGHT_OFF:
            return tr("LightOff"); // NOI18N
        case Conditional::TYPE_MEMORY_EQUALS:
            return tr("StateMemoryEquals"); // NOI18N
        case Conditional::TYPE_MEMORY_COMPARE:
            return tr("StateMemoryCompare"); // NOI18N
        case Conditional::TYPE_FAST_CLOCK_RANGE:
            return ""; // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_RED:
            return tr("Red"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_YELLOW:
            return tr("Yellow"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_GREEN:
            return tr("Green"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_DARK:
            return tr("Dark"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_FLASHRED:
            return tr("Flashing Red"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW:
            return tr("Flashing Yellow"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN:
            return tr("Flashing Green"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_HELD:
            return tr("Held"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_LUNAR:
            return tr("Lunar"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_FLASHLUNAR:
            return tr("Flashing Lunar"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_LIT:
            return tr("TypeSignalHeadLit"); // NOI18N
        case Conditional::TYPE_MEMORY_EQUALS_INSENSITIVE:
            return tr("StateMemoryEqualsInsensitive"); // NOI18N
        case Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE:
            return tr("StateMemoryCompareInsensitive"); // NOI18N
        case Conditional::TYPE_ROUTE_FREE:
            return tr("StateRouteFree"); // NOI18N
        case Conditional::TYPE_ROUTE_OCCUPIED:
            return tr("stateRouteOccupied"); // NOI18N
        case Conditional::TYPE_ROUTE_ALLOCATED:
            return tr("StateRouteReserved"); // NOI18N
        case Conditional::TYPE_ROUTE_SET:
            return tr("StateRouteIsSet"); // NOI18N
        case Conditional::TYPE_TRAIN_RUNNING:
            return tr("StateTrainRunning"); // NOI18N
        case Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS:
            return tr("TypeSignalMastAspectEquals"); // NOI18N
        case Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS:
            return tr("TypeSignalHeadAspectEquals"); // NOI18N
        case Conditional::TYPE_SIGNAL_MAST_LIT:
            return tr("StateSignalMastLit"); // NOI18N
        case Conditional::TYPE_SIGNAL_MAST_HELD:
            return tr("StateSignalMastHeld"); // NOI18N
        case Conditional::TYPE_ENTRYEXIT_ACTIVE:
            return tr("SensorStateActive"); // NOI18N
        case Conditional::TYPE_ENTRYEXIT_INACTIVE:
            return tr("SensorStateInactive"); // NOI18N
        default:
            log->warn(tr("Unhandled condition type: %1").arg(t)); // NOI18N
            return "<none>";
    }
}
/**
 * get state name from Variable Test Type
 */
/*public*/ /*static*/ QString ConditionalVariable::getStateString(int t) {
    switch (t) {
        case Conditional::TYPE_NONE:
            return "";
        case Conditional::TYPE_SENSOR_ACTIVE:
            return (tr("Active"));
        case Conditional::TYPE_SENSOR_INACTIVE:
            return (tr("Inactive"));
        case Conditional::TYPE_TURNOUT_THROWN:
            return (tr("Thrown"));
        case Conditional::TYPE_TURNOUT_CLOSED:
            return (tr("Closed"));
        case Conditional::TYPE_CONDITIONAL_TRUE:
            return (tr("True"));
        case Conditional::TYPE_CONDITIONAL_FALSE:
            return (tr("False"));
        case Conditional::TYPE_LIGHT_ON:
            return (tr("On"));
        case Conditional::TYPE_LIGHT_OFF:
            return (tr("Off"));
        case Conditional::TYPE_MEMORY_EQUALS:
            return (tr("(case sensitive) Value"));
        case Conditional::TYPE_MEMORY_COMPARE:
            return (tr("(case sensitive) Memory"));
        case Conditional::TYPE_FAST_CLOCK_RANGE:
            return ("");
        case Conditional::TYPE_SIGNAL_HEAD_RED:
            return (tr("Red"));
        case Conditional::TYPE_SIGNAL_HEAD_YELLOW:
            return (tr("Yellow"));
        case Conditional::TYPE_SIGNAL_HEAD_GREEN:
            return (tr("Green"));
        case Conditional::TYPE_SIGNAL_HEAD_DARK:
            return (tr("Dark"));
        case Conditional::TYPE_SIGNAL_HEAD_FLASHRED:
            return (tr("Flashing Red"));
        case Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW:
            return (tr("Flashing Yellow"));
        case Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN:
            return (tr("Flashing Green"));
        case Conditional::TYPE_SIGNAL_HEAD_LIT:
            return (tr("Signal Head Lit"));
        case Conditional::TYPE_SIGNAL_HEAD_HELD:
            return (tr("Signal Head Held"));
        case Conditional::TYPE_SIGNAL_HEAD_LUNAR:
            return (tr("Lunar"));
        case Conditional::TYPE_SIGNAL_HEAD_FLASHLUNAR:
            return (tr("Flashing Lunar"));
        case Conditional::TYPE_MEMORY_EQUALS_INSENSITIVE:
            return (tr("(case insensitive) Value "));
        case Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE:
            return (tr("(case insensitive) Memory"));
        case Conditional::TYPE_ROUTE_FREE:
            return (tr("Route Free"));
        case Conditional::TYPE_ROUTE_OCCUPIED:
            return (tr("stateRouteOccupied"));
        case Conditional::TYPE_ROUTE_ALLOCATED:
            return (tr("Route Reserved"));
        case Conditional::TYPE_ROUTE_SET:
            return (tr("Route Is Set"));
        case Conditional::TYPE_TRAIN_RUNNING:
            return (tr("StateTrainRunning"));
        case Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS:
            return (tr("Signal Mast Aspect Equals"));
        case Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS:
            return (tr("Signal Head Appearance Equals"));
        case Conditional::TYPE_SIGNAL_MAST_LIT:
            return (tr("Signal Mast Lit"));
        case Conditional::TYPE_SIGNAL_MAST_HELD:
            return (tr("Signal Mast Held"));
        case Conditional::TYPE_ENTRYEXIT_ACTIVE:
            return (tr("Entry Exit Active"));
        case Conditional::TYPE_ENTRYEXIT_INACTIVE:
            return (tr("Entry Exit Inactive"));
    }
    return "";
}

/**
 * Convert Variable Test Type to Text String
 */
/*public*/ /*static*/ QString ConditionalVariable::getTestTypeString(int t) {
    switch (t) {
        case Conditional::TYPE_NONE:
            return "";
        case Conditional::TYPE_SENSOR_ACTIVE:
            return (tr("Sensor Active"));
        case Conditional::TYPE_SENSOR_INACTIVE:
            return (tr("Sensor Inactive"));
        case Conditional::TYPE_TURNOUT_THROWN:
            return (tr("Turnout Thrown"));
        case Conditional::TYPE_TURNOUT_CLOSED:
            return (tr("Turnout Closed"));
        case Conditional::TYPE_CONDITIONAL_TRUE:
            return (tr("Conditional True"));
        case Conditional::TYPE_CONDITIONAL_FALSE:
            return (tr("Conditional False"));
        case Conditional::TYPE_LIGHT_ON:
            return (tr("Light On"));
        case Conditional::TYPE_LIGHT_OFF:
            return (tr("Light Off"));
        case Conditional::TYPE_MEMORY_EQUALS:
            return (tr("Memory Equals"));
        case Conditional::TYPE_MEMORY_COMPARE:
            return (tr("Memory Compare"));
        case Conditional::TYPE_FAST_CLOCK_RANGE:
            return (tr("Fast Clock Range"));
        case Conditional::TYPE_SIGNAL_HEAD_RED:
            return (tr("Signal Head Red"));
        case Conditional::TYPE_SIGNAL_HEAD_YELLOW:
            return (tr("Signal Head Yellow"));
        case Conditional::TYPE_SIGNAL_HEAD_GREEN:
            return (tr("Signal Head Green"));
        case Conditional::TYPE_SIGNAL_HEAD_DARK:
            return (tr("Signal Head Dark"));
        case Conditional::TYPE_SIGNAL_HEAD_FLASHRED:
            return (tr("Signal Head Flashing Red"));
        case Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW:
            return (tr("Signal Head Flashing Yellow"));
        case Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN:
            return (tr("Signal Head Flashing Green"));
        case Conditional::TYPE_SIGNAL_HEAD_LIT:
            return (tr("Signal Head Lit"));
        case Conditional::TYPE_SIGNAL_HEAD_HELD:
            return (tr("Signal Head Held"));
        case Conditional::TYPE_SIGNAL_HEAD_LUNAR:
            return (tr("Signal Head Lunar"));
        case Conditional::TYPE_SIGNAL_HEAD_FLASHLUNAR:
            return (tr("Signal Head Flashing Lunar"));
        case Conditional::TYPE_MEMORY_EQUALS_INSENSITIVE:
            return (tr("Memory Equals Insensitive"));
        case Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE:
            return (tr("Memory Compare Insensitive"));
        case Conditional::TYPE_ROUTE_FREE:
            return (tr("Warrant Route Free"));
        case Conditional::TYPE_ROUTE_OCCUPIED:
            return (tr("Warrant Route Occupied"));
        case Conditional::TYPE_ROUTE_ALLOCATED:
            return (tr("WarrantRouteAllocated"));
        case Conditional::TYPE_ROUTE_SET:
            return (tr("RouteIsSet"));
        case Conditional::TYPE_TRAIN_RUNNING:
            return (tr("Train Running"));
        case Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS:
            return (tr("Signal Mast Aspect Equals"));
        case Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS:
            return (tr("Signal Head Aspec tEquals"));
        case Conditional::TYPE_SIGNAL_MAST_LIT:
            return (tr("Signal Mast Lit"));
        case Conditional::TYPE_SIGNAL_MAST_HELD:
            return (tr("Signal Mast Held"));
        case Conditional::TYPE_ENTRYEXIT_ACTIVE:
            return (tr("Entry Exit Active"));
        case Conditional::TYPE_ENTRYEXIT_INACTIVE:
            return (tr("Entry Exit Inactive"));
    }
    return ("None");
}

/*public*/ /*static*/ QString ConditionalVariable::getCompareOperationString(int index) {
    switch(index) {
        case LESS_THAN:
            return (tr("LessThan"));
        case LESS_THAN_OR_EQUAL:
            return (tr("LessOrEqual"));
        case 0:
        case EQUAL:
            return (tr("Equal"));
        case GREATER_THAN_OR_EQUAL:
            return (tr("GreaterOrEqual"));
        case GREATER_THAN:
            return (tr("GreaterThan"));
    }
    return ("");
}

/*public*/ /*static*/ QString ConditionalVariable::getCompareSymbols(int index) {
    switch(index) {
        case LESS_THAN:
            return ("<");
        case LESS_THAN_OR_EQUAL:
            return ("<=");
        case 0:
        case EQUAL:
            return ("=");
        case GREATER_THAN_OR_EQUAL:
            return (">=");
        case GREATER_THAN:
            return (">");
    }
    return ("");
}

/**
 * Identifies action Data from Text String Note: if string does not
 * correspond to an action Data as defined in
 * ConditionalAction, returns -1.
 */
/*public*/ /*static*/ int ConditionalVariable::stringToVariableTest(QString str) {
    Logger* log = new Logger("ConditionalVariable");
    if (str==(tr("Red"))) {
        return Conditional::TYPE_SIGNAL_HEAD_RED;
    }
    else if (str==(tr("Yellow"))) {
        return Conditional::TYPE_SIGNAL_HEAD_YELLOW;
    }
    else if (str==(tr("Green"))) {
        return Conditional::TYPE_SIGNAL_HEAD_GREEN;
    }
    else if (str==(tr("Dark"))) {
        return Conditional::TYPE_SIGNAL_HEAD_DARK;
    }
    else if (str==(tr("Flashing Red"))) {
        return Conditional::TYPE_SIGNAL_HEAD_FLASHRED;
    }
    else if (str==(tr("Flashing Yellow"))) {
        return Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW;
    }
    else if (str==(tr("Flashing Green"))) {
        return Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN;
    }
    else if (str==(tr("Lunar"))) {
        return Conditional::TYPE_SIGNAL_HEAD_LUNAR;
    }
    else if (str==(tr("Flashing Lunar"))) {
        return Conditional::TYPE_SIGNAL_HEAD_FLASHLUNAR;
    }
    // empty strings can occur frequently with types that have no integer data
    if (str.length() > 0)
    {
        log->warn("Unexpected parameter to stringToVariableTest("+str+")");
    }
    return -1;
}

/*public*/ QString ConditionalVariable::toString() {
    QString type = getTestTypeString(_type);
    int itemType = Conditional::TEST_TO_ITEM[_type];
    switch (itemType) {
        case Conditional::ITEM_TYPE_SENSOR:
        return tr("%1 \"%2\" state is %3").arg("Sensor").arg(getName()).arg(type) ;
        case Conditional::ITEM_TYPE_TURNOUT:
        return tr("%1 \"%2\" state is %3").arg("Turnout").arg(getName()).arg(type );
        case Conditional::ITEM_TYPE_LIGHT:
        return tr("%1 \"%2\" state is %3").arg("Light").arg(getName()).arg(type );
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            if ((_type==Conditional::TYPE_SIGNAL_HEAD_LIT) ||
                    (_type==Conditional::TYPE_SIGNAL_HEAD_HELD)) {
                return tr("%1 \"%2\" state is %3").arg("Signal Head").arg(getName()).arg(type );
            } else {
                return tr("%1 \"%2\" appearance is %3").arg("Signal Head").arg(getName()).arg(type);
            }
        case Conditional::ITEM_TYPE_SIGNALMAST:
            if ((_type==Conditional::TYPE_SIGNAL_MAST_LIT) ||
                    (_type==Conditional::TYPE_SIGNAL_MAST_HELD)) {
                return tr("%1 \"%2\" state is %3").arg("Signal Mast").arg(getName()).arg( type );
            } else {
        return tr("%1 \"%2\" aspect is %3").arg("Signal Mast").arg(getName()).arg(_dataString);
            }
        case Conditional::ITEM_TYPE_MEMORY:
            if ((_type==Conditional::TYPE_MEMORY_EQUALS) ||
                    (_type==Conditional::TYPE_MEMORY_EQUALS_INSENSITIVE)) {
                return tr("%1 \"%2\" %3 value \"%4\"").arg("Memory").arg(getName()).arg(
                            getCompareSymbols(_num1)).arg(_dataString);
            } else {
                return tr("%1 \"%2\" %3 %1 \"%4\"").arg("Memory").arg( getName()).arg(
                            getCompareSymbols(_num1)).arg(_dataString);
            }
        case Conditional::ITEM_TYPE_CONDITIONAL:
        return tr("%1 \"%2\" state is %3").arg("Conditional").arg(getName()).arg(type );
        case Conditional::ITEM_TYPE_WARRANT:
        return tr("%1 \"%2\" state is %3").arg("Warrant Route").arg(getName()).arg(type);
        case Conditional::ITEM_TYPE_CLOCK:
        return tr("%1 range from %2 to %3").arg("Fast Clock").arg(LogixTableAction::formatTime(_num1 / 60, _num1 - ((_num1 / 60) * 60))).arg(LogixTableAction::formatTime(_num2 / 60, _num2 - ((_num2 / 60) * 60)) );
        case Conditional::ITEM_TYPE_OBLOCK:
        return tr("%1 \"%2\" state is %3").arg("OBlock Status").arg(getName()).arg(_dataString );
        case Conditional::ITEM_TYPE_ENTRYEXIT:
        return tr("%1 \"%2\" state is %3").arg("Entry Exit").arg(getBean()->getUserName()).arg(type) ;
        case Conditional::TYPE_NONE:
        {
         QString n = getName();
         //return n + " type " + type;
         return "none";
        }
    }
    return objectName();
}
/*private*/ /*final*/ /*static*/ Logger* ConditionalVariable::log = LoggerFactory::getLogger("ConditionalVariable");
