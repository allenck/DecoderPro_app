#ifndef BUFFEREDWRITER_H
#define BUFFEREDWRITER_H
#include "writer.h"
#include "exceptions.h"

class BufferedWriter : public Writer
{
public:
 /*public*/ BufferedWriter(Writer* out);
 /*public*/ BufferedWriter(Writer* out, int sz);
 /*public*/ void newLine() throw (IOException);
 /*public*/ void flush() throw (IOException);
 /*public*/ void write(int c) throw (IOException);
 /*public*/ void write(QByteArray cbuf, int off, int len) throw (IOException);
 /*public*/ void write(QString s, int off, int len) throw (IOException);

 /*public*/ void close() throw (IOException);

private:
 /*private*/ Writer* out;

 /*private*/ QByteArray cb;
 /*private*/ int nChars, nextChar;

 /*private*/ static int defaultCharBufferSize;// = 8192;
 /**
  * Line separator string.  This is the value of the line.separator
  * property at the moment that the stream was created.
  */
 /*private*/ QString lineSeparator;
 void common(Writer* out, int sz);
 /*private*/ void ensureOpen() throw (IOException);
 void flushBuffer() throw (IOException);
 /*private*/ int min(int a, int b);

 friend class PrintStream;
};

#endif // BUFFEREDWRITER_H
