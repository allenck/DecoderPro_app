#include "defaultconditionalaction.h"
#include "conditional.h"
#include "instancemanager.h"
#include "logger.h"
#include "abstractlightmanager.h"
#include "abstractmemorymanager.h"
#include "abstractsignalheadmanager.h"
#include "defaultsignalmastmanager.h"
#include "namedbean.h"
#include "signalhead.h"
#include "defaultsignalhead.h"
#include "../Tables/logixtableaction.h"
#include "warrant.h"
#include "audio.h"

DefaultConditionalAction::DefaultConditionalAction(QObject *parent) :
    ConditionalAction(parent)
{
    common();
}
/**
 * ConditionalAction.java
 *
 * The consequent of the antecedent of the conditional proposition.
 * The data for the action to be taken when a Conditional calculates to True
 * <P>
 * This is in the implementations package because of a Swing dependence
 * via the times.  Java 1.5 or Java 1.6 might make it possible to
 * break that, which will simplify things.
 *
 * @author Pete Cressman Copyright (C) 2009, 2010, 2011
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 22323 $
 */
void DefaultConditionalAction::common()
{
    log = new Logger("DefaultConditionalAction");
    _option = Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE;
    _type = Conditional::ACTION_NONE ;
    _deviceName = " ";
    _actionData = 0;
    _actionString = "";
    _namedBean = NULL;
    _type = 0;

    _timer = NULL;
    _listener = NULL;
    _timerActive = false;
   // _sound = NULL;
    nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");

}

///*public*/ class DefaultConditionalAction implements ConditionalAction {


//	static final java.util.ResourceBundle rbx = java.util.ResourceBundle.getBundle("jmri.jmrit.beantable.LogixTableBundle");

//    /*public*/ DefaultConditionalAction() {
//    }

/*public*/ DefaultConditionalAction::DefaultConditionalAction(int option, int type, QString name, int actionData, QString actionStr ,QObject *parent) : ConditionalAction(parent)
{
    common();
    _option = option;
    _type = type;
    _deviceName = name;
    _actionData = actionData;
    _actionString = actionStr;

    NamedBean* bean = NULL;
    try {
        int itemType = Conditional::ACTION_TO_ITEM[_type];
        switch (itemType) {
            case Conditional::ITEM_TYPE_SENSOR:
                bean = (NamedBean*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(_deviceName);
                if (bean == NULL) {
                    log->error("invalid sensor name= \""+_deviceName+"\" in conditional action");
                    return;
                }
                break;
            case Conditional::ITEM_TYPE_TURNOUT:
                bean = (NamedBean*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(_deviceName);
                if (bean == NULL) {
                    log->error("invalid turnout name= \""+_deviceName+"\" in conditional action");
                    return;
                }
                break;
            case Conditional::ITEM_TYPE_MEMORY:
                bean = (NamedBean*)((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->provideMemory(_deviceName);
                if (bean == NULL) {
                    log->error("invalid memory name= \""+_deviceName+"\" in conditional action");
                    return;
                }
                break;
            case Conditional::ITEM_TYPE_LIGHT:
                bean = (NamedBean*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getLight(_deviceName);
                if (bean == NULL) {
                    log->error("invalid light name= \""+_deviceName+"\" in conditional action");
                    return;
                }
                break;
            case Conditional::ITEM_TYPE_SIGNALMAST:
                bean = (NamedBean*)static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(_deviceName);
                if (bean == NULL) {
                    log->error("invalid signal mast name= \""+_deviceName+"\" in conditional action");
                    return;
                }
                break;
            case Conditional::ITEM_TYPE_SIGNALHEAD:
                bean = (NamedBean*)static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(_deviceName);
                if (bean == NULL) {
                    log->error("invalid signal head name= \""+_deviceName+"\" in conditional action");
                    return;
                }
                break;
        }
    } catch (NumberFormatException ex){
        //Can be considered normal if the logixs are loaded prior to any other beans
    }
    if (bean!=NULL){
        _namedBean = nbhm->getNamedBeanHandle(_deviceName, bean);
    } else {
        _namedBean = NULL;
    }
}

/**
 * The consequent device or element type
 */
/*public*/ int DefaultConditionalAction::getType() {
    return _type;
}

/*public*/ void DefaultConditionalAction::setType(int type) {
    _type = type;
}

/**
* Sets type from user's name for it
*/
/*public*/ void DefaultConditionalAction::setType(QString type) {
    _type = stringToActionType(type);
}

/**
 * Name of the device or element that is effected
 */
/*public*/ QString DefaultConditionalAction::getDeviceName() {
    if(_namedBean!=NULL) {
        return _namedBean->getName();
    }
    /* As we have a trigger for something using the action, then hopefully
    all the managers have been loaded and we can get the bean, which prevented
    the bean from being loaded in the first place */
    setDeviceName(_deviceName);
    return _deviceName;
}

/*public*/ void DefaultConditionalAction::setDeviceName(QString deviceName) {
    _deviceName = deviceName;
    NamedBean* bean = NULL;
    int itemType = Conditional::ACTION_TO_ITEM[_type];
    try {
        switch (itemType) {
            case Conditional::ITEM_TYPE_SENSOR:
                bean = (NamedBean*)((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(_deviceName);
                break;
            case Conditional::ITEM_TYPE_TURNOUT:
                bean = (NamedBean*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(_deviceName);
                break;
            case Conditional::ITEM_TYPE_MEMORY:
                bean = (NamedBean*)((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->provideMemory(_deviceName);
                break;
            case Conditional::ITEM_TYPE_LIGHT:
                bean = (NamedBean*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getLight(_deviceName);
                break;
            case Conditional::ITEM_TYPE_SIGNALMAST:
                bean = (NamedBean*)static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(_deviceName);
                break;
            case Conditional::ITEM_TYPE_SIGNALHEAD:
                bean = (NamedBean*)static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(_deviceName);
                break;
        }
    } catch (NumberFormatException ex){
        //Can be considered normal if the logixs are loaded prior to the sensors
    }
    if (bean!=NULL){
        _namedBean = nbhm->getNamedBeanHandle(_deviceName, bean);
    } else {
        _namedBean = NULL;
    }
}

/*public*/ NamedBeanHandle<NamedBean*>* DefaultConditionalAction::getNamedBean(){
    return _namedBean;
}

/*public*/ NamedBean* DefaultConditionalAction::getBean(){
    if (_namedBean!=NULL){
        return (NamedBean*) _namedBean->getBean();
    }
    setDeviceName(_deviceName); //ReApply name as that will create namedBean, save replicating it here
    if(_namedBean!=NULL)
        return (NamedBean*) _namedBean->getBean();
    return NULL;
}

/**
 * Options on when action is taken
 */
/*public*/ int DefaultConditionalAction::getOption() {
    return _option;
}

/*public*/ void DefaultConditionalAction::setOption(int option) {
    _option = option;
}

/**
 * Integer data for action
 */
/*public*/ int DefaultConditionalAction::getActionData() {
    return _actionData;
}

/*public*/ void DefaultConditionalAction::setActionData(int actionData) {
    _actionData = actionData;
}

/**
* Sets action data from user's name for it
*/
/*public*/ void DefaultConditionalAction::setActionData(QString actionData) {
    _actionData = stringToActionData(actionData);
}

/**
 * String data for action
 */
/*public*/ QString DefaultConditionalAction::getActionString() {
    if (_actionString=="") {
        _actionString = getTypeString();
    }
    return _actionString;
}

/*public*/ void DefaultConditionalAction::setActionString(QString actionString) {
    _actionString = actionString;
}

/*
* get timer for delays and other timed events
*/
/*public*/ QTimer* DefaultConditionalAction::getTimer() {
    return _timer;
}

/*
* set timer for delays and other timed events
*/
/*public*/ void DefaultConditionalAction::setTimer(QTimer* timer) {
    _timer = timer;
}

/*public*/ bool DefaultConditionalAction::isTimerActive() {
    return _timerActive;
}

/*public*/ void DefaultConditionalAction::startTimer() {
    if (_timer != NULL)
    {
        _timer->start();
        _timerActive = true;
    }
    else {
        log->error("timer is NULL for "+_deviceName+" of type "+getTypeString());
    }
}

/*public*/ void DefaultConditionalAction::stopTimer() {
    if (_timer != NULL)
    {
        _timer->stop();
        _timerActive = false;
    }
}

/*
* set listener for delays and other timed events
*/
/*public*/ ActionListener* DefaultConditionalAction::getListener() {
    return _listener;
}

/*
* set listener for delays and other timed events
*/
/*public*/ void DefaultConditionalAction::setListener(ActionListener* listener) {
    _listener = listener;
}

/**
* get Sound file
*/
///*public*/ Sound* DefaultConditionalAction::getSound() {
//    return _sound;
//}

/**
* set Sound file
*/
//protected void DefaultConditionalAction::setSound(Sound* sound) {
//    _sound = sound;
//}

/**** Methods that return user interface strings *****/

/**
 * return String name of this consequent type
 */
/*public*/ QString DefaultConditionalAction::getTypeString() {
    return getActionTypeString(_type);
}

/**
 * return String name of the option for this consequent type
 */
/*public*/ QString DefaultConditionalAction::getOptionString(bool type) {
    return getOptionString(_option, type);
}

/*public*/ QString DefaultConditionalAction::getActionDataString() {
    return getActionDataString(_type, _actionData);
}


/**
 * Convert Variable Type to Text String
 */
/*public*/ /*static*/ QString DefaultConditionalAction::getItemTypeString(int t) {
    switch (t) {
        case Conditional::ITEM_TYPE_SENSOR:
            return (tr("Sensor"));
        case Conditional::ITEM_TYPE_TURNOUT:
            return (tr("Turnout"));
        case Conditional::ITEM_TYPE_LIGHT:
            return (tr("Light"));
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            return (tr("Signal Head"));
        case Conditional::ITEM_TYPE_SIGNALMAST:
            return (tr("Signal Mast"));
        case Conditional::ITEM_TYPE_MEMORY:
            return (tr("Memory"));
        case Conditional::ITEM_TYPE_LOGIX:
            return (tr("Logix"));
        case Conditional::ITEM_TYPE_WARRANT:
            return (tr("Warrant"));
        case Conditional::ITEM_TYPE_OBLOCK:
            return (tr("OBlock"));
        case Conditional::ITEM_TYPE_CLOCK:
            return (tr("FastClock"));
        case Conditional::ITEM_TYPE_AUDIO:
            return (tr("Audio"));
        case Conditional::ITEM_TYPE_SCRIPT:
            return (tr("Script"));
        case Conditional::ITEM_TYPE_OTHER:
            return (tr("Other"));
    }
    return "";
}


/**
 * Convert Consequent Type to Text String
 */
/*public*/ /*static*/ QString DefaultConditionalAction::getActionTypeString(int t) {
    Logger* log = new Logger("DefaultConditionalAction");
    switch (t) {
        case Conditional::ACTION_NONE:
            return (tr("None"));
        case Conditional::ACTION_SET_TURNOUT:
            return (tr("Set Turnout"));
        case Conditional::ACTION_SET_SIGNAL_APPEARANCE:
            return (tr("Set Signal"));
        case Conditional::ACTION_SET_SIGNAL_HELD:
            return (tr("Set Signal Held"));
        case Conditional::ACTION_CLEAR_SIGNAL_HELD:
            return (tr("Clear Signal Held"));
        case Conditional::ACTION_SET_SIGNAL_DARK:
            return (tr("Set Signal Dark"));
        case Conditional::ACTION_SET_SIGNAL_LIT:
            return (tr("Set Signal Lit"));
        case Conditional::ACTION_TRIGGER_ROUTE:
            return (tr("Trigger Route"));
        case Conditional::ACTION_SET_SENSOR:
            return (tr("Set Sensor"));
        case Conditional::ACTION_DELAYED_SENSOR:
            return (tr("Delayed Set Sensor"));
        case Conditional::ACTION_SET_LIGHT:
            return (tr("Set Light"));
        case Conditional::ACTION_SET_MEMORY:
            return (tr("Set Memory"));
        case Conditional::ACTION_ENABLE_LOGIX:
            return (tr("Enable Logix"));
        case Conditional::ACTION_DISABLE_LOGIX:
            return (tr("Disable Logix"));
        case Conditional::ACTION_PLAY_SOUND:
            return (tr("Play Sound"));
        case Conditional::ACTION_RUN_SCRIPT:
            return (tr("Run Script"));
        case Conditional::ACTION_DELAYED_TURNOUT:
            return (tr("Delayed Set Turnout"));
        case Conditional::ACTION_LOCK_TURNOUT:
            return (tr("Turnout Lock"));
        case Conditional::ACTION_RESET_DELAYED_SENSOR:
            return (tr("Reset Delayed Sensor"));
        case Conditional::ACTION_CANCEL_SENSOR_TIMERS:
            return (tr("ActionCancelSensorTimers"));
        case Conditional::ACTION_RESET_DELAYED_TURNOUT:
            return (tr("ActionResetDelayedTurnout"));
        case Conditional::ACTION_CANCEL_TURNOUT_TIMERS:
            return (tr("Cancel Turnout Timers"));
        case Conditional::ACTION_SET_FAST_CLOCK_TIME:
            return (tr("Set Fast Clock Time"));
        case Conditional::ACTION_START_FAST_CLOCK:
            return (tr("ActionStartFastClock"));
        case Conditional::ACTION_STOP_FAST_CLOCK:
            return (tr("Stop Fas tClock"));
        case Conditional::ACTION_COPY_MEMORY:
            return (tr("Copy Memory"));
        case Conditional::ACTION_SET_LIGHT_INTENSITY:
            return (tr("Set Light Intensity"));
        case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
            return (tr("Set Light Transition Time"));
        case Conditional::ACTION_CONTROL_AUDIO:
            return (tr("Control Audio"));
        case Conditional::ACTION_JYTHON_COMMAND:
            return (tr("Jython Command"));
        case Conditional::ACTION_ALLOCATE_WARRANT_ROUTE:
            return (tr("Allocate Warrant"));
        case Conditional::ACTION_DEALLOCATE_WARRANT_ROUTE:
            return (tr("Deallocate Warrant"));
        case Conditional::ACTION_SET_ROUTE_TURNOUTS:
            return (tr("Set Warrant Turnouts"));
        case Conditional::ACTION_AUTO_RUN_WARRANT:
            return (tr("Auto Run Warrant"));
        case Conditional::ACTION_MANUAL_RUN_WARRANT:
            return (tr("Manual Run Warrant"));
        case Conditional::ACTION_CONTROL_TRAIN:
            return (tr("ActionControlTrain"));
        case Conditional::ACTION_SET_TRAIN_ID:
           return (tr("Set Train Id"));
        case Conditional::ACTION_SET_TRAIN_NAME:
           return (tr("Set Train Name"));
        case Conditional::ACTION_SET_SIGNALMAST_ASPECT:
           return (tr("Set Signal Mast Aspect"));
        case Conditional::ACTION_THROTTLE_FACTOR:
           return (tr("Set Throttle Factor"));
        case Conditional::ACTION_SET_SIGNALMAST_HELD:
           return (tr("Set Signal Mast Held"));
        case Conditional::ACTION_CLEAR_SIGNALMAST_HELD:
           return (tr("Clear Signal Mast Held"));
        case Conditional::ACTION_SET_SIGNALMAST_DARK:
           return (tr("Set Signal Mast Dark"));
        case Conditional::ACTION_SET_SIGNALMAST_LIT:
           return (tr("Clear Signal Mast Dark"));
           return (tr("Set Bloc kPath Turnouts"));
        case Conditional::ACTION_DEALLOCATE_BLOCK:
           return (tr("Deallocate Block"));
        case Conditional::ACTION_SET_BLOCK_OUT_OF_SERVICE:
           return (tr("Set Block Out Of Service"));
        case Conditional::ACTION_SET_BLOCK_IN_SERVICE:
            return (tr("Block In Service"));
    }
    log->warn("Unexpected parameter to getActionTypeString("+QString::number(t)+")");
    return ("");
}

/**
 * Convert consequent option to String
 */
/*public*/ /*static*/ QString DefaultConditionalAction::getOptionString(int opt, bool type) {
    Logger* log = new Logger("DefaultConditionalAction");

    switch (opt) {
        case Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE:
            if (type){
                return (tr("OnChangeToTrue"));
            } else {
                return (tr("OnTriggerToTrue"));
            }
        case Conditional::ACTION_OPTION_ON_CHANGE_TO_FALSE:
            if (type){
                return (tr("OnChangeToFalse"));
            } else {
                return (tr("OnTriggerToFalse"));
            }
        case Conditional::ACTION_OPTION_ON_CHANGE:
            if (type){
                return (tr("OnChange"));
            } else {
                return (tr("OnTrigger"));
            }
    }
    log->warn("Unexpected parameter to getOptionString("+QString::number(opt)+")");
    return "";
}

/**
 * Identifies action Type from Text String Note: if string does not
 * correspond to an action type as defined in
 * ConditionalAction, returns 0.
 */
/*public*/ /*static*/ int DefaultConditionalAction::stringToActionType(QString str) {
    Logger* log = new Logger("DefaultConditionalAction");

    if (str != NULL)
    {
        for (int i = 1; i <= Conditional::NUM_ACTION_TYPES; i++) {
            if (str==(getActionTypeString(i))) {
                return (i);
            }
        }
    }
    log->warn("Unexpected parameter to stringToActionType("+str+")");
    return 0;
}

/**
 * Identifies action Data from Text String Note: if string does not
 * correspond to an action Data as defined in
 * ConditionalAction, returns -1.
 */
/*public*/ /*static*/ int DefaultConditionalAction::stringToActionData(QString str) {
    Logger* log = new Logger("DefaultConditionalAction");

    if (str==(tr("Closed"))) {
            return Turnout::CLOSED;
    }
    else if (str==(tr("Thrown"))) {
        return Turnout::THROWN;
    }
    else if (str==(tr("Active")))
    {
        return Sensor::ACTIVE;
    }
    else if (str==(tr("Inactive"))) {
        return Sensor::INACTIVE;
    }
    else if (str==(tr("On"))) {
        return Light::ON;
    }
    else if (str==(tr("Off"))) {
        return Light::OFF;
    }
    else if (str==(tr("Unlock"))) {
        return Turnout::UNLOCKED;
    }
    else if (str==(tr("Lock"))) {
        return Turnout::LOCKED;
    }
    else if (str==(tr("Red"))) {
        return SignalHead::RED;
    }
    else if (str==(tr("Yellow"))) {
        return SignalHead::YELLOW;
    }
    else if (str==(tr("Green"))) {
        return SignalHead::GREEN;
    }
    else if (str==(tr("Dark"))) {
        return SignalHead::DARK;
    }
    else if (str==(tr("Flashing Red"))) {
        return SignalHead::FLASHRED;
    }
    else if (str==(tr("Flashing Yellow"))) {
        return SignalHead::FLASHYELLOW;
    }
    else if (str==(tr("Flashing Green"))) {
        return SignalHead::FLASHGREEN;
    }
    else if (str==(tr("Lunar"))) {
        return SignalHead::LUNAR;
    }
    else if (str==(tr("Flashing Lunar"))) {
        return SignalHead::FLASHLUNAR;
    }
#if 1
    else if (str==(tr("AudioSourcePlay"))) {
        return Audio::CMD_PLAY;
    }
    else if (str==(tr("AudioSourceStop"))) {
        return Audio::CMD_STOP;
    }
    else if (str==(tr("AudioSourcePlayToggle"))) {
        return Audio::CMD_PLAY_TOGGLE;
    }
    else if (str==(tr("AudioSourcePause"))) {
        return Audio::CMD_PAUSE;
    }
    else if (str==(tr("AudioSourceResume"))) {
        return Audio::CMD_RESUME;
    }
    else if (str==(tr("AudioSourcePauseToggle"))) {
        return Audio::CMD_PAUSE_TOGGLE;
    }
    else if (str==(tr("AudioSourceRewind"))) {
        return Audio::CMD_REWIND;
    }
    else if (str==(tr("AudioSourceFadeIn"))) {
        return Audio::CMD_FADE_IN;
    }
    else if (str==(tr("AudioSourceFadeOut"))) {
        return Audio::CMD_FADE_OUT;
    }
    else if (str==(tr("AudioResetPosition"))) {
        return Audio::CMD_RESET_POSITION;
    }
#endif
    // empty strings can occur frequently with types that have no integer data
    if (str.length() > 0)
    {
        log->warn("Unexpected parameter to stringToActionData("+str+")");
    }
    return -1;
}

/*public*/ /*static*/ QString DefaultConditionalAction::getActionDataString(int t, int data) {
    switch (t) {
        case Conditional::ACTION_SET_TURNOUT:
        case Conditional::ACTION_DELAYED_TURNOUT:
        case Conditional::ACTION_RESET_DELAYED_TURNOUT:
            if (data == Turnout::CLOSED) {
                return (tr("Closed"));
            } else if (data == Turnout::THROWN) {
                return (tr("Thrown"));
            } else if (data == Route::TOGGLE) {
                return (tr("Toggle"));
            }
            break;
        case Conditional::ACTION_SET_SIGNAL_APPEARANCE:
            return DefaultSignalHead::getDefaultStateName(data);
        case Conditional::ACTION_SET_SENSOR:
        case Conditional::ACTION_DELAYED_SENSOR:
        case Conditional::ACTION_RESET_DELAYED_SENSOR:
            if (data == Sensor::ACTIVE) {
                return (tr("Active"));
            } else if (data == Sensor::INACTIVE) {
                return (tr("Inactive"));
            } else if (data == Route::TOGGLE) {
                return (tr("Toggle"));
            }
            break;
        case Conditional::ACTION_SET_LIGHT:
            if (data == Light::ON) {
                return (tr("On"));
            } else if (data == Light::OFF) {
                return (tr("Off"));
            }  else if (data == Route::TOGGLE) {
                return (tr("Toggle"));
            }
            break;
        case Conditional::ACTION_LOCK_TURNOUT:
            if (data == Turnout::UNLOCKED) {
                return (tr("Unlock"));
            } else if (data == Turnout::LOCKED) {
                return (tr("Lock"));
            } else if (data == Route::TOGGLE) {
                return (tr("Toggle"));
            }
            break;
#if 1
        case Conditional::ACTION_CONTROL_AUDIO:
            switch (data) {
                case Audio::CMD_PLAY:
                    return (tr("AudioSourcePlay"));
                case Audio::CMD_STOP:
                    return (tr("AudioSourceStop"));
                case Audio::CMD_PLAY_TOGGLE:
                    return (tr("AudioSourcePlayToggle"));
                case Audio::CMD_PAUSE:
                    return (tr("AudioSourcePause"));
                case Audio::CMD_RESUME:
                    return (tr("AudioSourceResume"));
                case Audio::CMD_PAUSE_TOGGLE:
                    return (tr("AudioSourcePauseToggle"));
                case Audio::CMD_REWIND:
                    return (tr("AudioSourceRewind"));
                case Audio::CMD_FADE_IN:
                    return (tr("AudioSourceFadeIn"));
                case Audio::CMD_FADE_OUT:
                    return (tr("AudioSourceFadeOut"));
                case Audio::CMD_RESET_POSITION:
                    return (tr("AudioResetPosition"));
            }
            break;
#endif
        case Conditional::ACTION_CONTROL_TRAIN:
            if (data == Warrant::HALT) {
                return (tr("WarrantHalt"));
            } else if (data == Warrant::RESUME) {
                return (tr("WarrantResume"));
            } else
                return (tr("WarrantAbort"));
    }
    return "";
}

/*public*/ QString DefaultConditionalAction::description(bool triggerType)
{
 QString str = getOptionString(triggerType)+", "+ getTypeString();
 if (_deviceName.length() > 0)
 {
  switch (_type)
  {
      case Conditional::ACTION_CANCEL_TURNOUT_TIMERS:
      case Conditional::ACTION_SET_SIGNAL_HELD:
      case Conditional::ACTION_CLEAR_SIGNAL_HELD:
      case Conditional::ACTION_SET_SIGNAL_DARK:
      case Conditional::ACTION_SET_SIGNAL_LIT:
      case Conditional::ACTION_TRIGGER_ROUTE:
      case Conditional::ACTION_CANCEL_SENSOR_TIMERS:
      case Conditional::ACTION_SET_MEMORY:
      case Conditional::ACTION_ENABLE_LOGIX:
      case Conditional::ACTION_DISABLE_LOGIX:
      case Conditional::ACTION_COPY_MEMORY:
      case Conditional::ACTION_SET_LIGHT_INTENSITY:
      case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
      case Conditional::ACTION_ALLOCATE_WARRANT_ROUTE:
      case Conditional::ACTION_DEALLOCATE_WARRANT_ROUTE:
      case Conditional::ACTION_SET_SIGNALMAST_HELD:
      case Conditional::ACTION_CLEAR_SIGNALMAST_HELD:
      case Conditional::ACTION_SET_SIGNALMAST_DARK:
      case Conditional::ACTION_SET_SIGNALMAST_LIT:
      case Conditional::ACTION_DEALLOCATE_BLOCK:
      case Conditional::ACTION_SET_BLOCK_OUT_OF_SERVICE:
      case Conditional::ACTION_SET_BLOCK_IN_SERVICE:
          str = str + ", \""+ _deviceName+"\".";
          break;
      case Conditional::ACTION_SET_ROUTE_TURNOUTS:
      case Conditional::ACTION_AUTO_RUN_WARRANT:
      case Conditional::ACTION_MANUAL_RUN_WARRANT:
          str = str +" "+tr("onWarrant")+", \""+ _deviceName+"\".";
          break;
      case Conditional::ACTION_SET_SENSOR:
      case Conditional::ACTION_SET_TURNOUT:
      case Conditional::ACTION_SET_LIGHT:
      case Conditional::ACTION_LOCK_TURNOUT:
      case Conditional::ACTION_RESET_DELAYED_SENSOR:
      case Conditional::ACTION_SET_SIGNAL_APPEARANCE:
      case Conditional::ACTION_RESET_DELAYED_TURNOUT:
      case Conditional::ACTION_DELAYED_TURNOUT:
      case Conditional::ACTION_DELAYED_SENSOR:
      case Conditional::ACTION_CONTROL_AUDIO:
          str = str + ", \""+ _deviceName +"\" " + tr("to")
                + " " + getActionDataString();
          break;
      case Conditional::ACTION_SET_SIGNALMAST_ASPECT:
          str = str + ", \""+ _deviceName +"\" " + tr("to")
                + " " + _actionString;
          break;
      case Conditional::ACTION_CONTROL_TRAIN:
          str = str +" "+tr("onWarrant")+" \""+ _deviceName +"\" "
                +tr("to")+ " " + getActionDataString();
     }
    }
    if (_actionString.length() > 0)
    {
     switch (_type)
     {
      case Conditional::ACTION_SET_MEMORY:
      case Conditional::ACTION_COPY_MEMORY:
          str = str + " " + tr("to")+ " " + _actionString + ".";
          break;
      case Conditional::ACTION_PLAY_SOUND:
      case Conditional::ACTION_RUN_SCRIPT:
          str = str + " " + tr("FromFile")+ " "+ _actionString+ ".";
          break;
      case Conditional::ACTION_RESET_DELAYED_TURNOUT:
      case Conditional::ACTION_RESET_DELAYED_SENSOR:
      case Conditional::ACTION_DELAYED_TURNOUT:
      case Conditional::ACTION_DELAYED_SENSOR:
          str = str + tr("After") + " ";
          //try {
          bool bOk;
          _actionString.toInt(&bOk);
          str = str + _actionString + " " + tr("Seconds")+ ".";
          //} catch (NumberFormatException nfe) {
          if(!bOk)
          {
              str = str + _actionString + " " + tr("ValueInMemory")
                   + " " + tr("Seconds") + ".";
          }
          break;
      case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
      case Conditional::ACTION_SET_LIGHT_INTENSITY:
          try {
              //int t = Integer.parseInt(_actionString);
              str = str + " " + tr("to")+ " "+ _actionString + ".";
          } catch (NumberFormatException nfe) {
              str = str + " " + tr("to") + " " + _actionString + " "
                  + tr("ValueInMemory") + ".";
          }
          break;
      case Conditional::ACTION_JYTHON_COMMAND:
          str = str + " " + tr("ExecJythonCmd")+ " "+ _actionString+ ".";
          break;
      case Conditional::ACTION_SET_TRAIN_ID:
      case Conditional::ACTION_SET_TRAIN_NAME:
      case Conditional::ACTION_THROTTLE_FACTOR:
          str = str + ", \""+_actionString+"\" "+tr("onWarrant")+
              " \""+_deviceName+"\".";
          break;
     }
    }
    switch (_type)
    {
     case Conditional::ACTION_SET_LIGHT_INTENSITY:
     case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
         str = str + " " + tr("to")+ " " + _actionData + ".";
         break;
     case Conditional::ACTION_SET_FAST_CLOCK_TIME:
         str = str + " " +tr("to")+ " " +
               LogixTableAction::formatTime(_actionData / 60, _actionData - ((_actionData / 60) * 60));
         break;
    }
    return str;
}
