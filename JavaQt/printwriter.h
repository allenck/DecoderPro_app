#ifndef PRINTWRITER_H
#define PRINTWRITER_H

#include "writer.h"

class PrintWriter : public Writer
{
public:
 /*public*/ PrintWriter (Writer* out);
 /*public*/ PrintWriter(Writer* out, bool autoFlush);
 /*public*/ PrintWriter(QTextStream* out);
 /*public*/ PrintWriter(QTextStream* out, bool autoFlush);
 /*public*/ void println();
 /*public*/ void flush();
 /*public*/ void print(const QString s);
 /*public*/ void println(const QString x);

private:
 //void common(Writer* out, bool AutoFlush);

 /*private*/ /*final*/ bool autoFlush;
 /*private*/ bool trouble;// = false;
//    /*private*/ Formatter formatter;
//    /*private*/ PrintStream psOut = null;

 /**
  * Line separator string.  This is the value of the line.separator
  * property at the moment that the stream was created.
  */
 /*private*/ /*final*/ QString lineSeparator;
 /*private*/ void newLine();
 /*private*/ void ensureOpen();// //throws IOException

protected:
 /**
  * The underlying character-output stream of this
  * <code>PrintWriter</code>.
  *
  * @since 1.2
  */
 /*protected*/ Writer* out;

};

#endif // PRINTWRITER_H
