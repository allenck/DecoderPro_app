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
#include "exceptions.h"
#include <QVector>
#include "namedbean.h"
#include "vetoablechangeprovider.h"
#include "silenceablepropertychangeprovider.h"

class NamedBeanPropertyDescriptor;
class Logger;
class SystemConnectionMemo;
class QStringList;
class PropertyChangeListener;
class JAVAQTSHARED_EXPORT   Manager : public SilenceablePropertyChangeProvider, public VetoableChangeProvider
{
 //Q_OBJECT
  Q_INTERFACES(SilenceablePropertyChangeProvider VetoableChangeProvider)
public:
    //explicit Manager(QObject *parent = 0) : QObject(parent) {}
    //Manager(SystemConnectionMemo* /*memo*/, QObject *parent = 0) : QObject(parent) {}
    //virtual ~Manager() {}
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
 //Q_ENUM(NameValidity)

 /**
  * Get the system connection for this manager.
  *
  * @return the system connection for this manager
  */
 //@CheckReturnValue
 //@Nonnull
 /*public*/ virtual SystemConnectionMemo* getMemo() const =0;

/**
 * Provides access to the system prefix string.
 * This was previously called the "System letter"
 */
 virtual QString getSystemPrefix()  const /*= 0*/ {return "L";}

/**
 * @return The type letter for a specific implementation
 */
 virtual char typeLetter() const {return '?';}

 /**
 * Get the class of NamedBean supported by this Manager. This should be the
 * generic class used in the Manager's class declaration.
 *
 * @return the class supported by this Manager.
 */
/*public*/ /*abstract*/ virtual QString getNamedBeanClass()const =0;
 /**
  * Get the prefix and type for the system name of the NamedBeans handled by
  * this manager.
  *
  * @return the prefix generated by concatenating the result of
  * {@link #getSystemPrefix() } and {@link #typeLetter() }
  */
 /*public*/ /*default*/ QString getSystemNamePrefix() const{
     return getSystemPrefix() + typeLetter();
 }
 /*public*/ /*default*/ QString getSubSystemNamePrefix() const{
     return getSystemNamePrefix();
 }
 /**
  * @return A system name from a user input, typically a number.
  */
 /*public*/ /*default*/ virtual QString makeSystemName(/*@Nonnull*/ QString name) const;

/**
 * Create a SystemName by prepending the system name prefix to the name if
 * not already present.
 * <p>
 * The {@code logErrors} parameter is present to allow user interface input
 * validation to use this method without logging system name validation
 * errors as the user types.
 * <p>
 * <strong>Note:</strong> implementations <em>must</em> call
 * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)} to ensure
 * the returned name is valid.
 *
 * @param name      the item to make the system name for
 * @param logErrors true to log errors; false to not log errors
 * @return a valid system name
 * @throws BadSystemNameException if a valid name can't be created
 */
//@Nonnull
/*public*/ /*default*/ virtual QString makeSystemName(/*@Nonnull*/ QString name, bool logErrors) const;

/**
 * Create a SystemName by prepending the system name prefix to the name if
 * not already present.
 * <p>
 * The {@code logErrors} parameter is present to allow user interface input
 * validation to use this method without logging system name validation
 * errors as the user types.
 * <p>
 * <strong>Note:</strong> implementations <em>must</em> call
 * {@link #validateSystemNameFormat(java.lang.String, java.util.Locale)} to ensure
 * the returned name is valid.
 *
 * @param name      the item to make the system name for
 * @param logErrors true to log errors; false to not log errors
 * @param locale    the locale for a localized exception; this is needed for
 *                      the JMRI web server, which supports multiple locales
 * @return a valid system name
 * @throws BadSystemNameException if a valid name can't be created
 */
//@Nonnull
/*public*/ /*default*/ virtual QString makeSystemName(/*@Nonnull*/ QString name, bool /*logErrors*/, QLocale locale) const;


 /**
  * Test if parameter is a properly formatted system name.
  *
  * @since 4.9.5, although similar methods existed previously in lower-level
  * classes
  * @param systemName the system name
  * @return enum indicating current validity, which might be just as a prefix
  */
 //@CheckReturnValue
 virtual /*public*/ NameValidity validSystemNameFormat(/*@Nonnull*/ QString /*systemName*/) const;

 /**
  * Free resources when no longer used. Specifically, remove all references
  * to and from this object, so it can be garbage-collected.
  */
 virtual void dispose()  {}

 /**
  * Get the count of managed objects.
  *
  * @return the number of managed objects
  */
 //@CheckReturnValue
 virtual /*public*/ int getObjectCount() {return 0;}

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
     virtual NamedBean* getBeanBySystemName(QString /*systemName*/) const {return NULL;}

     /**
      * Locate an instance based on a user name.  Returns null if no
      * instance already exists.
      * @param userName System Name of the required NamedBean
      * @return requested NamedBean object or null if none exists
      */
     QT_DEPRECATED virtual NamedBean* getBeanByUserName(QString /*userName*/)  const {return NULL;}

     /**
      * Locate an existing instance based on a system name.
      *
      * @param systemName System Name of the required NamedBean
      * @return requested NamedBean object or null if none exists
      * @throws IllegalArgumentException if provided name is invalid
      */
     //@CheckReturnValue
     //@CheckForNull
     virtual/*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString /*systemName*/)  const {return NULL;}

     /**
      * Locate an existing instance based on a user name.
      *
      * @param userName System Name of the required NamedBean
      * @return requested NamedBean object or null if none exists
      */
     //@CheckReturnValue
     //@CheckForNull
     virtual /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString /*userName*/) const =0;

     /**
      * Locate an instance based on a name.  Returns null if no
      * instance already exists.
      * @param name System Name of the required NamedBean
      * @return requested NamedBean object or null if none exists
      */
     virtual  NamedBean* getNamedBean(QString /*name*/) const {return NULL;}


     /**
      * Method for a UI to delete a bean.
      * <p>
      * The UI should first request a "CanDelete", this will return a list of
      * locations (and descriptions) where the bean is in use via throwing a
      * VetoException, then if that comes back clear, or the user agrees with the
      * actions, then a "DoDelete" can be called which inform the listeners to
      * delete the bean, then it will be deregistered and disposed of.
      * <p>
      * If a property name of "DoNotDelete" is thrown back in the VetoException
      * then the delete process should be aborted.
      *
      * @param n        The NamedBean to be deleted
      * @param property The programmatic name of the request. "CanDelete" will
      *                 enquire with all listeners if the item can be deleted.
      *                 "DoDelete" tells the listener to delete the item.
      * @throws java.beans.PropertyVetoException - If the recipients wishes the
      *                                          delete to be aborted (see
      *                                          above).
      */
      virtual /*public*/ void deleteBean(/*@Nonnull*/ NamedBean* /*n*/, /*@Nonnull*/ QString /*property*/) /*throw (PropertyVetoException)*/ {}

      virtual /*default*/ /*public*/ QList<NamedBeanPropertyDescriptor*> getKnownBeanProperties();


     /**
      * Remember a NamedBean Object created outside the manager.
      * <P>
      * The non-system-specific SignalHeadManagers
      * use this method extensively.
      */
     virtual void Register(NamedBean* /*n*/) const =0;

     /**
      * Forget a NamedBean Object created outside the manager.
      * <P>
      * The non-system-specific RouteManager
      * uses this method.
      */
     virtual void deregister(NamedBean* /*n*/) const =0;

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
     static const   int ANALOGIOS = IDTAGS + 10;
     static const   int METERS = ANALOGIOS + 10;
     static const   int STRINGIOS = METERS + 10;
     static const   int LOGIXS = STRINGIOS + 10;
     static const   int CONDITIONALS = LOGIXS + 10;
     static const   int AUDIO = CONDITIONALS + 10;
     static const   int TIMEBASE = AUDIO + 10;
     static const   int PANELFILES = TIMEBASE + 10;
     static const   int ENTRYEXIT = PANELFILES + 10;
     static const   int LOGIXNGS = ENTRYEXIT + 10;                          // LogixNG
     static const   int LOGIXNG_CONDITIONALNGS = LOGIXNGS + 10;             // LogixNG ConditionalNG
     static const   int LOGIXNG_TABLES = LOGIXNG_CONDITIONALNGS + 10;       // LogixNG Tables (not bean tables)
     static const   int LOGIXNG_DIGITAL_EXPRESSIONS = LOGIXNG_TABLES + 10;          // LogixNG Expression
     static const   int LOGIXNG_DIGITAL_ACTIONS = LOGIXNG_DIGITAL_EXPRESSIONS + 10; // LogixNG Action
     static const   int LOGIXNG_DIGITAL_BOOLEAN_ACTIONS = LOGIXNG_DIGITAL_ACTIONS + 10;   // LogixNG Digital Boolean Action
     static const   int LOGIXNG_ANALOG_EXPRESSIONS = LOGIXNG_DIGITAL_BOOLEAN_ACTIONS + 10;  // LogixNG AnalogExpression
     static const   int LOGIXNG_ANALOG_ACTIONS = LOGIXNG_ANALOG_EXPRESSIONS + 10;   // LogixNG AnalogAction
     static const   int LOGIXNG_STRING_EXPRESSIONS = LOGIXNG_ANALOG_ACTIONS + 10;   // LogixNG StringExpression
     static const   int LOGIXNG_STRING_ACTIONS = LOGIXNG_STRING_EXPRESSIONS + 10;   // LogixNG StringAction
     static const   int METERFRAMES = LOGIXNG_STRING_ACTIONS + 10;
     static const   int CTCDATA = METERFRAMES + 10;

     /**
      * Determine the order that types should be written when storing panel
      * files. Uses one of the constants defined in this class.
      * <p>
      * Yes, that's an overly-centralized methodology, but it works for now.
      *
      * @return write order for this Manager; larger is later.
      */
     /*@CheckReturnValuevirtual*/virtual int getXMLOrder() const =0;

     /**
      * For instances in the code where we are dealing with just a bean and a
      * message needs to be passed to the user or in a log.
      *
      * @return a string of the bean type that the manager handles, eg Turnout,
      *         Sensor etc
      */
     //@CheckReturnValue
     //@Nonnull
     /*public*/ virtual QString getBeanTypeHandled() const {return getBeanTypeHandled(false);}
     /*public*/ virtual /*default*/ QString getBeanTypeHandled(bool /*plural*/) const {return "??";}
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
     QString virtual normalizeSystemName(/*@Nonnull */QString /*inputName*/)const {return "";} //throw NamedBean.BadSystemNameException;
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
     int getSystemPrefixLength(/*@Nonnull*/ QString inputName) /*throw (NamedBean::BadSystemNameException)*/;
     /*public*/ static QString getSystemPrefix(/*@Nonnull*/ QString inputName);

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
     /*public*/ /*default*/ QString validateSystemNameFormat(/*@Nonnull*/ QString name) const /*throw (NamedBean::BadSystemNameException)*/;
     /*public*/ /*default*/ QString validateSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) const /*throw (NamedBean::BadSystemNameException)*/;
     /*public*/ /*default*/ QString validateSystemNamePrefix(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) const /*throw (NamedBean::BadSystemNameException)*/;
     /*public*/ /*default*/ QString validateTrimmedSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale);
     /*public*/ /*default*/ QString validateUppercaseTrimmedSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale);
     /*public*/ /*default*/ QString validateIntegerSystemNameFormat(/*@Nonnull*/ QString name, int min, int max, /*@Nonnull*/ QLocale locale);
     /*public*/ /*default*/ QString validateNmraAccessorySystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale);
     /*public*/ /*default*/ bool isValidSystemNameFormat(/*@Nonnull*/ QString systemName);

     /**
       * Defines an event that encapsulates changes to a list.
       * <p>
       * Intended to be equivalent to {@link javax.swing.event.ListDataEvent}
       * without introducing a Swing dependency into core JMRI.
       *
       * @param <E> the type to support in the event
       * @since JMRI 4.11.4
       */
      //@javax.annotation.concurrent.Immutable
      /*public*/ /*final*/ class ManagerDataEvent  /*<E extends NamedBean>*/: public EventObject
      {
       public:
          /**
           * Equal to {@link javax.swing.event.ListDataEvent#CONTENTS_CHANGED}
           */
          /*final*/ static /*public*/ int CONTENTS_CHANGED;// = 0;
          /**
           * Equal to {@link javax.swing.event.ListDataEvent#INTERVAL_ADDED}
           */
          /*final*/ static /*public*/ int INTERVAL_ADDED;// = 1;
          /**
           * Equal to {@link javax.swing.event.ListDataEvent#INTERVAL_REMOVED}
           */
          /*final*/ static /*public*/ int INTERVAL_REMOVED;// = 2;
        private:
          /*final*/ /*private*/ int type;
          /*final*/ /*private*/ int index0;
          /*final*/ /*private*/ int index1;
          /*final*/ /*private*/ /*E*/NamedBean* changedBean; // used when just one bean is added or removed as an efficiency measure
          /*final*/ /*private*/ Manager/*<E>*/* source;
             public:
          /**
           * Creates a <code>ListDataEvent</code> object.
           *
           * @param source      the source of the event (<code>null</code> not
           *                    permitted).
           * @param type        the type of the event (should be one of
           *                    {@link #CONTENTS_CHANGED}, {@link #INTERVAL_ADDED}
           *                    or {@link #INTERVAL_REMOVED}, although this is not
           *                    enforced).
           * @param index0      the index for one end of the modified range of
           *                    list elements.
           * @param index1      the index for the other end of the modified range
           *                    of list elements.
           * @param changedBean used when just one bean is added or removed,
           *                    otherwise null
           */
          /*public*/ ManagerDataEvent(/*@Nonnull*/ Manager/*<E>*/* source, int type, int index0, int index1, /*E*/NamedBean* changedBean);

          /**
           * Returns the source of the event in a type-safe manner.
           *
           * @return the event source
           */
          //@Override
          /*public*/ Manager/*<E>*/* getSource();

          /**
           * Returns the index of the first item in the range of modified list
           * items.
           *
           * @return The index of the first item in the range of modified list
           *         items.
           */
          /*public*/ int getIndex0();

          /**
           * Returns the index of the last item in the range of modified list
           * items.
           *
           * @return The index of the last item in the range of modified list
           *         items.
           */
          /*public*/ int getIndex1();

          /**
           * Returns the changed bean or null
           *
           * @return null if more than one bean was changed
           */
          /*public*/ /*E*/NamedBean* getChangedBean();

          /**
           * Returns a code representing the type of this event, which is usually
           * one of {@link #CONTENTS_CHANGED}, {@link #INTERVAL_ADDED} or
           * {@link #INTERVAL_REMOVED}.
           *
           * @return The event type.
           */
          /*public*/ int getType() ;

          /**
           * Returns a string representing the state of this event.
           *
           * @return A string.
           */
          //@Override
          /*public*/ QString toString();
         }; // end class definition ManagerDataEvent
     virtual/*public*/ void addDataListener(/*ManagerDataListener<E>*/QObject* e);

     /**
      * Unregister a previously-added {@link ManagerDataListener}.
      *
      * @param e the data listener to remove
      */
     virtual /*public*/ void removeDataListener(/*ManagerDataListener<E>*/QObject* e);

     /**
      * Temporarily suppress DataListener notifications.
      * <p>
      * This avoids O(N^2) behavior when doing bulk updates, i.e. when loading
      * lots of Beans. Note that this is (1) optional, in the sense that the
      * manager is not required to mute and (2) if present, its' temporary, in
      * the sense that the manager must do a cumulative notification when done.
      *
      * @param muted true if notifications should be suppressed; false otherwise
      */
     /*public*/ /*default*/ void setDataListenerMute(bool muted);
     virtual /*public*/QString toString() {return "Manager";}
     bool operator==(const Manager& other)
     {
      return this->getSystemNamePrefix() == other.getSystemPrefix();
     }

     virtual QObject* self() =0;


private:
        QT_DEPRECATED
//            static /*final*/ java.util.TreeSet<String> legacyPrefixes
//                = new java.util.TreeSet<>(java.util.Arrays.asList(
//                    new String[]{
//                        "DX", "DCCPP", "DP", "MR", "MC", "PI", "TM"
//                    }));
        static QStringList legacyPrefixes;// = QStringList() << "DX" << "DCCPP" << "DP" << "MR" << "MC" << "PI" << "TM";
     //SystemConnectionMemo* memo = nullptr;
    
};

Q_DECLARE_INTERFACE(Manager, "Manager")
/**
 * Intended to be equivalent to {@link javax.swing.event.ListDataListener}
 * without introducing a Swing dependency into core JMRI.
 *
 * @param <E> the type to support listening for
 * @since JMRI 4.11.4
 */
/*interface*/ class ManagerDataListener/*<E extends NamedBean>*/ : public QObject{
Q_OBJECT
public slots:
    /**
     * Sent when the contents of the list has changed in a way that's too
     * complex to characterize with the previous methods.
     *
     * @param e encapsulates event information
     */
    virtual void contentsChanged(Manager::ManagerDataEvent/*<E>*/* /*e*/) {}

    /**
     * Sent after the indices in the index0,index1 interval have been
     * inserted in the data model.
     *
     * @param e encapsulates the event information
     */
     virtual void intervalAdded(Manager::ManagerDataEvent/*<E>*/* /*e*/) {}

    /**
     * Sent after the indices in the index0,index1 interval have been
     * removed from the data model.
     *
     * @param e encapsulates the event information
     */
     virtual void intervalRemoved(Manager::ManagerDataEvent/*<E>*/* /*e*/) {}

    // Providing Manager stuff

};
#endif // MANAGER_H
