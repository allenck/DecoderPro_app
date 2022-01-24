#ifndef BUFFEREDINPUTSTREAM_H
#define BUFFEREDINPUTSTREAM_H

#include <QObject>
#include <limits.h>
#include <QByteArray>
#include <QDataStream>
#include "exceptions.h"

class BufferedInputStream : public QObject
{
 Q_OBJECT
public:
 /*public*/ BufferedInputStream(QDataStream* in, QObject *parent = nullptr);
 /*public*/ BufferedInputStream(QDataStream* in, int size, QObject* parent = nullptr);
 /*public*/ /*synchronized*/ int read() /*throw (IOException)*/;

signals:

public slots:
private:
 /*private*/ static int DEFAULT_BUFFER_SIZE;// = 8192;
 /*private*/ static int MAX_BUFFER_SIZE;// = INT_MAX - 8;
 void common(QDataStream* in, int size);
 /*private*/ QDataStream* getInIfOpen() ;
 /*private*/ QByteArray getBufIfOpen() ;
 QDataStream* in;
 /*private*/ void fill() /*throw (IOException)*/;

protected:
 /**
  * The internal buffer array where the data is stored. When necessary,
  * it may be replaced by another array of
  * a different size.
  */
 /*protected*/ /*volatile*/ QByteArray buf;
 /**
  * The index one greater than the index of the last valid byte in
  * the buffer.
  * This value is always
  * in the range <code>0</code> through <code>buf.length</code>;
  * elements <code>buf[0]</code>  through <code>buf[count-1]
  * </code>contain buffered input data obtained
  * from the underlying  input stream.
  */
 /*protected*/ int count;

 /**
  * The current position in the buffer. This is the index of the next
  * character to be read from the <code>buf</code> array.
  * <p>
  * This value is always in the range <code>0</code>
  * through <code>count</code>. If it is less
  * than <code>count</code>, then  <code>buf[pos]</code>
  * is the next byte to be supplied as input;
  * if it is equal to <code>count</code>, then
  * the  next <code>read</code> or <code>skip</code>
  * operation will require more bytes to be
  * read from the contained  input stream.
  *
  * @see     java.io.BufferedInputStream#buf
  */
 /*protected*/ int pos;

 /**
  * The value of the <code>pos</code> field at the time the last
  * <code>mark</code> method was called.
  * <p>
  * This value is always
  * in the range <code>-1</code> through <code>pos</code>.
  * If there is no marked position in  the input
  * stream, this field is <code>-1</code>. If
  * there is a marked position in the input
  * stream,  then <code>buf[markpos]</code>
  * is the first byte to be supplied as input
  * after a <code>reset</code> operation. If
  * <code>markpos</code> is not <code>-1</code>,
  * then all bytes from positions <code>buf[markpos]</code>
  * through  <code>buf[pos-1]</code> must remain
  * in the buffer array (though they may be
  * moved to  another place in the buffer array,
  * with suitable adjustments to the values
  * of <code>count</code>,  <code>pos</code>,
  * and <code>markpos</code>); they may not
  * be discarded unless and until the difference
  * between <code>pos</code> and <code>markpos</code>
  * exceeds <code>marklimit</code>.
  *
  * @see     java.io.BufferedInputStream#mark(int)
  * @see     java.io.BufferedInputStream#pos
  */
 /*protected*/ int markpos = -1;

 /**
  * The maximum read ahead allowed after a call to the
  * <code>mark</code> method before subsequent calls to the
  * <code>reset</code> method fail.
  * Whenever the difference between <code>pos</code>
  * and <code>markpos</code> exceeds <code>marklimit</code>,
  * then the  mark may be dropped by setting
  * <code>markpos</code> to <code>-1</code>.
  *
  * @see     java.io.BufferedInputStream#mark(int)
  * @see     java.io.BufferedInputStream#reset()
  */
 /*protected*/ int marklimit;

};

class OutOfMemoryError : public Exception
{
public:
 OutOfMemoryError(QString msg) : Exception(msg){}
};
#endif // BUFFEREDINPUTSTREAM_H
