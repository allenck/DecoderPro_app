#include "abstractaudiomanager.h"
#include "exceptions.h"

AbstractAudioManager::AbstractAudioManager(QObject *parent) :
  AudioManager(parent)
{
 log = new Logger("AbstractAudioManager");
}
/**
 * Abstract partial implementation of an AudioManager.
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
// /*public*/ abstract class AbstractAudioManager extends AbstractManager
//        implements AudioManager {

//@Override
/*public*/ char AbstractAudioManager::typeLetter() const{
    return 'A';
}

//@Override
/*public*/ Audio* AbstractAudioManager::provideAudio(QString name) /*throws AudioException*/
{
 Audio* t = getAudio(name);
 if (t != NULL)
 {
  return t;
 }
 if (name.startsWith(getSystemPrefix() + typeLetter()))
 {
  return newAudio(name, NULL);
 }
 else
 {
  return newAudio(makeSystemName(name), NULL);
 }
}

//@Override
/*public*/ Audio* AbstractAudioManager::getAudio(QString name) {
    Audio* t = getByUserName(name);
    if (t != NULL) {
        return t;
    }

    return getBySystemName(name);
}

//@Override
/*public*/ Audio* AbstractAudioManager::getBySystemName(QString key) const
{
 //return (Audio)_tsys.get(key);
 NamedBean* bean = _tsys->value(key);
 if (bean == NULL)
 {
  bean = _tsys->value(key.toUpper());
 }
 return (Audio*)bean;
}

//@Override
/*public*/ Audio* AbstractAudioManager::getByUserName(QString key) const {
    //return key==NULL?NULL:(Audio)_tuser.get(key);
    if (key == NULL) {
        return (NULL);
    }
    Audio* rv = (Audio*) _tuser->value(key);
    if (rv == NULL) {
        rv = this->getBySystemName(key);
    }
    return (rv);
}

//@Override
/*public*/ Audio* AbstractAudioManager::newAudio(QString systemName, QString userName) /*throws AudioException */
{
 if (log->isDebugEnabled())
 {
  log->debug("new Audio:"
             + ((systemName == NULL) ? "NULL" : systemName) // NOI18N
             + ";" + ((userName == NULL) ? "NULL" : userName)); // NOI18N
 }
 if (systemName == NULL)
 {
  log->error("SystemName cannot be NULL. UserName was "
             + ((userName == NULL) ? "NULL" : userName)); // NOI18N
  return NULL;
 }
 // is system name in correct format?
 if ((!systemName.startsWith("" + getSystemPrefix() + typeLetter() + Audio::BUFFER))
         && (!systemName.startsWith("" + getSystemPrefix() + typeLetter() + Audio::SOURCE))
         && (!systemName.startsWith("" + getSystemPrefix() + typeLetter() + Audio::LISTENER)))
 {
  log->error("Invalid system name for Audio: " + systemName
          + " needed either " + getSystemPrefix() + typeLetter() + Audio::BUFFER // NOI18N
          + " or " + getSystemPrefix() + typeLetter() + Audio::SOURCE // NOI18N
          + " or " + getSystemPrefix() + typeLetter() + Audio::LISTENER);        // NOI18N
  throw  AudioException("Invalid system name for Audio: " + systemName
          + " needed either " + getSystemPrefix() + typeLetter() + Audio::BUFFER
          + " or " + getSystemPrefix() + typeLetter() + Audio::SOURCE
          + " or " + getSystemPrefix() + typeLetter() + Audio::LISTENER);
 }

 // return existing if there is one
 Audio* s;
 if ((userName != NULL) && ((s = getByUserName(userName)) != NULL))
 {
  if (getBySystemName(systemName) != s)
  {
   log->error("inconsistent user (" + userName + ") and system name (" + systemName + ") results; userName related to (" + s->getSystemName() + ")");
  }
  log->debug("Found existing Audio (" + s->getSystemName() + "). Returning existing (1).");
  return s;
 }
 if ((s = getBySystemName(systemName)) != NULL)
 {
  if ((s->getUserName() == NULL) && (userName != NULL))
  {
   s->setUserName(userName);
  }
  else if (userName != NULL)
  {
   log->warn("Found audio via system name (" + systemName
                 + ") with non-NULL user name (" + userName + ")"); // NOI18N
  }
  log->debug("Found existing Audio (" + s->getSystemName() + "). Returning existing (2).");
  return s;
 }

 log->debug("Existing audio not found. Creating new. (" + systemName + ")");
 // doesn't exist, make a new one
 s = createNewAudio(systemName, userName);

 // save in the maps
 if (!(s == NULL))
 {
  Register(s);
 }
 return s;
}

/**
 * Internal method to invoke the factory, after all the logic for returning
 * an existing method has been invoked.
 *
 * @param systemName Audio object system name (e.g. IAS1, IAB4)
 * @param userName   Audio object user name
 * @return never NULL
 * @throws AudioException if error occurs during creation
 */
/*abstract*/ /*protected*/ Audio* AbstractAudioManager::createNewAudio(QString systemName, QString userName) /*throws AudioException*/ {return NULL;}

/*public*/ QString AbstractAudioManager::getBeanTypeHandled(bool plural) {
    return (plural ? tr("Audios") : tr("Audio"));
}
