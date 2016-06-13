#include "abstractaudiolistener.h"
#include "exceptions.h"
#include <QDateTime>
#include "audiocommand.h"
#include "audiofactory.h"
#include "instancemanager.h"

//AbstractAudioListener::AbstractAudioListener(QObject *parent) :
//  AbstractListener(parent)
//{
//}
/**
 * Base implementation of the AudioListener class.
 * <P>
 * Specific implementations will extend this base class.
 * <P>
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28771 $
 */
// /*public*/ abstract class AbstractAudioListener extends AbstractAudio implements AudioListener {

    /**
     *
     */
//    /*private*/ static final long serialVersionUID = 7653942390344476939L;

//    /*private*/ static final AudioFactory activeAudioFactory = InstanceManager.audioManagerInstance().getActiveAudioFactory();

/**
 * Abstract constructor for new AudioListener with system name
 *
 * @param systemName AudioListener object system name (e.g. IAL)
 */
/*public*/ AbstractAudioListener::AbstractAudioListener(QString systemName, QObject *parent) :
  AudioListener(systemName, parent) {
    //super(systemName);
    common();
    this->setState(STATE_POSITIONED);
}

/**
 * Abstract constructor for new AudioListener with system name and user name
 *
 * @param systemName AudioListener object system name (e.g. IAL)
 * @param userName   AudioListener object user name
 */
/*public*/ AbstractAudioListener::AbstractAudioListener(QString systemName, QString userName, QObject *parent) :
  AudioListener(systemName, userName, parent)
{
 //super(systemName, userName);
 common();
    this->setState(STATE_POSITIONED);
}
void AbstractAudioListener::common()
{
 _position =  QVector3D(0.0, 0.0, 0.0);
 _currentPosition =  QVector3D(0.0, 0.0, 0.0);
 _velocity =  QVector3D(0.0, 0.0, 0.0);
 _orientationAt =  QVector3D(0.0, 1.0, 0.0);
 _orientationUp =  QVector3D(0.0, 0.0, 1.0);
 _currentOriAt =  QVector3D(0.0, 1.0, 0.0);
 _currentOriUp =  QVector3D(0.0, 0.0, 1.0);
 _gain = 1.0;
 _metersPerUnit = 1.0;
 _timeOfLastPositionCheck = 0;
 log = new Logger(tr("AbstractAudioListener"));
}

//@Override
/*public*/ QChar AbstractAudioListener::getSubType() {
    return LISTENER;
}

//@Override
/*public*/ void AbstractAudioListener::setPosition(QVector3D pos) {
    this->_position = pos;
    changePosition(pos);
    if (log->isDebugEnabled()) {
     log->debug("Set position of Listener " + this->getSystemName() + " to " + "x= "+ QString::number(pos.x())+ "y= "+ QString::number(pos.y())+ "z= "+ QString::number(pos.z()));
    }
}

//@Override
/*public*/ void AbstractAudioListener::setPosition(float x, float y, float z) {
    this->setPosition( QVector3D(x, y, z));
}

//@Override
/*public*/ void AbstractAudioListener::setPosition(float x, float y) {
    this->setPosition( QVector3D(x, y, 0.0));
}

//@Override
/*public*/ QVector3D AbstractAudioListener::getPosition() {
    return this->_position;
}

//@Override
/*public*/ QVector3D AbstractAudioListener::getCurrentPosition() {
    return this->_currentPosition;
}

//@Override
/*public*/ void AbstractAudioListener::setVelocity(QVector3D vel) {
    this->_velocity = vel;
    this->setState(vel.length() != 0 ? STATE_MOVING : STATE_POSITIONED);
    if (log->isDebugEnabled()) {
        log->debug("Set velocity of Listener " + this->getSystemName() + " to " + "x= "+ QString::number(vel.x())+ "y= "+ QString::number(vel.y())+ "z= "+ QString::number(vel.z()));
    }
}

//@Override
/*public*/ QVector3D AbstractAudioListener::getVelocity() {
    return this->_velocity;
}

/**
 * Method to calculate current position based on velocity
 */
/*protected*/ void AbstractAudioListener::calculateCurrentPosition()
{
 // Calculate how long it's been since we lasted checked position
 //long currentTime = System.currentTimeMillis();
 qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
 qint64 timePassed = (currentTime - this->_timeOfLastPositionCheck) / 1000;
 this->_timeOfLastPositionCheck = currentTime;

 if (this->_velocity.length() != 0)
 {
#if 0
  this->_currentPosition.scaleAdd(
                timePassed * this->_metersPerUnit,
                this->_velocity,
                this->_currentPosition);
  this->_currentOriAt.scaleAdd(
                timePassed * this->_metersPerUnit,
                this->_velocity,
                this->_currentOriAt);
  this->_currentOriUp.scaleAdd(
                timePassed * this->_metersPerUnit,
                this->_velocity,
                this->_currentOriUp);
#endif
 }
}
/*private*/ /*static*/ /*final*/ AudioFactory* AbstractAudioListener::activeAudioFactory = InstanceManager::audioManagerInstance()->getActiveAudioFactory();

//@Override
/*public*/ void AbstractAudioListener::resetCurrentPosition() {
    activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_RESET_POSITION));
    activeAudioFactory->getCommandThread()->exit();
}

/**
 * Method to reset the current position
 */
/*protected*/ void AbstractAudioListener::doResetCurrentPosition() {
    this->_currentPosition = this->_position;
}

/**
 * Method to change the current position of this source
 *
 * @param pos new position
 */
/*abstract*/ /*protected*/ void AbstractAudioListener::changePosition(QVector3D /*pos*/) {}

//@Override
/*public*/ void AbstractAudioListener::setOrientation(QVector3D at, QVector3D up) {
    this->_orientationAt = at;
    this->_orientationUp = up;
    if (log->isDebugEnabled()) {
        log->debug("Set orientation of Listener " + this->getSystemName() + " to (at) " + "x= "+ QString::number(at.x())+ "y= "+ QString::number(at.y())+ "z= "+ QString::number(at.z()) + " (up) " + "x= "+ QString::number(up.x())+ "y= "+ QString::number(up.y())+ "z= "+ QString::number(up.z()));
    }
}

//@Override
/*public*/ QVector3D AbstractAudioListener::getOrientation(int which) {
    QVector3D _orientation;// = null;
    switch (which) {
        case AT: {
            _orientation = this->_orientationAt;
            break;
        }
        case UP: {
            _orientation = this->_orientationUp;
            break;
        }
        default:
            throw new IllegalArgumentException();
    }
    return _orientation;
}

//@Override
/*public*/ QVector3D AbstractAudioListener::getCurrentOrientation(int which) {
    QVector3D _orientation;// = null;
    switch (which) {
        case AT: {
            _orientation = this->_currentOriAt;
            break;
        }
        case UP: {
            _orientation = this->_currentOriUp;
            break;
        }
        default:
            throw new IllegalArgumentException();
    }
    return _orientation;
}

//@Override
/*public*/ void AbstractAudioListener::setGain(float gain) {
    this->_gain = gain;
    if (log->isDebugEnabled()) {
        log->debug("Set gain of Listener " + this->getSystemName() + " to " + gain);
    }
}

//@Override
/*public*/ float AbstractAudioListener::getGain() {
    return this->_gain;
}

//@Override
/*public*/ void AbstractAudioListener::setMetersPerUnit(float metersPerUnit) {
    this->_metersPerUnit = metersPerUnit;
    if (log->isDebugEnabled()) {
        log->debug("Set Meters per unit of Listener " + this->getSystemName() + " to " + metersPerUnit);
    }
}

//@Override
/*public*/ float AbstractAudioListener::getMetersPerUnit() {
    return this->_metersPerUnit;
}

//@Override
/*public*/ void AbstractAudioListener::stateChanged(int oldState) {
    // Move along... nothing to see here...
}

//@Override
/*public*/ QString AbstractAudioListener::toString()
{
 QVector3D pos = this->getPosition();
    return QString("Pos: ") + " x="+ QString::number(pos.x())+ " y="+ QString::number(pos.y())+ " z="+ QString::number(pos.z())
            + ", gain=" + QString::number(this->getGain())
            + ", meters/unit=" + QString::number(this->getMetersPerUnit());
}

// /*private*/ static final Logger log = LoggerFactory.getLogger(AbstractAudioListener.class.getName());

/**
 * An internal class used to create a new thread to monitor and maintain
 * current listener position with respect to velocity.
 */
///*protected*/ static class AudioListenerMoveThread extends AbstractAudioThread {

    /**
     * Reference to the AudioListener object being monitored
     */
//    /*private*/ AbstractAudioListener audioListener;

    /**
     * Constructor that takes handle to AudioListener to monitor
     *
     * @param audioListener AudioListener to monitor
     */
AudioListenerMoveThread::AudioListenerMoveThread(AbstractAudioListener* audioListener, QObject* parent) : AbstractAudioThread(parent)
    {
     //super();
        log = new Logger("AudioListenerMoveThread");
        this->setObjectName("movelis-" + AbstractAudioThread::objectName());
        this->audioListener = audioListener;
        if (log->isDebugEnabled()) {
            log->debug("Created AudioListenerMoveThread for AudioListener " + audioListener->getSystemName());
        }
    }

    /**
     * Main processing loop
     */
    //@Override
    /*public*/ void AudioListenerMoveThread::run() {

        while (!dying()) {

            // Recalculate the position
            audioListener->calculateCurrentPosition();

            // Check state and die if not playing
            if (audioListener->getState() != Audio::STATE_MOVING) {
                die();
            }

            // sleep for a while so as not to overload CPU
            snooze(20);
        }

//            // Reset the current position
//            audioListener.resetCurrentPosition();
        // Finish up
        if (log->isDebugEnabled()) {
            log->debug("Clean up thread " + this->objectName());
        }
        cleanup();
    }

    /**
     * Shuts this thread down and clears references to created objects
     */
    //@Override
    /*protected*/ void AudioListenerMoveThread::cleanup() {
        // Thread is to shutdown
        die();

        // Clear references to objects
        this->audioListener = NULL;

        // Finalise cleanup in super-class
        AbstractAudioThread::cleanup();
    }
//};
