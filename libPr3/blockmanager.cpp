#include "blockmanager.h"
#include "instancemanager.h"
#include "sensormanager.h"
#include "reportermanager.h"
#include "powermanager.h"
#include "vptr.h"
#include "nosuchmethoderror.h"
#include "rosterentry.h"
#include "limits.h"
#include "loggerfactory.h"

///*static*/ BlockManager* BlockManager::_instance = NULL;

BlockManager::BlockManager(QObject *parent) :
    AbstractBlockManager(parent)
{
 setObjectName("BlockManager");
 setProperty("JavaClassName", "jmri.BlockManager");
 setProperty("InstanceManagerAutoDefault", "true");

 registerSelf();
 saveBlockPath = true;
 lastAutoBlockRef = 0;
 defaultSpeed = "Normal";
 paddedNumber = new DecimalFormat("0000");

 static_cast<SensorManager*>(InstanceManager::getDefault("SensorManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
 //connect(InstanceManager::sensorManagerInstance()->vcs, SIGNAL(vetoablePropertyChange(PropertyChangeEvent*)), this, SLOT(vetoableChange(PropertyChangeEvent*)));

static_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
 //connect(static_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->vcs, SIGNAL(vetoablePropertyChange(PropertyChangeEvent*)), this, SLOT(vetoableChange(PropertyChangeEvent*)));
 //InstanceManager.getList(PowerManager.class).forEach((pm) -> {
 foreach(QObject* pm, *InstanceManager::getList("PowerManager"))
 {
     //static_cast<PowerManager*>(pm)->addPropertyChangeListener(this);
  //connect(static_cast<PowerManager*>(pm)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }//);
 powerManagerChangeName = InstanceManager::getListPropertyName("PowerManager");
 InstanceManager::addPropertyChangeListener((PropertyChangeListener*)this);
 //connect(InstanceManager::getDefault(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}
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

//    /*public*/ BlockManager() {
//        super();
//    }

    /*public*/ int BlockManager::getXMLOrder()const{
        return Manager::BLOCKS;
    }

    /*public*/ QString BlockManager::getSystemPrefix()const { return "I"; }
    /*public*/ char BlockManager::typeLetter() const { return 'B'; }

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
/*public*/ Block* BlockManager::createNewBlock(QString systemName, QString userName) const
{
 // Check that Block does not already exist
 Block* r ;
 if (!userName.isNull() && !userName.isEmpty())
 {
  r = (Block*)getByUserName(userName);
  if (r!=NULL) return NULL;
 }
 r = (Block*)getBySystemName(systemName);
 if (r!=NULL) return NULL;
 // Block does not exist, create a new Block
 QString sName = systemName.toUpper();
 r = new Block(sName,userName);

 updateAutoNumber(systemName);
 // save in the maps
 Register(r);
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

/*public*/ Block* BlockManager::createNewBlock(QString userName) const{
 return createNewBlock(getAutoSystemName(), userName);
}

/*public*/ Block* BlockManager::provideBlock(QString name) const  {
 if (name.isEmpty()) {
     throw IllegalArgumentException("Could not create block, no name supplied");
 }
 Block* b = getBlock(name);
 if (b != nullptr) {
     return b;
 }

 if (name.startsWith(getSystemNamePrefix())) {
     b = createNewBlock(name, QString());
 } else {
     b = createNewBlock(name);
 }
 if (b == nullptr) {
     throw IllegalArgumentException("Could not create block \"" + name + "\"");
 }
 return b;
}


/**
 * Method to get an existing Block.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ Block* BlockManager::getBlock(QString name) const{
    Block* r = (Block*)getByUserName(name);
    if (r!=NULL) return r;
    return (Block*)getBySystemName(name);
}
#if 1
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
 Block* retv = (Block*)this->getByUserName(key);
 if (retv == NULL)
 {
     retv = (Block*)this->getBySystemName(key);
 }
 // If it's not in the system list, go ahead and return NULL
 return (retv);
}


//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="NP_NULL_PARAM_DEREF", justification="We are validating user input however the value is stored in its original format")
/*public*/ void BlockManager::setDefaultSpeed(QString speed) throw (JmriException)
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
    } catch (NumberFormatException nx) {
        try{
 // TODO:           jmri.implementation.SignalSpeedMap.getMap().getSpeed(speed);
        } catch (Exception ex){
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
    foreach(NamedBean* b, getNamedBeanSet())
    {
        if (b != nullptr) {
            QVariant val = ((Block*)b)->getValue();
            RosterEntry* obj = VPtr<RosterEntry>::asPtr(val) ;
            if ((obj && obj == re) ||
                    obj->toString() == (re->getId()) ||
                    obj->toString() == (re->getDccAddress())) {
                blockList.append((Block*)b);
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
  QStringList nameList = getSystemNameList();
  QStringList completerList;
  foreach(QString systemName, nameList)
  {
   Block* b = (Block*)getBySystemName(systemName);
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
            PowerManager* pm = (PowerManager*) e->getSource();
            if (pm->getPower() == PowerManager::ON) {
                lastTimeLayoutPowerOn = /*Instant::now()*/ QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
            }
        } catch (JmriException  xe) {
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
            PowerManager* pm = VPtr<PowerManager>::asPtr( e->getOldValue());
            pm->removePropertyChangeListener((PropertyChangeListener*)this);
            //disconnect(pm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        } else {
            // a powermanager has been added
         PowerManager* pm = VPtr<PowerManager>::asPtr( e->getOldValue());
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
    QDateTime::currentMSecsSinceEpoch() - lastTimeLayoutPowerOn;
}

/*public*/ void BlockManager::vetoableChange(PropertyChangeEvent* evt)
{
 AbstractManager::vetoableChange(evt);
}

//@Override
/*public*/ Block* BlockManager::provide(QString name) const throw (IllegalArgumentException) {
    return provideBlock(name);
}
/*private*/ /*static*/ /*final*/ Logger* BlockManager::log = LoggerFactory::getLogger("BlockManager");
