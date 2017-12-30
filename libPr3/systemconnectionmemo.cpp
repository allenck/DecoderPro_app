#include "systemconnectionmemo.h"
#include <QVariant>
#include <QVector>
#include "instancemanager.h"
#include "createbuttonmodel.h"
#include "resourcebundle.h"
#include "internalsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "startupactionmodelutil.h"

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
//QVector<PropertyChangeListener*> SystemConnectionMemo::listeners =QVector<PropertyChangeListener*>();
QStringList* SystemConnectionMemo::userNames = new QStringList();
QStringList* SystemConnectionMemo::sysPrefixes = new QStringList();
//QString SystemConnectionMemo::userName = "";
//QString SystemConnectionMemo::prefix = "";
SystemConnectionMemo* SystemConnectionMemo::_instance = NULL;
SystemConnectionMemo* SystemConnectionMemo::instance() {return _instance;}

//SystemConnectionMemo::SystemConnectionMemo(QObject *parent) : QObject(parent)
//{
//    disabled = false;
//    disabledAsLoaded = /*null*/ false; // Boolean can be true, false, or null
// initialise();
//}

SystemConnectionMemo::SystemConnectionMemo(QString prefix, QString userName, QObject *parent) :
    QObject(parent)
{
 disabled = false;
 disabledAsLoaded = /*null*/ false; // Boolean can be true, false, or null
 _instance = this;


 log->debug(tr("SystemConnectionMemo created for prefix \"%1\" user name \"%2\"").arg(prefix).arg(userName));
 initialise();
 if(!setSystemPrefix(prefix))
 {
  for (int x = 2; x<50; x++)
  {
   if(setSystemPrefix(prefix+QString("%1").arg(x)))
   {
    break;
   }
  }
 }

 if(!setUserName(userName))
 {
  for (int x = 2; x<50; x++)
  {
   if(setUserName(userName+QString("%1").arg(x)))
   {
    break;
   }
  }
 }
 addToActionList();
 // reset to null so these get set by the first setPrefix/setUserName
 // call after construction
 this->prefixAsLoaded = "";
 this->userNameAsLoaded = "";
}

/**
 * Provides a method to reserve System Names and prefixes at creation
 */
void SystemConnectionMemo::initialise(){
    log->debug("initialise called");
//    if (!initialised){
//        addUserName("Internal");
//        addSystemPrefix("I");
//        initialised = true;
//    }
}

bool SystemConnectionMemo::addUserName(QString userName){
    if (userNames == NULL)
        userNames = new QStringList();
    if (userNames->contains(userName))
        return false;

    userNames->append(userName);
    return true;
}

//This should probably throwing an exception
bool SystemConnectionMemo::addSystemPrefix(QString systemPrefix)
{
 if (sysPrefixes->contains(systemPrefix))
     return false;
 sysPrefixes->append(systemPrefix);
 return true;
}

void SystemConnectionMemo::removeUserName(QString userName){
 if(!userNames->isEmpty())
 {
  if (userNames->contains(userName)){
   int index = userNames->indexOf(userName);
   userNames->removeAt(index);
  }
 }
}

void SystemConnectionMemo::removeSystemPrefix(QString systemPrefix){
    if(!sysPrefixes->isEmpty())
    {
        if (sysPrefixes->contains(systemPrefix)){
            int index = sysPrefixes->indexOf(systemPrefix);
            sysPrefixes->removeAt(index);
        }
    }
}

/**
 * Store in InstanceManager with
 * proper ID for later retrieval as a
 * generic system
 */
void SystemConnectionMemo::Register()
{
 log->debug(tr("register as SystemConnectionMemo, really of type %1").arg(this->metaObject()->className()));

 // check for special case
 QObjectList* list = InstanceManager::getList("SystemConnectionMemo");
 if ((list->size() > 0) && (qobject_cast<InternalSystemConnectionMemo*>(list->at(list->size()-1)) != NULL))
 {
     // last is internal, so insert before that one
     log->debug("   putting one before end");
//     SystemConnectionMemo* old = (SystemConnectionMemo*)list->at(list->size()-1);
//     InstanceManager::deregister(old, "SystemConnectionMemo");
//     InstanceManager::store(this, "SystemConnectionMemo");
//     InstanceManager::store(old, "SystemConnectionMemo");
     InstanceManager::storeBefore(list->size()-1, this,"SystemConnectionMemo");
 } else {
     // just add on end
     InstanceManager::store(this, "SystemConnectionMemo");
 }

 notifyPropertyChangeListener("ConnectionAdded", QVariant(), QVariant());
}

/**
 * Provides access to the system prefix string.
 * This was previously called the "System letter"
 */
QString SystemConnectionMemo::getSystemPrefix() { return prefix; }

//This should probably throwing an exception
bool SystemConnectionMemo::setSystemPrefix(QString systemPrefix)
{
 if (systemPrefix == "")
  throw new NullPointerException();
 if (systemPrefix == (prefix))
 {
  if (this->prefixAsLoaded == "")
  {
   this->prefixAsLoaded = systemPrefix;
  }
  return true;
 }
 QString oldPrefix = prefix;
 if(addSystemPrefix(systemPrefix))
 {
  prefix = systemPrefix;
  if (this->prefixAsLoaded == "")
  {
   this->prefixAsLoaded = systemPrefix;
  }
  removeSystemPrefix(oldPrefix);
  notifyPropertyChangeListener("ConnectionPrefixChanged", QVariant(oldPrefix), QVariant(systemPrefix));
  return true;
 }
 log->debug(tr("setSystemPrefix false for \"%1\"").arg( systemPrefix));
 return false;
}

/**
 * Provides access to the system user name string.
 * This was previously fixed at configuration time.
 */
QString SystemConnectionMemo::getUserName() { return userName; }

//This should probably throwing an exception
bool SystemConnectionMemo::setUserName(QString name)
{
 if (name == "")
  throw new NullPointerException();
 if (name == (userName))
 {
  if (this->userNameAsLoaded == "")
  {
      this->userNameAsLoaded = name;
  }
  return true;
 }

 QString oldUserName = this->userName;
 if(addUserName(name))
 {
  this->userName = name;
  if (this->userNameAsLoaded == "")
  {
      this->userNameAsLoaded = name;
  }
  removeUserName(oldUserName);
  notifyPropertyChangeListener("ConnectionNameChanged", oldUserName, name);
  return true;
 }
 return false;
}

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
QObject* SystemConnectionMemo::get(QString T) {
 Q_UNUSED(T)
    return NULL; // nothing, by default
}

void SystemConnectionMemo::dispose(){
    removeFromActionList();
    removeUserName(userName);
    removeSystemPrefix(prefix);
//    InstanceManager::deregister(this, "SystemConnectionMemo");
    notifyPropertyChangeListener("ConnectionRemoved", QVariant(userName), QVariant());
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
// if (listeners.contains(l))
// {
//  int i = listeners.indexOf(l);
//  listeners.remove(i);
// }
//}

///*static*/ void SystemConnectionMemo::addPropertyChangeListener(PropertyChangeListener* l) {
//    // add only if not already registered
//    if (!listeners.contains(l)) {
//        listeners.append(l);
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


/*private*/ /*final*/ /*static*/ Logger* SystemConnectionMemo::log = LoggerFactory::getLogger("SystemConnectionMemo");
