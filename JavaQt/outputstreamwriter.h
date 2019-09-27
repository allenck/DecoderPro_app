#ifndef OUTPUTSTREAMWRITER_H
#define OUTPUTSTREAMWRITER_H
#include "writer.h"
#include "exceptions.h"

class StreamEncoder;
class OutputStreamWriter : public Writer
{
public:
 /*public*/ OutputStreamWriter(QDataStream* out);

 /*public*/ void write(QString str, int off, int len) throw (IOException);

private:
 /*private*/ /*final*/ StreamEncoder* se;
 void flushBuffer() throw (IOException);

 friend class PrintStream;
};

#endif // OUTPUTSTREAMWRITER_H
