#ifndef AUDIOINPUTSTREAM_H
#define AUDIOINPUTSTREAM_H

#include <QDataStream>
#include "libPr3_global.h"

class Logger;
class QAudioFormat;
class LIBPR3SHARED_EXPORT AudioInputStream : public QObject
{
 //Q_OBJECT
public:
 //explicit AudioInputStream(QObject *parent = 0);
 /*public*/ AudioInputStream(QDataStream* stream, QAudioFormat* format, long length, QObject *parent = 0);
 /*public*/ QAudioFormat* getFormat();
 /*public*/ long getFrameLength();
 /*public*/ int read() /*throws IOException*/;
 /*public*/ int read(QByteArray* b) /*throws IOException */;
 /*public*/ int read(QByteArray* b, int off, int len) /*throws IOException*/;
 /*public*/ long skip(long n) /*throws IOException */;
 /*public*/ int available() /*throws IOException*/;
 /*public*/ void close() /*throws IOException*/;
 /*public*/ void mark(int readlimit);
 /*public*/ void reset() /*throws IOException*/;
 /*public*/ bool markSupported();


signals:

public slots:
private:
 /**
  * The <code>InputStream</code> from which this <code>AudioInputStream</code>
  * object was constructed.
  */
 /*private*/ QDataStream* stream;
 void common();
 /**
  * The position where a mark was set.
  */
 /*private*/ long markpos;

 /**
  * When the underlying stream could only return
  * a non-integral number of frames, store
  * the remainder in a temporary buffer
  */
 /*private*/ QByteArray* pushBackBuffer;// = null;

 /**
  * number of valid bytes in the pushBackBuffer
  */
 /*private*/ int pushBackLen;// = 0;

 /**
  * MarkBuffer at mark position
  */
 /*private*/ QByteArray* markPushBackBuffer;// = null;

 /**
  * number of valid bytes in the markPushBackBuffer
  */
 /*private*/ int markPushBackLen;// = 0;
protected:
 /**
  * The format of the audio data contained in the stream.
  */
 /*protected*/ QAudioFormat* format;

 /**
  * This stream's length, in sample frames.
  */
 /*protected*/ long frameLength;

 /**
  * The size of each frame, in bytes.
  */
 /*protected*/ int frameSize;

 /**
  * The current position in this stream, in sample frames (zero-based).
  */
 /*protected*/ long framePos;
 int bytesRead;// = 0;
 int thisOff;// = off;
 Logger* log;

};

#endif // AUDIOINPUTSTREAM_H
