#include "sound.h"
#include "loggerfactory.h"
#include "fileutil.h"
#include "file.h"
#include "clip.h"
#include "audiosystem.h"
#include <QUrl>
#include "sensor.h"
#include "audioinputstream.h"
#include "audioformat.h"
#include "instancemanager.h"
#include "system.h"
#include "unsupportedaudiofileexception.h"
#include "urisyntaxexception.h"
#include "lineunavailableexception.h"
#include "audiosystem.h"

/**
 * Provide simple way to load and play sounds in JMRI.
 * <P>
 * This is placed in the jmri.jmrit package by process of elimination. It
 * doesn't belong in the base jmri package, as it's not a basic interface. Nor
 * is it a specific implementation of a basic interface, which would put it in
 * jmri.jmrix. It seems most like a "tool using JMRI", or perhaps a tool for use
 * with JMRI, so it was placed in jmri.jmrit.
 * <P>
 * @see jmri.jmrit.sound
 *
 * @author Bob Jacobsen Copyright (C) 2004, 2006
 * @author Dave Duchamp Copyright (C) 2011 - add streaming play of large files
 */
///*public*/ class Sound {

// files over this size will be streamed
/*public*/ /*static*/ /*final*/ long Sound::LARGE_SIZE = 100000;
/*private*/ /*final*/ /*static*/ Logger* Sound::log = LoggerFactory::getLogger("Sound");

/**
 * Create a Sound object using the media file at path
 *
 * @param path path, portable or absolute, to the media
 * @throws NullPointerException if path cannot be converted into a URL by
 *                              {@link jmri.util.FileUtilSupport#findURL(java.lang.String)}
 */
/*public*/ Sound::Sound(/*@Nonnull*/ QString path, QObject *parent) throw (NullPointerException)
 : QSound(path, parent)
{
// QUrl url = FileUtil::findURL(path);
// common(&url);
}

/**
 * Create a Sound object using the media file
 *
 * @param file reference to the media
 * @throws java.net.MalformedURLException if file cannot be converted into a
 *                                        valid URL
 */
/*public*/ Sound::Sound(/*@Nonnull*/ File* file, QObject *parent) throw (MalformedURLException)
 : QSound(file->getPath(),parent)
{
// QUrl url = FileUtil::findURL(file->getPath();
//    common(&url);
}

/**
 * Create a Sound object using the media URL
 *
 * @param url path to the media
 * @throws NullPointerException if URL is null
 */
/*public*/ Sound::Sound(/*@Nonnull*/ QUrl* url, QObject *parent) throw (NullPointerException)
 : QSound(url->fileName(), parent)
{
// common(url);
}

//void Sound::common(QUrl* url)
//{
//    if (url == nullptr) {
//        throw  NullPointerException();
//    }
//    this->url = url;
//    try {
//        this->clip = AudioSystem::getClip();
//        streaming = this->needStreaming();
//        if (!streaming) {
//            this->clip->open(AudioSystem::getAudioInputStream(this->url));
//        }
//    } catch (URISyntaxException ex) {
//        streaming = false;
//    } catch (IOException* ex) {
//        log->error(tr("Unable to open %1").arg(url->toDisplayString()));
//    } catch (LineUnavailableException ex) {
//        log->error("Unable to provide audio playback", ex);
//    } catch (UnsupportedAudioFileException ex) {
//        log->error(tr("%1 is not a recognised audio format").arg(url->toDisplayString()));
//    }
//}

/**
 * Play the sound once.
 */
/*public*/ void Sound::play() {
//    if (streaming) {
//        Runnable* streamSound = new StreamingSound(this->url);
//        QThread* tStream = new QThread(streamSound);
//        tStream->start();
//    } else {
//        this->clip->start();
//    }
 QSound::play();
}

/**
 * Play the sound as an endless loop
 */
/*public*/ void Sound::loop() {
//    this->loop(Clip::LOOP_CONTINUOUSLY);
 QSound::setLoops(QSound::Infinite);
 QSound::play();
}

/**
 * Play the sound in a loop count times. Use
 * {@link javax.sound.sampled.Clip#LOOP_CONTINUOUSLY} to create an endless
 * loop.
 *
 * @param count the number of times to loop
 */
/*public*/ void Sound::loop(int count) {
//    if (streaming) {
//        log->warn("Streaming this audio file, loop() not allowed");
//    } else {
//        this->clip->loop(count);
//    }
 QSound::setLoops(count);
 QSound::play();

}

/**
 * Stop playing a loop.
 */
/*public*/ void Sound::stop() {
//    if (streaming) {
//        streamingStop = true;
//    } else {
//        this->clip->stop();
//    }
 QSound::stop();
}
#if 0
/*private*/ bool Sound::needStreaming() throw (URISyntaxException, IOException ){
    if (url != nullptr) {
#if 0 // TODO:
        if ("file" == (this->url->getProtocol())) {
            return (new File(this->url.toURI()).length() > LARGE_SIZE);
        } else {
            return this->url->openConnection().getContentLengthLong() > LARGE_SIZE;
        }
#endif
    }
    return false;
}

/**
 * Play a sound from a buffer
 *
 * @param wavData data to play
 */
/*public*/ /*static*/ void Sound::playSoundBuffer(QByteArray wavData) {

    // get characteristics from buffer
    float sampleRate = 11200.0f;
    int sampleSizeInBits = 8;
    int channels = 1;
    bool _signed = (sampleSizeInBits > 8);
    bool bigEndian = true;

    AudioFormat* format = new AudioFormat(sampleRate, sampleSizeInBits, channels, _signed, bigEndian);
    SourceDataLine* line;
    DataLine::Info info = DataLine::Info("SourceDataLine", format); // format is an AudioFormat object
    if (!AudioSystem::isLineSupported(info)) {
        // Handle the error.
        log->warn("line not supported: " + info.toString());
        return;
    }
    // Obtain and open the line->
    try {
        line = (SourceDataLine*) AudioSystem::getLine(info);
        line->open(format);
    } catch (LineUnavailableException ex) {
        // Handle the error.
        log->error("error opening line: " + ex);
        return;
    }
    line->start();
    // write(byte[] b, int off, int len)
    line->write(wavData, 0, wavData.length());

}

///*public*/ static class WavBuffer {
/*static*/ Logger* WavBuffer::log = new LoggerFactory::getLogger("WavBuffer");
    /*public*/ WavBuffer::WavBuffer(QByteArray content) {
        //buffer = Arrays.copyOf(content, content.length);
        buffer = QByteArray(content);

        // find fmt chunk and set offset
        int index = 12; // skip RIFF header
        while (index < buffer.length()) {
            // new chunk
            if (buffer[index] == 0x66
                    && buffer[index + 1] == 0x6D
                    && buffer[index + 2] == 0x74
                    && buffer[index + 3] == 0x20) {
                // found it
                fmtOffset = index;
                return;
            } else {
                // skip
                index = index + 8
                        + buffer[index + 4]
                        + buffer[index + 5] * 256
                        + buffer[index + 6] * 256 * 256
                        + buffer[index + 7] * 256 * 256 * 256;
                System::out.println("index now " + index);
            }
        }
        log->error("Didn't find fmt chunk");

    }

//    // we maintain this, but don't use it for anything yet
//    @SuppressFBWarnings(value = "URF_UNREAD_FIELD")
//    int fmtOffset;

//    byte[] buffer;

    float WavBuffer::getSampleRate() {
        return 11200.0;
    }

    int WavBuffer::getSampleSizeInBits() {
        return 8;
    }

    int WavBuffer::getChannels() {
        return 1;
    }

    bool WavBuffer::getBigEndian() {
        return false;
    }

    bool WavBuffer::getSigned() {
        return (getSampleSizeInBits() > 8);
    }
//};

///*public*/ class StreamingSound implements Runnable {

//    /*private*/ final URL url;
//    /*private*/ AudioInputStream stream = null;
//    /*private*/ AudioFormat format = null;
//    /*private*/ SourceDataLine line = null;
//    /*private*/ jmri.Sensor streamingSensor = null;
    /*static*/ Logger* StreamingSound::log = new LoggerFactory::getLogger("StreamingSound");

    /**
     * A runnable to stream in sound and play it This method does not read
     * in an entire large sound file at one time, but instead reads in
     * smaller chunks as needed.
     *
     * @param url the URL containing audio media
     */
    /*public*/ StreamingSound::StreamingSound(QUrl* url) {
        this->url = url;
    }

    //@Override
    /*public*/ void StreamingSound::run() {
        // Note: some of the following is based on code from
        //      "Killer Game Programming in Java" by A. Davidson.
        // Set up the audio input stream from the sound file
        try {
            // link an audio stream to the sampled sound's file
            stream = AudioSystem::getAudioInputStream(url);
            format = stream->getFormat();
            log->debug("Audio format: " + format);
            // convert ULAW/ALAW formats to PCM format
            if ((format->getEncoding() == AudioFormat::Encoding::ULAW)
                    || (format->getEncoding() == AudioFormat::Encoding.ALAW)) {
                AudioFormat* newFormat
                        = new AudioFormat(AudioFormat::Encoding::PCM_SIGNED,
                                format->getSampleRate(),
                                format->getSampleSizeInBits() * 2,
                                format->getChannels(),
                                format->getFrameSize() * 2,
                                format->getFrameRate(), true);  // big endian
                // update stream and format details
                stream = AudioSystem.getAudioInputStream(newFormat, stream);
                System::out.println("Converted Audio format: " + newFormat);
                format = newFormat;
                log->debug("new converted Audio format: " + format);
            }
        } catch (UnsupportedAudioFileException e) {
            log->error("AudioFileException " + e.getMessage());
            return;
        } catch (IOException e) {
            log->error("IOException " + e.getMessage());
            return;
        }
        streamingStop = false;
        if (streamingSensor == nullptr) {
            streamingSensor = InstanceManager::sensorManagerInstance()->provideSensor("ISSOUNDSTREAMING");
        }

        setSensor(Sensor::ACTIVE);

        if (!streamingStop) {
            // set up the SourceDataLine going to the JVM's mixer
            try {
                // gather information for line creation
                DataLine::Info info
                        = new DataLine::Info("SourceDataLine", format);
                if (!AudioSystem::isLineSupported(info)) {
                    log->error("Audio play() does not support: " + format);
                    return;
                }
                // get a line of the required format
                line = (SourceDataLine) AudioSystem.getLine(info);
                line->open(format);
            } catch (Exception e) {
                log->error("Exception while creating Audio out " + e.getMessage());
                return;
            }
        }
        if (streamingStop) {
            line->close();
            setSensor(Sensor::INACTIVE);
            return;
        }
        // Read  the sound file in chunks of bytes into buffer, and
        //   pass them on through the SourceDataLine
        int numRead;
        QByteArray buffer = QByteArray(line->getBufferSize(), 0);
        log->debug("streaming sound buffer size = " + line->getBufferSize());
        line->start();
        // read and play chunks of the audio
        try {
            int offset;
            while ((numRead = stream.read(buffer, 0, buffer.length)) >= 0) {
                offset = 0;
                while (offset < numRead) {
                    offset += line->write(buffer, offset, numRead - offset);
                }
            }
        } catch (IOException e) {
            log->error("IOException while reading sound file " + e.getMessage());
        }
        // wait until all data is played, then close the line
        line->drain();
        line->stop();
        line->close();
        setSensor(Sensor::INACTIVE);
    }

    /*private*/ void StreamingSound::setSensor(int mode) {
        if (streamingSensor != nullptr) {
            try {
                streamingSensor->setState(mode);
            } catch (JmriException* ex) {
                log->error(tr("Exception while setting ISSOUNDSTREAMING sensor %1 to %2").arg(streamingSensor->getDisplayName()).arg(mode));
            }
        }
    }

}
#endif
