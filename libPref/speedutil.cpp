#include "speedutil.h"
#include "loggerfactory.h"
#include "rosterentry.h"
#include "dcclocoaddress.h"
#include "instancemanager.h"
#include "warrantmanager.h"
#include "rosterspeedprofile.h"
#include "roster.h"
#include "signalspeedmap.h"
#include "warrantpreferences.h"
#include "file.h"
#include "rosterspeedprofile.h"
#include "warrant.h"
#include "nxframe.h"
#include "blockorder.h"
#include "opath.h"
#include "oblock.h"
#include "rampdata.h"

SpeedUtil::SpeedUtil(QObject *parent) : QObject(parent)
{

}
/**
 * All speed related method transferred from Engineer and Warrant classes.
 * Until June 2017, the problem of determining the actual track speed of a
 * model train in millimeters per millisecond (same as meters/sec) from the
 * throttle setting was usually done with an ad hoc "throttle factor".  When
 * created, the RosterSpeedProfile provides this needed conversion but
 * generally is not done by users for each of their locos.
 *
 * Methods to dynamically determine a RosterSpeedProfile for each loco are
 * implemented in this class.
 *
 * @author Pete Cressman Copyright (C) 2009, 2010, 2017
 *
 */
// /*public*/ class SpeedUtil {


/*public*/ /*static*/ float SpeedUtil::SCALE_FACTOR = 125; // divided by _scale, gives a rough correction for track speed
/*protected*/ SpeedUtil::SpeedUtil(QList<BlockOrder*>* orders, QObject* parent) : QObject(parent) {
    if (orders !=nullptr) {
        _orders = orders;
    }
}

/*protected*/ void SpeedUtil::setOrders(QList<BlockOrder*>* orders) {
    if (orders !=nullptr) {
        _orders = orders;
    }
}

/*protected*/ void SpeedUtil::setIsForward(bool forward) {
        _isForward = forward;
    }
/*public*/ RosterEntry* SpeedUtil::getRosterEntry() {
    if (_rosterEntry == nullptr) {
        _rosterEntry = Roster::getDefault()->entryFromTitle(_rosterId);
    }
    return _rosterEntry;
}

/**
 * Set the identifier for the Speed Profile
 * If a RosterEntry exists, _rosterId is the RosterEntry id,
 * otherwise it may be just the decoder address
 * @return key to speedProfile
 */
/*public*/ QString SpeedUtil::getRosterId() {
    return _rosterId;
}

/*public*/ void SpeedUtil::setRosterId(QString id) {
   if (log->isTraceEnabled()) log->debug(tr("setRosterId(%1) _rosterId= %1").arg(id).arg(_rosterId));
   if (id == "" || id!=(_rosterId)) {
        _mergeProfile = nullptr;
        _sessionProfile = nullptr;
        if (id != "") {
            _rosterId = id;
            makeSpeedTree();
            makeRampParameters();
        } else {
            _rosterId = nullptr;
            _rosterEntry = nullptr;
        }
    }
}

/*public*/ DccLocoAddress* SpeedUtil::getDccAddress() {
    if (_dccAddress == nullptr) {
        if (_rosterEntry != nullptr) {
            _dccAddress = _rosterEntry->getDccLocoAddress();
        } else if (_rosterId != ""){
            setDccAddress(_rosterId);
        }
    }
    return _dccAddress;
}

/*public*/ QString SpeedUtil::getAddress() {
    if (_dccAddress != nullptr) {
        return _dccAddress->toString();
    }
    return "";
}

/*protected*/ void SpeedUtil::setDccAddress(DccLocoAddress* dccAddr) {
    _dccAddress = dccAddr;
}

/**
 * Sets dccAddress and will fetch RosterEntry if one exists.
 * If _rosterEntry exists, _rosterId set to RosterEntry Id (which may or not be "id")
 * else _rosterId set to "id" or decoder address.
 * Called from:
 *    WarrantRoute.setAddress() - whatever is in _dccNumBox.getText()
 *    WarrantRoute.setTrainInfo(name) - whatever = name
 *    WarrantTableModel - whatever address is put into the ADDRESS_COLUMN
 * @param id address as a String, either RosterEntryTitle or decoder address
 * @return true if address found for id
 */
/*public*/ bool SpeedUtil::setDccAddress(QString id) {
    if (log->isTraceEnabled()) log->debug(tr("setDccAddress(%1) _rosterId= %2").arg(id).arg( _rosterId));
    if (id.isEmpty()) {
        setRosterId("");   // set _rosterId
        _dccAddress = nullptr;
       return false;
    } else if (id ==(_rosterId)){
        return true;
    }
    _rosterEntry = Roster::getDefault()->entryFromTitle(id);
    if (_rosterEntry == nullptr) {
        int index = id.indexOf('(');
        QString numId;
        if (index >= 0) {
            numId = id.mid(0, index);
        } else {
            QChar ch = id.at(id.length() - 1);
            if (!ch.isDigit()) {
                numId = id.mid(0, id.length() - 1);
            } else {
                numId = id;
            }
        }
        int num = numId.toInt();
        try {
            QList<RosterEntry*> l = Roster::getDefault()->matchingList("", "", "", "", "", "", "");
            if (l.size() > 0) {
                _rosterEntry = l.at(0);
                if (num != 0) {
                    // In some systems, such as Maerklin MFX or ESU ECOS M4, the DCC address is always 0.
                    // That should not make us overwrite the _trainId.
                    setRosterId(_rosterEntry->getId());
                }
                _dccAddress = _rosterEntry->getDccLocoAddress();
            } else {
                bool isLong = true;
                if ((index + 1) < id.length()
                        && (id.at(index + 1) == 'S' || id.at(index + 1) == 's')) {
                    isLong = false;
                }
                _dccAddress = new DccLocoAddress(num, isLong);
                setRosterId(_dccAddress->toString()); // not a rosterId, but does identify the  DccLocoAddress
           }
        } catch (NumberFormatException e) {
            _dccAddress = nullptr;
            return false;
        }
    } else {
        setRosterId(id);
        _dccAddress = _rosterEntry->getDccLocoAddress();
//            _rosterId = _rosterEntry.getId();
    }
    if (log->isTraceEnabled()) log->debug(tr("setDccAddress: _rosterId= %1, _dccAddress= %2").arg(_rosterId).arg(_dccAddress->toString()));
    return true;
}

// Possibly customize these ramping values per warrant or loco later
// for now use global values set in WarrantPreferences
// user's ramp speed increase amount
/*protected*/ float SpeedUtil::getRampThrottleIncrement() {
    return _stepRampThrottleIncrement;
}

/*protected*/ int SpeedUtil::getRampTimeIncrement() {
    return _stepRampTimeIncrement;
}

/** ms time to change one _stepRampThrottleIncrement amount
 * @param delta throttle change
 * @param increasing  is acceleration
 * @return momentum time
 */
/*protected*/ float SpeedUtil::getMomentumTime(float delta, bool increasing) {
    float incr = getThrottleSpeedStepIncrement();  // step amount
    if (increasing) {
        return _ma * qAbs(delta) / incr;   // accelerating
    } else {
        return _md * qAbs(delta) / incr;
    }
}

/**
 * throttle's minimum speed change amount
 * @return speed step amount
 */
/*protected*/ float SpeedUtil::getThrottleSpeedStepIncrement() {
    if (_throttle != nullptr) {
        return _throttle->getSpeedIncrement();
    }
    return 1.0f / 126.0f;
}

/*protected*/ RosterSpeedProfile* SpeedUtil::getSpeedProfile() {
    if (_mergeProfile == nullptr) {
        makeSpeedTree();
        makeRampParameters();
    }
    return _mergeProfile;
}

/*private*/ void SpeedUtil::makeSpeedTree()
{
    if (_rosterId == nullptr) {
        setDccAddress(getAddress());
    }
    if (log->isDebugEnabled()) log->debug(tr("makeSpeedTree for %1.").arg(_rosterId));
    WarrantManager* manager = static_cast<WarrantManager*>(InstanceManager::getDefault("WarrantManager"));
    _mergeProfile = manager->getMergeProfile(_rosterId);
    _sessionProfile = manager->getSessionProfile(_rosterId);
    if (_sessionProfile == nullptr) {
        _sessionProfile = new RosterSpeedProfile(nullptr);
    }
    if (_mergeProfile == nullptr) {
        _mergeProfile = new RosterSpeedProfile(getRosterEntry());   // will be a copy or an empty profile
        if (_rosterEntry!=nullptr) {
            if (log->isDebugEnabled()) log->debug("makeSpeedTree - Copy TreeMap");
            RosterSpeedProfile* speedProfile = _rosterEntry->getSpeedProfile();
            if (speedProfile!=nullptr) { // make copy of tree
                QMap<int, SpeedStep*> rosterTree = speedProfile->getProfileSpeeds();
                //for (QMap<int, SpeedStep*> entry : rosterTree.entrySet())
                QMapIterator<int, SpeedStep*> entry(rosterTree);
                while(entry.hasNext())
                {
                 entry.next();
                 _mergeProfile->setSpeed(entry.key(), entry.value()->getForwardSpeed(), entry.value()->getReverseSpeed());
                }
            }
        }
    }
    _signalSpeedMap = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"));

    if (log->isDebugEnabled()) log->debug(tr("SignalSpeedMap: throttle factor= %1, layout scale= %2 convesion to m/s= %3").arg(
             _signalSpeedMap->getDefaultThrottleFactor(), _signalSpeedMap->getLayoutScale(),
             _signalSpeedMap->getDefaultThrottleFactor() *  _signalSpeedMap->getLayoutScale() / SCALE_FACTOR));
}

/*private*/ void SpeedUtil::makeRampParameters() {
    WarrantPreferences* preferences = WarrantPreferences::getDefault();
    _stepRampTimeIncrement = preferences->getTimeIncrement();
    _stepRampThrottleIncrement = preferences->getThrottleIncrement();
    // Can't use actual speed step amount since these numbers are needed before throttle is acquired
    // Nevertheless throttle % is a reasonable approximation
    // default cv setting of momentum speed change per 1% of throttle increment
    _ma = 0;  // acceleration momentum time
    _md = 0;  // deceleration momentum time
    if (_rosterEntry!=nullptr) {
        QString fileName = LocoFile::getFileLocation() + _rosterEntry->getFileName();
        File* file;
        QDomElement root;
        XmlFile* xmlFile = new XmlFile();
        try {
            file = new File(fileName);
            if (file->length() == 0) {
                return;
            }
            root = xmlFile->rootFromFile(file);
        } catch (NullPointerException npe) {
            return;
        }
        catch (IOException  eb) {
            log->error("Exception while loading warrant preferences: " + eb.getMessage());
            return;
        }
        catch ( JDOMException eb) {
            log->error("Exception while loading warrant preferences: " + eb.getMessage());
            return;
        }
        if (root.isNull()) {
            return;
        }
        QDomElement child = root.firstChildElement("locomotive");
        if (child.isNull()) {
            return;
        }
        child = child.firstChildElement("values");
        if (child.isNull()) {
            return;
        }
        QDomNodeList list = child.elementsByTagName("CVvalue");
        int count = 0;
        //for (QDomNode cvn : list)
        for(int i=0; i < list.size(); i++)
        {
         QDomElement cv = list.at(i).toElement();
            QString attr = cv.attribute("name");
            if (attr != "") {
                if (attr == ("3")) {
                    _ma += getMomentumFactor(cv);
                   count++;
                } else if (attr ==("4")) {
                    _md += getMomentumFactor(cv);
                    count++;
                } else if (attr==("23")) {
                    _ma += getMomentumAdustment(cv);
                    count++;
                } else if (attr==("24")) {
                    _md += getMomentumAdustment(cv);
                    count++;
                }
            }
            if (count > 3) {
                break;
            }
        }
        if (_ma < 10) {
            _ma = 10;
        }
        if (_md < 10) {
            _md = 10;
        }
        if (_stepRampTimeIncrement < _ma) {
            _stepRampTimeIncrement = (int)_ma;
        }
        if (_stepRampTimeIncrement < _md) {
            _stepRampTimeIncrement = (int)_md;
        }
        if (log->isDebugEnabled()) log->debug(tr("makeRampParameters for %1, _ma= %2ms, _md= %3ms. rampIncr= %4").arg(
                _rosterId).arg(_ma).arg(_md).arg(_stepRampThrottleIncrement));
    }
}

// return milliseconds per one speed step
/*private*/ float SpeedUtil::getMomentumFactor(QDomElement cv) {
    QString attr = cv.attribute("value");
    float num = 0;
    if (attr != "") {
        bool bok;
             num =  attr.toInt(&bok);
            // even with instant speed change, allow some time for new speed to be attained
            // therefore add 1.  (.896 is NMRA spec)
//                return (num + 1) * 896 / 28;     // milliseconds per step
            num = (num + 1) * 896 * getThrottleSpeedStepIncrement();     // milliseconds per step
        if(!bok) {
            num = 0;
        }
    }
    if (log->isDebugEnabled()) log->debug(tr("getMomentumFactor for cv %1 #2, num= %3").arg(cv.attribute("name")).arg(attr).arg(num));
    return num;
}

// return milliseconds per one speed step
/*private*/ float SpeedUtil::getMomentumAdustment(QDomElement cv) {
    QString attr = cv.attribute("value");
    float num = 0;
    if (attr != "") {
        try {
            int val =attr.toInt();
            num = val & 0x3F;  //value is 6 bits
            if ((val & 0x40) != 0) {    // 7th bit sign
                num = -num;
            }
        } catch (NumberFormatException nfe) {
            num = 0;
        }
    }
    if (log->isDebugEnabled()) log->debug(tr("getMomentumAdustment for cv %1 %2,  num= %3").arg(cv.attribute("name")).arg(attr).arg(num));
    return num;
}

/*protected*/ bool SpeedUtil::profileHasSpeedInfo() {
    RosterSpeedProfile* speedProfile = getSpeedProfile();
    if (speedProfile == nullptr) {
        return false;
    }
    if (speedProfile->hasForwardSpeeds() || speedProfile->hasReverseSpeeds()) {
        return true;
    }
    return false;
}

/*protected*/ void SpeedUtil::stopRun(bool updateSpeedProfile) {
    if (updateSpeedProfile && _sessionProfile != nullptr) {
        WarrantManager* manager = static_cast<WarrantManager*>(InstanceManager::getDefault("WarrantManager"));
        manager->setSpeedProfiles(_rosterId, _mergeProfile, _sessionProfile);
    }
}

/************* runtime speed needs - throttle, engineer acquired ***************/

/**
 * @param throttle set DccThrottle
 */
/*protected*/ void SpeedUtil::setThrottle( DccThrottle* throttle) {
    _throttle = throttle;
    getSpeedProfile();
    // adjust user's setting to be throttle speed step settings
    float stepIncrement = _throttle->getSpeedIncrement();
    _rampThrottleIncrement = stepIncrement * qRound(getRampThrottleIncrement()/stepIncrement);
    if (log->isTraceEnabled()) log->debug(tr("User's Ramp increment modified to %1 (%2 speed steps)").arg(
            _rampThrottleIncrement).arg(qRound(_rampThrottleIncrement/stepIncrement)));
}

// return true if the speed named 'speed2' is strictly greater than that of 'speed1'
/*protected*/ bool SpeedUtil::secondGreaterThanFirst(QString speed1, QString speed2) {
    if (speed2 == nullptr) {
        return false;
    }
    if (speed1 == nullptr) {
        return true;
    }
    float s1 =  _signalSpeedMap->getSpeed(speed1);
    float s2 =  _signalSpeedMap->getSpeed(speed2);
    return (s1 < s2);
}

/**
 * Modify a throttle setting to match a speed name type
 * Modification is done according to the interpretation of the speed name
 * @param tSpeed throttle setting (current)
 * @param sType speed type name
 * @param isForward direction of travel
 * @return modified throttle setting
 */
/*protected*/ float SpeedUtil::modifySpeed(float tSpeed, QString sType) {
//        if (log->isTraceEnabled()) log->trace("modifySpeed speed= {} for SpeedType= \"{}\"", tSpeed, sType);
    if (sType == ( Warrant::Stop)) {
        return 0.0f;
    }
    if (sType == ( Warrant::EStop)) {
        return -1.0f;
    }
    float throttleSpeed = tSpeed;       // throttleSpeed is a throttle setting
    if (sType == ( Warrant::Normal)) {
        return throttleSpeed;
    }
    float signalSpeed =  _signalSpeedMap->getSpeed(sType);

    switch ( _signalSpeedMap->getInterpretation()) {
        case SignalSpeedMap::PERCENT_NORMAL:
            throttleSpeed *= signalSpeed / 100;      // ratio of normal
            break;
        case SignalSpeedMap::PERCENT_THROTTLE:
            signalSpeed = signalSpeed / 100;            // ratio of full throttle setting
            if (signalSpeed < throttleSpeed) {
                throttleSpeed = signalSpeed;
            }
            break;

        case SignalSpeedMap::SPEED_MPH:          // convert miles per hour to track speed
    {
            signalSpeed = signalSpeed /  _signalSpeedMap->getLayoutScale();
            signalSpeed = signalSpeed / 2.2369363f;  // layout track speed mph -> mm/ms
            float trackSpeed = getTrackSpeed(throttleSpeed);
            if (signalSpeed < trackSpeed) {
                throttleSpeed = getThrottleSettingForSpeed(signalSpeed, _throttle->getIsForward());
                if (throttleSpeed <= 0.0f) {
                    return signalSpeed *  _signalSpeedMap->getLayoutScale() / (SCALE_FACTOR * _signalSpeedMap->getDefaultThrottleFactor());
                }
            }
            break;
}
        case SignalSpeedMap::SPEED_KMPH:
    {
            signalSpeed = signalSpeed /  _signalSpeedMap->getLayoutScale();
            signalSpeed = signalSpeed / 3.6f;  // layout track speed mm/ms -> kmph
            float trackSpeed = getTrackSpeed(throttleSpeed);
            if (signalSpeed < trackSpeed) {
                throttleSpeed = getThrottleSettingForSpeed(signalSpeed, _throttle->getIsForward());
                if (throttleSpeed <= 0.0f) {
                    return signalSpeed *  _signalSpeedMap->getLayoutScale() / (SCALE_FACTOR * _signalSpeedMap->getDefaultThrottleFactor());
                }
            }
            break;
    }
        default:
            log->error(tr("Unknown speed interpretation %1").arg( _signalSpeedMap->getInterpretation()));
            throw IllegalArgumentException("Unknown speed interpretation " +  _signalSpeedMap->getInterpretation());
    }
    if (log->isTraceEnabled()) log->trace(tr("modifySpeed: from %1, to %2, signalSpeed= %3. interpretation= %4").arg(
            tSpeed).arg(throttleSpeed).arg(signalSpeed).arg(_signalSpeedMap->getInterpretation()));
    return throttleSpeed;
}


/**
 * Get the track speed in millimeters per millisecond (= meters/sec)
 * If SpeedProfile has no speed information an estimate is given using the WarrantPreferences
 * throttleFactor.
 * NOTE:  Call profileHasSpeedInfo() first to determine if a reliable speed is known.
 * for a given throttle setting and direction.
 * SpeedProfile returns 0 if it has no speed information
 * @param throttleSetting throttle setting
 * @param isForward direction
 * @return track speed in millimeters/millisecond (not mm/sec)
 */
/*protected*/ float SpeedUtil::getTrackSpeed(float throttleSetting) {
    if (throttleSetting <= 0.0f) {
        return 0.0f;
    }
    RosterSpeedProfile* speedProfile = getSpeedProfile();
    // Note SpeedProfile uses milliseconds per second.
    float speed = speedProfile->getSpeed(throttleSetting, _isForward) / 1000;
    if (speed <= 0.0f) {
        float factor =  _signalSpeedMap->getDefaultThrottleFactor() * SCALE_FACTOR /  _signalSpeedMap->getLayoutScale();
        speed = throttleSetting * factor;
        if (log->isTraceEnabled()) log->trace(tr("getTrackSpeed for setting= %1, speed= %2, by factor= %3. train= %4").arg(
                throttleSetting).arg(speed).arg(factor).arg(_rosterId));
    } else {
        if (log->isTraceEnabled()) log->trace(tr("getTrackSpeed for setting= %1, speed= %2, SpeedProfile. train= %3").arg(
                throttleSetting).arg(speed).arg(_rosterId));
    }
    return speed;
}

/**
 * Get the throttle setting needed to achieve a given track speed
 * track speed is mm/ms.  SpeedProfile wants mm/s
 * SpeedProfile returns 0 if it has no speed information
 * @param trackSpeed in millimeters per millisecond (m/s)
 * @param isForward direction
 * @return throttle setting or 0
 */
/*protected*/ float SpeedUtil::getThrottleSettingForSpeed(float trackSpeed, bool isForward) {
    RosterSpeedProfile* speedProfile = getSpeedProfile();
    return speedProfile->getThrottleSetting(trackSpeed * 1000, isForward);
}

/**
 * Get distance traveled at a constant speed. If this is called at
 * a speed change the throttleSetting should be modified to reflect the
 * average speed over the time interval.
 * @param speedSetting Recorded (Normal) throttle setting
 * @param speedtype speed name to modify throttle setting to get modified speed
 * @param time milliseconds
 * @param isForward direction
 * @return distance in millimeters
 */
/*protected*/ float SpeedUtil::getDistanceTraveled(float speedSetting, QString speedtype, float time) {
 if (time <= 0) {
     return 0;
 }
 float throttleSetting = modifySpeed(speedSetting, speedtype);
 return getTrackSpeed(throttleSetting) * time;
}

/**
 * Get time needed to travel a distance at a constant speed.
 * @param throttleSetting Throttle setting
 * @param distance in millimeters
 * @param isForward direction
 * @return time in milliseconds
 */
/*protected*/ float SpeedUtil::getTimeForDistance(float throttleSetting, float distance) {
    float speed = getTrackSpeed(throttleSetting);
    if (distance <= 0 || speed <= 0) {
        return 0.0f;
    }
    return (distance/speed);
}

/**
 * get time to ramp up/down from/to speed 0 and travel no farther than given distance.
 * @param rampLen ramp length
 * @return time
 *
protected float timeOfRampDistance(float rampLen, bool isForward) {
    float time = 0.0f;
    float dist = 0.0f;
    float deltaTime = getRampTimeIncrement();
    float deltaThrottle = getRampThrottleIncrement();
    float momentumTime = getMomentumTime(deltaThrottle, isForward);
    float speed = deltaThrottle;

    while (dist <= rampLen) {
        float d = getTrackSpeed(speed + deltaThrottle/2, isForward) * momentumTime;
        if (deltaTime > momentumTime) {
            d += getTrackSpeed(speed + deltaThrottle, isForward) * (deltaTime - momentumTime);
        }
        speed += deltaThrottle;
        dist += d;
        time += deltaTime;
    }
    time -= deltaTime;  // back out time when dist exceeded
    return time;
}
*/

/**
  * Get ramp length needed to change speed using the WarrantPreference deltas for
  * throttle increment and time increment.  This should only be used for ramping down
  * when the warrant is interrupted for a signal or obstacle ahead.  The length is
  * increased by 40 scale feet to allow a safety margin.
  * @param curSetting current throttle setting
  * @param curSpeedType current speed type
  * @param toSpeedType Speed type change
  * @return distance in millimeters
  */
 /*protected*/ float SpeedUtil::rampLengthForRampDown(float curSetting, QString curSpeedType, QString toSpeedType) {
     if (curSpeedType == (toSpeedType)) {
         return 0.0f;
     }
     float fromSpeed = modifySpeed(curSetting, curSpeedType);
     float toSpeed = modifySpeed(curSetting, toSpeedType);
     return getRampForSpeedChange(fromSpeed, toSpeed)->getRampLength()
             + 12192 / WarrantPreferences::getDefault()->getLayoutScale();
 }

/**
 * Get the length of ramp for a speed change
 * @param fSpeed - starting speed
 * @param toSpeed - ending speed
 * @param isForward - direction
 * @return distance in millimeters
 */
/*protected*/ float SpeedUtil::rampLengthForSpeedChange(float fSpeed, float toSpeed, bool isForward) {
    float fromSpeed = fSpeed;
    float rampLength = 0.0f;
    float deltaTime = getRampTimeIncrement();
    float deltaThrottle = getRampThrottleIncrement();
    int numSteps = 0;
    bool increasing = (fromSpeed <= toSpeed);
    float momentumTime = getMomentumTime(deltaThrottle, increasing);

    if (increasing) {
        while (fromSpeed < toSpeed) {
            float dist = getTrackSpeed(fromSpeed + deltaThrottle/2) * momentumTime;
            if (deltaTime > momentumTime) {
                dist += getTrackSpeed(fromSpeed + deltaThrottle) * (deltaTime - momentumTime);
            }
            fromSpeed += deltaThrottle;
            if (fromSpeed <= toSpeed) {
                rampLength += dist;
            } else {
                rampLength += (fromSpeed - toSpeed) * dist / deltaThrottle;
            }
            deltaThrottle *= NXFrame::INCRE_RATE;
            numSteps++;
        }
    } else {
        // Start with largest throttle increment
        float tempSpeed = toSpeed;
        while (tempSpeed + deltaThrottle <= fromSpeed) {
            tempSpeed += deltaThrottle;
            deltaThrottle *= NXFrame::INCRE_RATE;
        }
        while (fromSpeed >= toSpeed) {
            float nextSpeed;
            if (fromSpeed < deltaThrottle) {
                nextSpeed = deltaThrottle - fromSpeed;
            } else {
                nextSpeed = fromSpeed - deltaThrottle;
            }
            float dist = getTrackSpeed((fromSpeed + nextSpeed)/2) * momentumTime;
            if (deltaTime > momentumTime) {
                dist += getTrackSpeed(nextSpeed) * (deltaTime - momentumTime);
            }
            if (dist <= 0.0f) {
                break;
            }
            fromSpeed -= deltaThrottle;
            if (fromSpeed > toSpeed) {
                rampLength += dist;
            } else {
                rampLength += (toSpeed - fromSpeed) * dist / deltaThrottle;
            }
            deltaThrottle /= NXFrame::INCRE_RATE;
            numSteps++;
        }
    }
    if (log->isDebugEnabled()) log->debug(tr("rampLengthForSpeedChange()= %1 in %2ms from speed= %3 to speed= %4").arg(
            rampLength).arg(deltaTime*numSteps).arg(fSpeed).arg(toSpeed));
    return rampLength;
}

/**
 * Get the length of ramp for a speed change
 * @param fromSpeed - starting speed setting
 * @param toSpeed - ending speed setting
 * @return distance in millimeters
 */
/*protected*/ RampData* SpeedUtil::getRampForSpeedChange(float fromSpeed, float toSpeed) {
    RampData* ramp = new RampData(getRampThrottleIncrement(), getRampTimeIncrement());
    ramp->makeThrottleSettings(fromSpeed, toSpeed);
    if (ramp->isUpRamp()) {
        makeUpRamp(ramp);
    } else {
        makeDownRamp(ramp);
    }

    if (log->isTraceEnabled()) log->debug(tr("rampLengthForSpeedChange()= %1 for fromSpeed= %2 toSpeed= %3").arg(
            ramp->getRampLength()).arg(fromSpeed).arg(toSpeed));
    return ramp;
}

/*private*/ void SpeedUtil::makeUpRamp(RampData* ramp) {
    float rampLength = 0.0f;
    float prevSetting = 0.0f;
    float nextSetting;
    QListIterator<float> iter = ramp->speedIterator(true);
    if (iter.hasNext()) {
        prevSetting = iter.next();
    }
    while (iter.hasNext()) {
        nextSetting = iter.next();
        rampLength += getDistanceOfSpeedChange(prevSetting, nextSetting, _rampTimeIncrement);
//            if (log.isDebugEnabled()) log.debug("makeUpRamp()= {} for fromSpeed= {} toSpeed= {} dist= {}",
//                    ramp.getRampLength(), prevSetting, nextSetting, getDistanceOfSpeedChange(prevSetting, nextSetting, _rampTimeIncrement));
        prevSetting = nextSetting;
    }
    ramp->setRampLength(rampLength);
}

/*private*/ void SpeedUtil::makeDownRamp(RampData* ramp) {
    float rampLength = 0.0f;
    float prevSetting = 0.0f;
    float nextSetting;
    QListIterator<float> iter = ramp->speedIterator(false);
    if (iter.hasPrevious()) {
        prevSetting = iter.previous();
    }
    while (iter.hasPrevious()) {
        nextSetting = iter.previous();
        rampLength += getDistanceOfSpeedChange(prevSetting, nextSetting, _rampTimeIncrement);
//            if (log.isDebugEnabled()) log.debug("makeDownRamp()= {} for fromSpeed= {} toSpeed= {} dist= {}",
//                    ramp.getRampLength(), prevSetting, nextSetting, getDistanceOfSpeedChange(prevSetting, nextSetting, _rampTimeIncrement));
        prevSetting = nextSetting;
    }
    ramp->setRampLength(rampLength);
}
/**
 * Return the distance traveled at current speed after a speed change was made.
 * Takes into account the momentum configured for the decoder to change from
 * the previous speed to the current speed.  Assumes the velocity change is linear.
 *
 * @param prevSpeed throttle setting when speed changed to currSpeed
 * @param currSpeed throttle setting being set
 * @param speedTime elapsed time from when the speed change was made to now
 * @return distance traveled
 */
/*protected*/ float SpeedUtil::getDistanceOfSpeedChange(float prevSpeed, float currSpeed, long speedTime) {
    bool increasing = (prevSpeed <= currSpeed);
    float momentumTime = getMomentumTime(currSpeed - prevSpeed, increasing);
    if (speedTime <=momentumTime ) {
        // most likely will be too far since currSpeed is not attained
        return getTrackSpeed((prevSpeed + currSpeed)/2) * speedTime;
    }
    // assume a linear change of speed
    float dist = getTrackSpeed((prevSpeed + currSpeed)/2) * momentumTime;
    if (speedTime > momentumTime) { // time remainder at changed speed
        dist += getTrackSpeed(currSpeed) * (speedTime - momentumTime);
    }
    return dist;
}

/*************** dynamic calibration ***********************/


/**
 * Just entered block at newIdx. Do that calculation of speed from lastIdx
 *  Dynamic measurement of speed profile is being studied further.  For now the
 *  only recorded speeds are those at constant speed.
 * @param lastIdx BlockOrder index of where data collection started
 * @param newIdx BlockOrder index of block just entered
 */
/*protected*/ void SpeedUtil::enteredBlock(int lastIdx, int newIdx) {
    speedChange();
    if (lastIdx > 0) {   // Distance traveled in 1st block unknown
        if (!log->isDebugEnabled() && _numchanges > 1) {
            return;
        }
        float totalLength = 0.0f;
        bool isForward = _throttle->getIsForward();
        bool mergeOK = true;
        // actual exit - entry times
        if (newIdx > 1) {
            for (int i=lastIdx; i<newIdx; i++) {
                BlockOrder* blkOrder = _orders->value(i);
                float length = blkOrder->getPath()->getLengthMm();
                if (length <= 0) {
                    log->warn(tr("Block %1 does not have a length for path %2").arg(
                            blkOrder->getBlock()->getDisplayName()).arg(blkOrder->getPathName()));
                    mergeOK = false;
                }
                totalLength += length;
            }
        }
        OBlock* fromBlock = _orders->value(newIdx)->getBlock();
        OBlock* toBlock = _orders->value(lastIdx)->getBlock();
        if (!mergeOK || (_numchanges > 1 && qAbs(_distanceTravelled - totalLength) < 25.0f)) {   // allow 1 inch
            clearStats();
            if (log->isDebugEnabled())
                log->debug(tr("Speed data invalid between %1 and %2 (bad length data)").arg(fromBlock->getDisplayName()).arg(toBlock->getDisplayName()));
            return;
        }
        long elpsedTime = fromBlock->_entryTime - toBlock->_entryTime;
        float speed;
        float throttle;
        float aveSpeed = totalLength / elpsedTime;
        if (_numchanges == 1) {
            throttle = _throttle->getSpeedSetting();
            speed = aveSpeed;
        } else {
            if (qAbs(elpsedTime - _timeAtSpeed) < 30) { // only allow 30ms
                clearStats();
                if (log->isDebugEnabled())
                    log->debug(tr("Speed data invalid between %1 and %2 (timing bad)").arg(fromBlock->getDisplayName()).arg(toBlock->getDisplayName()));
                return;
            }
            speed = totalLength / _timeAtSpeed;
            throttle = _settingsTravelled / _timeAtSpeed;
        }
        speed *= 1000;   // SpeedProfile is mm/sec

        float stepIncrement = _throttle->getSpeedIncrement();

        if (throttle < stepIncrement || speed <= 0.0f || qAbs(aveSpeed - speed) < 20) {
            clearStats();
            if (log->isDebugEnabled())
                log->debug(tr("Speeds invalid between %1 and %2").arg(fromBlock->getDisplayName()).arg(toBlock->getDisplayName()));
            return;
        }
        float mergeSpeed = _mergeProfile->getSpeed(throttle, isForward);
        float profileSpeed = _sessionProfile->getSpeed(throttle, isForward);
        throttle = stepIncrement * qRound(throttle/stepIncrement);
        if (log->isDebugEnabled()) {
            log->debug(tr("%1 changes on block %2. ave speed= %3mm/ms").arg(
                    _numchanges).arg(fromBlock->getDisplayName()).arg(aveSpeed));
            log->debug(tr("throttle= %1, speed= %2, profileSpeed=%3, mergeSpeed=%4").arg(
                    throttle).arg(speed).arg(profileSpeed).arg(mergeSpeed));
        }
        if (_numchanges == 1) {
            mergeSpeed = (mergeSpeed + speed) / 2;
            if (isForward) {
                _mergeProfile->setForwardSpeed(throttle, mergeSpeed);
                _sessionProfile->setForwardSpeed(throttle, speed);
            } else {
                _mergeProfile->setReverseSpeed(throttle, mergeSpeed);
                _sessionProfile->setReverseSpeed(throttle, speed);
            }
            if (log->isDebugEnabled()) log->debug(tr("Set ProfileSpeed throttle= %1, sessionSpeed= %2 mergeSpeed=%3").arg(throttle).arg(speed).arg(mergeSpeed));
        }
    }
    clearStats();
}
// if a speed has been recorded, average it. Otherwise write measuredSpeed
/*private*/ void SpeedUtil::setSpeed(RosterSpeedProfile* profile, float throttle, float measuredSpeed, bool isForward) {
    SpeedStep* ss = profile->getSpeedStep(throttle);
    float mergeSpeed;
    if (ss != nullptr) {
        if (isForward) {
            if (ss->getForwardSpeed() > 0.0f) {
                mergeSpeed = (ss->getForwardSpeed() + measuredSpeed) / 2;
            } else {
                mergeSpeed = measuredSpeed;
            }
        } else {
            if (ss->getReverseSpeed() > 0.0f) {
                mergeSpeed = (ss->getReverseSpeed() + measuredSpeed) / 2;
            } else {
                mergeSpeed = measuredSpeed;
            }
        }
    } else {
        mergeSpeed = measuredSpeed;
    }
    if (isForward) {
        profile->setForwardSpeed(throttle, mergeSpeed);
    } else {
        profile->setReverseSpeed(throttle, mergeSpeed);
    }
}

/*private*/ void SpeedUtil::clearStats() {
    _timeAtSpeed = 0;
    _changetime = QDateTime::currentMSecsSinceEpoch(); //System.currentTimeMillis();
    _distanceTravelled = 0.0f;
    _settingsTravelled = 0.0f;
    _numchanges = 0;
}

/*
 *
 */
/*protected*/ void SpeedUtil::speedChange() {
    _numchanges++;
    if (!log->isDebugEnabled() && _numchanges > 1) {
        return;
    }
    long time = QDateTime::currentMSecsSinceEpoch(); //System.currentTimeMillis();
    float throttleSetting = _throttle->getSpeedSetting();
    long elapsedTime = time - _changetime;
    if (throttleSetting > 0.0f) {
        _timeAtSpeed += elapsedTime;
        RosterSpeedProfile* speedProfile = getSpeedProfile();
        float speed = speedProfile->getSpeed(throttleSetting, _throttle->getIsForward());
        if (speed > 0.0f) {
            _distanceTravelled += elapsedTime * speed / 1000;
        }
        _settingsTravelled += throttleSetting * elapsedTime;
    }
    _changetime = time;
}

/*protected*/ float SpeedUtil::getDistanceTravelled() {
    return _distanceTravelled;
}
/*protected*/ void SpeedUtil::setDistanceTravelled(float dist) {
    clearStats();
    _distanceTravelled = dist;
}

/*private*/ /*final*/ /*static*/ Logger* SpeedUtil::log = LoggerFactory::getLogger("SpeedUtil");
