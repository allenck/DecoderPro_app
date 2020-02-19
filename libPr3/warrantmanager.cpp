#include "warrantmanager.h"
#include "warrant.h"
#include "rosterspeedprofile.h"
#include "instancemanager.h"
#include "shutdownmanager.h"
#include "shutdowntask.h"
#include "warrantshutdowntask.h"
#include "loggerfactory.h"
#include "scwarrant.h"

WarrantManager::WarrantManager(QObject *parent) :
    AbstractManager(parent)
{
 setObjectName("WarrantManager");
 setProperty("JavaClassName", "jmri.managers.WarrantManager");
 setProperty("InstanceManagerAutoDefault", "yes");

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
 * Method to create a new Warrant if it does not exist Returns null if a
 * Warrant with the same systemName or userName already exists, or if there
 * is trouble creating a new Warrant.
 *
 * @param systemName the system name
 * @param userName   the user name
 * @return an existing warrant if found or a new warrant
 */
/*public*/ Warrant* WarrantManager::createNewWarrant(QString systemName, QString userName, bool SCWa, long TTP) {
    log->debug("createNewWarrant " + systemName + " SCWa="+(SCWa?"true":"false"));
    // Check that Warrant does not already exist
    Warrant* r;
    if (userName != "" && userName.trimmed().length() > 0) {
        r = (Warrant*)getByUserName(userName);
        if (r == nullptr) {
            r = (Warrant*)getBySystemName(systemName);
        }
        if (r != nullptr) {
            log->warn("Warrant " + r->getDisplayName() + "  exits.");
            return nullptr;
        }
    }
    if (!systemName.startsWith("IW") || systemName.length() < 3) {
        log->error("Warrant system name \"" + systemName + "\" must begin with \"IW\".");
        return nullptr;
    }
    // Warrant does not exist, create a new Warrant
    if (SCWa) {
        r = new SCWarrant(systemName, userName, TTP);
    } else {
        r = new Warrant(systemName, userName);
    }
    // save in the maps
    Register(r);
    return r;
}


/**
 * Method to get an existing Warrant.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ Warrant* WarrantManager::getWarrant(QString name) {
    Warrant* r = (Warrant*)getByUserName(name);
    if (r!=NULL) return r;
    return (Warrant*)getBySystemName(name);
}

/*public*/ NamedBean *WarrantManager::getBySystemName(QString name) {
    if (name==NULL || name.trimmed().length()==0) { return NULL; }
    QString key = name.toUpper();
    return (Warrant*)_tsys->value(key);
}

/*public*/ NamedBean *WarrantManager::getByUserName(QString key) {
    if (key==NULL || key.trimmed().length()==0) { return NULL; }
    return (Warrant*)_tuser->value(key);
}

/*public*/ Warrant* WarrantManager::provideWarrant(QString name) {
    if (name==NULL || name.trimmed().length()==0) { return NULL; }
    Warrant* w = (Warrant*)getByUserName(name);
    if (w==NULL) {
        w = (Warrant*)getBySystemName(name);
    }
    if (w==NULL) {
        w = createNewWarrant(name, NULL, false, 0);
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

/*protected*/ void WarrantManager::setSpeedProfiles(QString id, RosterSpeedProfile* merge, RosterSpeedProfile* session) {
    if (_mergeProfiles == nullptr) {
        _mergeProfiles = new QMap<QString, RosterSpeedProfile*>();
        _sessionProfiles = new QMap<QString, RosterSpeedProfile*>();
        if (InstanceManager::getNullableDefault("ShutDownManager") != nullptr) {
            ShutDownTask* shutDownTask = new WarrantShutdownTask("WarrantRosterSpeedProfileCheck");
                    static_cast<ShutDownManager*>(InstanceManager::getDefault("ShutDownManager"))->_register(shutDownTask);
        } else {
            log->error("No ShutDownManager for WarrantRosterSpeedProfileCheck");
        }
    }
    if (id != nullptr && merge != nullptr) {
        _mergeProfiles->insert(id, merge);
        _sessionProfiles->insert(id, session);
    }
}

/*protected*/ RosterSpeedProfile*  WarrantManager::getMergeProfile(QString id) {
    if (_mergeProfiles == nullptr) {
        return nullptr;
    }
    return _mergeProfiles->value(id);
}
/*protected*/ RosterSpeedProfile* WarrantManager::getSessionProfile(QString id) {
    if (_sessionProfiles == nullptr) {
        return nullptr;
    }
    return _sessionProfiles->value(id);
}


/*protected*/ QMap<QString, RosterSpeedProfile*>* WarrantManager::getMergeProfiles() {
    return _mergeProfiles;
}
/*protected*/ QMap<QString, RosterSpeedProfile*>* WarrantManager::getSessionProfiles() {
    return _sessionProfiles;
}
/*private*/ /*final*/ /*static*/ Logger* WarrantManager::log = LoggerFactory::getLogger("WarrantManager");
