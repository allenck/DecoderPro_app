#include "connectionstatus.h"
#include "exceptions.h"
#include "loggerfactory.h"

/**
 * Interface for classes that wish to get notification when the connection to
 * the layout changes.
 * <p>
 * Maintains a single instance, as there is only one set of connections for the
 * running program.
 * <p>
 * The "system name" referred to here is the human-readable name like "LocoNet 2"
 * which can be obtained from i.e.
 * {@link jmri.SystemConnectionMemo#getUserName}.
 * Not clear whether {@link ConnectionConfig#getConnectionName} is correct.
 * It's not intended to be the prefix from i.e. {@link PortAdapter#getSystemPrefix}.
 * Maybe the right thing is to pass in the SystemConnectionMemo?
 *
 * @author Daniel Boudreau Copyright (C) 2007
 * @author Paul Bender Copyright (C) 2016
 */

/*public*/ /*static*/ const QString ConnectionStatus::CONNECTION_UNKNOWN = "Unknown";
/*public*/ /*static*/ const QString ConnectionStatus::CONNECTION_UP = "Connected";
/*public*/ /*static*/ const QString ConnectionStatus::CONNECTION_DOWN = "Not Connected";
QMutex* ConnectionStatus::mutex = new QMutex();

/**
 * Record the single instance *
 */ConnectionStatus* ConnectionStatus::_instance = NULL;

ConnectionStatus::ConnectionStatus(QObject *parent) :
    QObject(parent)
{
 pcs = new SwingPropertyChangeSupport(this, nullptr);
 setObjectName("ConnectionStatus");
 portStatus = QMap<QString, QString>(); // NOTE: key is concatenation of systemname and port
}

/*public*/ /*static*/ /*synchronized*/ ConnectionStatus* ConnectionStatus::instance()
{
 //QMutexLocker locker(mutex);
 if (_instance == NULL)
 {
  if (log->isDebugEnabled()) log->debug("ConnectionStatus creating instance");
  // create and load
  _instance = new ConnectionStatus();
 }
 if (log->isDebugEnabled()) log->debug("ConnectionStatus returns instance "+ _instance->objectName());
 return _instance;
}

/**
 * Add a connection with a given name and port name to the portStatus set
 * if not yet present in the set.
 *
 * @param systemName human-readable name for system like "LocoNet 2"
 *                   which can be obtained from i.e. {@link SystemConnectionMemo#getUserName}.
 * @param portName   the port name
 */
/*public*/ /*synchronized*/ void ConnectionStatus::addConnection (QString systemName, QString portName)
{
 QMutexLocker locker(mutex);
 log->debug(tr("addConnection systemName %1 portName %2").arg(systemName, portName));
 ConnectionKey newKey (systemName, portName);
 if (!portStatus.contains(newKey.key())) {
     portStatus.insert(newKey.key(), CONNECTION_UNKNOWN);
     firePropertyChange("add", QVariant(), portName);
 }
}

/**
 * Set the connection state of a communication port.
 *
 * @param systemName the system name
 * @param portName   the port name
 * @param state      one of ConnectionStatus.UP, ConnectionStatus.DOWN, or
 *                   ConnectionStatus.UNKNOWN.
 */
/*public*/ /*synchronized*/ void ConnectionStatus::setConnectionState(QString systemName, QString portName, QString state)
{
 QMutexLocker locker(mutex);
 log->debug(tr("setConnectionState systemName: %1 portName: %2 state: %3").arg(systemName, portName, state));
 ConnectionKey newKey (systemName, portName);
 //QPair<QString, QString> newKey(systemName, portName);
 //if (!portStatus.contains(newKey))
// QList<ConnectionKey*> list = portStatus.keys();
// for(ConnectionKey* key : list)
// {
//  if(newKey->equals(key))
//  {
//     portStatus.insert(newKey, state);
//     firePropertyChange("add", QVariant(), portName);
//     return;
//  }
// }
//  portStatus.insert(newKey, state); // will overlay existing entry
//  firePropertyChange("change", state, portName);
 if (!portStatus.contains(newKey.key())) {
      portStatus.insert(newKey.key(), state);
      firePropertyChange("add", QVariant(), portName);
      log->debug(tr("New Connection added: %1 ").arg(newKey.getPortName()));
  } else {
//      firePropertyChange("change", portStatus.insert(newKey, state), portName);
       portStatus.insert(newKey.key(), state);
       firePropertyChange("add", QVariant(), portName);
 }
}

/**
 * Get the status of a communication port with a given name.
 *
 * @param systemName human-readable name for system like "LocoNet 2"
 *                      which can be obtained from i.e. {@link SystemConnectionMemo#getUserName}.
 * @param portName   the port name
 * @return the status
 */
/*public*/ /*synchronized*/ QString ConnectionStatus::getConnectionState(QString systemName, /*@Nonnull*/ QString portName)
{
 //QMutexLocker locker(mutex);
 log->debug(tr("getConnectionState systemName: %1 portName: %2").arg(systemName, portName));
 QString stateText = CONNECTION_UNKNOWN;
 ConnectionKey newKey (systemName, portName);
 if (portStatus.contains(newKey.key())) {
     stateText = portStatus.value(newKey.key());
     log->debug(tr("connection found : %1").arg(stateText));
 } else {
     log->debug(tr("connection systemName %1 portName %2 not found, %3").arg(systemName, portName, stateText));
 }
 return stateText;
}

/**
 * get the status of a communication port based on the system name.
 *
 * @param systemName the system name
 * @return the status
 */
/*public*/ /*synchronized*/ QString ConnectionStatus::getSystemState(/*@Nonnull*/ QString systemName) {
 QMutexLocker locker(mutex);
 log->debug(tr("getSystemState systemName: %1 ").arg(systemName));
 // see if there is a key that has systemName as the port value.
 //for (Map.Entry<ConnectionKey, String> entry : portStatus.entrySet())
 QMapIterator<QString, QString> iter(portStatus);
 while(iter.hasNext())
 {
  iter.next();
     //if ((iter.key().getSystemName() != "") && (iter.key().getSystemName() == (systemName))) {
  if(iter.key().contains(systemName)){
         // if we find a match, return it
         return iter.value();
     }
 }
 // If we still don't find a match, then we don't know the status
 log->warn(tr("Didn't find system status for system %1").arg(systemName));
 return CONNECTION_UNKNOWN;
}



/**
 * Returns status of a communication port
 * @param portName
 * @return true if port connection is operational or unknown, false if not
 */
/*public*/ /*synchronized*/ bool ConnectionStatus::isConnectionOk(QString systemName, /*@Nonnull*/ QString portName)
{
 //QMutexLocker locker(mutex);
 QString stateText = getConnectionState(systemName, portName);
 return !(stateText == CONNECTION_DOWN);
}

/*public*/ /*synchronized*/ void ConnectionStatus::addPropertyChangeListener(PropertyChangeListener* l)
{
 pcs->addPropertyChangeListener(l);
}

/*protected*/ void ConnectionStatus::firePropertyChange(QString p, QVariant old, QVariant n)
{
 log->debug ("firePropertyChange \"" + p + "\" old: " +old.toString() + " new: "+ n.toString());
 pcs->firePropertyChange(p,old,n);
}

/*public*/ /*synchronized*/ void ConnectionStatus::removePropertyChangeListener(PropertyChangeListener* l)
{
 QMutexLocker locker(mutex);
 pcs->removePropertyChangeListener(l);
}

/*public*/ void ConnectionStatus::PropertyChange(PropertyChangeEvent* e)
{
  log->debug(tr("property change: %1").arg(e->getPropertyName()));
}

/*private*/ /*final*/ /*static*/ Logger* ConnectionStatus::log = LoggerFactory::getLogger("ConnectionStatus");

