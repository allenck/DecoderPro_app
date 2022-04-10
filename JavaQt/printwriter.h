#ifndef PRINTWRITER_H
#define PRINTWRITER_H

#include "writer.h"
#include "javaqt_global.h"
#include "exceptions.h"

class StringWriter;
class Formatter;
class PrintStream;
class JAVAQTSHARED_EXPORT PrintWriter : public QObject, public Writer
{
  Q_OBJECT
  Q_INTERFACES(Writer)
public:
 /*public*/ PrintWriter(Writer* out);
 /*public*/ PrintWriter(Writer* out, bool autoFlush);
 /*public*/ PrintWriter(QTextStream* out);
 /*public*/ PrintWriter(QTextStream* out, bool autoFlush);
 /*public*/ PrintWriter(QString fileName) /*throw (FileNotFoundException)*/;
 /*Public*/ PrintWriter(StringWriter* sw);
 /*public*/ void println();
 /*public*/ void flush();
 /*public*/ void print(const QString s);
 /*public*/ void println(const QString x);
 /*public*/ void close() /*throw (IOException)*/ override;
 /*public*/ void format(const char *format, ...);

private:
 //void common(Writer* out, bool AutoFlush);

 /*private*/ /*final*/ bool autoFlush = false;
 /*private*/ bool trouble = false;
 /*private*/ Formatter* formatter = nullptr;
 /*private*/ QTextStream* psOut = nullptr;
 /*private*/ StringWriter* sw = nullptr;
  bool bOpen;
  qint64 cpos;
 /**
  * Line separator string.  This is the value of the line.separator
  * property at the moment that the stream was created.
  */
 /*private*/ /*final*/ QString lineSeparator = "\n";
 /*private*/ void newLine();
 /*private*/ void ensureOpen() /*throw (IOException)*/;

protected:
 /**
  * The underlying character-output stream of this
  * <code>PrintWriter</code>.
  *
  * @since 1.2
  */
 /*protected*/ Writer* out =nullptr;

};

#endif // PRINTWRITER_H
