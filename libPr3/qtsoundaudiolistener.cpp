#include "qtsoundaudiolistener.h"
#include "audiomanager.h"
#include "instancemanager.h"
#include "qtsoundaudiosource.h"

//QtSoundAudioListener::QtSoundAudioListener(QObject *parent) :
//  AbstractAudioListener(parent)
//{
//}
/**
 * QtSound implementation of the Audio Listener sub-class.
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
///*public*/ class QtSoundAudioListener extends AbstractAudioListener {

/**
 *
 */
// /*private*/ static final long serialVersionUID = 9173649719613819402L;

/**
 * Constructor for new QtSoundAudioListener with system name
 *
 * @param systemName AudioListener object system name (e.g. IAL)
 */
/*public*/ QtSoundAudioListener::QtSoundAudioListener(QString systemName, QObject *parent) :
  AbstractAudioListener(systemName, parent)
{
 //super(systemName);
 common();
 if (log->isDebugEnabled()) {
     log->debug("New QtSoundAudioListener: " + systemName);
 }
}

/**
 * Constructor for new QtSoundAudioListener with system name and user name
 *
 * @param systemName AudioListener object system name (e.g. IAL)
 * @param userName   AudioListener object user name
 */
/*public*/ QtSoundAudioListener::QtSoundAudioListener(QString systemName, QString userName, QObject *parent) :
  AbstractAudioListener(systemName, userName, parent)
{
 //super(systemName, userName);
 common();
 if (log->isDebugEnabled()) {
     log->debug("New QtSoundAudioListener: " + userName + " (" + systemName + ")");
 }
}

void QtSoundAudioListener::common()
{
 log = new Logger("QtSoundAudioListener");
 log->setDebugEnabled(true);
}

//@Override
/*protected*/ void QtSoundAudioListener::changePosition(QVector3D pos)
{
 recalculateSources();
}

//@Override
/*public*/ void QtSoundAudioListener::setGain(float gain)
{
 AbstractAudioListener::setGain(gain);
 recalculateSources();
}

/**
 * Private method to loop through all sources and recalculate gain & pan
 */
/*private*/ void QtSoundAudioListener::recalculateSources()
{
 // Loop through each AudioSource and recalculate their gain & pan
 AudioManager* am = (AudioManager*)InstanceManager::getDefault("AudioManager");
 foreach (QString sysName, am->getSystemNameList())
 {
  Audio* audio = am->getBySystemName(sysName);
  if (audio->getSubType() == Audio::SOURCE
//          && audio instanceof QtSoundAudioSource)
      && qobject_cast<QtSoundAudioSource*>(audio)!= nullptr)
  {
   ((QtSoundAudioSource*) audio)->calculateGain();
   ((QtSoundAudioSource*) audio)->calculatePan();
   if (log->isDebugEnabled()) {
       log->debug("Recalculating gain & pan for QtSoundAudioSource " + audio->getSystemName());
   }
  }
 }
}

//@Override
/*protected*/ void QtSoundAudioListener::cleanUp() {
    // no clean-up needed for Listener
    if (log->isDebugEnabled()) {
        log->debug("Cleanup QtSoundAudioListener (" + this->getSystemName() + ")");
    }
    this->dispose();
}
