#include "warrantmanager.h"
#include "warrant.h"

WarrantManager::WarrantManager(QObject *parent) :
    AbstractManager(parent)
{
 setObjectName("WarrantManager");
 registerSelf();
}
/**
 * Basic Implementation of a WarrantManager.
 * <P>
 * Note this is a concrete class.
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
 * @author      Pete Cressman Copyright (C) 2009
 * @version     $Revision: 22528 $
 */
///*public*/ class WarrantManager extends AbstractManager
//    implements java.beans.PropertyChangeListener, jmri.InstanceManagerAutoDefault {

//    /*public*/ WarrantManager() {
//        super();
//    }

/*public*/ int WarrantManager::getXMLOrder(){
    return Manager::WARRANTS;
}

/*public*/ QString WarrantManager::getSystemPrefix() { return "I"; }
/*public*/ char WarrantManager::typeLetter() { return 'W'; }

/**
 * Method to create a new Warrant if it does not exist
 *   Returns NULL if a Warrant with the same systemName or userName
 *       already exists, or if there is trouble creating a new Warrant.
 */
/*public*/ Warrant* WarrantManager::createNewWarrant(QString systemName, QString userName) {
    // Check that Warrant does not already exist
    Warrant* r;
    if (userName!= NULL && userName.trimmed().length() > 0) {
        r = getByUserName(userName);
        if (r!=NULL) return NULL;
    }
    QString sName = systemName.toUpper();
    if (!sName.startsWith("IW")) {
        sName = "IW"+sName;
    }
    if (sName.length() < 3) {
        return NULL;
    }
    r = getBySystemName(sName);
    if (r!=NULL) return NULL;
    // Warrant does not exist, create a new Warrant
    r = new Warrant(sName,userName);
    // save in the maps
    Register(r);
    emit propertyChange(new PropertyChangeEvent(this, "length", QVariant(), QVariant(_tsys->count())));
    return r;
}

/**
 * Method to get an existing Warrant.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ Warrant* WarrantManager::getWarrant(QString name) {
    Warrant* r = getByUserName(name);
    if (r!=NULL) return r;
    return getBySystemName(name);
}

/*public*/ Warrant* WarrantManager::getBySystemName(QString name) {
    if (name==NULL || name.trimmed().length()==0) { return NULL; }
    QString key = name.toUpper();
    return (Warrant*)_tsys->value(key);
}

/*public*/ Warrant* WarrantManager::getByUserName(QString key) {
    if (key==NULL || key.trimmed().length()==0) { return NULL; }
    return (Warrant*)_tuser->value(key);
}

/*public*/ Warrant* WarrantManager::provideWarrant(QString name) {
    if (name==NULL || name.trimmed().length()==0) { return NULL; }
    Warrant* w = getByUserName(name);
    if (w==NULL) {
        w = getBySystemName(name);
    }
    if (w==NULL) {
        w = createNewWarrant(name, NULL);
    }
    return w;
}

/*static*/ WarrantManager* WarrantManager::_instance = NULL;
/*static*/ /*public*/ WarrantManager* WarrantManager::instance() {
    if (_instance == NULL) {
        _instance = new WarrantManager();
    }
    return (_instance);
}
