#include "rosterspeedprofile.h"
#include "dccthrottle.h"
#include "rosterentry.h"
#include "namedbean.h"
#include "block.h"
#include "section.h"
#include "logger.h"

//RosterSpeedProfile::RosterSpeedProfile(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * A simple class to store a speed profile for a given loco The speed steps
 * against the profile are on a scale of 0 to 1000, this equates to the float
 * speed x 1000. This allows a single profile to cover different throttle speed
 * step settings. So a profile generate for a loco using 28 steps can be used
 * for a throttle using 126 steps.
 *
 */
///*public*/ class RosterSpeedProfile {


/*public*/ RosterSpeedProfile::RosterSpeedProfile(RosterEntry* re, QObject *parent) :
  QObject(parent)
{
 overRunTimeReverse = 0.0;
 overRunTimeForward = 0.0;
 speeds =  QMap<int, SpeedStep*>();
 desiredSpeedStep = -1;
 extraDelay = 0.0;
 referenced = NULL;
 stopTimer = NULL;
 lastTimeTimerStarted = new QElapsedTimer;
 increaseSpeed = false;
 log = new Logger("RosterSpeedProfile");
 extraTime = 0;
 stepQueue = QLinkedList<SpeedSetting*>();


 _re = re;
}

/*public*/ RosterEntry* RosterSpeedProfile::getRosterEntry() {
    return _re;
}

/*public*/ float RosterSpeedProfile::getOverRunTimeForward() {
    return overRunTimeForward;
}

/*public*/ void RosterSpeedProfile::setOverRunTimeForward(float dt) {
    overRunTimeForward = dt;
}

/*public*/ float RosterSpeedProfile::getOverRunTimeReverse() {
    return overRunTimeReverse;
}

/*public*/ void RosterSpeedProfile::setOverRunTimeReverse(float dt) {
    overRunTimeReverse = dt;
}

/*public*/ void RosterSpeedProfile::clearCurrentProfile() {
    speeds =  QMap<int, SpeedStep*>();
}

/**
 * forward and reverse values are in meters per second
 */
/*public*/ void RosterSpeedProfile::setSpeed(int speedStep, float forward, float reverse) {
    //int iSpeedStep = qRound(speedStep*1000);
    if (!speeds.contains(speedStep)) {
        speeds.insert(speedStep, new SpeedStep());
    }
    SpeedStep* ss = speeds.value(speedStep);
    ss->setForwardSpeed(forward);
    ss->setReverseSpeed(reverse);
}

/*public*/ void RosterSpeedProfile::setForwardSpeed(float speedStep, float forward) {
    int iSpeedStep = qRound(speedStep * 1000);
    if (!speeds.contains(iSpeedStep)) {
        speeds.insert(iSpeedStep, new SpeedStep());
    }
    SpeedStep* ss = speeds.value(iSpeedStep);
    ss->setForwardSpeed(forward);
}

/*public*/ void RosterSpeedProfile::setReverseSpeed(float speedStep, float reverse) {
    int iSpeedStep = qRound(speedStep * 1000);
    if (!speeds.contains(iSpeedStep)) {
        speeds.insert(iSpeedStep, new SpeedStep());
    }
    SpeedStep* ss = speeds.value(iSpeedStep);
    ss->setReverseSpeed(reverse);
}

/**
 * return the forward speed in milli-meters per second for a given speed
 * step
 */
/*public*/ float RosterSpeedProfile::getForwardSpeed(float speedStep) {
    int iSpeedStep = qRound(speedStep * 1000);
    if (speeds.contains(iSpeedStep)) {
        return speeds.value(iSpeedStep)->getForwardSpeed();
    }
    log->debug("no exact match forward for " + iSpeedStep);
    float lower = 0;
    float higher = 0;
    int highStep = 0;
    int lowStep = 0;
    if (/*speeds.*/higherKey(iSpeedStep) != NULL) {
        highStep = /*speeds.*/higherKey(iSpeedStep);
        higher = speeds.value(highStep)->getForwardSpeed();
    } else {
        return -1.0f;
    }
    if (/*speeds.*/lowerKey(iSpeedStep) != NULL) {
        lowStep = /*speeds.*/lowerKey(iSpeedStep);
        lower = speeds.value(lowStep)->getForwardSpeed();
    }

    float valperstep = (higher - lower) / (highStep - lowStep);

    float retValue = lower + (valperstep * (iSpeedStep - lowStep));
    return retValue;
}
int RosterSpeedProfile::higherKey(int key)
{
 QVector<int> kv = speeds.keys().toVector();
 for(int i = 0; i < kv.size(); i++)
 {
  if(kv.at(i) > key)
   return kv.at(i);
 }
 return 0;
}
int RosterSpeedProfile::lowerKey(int key)
{
 QVector<int> kv = speeds.keys().toVector();
 for(int i = kv.size()-1; i >=0; i--)
 {
  if(kv.at(i) < key)
   return kv.at(i);
 }
 return 0;
}

/**
 * return the reverse speed in milli-meters per second for a given speed
 * step
 */
/*public*/ float RosterSpeedProfile::getReverseSpeed(float speedStep) {
    int iSpeedStep = qRound(speedStep * 1000);
    if (speeds.contains(iSpeedStep)) {
        return speeds.value(iSpeedStep)->getReverseSpeed();
    }
    log->debug("no exact match reverse for " + iSpeedStep);
    float lower = 0;
    float higher = 0;
    int highStep = 0;
    int lowStep = 0;
    if (/*speeds.*/higherKey(iSpeedStep) != NULL) {
        highStep = /*speeds.*/higherKey(iSpeedStep);
        higher = speeds.value(highStep)->getForwardSpeed();
    } else {
        return -1.0f;
    }
    if (/*speeds.*/lowerKey(iSpeedStep) != NULL) {
        lowStep = /*speeds.*/lowerKey(iSpeedStep);
        lower = speeds.value(lowStep)->getForwardSpeed();
    }

    float valperstep = (higher - lower) / (highStep - lowStep);

    float retValue = lower + (valperstep * (iSpeedStep - lowStep));
    return retValue;
}

/**
 * return the approximate duration in seconds that a loco may travel for a
 * given speed step
 */
/*public*/ float RosterSpeedProfile::getDurationOfTravelInSeconds(bool isForward, float speedStep, int distance) {
    float spd = 0.0;
    if (isForward) {
        spd = getForwardSpeed(speedStep);
    } else {
        spd = getReverseSpeed(speedStep);
    }
    return (distance / spd);
}

/**
 * return the approximate distance travelled in millimeters for a give
 * duration in seconds and speed step.
 */
/*public*/ float RosterSpeedProfile::getDistanceTravelled(bool isForward, float speedStep, float duration) {
    float spd = 0.0;
    if (isForward) {
        spd = getForwardSpeed(speedStep);
    } else {
        spd = getReverseSpeed(speedStep);
    }
    return qAbs(spd * duration);
}


/**
 * reset everything back to default once the change has finished.
 */
void RosterSpeedProfile::finishChange()
{
 if (stopTimer != NULL)
 {
  stopTimer->stop();
 }
 stopTimer = NULL;
 _throttle = NULL;
 distanceRemaining = 0;
 desiredSpeedStep = -1;
 extraDelay = 0.0f;
 referenced = NULL;
 /*synchronized (this)*/ {
     distanceTravelled = 0;
     stepQueue = QLinkedList<SpeedSetting*>();
 }
}

/*public*/ void RosterSpeedProfile::setExtraInitialDelay(float eDelay) {
    extraDelay = eDelay;
}

/**
 * Set speed of a throttle to a speeed set by a float, using the block for
 * the length details
 */
/*public*/ void RosterSpeedProfile::changeLocoSpeed(DccThrottle* t, Block* blk, float speed) {
    if (blk == referenced && speed == desiredSpeedStep) {
        //if(log->isDebugEnabled()) log->debug("Already setting to desired speed step for this block");
        return;
    }
    float blockLength = blk->getLengthMm();
    if (blk == referenced) {
        distanceRemaining = distanceRemaining - getDistanceTravelled(_throttle->getIsForward(), _throttle->getSpeedSetting(), ((float) (/*System.nanoTime() -*/ lastTimeTimerStarted->nsecsElapsed()) / 1000000000));
        blockLength = distanceRemaining;
        //Not entirely reliable at this stage as the loco could still be running and not completed the calculation of the distance, this could result in an over run
        log->debug("Block passed is the same as we are currently processing");
    } else {
        referenced = blk;
    }
    changeLocoSpeed(t, blockLength, speed);

}

/**
 * Set speed of a throttle to a speeed set by a float, using the section for
 * the length details
 */
//@TODO if a section contains multiple blocks then we could calibrate the change of speed based upon the block status change.
/*public*/ void RosterSpeedProfile::changeLocoSpeed(DccThrottle* t, Section* sec, float speed) {
    if (sec == referenced && speed == desiredSpeedStep) {
        if (log->isDebugEnabled()) {
            log->debug("Already setting to desired speed step for this section");
        }
        return;
    }
    float sectionLength = sec->getActualLength();
    if (log->isDebugEnabled()) {
        log->debug("call to change speed via section " + sec->getDisplayName());
    }
    if (sec == referenced) {
        distanceRemaining = distanceRemaining - getDistanceTravelled(_throttle->getIsForward(), _throttle->getSpeedSetting(), ((float) (/*System.nanoTime() -*/ lastTimeTimerStarted->nsecsElapsed()) / 1000000000));
        sectionLength = distanceRemaining;
    } else {
        referenced = sec;
    }

    changeLocoSpeed(t, sectionLength, speed);
}

/**
 * Set speed by float increment of a speed step.
 */
/*public*/ void RosterSpeedProfile::changeLocoSpeed(DccThrottle* t, float distance, float speed) {
    if (log->isDebugEnabled()) {
        log->debug("Call to change speed over specific distance float " + QString::number(speed) + " distance " + QString::number(distance));
    }
    if (speed == t->getSpeedSetting()) {
        if (log->isDebugEnabled()) {
            log->debug("Throttle and request speed setting are the same " + QString::number(speed) + " " + QString::number(t->getSpeedSetting()) + " so will quit");
        }
        //Already at correct speed setting
        finishChange();
        return;
    }

    if (desiredSpeedStep == speed) {
        if (log->isDebugEnabled()) {
            log->debug("Already setting to desired speed step");
        }
        return;
    }
    if (log->isDebugEnabled()) {
        log->debug("/*public*/ change speed step by float " + QString::number(speed));
    }
    if (log->isDebugEnabled()) {
        log->debug("Desired Speed Step " + QString::number(desiredSpeedStep) + " asked for " + QString::number(speed));
    }

    if (stopTimer != NULL) {
        if (log->isDebugEnabled()) {
            log->debug("stop timer valid so will cancel");
        }
        cancelSpeedChange();
    }
    _throttle = t;

    if (log->isDebugEnabled()) {
        log->debug("Desired Speed Step " + QString::number(desiredSpeedStep) + " asked for " + QString::number(speed));
    }
    desiredSpeedStep = speed;

    if (log->isDebugEnabled()) {
        log->debug("calculated current step " + QString::number(_throttle->getSpeedSetting()) + " required " + QString::number(speed) + " current " + QString::number(_throttle->getSpeedSetting()));
    }
    if (_throttle->getSpeedSetting() < speed) {
        increaseSpeed = true;
        if (log->isDebugEnabled()) {
            log->debug("Going for acceleration");
        }
    } else {
        increaseSpeed = false;
        if (log->isDebugEnabled()) {
            log->debug("Going for deceleration");
        }
    }

    calculateStepDetails(speed, distance);
}


void RosterSpeedProfile::calculateStepDetails(float speedStep, float distance) {

    float stepIncrement = _throttle->getSpeedIncrement();
    if (log->isDebugEnabled()) {
        log->debug("Desired Speed Step " + QString::number(desiredSpeedStep) + " asked for " + speedStep);
    }
    desiredSpeedStep = speedStep;
    //int step = qRound(_throttle->getSpeedSetting()*1000);
    if (log->isDebugEnabled()) {
        log->debug("calculated current step " + QString::number(_throttle->getSpeedSetting()) + " required " + QString::number(speedStep) + " current " + QString::number(_throttle->getSpeedSetting()) + " increment " + QString::number(stepIncrement));
    }
    bool increaseSpeed = false;
    if (_throttle->getSpeedSetting() < speedStep) {
        increaseSpeed = true;
        if (log->isDebugEnabled()) {
            log->debug("Going for acceleration");
        }
    } else {
        if (log->isDebugEnabled()) {
            log->debug("Going for deceleration");
        }
    }

    if (distance <= 0) {
        if (log->isDebugEnabled()) {
            log->debug("Distance is less than 0 " + QString::number(distance));
        }
        _throttle->setSpeedSetting(speedStep);
        finishChange();
        return;
    }

    float calculatedDistance = distance;

    if (stopTimer != NULL) {
        stopTimer->stop();
        distanceRemaining = distance;
    } else {
        calculatedDistance = calculateInitialOverRun(distance);
        distanceRemaining = calculatedDistance;
    }

    float calculatingStep = _throttle->getSpeedSetting();

    float endspd = 0;
    if (calculatingStep != 0.0 && desiredSpeedStep > 0) { // current speed
        if (_throttle->getIsForward()) {
            endspd = getForwardSpeed(desiredSpeedStep);
        } else {
            endspd = getReverseSpeed(desiredSpeedStep);
        }
    } else if (desiredSpeedStep != 0.0) {
        if (_throttle->getIsForward()) {
            endspd = getForwardSpeed(desiredSpeedStep);
        } else {
            endspd = getReverseSpeed(desiredSpeedStep);
        }
    }

    bool calculated = false;

    while (!calculated) {
        float spd = 0;
        if (calculatingStep != 0.0) { // current speed
            if (_throttle->getIsForward()) {
                spd = getForwardSpeed(calculatingStep);
            } else {
                spd = getReverseSpeed(calculatingStep);
            }
        }

        if (log->isDebugEnabled()) {
            log->debug("end spd " + QString::number(endspd) + " spd " + QString::number(spd));
        }
        double avgSpeed = qAbs((endspd + spd) * 0.5);
        if (log->isDebugEnabled()) {
            log->debug("avg Speed " + QString::number(avgSpeed));
        }

        double time = (calculatedDistance / avgSpeed); //in seconds
        time = time * 1000; //covert it to milli seconds
        /*if(stopTimer==NULL){
         if(log->isDebugEnabled()) log->debug("time before remove over run " + time);
         time = calculateInitialOverRun(time);//At the start we will deduct the over run time if configured
         if(log->isDebugEnabled()) log->debug("time after remove over run " + time);
         }*/
        float speeddiff = calculatingStep - desiredSpeedStep;
        float noSteps = speeddiff / stepIncrement;
        if (log->isDebugEnabled()) {
            log->debug("Speed diff " + QString::number(speeddiff) + " number of Steps " + QString::number(noSteps) + " step increment " + QString::number(stepIncrement));
        }

        int timePerStep = qAbs((int) (time / noSteps));
        float calculatedStepInc = stepIncrement;
        if (calculatingStep > (stepIncrement * 2)) {
            //We do not get reliable time results if the duration per speed step is less than 500ms
            //therefore we calculate how many speed steps will fit in to 750ms.
            if (timePerStep <= 500 && timePerStep > 0) {
                //thing tIncrement should be different not sure about this bit
                float tmp = (750.0f / timePerStep);
                calculatedStepInc = stepIncrement * tmp;
                if (log->isDebugEnabled()) {
                    log->debug("time per step was " + QString::number(timePerStep) + " no of increments in 750 ms is " + QString::number(tmp) + " new step increment in " + QString::number(calculatedStepInc));
                }

                timePerStep = 750;
            }
        }
        if (log->isDebugEnabled()) {
            log->debug("per interval " + timePerStep);
        }

        //Calculate the new speed setting
        if (increaseSpeed) {
            calculatingStep = calculatingStep + calculatedStepInc;
            if (calculatingStep > 1.0f) {
                calculatingStep = 1.0f;
                calculated = true;
            }
            if (calculatingStep > desiredSpeedStep) {
                calculatingStep = desiredSpeedStep;
                calculated = true;
            }
        } else {
            calculatingStep = calculatingStep - calculatedStepInc;
            if (calculatingStep < _throttle->getSpeedIncrement()) {
                calculatingStep = 0.0f;
                calculated = true;
                timePerStep = 0;
            }
            if (calculatingStep < desiredSpeedStep) {
                calculatingStep = desiredSpeedStep;
                calculated = true;
            }
        }
        if (log->isDebugEnabled()) {
            log->debug("Speed Step current " + QString::number(_throttle->getSpeedSetting()) + " speed to set " + QString::number(calculatingStep));
        }

        SpeedSetting* ss = new SpeedSetting(calculatingStep, timePerStep);
        /*synchronized (this)*/ {
            stepQueue.append(ss);
        }
        if (stopTimer == NULL) { //If this is the first time round then kick off the speed change
            setNextStep();
        }

        calculatedDistance = calculatedDistance - getDistanceTravelled(_throttle->getIsForward(), calculatingStep, ((float) (timePerStep / 1000.0)));

        if (calculatedDistance < 0 && !calculated) {
            log->error("distance remaining is now 0, but we have not reached desired speed setting " + QString::number(desiredSpeedStep) + " v " + QString::number(calculatingStep));
            ss = new SpeedSetting(desiredSpeedStep, 10);
            /*synchronized (this)*/ {
                stepQueue.append(ss);
            }
            calculated = true;
        }
    }
}

//The bit with the distance is not used
float RosterSpeedProfile::calculateInitialOverRun(float distance) {
    if (log->isDebugEnabled()) {
        log->debug("Stop timer not configured so will add overrun " + QString::number(distance));
    }
    if (_throttle->getIsForward()) {
        float extraAsDouble = (getOverRunTimeForward() + extraDelay) / 1000;
        if (log->isDebugEnabled()) {
         log->debug(tr("Over run time to remove (Forward) %1").arg(getOverRunTimeForward()));
         log->debug(QString("%1").arg(extraAsDouble));
        }
        float olddistance = getDistanceTravelled(true, _throttle->getSpeedSetting(), extraAsDouble);
        distance = distance - olddistance;
        //time = time-getOverRunTimeForward();
        //time = time-(extraAsDouble*1000);
    } else {
        float extraAsDouble = (getOverRunTimeReverse() + extraDelay) / 1000;
        if (log->isDebugEnabled()) {
            log->debug(tr("Over run time to remove (Reverse) %1").arg(getOverRunTimeReverse()));
            log->debug(QString("%1").arg(extraAsDouble));
        }
        float olddistance = getDistanceTravelled(false, _throttle->getSpeedSetting(), extraAsDouble);
        distance = distance - olddistance;
        //time = time-getOverRunTimeReverse();
        //time = time-(extraAsDouble*1000);
    }
    if (log->isDebugEnabled()) {
        log->debug("Distance remaining " + QString::number(distance));
        //log->debug("Time after overrun removed " + time);
    }
    return distance;

}

void RosterSpeedProfile::stopLocoTimeOut(DccThrottle* t) {
    log->debug("Stopping loco");
    t->setSpeedSetting(0.0);
}

/**
 * This method is called to cancel the existing change in speed.
 */
/*public*/ void RosterSpeedProfile::cancelSpeedChange() {
    if (stopTimer != NULL && stopTimer->isActive()) {
        stopTimer->stop();
    }
    finishChange();
}

/*synchronized*/ void RosterSpeedProfile::setNextStep() {
    if (stepQueue.isEmpty()) {
        log->debug("No more results");
        finishChange();
        return;
    }
    SpeedSetting* ss = stepQueue.first();
    if (ss->getDuration() == 0) {
        _throttle->setSpeedSetting(0);
        finishChange();
        return;
    }
    if (stopTimer != NULL) {
        //Reduce the distanceRemaining and calculate the distance travelling
        float distanceTravelledThisStep = getDistanceTravelled(_throttle->getIsForward(), _throttle->getSpeedSetting(), ((float) (stopTimer->interval() / 1000.0)));
        distanceTravelled = distanceTravelled + distanceTravelledThisStep;
        distanceRemaining = distanceRemaining - distanceTravelledThisStep;
    }
    stepQueue.removeFirst();
    _throttle->setSpeedSetting(ss->getSpeedStep());
    stopTimer = new QTimer;//(ss->getDuration(), new java.awt.event.ActionListener() {
    stopTimer->setInterval(ss->getDuration());
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            setNextStep();
//        }
//    });
    connect(stopTimer, SIGNAL(timeout()), this, SLOT(setNextStep()));
    stopTimer->setSingleShot(true);
    lastTimeTimerStarted->start(); /*= System.nanoTime();*/
    stopTimer->start();

}

#if 0
static class SpeedSetting {

    float step = 0.0f;
    int duration = 0;

    SpeedSetting(float step, int duration) {
        this.step = step;
        this.duration = duration;
    }

    float getSpeedStep() {
        return step;
    }

    int getDuration() {
        return duration;
    }
}
#endif
/*
 * The follow deals with the storage and loading of the speed profile for a roster entry.
 */
/*public*/ void RosterSpeedProfile::store(QDomElement e)
{
 QDomDocument doc = e.ownerDocument(); // not sure about this. ACK
 QDomElement d  = doc.createElement("speedprofile");
 d.appendChild(doc.createElement("overRunTimeForward").appendChild(doc.createTextNode(QString::number(getOverRunTimeForward()))));
 d.appendChild(doc.createElement("overRunTimeReverse").appendChild(doc.createTextNode(QString::number(getOverRunTimeReverse()))));
 QDomElement s = doc.createElement("speeds");
 foreach (int i, speeds.keys())
 {
  QDomElement ss = doc.createElement("speed");
  ss.appendChild(doc.createElement("step").appendChild(doc.createTextNode(QString::number(i))));
  ss.appendChild(doc.createElement("forward").appendChild(doc.createTextNode(QString::number(speeds.value(i)->getForwardSpeed()))));
  ss.appendChild(doc.createElement("reverse").appendChild(doc.createTextNode(QString::number(speeds.value(i)->getReverseSpeed()))));
  s.appendChild(ss);
 }
 d.appendChild(s);
 e.appendChild(d);
}

//@SuppressWarnings({"unchecked"})
/*public*/ void RosterSpeedProfile::load(QDomElement e)
{
 try
 {
  setOverRunTimeForward(e.firstChildElement("overRunTimeForward").text().toFloat());
 }
 catch (Exception ex)
 {
  log->error("Over run Error For " + _re->getId());
 }
 try
 {
  setOverRunTimeReverse(e.firstChildElement("overRunTimeReverse").text().toFloat());
 }
 catch (Exception ex)
 {
  log->error("Over Run Error Rev " + _re->getId());
 }
 QDomElement speeds = e.firstChildElement("speeds");
 QDomNodeList speedlist = speeds.elementsByTagName("speed");
 for(int i=0; i < speedlist.size(); i++)
 {
  QDomElement spd = speedlist.at(i).toElement();
  try
  {
   QString step = spd.firstChildElement("step").text();
   QString forward = spd.firstChildElement("forward").text();
   QString reverse = spd.firstChildElement("reverse").text();
   setSpeed(step.toInt(), forward.toFloat(), reverse.toFloat());
  } catch (Exception ex)
  {
   log->error("Not loaded");
  }
 }
}



/* If there are too few SpeedSteps to get reasonable distances and speeds
 * over a good range of throttle settings, compute a factor that averages
 * a ratio for what whatever SpeedSteps exist.
 */
/*public*/ int RosterSpeedProfile::getProfileSize() {
    return speeds.size();
}
/**
 * @return an average ratio of forward speed to throttle setting
 */
/*public*/ float RosterSpeedProfile::getForwardFactor()
{
 float factor = 0.0;
 int count = 0;
 //Iterator<Map.Entry<Integer, SpeedStep>> it = speeds.entrySet().iterator();
 QMapIterator<int, SpeedStep*> it(speeds);
 while (it.hasNext())
 {
     //Map.Entry<Integer, SpeedStep> entry = it.next();
  it.next();
  float fac = it.value()->getForwardSpeed()/it.key();
  if (fac > 0.0)
  {
   factor += fac;
   count++;
  }
 }
 if (count>0)
 {
  return factor/count;
 }
 return factor;
}
/**
 * @return an average ratio of reverse speed to throttle setting
 */
/*public*/ float RosterSpeedProfile::getReverseFactor() {
    float factor = 0.0f;
    int count = 0;
//    Iterator<Map.Entry<Integer, SpeedStep>> it = speeds.entrySet().iterator();
    QMapIterator<int, SpeedStep*> it(speeds);
    while (it.hasNext()) {
//        Map.Entry<Integer, SpeedStep> entry = it.next();
     it.next();
        float fac = it.value()->getReverseSpeed()/it.key();
        if (fac > 0.0f) {
            factor += fac;
            count++;
        }
    }
    if (count>0) {
        return factor/count;
    }
    return factor;
}
/*public*/ float RosterSpeedProfile::getSpeed(float speedStep, bool isForward) {
        float speed;
        if (isForward) {
            speed = getForwardSpeed(speedStep);
        } else {
            speed = getReverseSpeed(speedStep);
        }
        if (speed<=0) {
            if (isForward) {
                speed = getReverseSpeed(speedStep);
            } else {
                speed = getForwardSpeed(speedStep);
            }
        }
        return speed;
    }
