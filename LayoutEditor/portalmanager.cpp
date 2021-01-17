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
/*public*/ int PortalManager::getPortalCount() {
        return _nameList.size();
}

/*public*/ Portal* PortalManager::getPortal(int idx) {
 if(_nameList.size() == 0)
  return nullptr;
    return _nameList.at(idx);
}
/*public*/ int PortalManager::getIndexOf(Portal* portal) {
    return _nameList.indexOf(portal);
}

/*public*/ int PortalManager::getXMLOrder() const{
    return Manager::OBLOCKS;
}

/*public*/ QString PortalManager::getSystemPrefix() const{
    return "I";
}

/*public*/ char PortalManager::typeLetter()const {
    return 'P';
}

/*
 * Create a new Portal with a given user name.
 *
 * @return null if a Portal with the same userName already exists,
 * or if an empty userName was requested
 */
/*public*/ Portal* PortalManager::createNewPortal(/*@Nonnull*/ QString userName) {
    //java.util.Objects.requireNonNull(userName, "Name cannot be null");
    // Check that Portal does not already exist
    Portal* portal = nullptr;
    if (userName.trimmed().length() > 0) {
        portal = _portalMap.value(userName);
        if (portal != nullptr) {
            return nullptr;
        }
    } else {  // must have a user name for backward compatibility
        return nullptr;
    }
    // Portal does not exist, create a new Portal
    portal = new Portal(userName);
    // save in the maps
    _nameList.append(portal);
    _portalMap.insert(userName, portal);
    _nextIndex = _nextIndex + 1;
    pcs->firePropertyChange("numPortals", QVariant(), _nameList.size());
    // listen for name and state changes to forward
    portal->addPropertyChangeListener((PropertyChangeListener*)this);
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

/*public*/ Portal *PortalManager::getBySystemName(QString name)const {
    if (name == NULL || name.trimmed().length() == 0) {
        return NULL;
    }
    return (Portal*) _tsys->value(name);
}

/*public*/ QSet<Portal*> PortalManager::getPortalSet() {
        //return Collections.unmodifiableCollection(_nameList);
 return _nameList.toSet();
    }

/*public*/ Portal *PortalManager::getByUserName(QString key) const{
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
        portal = createNewPortal( name);
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
