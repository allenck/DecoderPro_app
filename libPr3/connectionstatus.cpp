#include "connectionstatus.h"

/*public*/ /*static*/ const QString ConnectionStatus::CONNECTION_UNKNOWN = "Unknown";
/*public*/ /*static*/ const QString ConnectionStatus::CONNECTION_UP = "Connected";
/*public*/ /*static*/ const QString ConnectionStatus::CONNECTION_DOWN = "Not Connected";
QMutex* ConnectionStatus::mutex = new QMutex();
ConnectionStatus* ConnectionStatus::_instance = NULL;
QStringList* ConnectionStatus::portNames= new QStringList();
QStringList* ConnectionStatus::portStatus = new QStringList();


ConnectionStatus::ConnectionStatus(QObject *parent) :
    QObject(parent)
{
 log = new Logger("ConnectionStatus");
 pcs = new PropertyChangeSupport(this);
 setObjectName("ConnectionStatus");
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
 QMutexLocker locker(mutex);
 log->debug ("add connection to monitor " + systemName + " " + portName);
 if (portName == NULL)
  return;
 if (portNames->contains(portName))
  return;
 portNames->append(portName);
 portStatus->append(CONNECTION_UNKNOWN);
 firePropertyChange("add", QVariant(), QVariant(portName));
}
/**
 * sets the connection state of a communication port
 * @param portName = communication port name
 * @param state
 */
/*public*/ /*synchronized*/ void ConnectionStatus::setConnectionState(QString portName, QString state)
{
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
}

/**
 * get the status of a communication port
 * @param portName
 * @return status string
 */
/*public*/ /*synchronized*/ QString ConnectionStatus::getConnectionState(QString portName)
{
 //QMutexLocker locker(mutex);
 QString stateText = CONNECTION_UNKNOWN;
 if (portNames->contains(portName))
 {
  for (int i=0; i<portNames->size(); i++)
  {
   if (portName==(portNames->at(i)))
   {
    stateText = portStatus->at(i);
    break;
   }
  }
 }
 log->debug ("get connection status: " + portName + " " + stateText);
 return stateText;
}

/**
 * Returns status of a communication port
 * @param portName
 * @return true if port connection is operational or unknown, false if not
 */
/*public*/ /*synchronized*/ bool ConnectionStatus::isConnectionOk(QString portName)
{
 QString stateText = getConnectionState(portName);
 //QMutexLocker locker(mutex);
 if (stateText!=(CONNECTION_UP))
  return false;
 else
  return true;
}

/*public*/ /*synchronized*/ void ConnectionStatus::addPropertyChangeListener(PropertyChangeListener* l)
{
 pcs->addPropertyChangeListener(l);
 connect(pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*protected*/ void ConnectionStatus::firePropertyChange(QString p, QVariant old, QVariant n)
{
 log->debug ("firePropertyChange \"" + p + "\" old: " +old.toString() + " new: "+ n.toString());
    pcs->firePropertyChange(p,old,n);
}

/*public*/ /*synchronized*/ void ConnectionStatus::removePropertyChangeListener(PropertyChangeListener* l)
{
 pcs->removePropertyChangeListener(l);
 disconnect(pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
}
