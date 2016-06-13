#ifndef NULLAUDIOBUFFER_H
#define NULLAUDIOBUFFER_H
#include "abstractaudiobuffer.h"

class NullAudioBuffer : public AbstractAudioBuffer
{
 Q_OBJECT
public:
 //explicit NullAudioBuffer(QObject *parent = 0);
 /*public*/ NullAudioBuffer(QString systemName, QObject *parent = 0);
 /*public*/ NullAudioBuffer(QString systemName, QString userName, QObject *parent=0);
 /*public*/ QString toString();
 /*public*/ int getFormat();
 /*public*/ long getLength();
 /*public*/ int getFrequency();

signals:

public slots:
private:
 Logger* log;
 void common();
 /*private*/ QString parseFormat();

protected:
 /*protected*/ void cleanUp();
 /*protected*/ bool loadBuffer(QDataStream* stream);
 /*protected*/ bool loadBuffer() ;
 /*protected*/ void generateLoopBuffers(int which);
 /*protected*/ bool generateStreamingBuffers() ;
 /*protected*/ void removeStreamingBuffers();
friend class NullAudioFactory;
};

#endif // NULLAUDIOBUFFER_H
