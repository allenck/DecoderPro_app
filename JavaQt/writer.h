#ifndef WRITER_H
#define WRITER_H

#include <QTextStream>
#include <QObject>
#include "javaqt_global.h"
#include "exceptions.h"

class JAVAQTSHARED_EXPORT Writer : public QTextStream
{
  //Q_OBJECT
public:
    Writer();
    ///*abstract*/ /*public*/ virtual void flush() /*throw (IOException)*/;
    /*public*/ void write(QString str) /*throw (IOException)*/;
    /*abstract*/ /*public*/ virtual void close() /*throw (IOException)*/;
    /*public*/ void write(QByteArray cbuf) /*throw (IOException)*/;
    virtual /*public*/ void write(QByteArray /*cbuf*/, int /*off*/, int /*len*/) /*throw (IOException)*/ {}

private:
    /**
     * Temporary buffer used to hold writes of strings and single characters
     */
    /*private*/ QList<QChar> writeBuffer;

    /**
     * Size of writeBuffer, must be >= 1
     */
    /*private*/ static /*final*/ int WRITE_BUFFER_SIZE;// = 1024;

    /**
     * The object used to synchronize operations on this stream.  For
     * efficiency, a character-stream object may use an object other than
     * itself to protect critical sections.  A subclass should therefore use
     * the object in this field rather than <tt>this</tt> or a synchronized
     * method.
     */
    /*protected*/ QObject* lock;
    /*protected*/ Writer(QObject* lock);
 friend class StringWriter;
};
Q_DECLARE_INTERFACE(Writer, "Wreiter")
#endif // WRITER_H
