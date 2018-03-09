#ifndef BUFFEREDOUTPUTSTREAM_H
#define BUFFEREDOUTPUTSTREAM_H

#include <QObject>
#include "exceptions.h"
#include <QDataStream>

class BufferedOutputStream : public QObject
{
 Q_OBJECT
public:
 /*public*/ BufferedOutputStream(QDataStream* out, QObject* parent = nullptr);
 /*public*/ BufferedOutputStream(QDataStream* out, int size, QObject* parent = nullptr);
 /*public*/ /*synchronized*/ void write(int b) throw (IOException);
 /*public*/ /*synchronized*/ void flush() throw (IOException);
 /*public*/ void close() throw (IOException);

signals:

public slots:

private:
 void common(QDataStream* out, int size);
 /*private*/ void flushBuffer() throw (IOException);
 QDataStream* out;

protected:
 /**
  * The internal buffer where data is stored.
  */
 /*protected*/ QByteArray buf;

 /**
  * The number of valid bytes in the buffer. This value is always
  * in the range <tt>0</tt> through <tt>buf.length</tt>; elements
  * <tt>buf[0]</tt> through <tt>buf[count-1]</tt> contain valid
  * byte data.
  */
 /*protected*/ int count;

};

#endif // BUFFEREDOUTPUTSTREAM_H
