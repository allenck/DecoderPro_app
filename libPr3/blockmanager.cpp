#include "blockmanager.h"

/*static*/ BlockManager* BlockManager::_instance = NULL;

BlockManager::BlockManager(QObject *parent) :
    AbstractManager(parent)
{
 setObjectName("BlockManager");
 registerSelf();
 saveBlockPath = true;
 lastAutoBlockRef = 0;
 defaultSpeed = "Normal";
 paddedNumber = new DecimalFormat("0000");
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

    /*public*/ int BlockManager::getXMLOrder(){
        return Manager::BLOCKS;
    }

    /*public*/ QString BlockManager::getSystemPrefix() { return "I"; }
    /*public*/ char BlockManager::typeLetter() { return 'B'; }


    /*public*/ bool BlockManager::savePathInfo() { return saveBlockPath; }

    /*public*/ void BlockManager::savePathInfo(bool save) { saveBlockPath=save; }

/**
 * Method to create a new Block if it does not exist
 *   Returns NULL if a Block with the same systemName or userName
 *       already exists, or if there is trouble creating a new Block.
 */
/*public*/ Block* BlockManager::createNewBlock(QString systemName, QString userName)
{
 // Check that Block does not already exist
 Block* r ;
 if (!userName.isEmpty() && !userName.isEmpty())
 {
  r = getByUserName(userName);
  if (r!=NULL) return NULL;
 }
 r = getBySystemName(systemName);
 if (r!=NULL) return NULL;
 // Block does not exist, create a new Block
 QString sName = systemName.toUpper();
 r = new Block(sName,userName);
 // save in the maps
 Register(r);

 emit newBlockCreated(r);

 /*The following keeps trace of the last created auto system name. currently we do not reuse numbers, although there is nothing to stop the user from manually recreating them*/
 if (systemName.startsWith("IB:AUTO:"))
 {
  try
  {
   bool bOk=false;
   int autoNumber = /*Integer.parseInt(*/systemName.mid(8).toInt(&bOk);
   if(!bOk) throw new NumberFormatException();
   if (autoNumber > lastAutoBlockRef)
   {
    lastAutoBlockRef = autoNumber;
   }
  }
  catch (NumberFormatException* e)
  {
   log.warn("Auto generated SystemName "+ systemName + " is not in the correct format");
  }
 }
 try
 {
  r->setBlockSpeed("Global");
 }
 catch (JmriException* ex)
 {
  log.error(ex->toString());
 }
 return r;
}

/*public*/ Block* BlockManager::createNewBlock(QString userName) {
    int nextAutoBlockRef = lastAutoBlockRef+1;
    QString b = QString("IB:AUTO:");
    QString nextNumber = paddedNumber->format(nextAutoBlockRef);
    b.append(nextNumber);
    return createNewBlock(b, userName);
}

/*public*/ Block* BlockManager::provideBlock(QString name) {
    Block* b = getBlock(name);
    if (b!=NULL) return b;
    if (name.startsWith(getSystemPrefix()+typeLetter()))
        return createNewBlock(name, NULL);
    else
        return createNewBlock(makeSystemName(name), NULL);
}


/**
 * Method to get an existing Block.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ Block* BlockManager::getBlock(QString name) {
    Block* r = getByUserName(name);
    if (r!=NULL) return r;
    return getBySystemName(name);
}

/*public*/ Block* BlockManager::getBySystemName(QString name) {
    QString key = name.toUpper();
    return (Block*)_tsys->value(key);
}

/*public*/ Block* BlockManager::getByUserName(QString key) {
    return (Block*)_tuser->value(key);
}

/*public*/ Block* BlockManager::getByDisplayName(QString key) {
// First try to find it in the user list.
// If that fails, look it up in the system list
Block* retv = this->getByUserName(key);
if (retv == NULL)
{
    retv = this->getBySystemName(key);
}
// If it's not in the system list, go ahead and return NULL
return(retv);
}



/*static*/ /*public*/ BlockManager* BlockManager::instance() {
    if (_instance == NULL) {
        _instance = new BlockManager();
    }
    return (_instance);
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

/*public*/ QString BlockManager::getDefaultSpeed()
{
    return defaultSpeed;
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
   Block* b = getBySystemName(systemName);
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


