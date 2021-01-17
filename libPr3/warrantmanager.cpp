#include "warrantmanager.h"
#include "warrant.h"
#include "rosterspeedprofile.h"
#include "instancemanager.h"
#include "shutdownmanager.h"
#include "shutdowntask.h"
#include "warrantshutdowntask.h"
#include "loggerfactory.h"
#include "scwarrant.h"
#include "oblock.h"
#include "portal.h"
#include "joptionpane.h"
#include "blockorder.h"
#include "opath.h"

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

/*public*/ int WarrantManager::getXMLOrder() const{
    return Manager::WARRANTS;
}

/*public*/ QString WarrantManager::getSystemPrefix()const { return "I"; }
/*public*/ char WarrantManager::typeLetter()const { return 'W'; }

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

/*public*/ Warrant *WarrantManager::getBySystemName(QString name) const {
    if (name==NULL || name.trimmed().length()==0) { return NULL; }
    QString key = name.toUpper();
    return (Warrant*)_tsys->value(key);
}

/*public*/ Warrant *WarrantManager::getByUserName(QString key) const{
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

/*protected*/ bool WarrantManager::okToRemoveBlock(OBlock* block) {
    QString name = block->getDisplayName();
    QList<Warrant*> list = warrantsUsing(block);
    bool ok = true;
    if (!list.isEmpty()) {
//            ok = false;   Last setting was OK = true when _suppressWarnings was set to true
        if (!_suppressWarnings) {
            QString sb;// = new StringBuilder();
            for (Warrant* w : list) {
                sb.append(tr("Deleting block \"%1\" will disable warrant%2\{1}\".").arg(name).arg(w->getDisplayName()));
            }
            sb.append(tr("Do you want to delete \"%1\" and remove these disabled warrants?").arg(name));
            ok = okToRemove(name, sb);
        }
    }
    if (ok) {
        removeWarrants(list);
    }
    return ok;
}

/*protected*/ bool WarrantManager::okToRemovePortal(Portal* portal) {
    QString name = portal->getName();
    bool ok = true;
    QList<Warrant*> wList = warrantsUsing(portal);
    if (!wList.isEmpty()) {
//          ok = false;   Last setting was OK = true when _suppressWarnings was set to true
        if (!_suppressWarnings) {
            QString sb;// = new StringBuilder();
            for (Warrant* w : wList) {
                sb.append(tr("Deleting portal \"%1\" will disable warrant \"%2\".").arg(name).arg(w->getDisplayName()));
             }
            sb.append(tr("Do you want to delete \"%1\" and remove these disabled warrants?").arg(name));
            ok = okToRemove(name, sb);
        }
    }
    QList<NamedBean*> sList = signalsUsing(portal);
    if (!sList.isEmpty()) {
//          ok = false;   Last setting was OK = true when _suppressWarnings was set to true
        if (!_suppressWarnings) {
            QString sb;// = new StringBuilder();
            for (NamedBean* s : sList) {
                sb.append(tr("If portal \"%1\" is deleted, signal \"%2\" cannot protect block \"%3\".").arg(
                        name).arg(s->getDisplayName()).arg(portal->getProtectedBlock(s)->getDescription()));
             }
            sb.append(tr("Do you want to delete \"%1\"and undo configuration of these signals?").arg(name));
            ok = okToRemove(name, sb);
        }
    }

    if (ok) {
        removeWarrants(wList);
        for (NamedBean* s : sList) {
            portal->deleteSignal(s);
        }
    }
    return ok;
}

/*protected*/ bool WarrantManager::okToRemoveBlockPath(OBlock* block, OPath* path) {
    QString pathName = path->getName();
    QString blockName = block->getDisplayName();
    bool ok = true;
    QList<Warrant*> list = warrantsUsing(block, path);
    if (!list.isEmpty()) {
//          ok = false;   Last setting was OK = true when _suppressWarnings was set to true
        if (!_suppressWarnings) {
            QString sb;// = new StringBuilder();
            for (Warrant* w : list) {
                sb.append(tr("Deleting path \"%1\" in block \"%2\" will disable warrant \"{%3\".").arg(
                        pathName).arg(blockName).arg(w->getDisplayName()));
             }
            sb.append(tr("Do you want to delete \"%1\" and remove these disabled warrants?").arg(pathName));
            ok = okToRemove(pathName, sb);
        }
    }
    if (ok) {
        removeWarrants(list);
    }
    return ok;
}

/*private*/ void WarrantManager::removeWarrants(QList<Warrant*> list) {
    for (Warrant* w : list) {
        if (w->getRunMode() != Warrant::MODE_NONE) {
            w->controlRunTrain(Warrant::ABORT);
        }
        deregister(w);
        w->dispose();
    }
}

/*private*/ bool WarrantManager::okToRemove(QString name, QString message) {
//    if (!ThreadingUtil.isLayoutThread()) {  //need GUI
//        log.warn("Cannot delete portal \"{}\" from this thread", name);
//        return false;
//    }
 QVariantList object = {tr("Yes"), tr("YesPlus"), tr("no")};
    int val = JOptionPane::showOptionDialog(nullptr, message,
            tr("Warning"), JOptionPane::YES_NO_CANCEL_OPTION,
            JOptionPane::QUESTION_MESSAGE, QIcon(),
            object,
            QVariant("No")); // default NO
    if (val == 2) {
        return false;
    }
    if (val == 1) { // suppress future warnings
        _suppressWarnings = true;
    }
    return true;
}
/*synchronized*/ /*protected*/ void WarrantManager::portalNameChange(QString oldName, QString newName) {
    for (NamedBean* nb : getNamedBeanSet()) {
     Warrant* w = (Warrant*)nb;
        QList<BlockOrder*>* orders = w->getBlockOrders();
        QListIterator<BlockOrder*> it(*orders);
        while (it.hasNext()) {
            BlockOrder* bo = it.next();
            if (oldName == (bo->getEntryName())) {
                bo->setEntryName(newName);
            }
            if (oldName == (bo->getExitName())) {
                bo->setExitName(newName);
            }
        }
    }
}

/*protected*/ QList<Warrant*> WarrantManager::warrantsUsing(OBlock* block) {
    QList<Warrant*> list = QList<Warrant*>();
    for (NamedBean* nb : getNamedBeanSet()) {
     Warrant* w = (Warrant*)nb;
        QList<BlockOrder*>* orders = w->getBlockOrders();
        QListIterator<BlockOrder*> it(*orders);
        while (it.hasNext()) {
            if (block->equals(it.next()->getBlock()))
                list.append(w);
        }
    }
    return list;
}

/*protected*/QList<Warrant*> WarrantManager::warrantsUsing(Portal* portal) {
    QList<Warrant*> list = QList<Warrant*>();
    QString name = portal->getName();
    for (NamedBean* nb : getNamedBeanSet()) {
     Warrant* w = (Warrant*)nb;
        QList<BlockOrder*>* orders = w->getBlockOrders();
        QListIterator<BlockOrder*> it(*orders);
        while (it.hasNext()) {
            BlockOrder* bo = it.next();
            if (name == (bo->getEntryName()) && !list.contains(w)) {
                list.append(w);
            } else if (name == (bo->getExitName()) && !list.contains(w)) {
                list.append(w);
            }
        }
    }
    return list;
}

/*protected*/ QList<NamedBean*> WarrantManager::signalsUsing(Portal* portal) {
    QList<NamedBean*> list = QList<NamedBean*>();
    NamedBean* signal = portal->getToSignal();
    if (signal != nullptr) {
        list.append(signal);
    }
    signal = portal->getFromSignal();
    if (signal != nullptr) {
        list.append(signal);
    }
    return list;
}

/*protected*/ QList<Warrant*> WarrantManager::warrantsUsing(OBlock* block, OPath* path) {
    QList<Warrant*> list = QList<Warrant*>();
    QString name = path->getName();
    for (NamedBean* nb : getNamedBeanSet()) {
     Warrant* w = (Warrant*)nb;
        QList<BlockOrder*>* orders = w->getBlockOrders();
        QListIterator<BlockOrder*> it(*orders);
        while (it.hasNext()) {
            BlockOrder* bo = it.next();
            if (block->equals(bo->getBlock()) && name == (bo->getPathName())) {
                list.append(w);
            }
        }
    }
    return list;
}
/*synchronized*/ /*protected*/ void WarrantManager::pathNameChange(OBlock* block, QString oldName, QString newName) {
 for (NamedBean* nb : getNamedBeanSet()) {
  Warrant* w = (Warrant*)nb;
        QList<BlockOrder*>* orders = w->getBlockOrders();
        QListIterator<BlockOrder*> it(*orders);
        while (it.hasNext()) {
            BlockOrder* bo = it.next();
            if (bo->getBlock()->equals(block) && bo->getPathName()==(oldName)) {
                bo->setPathName(newName);
            }
        }
    }
}

/**
 * Get the default WarrantManager.
 *
 * @return the default WarrantManager, creating it if necessary
 */
/*public*/ /*static*/ WarrantManager* WarrantManager::getDefault() {
     WarrantManager* result = (WarrantManager*)InstanceManager::getOptionalDefault("WarrantManager");//.orElseGet(() -> {
     if(!result)
        return (WarrantManager*)InstanceManager::setDefault("WarrantManager", new WarrantManager());
    else
        return result;
}

//@Override
//@Nonnull
/*public*/ QString WarrantManager::getBeanTypeHandled(bool plural) {
    return tr(plural ? "Warrants" : "Warrant");
}
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString WarrantManager::getNamedBeanClass() {
    return "Warrant";
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
