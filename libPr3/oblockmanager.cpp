#include "oblockmanager.h"
#include "oblock.h"

OBlockManager::OBlockManager(QObject *parent) :
    AbstractManager(parent)
{
 setObjectName("OBlockManager");
 setProperty("JavaClassName", "jmri.jmrit.logix.OBlockManager");
 setProperty("InstanceManagerAutoDefault", "yes");

 registerSelf();
}
/**
 * Basic Implementation of a OBlockManager.
 * <P>
 * Note that this does not enforce any particular system naming convention.
 * <P>
 * Note this is a concrete class, there are now 2 types of Blocks (LayoutBlocks use
 * a Block member.  LBlocks use inheritance.  Perhaps now the proxyManager strategy
 * of interface/implementation pairs like other Managers should be implemented.
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
 * @author      Pete Cressman Copyright (C) 2009
 * @version     $Revision: 22528 $
 */
///*public*/ class OBlockManager extends AbstractManager
//    implements java.beans.PropertyChangeListener, jmri.InstanceManagerAutoDefault {

//    /*public*/ OBlockManager() {
//        super();
//    }

/*public*/ int OBlockManager::getXMLOrder(){
    return Manager::OBLOCKS;
}

/*public*/ QString OBlockManager::getSystemPrefix() { return "O"; }
/*public*/ char OBlockManager::typeLetter() { return 'B'; }

/**
 * Method to create a new OBlock if it does not exist
 *   Returns NULL if a OBlock with the same systemName or userName
 *       already exists, or if there is trouble creating a new OBlock.
 */
/*public*/ OBlock* OBlockManager::createNewOBlock(QString systemName, QString userName)
{
    // Check that OBlock does not already exist
    OBlock* r;
    if (userName!= NULL && userName!=("")) {
        r = getByUserName(userName);
        if (r!=NULL) return NULL;
    }
    QString sName = systemName.toUpper();
    if (!sName.startsWith("OB")) {
        sName = "OB"+sName;
    }
    if (sName.length() < 3) {
        return NULL;
    }
    r = getBySystemName(sName);
    if (r!=NULL) return NULL;
    // OBlock does not exist, create a new OBlock
    r = new OBlock(sName,userName);
    // save in the maps
    Register(r);
    return r;
}

/**
 * Method to get an existing OBlock.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ OBlock* OBlockManager::getOBlock(QString name) {
    OBlock* r = getByUserName(name);
    if (r!=NULL) return r;
    return getBySystemName(name);
}

/*public*/ OBlock* OBlockManager::getBySystemName(QString name) {
    if (name==NULL || name.trimmed().length()==0) { return NULL; }
    QString key = name.toUpper();
    return (OBlock*)_tsys->value(key);
}

/*public*/ OBlock* OBlockManager::getByUserName(QString key) {
    if (key==NULL || key.trimmed().length()==0) { return NULL; }
    return (OBlock*)_tuser->value(key);
}
//@Override
/*public*/ OBlock* OBlockManager::provide(QString name) throw (IllegalArgumentException) {
    return provideOBlock(name);
}

/*public*/ OBlock* OBlockManager::provideOBlock(QString name) {
    if (name==NULL || name.length()==0) { return NULL; }
    OBlock* ob = getByUserName(name);
    if (ob==NULL) {
        ob = getBySystemName(name);
    }
    return ob;
}

/*static*/ OBlockManager* OBlockManager:: _instance = NULL;
/*static*/ /*public*/ OBlockManager* OBlockManager::instance() {
    if (_instance == NULL) {
        _instance = new OBlockManager();
    }
    return (_instance);
}
