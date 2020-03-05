#include "portalmanager.h"
#include "portal.h"

PortalManager::PortalManager(QObject *parent) :
  AbstractManager(parent)
{
 setProperty("InstanceManagerAutoDefault", "yes");
 registerSelf();
}
/**
 * Basic Implementation of a PortalManager.
 * <P>
 * Note that this does not enforce any particular system naming convention.
 * <P>
 * Note this is an 'after thought' manager. Portals have been in use since 2009.
 * Their use has now expanded well beyond what was expected. A Portal factory is
 * needed for development to continue.
 *
 * Portal system names will be numbers and they will not be shown to users. The
 * UI will treat Portal names as it does now as user names.
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Pete Cressman Copyright (C) 2014
 * @version $Revision: 22821 $
 */
///*public*/ class PortalManager extends AbstractManager
//        implements java.beans.PropertyChangeListener, jmri.InstanceManagerAutoDefault {

/*private*/ /*static*/ int PortalManager::_nextSName = 1;

//    /*public*/ PortalManager() {
//        super();
//    }
    /*
 public void PortalManager::setNextSysNum(int next) {
 _nextSName = next;
 }
 public int PortalManager::getNextSysNum() {
 return _nextSName;
 }
 */

/*public*/ int PortalManager::getXMLOrder() const{
    return Manager::OBLOCKS;
}

/*public*/ QString PortalManager::getSystemPrefix() const{
    return "I";
}

/*public*/ char PortalManager::typeLetter()const {
    return 'P';
}

/**
 * Method to create a new Portal if it does not exist Returns NULL if a
 * Portal with the same systemName or userName already exists, or if there
 * is trouble creating a new Portal. Generate a systemName if called with
 * sName==NULL
 */
/*public*/ Portal* PortalManager::createNewPortal(QString sName, QString userName) {
    // Check that Portal does not already exist
    Portal* portal;
    if (userName != NULL && userName.trimmed().length() > 0) {
        portal = (Portal*)getByUserName(userName);
        if (portal != NULL) {
            return NULL;
        }
    } else {  // must have a user name for backward compatibility
        return NULL;
    }
    if (sName == NULL) {
        sName = generateSystemName();
    }
    if (!sName.startsWith("IP")) {
        sName = "IP" + sName;
    }
    if (sName.length() < 3) {
        return NULL;
    }
    portal = (Portal*)getBySystemName(sName);
    if (portal != NULL) {
        return NULL;
    }
    // Portal does not exist, create a new Portal
    portal = new Portal(sName, userName);
    // save in the maps
    Register(portal);
    return portal;
}

/*public*/ QString PortalManager::generateSystemName() {
    QString name;
    do {
        name = "IP" + QString::number(_nextSName++);
    } while (getBySystemName(name) != NULL);
    return name;
}

/**
 * Method to get an existing Portal. First looks up assuming that name is a
 * User Name. If this fails looks up assuming that name is a System Name. If
 * both fail, returns NULL.
 */
/*public*/ Portal* PortalManager::getPortal(QString name) {
    Portal* portal = (Portal*)getByUserName(name);
    if (portal != NULL) {
        return portal;
    }
    return (Portal*)getBySystemName(name);
}

/*public*/ NamedBean *PortalManager::getBySystemName(QString name)const {
    if (name == NULL || name.trimmed().length() == 0) {
        return NULL;
    }
    return (Portal*) _tsys->value(name);
}

/*public*/ NamedBean *PortalManager::getByUserName(QString key) const{
    if (key == NULL || key.trimmed().length() == 0) {
        return NULL;
    }
    return (Portal*) _tuser->value(key);
}

/*public*/ Portal* PortalManager::providePortal(QString name) {
    if (name == NULL || name.trimmed().length() == 0) {
        return NULL;
    }
    Portal* portal = (Portal*)getByUserName(name);
    if (portal == NULL) {
        portal = createNewPortal(NULL, name);
    }
    return portal;
}

/*protected*/ void PortalManager::registerSelf() {
    // Override, don't register, OBlockManager does store and load of Portals
}

/*static*/ PortalManager* PortalManager::_instance = NULL;

/*static*/ /*public*/ PortalManager* PortalManager::instance() {
    if (_instance == NULL) {
        _instance = new PortalManager();
    }
    return (_instance);
}

/*public*/ QString PortalManager::getBeanTypeHandled() {
    return tr("Portal");
}
