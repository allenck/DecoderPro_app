#include "qtsoundaudiosource.h"
#include "qtsoundaudiofactory.h"
#include "instancemanager.h"
#include "audiosource.h"
#include "sleeperthread.h"
#include "qtsoundaudiobuffer.h"
#include "audiolistener.h"
#include "floatcontrol.h"
#include "qmath.h"
#include "math.h"
#include "clip.h"
#include <QAudioOutput>
#include <QEventLoop>
#include "mixer.h"
#include "loconet/qtsoundaudioclip.h"

/*private*/ /*static*/ Mixer* QtSoundAudioSource::_mixer = QtSoundAudioFactory::getMixer();

//QtSoundAudioSource::QtSoundAudioSource(QObject *parent) :
//  AbstractAudioSource(parent)
//{
//}
/**
 * QtSound implementation of the Audio Source sub-class.
 * <p>
 * For now, no system-specific implementations are forseen - this will remain
 * internal-only
 * <p>
 * For more information about the QtSound API, visit
 * <a href="http://java.sun.com/products/java-media/sound/">http://java.sun.com/products/java-media/sound/</a>
 *
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <p>
 *
 * @author Matthew Harris copyright (c) 2009
 * @version $Revision: 28771 $
 */
// /*public*/ class QtSoundAudioSource extends AbstractAudioSource {


/**
 * Constructor for new QtSoundAudioSource with system name
 *
 * @param systemName AudioSource object system name (e.g. IAS1)
 */
/*public*/ QtSoundAudioSource::QtSoundAudioSource(QString systemName, QObject *parent) :
  AbstractAudioSource(systemName, parent)
{
 //super(systemName);
 common();
 if (log->isDebugEnabled())
 {
  log->debug("New QtSoundAudioSource: " + systemName);
 }
 _initialised = init();
}

/**
 * Constructor for new QtSoundAudioSource with system name and user name
 *
 * @param systemName AudioSource object system name (e.g. IAS1)
 * @param userName   AudioSource object user name
 */
/*public*/ QtSoundAudioSource::QtSoundAudioSource(QString systemName, QString userName, QObject *parent) :
  AbstractAudioSource(systemName, userName, parent)
{
 //super(systemName, userName);
 common();
 if (log->isDebugEnabled())
 {
  log->debug("New QtSoundAudioSource: " + userName + " (" + systemName + ")");
 }
 _initialised = init();
}

void QtSoundAudioSource::common()
{
 log = new Logger("QtSoundAudioSource");
 log->setDebugEnabled(true);
 _mixer = QtSoundAudioFactory::getMixer();
 audioOut = NULL;
 loop = NULL;

 /**
  * Reference to current active AudioListener
  */
 _activeAudioListener = InstanceManager::audioManagerInstance()->getActiveAudioFactory()->getActiveAudioListener();

 /**
  * True if we've been initialised
  */
 _initialised = false;

 /**
  * Used for playing back sound source
  */
 _clip = NULL;

 /**
  * Holds reference to the QtSoundAudioChannel object
  */
 _audioChannel = NULL;
 _jsState = false;
}

/**
 * Initialise this AudioSource
 *
 * @return True if initialised
 */
/*private*/ bool QtSoundAudioSource::init()
{
 return true;
}

//@SuppressWarnings("SleepWhileInLoop")
//@Override
bool QtSoundAudioSource::bindAudioBuffer(AudioBuffer* audioBuffer)
{
 // First check we've been initialised
 if (!_initialised)
 {
  return false;
 }

 // Wait for AudioBuffer to be loaded, or 20 seconds
 //long startTime = System.currentTimeMillis();
 quint64 startTime = QDateTime::currentMSecsSinceEpoch();
 while (audioBuffer->getState() != AudioBuffer::STATE_LOADED
         && QDateTime::currentMSecsSinceEpoch() - startTime < 20000)
 {
//     try {
         //Thread.sleep(50);
  SleeperThread::msleep(50);
//     } catch (InterruptedException ex) {
//     }
 }

// if (audioBuffer instanceof QtSoundAudioBuffer
//         && audioBuffer.getState() == AudioBuffer.STATE_LOADED)
 if(qobject_cast<QtSoundAudioBuffer*>(audioBuffer)!=NULL && audioBuffer->getState() == AudioBuffer::STATE_LOADED)
 {
  // Cast to QtSoundAudioBuffer to enable easier access to specific methods
  QtSoundAudioBuffer* buffer = (QtSoundAudioBuffer*) audioBuffer;

  // Get a QtSound DataLine and Clip
#if 1
//  DataLine::Info<Clip*>* lineInfo;
//  lineInfo = new DataLine::Info<Clip*>( buffer->getAudioFormat());
//  Clip* newClip = NULL;
//  try {
//      newClip = (Clip*) _mixer->getLine(lineInfo);
//  } catch (LineUnavailableException ex) {
//      log->warn("Error binding QtSoundSource (" + this->getSystemName()
//              + ") to AudioBuffer (" + this->getAssignedBufferName() + ") " + ex);
//      return false;
//  }

  this->_clip = new QtSoundAudioClip(buffer, this);
  //newClip = NULL;

  //try {
  if(!_clip->open(buffer->getAudioFormat(),
              buffer->getDataStorageBuffer(),
              0,
                  buffer->getDataStorageBuffer()->length()))
  {
   log->warn("Error binding QtSoundSource (" + this->getSystemName()
              + ") to AudioBuffer (" + this->getAssignedBufferName() + ")");
   return false;
  }
#endif
#if 0
  QByteArray* ba = ((QtSoundAudioBuffer*) audioBuffer)->getDataStorageBuffer();
  buf = new QBuffer(ba);
  if(!buf->open(QIODevice::ReadOnly))
   log->error("Error opening sound buffer");
  QAudioFormat qFormat = *((QtSoundAudioBuffer*) audioBuffer)->getAudioFormat();
  log->debug(QString("qFormat(bind): channnels %1, codec: %2, sampleRate: %3, sampleSize: %4, bufferSize: %5").arg(qFormat.channels()).arg(qFormat.codec()).arg(qFormat.sampleRate()).arg(qFormat.sampleSize()).arg(ba->size()));
  audioOut = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(),QAudioFormat(*((QtSoundAudioBuffer*) audioBuffer)->getAudioFormat()), this);

#if 0 // Test code
  if(loop == NULL)
   loop = new QEventLoop;
  connect(audioOut, SIGNAL(stateChanged(QAudio::State)), this, SLOT(stateChanged(QAudio::State)));
  audioOut->start(buf);
  do
  {
   loop->exec();
  } while(loop->isRunning() && audioOut->state() == QAudio::ActiveState);
  audioOut->reset();
#endif// end test code
  if (log->isDebugEnabled())
  {
   log->debug("Bind QtSoundAudioSource (" + this->getSystemName()
              + ") to QtSoundAudioBuffer (" + audioBuffer->getSystemName() + ")");
  }
#endif
  setBound(true);

  return true;
 }
 else
 {
  log->warn("AudioBuffer not loaded error when binding QtSoundSource (" + this->getSystemName()
          + ") to AudioBuffer (" + this->getAssignedBufferName() + ")");
  return false;
 }
}
#if 1
//@Override
/*protected*/ void QtSoundAudioSource::changePosition(QVector3D pos)
{
 if (_initialised && isBound() && _audioChannel != NULL)
 {
  calculateGain();
  calculatePan();
 }
}

//@Override
/*public*/ void QtSoundAudioSource::setGain(float gain)
{
 AbstractAudioSource::setGain(gain);
 if (_initialised && isBound() && _audioChannel != NULL)
 {
  calculateGain();
 }
}

//@Override
/*public*/ void QtSoundAudioSource::setPitch(float pitch)
{
 AbstractAudioSource::setPitch(pitch);
 if (_initialised && isBound() && _audioChannel != NULL)
 {
  calculatePitch();
 }
}

//@Override
/*public*/ void QtSoundAudioSource::setReferenceDistance(float referenceDistance)
{
 AbstractAudioSource::setReferenceDistance(referenceDistance);
 if (_initialised && isBound() && _audioChannel != NULL)
 {
  calculateGain();
 }
}

//@Override
/*public*/ int QtSoundAudioSource::getState()
{
 bool old = _jsState;
 _jsState = (this->_clip != NULL ? this->_clip->isActive() : false);
 if (_jsState != old)
 {
  if (_jsState == true)
  {
   this->setState(STATE_PLAYING);
  }
  else
  {
   this->setState(STATE_STOPPED);
  }
 }
 return AbstractAudioSource::getState();
}

//@Override
/*public*/ void QtSoundAudioSource::stateChanged(QAudio::State oldState)
{
 AbstractAudioSource::stateChanged(oldState);
 if(oldState != QAudio::ActiveState && loop != NULL && loop->isRunning())
 {
  log->debug(QString("play finished: state = %1").arg(oldState));
  loop->quit();
 }
 if (_initialised && isBound() && _audioChannel != NULL)
 {
  calculateGain();
  calculatePan();
  calculatePitch();
 }
 else
 {
  _initialised = init();
 }

}

//@Override
/*protected*/ void QtSoundAudioSource::doPlay()
{
 if (log->isDebugEnabled())
 {
  log->debug("Play QtSoundAudioSource (" + this->getSystemName() + ")");
 }
 if (_initialised && isBound())
 {
  doRewind();
  doResume();
 }
}

//@Override
/*protected*/ void QtSoundAudioSource::doStop()
{
 if (log->isDebugEnabled())
 {
  log->debug("Stop QtSoundAudioSource (" + this->getSystemName() + ")");
 }
 if (_initialised && isBound())
 {
  doPause();
  doRewind();
 }
}

//@Override
/*protected*/ void QtSoundAudioSource::doPause()
{
 if (log->isDebugEnabled()) {
     log->debug("Pause QtSoundAudioSource (" + this->getSystemName() + ")");
 }
 if (_initialised && isBound())
 {
  if(this->_clip != NULL)
   this->_clip->stop();
  if (_audioChannel != NULL)
  {
   if (log->isDebugEnabled())
   {
    log->debug("Remove QtSoundAudioChannel for Source " + this->getSystemName());
   }
   _audioChannel = NULL;
  }
 }
 this->setState(STATE_STOPPED);
}

//@Override
/*protected*/ void QtSoundAudioSource::doResume()
{
 if (log->isDebugEnabled())
 {
  log->debug("Resume QtSoundAudioSource (" + this->getSystemName() + ")");
 }
 if (_initialised && isBound())
 {
  if (_audioChannel == NULL)
  {
   if (log->isDebugEnabled())
   {
    log->debug("Create QtSoundAudioChannel for Source " + this->getSystemName());
   }
//   _audioChannel = new QtSoundAudioChannel(this);
  }

  if(this->_clip != NULL)
   this->_clip->loop(this->getNumLoops());
  this->setState(STATE_PLAYING);
#if 0
  QtSoundAudioBuffer* audioBuffer = (QtSoundAudioBuffer*)_buffer;
  if(log->isDebugEnabled()) log->debug(QString("play sound: buffersize = %1").arg(buf->size()));
  QAudioFormat qFormat = *((QtSoundAudioBuffer*) audioBuffer)->getAudioFormat();
  log->debug(QString("qFormat(doResume): channnels %1, codec: %2, sampleRate: %3, sampleSize: %4, bufferSize: %5").arg(qFormat.channels()).arg(qFormat.codec()).arg(qFormat.sampleRate()).arg(qFormat.sampleSize()).arg(buf->size()));

  if(!buf->isOpen())
  {
   if(!buf->open(QIODevice::ReadOnly))
   {
    log->error("error opening sound buffer");
    return;
   }
  }
  buf->seek(0);
  if(loop == NULL)
   loop = new QEventLoop;
  connect(audioOut, SIGNAL(stateChanged(QAudio::State)), this, SLOT(stateChanged(QAudio::State)));

  audioOut->start(buf);
  this->setState(STATE_PLAYING);

  do
  {
   loop->exec();
   if(audioOut->error() != QAudio::NoError)
    loop->quit();
  } while(loop->isRunning() && audioOut->state() == QAudio::ActiveState);

  setBound(true);
  this->setState(STATE_STOPPED);
  if (log->isDebugEnabled())
  {
   log->debug("Resume QtSoundAudioSource (" + this->getSystemName()
              + ") to QtSoundAudioBuffer (" + audioBuffer->getSystemName() + ")");
  }
  audioOut->reset();
#endif
 }
#endif
}

//@Override
/*protected*/ void QtSoundAudioSource::doRewind()
{
 if (log->isDebugEnabled())
 {
  log->debug("Rewind QtSoundAudioSource (" + this->getSystemName() + ")");
 }
 if (_initialised && isBound())
 {
  if(this->_clip != NULL)
   this->_clip->setFramePosition(0);
 }
}

//@Override
/*protected*/ void QtSoundAudioSource::doFadeIn()
{
 if (log->isDebugEnabled())
 {
  log->debug("Fade-in QtSoundAudioSource (" + this->getSystemName() + ")");
 }
 if (_initialised && isBound())
 {
  doPlay();
  AudioSourceFadeThread* asft = new AudioSourceFadeThread(this);
  asft->start();
 }
}

//@Override
/*protected*/ void QtSoundAudioSource::doFadeOut()
{
 if (log->isDebugEnabled()) {
     log->debug("Fade-out QtSoundAudioSource (" + this->getSystemName() + ")");
 }
 if (_initialised && isBound()) {
     AudioSourceFadeThread* asft = new AudioSourceFadeThread(this);
     asft->start();
 }
}

//@Override
/*protected*/ void QtSoundAudioSource::cleanUp()
{
 if (_initialised && isBound())
 {
  if(this->_clip != NULL)
  {
   this->_clip->stop();
   this->_clip->close();
   this->_clip = NULL;
  }
 }
 if (log->isDebugEnabled())
 {
  log->debug("Cleanup QtSoundAudioSource (" + this->getSystemName() + ")");
 }
 this->dispose();
}

/**
 * Calculates the panning of this Source between fully left (-1.0f) and
 * fully right (1.0f)
 * <p>
 * Calculated internally from the relative positions of this source and the
 * listener.
 */
/*protected*/ void QtSoundAudioSource::calculatePan()
{
 QVector3D side = QVector3D();
 side.crossProduct(_activeAudioListener->getOrientation(UP), _activeAudioListener->getOrientation(AT));
 side.normalize();
 QVector3D vecX =  QVector3D(this->getCurrentPosition());
 QVector3D vecZ =  QVector3D(this->getCurrentPosition());
 //float x = vecX.dotProduct(side);
 float x = QVector3D::dotProduct(vecX, side);
 //float z = vecZ.dotProduct(_activeAudioListener->getOrientation(AT));
 float z = QVector3D::dotProduct(vecZ, _activeAudioListener->getOrientation(AT));
 float angle = (float) qAtan2(x, z);
 float pan = (float) -qSin(angle);

 // If playing, update the pan
 if (_audioChannel != NULL) {
     _audioChannel->setPan(pan);
 }
 if (log->isDebugEnabled()) {
     log->debug("Set pan of QtSoundAudioSource " + this->getSystemName() + " to " + pan);
 }
}
#if 1
//@Override
/*protected*/ void QtSoundAudioSource::calculateGain()
{
#if 1
 // Calculate distance from listener
 QVector3D distance = QVector3D(this->getCurrentPosition());
 if (!this->isPositionRelative())
 {
  //distance.sub(_activeAudioListener->getCurrentPosition());
  distance = distance - _activeAudioListener->getCurrentPosition();
 }

 float distanceFromListener
//         = (float) qSqrt(distance.dotProduct(distance));
   = (float)qSqrt(distance.lengthSquared());
 if (log->isDebugEnabled())
 {
  log->debug("Distance of QtSoundAudioSource " + this->getSystemName() + " from Listener = " + QString::number(distanceFromListener));
 }

 // Default value to start with (used for no distance attenuation)
 float currentGain = 1.0f;

 if (InstanceManager::audioManagerInstance()->getActiveAudioFactory()->isDistanceAttenuated())
 {
  // Calculate gain of this source using clamped inverse distance
  // attenuation model

  distanceFromListener = qMax(distanceFromListener, this->getReferenceDistance());
  if (log->isDebugEnabled())
  {
   log->debug("After initial clamping, distance of QtSoundAudioSource " + this->getSystemName() + " from Listener = " + distanceFromListener);
  }
  distanceFromListener = qMin(distanceFromListener, this->getMaximumDistance());
  if (log->isDebugEnabled())
  {
   log->debug("After final clamping, distance of QtSoundAudioSource " + this->getSystemName() + " from Listener = " + distanceFromListener);
  }

  currentGain
          = _activeAudioListener->getMetersPerUnit()
          * (this->getReferenceDistance()
          / (this->getReferenceDistance() + this->getRollOffFactor()
          * (distanceFromListener - this->getReferenceDistance())));
  if (log->isDebugEnabled())
  {
   log->debug("Calculated for QtSoundAudioSource " + this->getSystemName() + " gain = " + currentGain);
  }

  // Ensure that gain is between 0 and 1
  if (currentGain > 1.0f) {
      currentGain = 1.0f;
  } else if (currentGain < 0.0f)
  {
   currentGain = 0.0f;
  }
 }

 // Finally, adjust based on master gain for this source, the gain
 // of listener and any calculated fade gains
 currentGain *= this->getGain() * _activeAudioListener->getGain() * this->getFadeGain();

 // If playing, update the gain
 if (_audioChannel != NULL)
 {
  _audioChannel->setGain(currentGain);
  if (log->isDebugEnabled())
  {
   log->debug("Set current gain of QtSoundAudioSource " + this->getSystemName() + " to " + QString::number(currentGain));
  }
 }
#endif
}

/**
 * Internal method used to calculate the pitch
 */
/*protected*/ void QtSoundAudioSource::calculatePitch()
{
 // If playing, update the pitch
 if (_audioChannel != NULL) {
     _audioChannel->setPitch(this->getPitch());
 }
}

///*private*/ static final Logger log = LoggerFactory.getLogger(QtSoundAudioSource.class.getName());
#endif
///*private*/ /*static*/ class QtSoundAudioChannel {

//    /**
//     * Control for changing the gain of this AudioSource
//     */
//    /*private*/ FloatControl _gainControl = NULL;

//    /**
//     * Control for changing the pan of this AudioSource
//     */
//    /*private*/ FloatControl _panControl = NULL;

//    /**
//     * Control for changing the sample rate of this AudioSource
//     */
//    /*private*/ FloatControl _sampleRateControl = NULL;

//    /**
//     * Holds the initial sample rate setting
//     */
//    /*private*/ float _initialSampleRate = 0.0f;

//    /**
//     * Holds the initial gain setting
//     */
//    /*private*/ float _initialGain = 0.0f;

//    /**
//     * Holds reference to the parent AudioSource object
//     */
//    /*private*/ QtSoundAudioSource _audio;

//    /**
//     * Holds reference to the QtSound clip
//     */
//    /*private*/ Clip _clip;

/**
 * Constructor for creating an AudioChannel for a specific
 * QtSoundAudioSource
 *
 * @param audio the specific QtSoundAudioSource
 */
/*public*/ QtSoundAudioChannel::QtSoundAudioChannel(QtSoundAudioSource* audio)
{
 _gainControl = NULL;
 _panControl = NULL;
 _sampleRateControl = NULL;
 _initialSampleRate = 0.0;
 _initialGain = 0.0;
 log = new Logger("QtSoundAudioCHannel");

 this->_audio = audio;
 this->_clip = this->_audio->_clip;

 // Check if changing gain is supported
 if (this->_clip->isControlSupported(FloatControl::Type::MASTER_GAIN))
 {
  // Yes, so create a new gain control
  this->_gainControl = (FloatControl*) this->_clip->getControl(FloatControl::Type::MASTER_GAIN);
  this->_initialGain = this->_gainControl->getValue();
  if (log->isDebugEnabled())
  {
   log->debug("QtSound gain control created");
   log->debug("Initial Gain = " + QString::number(this->_initialGain));
  }
 } else {
     log->info("Gain control is not supported");
     this->_gainControl = NULL;
 }

 // Check if changing pan is supported
 if (this->_clip->isControlSupported(FloatControl::Type::PAN)) {
     // Yes, so create a new pan control
     this->_panControl = (FloatControl*) this->_clip->getControl(FloatControl::Type::PAN);
     if (log->isDebugEnabled()) {
         log->debug("QtSound pan control created");
     }
 } else {
     log->info("Pan control is not supported");
     this->_panControl = NULL;
 }

 // Check if changing pitch is supported
 if (this->_clip->isControlSupported(FloatControl::Type::SAMPLE_RATE)) {
     // Yes, so create a new pitch control
     this->_sampleRateControl = (FloatControl*) this->_clip->getControl(FloatControl::Type::SAMPLE_RATE);
     this->_initialSampleRate = this->_sampleRateControl->getValue();
     if (log->isDebugEnabled()) {
         log->debug("QtSound pitch control created");
         log->debug("Initial Sample Rate = " + QString::number(this->_initialSampleRate));
     }
 } else {
     log->info("Sample Rate control is not supported");
     this->_sampleRateControl = NULL;
     this->_initialSampleRate = 0;
 }
    }

/**
 * Sets the gain of this AudioChannel
 *
 * @param gain the gain (0.0f to 1.0f)
 */
/*protected*/ void QtSoundAudioChannel::setGain(float gain)
{
 if (this->_gainControl != NULL)
 {
  // Ensure gain is within limits
  if (gain <= 0.0) {
      gain = 0.0001;
  } else if (gain > 1.0) {
      gain = 1.0;
  }

  // Convert this linear gain to a decibel value
  float dB = (float) (log10(gain) / log10(10.0) * 20.0);

  this->_gainControl->setValue(dB);
  if (log->isDebugEnabled())
  {
   log->debug("Actual gain value of QtSoundAudioSource " + this->_audio->toString() + " is " + QString::number(this->_gainControl->getValue()));
  }
 }
 if (log->isDebugEnabled()) {
     log->debug("Set gain of QtSoundAudioSource " + this->_audio->toString() + " to " + QString::number(gain));
 }
}

/**
 * Sets the pan of this AudioChannel
 *
 * @param pan the pan (-1.0f to 1.0f)
 */
/*protected*/ void QtSoundAudioChannel::setPan(float pan)
{
 if (this->_panControl != NULL)
 {
  this->_panControl->setValue(pan);
 }
 if (log->isDebugEnabled())
 {
  log->debug("Set pan of QtSoundAudioSource " + this->_audio->toString() + " to " + QString::number(pan));
 }
}

/**
 * Sets the pitch of this AudioChannel
 * <p>
 * Calculated as a ratio of the initial sample rate
 *
 * @param pitch the pitch
 */
/*protected*/ void QtSoundAudioChannel::setPitch(float pitch)
{
 if (this->_sampleRateControl != NULL)
 {
  this->_sampleRateControl->setValue(pitch * this->_initialSampleRate);
 }
 if (log->isDebugEnabled())
 {
  log->debug("Set pitch of QtSoundAudioSource " + this->_audio->toString() + " to " + QString::number(pitch));
 }
}
//};

