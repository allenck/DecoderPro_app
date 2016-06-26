#include "qtsoundaudiofactory.h"
#include "audiomanager.h"
#include "instancemanager.h"
#include "audio.h"
#include "qtsoundaudiobuffer.h"
#include "qtsoundaudiosource.h"
#include "qtsoundaudiolistener.h"
#include <QAudioDeviceInfo>
#include "mixer.h"

/*private*/ /*volatile*/ /*static*/ Mixer* QtSoundAudioFactory::_mixer = NULL;
/*private*/ /*static*/ bool QtSoundAudioFactory::_initialised = false;


QtSoundAudioFactory::QtSoundAudioFactory(QObject *parent) :
  AbstractAudioFactory(parent)
{
 log = new Logger("QtSoundAudioFactory");
 _activeAudioListener = NULL;
}
#if 1
/**
 * This is the JavaSound audio system specific AudioFactory.
 * <p>
 * The JavaSound sound system supports, where available, 2-channel stereo.
 * <p>
 * The implemented Audio objects provide an approximation of a 3D positionable
 * audio model through the use of calculated panning and gain based on the 3D
 * position of the individual sound sources.
 * <p>
 * This factory initialises JavaSound, provides new JavaSound-specific Audio
 * objects and deals with clean-up operations.
 * <p>
 * For more information about the JavaSound API, visit
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
 * @version $Revision: 28746 $
 */
///*public*/ class JavaSoundAudioFactory extends AbstractAudioFactory {


//@Override
/*public*/ bool QtSoundAudioFactory::init()
{
 if (_initialised)
 {
  return true;
 }

#if 0
 // Initialise JavaSound
 if (_mixer == NULL)
 {
  // Iterate through possible mixers until we find the one we require
  foreach (Mixer::Info mixerInfo, QAudioSystem::getMixerInfo()) {
      if (mixerInfo.getName().equals("Java Sound Audio Engine")) {
          _mixer = AudioSystem.getMixer(mixerInfo);
          break;
      }
  }
 }
 // Check to see if a suitable mixer has been found
 if (_mixer == NULL)
 {
  if (log->isDebugEnabled())
  {
   log->debug("No JavaSound audio system found.");
  }
  return false;
 }
 else
 {
  if (log->isInfoEnabled())
  {
   log->info("Initialised JavaSound:"
           + " vendor - " + _mixer.getMixerInfo().getVendor()
           + " version - " + _mixer.getMixerInfo().getVersion());
  }
 }
#else
 // Initialize QtSound.
// QList<QAudioDeviceInfo> list =  QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
// log->info("Available Audio output devices:");
// foreach (QAudioDeviceInfo info , list)
// {
//  log->info(" Name"+ info.deviceName());
//  if(QAudioDeviceInfo::defaultOutputDevice().deviceName() == info.deviceName())
//  {
//   log->info(" Is default!");
//  }
//  QAudioFormat format = info.preferredFormat();
//  log->info(QString("  %1Hz %2 %3 bit %4 endian").arg(format.sampleRate()).arg(format.channelCount()> 1?"stereo":"mono").arg(format.sampleSize()).arg(format.BigEndian?"big":"little"));
// }
// QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();
// QAudioFormat format = info.preferredFormat();
// log->info(QString("  %1Hz %2 %3 bit %4 endian").arg(format.sampleRate()).arg(format.channelCount()> 1?"stereo":"mono").arg(format.sampleSize()).arg(format.BigEndian?"big":"little"));
#endif

 AbstractAudioFactory::init();
 _initialised = true;
 return true;
}

//@Override
/*public*/ QString QtSoundAudioFactory::toString()
{
#if 0
 return "QtSoundAudioFactory:"
         + " vendor - " + _mixer.getMixerInfo().getVendor()
         + " version - " + _mixer.getMixerInfo().getVersion();
#else
 return "QtSoundAudioFactory: " + _mixer->deviceInfo()->deviceName();
#endif
}

//@Override
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
// OK to write to static variable _mixer as we are cleaning up
/*public*/ void QtSoundAudioFactory::cleanup()
{
 // Stop the command thread
 AbstractAudioFactory::cleanup();

 // Get the active AudioManager
 AudioManager* am = InstanceManager::audioManagerInstance();

 // Retrieve list of Audio Objects and remove the sources
 QStringList audios = am->getSystemNameList();
 foreach (QString audioName, audios)
 {
  Audio* audio = am->getAudio(audioName);
  if (audio->getSubType() == Audio::SOURCE)
  {
   if (log->isDebugEnabled())
   {
       log->debug("Removing JavaSoundAudioSource: " + audioName);
   }
   // Cast to JavaSoundAudioSource and cleanup
   ((QtSoundAudioSource*) audio)->cleanUp();
  }
 }

 // Now, re-retrieve list of Audio objects and remove the buffers
 audios = am->getSystemNameList();
 foreach (QString audioName, audios)
 {
  Audio* audio = am->getAudio(audioName);
  if (audio->getSubType() == Audio::BUFFER)
  {
   if (log->isDebugEnabled()) {
       log->debug("Removing JavaSoundAudioBuffer: " + audioName);
   }
   // Cast to JavaSoundAudioBuffer and cleanup
   ((QtSoundAudioBuffer*) audio)->cleanUp();
  }
 }

 // Lastly, re-retrieve list and remove listener.
 audios = am->getSystemNameList();
 foreach (QString audioName, audios)
 {
  Audio* audio = am->getAudio(audioName);
  if (audio->getSubType() == Audio::LISTENER)
  {
   if (log->isDebugEnabled()) {
       log->debug("Removing JavaSoundAudioListener: " + audioName);
   }
   // Cast to JavaSoundAudioListener and cleanup
   ((QtSoundAudioListener*) audio)->cleanUp();
  }
 }

 // Finally, shutdown JavaSound and close the output device
 log->debug("Shutting down JavaSound");
 _mixer = NULL;
}

//@Override
/*public*/ AudioBuffer* QtSoundAudioFactory::createNewBuffer(QString systemName, QString userName)
{
 return new QtSoundAudioBuffer(systemName, userName);
}

//@Override
/*public*/ AudioListener* QtSoundAudioFactory::createNewListener(QString systemName, QString userName)
{
 _activeAudioListener = new QtSoundAudioListener(systemName, userName);
 return _activeAudioListener;
}

//@Override
/*public*/ AudioListener* QtSoundAudioFactory::getActiveAudioListener() {
    return _activeAudioListener;
}

//@Override
/*public*/ AudioSource* QtSoundAudioFactory::createNewSource(QString systemName, QString userName)
{
 return new QtSoundAudioSource(systemName, userName);
}
#endif
/**
 * Return reference to the current JavaSound mixer object
 *
 * @return current JavaSound mixer
 */
/*public*/ /*static*/ /*synchronized*/ Mixer* QtSoundAudioFactory::getMixer()
{
 return _mixer;
}

