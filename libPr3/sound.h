#ifndef SOUND_H
#define SOUND_H

#include <QObject>
#include "exceptions.h"
#include "runnable.h"
#include <QSound>

class URISyntaxException;
class UnsupportedAudioFileException;
class SourceDataLine;
class Sensor;
class AudioFormat;
class AudioInputStream;
class File;
class Clip;
class Logger;
class Sound : public QSound
{
 Q_OBJECT
public:
 explicit Sound(QString path, QObject *parent = nullptr) throw (NullPointerException);
 /*public*/ static /*final*/ long LARGE_SIZE;// = 100000;
 /*public*/ Sound(/*@Nonnull*/ File* file, QObject *parent =nullptr) throw (MalformedURLException);
 /*public*/ Sound(/*@Nonnull*/ QUrl* url, QObject *parent = nullptr) throw (NullPointerException);
 /*public*/ void play();
 /*public*/ void loop();
 /*public*/ void loop(int count);
 /*public*/ void stop();
// /*public*/ static void playSoundBuffer(QByteArray wavData);

signals:

public slots:

private:
 /*private*/ /*final*/ QUrl* url;
// /*private*/ bool streaming = false;
// /*private*/ bool streamingStop = false;
// /*private*/ Clip* clip = nullptr;
 static Logger* log;
// void common(QUrl* url);
// /*private*/ bool needStreaming() throw (URISyntaxException, IOException);
 QString path;

};
#if 0
/*public*/ /*static*/ class WavBuffer {

    /*public*/ WavBuffer(QByteArray content);
private:
 static Logger* log;
    // we maintain this, but don't use it for anything yet
    //@SuppressFBWarnings(value = "URF_UNREAD_FIELD")
    int fmtOffset;

    QByteArray buffer;

    float getSampleRate() ;
    int getSampleSizeInBits() ;
    int getChannels();
    bool getBigEndian();
    bool getSigned();
};

/*public*/ class StreamingSound : public Runnable {

    /*private*/ /*final*/ QUrl* url;
    /*private*/ AudioInputStream* stream = nullptr;
    /*private*/ AudioFormat* format = nullptr;
    /*private*/ SourceDataLine* line = nullptr;
    /*private*/ Sensor* streamingSensor = nullptr;
 static Logger* log;

public:
    /**
     * A runnable to stream in sound and play it This method does not read
     * in an entire large sound file at one time, but instead reads in
     * smaller chunks as needed.
     *
     * @param url the URL containing audio media
     */
    /*public*/ StreamingSound(QUrl* url);
    /*public*/ void run();
private:
    /*private*/ void setSensor(int mode);

};
#endif
#endif // SOUND_H
