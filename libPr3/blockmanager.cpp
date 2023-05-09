#include "blockmanager.h"
#include "instancemanager.h"
#include "abstractpowermanager.h"
#include "vptr.h"
#include "nosuchmethoderror.h"
#include "rosterentry.h"
#include "limits.h"
#include "loggerfactory.h"
#include "jmriexception.h"

/**
 * Basic Implementation of a BlockManager.
 * <P>
 * Note that this does not enforce any particular system naming convention.
 * <P>
 * Note this is a concrete class, unlike the interface/implementation pairs
 * of most Managers, because there are currently only one implementation for Blocks.
 *
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
 *
 * @author      Bob Jacobsen Copyright (C) 2006
 * @version	$Revision: 22187 $
 */
///*public*/ class BlockManager extends AbstractManager
//    implements java.beans.PropertyChangeListener {

BlockManager::BlockManager(QObject *parent) :
    AbstractBlockManager(parent)
{
 setObjectName("BlockManager");
 setProperty("JavaClassName", "jmri.BlockManager");
 setProperty("InstanceManagerAutoDefault", "true");
 setProperty("AdapterName", "jmri.configurexml.BlockManagerXml");

 registerSelf();
 saveBlockPath = true;
 lastAutoBlockRef = 0;
 defaultSpeed = "Normal";
 paddedNumber = new DecimalFormat("0000");

 ((AbstractProxyManager*)InstanceManager::getDefault("SensorManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
 ((AbstractProxyManager*)InstanceManager::getDefault("ReporterManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
 //InstanceManager.getList("PowerManager").forEach(pm -> pm.addPropertyChangeListener(this));
 for(QObject* obj : *InstanceManager::getList("PowerManager"))
 {
  ((PowerManager*)obj)->addPropertyChangeListener(this);
 }
 powerManagerChangeName = InstanceManager::getListPropertyName("PowerManager");
 InstanceManager::addPropertyChangeListener(this);
 ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->_register(shutDownTask);
}

    //@Override
    /*public*/ void BlockManager::dispose() {
        AbstractManager::dispose();
//        ((BlockManager*)InstanceManager::getDefault("BlockManager"))->deregister(shutDownTask);
    }

    /*public*/ int BlockManager::getXMLOrder()const{
        return Manager::BLOCKS;
    }

    /*public*/ QString BlockManager::getSystemPrefix() const { return "I"; }
    /*public*/ QChar BlockManager::typeLetter()  const { return 'B'; }

    //@Override
    /*public*/ QString BlockManager::getNamedBeanClass()const {
        return "Block";
    }


    //@CheckReturnValue
    /*public*/ bool BlockManager::isSavedPathInfo() {
        return saveBlockPath;
    }

    /*public*/ void BlockManager::setSavedPathInfo(bool save) {
        saveBlockPath = save;
    }


/**
 * Method to create a new Block if it does not exist
 *   Returns NULL if a Block with the same systemName or userName
 *       already exists, or if there is trouble creating a new Block.
 */
/*public*/ Block* BlockManager::createNewBlock(QString systemName, QString userName)
{
 // Check that Block does not already exist
 Block* r ;
 NamedBean* nb;
 if (!userName.isNull() && !userName.isEmpty())
 {
  nb = AbstractManager::getByUserName(userName);
  if (nb) return(Block*)nb->self();
 }
 nb = AbstractManager::getBySystemName(systemName);
 if (nb) return(Block*)nb->self();

 // Block does not exist, create a new Block
 QString sName = systemName.toUpper();
 r = new Block(sName,userName);

 updateAutoNumber(systemName);
 // save in the maps
 AbstractManager::Register(r);
 try
 {
  r->setBlockSpeed("Global");
 }
 catch (JmriException* ex)
 {
  log->error(ex->toString());
 }
 return r;
}

/*public*/ Block* BlockManager::createNewBlock(QString userName) {
 return createNewBlock(getAutoSystemName(), userName);
}

/*public*/ Block* BlockManager::provideBlock(QString name)  {
 if (name.isEmpty()) {
     throw new IllegalArgumentException("Could not create block, no name supplied");
 }
 Block* b = getBlock(name);
 if (b != nullptr) {
     return b;
 }

 if (name.startsWith(AbstractManager::getSystemNamePrefix())) {
     b = createNewBlock(name, QString());
 } else {
     b = createNewBlock(name);
 }
 if (b == nullptr) {
     throw new IllegalArgumentException("Could not create block \"" + name + "\"");
 }
 return b;
}


/**
 * Method to get an existing Block.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ Block* BlockManager::getBlock(QString name) {
    NamedBean* nb = AbstractManager::getByUserName(name);
    if (nb)
     return (Block*)nb->self();
    nb = AbstractManager::getBySystemName(name);
    if (!nb)
     return nullptr;
    else
     return (Block*)nb->self();

}
#if 0
/*public*/ Block *BlockManager::getBySystemName(QString name) const {
    QString key = name.toUpper();
    return (Block*)_tsys->value(key);
}

/*public*/ Block* BlockManager::getByUserName(QString key) const {
    return (Block*)_tuser->value(key);
}
#endif
/*public*/ Block* BlockManager::getByDisplayName(QString key)
{
 // First try to find it in the user list.
 // If that fails, look it up in the system list
 Block* retv = (Block*)this->AbstractManager::getByUserName(key)->self();
 if (retv == NULL)
 {
     retv = (Block*)this->AbstractManager::getBySystemName(key)->self();
 }
 // If it's not in the system list, go ahead and return NULL
 return (retv);
}


//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="NP_NULL_PARAM_DEREF", justification="We are validating user input however the value is stored in its original format")
/*public*/ void BlockManager::setDefaultSpeed(QString speed) /*throw (JmriException)*/
{
    if(speed==NULL)
        throw new JmriException("Value of requested default thrown speed can not be NULL");
    if (defaultSpeed==(speed))
        return;

    try {
        //Float.parseFloat(speed);
        bool bOk = false;
        float f = speed.toFloat(&bOk);
        if(!bOk) throw new NumberFormatException();
    } catch (NumberFormatException* nx) {
        try{
 // TODO:           jmri.implementation.SignalSpeedMap.getMap().getSpeed(speed);
        } catch (Exception* ex){
            throw new JmriException("Value of requested default block speed is not valid");
        }
    }
    QString oldSpeed = defaultSpeed;
    defaultSpeed = speed;
    firePropertyChange("DefaultBlockSpeedChange", oldSpeed, speed);
}

///*static*/ /*public*/ BlockManager* BlockManager::instance() {
//    if (_instance == NULL) {
//        _instance = new BlockManager();
//    }
//    return (_instance);
//}



/*public*/ QString BlockManager::getDefaultSpeed()
{
    return defaultSpeed;
}

//@Override
//@CheckReturnValue
//@Nonnull
/*public*/ QString BlockManager::getBeanTypeHandled(bool plural)const {
    return tr(plural ? "Blocks" : "Block");
}

/**
 * Get a list of blocks which the supplied roster entry appears to be
 * occupying. A block is assumed to contain this roster entry if its value
 * is the RosterEntry itself, or a string with the entry's id or dcc
 * address.
 *
 * @param re the roster entry
 * @return list of block system names
 */
//@CheckReturnValue
//@Nonnull
/*public*/ QList<Block*> BlockManager::getBlocksOccupiedByRosterEntry(/*@Nonnull*/ RosterEntry* re) {
    QList<Block*> blockList = QList<Block*>();
    //getNamedBeanSet().stream().forEach(b ->
    foreach(NamedBean* b, AbstractManager::getNamedBeanSet())
    {
        if (b != nullptr) {
            QVariant val = ((Block*)b->self())->getValue();
            RosterEntry* obj = VPtr<RosterEntry>::asPtr(val) ;
            if ((obj && obj == re) ||
                    obj->toString() == (re->getId()) ||
                    obj->toString() == (re->getDccAddress())) {
                blockList.append((Block*)b->self());
            }
        }
    }//);
    return blockList;
}
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(BlockManager.class.getName());
//}
QCompleter* BlockManager::getCompleter(QString text)
{
 if(text.length()>2)
 {
  QStringList nameList = AbstractManager::getSystemNameList();
  QStringList completerList;
  foreach(QString systemName, nameList)
  {
   Block* b = (Block*)AbstractManager::getBySystemName(systemName)->self();
   if(b->getUserName().startsWith(text))
    completerList.append(b->getUserName());
  }
  if(completerList.size() > 0)
  {
   QCompleter* completer = new QCompleter(completerList, this);
    return completer;
  }
 }
 return NULL;
}


/**
 * Listen for changes to the power state from any power managers
 * in use in order to track how long it's been since power was applied
 * to the layout. This information is used in {@link Block#goingActive()}
 * when deciding whether to restore a block's last value.
 *
 * Also listen for additions/removals or PowerManagers
 *
 * @param e - the change event
 */

//@Override
/*public*/ void BlockManager::propertyChange(PropertyChangeEvent* e) {
    AbstractManager::propertyChange(e);
    if (PowerManager::POWER == (e->getPropertyName())) {
        try {
            PowerManager* pm = (AbstractPowerManager*) e->getSource();
            if (pm->getPower() == PowerManager::ON) {
                lastTimeLayoutPowerOn = /*Instant::now()*/ QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
            }
        } catch (JmriException*  xe) {
            // do nothing
        }
     catch (NoSuchMethodError xe)
     {
      // do nothing
     }
    }
    if (powerManagerChangeName == (e->getPropertyName())) {
        if (e->getNewValue() == QVariant()) {
            // powermanager has been removed
            PowerManager* pm = VPtr<AbstractPowerManager>::asPtr( e->getOldValue());
            pm->removePropertyChangeListener((PropertyChangeListener*)this);
            //disconnect(pm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        } else {
            // a powermanager has been added
         PowerManager* pm = VPtr<AbstractPowerManager>::asPtr( e->getOldValue());
         if(pm)
            pm->addPropertyChangeListener((PropertyChangeListener*)this);
         //connect(pm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

        }
    }
}
/**
    * Get the amount of time since the layout was last powered up,
    * in milliseconds. If the layout has not been powered up as far as
    * JMRI knows it returns a very long time indeed.
 *
 * @return long int
 */
/*public*/ qint64 BlockManager::timeSinceLastLayoutPowerOn()const {
    if (lastTimeLayoutPowerOn == 0) {
        return LONG_LONG_MAX;
    }
    //return Instant.now().toEpochMilli() - lastTimeLayoutPowerOn.toEpochMilli();
   return QDateTime::currentMSecsSinceEpoch() - lastTimeLayoutPowerOn;
}

///*public*/ void BlockManager::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException)
//{
// AbstractManager::vetoableChange(evt);
//}

//@Override
/*public*/ NamedBean *BlockManager::provide(QString name)  /*throw (IllegalArgumentException)*/ {
    return provideBlock(name);
}
#if 1
// try to resolve these:
/*public*/ SystemConnectionMemo*  BlockManager::getMemo()
{
 return AbstractManager::getMemo();
}
/*public*/ NamedBean* BlockManager::getNamedBean(QString s)
{
 return AbstractManager::getNamedBean(s);
}
/*public*/ void BlockManager::Register(NamedBean* b)
{
 AbstractManager::Register(b);
}
/*public*/ void BlockManager::deregister(NamedBean* b)
{
 AbstractManager::deregister(b);
}
/*public*/ void BlockManager::addDataListener(Manager::ManagerDataListener* l)
{
 AbstractManager::addDataListener(l);
}
/*public*/ void BlockManager::removeDataListener(Manager::ManagerDataListener* l)
{
 AbstractManager::removeDataListener(l);
}
#endif
/*private*/ /*static*/ /*final*/ Logger* BlockManager::log = LoggerFactory::getLogger("BlockManager");
