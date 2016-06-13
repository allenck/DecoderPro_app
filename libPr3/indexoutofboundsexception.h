#ifndef INDEXOUTOFBOUNDSEXCEPTION_H
#define INDEXOUTOFBOUNDSEXCEPTION_H

#include <QObject>

class IndexOutOfBoundsException : public QObject
{
    Q_OBJECT
public:
    explicit IndexOutOfBoundsException(QObject *parent = 0);
    /**
     * Constructs an <code>IndexOutOfBoundsException</code> with the
     * specified detail message.
     *
     * @param   s   the detail message.
     */
    /*public*/ IndexOutOfBoundsException(QString s);

signals:
    
public slots:
private:
    /*private static final*/ const static long serialVersionUID = 234122996006267687L;
 QString msg;
    
};

#endif // INDEXOUTOFBOUNDSEXCEPTION_H
