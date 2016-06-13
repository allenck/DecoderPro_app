#ifndef WAVBUFFER_H
#define WAVBUFFER_H

#include <QObject>
#include <QAudio>

class QEventLoop;
class Logger;
class File;
class WavBuffer : public QObject
{
 Q_OBJECT
public:
 //explicit WavBuffer(QObject *parent = 0);
 /*public*/ WavBuffer(QVector<char>* content, QObject *parent = 0);
 /*public*/ WavBuffer(File* file, QObject *parent = 0) /*throws java.io.IOException*/ ;
 /*public*/ int findHeader(int i1, int i2, int i3, int i4);
 /*public*/ float getSampleRate();
 /*public*/ int getSampleSizeInBits();
 /*public*/ int getChannels();
 /*public*/ bool getBigEndian();
 /*public*/ bool getSigned();
 /*public*/ int getDataStart();
 /*public*/ int getDataSize();
 /*public*/ int getDataEnd();
 /*public*/ QVector<char>* getByteArray();
 void play();

signals:

public slots:
 void onStateChanged(QAudio::State);

private:
 /*private*/ void initFmt();
 /*private*/ void initData();
 int fmtOffset;
 int dataOffset;

 QVector<char>* buffer;
 Logger* log;
 int fourByte(int index) ;
 int twoByte(int index);
 QEventLoop* loop;
};

#endif // WAVBUFFER_H
