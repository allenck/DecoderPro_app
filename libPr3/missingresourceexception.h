#ifndef MISSINGRESOURCEEXCEPTION_H
#define MISSINGRESOURCEEXCEPTION_H

//#include <qtconcurrentexception.h>
#include <QObject>
#include <stdexcept>

class MissingResourceException : public QObject
{
    Q_OBJECT
public:
    explicit MissingResourceException(QObject *parent = 0);
    MissingResourceException(QString s, QString className, QString key, QObject *parent = 0);
//    MissingResourceException(QString message, QString className, QString key, Throwable cause);
    ~MissingResourceException();
    QString getClassName();
    QString getKey();


signals:
    
public slots:
private:
    // serialization compatibility with JDK1.1
    static const long serialVersionUID = -4876345176062000401L;
    /**
     * The class name of the resource bundle requested by the user.
     * @serial
     */
    QString className;

    /**
     * The name of the specific resource requested by the user.
     * @serial
     */
    QString key;
    
};

#endif // MISSINGRESOURCEEXCEPTION_H
