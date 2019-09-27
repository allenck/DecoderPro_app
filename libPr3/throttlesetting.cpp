#include "throttlesetting.h"
#include "loggerfactory.h"
#include "sensor.h"
#include "instancemanager.h"
#include "namedbeanhandlemanager.h"
#include "warrant.h"
#include "warrantmanager.h"
#include "sensormanager.h"
#include "oblock.h"
#include "oblockmanager.h"

ThrottleSetting::ThrottleSetting(QObject *parent) :
    QObject(parent)
{
}
///*public*/ class ThrottleSetting {


//    /*public*/ ThrottleSetting() {
//    }

/*public*/ ThrottleSetting::ThrottleSetting(long time, QString command, QString value, QString beanName, QObject *parent) :
    QObject(parent){
    _time = time;
    _command = command;
    _value = value;
    setNamedBean(command, beanName);
    _speed = 0;
}
/*public*/ ThrottleSetting::ThrottleSetting(long time, QString command, QString value, QString beanName, float sp, QObject *parent) : QObject(parent){
        _time = time;
        _command = command;
        _value = value;
        setNamedBean(command, beanName);
        _speed = sp;
    }
/*public*/ ThrottleSetting::ThrottleSetting(ThrottleSetting* ts,QObject *parent) :
    QObject(parent)
{
 //this(ts->getTime(), ts->getCommand(), ts->getValue(), ts->getBlockName());
    _time = ts->getTime();
    _command = ts->getCommand();
    _value = ts->getValue();
    _namedHandle = ts->getNamedBeanHandle();
    _speed = ts->getSpeed();
}

/**
* Time is an object so that a "synch to block entry" notation can be used
* rather than elapsed time.
*/
/*public*/ void ThrottleSetting::setTime(long time) { _time = time; }
/*public*/ long ThrottleSetting::getTime() { return _time; }

/*public*/ void ThrottleSetting::setCommand(QString command) { _command = command; }
/*public*/ QString ThrottleSetting::getCommand() { return _command; }

/*public*/ void ThrottleSetting::setValue(QString value) { _value = value; }
/*public*/ QString ThrottleSetting::getValue() { return _value; }

/*public*/ void ThrottleSetting::setSpeed(float s) {
    _speed = s;
}

/*public*/ float ThrottleSetting::getSpeed() {
    return _speed;
}

//_namedHandle may be of 3 different types
/*public*/ void ThrottleSetting::setNamedBean(QString cmd, QString name) {
    if (log->isDebugEnabled()) {
        log->debug(tr("setNamedBean(%1, %2)").arg(cmd).arg(name));
    }
    if (cmd == "" || name == "" || name.trimmed() ==("")) {
        _namedHandle = nullptr;
        return;
    }
    cmd = cmd.toUpper();
    try {
        if ("SET SENSOR" ==(cmd) || "WAIT SENSOR" == (cmd)) {
            Sensor* s = InstanceManager::sensorManagerInstance()->provideSensor(name);
            _namedHandle = (NamedBeanHandle<NamedBean*>*)((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, s);
        } else if ("RUN WARRANT" == (cmd)) {
            Warrant* w = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->provideWarrant(name);
            _namedHandle = (NamedBeanHandle<NamedBean*>*)((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, w);
        } else {
            OBlock* b = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(name);
            if (b != nullptr) {
                _namedHandle = (NamedBeanHandle<NamedBean*>*)((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, b);
            }
        }
    } catch (IllegalArgumentException iae) {
        log->error(iae.toString());
    }
}

// _namedHandle may be of 3 different types
/*public*/  void ThrottleSetting::setNamedBeanHandle(NamedBeanHandle <NamedBean*>* bh) {
    _namedHandle = bh;
}

// _namedHandle may be of 3 different types
/*public*/ NamedBeanHandle<NamedBean*>* ThrottleSetting::getNamedBeanHandle() {
    return _namedHandle;
}

/*public*/ QString ThrottleSetting::getBeanDisplayName() {
    if (_namedHandle == nullptr) {
        return "";
    }
    return _namedHandle->getBean()->getDisplayName();
}

/*public*/ QString ThrottleSetting::getBeanSystemName() {
    if (_namedHandle==nullptr) {
        return "";
    }
    return _namedHandle->getBean()->getSystemName();
}

//@Override
/*public*/ QString ThrottleSetting::toString() {
    QString sb = QString("ThrottleSetting: wait ");
    sb.append(QString::number(_time));
    sb.append("ms then do ");
    sb.append(_command);
    sb.append(" = ");
    sb.append(_value);
    sb.append(" for bean \"");
    sb.append( getBeanDisplayName());
    sb.append("\" at trackSpeed ");
    sb.append(QString::number( getSpeed()));
    sb.append("\"");
    return sb;
}

/*private*/ /*final*/ /*static*/ Logger* ThrottleSetting::log = LoggerFactory::getLogger("ThrottleSetting");
