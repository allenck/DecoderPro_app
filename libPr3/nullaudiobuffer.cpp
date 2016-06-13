#include "nullaudiobuffer.h"

//NullAudioBuffer::NullAudioBuffer(QObject *parent) :
//  AbstractAudioBuffer(parent)
//{
//}
/**
 * Null implementation of the Audio Buffer sub-class.
 * <P>
 * For now, no system-specific implementations are forseen - this will remain
 * internal-only
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
 * @author Matthew Harris copyright (c) 2009, 2011
 * @version $Revision: 28771 $
 */
///*public*/ class NullAudioBuffer extends AbstractAudioBuffer {

/**
 *
 */
// /*private*/ static final long serialVersionUID = -2227618459689268908L;

/**
 * Constructor for new NullAudioBuffer with system name
 *
 * @param systemName AudioBuffer object system name (e.g. IAB4)
 */
/*public*/ NullAudioBuffer::NullAudioBuffer(QString systemName, QObject *parent) :
  AbstractAudioBuffer(systemName, parent)
{
 //super(systemName);
 common();
 if (log->isDebugEnabled())
 {
  log->debug("New NullAudioBuffer: " + systemName);
 }
}

/**
 * Constructor for new NullAudioBuffer with system name and user name
 *
 * @param systemName AudioBuffer object system name (e.g. IAB4)
 * @param userName   AudioBuffer object user name
 */
/*public*/ NullAudioBuffer::NullAudioBuffer(QString systemName, QString userName, QObject *parent) :
  AbstractAudioBuffer(systemName, userName, parent)
{
 //super(systemName, userName);
 common();
 if (log->isDebugEnabled())
 {
  log->debug("New NullAudioBuffer: " + userName + " (" + systemName + ")");
 }
}
void NullAudioBuffer::common()
{
 log = new Logger("NullAudioBuffer");
}

//@Override
/*public*/ QString NullAudioBuffer::toString()
{
 if (this->getState() != STATE_LOADED)
 {
  return "Empty buffer";
 }
 else
 {
  return this->getURL() + " (" + parseFormat() + ", " + "?? Hz)";
 }
}

//@Override
/*protected*/ bool NullAudioBuffer::loadBuffer(QDataStream* stream) {
 // No need to do this for the NullAudioBuffer - it's always successful ;-)
 return true;
}

//@Override
/*protected*/ bool NullAudioBuffer::loadBuffer()
{
 // No need to do this for the NullAudioBuffer - it's always successful ;-)
 return true;
}

//@Override
/*protected*/ void NullAudioBuffer::generateLoopBuffers(int which) {
 // No need to do anything for the NullAudioBuffer
}

//@Override
/*protected*/ bool NullAudioBuffer::generateStreamingBuffers()
{
 // No need to do this for the NullAudioBuffer - it's always successful ;-)
 return true;
}

//@Override
/*protected*/ void NullAudioBuffer::removeStreamingBuffers()
{
 // No need to do anything for the NullAudioBuffer
}

//@Override
/*public*/ int NullAudioBuffer::getFormat()
{
 return FORMAT_UNKNOWN;
}

//@Override
/*public*/ long NullAudioBuffer::getLength()
{
 // Nothing stored for the NullAudioBuffer - always zero
 return 0;
}

//@Override
/*public*/ int NullAudioBuffer::getFrequency()
{
 // Nothing stored for the NullAudioBuffer - always zero
  return 0;
}

/**
 * Internal method to return a string representation of the audio format
 *
 * @return string representation
 */
/*private*/ QString NullAudioBuffer::parseFormat()
{
 return "unknown format";
}

//@Override
/*protected*/ void NullAudioBuffer::cleanUp()
{
 if (log->isDebugEnabled())
 {
  log->debug("Cleanup NullAudioBuffer (" + this->getSystemName() + ")");
 }
 this->dispose();
}
