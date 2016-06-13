#include "abstractaudiobuffer.h"
#include "fileutil.h"

//AbstractAudioBuffer::AbstractAudioBuffer(QObject *parent) :
//  AbstractAudio(parent)
//{
//}
/**
 * Base implementation of the AudioBuffer class.
 * <p>
 * Specific implementations will extend this base class.
 * <p>
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
 * @author Matthew Harris copyright (c) 2009, 2011
 * @version $Revision: 28771 $
 */
// /*public*/ abstract class AbstractAudioBuffer extends AbstractAudio implements AudioBuffer {

/**
 *
 */
// /*private*/ static final long serialVersionUID = 8268569137224309135L;


//    /**
//     *
//     */
//    /*private*/ WaveFileReader _waveFile;
/**
 * Identifier of start loop point
 */
/*protected*/ /*static*/ /*final*/ int AbstractAudioBuffer::LOOP_POINT_START = 0x01;

/**
 * Identifier of end loop point
 */
/*protected*/ /*static*/ /*final*/ int AbstractAudioBuffer::LOOP_POINT_END = 0x02;

/**
 * Identifier of both loop points
 */
/*protected*/ /*static*/ /*final*/ int AbstractAudioBuffer::LOOP_POINT_BOTH = 0x03;

/**
 * Abstract constructor for new AudioBuffer with system name
 *
 * @param systemName AudioBuffer object system name (e.g. IAB4)
 */
/*public*/ AbstractAudioBuffer::AbstractAudioBuffer(QString systemName, QObject *parent)
 :  AbstractAudio(systemName, parent)
{
 //super(systemName);
 common();
}

/**
 * Abstract constructor for new AudioBuffer with system name and user name
 *
 * @param systemName AudioBuffer object system name (e.g. IAB4)
 * @param userName   AudioBuffer object user name
 */
/*public*/ AbstractAudioBuffer::AbstractAudioBuffer(QString systemName, QString userName, QObject *parent)
 :  AbstractAudio(systemName, userName, parent)
{
 //super(systemName, userName);
 common();
}

void AbstractAudioBuffer::common()
{
 _streamed = false;
 _streamedForced = false;
 this->setState(STATE_EMPTY);
 log = new Logger("AbstractAudioBuffer");
 _startLoopPoint = 0;
 _endLoopPoint = 0;
}

//@Override
/*public*/ QChar AbstractAudioBuffer::getSubType() {
    return BUFFER;
}

//@Override
/*public*/ QString AbstractAudioBuffer::getURL() {
    return this->_url;
}

//@Override
/*public*/ void AbstractAudioBuffer::setURL(QString url)
{
 if(FileUtil::isPortableFilename(url))
  this->_url = FileUtil::getPortableFilename(url);
 else
  this->_url = url;

 // Run the loadBuffer method on the main AWT thread to avoid any
 // potential issues with interrupted exceptions if run on the audio
 // command thread
 loadBuffer();
 if (log->isDebugEnabled()) {
     log->debug("Set url of Buffer " + this->getSystemName() + " to " + url);
 }
}

//@Override
/*public*/ void AbstractAudioBuffer::setInputStream(QDataStream* stream) {
    this->_url = "stream";

    loadBuffer(stream);
    if (log->isDebugEnabled()) {
        log->debug("Set inputstream of Buffer " + this->getSystemName() + " to stream");
    }
}

//@Override
/*public*/ int AbstractAudioBuffer::getFrameSize() {
    switch (this->getFormat()) {
        case AudioBuffer::FORMAT_8BIT_MONO:
            return 1;
        case AudioBuffer::FORMAT_8BIT_STEREO:
            return 2;
        case AudioBuffer::FORMAT_8BIT_QUAD:
            return 4;
        case AudioBuffer::FORMAT_8BIT_5DOT1:
            return 6;
        case AudioBuffer::FORMAT_8BIT_6DOT1:
            return 7;
        case AudioBuffer::FORMAT_8BIT_7DOT1:
            return 8;
        case AudioBuffer::FORMAT_16BIT_MONO:
            return 2;
        case AudioBuffer::FORMAT_16BIT_STEREO:
            return 4;
        case AudioBuffer::FORMAT_16BIT_QUAD:
            return 8;
        case AudioBuffer::FORMAT_16BIT_5DOT1:
            return 12;
        case AudioBuffer::FORMAT_16BIT_6DOT1:
            return 14;
        case AudioBuffer::FORMAT_16BIT_7DOT1:
            return 16;
        default: //AudioBuffer::FORMAT_UNKNOWN:
            return 0;
    }
}

/**
 * Method used to load the actual sound data into the buffer
 *
 * @return True if successful; False if not
 */
/*abstract*/ /*protected*/ bool AbstractAudioBuffer::loadBuffer() {return false;}

/**
 * Method used to load the actual sound data from an InputStream into the
 * buffer
 *
 * @param s InputStream containing sound data
 * @return True if successful; False if not
 */
/*abstract*/ /*protected*/ bool AbstractAudioBuffer::loadBuffer(QDataStream* /*s*/) {return false;}

//@Override
/*public*/ void AbstractAudioBuffer::setStartLoopPoint(long startLoopPoint) {
    this->setStartLoopPoint(startLoopPoint, true);
}

// Can be made abstract later.
/*public*/ bool AbstractAudioBuffer::loadBuffer(QByteArray /*b*/, int /*format*/, int /*frequency*/) {
    return (false);
}

/**
 * Internal method used to set the start loop point of this buffer with
 * optional generation of loop buffers
 *
 * @param startLoopPoint      position of start loop point in samples
 * @param generateLoopBuffers True if loop buffers to be generated
 */
/*protected*/ void AbstractAudioBuffer::setStartLoopPoint(long startLoopPoint, bool _generateLoopBuffers) {
    this->_startLoopPoint = startLoopPoint;
    if (_generateLoopBuffers) {
        generateLoopBuffers(LOOP_POINT_START);
    }
    if (log->isDebugEnabled()) {
        log->debug("Set start loop point of Buffer " + this->getSystemName() + " to " + startLoopPoint);
    }
}

//@Override
/*public*/ long AbstractAudioBuffer::getStartLoopPoint()
{
 return this->_startLoopPoint;
}

//@Override
/*public*/ void AbstractAudioBuffer::setEndLoopPoint(long endLoopPoint) {
    this->setEndLoopPoint(endLoopPoint, true);
}

/**
 * Internal method used to set the end loop point of this buffer with
 * optional generation of loop buffers
 *
 * @param endLoopPoint        position of end loop point in samples
 * @param generateLoopBuffers True if loop buffers to be generated
 */
/*protected*/ void AbstractAudioBuffer::setEndLoopPoint(long endLoopPoint, bool _generateLoopBuffers)
{
 this->_endLoopPoint = endLoopPoint;
 if (_generateLoopBuffers) {
     generateLoopBuffers(LOOP_POINT_END);
 }
 if (log->isDebugEnabled()) {
     log->debug("Set end loop point of Buffer " + this->getSystemName() + " to " + endLoopPoint);
 }
}

//@Override
/*public*/ long AbstractAudioBuffer::getEndLoopPoint()
{
 return this->_endLoopPoint;
}

//@Override
/*public*/ void AbstractAudioBuffer::setStreamed(bool streamed) {
    if (streamed) {
        log->warn("Streaming not yet supported!!");
        streamed = !streamed;
    }
    bool changed = this->_streamed != streamed;
    this->_streamed = this->_streamedForced == true ? true : streamed;
    if (log->isDebugEnabled()) {
        log->debug("Set streamed property of Buffer " + this->getSystemName() + " to " + streamed + "; changed = " + changed);
    }
    if (streamed && changed) {
        generateStreamingBuffers();
    } else if (!streamed && changed) {
        removeStreamingBuffers();
    }
}

//@Override
/*public*/ bool AbstractAudioBuffer::isStreamed() {
    return this->_streamed;
}

/**
 * Protected method used internally to modify the forced streaming flag
 *
 * @param streamedForced True if required; False if not
 */
/*protected*/ void AbstractAudioBuffer::setStreamedForced(bool streamedForced) {
    bool changed = this->_streamedForced == false && streamedForced == true;
    this->_streamedForced = streamedForced;
    if (log->isDebugEnabled()) {
        log->debug("Set streamedForced property of Buffer " + this->getSystemName() + " to " + streamedForced + "; changed = " + changed);
    }
    this->setStreamed(streamedForced == true ? true : this->_streamed);
    if (changed) {
        this->generateLoopBuffers(LOOP_POINT_BOTH);
    }
}

//@Override
/*public*/ bool AbstractAudioBuffer::isStreamedForced() {
    return this->_streamedForced;
}

/**
 * Method used to generate any necessary loop buffers.
 *
 * @param which the loop buffer to generate:
 * <br>{@link #LOOP_POINT_START} for the start loop buffer
 * <br>{@link #LOOP_POINT_END} for the end loop buffer
 * <br>{@link #LOOP_POINT_BOTH} for both loop buffers
 */
/*abstract*/ /*protected*/ void AbstractAudioBuffer::generateLoopBuffers(int /*which*/) {}

/**
 * Internal method used to generate buffers for streaming
 *
 * @return True if successful; False if not
 */
/*abstract*/ /*protected*/ bool AbstractAudioBuffer::generateStreamingBuffers() { return false;}

/**
 * Internal method used to remove streaming buffers
 */
/*abstract*/ /*protected*/ void AbstractAudioBuffer::removeStreamingBuffers() {}

//@Override
/*public*/ void AbstractAudioBuffer::stateChanged(int /*oldState*/) {
    // Move along... nothing to see here...
}
