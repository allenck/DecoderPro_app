#ifndef CONFIGUREMANAGER_H
#define CONFIGUREMANAGER_H

#include <QObject>
#include "file.h"
#include <QUrl>
#include "xmlfile.h"
#include "exceptions.h"

class ConfigureManager :  public XmlFile
{
    //Q_OBJECT
public:
    //explicit ConfigureManager(QObject *parent = 0) : XmlFile(parent) {}
    /**
     * Provide load/store capabilities for general configuration.
     * <P>
     * Areas of responsibility:
     * <UL>
     * <LI>Register and deregister configuration objects so they can
     * eventually be stored.
     * <LI>Invoke the load and store operations as needed
     * <LI>Give access to the configuration objects for independent GUIs
     * </UL>
     *<P>
     *The managed items are divided into four types:
     *<OL>
     *<LI>"Prefs" - handled first on read, these are the general preferences
     *controlling how the program starts up
     *<LI>"Config" - layout configuration information, e.g. turnout, signal, etc
     *<LI>"Tool" - (Not really clear yet, but present)
     *<LI>"User" - typically information about panels and windows, these are handled
     *last during startup
     *</OL>
     *<P>
     *The configuration manager is generally located through the InstanceManager.
     *<P>
     *The original implementation was via the {@link jmri.configurexml} package.
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
     * @author	Bob Jacobsen Copyright (C) 2002
     * @version     $Revision: 22561 $
     * @see jmri.InstanceManager
     * @see jmri.configurexml.ConfigXmlManager
     */
//    public interface ConfigureManager {
    ConfigureManager(QObject* parent = 0) : XmlFile(parent) {}
    ~ConfigureManager() {}
    ConfigureManager(const ConfigureManager&) : XmlFile() {}
        virtual void registerPref(QObject* /*o*/) {}
        virtual void removePrefItems() {}

        virtual void registerConfig(QObject* /*o*/) {}
        virtual void registerConfig(QObject* /*o*/, int /*x*/) {}
        virtual void registerTool(QObject* /*o*/) {}
    virtual void registerUser(QObject* ) {}
        virtual void registerUserPrefs(QObject* /*o*/) {}

        virtual void deregister(QObject* /*o*/) {}

        /**
         * Find the ith instance of an object of particular class
         * that's been registered for storage.
         *<p>
         * Note that the index of an object can change when
         * other objects are stored or removed.  The index is
         * for indexing over the objects stored at a moment,
         * not for use as an identification number.
         *<P>
         * There may be synchronization issues associated with
         * this, although they are expected to be rare in practice.
         * @param c Class of the desired objects
         * @param index a 1-based index of the object to return
         * @return an object of class c or null
         */
        virtual QObject* findInstance(QString /*c*/, int /*index*/) {return NULL;}

        /**
         * Returns a list of instances stored for a given class.
         *
         * @param c Class of the desired objects
         * @return an ArrayList of objects of class c or null
         */
    virtual QObjectList getInstanceList(QString /*c*/) {return QObjectList();}

        /**
         * Stores prefs, config, tools and user information.
         * @param file Output file
         * @return true if succeeded
         */
        virtual bool storeAll(File* /*file*/) const {return false;}
        /**
         * Stores just preferences information.
         * <p>
         * Where that information is stored is implementation-specific.
         */
    virtual void storePrefs() /*const*/ {Logger::error("storePrefs not overridden like it should be!");}

        /**
         * Stores just preferences information.
         */
        virtual void storePrefs(File* /*file*/) /*const*/ {}

        /**
         * Stores just user preferences information.
         */
        virtual void storeUserPrefs(File* /*file*/) /*const*/ {}

        /**
         * Stores just configuration information.
         * @param file Output file
         */
        virtual bool storeConfig(File* /*file*/) /*const*/ {return false;}

        /**
         * Stores just user information.
         * @param file Output file
         * @return true if succeeded
         */
        virtual bool storeUser(File* /*file*/) /*const*/ {return false;}

        /**
         * Create the objects defined in a particular configuration
         * file
         * @param file Input file
         * @return true if succeeded
         */
        virtual bool load(File* /*file*/) throw (JmriException) {return false;}

        virtual bool load(QFile* /*file*/)  throw (JmriException){return false;}

        /**
         * Create the objects defined in a particular configuration
         * file
         * @param file Input URL
         * @return true if succeeded
         */
        virtual bool load(QUrl /*file*/) throw (JmriException) {return false;}

        /**
         * Create the objects defined in a particular configuration
         * file
         * @param file Input file
         * @param registerDeferred true to register actions for deferred load
         * @return true if succeeded
         * @throws JmriException
         * @since 2.11.2
         */
         virtual bool load(File* /*file*/, bool /*registerDeferred*/)  throw (JmriException) { return false;}

        /**
         * Create the objects defined in a particular configuration
         * file
         * @param file Input URL
         * @param registerDeferred true to register actions for deferred load
         * @return true if succeeded
         * @throws JmriException
         * @since 2.11.2
         */
        virtual bool load(QUrl /*file*/, bool /*registerDeferred*/) throw (JmriException) { return false;}

        /**
         * Create the objects defined in a particular configuration
         * file that have been deferred until after basic GUI construction
         * completed
         * @param file Input file
         * @return true if succeeded
         * @throws JmriException
         * @see jmri.configurexml.XmlAdapter#loadDeferred()
         * @since 2.11.2
         */
        virtual bool loadDeferred(File* /*file*/)  throw (JmriException) { return false;}

        /**
         * Create the objects defined in a particular configuration
         * file that have been deferred until after basic GUI construction
         * completed
         * @param file Input URL
         * @return true if succeeded
         * @throws JmriException
         * @see jmri.configurexml.XmlAdapter#loadDeferred()
         * @since 2.11.2
         */
        virtual bool loadDeferred(QUrl /*file*/) throw (JmriException) { return false;}

        /**
         * Provide a method-specific way of locating a file to be
         * loaded from a name.
         * @param filename Local filename, perhaps without path information
         * @return Corresponding {@link java.net.URL}
         */
        virtual QUrl find(QString /*filename*/) {return QUrl();}

        /**
         * Make a backup file.
         * @param file to be backed up
         * @return true if successful
         */
        virtual bool makeBackup(File* /*file*/) const { return false;}

signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(ConfigureManager, "ConfigureManager")
Q_DECLARE_METATYPE(ConfigureManager)
#endif // CONFIGUREMANAGER_H
