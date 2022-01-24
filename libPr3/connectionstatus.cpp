#include "connectionstatus.h"
#include "exceptions.h"

/*public*/ /*static*/ const QString ConnectionStatus::CONNECTION_UNKNOWN = "Unknown";
/*public*/ /*static*/ const QString ConnectionStatus::CONNECTION_UP = "Connected";
/*public*/ /*static*/ const QString ConnectionStatus::CONNECTION_DOWN = "Not Connected";
QMutex* ConnectionStatus::mutex = new QMutex();
ConnectionStatus* ConnectionStatus::_instance = NULL;
//QStringList* ConnectionStatus::portNames= new QStringList();


ConnectionStatus::ConnectionStatus(QObject *parent) :
    QObject(parent)
{
 log = new Logger("ConnectionStatus");
 pcs = new SwingPropertyChangeSupport(this, nullptr);
 setObjectName("ConnectionStatus");
 portStatus = QHash<ConnectionKey*, QString>();

}
/**
 * Interface for classes that wish to get notification when the
 * connection to the layout changes.
 *
 * @author     Daniel Boudreau   Copyright (C) 2007
 * @version    $Revision: 17977 $
 */
///*public*/ class ConnectionStatus {




/*public*/ /*static*/ /*synchronized*/ ConnectionStatus* ConnectionStatus::instance()
{
 //QMutexLocker locker(mutex);
 Logger log("ConnectionStatus");
 if (_instance == NULL)
 {
  if (log.isDebugEnabled()) log.debug("ConnectionStatus creating instance");
  // create and load
  _instance = new ConnectionStatus();
 }
 if (log.isDebugEnabled()) log.debug("ConnectionStatus returns instance "+ _instance->objectName());
 return _instance;
}

/*public*/ /*synchronized*/ void ConnectionStatus::addConnection (QString systemName, QString portName)
{
 log->debug(tr("addConnection systemName %1 portName %2").arg(systemName, portName));
 ConnectionKey* newKey = new ConnectionKey(systemName, portName);
 //if (!portStatus.contains(newKey))
 QList<ConnectionKey*> list = portStatus.keys();
 for(ConnectionKey* key : list)
 {
  if(newKey->equals(key))
  {
     portStatus.insert(newKey, CONNECTION_UNKNOWN);
     firePropertyChange("add", QVariant(), portName);
     break;
  }
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
 log->debug(tr("setConnectionState systemName: %1 portName: %2 state: %3").arg(systemName, portName, state));
 ConnectionKey* newKey= new ConnectionKey(systemName, portName);
 //QPair<QString, QString> newKey(systemName, portName);
 //if (!portStatus.contains(newKey))
 QList<ConnectionKey*> list = portStatus.keys();
 for(ConnectionKey* key : list)
 {
  if(newKey->equals(key))
  {
     portStatus.insert(newKey, state);
     firePropertyChange("add", QVariant(), portName);
     return;
  }
 }
  portStatus.insert(newKey, state); // will overlay existing entry
  firePropertyChange("change", state, portName);
}

/**
 * get the status of a communication port
 * @param portName
 * @return status string
 */
/*public*/ /*synchronized*/ QString ConnectionStatus::getConnectionState(QString systemName, /*@Nonnull*/ QString portName)
{
 log->debug(tr("getConnectionState systemName: %1 portName: %2").arg(systemName, portName));
 QString stateText = CONNECTION_UNKNOWN;
 ConnectionKey* newKey = new ConnectionKey(systemName, portName);
 //if (portStatus.contains(newKey))
 QList<ConnectionKey*> list = portStatus.keys();
 for(ConnectionKey* key : list)
 {
  if(newKey->equals(key))
  {
      stateText = portStatus.value(key);
      log->debug(tr("connection found : %1").arg(stateText));
      return stateText;
  }
 }
 log->debug(tr("connection systemName %1 portName %2 not found, %3").arg(systemName, portName, stateText));

 return stateText;
}

/**
 * get the status of a communication port based on the system name.
 *
 * @param systemName the system name
 * @return the status
 */
/*public*/ /*synchronized*/ QString ConnectionStatus::getSystemState(/*@Nonnull*/ QString systemName) {
 log->debug(tr("getSystemState systemName: %1 ").arg(systemName));
 // see if there is a key that has systemName as the port value.
 //for (Map.Entry<ConnectionKey, String> entry : portStatus.entrySet())
 QHashIterator<ConnectionKey*, QString> iter(portStatus);
 while(iter.hasNext())
 {
  iter.next();
     if ((iter.key()->getSystemName() != "") && (iter.key()->getSystemName() == (systemName))) {
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
 QString stateText = getConnectionState(systemName, portName);
 //QMutexLocker locker(mutex);
 if (stateText!=(CONNECTION_UP))
  return false;
 else
  return true;
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
 pcs->removePropertyChangeListener(l);
}

/*public*/ void ConnectionStatus::PropertyChange(PropertyChangeEvent* e)
{
  log->debug(tr("property change: %1").arg(e->getPropertyName()));
}


