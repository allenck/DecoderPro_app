#ifndef QTSOUNDAUDIOBUFFER_H
#define QTSOUNDAUDIOBUFFER_H
#include "abstractaudiobuffer.h"

class AudioInputStream;
class QDataStream;
class QAudioFormat;
class Logger;
class QtSoundAudioBuffer : public AbstractAudioBuffer
{
 Q_OBJECT
public:
 //explicit QtSoundAudioBuffer(QObject *parent = 0);
 /*public*/ QtSoundAudioBuffer(QString systemName, QObject *parent = 0);
 /*public*/ QtSoundAudioBuffer(QString systemName, QString userName, QObject *parent = 0);
 /*public*/ QString toString();
 /*public*/ int getFormat();
 /*public*/ long getLength();
 /*public*/ int getFrequency();

signals:

public slots:
private:
 Logger* log;
 /**
  * Holds the AudioFormat of this buffer
  */
 /*private*/ /*transient*/ QAudioFormat* _audioFormat;

 /**
  * Byte array used to store the actual data read from the file
  */
 /*private*/ QByteArray* _dataStorageBuffer;

 /**
  * Frequency of this AudioBuffer. Used to calculate pitch changes
  */
 /*private*/ int _freq;

 /*private*/ long _size;

 /**
  * Reference to the AudioInputStream used to read sound data from the file
  */
 /*private*/ /*transient*/ AudioInputStream* _audioInputStream;

 /**
  * Holds the initialised status of this AudioBuffer
  */
 /*private*/ bool _initialised;// = false;
 void common();
 /*private*/ bool init();
 /*private*/ bool processBuffer();
 /*private*/ QString parseFormat();
 /*private*/ static QByteArray* convertAudioEndianness(QByteArray* audioData, bool twoByteSamples);

protected:
 /*protected*/ QByteArray* getDataStorageBuffer();
 /*protected*/ QAudioFormat* getAudioFormat();
 /*protected*/ bool loadBuffer(QDataStream* stream);
 /*protected*/ bool loadBuffer();
 /*protected*/ void generateLoopBuffers(int which);
 /*protected*/ bool generateStreamingBuffers();
 /*protected*/ void removeStreamingBuffers();
 /*protected*/ void cleanUp();
friend class QtSoundAudioFactory;
friend class QtSoundAudioSource;
friend class QtSoundAudioClip;
};

#endif // QTSOUNDAUDIOBUFFER_H
