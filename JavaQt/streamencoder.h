#ifndef STREAMENCODER_H
#define STREAMENCODER_H
#include "writer.h"
#include "exceptions.h"

class StreamEncoder : public Writer
{
public:
 StreamEncoder();

private:
 /*private*/ static /*final*/ int DEFAULT_BYTE_BUFFER_SIZE;// = 8192;

 /*private*/ /*volatile*/ bool isOpen = true;

 /*private*/ void ensureOpen() throw (IOException);

};

#endif // STREAMENCODER_H
