#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <QObject>
#include "line.h"
#include "mixer.h"

class Logger;
class AudioFileReader;
class File;
class QAudioFormat;
class AudioInputStream;
class AudioSystem : public QObject
{
 Q_OBJECT
public:
 //explicit AudioSystem(QObject *parent = 0);
 /*public*/ static /*final*/ int NOT_SPECIFIED;// = -1;
 /*public*/ static AudioInputStream* getAudioInputStream(QString targetEncoding,
                                                    AudioInputStream* sourceStream);
 /*public*/ static AudioInputStream* getAudioInputStream(File* file);
 // /*public*/ static AudioFileFormat* getAudioFileFormat(QDataStream* stream);
 /*public*/ static AudioInputStream* getAudioInputStream(QDataStream* stream);
 /*public*/ static bool isLineSupported(Line::Info* info);
 /*public*/ static QList<Mixer::Info *>* getMixerInfo();
 /*public*/ static Mixer* getMixer(Mixer::Info *info);

signals:

public slots:
private:
 /*private*/ AudioSystem(QObject *parent = 0);
 /*private*/ static QList<AudioFileReader*>* getAudioFileReaders();
 Logger* log;
 /*private*/ static QList<AudioFileReader*>* getMixerInfoList();
 /*private*/ static QList<AudioFileReader*>* getProviders(QString providerClass);
 /*private*/ static QList<AudioFileReader*>* getMixerInfoList(QList<AudioFileReader*>* providers);
 /*private*/ static QList<AudioFileReader*>* getMixerProviders();

};

#endif // AUDIOSYSTEM_H
