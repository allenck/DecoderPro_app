#include "switchindicatorsroute.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 *
 * The purpose of this object is to just see if the passed indicators are all
 * lit (Sensor.ACTIVE), meaning that the specified route is "selected".
 * Any unspecified indicators are ignored.
 */
///*public*/ class SwitchIndicatorsRoute {

/*public*/ SwitchIndicatorsRoute::SwitchIndicatorsRoute(   QString module, QString userIdentifier, QString parameter,
                                QString switchIndicator1,
                                QString switchIndicator2,
                                QString switchIndicator3,
                                QString switchIndicator4,
                                QString switchIndicator5,
                                QString switchIndicator6, QObject *parent) : QObject(parent) {
    _mSwitchIndicator1 = new NBHSensor(module, userIdentifier, parameter + " switchIndicator1", switchIndicator1, true);    // NOI18N
    _mSwitchIndicator2 = new NBHSensor(module, userIdentifier, parameter + " switchIndicator2", switchIndicator2, true);    // NOI18N
    _mSwitchIndicator3 = new NBHSensor(module, userIdentifier, parameter + " switchIndicator3", switchIndicator3, true);    // NOI18N
    _mSwitchIndicator4 = new NBHSensor(module, userIdentifier, parameter + " switchIndicator4", switchIndicator4, true);    // NOI18N
    _mSwitchIndicator5 = new NBHSensor(module, userIdentifier, parameter + " switchIndicator5", switchIndicator5, true);    // NOI18N
    _mSwitchIndicator6 = new NBHSensor(module, userIdentifier, parameter + " switchIndicator6", switchIndicator6, true);    // NOI18N
}

/*public*/ SwitchIndicatorsRoute::SwitchIndicatorsRoute(NBHSensor* switchIndicator1, NBHSensor* switchIndicator2, NBHSensor* switchIndicator3, NBHSensor* switchIndicator4, NBHSensor* switchIndicator5, NBHSensor* switchIndicator6,QObject *parent) : QObject(parent) {
    _mSwitchIndicator1 = switchIndicator1;
    _mSwitchIndicator2 = switchIndicator2;
    _mSwitchIndicator3 = switchIndicator3;
    _mSwitchIndicator4 = switchIndicator4;
    _mSwitchIndicator5 = switchIndicator5;
    _mSwitchIndicator6 = switchIndicator6;
}

/*public*/ SwitchIndicatorsRoute::SwitchIndicatorsRoute(QList<NBHSensor *> *switchIndicators,  QObject *parent) : QObject(parent){
    int rows = switchIndicators->size();
    int i = 0;
    if (i < rows) _mSwitchIndicator1 = switchIndicators->at(i++); else _mSwitchIndicator1 = nullptr;
    if (i < rows) _mSwitchIndicator2 = switchIndicators->at(i++); else _mSwitchIndicator2 = nullptr;
    if (i < rows) _mSwitchIndicator3 = switchIndicators->at(i++); else _mSwitchIndicator3 = nullptr;
    if (i < rows) _mSwitchIndicator4 = switchIndicators->at(i++); else _mSwitchIndicator4 = nullptr;
    if (i < rows) _mSwitchIndicator5 = switchIndicators->at(i++); else _mSwitchIndicator5 = nullptr;
    if (i < rows) _mSwitchIndicator6 = switchIndicators->at(i++); else _mSwitchIndicator6 = nullptr;
}

/*public*/ bool SwitchIndicatorsRoute::isRouteSelected() {
    if (!isSwitchIndicatorLit(_mSwitchIndicator1)) return false;
    if (!isSwitchIndicatorLit(_mSwitchIndicator2)) return false;
    if (!isSwitchIndicatorLit(_mSwitchIndicator3)) return false;
    if (!isSwitchIndicatorLit(_mSwitchIndicator4)) return false;
    if (!isSwitchIndicatorLit(_mSwitchIndicator5)) return false;
    if (!isSwitchIndicatorLit(_mSwitchIndicator6)) return false;
    return true;
}

//  Quick and Dirty Routine: If it doesn't exist, it's considered lit.  If it exists, ACTIVE = lit.
/*private*/ bool SwitchIndicatorsRoute::isSwitchIndicatorLit(NBHSensor* sensor) {
    if (sensor == nullptr) return true;
    if (sensor->valid()) return sensor->getKnownState() == Sensor::ACTIVE;
    return true;
}
