#ifndef CONNECTIONSTATUS_H
#define CONNECTIONSTATUS_H

#include <QObject>
#include <QMutex>
#include "logger.h"
#include <QStringList>
#include "swingpropertychangesupport.h"
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
    QMap<QString, QString> portStatus;// = new QStringList();
    /*public*/ static /*synchronized*/ ConnectionStatus* instance();
    /*public*/ /*synchronized*/ void addConnection (QString systemName, QString portName);
    /*public*/ /*synchronized*/ void setConnectionState(QString systemName, QString portName, QString state);
    /*public*/ /*synchronized*/ QString getSystemState(QString systemName);
    /*public*/ /*synchronized*/ QString getConnectionState(QString systemName, QString portName);
    /*public*/ /*synchronized*/ bool isConnectionOk(QString systemName, /*@Nonnull*/QString portName);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    SwingPropertyChangeSupport* pcs;// = new SwingPropertyChangeSupport(this, nullptr);

signals:

public slots:
    /*public*/ void PropertyChange(PropertyChangeEvent* e);

private:
 static QMutex* mutex;
 /** record the single instance **/
 /*private*/ static ConnectionStatus* _instance;// = NULL;
 static Logger* log;
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
    QString _key;
public:
    /*public*/ ConnectionKey() {}
    /**
     * constructor
     *
     * @param system human-readable name for system like "LocoNet 2"
     *                      which can be obtained from i.e. {@link SystemConnectionMemo#getUserName}.
     * @param port   port name
     * @throws IllegalArgumentException if both system and port are null;
     */
    /*public*/ ConnectionKey(const QString system, /*@Nonnull*/ const QString port) {
        if (system == "" && port == "") {
            throw  new IllegalArgumentException("At least the port name must be provided");
        }
        systemName = system;
        portName = port;
        _key = system+port;
    }

    /*public*/ QString getSystemName() const {
        return systemName;
    }

    /*public*/ QString getPortName() const{
        return portName;
    }

    /*public*/ QString key() const{
     return _key;
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

    inline /*public*/ bool operator==(const ConnectionKey& other)
    {
     return (systemName == "" ? other.getSystemName() == "" : systemName == (other.getSystemName()))
             && (portName == "" ? other.getPortName() == "" : portName ==(other.getPortName()));

    }
#if 0
    //@Override
//    /*public*/ int hashCode() {
//        if (systemName == nullptr) {
//            return qHash(portName);//portName.hashCode();
//        } else if (portName == "") {
//            return qHash(systemName);//systemName.hashCode();
//        } else {
//            return (qHash(systemName) + qHash(portName));
//        }
//    }

    // despite being structured identically as documented for the QHash class, this won't compile!
    inline /*public*/ uint qHash(const ConnectionKey& key, uint seed) {
     QString portName = key.getPortName();
        if (key.systemName == nullptr) {
            return qHash(portName, seed);//portName.hashCode();
        } else if (key.portName == "") {
            return qHash(key.systemName, seed);//systemName.hashCode();
        } else {
            return (qHash(key.systemName, seed) + qHash(key.portName, seed));
        }
    }

#endif
};
#endif // CONNECTIONSTATUS_H
