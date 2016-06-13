#ifndef CONNECTIONSTATUS_H
#define CONNECTIONSTATUS_H

#include <QObject>
#include <QMutex>
#include "logger.h"
#include <QStringList>
#include "propertychangesupport.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ConnectionStatus : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionStatus(QObject *parent = 0);
    /*public*/ static const QString CONNECTION_UNKNOWN;// = "Unknown";
    /*public*/ static const QString CONNECTION_UP;// = "Connected";
    /*public*/ static const QString CONNECTION_DOWN;// = "Not Connected";
    // simple database of port names and their status
    static QStringList* portNames;// = new QStringList();
    static QStringList* portStatus;// = new QStringList();
    /*public*/ static /*synchronized*/ ConnectionStatus* instance();
    /*public*/ /*synchronized*/ void addConnection (QString systemName, QString portName);
    /*public*/ /*synchronized*/ void setConnectionState(QString portName, QString state);
    /*public*/ /*synchronized*/ QString getConnectionState(QString portName);
    /*public*/ /*synchronized*/ bool isConnectionOk(QString portName);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);

signals:

public slots:
private:
 static QMutex* mutex;
 /** record the single instance **/
 /*private*/ static ConnectionStatus* _instance;// = NULL;
 Logger* log;
protected:
 /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

};

#endif // CONNECTIONSTATUS_H
