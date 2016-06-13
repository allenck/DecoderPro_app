#include "throttlesetting.h"

ThrottleSetting::ThrottleSetting(QObject *parent) :
    QObject(parent)
{
}
///*public*/ class ThrottleSetting {


//    /*public*/ ThrottleSetting() {
//    }

/*public*/ ThrottleSetting::ThrottleSetting(long time, QString command, QString value, QString blockName, QObject *parent) :
    QObject(parent){
    _time = time;
    _command = command;
    _value = value;
    _blockName = blockName;
}
/*public*/ ThrottleSetting::ThrottleSetting(ThrottleSetting* ts,QObject *parent) :
    QObject(parent)
{
 //this(ts->getTime(), ts->getCommand(), ts->getValue(), ts->getBlockName());
    _time = ts->getTime();
    _command = ts->getCommand();
    _value = ts->getValue();
    _blockName = ts->getBlockName();
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

/*public*/ void ThrottleSetting::setBlockName(QString blockName) { _blockName = blockName; }
/*public*/ QString ThrottleSetting::getBlockName() { return _blockName; }

/*public*/ QString ThrottleSetting::toString() {
    return "ThrottleSetting: wait "+QString::number(_time)+"ms for "+_command+"= "+_value+" at block "+_blockName;
}
