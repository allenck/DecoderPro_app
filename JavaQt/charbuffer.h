#ifndef CHARBUFFER_H
#define CHARBUFFER_H
#include "buffer.h"

class ReadOnlyBufferException : public Exception
{
public:
 ReadOnlyBufferException(QString /*mag*/ = "") : Exception(msg) {}
};

class BufferOverflowException : public Exception
{
public:
 BufferOverflowException(QString = "") : Exception(msg) {}
};

class CharBuffer : public Buffer
{
public:
 CharBuffer(int mark, int pos, int lim, int cap,   // package-private
             QByteArray hb, int offset, QObject* parent = nullptr);
 CharBuffer(int mark, int pos, int lim, int cap, QObject* parent = nullptr); // package-private
 /*public*/ static CharBuffer* allocate(int capacity);
 /*public*/ static CharBuffer* wrap(QByteArray array, int offset, int length);
 /*public*/ static CharBuffer* wrap(QByteArray array);
 /*public*/ int read(CharBuffer* target) throw (IOException);

 /*public*/ CharBuffer* put(CharBuffer* src);
 /*public*/ CharBuffer* put(QByteArray src, int offset, int length);
 /*public*/ /*final*/ CharBuffer* put(QByteArray src);
 /*public*/ CharBuffer* put(QString src, int start, int end);
 /*public*/ /*final*/ CharBuffer* put(QString src);
 /*public*/ /*abstract*/ virtual char get();
 /*public*/ /*abstract*/ virtual CharBuffer* put(char c);


private:
 // These fields are declared here rather than in Heap-X-Buffer in order to
 // reduce the number of virtual method invocations needed to access these
 // values, which is especially costly when coding small buffers.
 //
 /*final*/ QByteArray hb;                  // Non-null only for heap buffers
 /*final*/ int offset;
 bool _isReadOnly;                 // Valid only for heap buffers

};

#endif // CHARBUFFER_H
