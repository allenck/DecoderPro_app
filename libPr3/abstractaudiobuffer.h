#ifndef ABSTRACTAUDIOBUFFER_H
#define ABSTRACTAUDIOBUFFER_H
#include "abstractaudio.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT AbstractAudioBuffer : public AbstractAudio
{
 Q_OBJECT
public:
 //explicit AbstractAudioBuffer(QObject *parent = 0);
 /*public*/ AbstractAudioBuffer(QString systemName,QObject *parent = 0);
 /*public*/ AbstractAudioBuffer(QString systemName, QString userName, QObject *parent = 0);
 /*public*/ QChar getSubType() ;
 /*public*/ QString getURL();
 /*public*/ void setURL(QString url);
 /*public*/ void setInputStream(QDataStream* stream) ;
 /*public*/ int getFrameSize();
 /*public*/ void setStartLoopPoint(long startLoopPoint);
 /*public*/ bool loadBuffer(QByteArray b, int format, int frequency);
 // Can be made abstract later.
 //@Override
 /*public*/ long getStartLoopPoint();
 /*public*/ void setEndLoopPoint(long endLoopPoint);
 /*public*/ long getEndLoopPoint();
 /*public*/ void setStreamed(bool streamed);
 /*public*/ bool isStreamed();
 /*public*/ bool isStreamedForced();
 /*public*/ void stateChanged(int oldState);

signals:

public slots:
private:

 /**
  * Holds the location of the sound sample used in this buffer
  */
 /*private*/ QString _url;

 /**
  * Start loop point for this buffer represented as a number of samples
  */
 /*private*/ long _startLoopPoint;

 /**
  * End loop point for this buffer represented as a number of samples
  */
 /*private*/ long _endLoopPoint;

 /**
  * Flag to determine if this buffer is to be streamed from file
  */
 /*private*/ bool _streamed;// = false;

 /**
  * Flag to determine if streaming has been forced
  */
 /*private*/ bool _streamedForced;// = false;
 void common();
 Logger* log;

protected:
 /**
  * Identifier of start loop point
  */
 /*protected*/ static /*final*/ int LOOP_POINT_START;// = 0x01;

 /**
  * Identifier of end loop point
  */
 /*protected*/ static /*final*/ int LOOP_POINT_END;// = 0x02;

 /**
  * Identifier of both loop points
  */
 /*protected*/ static /*final*/ int LOOP_POINT_BOTH;// = 0x03;
 virtual /*abstract*/ /*protected*/ bool loadBuffer();
 virtual /*abstract*/ /*protected*/ bool loadBuffer(QDataStream* s);
 /*protected*/ void setStartLoopPoint(long startLoopPoint, bool generateLoopBuffers);
 /*protected*/ void setEndLoopPoint(long endLoopPoint, bool generateLoopBuffers) ;
 /*protected*/ void setStreamedForced(bool streamedForced) ;
 virtual /*abstract*/ /*protected*/ void generateLoopBuffers(int which);
 virtual /*abstract*/ /*protected*/ bool generateStreamingBuffers();
 virtual /*abstract*/ /*protected*/ void removeStreamingBuffers();
 friend class AbstractAudioFactory;
};

#endif // ABSTRACTAUDIOBUFFER_H
