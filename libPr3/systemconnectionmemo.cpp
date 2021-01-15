#include "systemconnectionmemo.h"
#include <QVariant>
#include <QVector>
#include "instancemanager.h"
#include "createbuttonmodel.h"
#include "resourcebundle.h"
#include "internalsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "startupactionmodelutil.h"
#include "systemconnectionmemomanager.h"
#include "nmraconsistmanager.h"
#include "addressedprogrammermanager.h"
#include "conflictingsystemconnectionmemo.h"
#include "defaultprogrammermanager.h"

/**
 * Lightweight abstract class to denote that a system is active,
 * and provide general information.
 * <p>
 * Objects of specific subtypes are registered
 * in the instance manager to activate their
 * particular system.
 *
 * @author		Bob Jacobsen  Copyright (C) 2010
 * @version             $Revision: 18843 $
 */

/*public*/ /*static*/ /*final*/ QString SystemConnectionMemo::DISABLED = "ConnectionDisabled";
/*public*/ /*static*/ /*final*/ QString SystemConnectionMemo::USER_NAME = "ConnectionNameChanged";
/*public*/ /*static*/ /*final*/ QString SystemConnectionMemo::SYSTEM_PREFIX = "ConnectionPrefixChanged";
/*public*/ /*static*/ /*final*/ QString SystemConnectionMemo::INTERVAL = "OutputInterval";

//QVector<PropertyChangeListener*>* SystemConnectionMemo::listeners = new QVector<PropertyChangeListener*>();
//QStringList* SystemConnectionMemo::userNames = new QStringList();
//QStringList* SystemConnectionMemo::sysPrefixes = new QStringList();
//QString SystemConnectionMemo::userName = "";
//QString SystemConnectionMemo::prefix = "";
//SystemConnectionMemo* SystemConnectionMemo::_instance = NULL;
//SystemConnectionMemo* SystemConnectionMemo::instance() {return _instance;}

//SystemConnectionMemo::SystemConnectionMemo(QObject *parent) : QObject(parent)
//{
//    disabled = false;
//    disabledAsLoaded = /*null*/ false; // Boolean can be true, false, or null
// initialise();
//}
#if 0
SystemConnectionMemo::SystemConnectionMemo(QString prefix, QString userName, QObject *parent) :
    QObject(parent)
{
 propertyChangeSupport = new PropertyChangeSupport(this);
 if(log == nullptr)
  log = LoggerFactory::getLogger("SystemConnectionMemo");

 disabled = false;
 disabledAsLoaded = /*null*/ false; // Boolean can be true, false, or null
// _instance = this;
 if (qobject_cast<ConflictingSystemConnectionMemo*>(this)) {
     this->prefix = prefix;
     this->userName = userName;
     return;
 }

 log->debug(tr("SystemConnectionMemo created for prefix \"%1\" user name \"%2\"").arg(prefix).arg(userName));
 //initialise();
#if 0
 if (!setSystemPrefix(prefix))
 {
  int x = 2;
  while (!setSystemPrefix(prefix + QString::number(x))) {
      x++;
  }
  log->debug(tr("created system prefix %1").arg(prefix + QString::number(x)));
 }

 if (!setUserName(userName))
 {
  int x = 2;
  while (!setUserName(userName + QString::number(x))) {
      x++;
  }
  log->debug(tr("created user name %1").arg(prefix + QString::number(x)));
 }
 addToActionList();
 // reset to null so these get set by the first setPrefix/setUserName
 // call after construction
 this->prefixAsLoaded = "";
 this->userNameAsLoaded = "";
#endif
}


/**
 * Store in InstanceManager with proper ID for later retrieval as a generic
 * system
 */
void SystemConnectionMemo::_register()
{
 log->debug(tr("register as SystemConnectionMemo, really of type %1").arg(this->metaObject()->className()));
 SystemConnectionMemoManager::getDefault()->_register(this);
}

/**
 * Provides access to the system prefix string.
 * This was previously called the "System letter"
 */
//QString SystemConnectionMemo::getSystemPrefix(); const

/**
 * Set the system prefix.
 *
 * @param systemPrefix prefix to use for this system connection
 * @throws java.lang.NullPointerException if systemPrefix is null
 * @return true if the system prefix could be set
 */
//bool SystemConnectionMemo::setSystemPrefix(QString systemPrefix)
//{
// // return true if systemPrefix is not being changed
// if (systemPrefix == (prefix)) {
//     if (this->prefixAsLoaded.isNull()) {
//         this->prefixAsLoaded = systemPrefix;
//     }
//     return true;
// }
// QString oldPrefix = prefix;
// if (SystemConnectionMemoManager::getDefault()->isSystemPrefixAvailable(systemPrefix)) {
//     prefix = systemPrefix;
//     if (this->prefixAsLoaded.isNull()) {
//         this->prefixAsLoaded = systemPrefix;
//     }
//     notifyPropertyChangeListener(/*SYSTEM_PREFIX*/"ConnectionPrefixChanged", oldPrefix, systemPrefix);
//     return true;
// }
// log->debug(tr("setSystemPrefix false for \"%1\"").arg(systemPrefix));
// return false;
//}



/**
 * Provide access to the system user name string.
 * <p>
 * This was previously fixed at configuration time.
 *
 * @return User name
 */
/*public*/ QString SystemConnectionMemo::getUserName() const {
    return userName;
}

/**
 * Set the user name for the system connection.
 *
 * @param userName user name to use for this system connection
 * @throws java.lang.NullPointerException if name is null
 * @return true if the user name could be set.
 */
/*public*/ /*final*/ bool SystemConnectionMemo::setUserName(/*@Nonnull*/ QString userName) {
    //Objects.requireNonNull(userName);
    if (userName == (this->userName)) {
        if (this->userNameAsLoaded == "") {
            this->userNameAsLoaded = userName;
        }
        return true;
    }
    QString oldUserName = this->userName;
    if (SystemConnectionMemoManager::getDefault()->isUserNameAvailable(userName)) {
        this->userName = userName;
        if (this->userNameAsLoaded == "") {
            this->userNameAsLoaded = userName;
        }
        //this.propertyChangeSupport.firePropertyChange(USER_NAME, oldUserName, userName);
        return true;
    }
    return false;
}
/**
  * Get the connection specific OutputInterval to wait between/before commands
  * are sent, configured in AdapterConfig.
  * Used in {@link jmri.implementation.AbstractTurnout#setCommandedStateAtInterval(int)}.
  *
  * @return the output interval time in ms
  */
int SystemConnectionMemo::getOutputInterval() {return 0;}

 /**
  * Get the Default connection specific OutputInterval to wait between/before commands
  * are sent.
  * @return the default output interval time in ms.
  */
int SystemConnectionMemo::getDefaultOutputInterval() {return 0;}

void SystemConnectionMemo::setOutputInterval(int /*newInterval*/) {}

/**
 * Does this connection provide a manager of this type?
 */
bool SystemConnectionMemo::provides(QString c) {
 Q_UNUSED(c)
    return false; // nothing, by default
}

/**
 * Does this connection provide a manager of this type?
 */
Manager* SystemConnectionMemo::get(QString T) {
 Q_UNUSED(T)
    return NULL; // nothing, by default
}

void SystemConnectionMemo::dispose(){
    removeFromActionList();
//    removeUserName(userName);
//    removeSystemPrefix(prefix);
 SystemConnectionMemoManager::getDefault()->deregister(this);
}

bool SystemConnectionMemo::getDisabled()
{
 return disabled;
}

void SystemConnectionMemo::setDisabled(bool disabled)
{
 if(disabled==this->disabled)
  return;
 bool oldDisabled = this->disabled;
 this->disabled = disabled;
 notifyPropertyChangeListener("ConnectionDisabled", oldDisabled, disabled);
}

///*static*/void SystemConnectionMemo::removePropertyChangeListener(PropertyChangeListener* l)
//{
// if (listeners->contains(l))
// {
//  int i = listeners->indexOf(l);
//  listeners->remove(i);
// }
//}

///*static*/ void SystemConnectionMemo::addPropertyChangeListener(PropertyChangeListener* l) {
//    // add only if not already registered
//    if ( !listeners->contains(l)) {
//        listeners->append(l);
//    }
//}

/**
 * Trigger the notification of all PropertyChangeListeners
 */
//@SuppressWarnings("unchecked")
void SystemConnectionMemo::notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue)
{
//    if(listeners == NULL)
//        listeners = new QVector<PropertyChangeListener*>;
//    // make a copy of the listener vector to synchronized not needed for transmit
//    QVector<PropertyChangeListener*>* v = new QVector<PropertyChangeListener*>(listeners);
////    synchronized(this)
////        {
////            v = (QVector<PropertyChangeListener>) listeners.clone();
////        }
//    // forward to all listeners
//    int cnt = v->size();
//    for (int i=0; i < cnt; i++) {
//        PropertyChangeListener* client = v->at(i);
//        client->propertyChange( new PropertyChangeEvent(this, property, oldValue, newValue));
//    }
// foreach (PropertyChangeListener* listener, *listeners) {
//  connect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
// }
    emit propertyChange(new PropertyChangeEvent(this,  property, oldValue, newValue));
}


void SystemConnectionMemo::addToActionList()
{
#if 1
// CreateButtonModel* bm = (CreateButtonModel*)InstanceManager::getDefault("CreateButtonModel");
 StartupActionModelUtil* util = StartupActionModelUtil::getDefault();
 ResourceBundle* rb = getActionModelResourceBundle();
 if (rb==NULL )
   return;
 QStringListIterator e = rb->keys();
 while (e.hasNext())
 {
  QString key = e.next();
  try
  {
   util->addAction(key, rb->getString(key));
  }
  catch (ClassNotFoundException ex)
  {
   log->error("Did not find class "+key);
  }
 }
#endif
}

void SystemConnectionMemo::removeFromActionList()
{
// CreateButtonModel* bm = (CreateButtonModel*)InstanceManager::getDefault("CreateButtonModel");
 StartupActionModelUtil* util = StartupActionModelUtil::getDefault();
 ResourceBundle* rb = getActionModelResourceBundle();
 if (rb==NULL)
  return;
 QStringListIterator  e(rb->keys());
 while (e.hasNext())
 {
  QString key = e.next();
  try
  {
   util->removeAction(key);
  }
  catch (ClassNotFoundException ex)
  {
   log->error("Did not find class "+key);
  }
 }
}

/*public*/ bool SystemConnectionMemo::isDirty()
{
 return ((this->disabledAsLoaded == false || this->disabledAsLoaded != this->disabled)
      || (this->prefixAsLoaded == NULL || this->prefixAsLoaded!=(this->prefix))
      || (this->userNameAsLoaded == NULL || this->userNameAsLoaded!=(this->userName)));
}

/*public*/ bool SystemConnectionMemo::isRestartRequired()
{
 return this->isDirty();
}

/**
 * Provide access to the Consist Manager for this particular connection.
 * <p>
 * NOTE: Consist manager defaults to NULL
 */
/*public*/ ConsistManager* SystemConnectionMemo::getConsistManager() {
    if (consistManager == nullptr) {
        // a consist manager doesn't exist, so we can create it.
        if (provides("CommandStation")) {
            setConsistManager(new NmraConsistManager((CommandStation*)get("CommandStation")));
        } else if (provides("AddressedProgrammerManager")) {
            setConsistManager(new DccConsistManager((DefaultProgrammerManager*)get("AddressedProgrammerManager")));
        }
    }
    return consistManager;
}

/*public*/ void SystemConnectionMemo::setConsistManager(ConsistManager* c) {
    consistManager = c;
    InstanceManager::store(consistManager->self(), "ConsistManager");
}


/*private*/ /*final*/ /*static*/ Logger* SystemConnectionMemo::log = LoggerFactory::getLogger("SystemConnectionMemo");
#endif
