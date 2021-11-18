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
 pcs = new PropertyChangeSupport(this);
 setObjectName("ConnectionStatus");
 portStatus = QHash<QPair<QString, QString>, QString>();

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
 log->debug ("add connection to monitor " + systemName + " " + portName);
 QPair<QString, QString> newKey(systemName, portName);
 if (!portStatus.contains(newKey))
 {
     portStatus.insert(newKey, CONNECTION_UNKNOWN);
     firePropertyChange("add", QVariant(), portName);
 }
}
/**
 * sets the connection state of a communication port
 * @param portName = communication port name
 * @param state
 */
/*public*/ /*synchronized*/ void ConnectionStatus::setConnectionState(QString portName, QString state)
{
#if 0
 QMutexLocker locker(mutex);
 log->debug ("set " + portName + " connection status: " + state);
 if (portName == NULL)
  return;
 if (!portNames->contains(portName))
 {
  portNames->append(portName);
  portStatus->append(state);
  firePropertyChange("add", QVariant(), QVariant(portName));
 }
 else
 {
  for (int i=0; i<portNames->size(); i++)
  {
   if (portName==(portNames->at(i)))
   {
    if (state!=(portStatus->at(i)))
    {
     portStatus->replace(i, state);
     firePropertyChange("change", QVariant(), QVariant(portName));
     break;
    }
   }
  }
 }
#else
 setConnectionState(NULL, portName, state);
#endif
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
 log->debug(tr("set %1 connection status: %2").arg(portName).arg(state));
 QPair<QString, QString> newKey(systemName, portName);
 if (!portStatus.contains(newKey))
 {
     portStatus.insert(newKey, state);
     firePropertyChange("add", QVariant(), portName);
 }
 else
 {
  portStatus.insert(newKey, state); // will overlay existing entry
  firePropertyChange("change", state, portName);
 }
}

/**
 * get the status of a communication port
 * @param portName
 * @return status string
 */
/*public*/ /*synchronized*/ QString ConnectionStatus::getConnectionState(QString portName)
{
 QPair<QString, QString> newKey(NULL, portName);
 if (portStatus.contains(newKey))
 {
  return getConnectionState(NULL, portName);
 }
 else
 {
  // we have to see if there is a key that has portName as the port value.
  for (QPair<QString, QString> c : portStatus.keys())
  {
   if (c.first == NULL ? portName == NULL : c.second==(portName))
   {
       // if we find a match, return it.
       return getConnectionState(c.first, c.second);
   }
  }
 }
 // and if we still don't find a match, go ahead and try with NULL as
 // the system name.
 return getConnectionState(NULL, portName);
 }

/**
 * get the status of a communication port based on the system name.
 *
 * @param systemName the system name
 * @return the status
 */
/*public*/ /*synchronized*/ QString ConnectionStatus::getSystemState(QString systemName) {
    QPair<QString, QString> newKey(systemName, NULL);
    if (portStatus.contains(newKey)) {
        return getConnectionState(systemName, NULL);
    } else {
        // we have to see if there is a key that has systemName as the port value.
        for (QPair<QString, QString> c : portStatus.keys()) {
            if (c.first == NULL ? systemName == NULL : c.first == (systemName)) {
                // if we find a match, return it.
                return getConnectionState(c.first, c.second);
            }
        }
    }
    // and if we still don't find a match, go ahead and try with NULL as
    // the port name.
    return getConnectionState(systemName, NULL);
}

/**
 * Get the status of a communication port.
 *
 * @param systemName the system name
 * @param portName   the port name
 * @return the status
 */
/*public*/ /*synchronized*/ QString ConnectionStatus::getConnectionState(QString systemName, QString portName)
{
 QString stateText = CONNECTION_UNKNOWN;
 QPair<QString, QString> newKey(systemName, portName);
 if (portStatus.contains(newKey))
 {
    stateText = portStatus.value(newKey);
 }
 log->debug(tr("get connection status: %1 %2").arg(portName).arg(stateText));
 return stateText;
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
 //connect(pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l->self(), SLOT(propertyChange(PropertyChangeEvent*)));
}

/*protected*/ void ConnectionStatus::firePropertyChange(QString p, QVariant old, QVariant n)
{
 log->debug ("firePropertyChange \"" + p + "\" old: " +old.toString() + " new: "+ n.toString());
    pcs->firePropertyChange(p,old,n);
}

/*public*/ /*synchronized*/ void ConnectionStatus::removePropertyChangeListener(PropertyChangeListener* l)
{
 pcs->removePropertyChangeListener(l);
 disconnect(pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l->self(), SLOT(propertyChange(PropertyChangeEvent*)));
}




