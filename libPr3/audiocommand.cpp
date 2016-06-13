#include "audiocommand.h"
#include "audio.h"

//AudioCommand::AudioCommand(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Represents a queued command for later processing in the AudioController
 * thread.
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
// /*public*/ class AudioCommand {


/**
 * Constructor to process a command on an Audio object
 *
 * @param audio   Audio object to process
 * @param command Action to perform
 */
/*public*/ AudioCommand::AudioCommand(Audio* audio, int command, QObject *parent) :
  QObject(parent)
{
    this->audio = audio;
    this->command = command;
}

/**
 * Return the Audio object that this command refers to
 *
 * @return Audio object to process
 */
/*public*/ /*synchronized*/ Audio* AudioCommand::getAudio() {
    return this->audio;
}

/**
 * Return the action to perform
 *
 * @return Action
 */
/*public*/ /*synchronized*/ int AudioCommand::getCommand() {
    return this->command;
}

//@Override
/*public*/ QString AudioCommand::toString() {
    if (this->audio != NULL) {
        return "Command " + commandString() + " for Audio " + audio->getSystemName();
    } else {
        return "Command " + commandString() + " for NULL object";
    }
}

/**
 * Returns a string representation of the assigned command
 *
 * @return a string representation
 */
/*private*/ QString AudioCommand::commandString()
{
 switch (this->command)
 {
  case Audio::CMD_INIT_FACTORY:
      return "Initialise Factory (0x" + QString::number(this->command,16,16) + ")";
  case Audio::CMD_LOAD_SOUND:
      return "Load Sound (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_BIND_BUFFER:
      return "Bind buffer (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_QUEUE_BUFFERS:
      return "Queue buffers (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_UNQUEUE_BUFFERS:
      return "Unqueue buffers (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_PLAY:
      return "Play (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_PAUSE:
      return "Pause (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_PLAY_TOGGLE:
      return "Play/Stop toggle (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_PAUSE_TOGGLE:
      return "Pause/Resume toggle (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_RESUME:
      return "Resume (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_STOP:
      return "Stop (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_REWIND:
      return "Rewind (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_FADE_IN:
      return "Fade-in (0x" + QString::number(this->command,16) + ")";
  case Audio::CMD_FADE_OUT:
      return "Fade-out (0x" + QString::number(this->command,16) + ")";
  default:
         return "Unknown (0x" + QString::number(this->command,16) + ")";
 }
}
