#include "topologyinfo.h"
#include "ctcserialdata.h"
#include "nbhsensor.h"
#include "block.h"
#include "signalmast.h"
#include "signalmastlogic.h"
#include "turnout.h"

/**
 * This class contains all of the information needed (in lists) for the higher level
 * "TRL_Rules" to generate all of the entries in "_mTRL_TrafficLockingRulesSSVList"
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019, 2020
 */

///*public*/ class TopologyInfo {
    /*public*/ TopologyInfo::TopologyInfo(QObject *parent) : QObject(parent) { // Temporary for test suite only
        _mCTCSerialData = nullptr;
        _mDestinationSignalMast = "";
        _mNormal = "";
        _mReverse = "";
    }
    /*public*/ TopologyInfo::TopologyInfo(CTCSerialData* ctcSerialData, QString destinationSignalMast, QString normal, QString reverse,QObject *parent) : QObject(parent) {
        _mCTCSerialData = ctcSerialData;
        _mDestinationSignalMast = destinationSignalMast;
        _mNormal = normal;
        _mReverse = reverse;
    }
    /*public*/ QString TopologyInfo::getDestinationSignalMast() { return _mDestinationSignalMast; }

    /**
     * Simple class to contain simple info about a turnout.
     */
    /*private*/ /*static*/ class TurnoutInfo {
        /*public*/ /*final*/ QString _mOSSectionText;
        /*public*/ /*final*/ QString _mNormalReversed;
        /*public*/ /*final*/ int    _mUniqueID;
        /*public*/ TurnoutInfo(QString OSSectionText, QString normalReversed, int uniqueID) {
            _mOSSectionText = OSSectionText;
            _mNormalReversed = normalReversed;
            _mUniqueID = uniqueID;
        }
     friend class TopologyInfo;
    };

    /**
     * @return true if any of our lists have anything.
     */
    /*public*/ bool TopologyInfo::nonEmpty() { return !_mSensors.isEmpty() || !_mTurnoutInfos.isEmpty(); }

    /**
     * Quick and dirty routine to get O.S. section information.
     *
     * @param index Index into array
     * @return null if no information, else text (of form "29/30" for instance)
     */
    /*public*/ QString TopologyInfo::getOSSectionText(int index) {
        if (index < _mTurnoutInfos.size()) { // Safety: Can return info:
            return _mTurnoutInfos.value(index)->_mOSSectionText;
        } else {
            return QString();
        }
    }


    /**
     * Quick and dirty routine to get "Normal"/"Reverse" information.
     *
     * @param index Index into array
     * @return "Normal" if no information, else text (of form "Normal" for instance)
     */
    /*public*/ QString TopologyInfo::getNormalReversed(int index) {
        if (index < _mTurnoutInfos.size()) { // Safety: Can return info:
            return _mTurnoutInfos.value(index)->_mNormalReversed;
        } else {
            return "Normal";    // Doesn't hurt to return this for a turnout that has no information.
        }
    }


    /**
     * Quick and dirty routine to get the Display Name of the sensor.
     *
     * @param index Index into array
     * @return "" if no information, else text (of form "SW31-OS" for instance)
     */
    /*public*/ QString TopologyInfo::getSensorDisplayName(int index) {
        if (index < _mSensors.size()) { // Safety: Can return info:
            return _mSensors.value(index)->getDisplayName();
        } else {
            return "";
        }
    }


    /**
     * Quick and dirty routine to get the unique id..
     *
     * @param index Index into array
     * @return null if no information, else uniqueID as String of the O.S. section.
     */
    /*public*/ QString TopologyInfo::getUniqueID(int index) {
        if (index < _mTurnoutInfos.size()) { // Safety: Can return info:
            return QString::number(_mTurnoutInfos.value(index)->_mUniqueID);
        } else {
            return QString();
        }
    }


    /**
     * Quick and dirty routine to all all of the sensors in the passed blocks to
     * our internal lists.  Duplicates are ignored.  It is possible that the user
     * didn't associate a sensor with the block.  Ignore such entries.
     * @param blocks    List of Blocks to add.
     */
    /*public*/ void TopologyInfo::addBlocks(QList<Block*> blocks) {
        for (Block* block : blocks) {
            Sensor* sensor = block->getSensor();
            if (nullptr != sensor && !_mSensors.contains(sensor)) { //  Safety: valid && VERIFY not in list already for some reason (safety, shouldn't happen):
                _mSensors.append(sensor);
//              _mSensorNamesDebug.add(sensor.getDisplayName());
            }
        }
    }


    /**
     * Quick and dirty routine to add all of the turnouts in SML to our internal lists.
     * Duplicates are ignored.
     *
     * @param signalMastLogic   SML to work against.
     * @param signalMast        Destination mast in SML.
     */
    /*public*/ void TopologyInfo::addTurnouts(SignalMastLogic* signalMastLogic, SignalMast* signalMast) {
//  Right now, I cannot make a subroutine call out of this, because I have to call two different
//  routines at the lowest level: "signalMastLogic.getTurnoutState" and "signalMastLogic.getAutoTurnoutState"
//  depending on which it is.  In Java method reference is a way.  But I'm lazy and in a hurry:
        for (Turnout* turnout : signalMastLogic->getTurnouts(signalMast)) {
            if (!_mTurnouts.contains(turnout)) {    // VERIFY not in list already for some reason (safety, shouldn't happen):
                _mTurnouts.append(turnout);            // For above if statement dup check.
//  Need to convert the turnout to an O.S. section text:
                CTCSerialData::CTCTurnoutData* turnoutData = _mCTCSerialData->getCTCTurnoutData(turnout);
                if (nullptr != turnoutData) { // Safety:
//  ToDo someday: Reverse "isNormal" if feedback different?
                    bool isNormal = signalMastLogic->getTurnoutState(turnout, signalMast) == Turnout::CLOSED;
                    _mTurnoutInfos.append(new TurnoutInfo(turnoutData->_mOSSectionText, isNormal ? _mNormal : _mReverse, turnoutData->_mUniqueID));
//                  _mOSSectionInfosDebug.add(OSSectionText);
                }
            }
        }
        for (Turnout* turnout : signalMastLogic->getAutoTurnouts(signalMast)) {
            if (!_mTurnouts.contains(turnout)) {    // VERIFY not in list already for some reason (safety, shouldn't happen):
                _mTurnouts.append(turnout);            // For above if statement dup check.
//  Need to convert the turnout to an O.S. section text:
                CTCSerialData::CTCTurnoutData* turnoutData = _mCTCSerialData->getCTCTurnoutData(turnout);
                if (nullptr != turnoutData) { // Safety:
//  ToDo someday: Reverse "isNormal" if feedback different?
                    bool isNormal = signalMastLogic->getAutoTurnoutState(turnout, signalMast) == Turnout::CLOSED;
                    _mTurnoutInfos.append(new TurnoutInfo(turnoutData->_mOSSectionText, isNormal ? _mNormal : _mReverse, turnoutData->_mUniqueID));
//                  _mOSSectionInfosDebug.add(OSSectionText);
                }
            }
        }
    }
