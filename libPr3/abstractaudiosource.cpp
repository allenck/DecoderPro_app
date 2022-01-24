#include "abstractaudiosource.h"
#include "audiofactory.h"
#include "instancemanager.h"
#include "audiolistener.h"

//AbstractAudioSource::AbstractAudioSource(QObject *parent) :
//  AudioSource(parent)
//{
//}
/**
 * Base implementation of the AudioSource class.
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
///*public*/ abstract class AbstractAudioSource extends AbstractAudio implements AudioSource {

    /**
     *
     */
///*private*/ /*static*/ final long serialVersionUID = -984900360787361666L;

/*private*/ /*static*/ /*final*/ AudioFactory* AbstractAudioSource::activeAudioFactory = nullptr;//((AudioManager*) InstanceManager::getDefault("AudioManager"))->getActiveAudioFactory();

/*private*/ /*static*/ float AbstractAudioSource::metersPerUnit = 1; //AbstractAudioSource::activeAudioFactory->getActiveAudioListener()->getMetersPerUnit();

/**
 * Abstract constructor for new AudioSource with system name
 *
 * @param systemName AudioSource object system name (e.g. IAS1)
 */
/*public*/ AbstractAudioSource::AbstractAudioSource(QString systemName, QObject *parent) :
   AudioSource(systemName, parent) {
    //super(systemName);
 common();
}

/**
 * Abstract constructor for new AudioSource with system name and user name
 *
 * @param systemName AudioSource object system name (e.g. IAS1)
 * @param userName   AudioSource object user name
 */
/*public*/ AbstractAudioSource::AbstractAudioSource(QString systemName, QString userName, QObject *parent) :
  AudioSource(systemName, userName, parent)
{
 //super(systemName, userName);
 common();
}

void AbstractAudioSource::common()
{
 _position =  QVector3D(0.0, 0.0, 0.0);
 _currentPosition =  QVector3D(0.0, 0.0, 0.0);
 _velocity =  QVector3D(0.0, 0.0, 0.0);
 _gain = 1.0;
 _pitch = 1.0;
 _referenceDistance = 1.0;
_maximumDistance = Audio::MAX_DISTANCE;
_rollOffFactor = 1.0;
 _minLoops = LOOP_NONE;
 _maxLoops = LOOP_NONE;
 _numLoops = 0;
 _fadeInTime = 1000;
 _fadeOutTime = 1000;
 _fadeGain = 1.0;
 _dopplerFactor = 1.0;
 _timeOfLastFadeCheck = 0;
 _timeOfLastPositionCheck = 0;
 _fading = Audio::FADE_NONE;
 _bound = false;
 _positionRelative = false;
 _queued = false;
 pendingBufferQueue =  QQueue<AudioBuffer*>();
 _buffer = NULL;
 log = new Logger("AbstractAudioSource");
 if(activeAudioFactory == nullptr)
  activeAudioFactory = ((AudioManager*) InstanceManager::getDefault("AudioManager"))->getActiveAudioFactory();
}

//@Override
/*public*/ QChar AbstractAudioSource::getSubType() {
    return SOURCE;
}

//@Override
/*public*/ bool AbstractAudioSource::queueBuffers(QQueue<AudioBuffer*> audioBuffers)
 {

 // Note: Cannot queue buffers to a Source that has a bound buffer.
 if (!_bound)
 {
  this->pendingBufferQueue =  QQueue<AudioBuffer*>(audioBuffers);
  activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_QUEUE_BUFFERS));
  activeAudioFactory->getCommandThread()->exit();
  if (log->isDebugEnabled())
  {
   log->debug("Queued Buffer " + audioBuffers.head()->getSystemName() + " to Source " + this->getSystemName());
  }
  return (true);
 }
 else
 {
  log->error("Attempted to queue buffers " + audioBuffers.head()->getSystemName() + " (etc) to Bound Source " + this->getSystemName());
  return (false);
 }
}

//@Override
/*public*/ bool AbstractAudioSource::queueBuffer(AudioBuffer* audioBuffer)
 {
 if (!_bound)
 {
  //this->pendingBufferQueue.clear();
  this->pendingBufferQueue.append(audioBuffer);
  activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_QUEUE_BUFFERS));
  activeAudioFactory->getCommandThread()->exit();
  if (log->isDebugEnabled())
  {
   log->debug("Queued Buffer " + audioBuffer->getSystemName() + " to Source " + this->getSystemName());
  }
  return (true);
 }
 else
 {
  log->error("Attempted to queue buffer " + audioBuffer->getSystemName() + " to Bound Source " + this->getSystemName());
     return (false);
 }
}

//@Override
/*public*/ bool AbstractAudioSource::unqueueBuffers()
 {
  if (_bound)
  {
   log->error("Attempted to unqueue buffers on Bound Source " + this->getSystemName());
   return (false);
  }
  else if (_queued)
  {
   activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_UNQUEUE_BUFFERS));
   activeAudioFactory->getCommandThread()->exit();
   if (log->isDebugEnabled()) {
       log->debug("Unqueued Processed Buffers on Source " + this->getSystemName());
   }
   return (true);
  }
  else
  {
   log->debug("Source neither queued nor bound. Not an error. " + this->getSystemName());
   return (false);
  }
}

/*public*/ QQueue<AudioBuffer*> AbstractAudioSource::getQueuedBuffers()
{
 return (this->pendingBufferQueue);
}

//@Override
/*public*/ void AbstractAudioSource::setAssignedBuffer(AudioBuffer* audioBuffer)
 {
  if (!_queued)
  {
   this->_buffer = audioBuffer;
   // Ensure that the source is stopped
   this->stop(false);
   activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_BIND_BUFFER));
   activeAudioFactory->getCommandThread()->exit();
   if (log->isDebugEnabled())
   {
    log->debug("Assigned Buffer " + audioBuffer->getSystemName() + " to Source " + this->getSystemName());
   }
  }
  else
  {
     log->error("Attempted to assign buffer " + audioBuffer->getSystemName() + " to Queued Source " + this->getSystemName());
 }
}

//@Override
/*public*/ void AbstractAudioSource::setAssignedBuffer(QString bufferSystemName)
{
 if (!_queued)
 {
  AudioManager* am = (AudioManager*)InstanceManager::getDefault("AudioManager");
  Audio* a = am->getBySystemName(bufferSystemName);
  if (a->getSubType() == Audio::BUFFER)
  {
   setAssignedBuffer((AudioBuffer*) a);
  }
  else
  {
   log->warn("Attempt to assign incorrect object type to buffer - AudioBuffer expected.");
   this->_buffer = NULL;
   this->_bound = false;
  }
 }
 else
 {
  log->error("Attempted to assign buffer " + bufferSystemName + " to Queued Source " + this->getSystemName());
 }
}

//@Override
/*public*/ AudioBuffer* AbstractAudioSource::getAssignedBuffer() {
    return this->_buffer;
}

//@Override
/*public*/ QString AbstractAudioSource::getAssignedBufferName() {
    return (_buffer != NULL) ? _buffer->getSystemName() : "[none]";
}

//@Override
/*public*/ void AbstractAudioSource::setPosition(QVector3D pos)
{
 this->_position = pos;
 this->_currentPosition = pos;
 changePosition(pos);
 if (log->isDebugEnabled()) {
     log->debug("Set position of Source " + this->getSystemName() + " to " + "x= "+ QString::number(pos.x())+ "y= "+ QString::number(pos.y())+ "z= "+ QString::number(pos.z()));
 }
}

//@Override
/*public*/ void AbstractAudioSource::setPosition(float x, float y, float z)
{
 this->setPosition( QVector3D(x, y, z));
}

//@Override
/*public*/ void AbstractAudioSource::setPosition(float x, float y)
{
 this->setPosition( QVector3D(x, y, 0.0));
}

//@Override
/*public*/ QVector3D AbstractAudioSource::getPosition() {
    return this->_position;
}

//@Override
/*public*/ QVector3D AbstractAudioSource::getCurrentPosition() {
    return this->_currentPosition;
}

//@Override
/*public*/ void AbstractAudioSource::setPositionRelative(bool relative) {
    this->_positionRelative = relative;
}

//@Override
/*public*/ bool AbstractAudioSource::isPositionRelative() {
    return this->_positionRelative;
}

//@Override
/*public*/ void AbstractAudioSource::setVelocity(QVector3D vel) {
    this->_velocity = vel;
    if (log->isDebugEnabled()) {
        log->debug("Set velocity of Source " + this->getSystemName() + " to " + "x= "+ QString::number(vel.x())+ "y= "+ QString::number(vel.y())+ "z= "+ QString::number(vel.z()));
    }
}

//@Override
/*public*/ QVector3D AbstractAudioSource::getVelocity() {
    return this->_velocity;
}

/**
 * Method to calculate current position based on velocity
 */
/*protected*/ void AbstractAudioSource::calculateCurrentPosition() {

    // Calculate how long it's been since we lasted checked position
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    float timePassed = (currentTime - this->_timeOfLastPositionCheck);
    this->_timeOfLastPositionCheck = currentTime;

    log->debug("timePassed = " + QString::number(timePassed)
            + " metersPerUnit = " + QString::number(metersPerUnit)
            + " source = " + this->getSystemName()
            + " state = " + QString::number(this->getState()));
    if (this->_velocity.length() != 0)
    {
#if 0
        this->_currentPosition.scaleAdd(
                (timePassed / 1000) * metersPerUnit,
                this->_velocity,
                this->_currentPosition);
        changePosition(this->_currentPosition);
        if (log->isDebugEnabled()) {
            log->debug("Set current position of Source " + this->getSystemName() + " to " + this->_currentPosition);
        }
#endif
    }
}

//@Override
/*public*/ void AbstractAudioSource::resetCurrentPosition() {
    activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_RESET_POSITION));
    activeAudioFactory->getCommandThread()->exit();
}

/**
 * Method to reset the current position
 */
/*protected*/ void AbstractAudioSource::doResetCurrentPosition() {
    this->_currentPosition = this->_position;
}

/**
 * Method to change the current position of this source
 *
 * @param pos new position
 */
/*abstract*/ /*protected*/ void AbstractAudioSource::changePosition(QVector3D pos) {}

//@Override
/*public*/ void AbstractAudioSource::setGain(float gain)
{
 this->_gain = gain;
 if (log->isDebugEnabled())
 {
  log->debug("Set gain of Source " + this->getSystemName() + " to " + QString::number(gain));
 }
}

//@Override
/*public*/ float AbstractAudioSource::getGain() {
    return this->_gain;
}

/**
 * Method to calculate the gain of this AudioSource based on distance from
 * listener and fade levels
 */
/*abstract*/ /*protected*/ void AbstractAudioSource::calculateGain() {}

//@Override
/*public*/ void AbstractAudioSource::setPitch(float pitch) {
    if (pitch < 0.5) {
        pitch = 0.5;
    }
    if (pitch > 2.0) {
        pitch = 2.0;
    }
    this->_pitch = pitch;
    if (log->isDebugEnabled()) {
        log->debug("Set pitch of Source " + this->getSystemName() + " to " + pitch);
    }
}

//@Override
/*public*/ float AbstractAudioSource::getPitch() {
    return this->_pitch;
}

//@Override
/*public*/ void AbstractAudioSource::setReferenceDistance(float referenceDistance)
{
 if (referenceDistance < 0.0)
 {
  referenceDistance = 0.0;
 }
 this->_referenceDistance = referenceDistance;
 if (log->isDebugEnabled())
 {
  log->debug("Set reference distance of Source " + this->getSystemName() + " to " + referenceDistance);
 }
}

//@Override
/*public*/ float AbstractAudioSource::getReferenceDistance() {
    return this->_referenceDistance;
}

//@Override
/*public*/ void AbstractAudioSource::setMaximumDistance(float maximumDistance) {
    if (maximumDistance < 0.0) {
        maximumDistance = 0.0;
    }
    this->_maximumDistance = maximumDistance;
    if (log->isDebugEnabled()) {
        log->debug("Set maximum distance of Source " + this->getSystemName() + " to " + maximumDistance);
    }
}

//@Override
/*public*/ float AbstractAudioSource::getMaximumDistance() {
    return this->_maximumDistance;
}

//@Override
/*public*/ void AbstractAudioSource::setRollOffFactor(float rollOffFactor) {
    this->_rollOffFactor = rollOffFactor;
    if (log->isDebugEnabled()) {
        log->debug("Set roll-off factor of Source " + this->getSystemName() + " to " + rollOffFactor);
    }
}

//@Override
/*public*/ float AbstractAudioSource::getRollOffFactor() {
    return this->_rollOffFactor;
}

//@Override
/*public*/ void AbstractAudioSource::setLooped(bool loop) {
    if (loop) {
        this->_minLoops = LOOP_CONTINUOUS;
        this->_maxLoops = LOOP_CONTINUOUS;
    } else {
        this->_minLoops = LOOP_NONE;
        this->_maxLoops = LOOP_NONE;
    }
    calculateLoops();
}

//@Override
/*public*/ bool AbstractAudioSource::isLooped() {
    return (this->_minLoops != LOOP_NONE || this->_maxLoops != LOOP_NONE);
}

//@Override
/*public*/ void AbstractAudioSource::setMinLoops(int loops) {
    if (this->_maxLoops < loops) {
        this->_maxLoops = loops;
    }
    this->_minLoops = loops;
    calculateLoops();
}

//@Override
/*public*/ int AbstractAudioSource::getMinLoops() {
    return this->_minLoops;
}

//@Override
/*public*/ void AbstractAudioSource::setMaxLoops(int loops) {
    if (this->_minLoops > loops) {
        this->_minLoops = loops;
    }
    this->_maxLoops = loops;
    calculateLoops();
}

/**
 * Method to calculate the number of times to loop playback of this sound
 */
/*protected*/ void AbstractAudioSource::calculateLoops()
 {
  if (this->_minLoops != this->_maxLoops)
  {
//   Random r = new Random();
   int r = qrand();
   this->_numLoops = this->_minLoops + r* (this->_maxLoops - this->_minLoops);
  }
//  else
  {
   this->_numLoops = this->_minLoops;
  }
}

//@Override
/*public*/ int AbstractAudioSource::getMaxLoops() {
    return this->_maxLoops;
}

//@Override
/*public*/ int AbstractAudioSource::getNumLoops() {
    // Call the calculate method each time so as to ensure
    // randomness when min and max are not equal
    calculateLoops();
    return this->_numLoops;
}

//    /*public*/ void setMinLoopDelay(int loopDelay) {
//        if (this->_maxLoopDelay < loopDelay) {
//            this->_maxLoopDelay = loopDelay;
//        }
//        this->_minLoopDelay = loopDelay;
//        calculateLoopDelay();
//    }
//
//    /*public*/ int getMinLoopDelay() {
//        return this->_minLoopDelay;
//    }
//
//    /*public*/ void setMaxLoopDelay(int loopDelay) {
//        if (this->_minLoopDelay > loopDelay) {
//            this->_minLoopDelay = loopDelay;
//        }
//        this->_maxLoopDelay = loopDelay;
//        calculateLoopDelay();
//    }
//
//    /*public*/ int getMaxLoopDelay() {
//        return this->_maxLoopDelay;
//    }
//
//    /*public*/ int getLoopDelay() {
//        // Call the calculate method each time so as to ensure
//        // randomness when min and max are not equal
//        calculateLoopDelay();
//        return this->_loopDelay;
//    }
//
//    /**
//     * Method to calculate the delay between subsequent loops of this source
//     */
//    /*protected*/ void calculateLoopDelay() {
//        if (this->_minLoopDelay != this->_maxLoopDelay) {
//            Random r = new Random();
//            this->_loopDelay = this->_minLoopDelay + r.nextInt(this->_maxLoopDelay-this->_minLoopDelay);
//        } else {
//            this->_loopDelay = this->_minLoopDelay;
//        }
//    }
//@Override
/*public*/ void AbstractAudioSource::setFadeIn(int fadeInTime) {
    this->_fadeInTime = fadeInTime;
}

//@Override
/*public*/ int AbstractAudioSource::getFadeIn() {
    return this->_fadeInTime;
}

//@Override
/*public*/ void AbstractAudioSource::setFadeOut(int fadeOutTime) {
    this->_fadeOutTime = fadeOutTime;
}

//@Override
/*public*/ int AbstractAudioSource::getFadeOut() {
    return this->_fadeOutTime;
}

//@Override
/*public*/ void AbstractAudioSource::setDopplerFactor(float dopplerFactor) {
    this->_dopplerFactor = dopplerFactor;
}

//@Override
/*public*/ float AbstractAudioSource::getDopplerFactor() {
    return this->_dopplerFactor;
}

/**
 * Used to return the current calculated fade gain for this AudioSource
 *
 * @return current fade gain
 */
/*protected*/ float AbstractAudioSource::getFadeGain() {
    return this->_fadeGain;
}

/**
 * Method used to calculate the fade gains
 */
/*protected*/ void AbstractAudioSource::calculateFades() {

    // Calculate how long it's been since we lasted checked fade gains
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 timePassed = currentTime - this->_timeOfLastFadeCheck;
    this->_timeOfLastFadeCheck = currentTime;

    switch (this->_fading) {
        case Audio::FADE_NONE:
            // Reset fade gain
            this->_fadeGain = 1.0;
            break;
        case Audio::FADE_OUT:
            // Calculate fade-out gain
            this->_fadeGain -= qRound((float)timePassed) / (this->getFadeOut());

            // Ensure that fade-out gain is not less than 0.0
            if (this->_fadeGain < 0.0) {
                this->_fadeGain = 0.0;

                // If so, we're done fading
                this->_fading = Audio::FADE_NONE;
            }
            if (log->isDebugEnabled()) {
                log->debug("Set fade out gain of AudioSource "
                        + this->getSystemName() + " to " + this->_fadeGain);
            }
            break;
        case Audio::FADE_IN:
            // Calculate fade-in gain
            this->_fadeGain += qRound((float)timePassed) / (this->getFadeIn());

            // Ensure that fade-in gain is not greater than 1.0
            if (this->_fadeGain >= 1.0) {
                this->_fadeGain = 1.0;

                // If so, we're done fading
                this->_fading = Audio::FADE_NONE;
            }
            if (log->isDebugEnabled()) {
                log->debug("Set fade in gain of AudioSource "
                        + this->getSystemName() + " to " + this->_fadeGain);
            }
            break;
        default:
            throw new IllegalArgumentException();
    }
}

// Probably aught to be abstract, but I don't want to force the non-JOAL Source
// types to implement this (yet).  So default to failing.
/*public*/ bool AbstractAudioSource::queueAudioBuffers(QQueue<AudioBuffer*> audioBuffers) {
    log->debug("Abstract queueAudioBuffers() called.");
    return (false);
}

// Probably aught to be abstract, but I don't want to force the non-JOAL Source
// types to implement this (yet).  So default to failing.
/*public*/ bool AbstractAudioSource::queueAudioBuffer(AudioBuffer* audioBuffer) {
    return (false);
}

/*public*/ bool AbstractAudioSource::unqueueAudioBuffers() {
    return (false);
}

// Probably aught to be abstract, but I don't want to force the non-JOAL Source
// types to implement this (yet).  So default to failing.
//@Override
/*public*/ int AbstractAudioSource::numQueuedBuffers() {
    return (0);
}

// Probably aught to be abstract, but I don't want to force the non-JOAL Source
// types to implement this (yet).  So default to failing.
/*public*/ int AbstractAudioSource::numProcessedBuffers() {
    return (0);
}

/**
 * Binds this AudioSource with the specified AudioBuffer
 * <p>
 * Applies only to sub-types:
 * <ul>
 * <li>Source
 * </ul>
 *
 * @param buffer The AudioBuffer to bind to this AudioSource
 * @return true if successful
 */
/*abstract*/ bool AbstractAudioSource::bindAudioBuffer(AudioBuffer* buffer) {return false;}

/**
 * Method to define if this AudioSource has been bound to an AudioBuffer
 *
 * @param bound True if bound to an AudioBuffer
 */
/*protected*/ void AbstractAudioSource::setBound(bool bound) {
    this->_bound = bound;
}

/*protected*/ void AbstractAudioSource::setQueued(bool queued) {
    this->_queued = queued;
}

//@Override
/*public*/ bool AbstractAudioSource::isBound() {
    return this->_bound;
}

//@Override
/*public*/ bool AbstractAudioSource::isQueued() {
    return this->_queued;
}

//@Override
/*public*/ void AbstractAudioSource::stateChanged(int oldState) {
    // Get the current state
    int i = this->getState();

    // Check if the current state has changed to playing
    if (i != oldState && i == STATE_PLAYING) {
        // We've changed to playing so start the move thread
        this->_timeOfLastPositionCheck = QDateTime::currentMSecsSinceEpoch();
        AudioSourceMoveThread* asmt = new AudioSourceMoveThread(this);
        asmt->start();
    }

//        // Check if the current state has changed to stopped
//        if (i!=oldState && i==STATE_STOPPED) {
//            // We've changed to stopped so determine if we need to start the
//            // loop delay thread
//            if (isLooped() && getMinLoops()!=LOOP_CONTINUOUS) {
//                // Yes, we need to
//                if (asdt!=NULL) {
//                    asdt.cleanup();
//                    asdt = NULL;
//                }
//                asdt = new AudioSourceDelayThread(this);
//                asdt.start();
//            }
//        }
}

//@Override
/*public*/ void AbstractAudioSource::play() {
    this->_fading = Audio::FADE_NONE;
//        if (asdt!=NULL) {
//            asdt->exit();
//        }
    if (this->getState() != STATE_PLAYING) {
        this->setState(STATE_PLAYING);
        activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_PLAY));
        activeAudioFactory->getCommandThread()->exit();
    }
}

/**
 * Play the clip from the beginning. If looped, start looping
 */
/*abstract*/ /*protected*/ void AbstractAudioSource::doPlay() {}

//@Override
/*public*/ void AbstractAudioSource::stop() {
    stop(true);
}

/*private*/ void AbstractAudioSource::stop(bool interruptThread) {
    this->_fading = Audio::FADE_NONE;
    this->setState(STATE_STOPPED);
    activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_STOP));
    if (interruptThread) {
        activeAudioFactory->getCommandThread()->exit();
    }
}

/**
 * Stop playing the clip and rewind to the beginning
 */
/*abstract*/ /*protected*/ void AbstractAudioSource::doStop() {}

//@Override
/*public*/ void AbstractAudioSource::togglePlay() {
    this->_fading = Audio::FADE_NONE;
    activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_PLAY_TOGGLE));
    activeAudioFactory->getCommandThread()->exit();
}

/**
 * Toggle the current playing status. Will always start at/return to the
 * beginning of the sample
 */
/*protected*/ void AbstractAudioSource::doTogglePlay() {
    if (this->getState() == STATE_PLAYING) {
        stop();
    } else {
        play();
    }
}

//@Override
/*public*/ void AbstractAudioSource::pause() {
    this->_fading = Audio::FADE_NONE;
    this->setState(STATE_STOPPED);
    activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_PAUSE));
    activeAudioFactory->getCommandThread()->exit();
}

/**
 * Stop playing the clip but retain the current position
 */
/*abstract*/ /*protected*/ void AbstractAudioSource::doPause() {}

//@Override
/*public*/ void AbstractAudioSource::resume() {
    this->_fading = Audio::FADE_NONE;
    this->setState(STATE_PLAYING);
    activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_RESUME));
    activeAudioFactory->getCommandThread()->exit();
}

/**
 * Play the clip from the current position
 */
/*abstract*/ /*protected*/ void AbstractAudioSource::doResume() {}

//@Override
/*public*/ void AbstractAudioSource::togglePause() {
    this->_fading = Audio::FADE_NONE;
    activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_PAUSE_TOGGLE));
    activeAudioFactory->getCommandThread()->exit();
}

/**
 * Toggle the current playing status. Will retain the playback position of
 * the sample
 */
/*protected*/ void AbstractAudioSource::doTogglePause() {
    if (this->getState() == STATE_PLAYING) {
        pause();
    } else {
        resume();
    }
}

//@Override
/*public*/ void AbstractAudioSource::rewind() {
    this->_fading = Audio::FADE_NONE;
    this->setState(STATE_STOPPED);
    activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_REWIND));
    activeAudioFactory->getCommandThread()->exit();
}

/**
 * Rewind clip to the beginning
 */
/*abstract*/ /*protected*/ void AbstractAudioSource::doRewind() {}

//@Override
/*public*/ void AbstractAudioSource::fadeIn() {
    if (this->getState() != STATE_PLAYING && this->_fading != Audio::FADE_IN) {
        this->_fading = Audio::FADE_IN;
        this->_fadeGain = 0.0;
        this->_timeOfLastFadeCheck = QDateTime::currentMSecsSinceEpoch();
        this->setState(STATE_PLAYING);
        activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_FADE_IN));
        activeAudioFactory->getCommandThread()->exit();
    }
}

/**
 * Fade in then play this AudioSource
 */
/*abstract*/ /*protected*/ void AbstractAudioSource::doFadeIn() {}

//@Override
/*public*/ void AbstractAudioSource::fadeOut() {
    if (this->getState() == STATE_PLAYING && this->_fading != Audio::FADE_OUT) {
        this->_fading = Audio::FADE_OUT;
        this->_fadeGain = 1.0;
        this->_timeOfLastFadeCheck = QDateTime::currentMSecsSinceEpoch();
        this->setState(STATE_PLAYING);
        activeAudioFactory->audioCommandQueue(new AudioCommand(this, Audio::CMD_FADE_OUT));
        activeAudioFactory->getCommandThread()->exit();
    }
}

/**
 * Fade out then stop this AudioSource
 */
/*abstract*/ /*protected*/ void AbstractAudioSource::doFadeOut() {}

/**
 * Return the current fading status
 *
 * @return fading status
 */
/*protected*/ int AbstractAudioSource::getFading() {
    return this->_fading;
}

//@Override
/*public*/ QString AbstractAudioSource::toString()
 {
  QVector3D pos = this->getPosition();
    return QString("Pos: ") + "x="+ QString::number(pos.x())+ " y="+ QString::number(pos.y())+ " z="+ QString::number(pos.z())
            + ", bound to: " + this->getAssignedBufferName()
            + ", loops: "
            + ((this->getMinLoops() == LOOP_CONTINUOUS) ? "infinite"
                    : ((!this->isLooped()) ? "none"
                            : "(min=" + QString::number(this->getMinLoops()) + " max=" + QString::number(this->getMaxLoops()) + ")"));
}

// /*private*/ static final Logger log = LoggerFactory.getLogger(AbstractAudioSource.class.getName());

/**
 * An internal class used to create a new thread to monitor and maintain
 * fade in and fade out levels.
 * <p>
 * Will exist only as long as this source is in the process of fading in or
 * out.
 */
///*protected*/ static class AudioSourceFadeThread extends AbstractAudioThread {

/**
 * Reference to the AudioSource object being monitored
 */
///*private*/ AbstractAudioSource audioSource;

/**
 * Internal variable to hold the fade direction
 */
///*private*/ int fadeDirection;

/**
 * Constructor that takes handle to looping AudioSource to monitor
 *
 * @param audioSource looping AudioSource to monitor
 */
AudioSourceFadeThread::AudioSourceFadeThread(AbstractAudioSource* audioSource, QObject* parent)
 : AbstractAudioThread(parent)
{
 log = new Logger("AudioSourceFadeThread");
    //super();
    this->setObjectName("fadesrc-" + AbstractAudioThread::objectName());
    this->audioSource = audioSource;
    this->fadeDirection = audioSource->getFading();
    if (log->isDebugEnabled()) {
        log->debug("Created AudioSourceFadeThread for AudioSource " + audioSource->getSystemName());
    }
}

/**
 * Main processing loop
 */
//@Override
/*public*/ void AudioSourceFadeThread::run() {

    while (!dying()) {

        // Recalculate the fade levels
        audioSource->calculateFades();

        // Recalculate the gain levels
        audioSource->calculateGain();

        // Check if we've done fading
        if (audioSource->getFading() == Audio::FADE_NONE) {
            die();
        }

        // sleep for a while so as not to overload CPU
        snooze(20);
    }

    // Reset fades
    audioSource->calculateFades();

    // Check if we were fading out and, if so, stop.
    // Otherwise reset gain
    if (this->fadeDirection == Audio::FADE_OUT) {
        audioSource->doStop();
    } else {
        audioSource->calculateGain();
    }

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
/*protected*/ void AudioSourceFadeThread::cleanup() {
    // Thread is to shutdown
    die();

    // Clear references to objects
    this->audioSource = NULL;

    // Finalise cleanup in super-class
    AbstractAudioThread::cleanup();
}
//}

/**
* An internal class used to create a new thread to monitor and maintain
* current source position with respect to velocity.
*/
///*protected*/ static class AudioSourceMoveThread extends AbstractAudioThread {

/**
 * Reference to the AudioSource object being monitored
 */
///*private*/ AbstractAudioSource audioSource;

/**
 * Constructor that takes handle to looping AudioSource to monitor
 *
 * @param audioSource looping AudioSource to monitor
 */
AudioSourceMoveThread::AudioSourceMoveThread(AbstractAudioSource* audioSource, QObject* parent)
 : AbstractAudioThread(parent)
{
 //super();
 log = new Logger("AudioSourceMoveThread");
    this->setObjectName("movesrc-" + AbstractAudioThread::objectName());
    this->audioSource = audioSource;
    if (log->isDebugEnabled()) {
        log->debug("Created AudioSourceMoveThread for AudioSource " + audioSource->getSystemName());
    }
}

/**
 * Main processing loop
 */
//@Override
/*public*/ void AudioSourceMoveThread::run() {

    while (!dying()) {

        // Recalculate the position
        audioSource->calculateCurrentPosition();

        // Check state and die if not playing
        if (audioSource->getState() != Audio::STATE_PLAYING) {
            die();
        }

        // sleep for a while so as not to overload CPU
        snooze(100);
    }

//            // Reset the current position
//            audioSource.resetCurrentPosition();
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
/*protected*/ void AudioSourceMoveThread::cleanup() {
    // Thread is to shutdown
    die();

    // Clear references to objects
    this->audioSource = NULL;

    // Finalise cleanup in super-class
    AbstractAudioThread::cleanup();
}


//    /**
//     * An internal class used to create a new thread to delay subsequent
//     * playbacks of a non-continuous looped source.
//     */
//    /*private*/ class AudioSourceDelayThread extends Thread {
//
//        /**
//         * Reference to the AudioSource object being monitored
//         */
//        /*private*/ AbstractAudioSource audioSource;
//
//        /**
//         * Constructor that takes handle to looping AudioSource to monitor
//         *
//         * @param audioSource looping AudioSource to monitor
//         */
//        AudioSourceDelayThread(AbstractAudioSource audioSource) {
//            super();
//            this->setName("delaysrc-"+super.getName());
//            this->audioSource = audioSource;
//            if (log->isDebugEnabled()) log->debug("Created AudioSourceDelayThread for AudioSource " + audioSource.getSystemName());
//        }
//
//        /**
//         * Main processing loop
//         */
//        //@Override
//        /*public*/ void run() {
//
//            // Sleep for the required period of time
//            try {
//                Thread.sleep(audioSource.getLoopDelay());
//            } catch (InterruptedException ex) {}
//
//            // Restart playing this AudioSource
//            this->audioSource.play();
//
//            // Finish up
//            if (log->isDebugEnabled()) log->debug("Clean up thread " + this->getName());
//            cleanup();
//        }
//
//        /**
//         * Shuts this thread down and clears references to created objects
//         */
//        /*protected*/ void cleanup() {
//            // Clear references to objects
//            this->audioSource = NULL;
//        }
//    }

