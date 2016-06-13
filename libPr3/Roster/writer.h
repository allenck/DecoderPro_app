#ifndef WRITER_H
#define WRITER_H

#include <QObject>
#include <exceptions.h>

class IOException;
class Writer : public QObject
{
    Q_OBJECT
public:
    //explicit Writer(QObject *parent = 0);
    /*public*/ void write(QChar c) throw (IOException);
    /*public*/ void write(QList<QChar> cBuf) throw (IOException);
    /*abstract*/ /*public*/ virtual void write(QList<QChar> cBuf, int off, int len) throw (IOException);
    /*public*/ void write(QString str) throw (IOException);
    /*public*/ void write(QString str, int off, int len) throw (IOException);
    /*public*/ Writer* append(/*CharSequence*/QString csq) throw (IOException);
    /*public*/ Writer* append(QString csq, int start, int end) throw (IOException);
    /*public*/ Writer* append(char c) throw (IOException);
    /*abstract*/ /*public*/ virtual void flush() throw (IOException);
    /*abstract*/ /*public*/ virtual void close() throw (IOException);

signals:

public slots:
private:
    /**
     * Temporary buffer used to hold writes of strings and single characters
     */
    /*private*/ QVector<QChar>* writeBuffer;

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
    /*protected*/ Writer(QObject *parent);
    /*protected*/ Writer(QObject* lock, QObject *parent);
 friend class HardcopyWriter;
};

#endif // WRITER_H
