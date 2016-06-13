#ifndef WAVFILEREADER_H
#define WAVFILEREADER_H

#include "audiofilereader.h"
#include <QAudioFormat>
#include "audiofilereader.h"
#include <QAudio>

class QEventLoop;
class FileFormat;
class WavFileReader : public AudioFileReader
{
 Q_OBJECT
public:
 explicit WavFileReader(QObject *parent = 0);
 void readWAV(QString wavFile);
 /*public*/ AudioFileFormat* getAudioFileFormat(File* file);
 /*public*/ AudioFileFormat* getAudioFileFormat(QDataStream* stream);
 /*public*/ AudioInputStream* getAudioInputStream(File *);
 /*public*/ AudioInputStream* getAudioInputStream(QDataStream* stream);

signals:

public slots:
 void onStateChanged(QAudio::State s);

private:
 QAudioFormat f;\
 Logger* log;
 QByteArray* ba;
 QEventLoop* loop;
};

#endif // WAVFILEREADER_H
