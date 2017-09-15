#include "transitmanager.h"
#include "decimalformat.h"
#include "section.h"

TransitManager::TransitManager(QObject *parent) :
    AbstractManager(parent)
{
 paddedNumber = new DecimalFormat("0000");
 lastAutoTransitRef = 0;
 registerSelf();
}
/*static*/ TransitManager* TransitManager::_instance = NULL;

/**
 * Implementation of a Transit Manager
 * <P>
 * This doesn't need an interface, since Transits are
 * globaly implemented, instead of being system-specific.
 * <P>
 * Note that Transit system names must begin with IZ, and be followed by a
 * string, usually, but not always, a number. All alphabetic characters
 * in a Transit system name must be upper case. This is enforced when a Transit
 * is created.
 * <P>
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
 * @author      Dave Duchamp Copyright (C) 2008, 2011
 * @version	$Revision: 21084 $
 */
//public class TransitManager extends AbstractManager
//    implements java.beans.PropertyChangeListener {

//    public TransitManager() {
//        super();
//    }

    int TransitManager::getXMLOrder(){
        return Manager::TRANSITS;
    }

    QString TransitManager::getSystemPrefix() { return "I"; }
    char TransitManager::typeLetter() { return 'Z'; }

    /**
     * Method to create a new Transit if the Transit does not exist
     *   Returns NULL if a Transit with the same systemName or userName
     *       already exists, or if there is trouble creating a new Transit.
     */
    Transit* TransitManager::createNewTransit(QString systemName, QString userName) {
        // check system name
        if ( (systemName=="") || (systemName.length()<1) ) {
            // no valid system name entered, return without creating
            return NULL;
        }
        QString sysName = systemName;
        if ( (sysName.length()<2) || (sysName.mid(0,2)!=("IZ")) ) {
            sysName = "IZ"+sysName;
        }
        // Check that Transit does not already exist
        Transit* z;
        if (userName!= "" ) {
            z = getByUserName(userName);
            if (z!=NULL) return NULL;
        }
        QString sName = sysName.toUpper().trimmed();
        z = getBySystemName(sysName);
        if (z==NULL) z = getBySystemName(sName);
        if (z!=NULL) return NULL;
        // Transit does not exist, create a new Transit
        z = new Transit(sName,userName);
        // save in the maps
        Register(z);
        return z;
    }
    /**
     * For use with User GUI, to allow the auto generation of systemNames,
     * where the user can optionally supply a username.
     * Note: Since system names should be kept short for use in Dispatcher, the :AUTO:000 has been removed
     *    from automatically generated system names.
     *    Autogenerated system names will use IZnn, where nn is the first available number.
     */
    /*public*/ Transit* TransitManager::createNewTransit(QString userName) {
        bool found =false;
        QString testName = "";
        Transit* z;
        while (!found) {
            int nextAutoTransitRef = lastAutoTransitRef+1;
            testName = "IZ"+nextAutoTransitRef;
            z = getBySystemName(testName);
            if (z==NULL) found = true;
            lastAutoTransitRef = nextAutoTransitRef;
        }
        return createNewTransit(testName, userName);
    }


    /**
     * Method to get an existing Transit.  First looks up assuming that
     *      name is a User Name.  If this fails looks up assuming
     *      that name is a System Name.  If both fail, returns NULL.
     *
     * @param name
     * @return NULL if no match found
     */
    /*public*/ Transit* TransitManager::getTransit(QString name) {
        Transit* z = getByUserName(name);
        if (z!=NULL) return z;
        return getBySystemName(name);
    }

    /*public*/ Transit* TransitManager::getBySystemName(QString name) {
        QString key = name.toUpper();
        return (Transit*)_tsys->value(key);
    }

    /*public*/ Transit* TransitManager::getByUserName(QString key) {
        return (Transit*)_tuser->value(key);
    }

    /**
     * Remove an existing Transit
     */
    /*public*/ void TransitManager::deleteTransit(Transit* z) {
        // delete the Transit
        deregister(z);
        z->dispose();
    }
    /**
     * Returns a list of Transits which use a specified Section
     */
    /*public*/ QList<Transit*>* TransitManager::getListUsingSection(Section* s)
    {
     QList<Transit*>* list = new QList<Transit*>();
     QStringList tList = getSystemNameList();
     for (int i = 0; i < tList.size(); i++)
     {
      QString tName = tList.at(i);
            if ( (tName!=NULL) && (tName.length()>0) ) {
                Transit* tTransit = getTransit(tName);
                if (tTransit!=NULL) {
                    if (tTransit->containsSection(s)) {
                        // this Transit uses the specified Section
                        list->append(tTransit);
                    }
                }
            }
        }
        return list;
    }

    /*static*/ /*public*/ TransitManager* TransitManager::instance()
    {
        if (_instance == NULL) {
            _instance = new TransitManager();
        }
        return (_instance);
    }

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TransitManager.class.getName());
//}


/* @(#)TransitManager.java */
