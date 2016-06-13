#include "abstractaudiofactory.h"
#include <QLinkedList>
#include "audiocommandthread.h"
#include "exceptions.h"
#include "abstractaudiosource.h"
#include "abstractaudiobuffer.h"
#include "abstractaudiolistener.h"
#include "audiocommandthread.h"

AbstractAudioFactory::AbstractAudioFactory(QObject *parent) :
  AudioFactory(parent)
{
 log = new Logger("AbstractAudioFactory");
 log->setDebugEnabled(true);
}
/**
 * Abstract implementation of the AudioFactory class.
 * <p>
 * All code shared amongst the concrete AudioFactory classes is defined here.
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
///*public*/ abstract class AbstractAudioFactory implements AudioFactory {

/**
 * List of queued audio commands to process
 */
/*private*/ /*static*/ QList<AudioCommand*>* AbstractAudioFactory::commandQueue = new QList<AudioCommand*>();

/**
 * Boolean used to determine if this AudioFactory has been initialised
 */
/*private*/ /*static*/ bool AbstractAudioFactory::_initialised = false;

/**
 * Boolean used to determine if this AudioFactory should attenuate sources
 * based on their distance from the Listener
 */
/*private*/ /*static*/ bool AbstractAudioFactory::_distanceAttenuated = true;

/**
 * Reference to the separate thread used to process all AudioCommands
 */
/*private*/ /*static*/ AbstractAudioThread* AbstractAudioFactory::audioCommandThread = NULL;
//@edu.umd.cs.findbugs.annotations.SuppressWarnings("ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
//@Override
/*public*/ bool AbstractAudioFactory::init()
{
 if (_initialised) {
     log->debug("Already initialised");
     return true;
 }

 // Create the command queue
 commandQueue = new QList<AudioCommand*>();

 // Create and start the command thread
 audioCommandThread = new AudioCommandThread(this);
 //moveToThread(audioCommandThread);
 //connect(audioCommandThread, SIGNAL(executeCommand()), this, SLOT(audioCommandQueue()));
 connect(this, SIGNAL(queue_updated()), (AudioCommandThread*)audioCommandThread, SLOT(command_queued()));
 audioCommandThread->start();

 _initialised = true;
 return true;
}

//@Override
/*public*/ void AbstractAudioFactory::cleanup() {

    bool dieException = false;

    // End the command thread
    try {
        audioCommandThread->die();       // send the die signal to the thread
        audioCommandThread->exit(); // interrupt the thread to process die signal
    } catch (Exception e) {
        dieException = true;
    }

    if (!dieException) {
        // wait for up to 5 seconds for thread to end
        for (int i = 0; i < 50; i++) {
            if (!audioCommandThread->alive()) {
                break;
            }
            AbstractAudioThread::snooze(100);
        }
    }
}

//@Override
/*public*/ /*synchronized*/ bool AbstractAudioFactory::audioCommandQueue(AudioCommand* queueAudioCommand)
{
 if (queueAudioCommand == NULL)
 {
  log->debug("Processing command queue");
  // Process command queue
  AudioCommand* audioCommand;
  while (!commandQueue->isEmpty() && commandQueue->size() > 0)
  {
   audioCommand = commandQueue->at(0);
   commandQueue->removeAt(0);
   if (audioCommand != NULL)
   {
    if (log->isDebugEnabled())
    {
     log->debug("Process command: " + audioCommand->toString()
                + " (" + QString::number(commandQueue->size()) + " remaining)");
    }
    Audio* audio = audioCommand->getAudio();

    // Process AudioSource commands
    //if (audio instanceof AudioSource)
    if(dynamic_cast<AudioSource*>(audio) != NULL)
    {
     AbstractAudioSource* audioSource = (AbstractAudioSource*) audio;
     switch (audioCommand->getCommand())
     {
      case Audio::CMD_BIND_BUFFER:
          audioSource->setBound(audioSource->bindAudioBuffer(audioSource->getAssignedBuffer()));
          break;
      case Audio::CMD_QUEUE_BUFFERS:
          audioSource->setQueued(audioSource->queueAudioBuffers(audioSource->getQueuedBuffers()));
          break;
      case Audio::CMD_UNQUEUE_BUFFERS:
          audioSource->setQueued(audioSource->unqueueAudioBuffers());
          break;
      case Audio::CMD_PLAY:
          audioSource->doPlay();
          break;
      case Audio::CMD_STOP:
          audioSource->doStop();
          break;
      case Audio::CMD_PLAY_TOGGLE:
          audioSource->doTogglePlay();
          break;
      case Audio::CMD_PAUSE:
          audioSource->doPause();
          break;
      case Audio::CMD_RESUME:
          audioSource->doResume();
          break;
      case Audio::CMD_PAUSE_TOGGLE:
          audioSource->doTogglePause();
          break;
      case Audio::CMD_REWIND:
          audioSource->doRewind();
          break;
      case Audio::CMD_FADE_IN:
          audioSource->doFadeIn();
          break;
      case Audio::CMD_FADE_OUT:
          audioSource->doFadeOut();
          break;
      case Audio::CMD_RESET_POSITION:
          audioSource->doResetCurrentPosition();
          break;
      default:
          log->warn("Command " + audioCommand->toString()
                  + " not suitable for AudioSource (" + audioSource->getSystemName() + ")");
     }
    } // Process AudioBuffer commands
    else
     //if (audio instanceof AudioBuffer)
     if(qobject_cast<AudioBuffer*>(audio) != NULL)
     {
      AbstractAudioBuffer* audioBuffer = (AbstractAudioBuffer*) audio;
     switch (audioCommand->getCommand())
     {
      case Audio::CMD_LOAD_SOUND:
          audioBuffer->loadBuffer();
          break;
      default:
          log->warn("Command " + audioCommand->toString()
                  + " not suitable for AudioBuffer (" + audioBuffer->getSystemName() + ")");
     }
    } // Process AudioListener commands
    else
      //if (audio instanceof AudioListener)
      if(dynamic_cast<AudioListener*>(audio) != NULL)

    {
     AbstractAudioListener* audioListener = (AbstractAudioListener*) audio;
     switch (audioCommand->getCommand())
     {
      case Audio::CMD_RESET_POSITION:
          audioListener->doResetCurrentPosition();
          break;
      default:
          log->warn("Command " + audioCommand->toString()
                  + " not suitable for AudioListener (" + audioListener->getSystemName() + ")");
     }
    }
   }
  }
  return (!commandQueue->isEmpty() && commandQueue->size() > 0);
 }
 else
 {
  if (commandQueue == NULL)
  {
   log->warn("Audio commandQueue not initialised");
   return false;
  }
  commandQueue->append(queueAudioCommand);
  emit queue_updated(); // wake up the command thread.

  if (log->isDebugEnabled())
  {
   log->debug("New audio command: " + queueAudioCommand->toString());
  }
  return true;
 }
}

//@Override
/*public*/ QThread* AbstractAudioFactory::getCommandThread()
{
 return audioCommandThread;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings("ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
//@Override
/*public*/ void AbstractAudioFactory::setDistanceAttenuated(bool attenuated) {
    _distanceAttenuated = attenuated;
}

//@Override
/*public*/ bool AbstractAudioFactory::isDistanceAttenuated() {
    return _distanceAttenuated;
}
