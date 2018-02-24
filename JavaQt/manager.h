#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "namedbean.h"
#include <QList>
#include "javaqt_global.h"

class QString;
class QStringList;
class NamedBean;
class PropertyChangeListener;
class JAVAQTSHARED_EXPORT Manager : public QObject
{
 Q_OBJECT
public:
    explicit Manager(QObject *parent = 0) : QObject(parent) {}
    /**
     * Basic interface for access to named, managed objects.
     * <P>
     * {@link NamedBean} objects represent various real elements, and
     * have a "system name" and perhaps "user name".  A specific Manager
     * object provides access to them by name, and serves as a factory for
     * new objects.
     * <P>
     * Right now, this interface just contains the members needed
     * by {@link InstanceManager} to handle
     * managers for more than one system.
     * <P>
     * Although they are not defined here because their return type differs, any
     * specific Manager subclass
     * provides "get" methods to locate specific objects, and a "new" method
     * to create a new one via the Factory pattern.
     * The "get" methods will
     * return an existing object or null, and will never create a new object.
     * The "new" method will log a warning if an object already exists with
     * that system name.
     * <P>
     * add/remove PropertyChangeListener methods are provided. At a minimum,
     * subclasses must notify of changes to the list of available NamedBeans;
     * they may have other properties that will also notify.
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
     * @author      Bob Jacobsen Copyright (C) 2003
     * @version	$Revision: 20288 $
     */
//    public interface Manager {

//        /**
//         * @return The system-specific prefix letter for a specific implementation
//         * @deprecated 2.9.5 Use getSystemPrefix
//         */
//        @Deprecated
//        virtual char systemLetter();

        /**
         * Provides access to the system prefix string.
         * This was previously called the "System letter"
         */
 virtual QString getSystemPrefix()  /*= 0*/ {return "L";}

        /**
         * @return The type letter for a specific implementation
         */
 virtual char typeLetter()  {return ' ';}

        /**
         * @return A system name from a user input, typically a number.
         */
    virtual QString makeSystemName(QString /*s*/)  {return "";}

        /**
         * Free resources when no longer used. Specifically, remove all references
         * to and from this object, so it can be garbage-collected.
         */
    virtual void dispose()  {}

    virtual QStringList getSystemNameArray()  {return QStringList();}
    virtual QStringList getSystemNameList()  {return QStringList();}
    virtual /*public*/ QList<NamedBean*>* getNamedBeanList() {return NULL;}
        /**
         * Locate an instance based on a system name.  Returns null if no
         * instance already exists.
         * @param systemName System Name of the required NamedBean
         * @return requested NamedBean object or null if none exists
         */
        virtual NamedBean* getBeanBySystemName(QString /*systemName*/) {return NULL;}

        /**
         * Locate an instance based on a user name.  Returns null if no
         * instance already exists.
         * @param userName System Name of the required NamedBean
         * @return requested NamedBean object or null if none exists
         */
        virtual NamedBean* getBeanByUserName(QString /*userName*/)  {return NULL;}

        /**
         * Locate an instance based on a name.  Returns null if no
         * instance already exists.
         * @param name System Name of the required NamedBean
         * @return requested NamedBean object or null if none exists
         */
        virtual  NamedBean* getNamedBean(QString /*name*/) {return NULL;}

        /**
         * At a minimum,
         * subclasses must notify of changes to the list of available NamedBeans;
         * they may have other properties that will also notify.
         */
        virtual void addPropertyChangeListener(PropertyChangeListener* /*l*/) {}
        /**
         * At a minimum,
         * subclasses must notify of changes to the list of available NamedBeans;
         * they may have other properties that will also notify.
         */
        virtual void removePropertyChangeListener(PropertyChangeListener* /*l*/)  {}

        /**
         * Remember a NamedBean Object created outside the manager.
         * <P>
         * The non-system-specific SignalHeadManagers
         * use this method extensively.
         */
        virtual void Register(NamedBean* /*n*/)  {}

        /**
         * Forget a NamedBean Object created outside the manager.
         * <P>
         * The non-system-specific RouteManager
         * uses this method.
         */
        virtual void deregister(NamedBean* /*n*/)  {}

        /**
        * The order in which things get saved to the xml file.
        */
        static const   int SENSORS = 10;
        static const   int TURNOUTS = SENSORS + 10;
        static const   int LIGHTS = TURNOUTS + 10;
        static const   int REPORTERS = LIGHTS + 10;
        static const   int MEMORIES = REPORTERS + 10;
        static const   int SENSORGROUPS = MEMORIES + 10;
        static const   int SIGNALHEADS = SENSORGROUPS + 10;
        static const   int SIGNALMASTS = SIGNALHEADS + 10;
        static const   int SIGNALGROUPS = SIGNALMASTS + 10;
        static const   int BLOCKS = SIGNALGROUPS +10;
        static const   int OBLOCKS = BLOCKS +10;
        static const   int LAYOUTBLOCKS = OBLOCKS +10;
        static const   int SECTIONS = LAYOUTBLOCKS +10;
        static const   int TRANSITS = SECTIONS +10;
        static const   int BLOCKBOSS = TRANSITS +10;
        static const   int ROUTES = BLOCKBOSS + 10;
        static const   int WARRANTS = ROUTES + 10;
        static const   int SIGNALMASTLOGICS = WARRANTS + 10;
        static const   int IDTAGS = SIGNALMASTLOGICS + 10;
        static const   int LOGIXS = IDTAGS + 10;
        static const   int CONDITIONALS = LOGIXS + 10;
        static const   int AUDIO = LOGIXS + 10;
        static const   int TIMEBASE = AUDIO + 10;
        static const   int PANELFILES = TIMEBASE + 10;
        static const   int ENTRYEXIT = PANELFILES + 10;

        virtual int getXMLOrder() {return 0;}
        /**
         * For instances in the code where we are dealing with just a bean and a
         * message needs to be passed to the user or in a log.
         *
         * @return a string of the bean type that the manager handles, eg Turnout,
         *         Sensor etc
         */
        //@CheckReturnValue
        //@Nonnull
        /*public*/ virtual QString getBeanTypeHandled() {return "";}

        /**
         * Enforces, and as a user convenience converts to, the standard form for a
         * system name for the NamedBeans handled by this manager.
         *
         * @param inputName System name to be normalized
         * @throws NamedBean.BadSystemNameException If the inputName can't be
         *                                          converted to normalized form
         * @return A system name in standard normalized form
         */
        //@CheckReturnValue
        /*public*/ //@Nonnull
        QString virtual normalizeSystemName(/*@Nonnull */QString /*inputName*/) {return "";} //throw NamedBean.BadSystemNameException;

signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(Manager, "ManagerInterface")

#endif // MANAGER_H
