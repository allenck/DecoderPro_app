#ifndef PRINTSTREAM_H
#define PRINTSTREAM_H
#include "filteroutputstream.h"
#include "exceptions.h"

class Formatter;
class BufferedWriter;
class OutputStreamWriter;
class PrintStream : public FilterOutputStream
{
public:
 /*public*/ PrintStream(QDataStream* out, QObject* parent = nullptr);
 /*public*/ PrintStream(QDataStream* out, bool autoFlush, QObject* parent= nullptr);
 /*public*/ void println();
 /*public*/ void println(QString x);
 /*public*/ void print(QString s);

private:
 /*private*/ bool autoFlush = false;
 /*private*/ bool trouble = false;
 /*private*/ Formatter* formatter;
 /**
  * Track both the text- and character-output streams, so that their buffers
  * can be flushed without flushing the entire stream.
  */
 /*private*/ BufferedWriter* textOut;
 /*private*/ OutputStreamWriter* charOut;
 /*private*/ PrintStream(bool autoFlush, QDataStream* out, QObject* parent);
 void common(bool autoFlush, QDataStream* out);
 /*private*/ void init(OutputStreamWriter* osw);
 /*private*/ void newLine();
 /*private*/ void ensureOpen() throw (IOException);
 /*private*/ void write(QString s);


};

#endif // PRINTSTREAM_H
