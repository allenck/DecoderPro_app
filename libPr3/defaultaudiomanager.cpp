#include "defaultaudiomanager.h"
#include "manager.h"
#include "exceptions.h"
#include "instancemanager.h"
#include "quietshutdowntask.h"
#include "nullaudiofactory.h"
#include "qtsoundaudiofactory.h"

DefaultAudioManager::DefaultAudioManager(QObject *parent) :
  AbstractAudioManager(parent)
{
 setObjectName("DefaultAudioManager");
 log = new Logger("DefaultAudioManager");
 audioShutDownTask = nullptr;
 registerSelf();

 listeners = QSet<NamedBean*>();
 buffers = QSet<NamedBean*>();
 sources = QSet<NamedBean*>();

}
/**
 * Provide the concrete implementation for the Internal Audio Manager.
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
// /*public*/ class DefaultAudioManager extends AbstractAudioManager {

/*private*/ /*static*/ int DefaultAudioManager::countListeners = 0;
/*private*/ /*static*/ int DefaultAudioManager::countSources = 0;
/*private*/ /*static*/ int DefaultAudioManager::countBuffers = 0;

/**
 * Reference to the currently active AudioFactory
 */
/*private*/ /*static*/ AudioFactory* DefaultAudioManager::activeAudioFactory = nullptr;

/*private*/ /*static*/ bool DefaultAudioManager::_initialised = false;


//@Override
/*public*/ int DefaultAudioManager::getXMLOrder() const {
    return Manager::AUDIO;
}

//@Override
/*public*/ QString DefaultAudioManager::getSystemPrefix() const {
    return "I";
}

//@Override
/*protected*/ Audio* DefaultAudioManager::createNewAudio(QString systemName, QString userName) /*throws AudioException*/
{

 if (activeAudioFactory == nullptr)
 {
  log->debug("Initialise in createNewAudio");
  init();
 }

 Audio* a = nullptr;
 log->debug("sysName: " + systemName + " userName: " + userName);
 if (userName != "" && _tuser->contains(userName))
 {
  throw new AudioException("Duplicate name");
 }

 //    switch (systemName.at(2)) {
 QChar st = systemName.at(2);
 //        case Audio::BUFFER: {
 if(st == Audio::BUFFER)
 {
  if (countBuffers >= MAX_BUFFERS)
  {
   log->error("Maximum number of buffers reached (" +    QString::number(countBuffers) + ") " + QString::number(MAX_BUFFERS));
   //                throw new AudioException("Maximum number of buffers reached (" + countBuffers + ") " + MAX_BUFFERS);
  }
  countBuffers++;
  a = activeAudioFactory->createNewBuffer(systemName, userName);
  buffers.insert(a);
 //            break;
 }
 //        case Audio::LISTENER: {
 else if(st == Audio::LISTENER)
 {
  if (countListeners >= MAX_LISTENERS)
  {
   log->error("Maximum number of Listeners reached (" +  QString::number(countListeners) + ") " + QString::number(MAX_LISTENERS));
  //                throw new AudioException("Maximum number of Listeners reached (" + countListeners + ") " + MAX_LISTENERS);
  }
  countListeners++;
  a = (Audio*)activeAudioFactory->createNewListener(systemName, userName);
  listeners.insert(a);
  //            break;
 }
 //        case Audio::SOURCE: {
 else if(st == Audio::SOURCE)
 {
  if (countSources >= MAX_SOURCES)
  {
   log->error("Maximum number of Sources reached (" + QString::number(countSources) + ") " + QString::number(MAX_SOURCES));
 //     throw new AudioException("Maximum number of Sources reached (" + countSources + ") " + MAX_SOURCES);
  }
  countSources++;
  a = (Audio*)activeAudioFactory->createNewSource(systemName, userName);
  sources.insert(a);
 //            break;
 }
 //        default:
 //            throw new IllegalArgumentException();
 //    }

 return a;
}

//@Deprecated
//@Override
/*public*/ QStringList DefaultAudioManager::getSystemNameList(int subType) {
    return this->getSystemNameList((QChar) subType);
}

//@Override
/*public*/ QStringList DefaultAudioManager::getSystemNameList(QChar subType) {
    QStringList tempList = AbstractManager::getSystemNameList();
    QStringList out = QStringList();
    for (int i = 0; i < tempList.size(); i++) {
        Audio* audio = this->getBySystemName(tempList.at(i));
        if (audio->getSubType() == subType) {
            out.append(tempList.at(i));
        }
    }
    return out;
}
/*public*/ QSet<NamedBean*> DefaultAudioManager::getNamedBeanSet(QChar subType) {
// switch (subType)
// {
//     case Audio::BUFFER: {
//         return Collections.unmodifiableSortedSet(buffers);
//     }
//     case Audio::LISTENER: {
//         return Collections.unmodifiableSortedSet(listeners);
//     }
//     case Audio::SOURCE: {
//         return Collections.unmodifiableSortedSet(sources);
//     }
//     default: {
//         throw IllegalArgumentException();
//     }
// }
 if(subType == Audio::BUFFER)
  return QSet<NamedBean*>(buffers);
 else if(subType == Audio::LISTENER)
  return QSet<NamedBean*>(listeners);
 else if(subType == Audio::SOURCE)
  return QSet<NamedBean*>(sources);
 else  throw IllegalArgumentException();
}

/**
 * Method used to initialise the manager
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
// OK to write to static variables as we only do so if not initialised
//@Override
/*public*/ /*synchronized*/ void DefaultAudioManager::init()
{
 if (!_initialised)
 {
//            // First try to initialise LWJGL
//            activeAudioFactory = new LWJGLAudioFactory();
//            log->debug("Try to initialise LWJGLAudioFactory");
//
//            // If LWJGL fails, fall-back to JOAL
//            if (!activeAudioFactory.init()) {
#if 0
        activeAudioFactory = new JoalAudioFactory();
        log->debug("Try to initialise JoalAudioFactory");
#endif
  // If JOAL fails, fall-back to JavaSound
  if (activeAudioFactory == nullptr || !activeAudioFactory->init())
  {
   activeAudioFactory = new QtSoundAudioFactory();
   log->debug("Try to initialise JavaSoundAudioFactory");

   // Finally, if JavaSound fails, fall-back to a Null sound system
   if (activeAudioFactory == nullptr || !activeAudioFactory->init())
   {
    activeAudioFactory = new NullAudioFactory();
    log->debug("Try to initialise NullAudioFactory");
    activeAudioFactory->init();
   }
  }
//            }

  // Create default Listener and save in map
  try
  {
   Audio* s = createNewAudio("IAL$", "Default Audio Listener");
   if(s != nullptr)
    Register(s);
  }
  catch (AudioException ex)
  {
   log->error("Error creating Default Audio Listener: " + ex.getMessage());
  }

  // Finally, create and register a shutdown task to ensure clean exit
#if 1
  if (audioShutDownTask == nullptr)
  {
   audioShutDownTask = new AudioShutDownTask("AudioFactory Shutdown");
//   {
//    //@Override
//    /*public*/ bool doAction()
//    {
//     InstanceManager::audioManagerInstance().cleanUp();
//     return true;
//     }
//    };
   }
#endif
   if (InstanceManager::getNullableDefault("ShutDownManager") != nullptr)
   {
    ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->_register(audioShutDownTask);
   }

  _initialised = true;
  if (log->isDebugEnabled())
  {
    log->debug("Initialised AudioFactory type: " + QString(activeAudioFactory->/*getClass().getSimpleName()*/metaObject()->className()));
  }
 }
}
AudioShutDownTask::AudioShutDownTask(QString name) : QuietShutDownTask(name)
{

}

bool AudioShutDownTask::doAction()
{
 ((AudioManager*)InstanceManager::getDefault("AudioManager"))->cleanup();
 return true;
}

//@Override
/*public*/ void DefaultAudioManager::deregister(NamedBean* s)const {
    AbstractAudioManager::deregister(s);
    // Decrement the relevant Audio object counter
//    switch (((Audio*) s)->getSubType()) {
//        case (Audio::BUFFER): {
//            countBuffers--;
//            break;
//        }
//        case (Audio::SOURCE): {
//            countSources--;
//            break;
//        }
//        case (Audio::LISTENER): {
//            countListeners--;
//            break;
//        }
//        default:
//            throw new IllegalArgumentException();
//    }
    QChar st = ((Audio*) s)->getSubType();
    if(st == Audio::BUFFER)
     countBuffers--;
    if(st== Audio::SOURCE)
     countSources--;
    if(st == Audio::LISTENER)
     countListeners--;

}

//@Override
/*public*/ void DefaultAudioManager::cleanUp() {
    // Shutdown AudioFactory and close the output device
    log->info("Shutting down active AudioFactory");
    activeAudioFactory->cleanup();
}

//@Override
/*public*/ AudioFactory* DefaultAudioManager::getActiveAudioFactory() {
 if(!_initialised)
  init();
 return activeAudioFactory;
}

/**
 * Return the current instance of this object.
 * <p>
 * If not existing, create a new instance.
 *
 * @return reference to currently active AudioManager
 */
/*public*/ /*static*/ DefaultAudioManager* DefaultAudioManager::instance() {
 return (DefaultAudioManager*)InstanceManager::getDefault("DefaultAudioManager");
}

