#ifndef CONNECTIONSTATUS_H
#define CONNECTIONSTATUS_H

#include <QObject>
#include <QMutex>
#include "logger.h"
#include <QStringList>
#include "propertychangesupport.h"
#include "libPr3_global.h"
#include <QPair>

class ConnectionKey;
class LIBPR3SHARED_EXPORT ConnectionStatus : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionStatus(QObject *parent = 0);
    /*public*/ static const QString CONNECTION_UNKNOWN;// = "Unknown";
    /*public*/ static const QString CONNECTION_UP;// = "Connected";
    /*public*/ static const QString CONNECTION_DOWN;// = "Not Connected";
    // simple database of port names and their status
    //static QStringList* portNames;// = new QStringList();
    QHash<ConnectionKey*, QString> portStatus;// = new QStringList();
    /*public*/ static /*synchronized*/ ConnectionStatus* instance();
    /*public*/ /*synchronized*/ void addConnection (QString systemName, QString portName);
    /*public*/ /*synchronized*/ void setConnectionState(QString systemName, QString portName, QString state);
    /*public*/ /*synchronized*/ QString getSystemState(QString systemName);
    /*public*/ /*synchronized*/ QString getConnectionState(QString systemName, QString portName);
    /*public*/ /*synchronized*/ bool isConnectionOk(QString systemName, /*@Nonnull*/QString portName);
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

/**
 * ConnectionKey is an internal class containing the port name and system
 * name of a connection.
 * <p>
 * ConnectionKey is used as a key in a HashMap of the connections on the
 * system.
 * <p>
 * It is allowable for either the port name or the system name to be null,
 * but not both.
 */
/*static*/ /*private*/ class ConnectionKey : public QObject{
Q_OBJECT
    QString portName = "";
    QString systemName = "";  // human-readable name for system
public:
    /**
     * constructor
     *
     * @param system human-readable name for system like "LocoNet 2"
     *                      which can be obtained from i.e. {@link SystemConnectionMemo#getUserName}.
     * @param port   port name
     * @throws IllegalArgumentException if both system and port are null;
     */
    /*public*/ ConnectionKey(QString system, /*@Nonnull*/ QString port) {
        if (system == "" && port == "") {
            throw  IllegalArgumentException("At least the port name must be provided");
        }
        systemName = system;
        portName = port;
    }

    /*public*/ QString getSystemName() const {
        return systemName;
    }

    /*public*/ QString getPortName() {
        return portName;
    }

    //@Override
    /*public*/ bool equals(QObject* o) {
        if (o == nullptr || !(qobject_cast<ConnectionKey*>(o))) {
            return false;
        }
        ConnectionKey* other = (ConnectionKey*) o;

        return (systemName == "" ? other->getSystemName() == "" : systemName == (other->getSystemName()))
                && (portName == "" ? other->getPortName() == "" : portName ==(other->getPortName()));
    }
#if 0
    //@Override
    /*public*/ int hashCode() {
        if (systemName == nullptr) {
            return portName.hashCode();
        } else if (portName == "") {
            return systemName.hashCode();
        } else {
            return (systemName.hashCode() + portName.hashCode());
        }
    }
#endif
};
#endif // CONNECTIONSTATUS_H
