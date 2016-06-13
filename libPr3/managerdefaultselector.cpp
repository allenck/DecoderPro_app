#include "managerdefaultselector.h"
#include "systemconnectionmemo.h"
#include "instancemanager.h"

//ManagerDefaultSelector::ManagerDefaultSelector(QObject *parent) :
//    QObject(parent)
//{
//}
#if 1
/**
 * Records and executes a desired set of defaults
 * for the JMRI InstanceManager and ProxyManagers
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * @author			Bob Jacobsen Copyright (C) 2010
 * @version			$Revision: 28100 $
 * @since           2.9.4
 */
// /*public*/ class ManagerDefaultSelector {

/*public*/ /*static*/ /*final*/ ManagerDefaultSelector* ManagerDefaultSelector::instance = new ManagerDefaultSelector();

/* public static synchronized ManagerDefaultSelector instance() {
    if (instance == NULL) {
        if (log.isDebugEnabled()) log.debug("Manager Default Selector creating instance");
        // create and load
        instance = new ManagerDefaultSelector();
    }
    if (log.isDebugEnabled()) log.debug("ManagerDefaultSelector returns instance "+instance);
    return instance;
}*/

/*private*/ ManagerDefaultSelector::ManagerDefaultSelector(QObject *parent) : QObject(parent)
{
 log = new Logger("ManagerDefaultSlector");
 setObjectName("ManagerDefaultSelector");
 defaults =  QMap<QString, QString>();
 knownManagers = QList<Item*>();
 knownManagers <<
             new Item("Throttles", "ThrottleManager") <<
             new Item("<html>Power<br>Control</html>", "PowerManager") <<
             new Item("<html>Command<br>Station</html>", "CommandStation")<<
             new Item("<html>Service<br>Programmer</html>", "GlobalProgrammerManager")<<
             new Item("<html>Ops Mode<br>Programmer</html>", "AddressedProgrammerManager")<<
             new Item( "Consists ", "ConsistManager");
 //SystemConnectionMemo::addPropertyChangeListener(new PropertyChangeListener(){
 SystemConnectionMemo* memo =   (SystemConnectionMemo*)InstanceManager::getDefault("SystemConnectionMemo");
 connect(memo, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void ManagerDefaultSelector::propertyChange(PropertyChangeEvent* e)
{
 if(e->getPropertyName()==("ConnectionNameChanged"))
 {
  QString oldName =  e->getOldValue().toString();
  QString newName =  e->getNewValue().toString();
  foreach (QString c, defaults.keys())
  {
   QString connectionName = ManagerDefaultSelector::instance->defaults.value(c);
   if(connectionName==(oldName))
    ManagerDefaultSelector::instance->defaults.insert(c, newName);
  }
 }
 else if (e->getPropertyName()==("ConnectionDisabled"))
 {
  bool newState = e->getNewValue().toBool();
  if(newState)
  {
   SystemConnectionMemo* memo = (SystemConnectionMemo*)e->getSource();
   QString disabledName = memo->getUserName();
   QStringList tmpArray =  QStringList();
   foreach (QString c, defaults.keys())
   {
    QString connectionName = ManagerDefaultSelector::instance->defaults.value(c);
    if(connectionName==(disabledName))
    {
     log->warn("Connection " + disabledName + " has been disabled, we shall remove it as the default for " + c);
     tmpArray.append(c);
//                                ManagerDefaultSelector.instance.defaults.remove(c);
    }
   }
   for(int i = 0; i<tmpArray.size(); i++)
   {
    ManagerDefaultSelector::instance->defaults.remove(tmpArray.at(i));
   }
  }
 }
 else if (e->getPropertyName()==("ConnectionRemoved"))
 {
  QString removedName = e->getOldValue().toString();
  QStringList tmpArray =  QStringList();
  foreach (QString c, defaults.keys())
  {
   QString connectionName = ManagerDefaultSelector::instance->defaults.value(c);
   if(connectionName==(removedName))
   {
    log->warn("Connection " + removedName + " has been removed, we shall remove it as the default for " + c);
    //ManagerDefaultSelector.instance.defaults.remove(c);
    tmpArray.append(c);
   }
  }
  for(int i = 0; i<tmpArray.size(); i++)
  {
   ManagerDefaultSelector::instance->defaults.remove(tmpArray.at(i));
  }
 }
 notifyPropertyChangeListener("Updated", QVariant(), QVariant());
}

/**
 * Return the userName of the system
 * that provides the default instance
 * for a specific class.
 * @param managerClass the specific type, e.g. TurnoutManager,
 *          for which a default system is desired
 * @return userName of the system, or NULL if none set
 */
/*public*/ QString ManagerDefaultSelector::getDefault(QString managerClass)
{
 return defaults.value(managerClass);
}

/**
 * Record the userName of the system
 * that provides the default instance
 * for a specific class.
 *
 * To ensure compatibility of different preference versions,
 * only classes that are current registered are preserved.
 * This way, reading in an old file will just have irrelevant
 * items ignored.
 *
 * @param managerClass the specific type, e.g. TurnoutManager,
 *          for which a default system is desired
 * @param userName of the system, or NULL if none set
 */
/*public*/ void ManagerDefaultSelector::setDefault(QString managerClass, QString userName)
{
 foreach (Item* item, knownManagers)
 {
  if (item->managerClass==(managerClass))
  {
   defaults.insert(managerClass, userName);
   return;
  }
 }
 log->warn(QString("Ignoring preference for class %1 with name %2").arg(managerClass).arg( userName));
}

/**
 * load into InstanceManager
 */
//@SuppressWarnings("unchecked")
/*public*/ void ManagerDefaultSelector::configure()
{
 QList<SystemConnectionMemo*>* connList = (QList<SystemConnectionMemo*>*)InstanceManager::getList("SystemConnectionMemo");
 if (connList == NULL) return; // nothing to do

  if(defaults.size()== 0) return;
 foreach (QString c, defaults.keys())
 {
  // 'c' is the class to load
  QString connectionName = ManagerDefaultSelector::instance->defaults.value(c);
  // have to find object of that type from proper connection
  bool found = false;
  for (int x = 0; x<connList->size(); x++)
  {
   SystemConnectionMemo* memo = connList->at(x);
   QString testName = memo->getUserName();
   if (testName==(connectionName))
   {
    found = true;
    // match, store
    InstanceManager::setDefault(c, memo->get(c));
    break;
   }
  }
  /*
   * If the set connection can not be found then we shall set the manager default to use what
   * has currently been set.
   */
  if(!found)
  {
   QString currentName = NULL;
   if(c == "ThrottleManager" && InstanceManager::throttleManagerInstance()!=NULL)
   {
    currentName = InstanceManager::throttleManagerInstance()->getUserName();
   }
    else if(c=="PowerManager" && InstanceManager::powerManagerInstance()!=NULL)
    {
     currentName = InstanceManager::powerManagerInstance()->getUserName();
    }
    else if (c=="ProgrammerManager" && InstanceManager::programmerManagerInstance()!=NULL)
    {
     currentName = InstanceManager::programmerManagerInstance()->getUserName();
    }
   if(currentName!=NULL)
   {
    log->warn("The configured " + connectionName + " for " + c + " can not be found so will use the default " + currentName);
ManagerDefaultSelector::instance->defaults.insert(c, currentName);
   }
  }
 }
}



///*public*/ static class Item {
//    /*public*/ QString typeName;
//    /*public*/ QString managerClass;
//    /*public*/ bool proxy;
    ManagerDefaultSelector::Item::Item(QString typeName,QString managerClass) {
        this->typeName = typeName;
        this->managerClass = managerClass;
    }
//}

/*public*/ /*synchronized*/ void ManagerDefaultSelector::removePropertyChangeListener(PropertyChangeListener* l) {
    if (listeners.contains(l)) {
        listeners.remove(listeners.indexOf(l));
    }
}

/*public*/ /*synchronized*/ void ManagerDefaultSelector::addPropertyChangeListener(PropertyChangeListener* l) {
    // add only if not already registered
    if (!listeners.contains(l)) {
        listeners.append(l);
    }
}

/**
 * Trigger the notification of all PropertyChangeListeners
 */
//@SuppressWarnings("unchecked")
/*protected*/ void ManagerDefaultSelector::notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue) {
    // make a copy of the listener vector to synchronized not needed for transmit
    QVector<PropertyChangeListener*> v;
//    synchronized(this)
        {
         //v = (QVector<PropertyChangeListener*>) listeners.clone();
         foreach (PropertyChangeListener* l, listeners)
         {
            v.append(l);
         }
        }
    // forward to all listeners
    int cnt = v.size();
    for (int i=0; i < cnt; i++) {
        PropertyChangeListener* client = v.at(i);
        client->propertyChange(new PropertyChangeEvent(this, property, oldValue, newValue));
    }
    emit notifyPropertyChange(new PropertyChangeEvent(this, property, oldValue, newValue));
}
 /*final*/ /*private*/ /*static*/ QVector<PropertyChangeListener*> ManagerDefaultSelector::listeners =  QVector<PropertyChangeListener*>();

//    static Logger log = LoggerFactory.getLogger(ManagerDefaultSelector.class.getName());
//}

#endif
