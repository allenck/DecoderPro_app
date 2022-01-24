#include "qtsoundaudiobuffer.h"
#include "QAudioFormat"
#include "file.h"
#include "fileutil.h"
#include "audiosystem.h"
#include "audioinputstream.h"

//QtSoundAudioBuffer::QtSoundAudioBuffer(QObject *parent) :
//  AbstractAudioBuffer(parent)
//{
//}
/**
 * JavaSound implementation of the Audio Buffer sub-class.
 * <P>
 * For now, no system-specific implementations are forseen - this will remain
 * internal-only
 * <p>
 * For more information about the JavaSound API, visit
 * <a href="http://java.sun.com/products/java-media/sound/">http://java.sun.com/products/java-media/sound/</a>
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
// /*public*/ class JavaSoundAudioBuffer extends AbstractAudioBuffer {


/**
 * Constructor for new JavaSoundAudioBuffer with system name
 *
 * @param systemName AudioBuffer object system name (e.g. IAB4)
 */
/*public*/QtSoundAudioBuffer:: QtSoundAudioBuffer(QString systemName, QObject *parent)
 : AbstractAudioBuffer(systemName, parent)
{
 //super(systemName);
 common();
 if (log->isDebugEnabled()) {
     log->debug("New QtSoundAudioBuffer: " + systemName);
 }
 _initialised = init();
}

/**
 * Constructor for new JavaSoundAudioBuffer with system name and user name
 *
 * @param systemName AudioBuffer object system name (e.g. IAB4)
 * @param userName   AudioBuffer object user name
 */
/*public*/ QtSoundAudioBuffer::QtSoundAudioBuffer(QString systemName, QString userName, QObject *parent)
: AbstractAudioBuffer(systemName, userName,  parent)
{
 //super(systemName, userName);
 common();
 if (log->isDebugEnabled()) {
     log->debug("New QtSoundAudioBuffer: " + userName + " (" + systemName + ")");
 }
 _initialised = init();
}
void QtSoundAudioBuffer::common()
{
 log = new Logger("QtSoundAudioBuffer");
 log->setDebugEnabled(true);
 _initialised = false;
}

/**
 * Performs any necessary initialisation of this AudioBuffer
 *
 * @return True if successful
 */
/*private*/ bool QtSoundAudioBuffer::init() {
    this->_audioFormat = NULL;
    _dataStorageBuffer = NULL;
    this->_freq = 0;
    this->_size = 0;
    this->setStartLoopPoint(0, false);
    this->setEndLoopPoint(0, false);
    this->setState(STATE_EMPTY);
    return true;
}

/**
 * Return reference to the DataStorageBuffer byte array
 * <p>
 * Applies only to sub-types:
 * <ul>
 * <li>Buffer
 * </u>
 *
 * @return buffer[] reference to DataStorageBuffer
 */
/*protected*/ QByteArray* QtSoundAudioBuffer::getDataStorageBuffer() {
    return _dataStorageBuffer;
}

/**
 * Retrieves the format of the sound sample stored in this buffer as an
 * AudioFormat object
 *
 * @return audio format as an AudioFormat object
 */
/*protected*/ QAudioFormat* QtSoundAudioBuffer::getAudioFormat()
{
 return _audioFormat;
}

//@Override
/*public*/ QString QtSoundAudioBuffer::toString()
{
 if (this->getState() != STATE_LOADED)
 {
  return "Empty buffer";
 }
 else
 {
  return this->getURL() + " (" + parseFormat() + ", " + QString::number(this->_freq) + " Hz)";
 }
}

//@Override
/*protected*/ bool QtSoundAudioBuffer::loadBuffer(QDataStream* stream)
{
 if (!_initialised)
 {
  return false;
 }

 // Reinitialise
 init();

 // Create the input stream for the audio file
//    try {
 _audioInputStream = AudioSystem::getAudioInputStream(stream);
//    } catch (UnsupportedAudioFileException ex) {
//        log->error("Unsupported audio file format when loading buffer:" + ex);
//        return false;
//    } catch (IOException* ex) {
//        log->error("Error loading buffer:" + ex);
//        return false;
//    }

 return (this->processBuffer());
}

//@Override
/*protected*/ bool QtSoundAudioBuffer::loadBuffer()
{
 if (!_initialised)
 {
  return false;
 }

 // Reinitialise
 init();

 // Retrieve filename of specified .wav file
 File* file = new File(FileUtil::getExternalFilename(this->getURL()));

 // Create the input stream for the audio file
// try
// {
  _audioInputStream = AudioSystem::getAudioInputStream(file);
// } catch (UnsupportedAudioFileException ex) {
//     log->error("Unsupported audio file format when loading buffer:" + ex);
//     return false;
// } catch (IOException* ex) {
//     log->error("Error loading buffer:" + ex);
//     return false;
// }
 return (this->processBuffer());
}

/*private*/ bool QtSoundAudioBuffer::processBuffer()
{

 // Temporary storage buffer
 QByteArray* buffer;

 // Get the AudioFormat
 if(_audioInputStream == NULL)
 {
  log->error("cannot process buffer, stream = NULL");
  return false;
 }
 _audioFormat = _audioInputStream->getFormat();
 this->_freq = (int) _audioFormat->sampleRate();

 // Determine the required buffer size in bytes
 // number of channels * length in frames * sample size in bits / 8 bits in a byte
 int dataSize = _audioFormat->channelCount()
         * (int) _audioInputStream->getFrameLength()
         * _audioFormat->sampleSize() / 8;
 if (log->isDebugEnabled()) {
     log->debug("Size of QtSoundAudioBuffer (" + this->getSystemName() + ") = " + QString::number(dataSize));
 }
 if (dataSize > 0)
 {
  // Allocate buffer space
  buffer = new QByteArray(dataSize, 0);

  // Load into data buffer
  int bytesRead = 0, totalBytesRead = 0;
  try
  {
   // Read until end of audioInputStream reached
   log->debug("Start to load QtSoundBuffer...");
   while ((bytesRead = _audioInputStream->read(buffer,
                   totalBytesRead,
                   buffer->length() - totalBytesRead))
          != -1 && totalBytesRead < buffer->length())
   {
    log->debug("read " + QString::number(bytesRead) + " bytes of total " + QString::number(dataSize));
    totalBytesRead += bytesRead;
   }
  }
  catch (IOException* ex)
  {
   log->error("Error when reading QtSoundAudioBuffer (" + this->getSystemName() + ") " + ex->getMessage());
   return false;
  }

  // Done. All OK.
  log->debug("...finished loading QtSoundBuffer");
 }
 else
 {
  // Not loaded anything
  log->warn("Unable to determine length of QtSoundAudioBuffer (" + this->getSystemName() + ")");
  log->warn(" - buffer has not been loaded.");
  return false;
 }

 // Done loading - need to convert byte endian order
 this->_dataStorageBuffer = convertAudioEndianness(buffer, _audioFormat->sampleSize() == 16);

 // Set initial loop points
 this->setStartLoopPoint(0, false);
 this->setEndLoopPoint(_audioInputStream->getFrameLength(), false);
 this->generateLoopBuffers(LOOP_POINT_BOTH);

 // Store length of sample
 this->_size = _audioInputStream->getFrameLength();

 this->setState(STATE_LOADED);
 _dataStorageBuffer = buffer;
 if (log->isDebugEnabled()) {
     log->debug("Loaded buffer: " + this->getSystemName());
     log->debug(" from file: " + this->getURL());
     log->debug(" format: " + parseFormat() + ", " + QString::number(_freq) + " Hz");
     log->debug(" length: " + (QString::number(_audioInputStream->getFrameLength())));
 }
 return true;

}

//@Override
/*protected*/ void QtSoundAudioBuffer::generateLoopBuffers(int which) {
    // TODO: Actually write this bit
    //if ((which==LOOP_POINT_START)||(which==LOOP_POINT_BOTH)) {
    //}
    //if ((which==LOOP_POINT_END)||(which==LOOP_POINT_BOTH)) {
    //}
    if (log->isDebugEnabled()) {
        log->debug("Method generateLoopBuffers() called for JavaSoundAudioBuffer " + this->getSystemName());
    }
}

//@Override
/*protected*/ bool QtSoundAudioBuffer::generateStreamingBuffers() {
    // TODO: Actually write this bit
    if (log->isDebugEnabled()) {
        log->debug("Method generateStreamingBuffers() called for JavaSoundAudioBuffer " + this->getSystemName());
    }
    return true;
}

//@Override
/*protected*/ void QtSoundAudioBuffer::removeStreamingBuffers() {
    // TODO: Actually write this bit
    if (log->isDebugEnabled()) {
        log->debug("Method removeStreamingBuffers() called for JavaSoundAudioBuffer " + this->getSystemName());
    }
}

//@Override
/*public*/ int QtSoundAudioBuffer::getFormat() {
    if (_audioFormat != NULL) {
        if (_audioFormat->channelCount() == 1 && _audioFormat->sampleSize() == 8) {
            return FORMAT_8BIT_MONO;
        } else if (_audioFormat->channelCount() == 1 && _audioFormat->sampleSize() == 16) {
            return FORMAT_16BIT_MONO;
        } else if (_audioFormat->channelCount() == 2 && _audioFormat->sampleSize() == 8) {
            return FORMAT_8BIT_STEREO;
        } else if (_audioFormat->channelCount() == 2 && _audioFormat->sampleSize() == 16) {
            return FORMAT_16BIT_STEREO;
        } else {
            return FORMAT_UNKNOWN;
        }
    }
    return FORMAT_UNKNOWN;
}

//@Override
/*public*/ long QtSoundAudioBuffer::getLength() {
    return this->_size;
}

//@Override
/*public*/ int QtSoundAudioBuffer::getFrequency() {
    return this->_freq;
}

/**
 * Internal method to return a string representation of the audio format
 *
 * @return string representation
 */
/*private*/ QString QtSoundAudioBuffer::parseFormat() {
    switch (this->getFormat()) {
        case FORMAT_8BIT_MONO:
            return "8-bit mono";
        case FORMAT_16BIT_MONO:
            return "16-bit mono";
        case FORMAT_8BIT_STEREO:
            return "8-bit stereo";
        case FORMAT_16BIT_STEREO:
            return "16-bit stereo";
        default:
            return "unknown format";
    }
}

/**
 * Converts the endianness of an AudioBuffer to the format required by the
 * JRE.
 *
 * @param audioData      byte array containing the read PCM data
 * @param twoByteSamples true if 16-bits per sample
 * @return byte array containing converted PCM data
 */
/*private*/ /*static*/ QByteArray* QtSoundAudioBuffer::convertAudioEndianness(QByteArray* audioData, bool twoByteSamples)
{
#if 0
    // Create ByteBuffer for output and set endianness
    ByteBuffer out = ByteBuffer.allocate(audioData.length);
    out.order(ByteOrder.nativeOrder());

    // Wrap the audioData into a ByteBuffer for input and set endianness
    // (always Little Endian for a WAV file)
    ByteBuffer in = ByteBuffer.wrap(audioData);
    in.order(ByteOrder.LITTLE_ENDIAN);

    // Check if we have double-byte samples (i.e. 16-bit)
    if (twoByteSamples) {
        // If so, create ShortBuffer views of the in and out ByteBuffers
        // for further processing
        ShortBuffer outShort = out.asShortBuffer();
        ShortBuffer inShort = in.asShortBuffer();

        // Loop through appending data to the output buffer
        while (inShort.hasRemaining()) {
            outShort.put(inShort.get());
        }

    } else {
        // Otherwise, just loop through appending data to the output buffer
        while (in.hasRemaining()) {
            out.put(in.get());
        }
    }

    // Rewind the ByteBuffer
    out.rewind();

    // Convert output to an array if necessary
    if (!out.hasArray()) {
        // Allocate space
        byte[] array = new byte[out.capacity()];
        // fill the array
        out.get(array);
        // clear the ByteBuffer
        out.clear();

        return array;
    }

    return out.array();
#else
    return audioData;
#endif
}

//@Override
/*protected*/ void QtSoundAudioBuffer::cleanUp() {
    if (log->isDebugEnabled()) {
        log->debug("Cleanup JavaSoundAudioBuffer (" + this->getSystemName() + ")");
    }
    this->dispose();
}
