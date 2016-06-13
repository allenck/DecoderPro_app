#include "audiocommandthread.h"
#include "audiofactory.h"

//AudioCommandThread::AudioCommandThread(QObject *parent) :
//  AbstractAudioThread(parent)
//{
//}
/**
 * Represents a thread for processing commands contained within AudioCommand
 * objects. All commands are processed in the order in which thet were queued
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
///*public*/ class AudioCommandThread extends AbstractAudioThread {

    /**
     * Reference to active audio factory
     */
//    private AudioFactory activeAudioFactory;

/**
 * Constructor that takes handle to current active audio factory object
 *
 * @param activeAudioFactory handle to activeAudioFactory
 */
/*public*/ AudioCommandThread::AudioCommandThread(AudioFactory* activeAudioFactory,QObject *parent) :
AbstractAudioThread(parent)
{
 //super();
 log = new Logger("AudioCommandThread");
 this->setObjectName("command-" + AbstractAudioThread::objectName());
 this->activeAudioFactory = activeAudioFactory;
 if (log->isDebugEnabled())
 {
  log->debug("Created AudioThread for AudioFactory " /*+ activeAudioFactory->toString()*/);
 }
}

/**
 * Main loop for processing commands. Starts out asleep, and also sleeps
 * once finished processing commands, so must be interrupted to process any
 * queued commands.
 */
//@Override
/*public*/ void AudioCommandThread::run()
{

// // Start out asleep (5 minutes)
// snooze(300000);
 exec();
}
void AudioCommandThread::command_queued()
{
 while (!dying() )
 {
  // Process the command queue
  if(!activeAudioFactory->audioCommandQueue(NULL))
   return;

//  // Wait for more commands (5 minutes)
//  if (!dying()) {
//      snooze(300000);
//  }
 }

 // Finish up
 if (log->isDebugEnabled())
 {
  log->debug("Clean up thread " + this->objectName());
 }
 cleanup();
}

/**
 * Shuts this thread down and clears references to created objects
 */
//@Override
/*protected*/ void AudioCommandThread::cleanup()
{

 // Thread is to shutdown
 die();

 // Clear references to objects
 this->activeAudioFactory = NULL;

 // Finalise cleanup in super-class
 AbstractAudioThread::cleanup();
}
