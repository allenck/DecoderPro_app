#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "namedbean.h"
#include <QList>
#include "javaqt_global.h"
#include "vetoablechangelistener.h"
#include <QSet>

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
 enum NameValidity {
         /**
          * Indicates the name is valid as is,
          * and can also be a valid prefix for longer names
          */
         VALID,
          /**
           * Indicates name is not valid as-is, nor
           * can it be made valid by adding more characters;
           * just a bad start.
           */
         INVALID,
         /**
          * Indicates that adding additional characters might (or might not)
          * turn this into a valid name; it is not a valid name now.
          */
         VALID_AS_PREFIX_ONLY
     };
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
    /**
      * This provides an
      * {@linkplain java.util.Collections#unmodifiableList unmodifiable} List
      * of system names.
      * <p>
      * Note: this is ordered by the original add order, used for ConfigureXML
      * <p>
      * Note: Access via {@link getNamedBeanSet} is faster.
      * <p>
      * Note: This is a live list, it will be updated as beans are added and removed.
      * @return Unmodifiable access to a list of system names
      * @deprecated 4.11.5 - use direct access via
      *                  {@link getNamedBeanSet}
      */
//     @Deprecated // 4.11.5
//     @CheckReturnValue
//     @Nonnull
     QT_DEPRECATED /*public*/ /*default*/ virtual QStringList getSystemNameAddedOrderList() { return getSystemNameList(); }

     QT_DEPRECATED virtual /*public*/ QList<NamedBean*>* getNamedBeanList() {return NULL;}
     /**
      * This provides an
      * {@linkplain java.util.Collections#unmodifiableSet unmodifiable}
      * SortedSet of NamedBeans in system-name order.
      * <p>
      * Note: This is the fastest of the accessors, and is the only long-term form.
      * <p>
      * Note: This is a live set; the contents are kept up to date
      * @return Unmodifiable access to a SortedSet of NamedBeans
      */
     //@CheckReturnValue
     //@Nonnull
     /*public*/ /*SortedSet<E>*/virtual QSet<NamedBean*> getNamedBeanSet() {return QSet<NamedBean*>();}

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
         * Add a VetoableChangeListener to the listener list.
         *
         * @param l the listener
         */
        /*public*/ virtual void addVetoableChangeListener(/*@CheckForNull*/ VetoableChangeListener* l) {}

        /**
         * Remove a VetoableChangeListener to the listener list.
         *
         * @param l the listener
         */
        /*public*/ virtual void removeVetoableChangeListener(/*@CheckForNull*/ VetoableChangeListener* l) {}
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
        /**
         * Provides length of the system prefix of the given system name.
         * <p>
         * This is a common operation across JMRI, as the system prefix can be
         * parsed out without knowledge of the type of NamedBean involved.
         *
         * @param inputName System name to provide the prefix
         * @throws NamedBean.BadSystemNameException If the inputName can't be
         *                                          converted to normalized form
         * @return The length of the system-prefix part of the system name in standard normalized form
         */
        //@CheckReturnValue
        static /*public*/
        int getSystemPrefixLength(/*@Nonnull*/ QString inputName) throw (NamedBean::BadSystemNameException);

        /**
             * Indicate whether a system-prefix is one of the legacy non-parsable ones
             * that are being removed during the JMRI 4.11 cycle.
             * @deprecated to make sure we remember to remove this post-4.11
             * @since 4.11.2
             * @return true if a legacy prefix, hence non-parsable
             */
            //@Deprecated
        QT_DEPRECATED
            //@SuppressWarnings("fallthrough")
            //@SuppressFBWarnings(value = "SF_SWITCH_FALLTHROUGH", justification="intentional to make code more readable")
            //@CheckReturnValue
            /*public*/ static bool isLegacySystemPrefix(/*@Nonnull*/ QString prefix);

            //@Deprecated
        /**
         * If the argument starts with one of the legacy prefixes, detect that and
         * indicate its length.
         * <p>
         * This is a slightly-expensive operation, and should be used sparingly
         *
         * @deprecated to make sure we remember to remove this post-4.11
         * @since 4.11.2
         * @return length of a legacy prefix, if present, otherwise -1
         */
        //@Deprecated
        QT_DEPRECATED
        //@CheckReturnValue
        /*public*/ static int startsWithLegacySystemPrefix(/*@Nonnull*/ QString prefix);
        virtual /*public*/ QString getEntryToolTip() {return "";}

signals:
    void vetoablePropertyChange(PropertyChangeEvent*);
public slots:

private:
        QT_DEPRECATED
//            static /*final*/ java.util.TreeSet<String> legacyPrefixes
//                = new java.util.TreeSet<>(java.util.Arrays.asList(
//                    new String[]{
//                        "DX", "DCCPP", "DP", "MR", "MC", "PI", "TM"
//                    }));
        static QStringList legacyPrefixes;// = QStringList() << "DX" << "DCCPP" << "DP" << "MR" << "MC" << "PI" << "TM";

    
};
Q_DECLARE_INTERFACE(Manager, "ManagerInterface")

#endif // MANAGER_H
