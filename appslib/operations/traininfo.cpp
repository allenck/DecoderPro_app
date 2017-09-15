#include "traininfo.h"
#include "activetrain.h"
#include "proxysensormanager.h"
#include "instancemanager.h"

//TrainInfo::TrainInfo(QObject *parent) : QObject(parent)
//{

//}
/**
 * TrainInfo is a temporary object specifying New Train information just read
 * from disk, or to be written to disk
 * <P>
 * Used in conjunction with TrainInfoFile.java to save and retrieve New Train
 * information
 * <P>
 * When adding a new item of New Train information, modifications need to be
 * made to TrainInfoFile.java and dispatcher-traininfo.DTD as well as this
 * module.
 *
 * @author	Dave Duchamp Copyright (C) 2009
 */
///*public*/ class TrainInfo {

/*public*/ TrainInfo::TrainInfo(QObject *parent) {
 // instance variables for both manual and automatic operation
 transitName = "";
 trainName = "";
 dccAddress = "";
 trainInTransit = false;
 startBlockName = "";
 destinationBlockName = "";
 trainFromRoster = true;
 trainFromTrains = false;
 trainFromUser = false;
 priority = 5;
 autoRun = false;
 resetWhenDone = false;
 allocateAllTheWay = false;
 reverseAtEnd = false;
 delayedStart = ActiveTrain::NODELAY;
 delayedRestart = ActiveTrain::NODELAY;
 departureTimeHr = 8;
 departureTimeMin = 00;
 delaySensorName = "";
 restartSensorName = "";
 restartDelayMin = 0;
 trainType = "";
 terminateWhenDone = false;
 loadAtStartup = false;

 // instance variables for automatic operation
 speedFactor = 1.0;
 maxSpeed = 0.6;
 rampRate = tr("RAMP_NONE");
 resistanceWheels = true;
 runInReverse = false;
 soundDecoder = false;
 maxTrainLength = 200.0;

}

///*private*/ static final ResourceBundle rb = ResourceBundle
//        .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");


// temporary instance variables
/**
 * Access methods for manual and automatic instance variables
 */
/*protected*/ void TrainInfo::setTransitName(QString s) {
    transitName = s;
}

/*protected*/ QString TrainInfo::getTransitName() {
    return transitName;
}

/*protected*/ void TrainInfo::setTrainName(QString s) {
    trainName = s;
}

/*protected*/ QString TrainInfo::getTrainName() {
    return trainName;
}

/*protected*/ void TrainInfo::setDCCAddress(QString s) {
    dccAddress = s;
}

/*protected*/ QString TrainInfo::getDCCAddress() {
    return dccAddress;
}

/*protected*/ void TrainInfo::setTrainInTransit(bool b) {
    trainInTransit = b;
}

/*protected*/ bool TrainInfo::getTrainInTransit() {
    return trainInTransit;
}

/*protected*/ void TrainInfo::setStartBlockName(QString s) {
    startBlockName = s;
}

/*protected*/ QString TrainInfo::getStartBlockName() {
    return startBlockName;
}

/*protected*/ void TrainInfo::setDestinationBlockName(QString s) {
    destinationBlockName = s;
}

/*protected*/ QString TrainInfo::getDestinationBlockName() {
    return destinationBlockName;
}

/*protected*/ void TrainInfo::setTrainFromRoster(bool b) {
    trainFromRoster = b;
}

/*protected*/ bool TrainInfo::getTrainFromRoster() {
    return trainFromRoster;
}

/*protected*/ void TrainInfo::setTrainFromTrains(bool b) {
    trainFromTrains = b;
}

/*protected*/ bool TrainInfo::getTrainFromTrains() {
    return trainFromTrains;
}

/*protected*/ void TrainInfo::setTrainFromUser(bool b) {
    trainFromUser = b;
}

/*protected*/ bool TrainInfo::getTrainFromUser() {
    return trainFromUser;
}

/*protected*/ void TrainInfo::setTerminateWhenDone(bool b) {
    terminateWhenDone = b;
}

/*protected*/ bool TrainInfo::getTerminateWhenDone() {
    return terminateWhenDone;
}

/*protected*/ void TrainInfo::setPriority(int pri) {
    priority = pri;
}

/*protected*/ int TrainInfo::getPriority() {
    return priority;
}

/*protected*/ void TrainInfo::setAutoRun(bool b) {
    autoRun = b;
}

/*protected*/ bool TrainInfo::getAutoRun() {
    return autoRun;
}

/*protected*/ void TrainInfo::setResetWhenDone(bool b) {
    resetWhenDone = b;
}

/*protected*/ bool TrainInfo::getResetWhenDone() {
    return resetWhenDone;
}

/*protected*/ void TrainInfo::setAllocateAllTheWay(bool b) {
            allocateAllTheWay = b;
}

/*protected*/ bool TrainInfo::getAllocateAllTheWay() {
            return allocateAllTheWay;
}
/*protected*/ void TrainInfo::setReverseAtEnd(bool b) {
    reverseAtEnd = b;
}

/*protected*/ bool TrainInfo::getReverseAtEnd() {
    return reverseAtEnd;
}

/*protected*/ void TrainInfo::setDelayedStart(int ds) {
    delayedStart = ds;
}
/**
 * delayed start code for this train
 * @return one of ActiveTrain.NODELAY,TIMEDDELAY,SENSORDELAY
 */
/*protected*/ int TrainInfo::getDelayedStart() {
    return delayedStart;
}

/*protected*/ void TrainInfo::setDepartureTimeHr(int hr) {
    departureTimeHr = hr;
}

/*protected*/ int TrainInfo::getDepartureTimeHr() {
    return departureTimeHr;
}

/*protected*/ void TrainInfo::setDepartureTimeMin(int min) {
    departureTimeMin = min;
}

/*protected*/ int TrainInfo::getDepartureTimeMin() {
    return departureTimeMin;
}

/*protected*/ void TrainInfo::setDelaySensorName(QString sen) {
    delaySensorName = sen;
}

/*protected*/ QString TrainInfo::getDelaySensorName() {
    return delaySensorName;
}

/**
 * retrieve the startup delay sensor using the delay sensor name
 * @return delay sensor, or NULL if delay sensor name not set
 */
/*protected*/ Sensor* TrainInfo::getDelaySensor() {
    if (delaySensorName == NULL) {
        return NULL;
    }
    return ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor(delaySensorName);
}

/*protected*/ void TrainInfo::setTrainType(QString s) {
    trainType = s;
}

/*protected*/ QString TrainInfo::getTrainType() {
    return trainType;
}
/*protected*/ void TrainInfo::setDelayedRestart(int ds) {
    delayedRestart = ds;
}
/**
 * return restart code for this train, only used for continuous running
 * @return one of ActiveTrain.NODELAY,TIMEDDELAY,SENSORDELAY
 */
/*protected*/ int TrainInfo::getDelayedRestart() {
    return delayedRestart;
}

/*protected*/ void TrainInfo::setRestartSensorName(QString sen) {
    restartSensorName = sen;
}

/*protected*/ QString TrainInfo::getRestartSensorName() {
    return restartSensorName;
}
/**
 * retrieve the restart sensor using the restart sensor name
 * @return restart sensor, or NULL if the restart sensor name not set
 */
/*protected*/ Sensor* TrainInfo::getRestartSensor() {
    if (restartSensorName == NULL) {
        return NULL;
    }
    return ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(restartSensorName);
}

/**
 * number of minutes to delay between restarting for continuous runs
 * @param s number of minutes to delay
 */
/*protected*/ void TrainInfo::setRestartDelayMin(int s) {
    restartDelayMin = s;
}

/*protected*/ int TrainInfo::getRestartDelayMin() {
    return restartDelayMin;
}

/*protected*/ bool TrainInfo::getLoadAtStartup() {
    return loadAtStartup;
}

/*protected*/ void TrainInfo::setLoadAtStartup(bool loadAtStartup) {
    this->loadAtStartup = loadAtStartup;
}

/**
 * Access methods for automatic operation instance variables
 */
/*protected*/ void TrainInfo::setSpeedFactor(float f) {
    speedFactor = f;
}

/*protected*/ float TrainInfo::getSpeedFactor() {
    return speedFactor;
}

/*protected*/ void TrainInfo::setMaxSpeed(float f) {
    maxSpeed = f;
}

/*protected*/ float TrainInfo::getMaxSpeed() {
    return maxSpeed;
}

/*protected*/ void TrainInfo::setRampRate(QString s) {
    rampRate = s;
}

/*protected*/ QString TrainInfo::getRampRate() {
    return rampRate;
}

/*protected*/ void TrainInfo::setResistanceWheels(bool b) {
    resistanceWheels = b;
}

/*protected*/ bool TrainInfo::getResistanceWheels() {
    return resistanceWheels;
}

/*protected*/ void TrainInfo::setRunInReverse(bool b) {
    runInReverse = b;
}

/*protected*/ bool TrainInfo::getRunInReverse() {
    return runInReverse;
}

/*protected*/ void TrainInfo::setSoundDecoder(bool b) {
    soundDecoder = b;
}

/*protected*/ bool TrainInfo::getSoundDecoder() {
    return soundDecoder;
}

/*protected*/ void TrainInfo::setMaxTrainLength(float f) {
    maxTrainLength = f;
}

/*protected*/ float TrainInfo::getMaxTrainLength() {
    return maxTrainLength;
}
