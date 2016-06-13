#include "nullaudiofactory.h"
#include "version.h"
#include "instancemanager.h"
#include "audiomanager.h"
#include "nullaudiosource.h"
#include "nullaudiobuffer.h"
#include "nullaudiolistener.h"

NullAudioFactory::NullAudioFactory(QObject *parent) :
  AbstractAudioFactory(parent)
{
 log = new Logger("NullAudioFactory");
}
/**
 * This is the null audio system specific AudioFactory.
 *
 * It is a dummy factory which provides the necessary object generation but does
 * not produce any sound. This will normally only be used when running on a
 * system that has no sound-card installed.
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
 * @version $Revision: 28746 $
 */
// /*public*/ class NullAudioFactory extends AbstractAudioFactory {

    /*private*/ /*static*/ bool NullAudioFactory::_initialised = false;


    //@Override
/*public*/ bool NullAudioFactory::init() {
    if (_initialised) {
        return true;
    }

    log->warn("Initialised Null audio system - no sounds will be available.");

    AbstractAudioFactory::init();
    _initialised = true;
    return true;
}

//@Override
/*public*/ QString NullAudioFactory::toString() {
    return QString("NullAudioFactory:")
            + " vendor - JMRI Community"
            + " version - " + Version::name();
}

//@Override
/*public*/ void NullAudioFactory::cleanup()
{
 // Stop the command thread
 AbstractAudioFactory::cleanup();

 // Get the active AudioManager
 AudioManager* am = InstanceManager::audioManagerInstance();

 // Retrieve list of Audio Objects and remove the sources
 QStringList audios = ((AbstractManager*)am)->getSystemNameList();
 foreach (QString audioName, audios)
 {
  Audio* audio = am->getAudio(audioName);
  if (audio->getSubType() == Audio::SOURCE)
  {
   if (log->isDebugEnabled())
   {
    log->debug("Removing NullAudioSource: " + audioName);
   }
   // Cast to NullAudioSource and cleanup
   ((NullAudioSource*) audio)->cleanUp();
  }
 }

 // Now, re-retrieve list of Audio objects and remove the buffers
 audios = ((AbstractManager*)am)->getSystemNameList();
 foreach (QString audioName, audios)
 {
  Audio* audio = am->getAudio(audioName);
     if (audio->getSubType() == Audio::BUFFER) {
         if (log->isDebugEnabled()) {
             log->debug("Removing NullAudioBuffer: " + audioName);
         }
         // Cast to NullAudioBuffer and cleanup
         ((NullAudioBuffer*) audio)->cleanUp();
     }
 }

 // Lastly, re-retrieve list and remove listener.
 audios = ((AbstractManager*)am)->getSystemNameList();
 foreach (QString audioName, audios) {
     Audio* audio = am->getAudio(audioName);
     if (audio->getSubType() == Audio::LISTENER) {
         if (log->isDebugEnabled()) {
             log->debug("Removing NullAudioListener: " + audioName);
         }
         // Cast to NullAudioListener and cleanup
         ((NullAudioListener*) audio)->cleanUp();
     }
 }

 // Finally, shutdown NullAudio and close the output device
 log->debug("Shutting down NullAudio");
 // Do nothing
}

//@Override
/*public*/ AudioBuffer* NullAudioFactory::createNewBuffer(QString systemName, QString userName) {
    return new NullAudioBuffer(systemName, userName);
}

//@Override
/*public*/ AudioListener* NullAudioFactory::createNewListener(QString systemName, QString userName) {
    activeAudioListener = new NullAudioListener(systemName, userName);
    return activeAudioListener;
}

//@Override
/*public*/ AudioListener* NullAudioFactory::getActiveAudioListener() {
    return activeAudioListener;
}

//@Override
/*public*/ AudioSource* NullAudioFactory::createNewSource(QString systemName, QString userName) {
    return new NullAudioSource(systemName, userName);
}
