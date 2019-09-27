#include "rampdata.h"
#include "exceptions.h"

///*public*/ class RampData {


/*static*/ float RampData::INCRE_RATE = 1.10f;  // multiplier to increase throttle increments

RampData::RampData(float throttleIncre, int timeIncre,QObject*parent) : QObject(parent) {
    _throttleInterval = throttleIncre;
    _timeInterval = timeIncre;
}

/*protected*/ bool RampData::isUpRamp() {
    return _upRamp;
}

/*protected*/ void RampData::makeThrottleSettings(float fromSet, float toSet) {
    _upRamp = (toSet >= fromSet);
    _settings = QList<float>();
    float lowSetting;
    float highSetting;
    float throttleIncre = _throttleInterval;
    if (_upRamp) {
        lowSetting = fromSet;
        highSetting = toSet;
    } else {
        lowSetting = toSet;
        highSetting = fromSet;
    }
    while (lowSetting < highSetting) {
        _settings.append((lowSetting));
        lowSetting += throttleIncre;
        throttleIncre *= INCRE_RATE;
    }
    _settings.append((highSetting));
}

/*protected*/ void RampData::setRampLength(float rampLength) {
    _rampLength =  rampLength;
}

/*protected*/ float RampData::getRampLength() {
    return _rampLength;
}

/*protected*/ float RampData::getMaxSpeed() {
    if (_settings.isEmpty()) {
        throw IllegalArgumentException("Null array of throttle settings");
    }
    return _settings.value(_settings.size() - 1);
}

/*protected*/ QListIterator<float> RampData::speedIterator(bool up) {
    if (up) {
        return QListIterator<float>(_settings);//_settings.at(0);
    } else {
     QListIterator<float> iter(_settings);
     iter.toBack();
     return iter;// _settings.at(_settings.size());

    }
}

/*protected*/ int RampData::getRampTimeIncrement() {
    return _timeInterval;
}
