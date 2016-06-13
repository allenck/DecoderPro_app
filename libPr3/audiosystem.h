#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <QObject>

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

signals:

public slots:
private:
 /*private*/ AudioSystem(QObject *parent = 0);
 /*private*/ static QList<AudioFileReader*>* getAudioFileReaders();
 Logger* log;
};

#endif // AUDIOSYSTEM_H
