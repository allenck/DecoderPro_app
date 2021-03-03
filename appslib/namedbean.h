#ifndef NAMEDBEAN_H
#define NAMEDBEAN_H

#include <QObject>
#include "propertychangelistener.h"
#include "javaqt_global.h"
#include "exceptions.h"
#include "namedbean.h"
#include "namedbeanusagereport.h"

class JAVAQTSHARED_EXPORT NamedBean : public  QObject
{
 Q_OBJECT
public:
    explicit NamedBean(QObject *parent = 0);
    NamedBean(QString name, QObject *parent = 0);
    NamedBean(const NamedBean&);
    virtual ~NamedBean() {}
    /**
     * Parent class for a set of classes that describe if a user name or system
     * name is a bad name.
     */
    /*public*/ class BadNameException : public IllegalArgumentException {

        /*private*/ /*final*/ QString localizedMessage;
        protected:
        /**
         * Create an exception with no message to the user or for logging.
         */
        /*protected*/ BadNameException() {
            //super();
            localizedMessage = IllegalArgumentException::getMessage();
        }

        /**
         * Create a localized exception, suitable for display to the user.This
         * takes the non-localized message followed by the localized message.
         * <p>
         * Use {@link #getLocalizedMessage()} to display the message to the
         * user, and use {@link #getMessage()} to record the message in logs.
         *
         * @param logging the English message for logging
         * @param display the localized message for display
         */
        /*protected*/ BadNameException(QString logging, QString display) : IllegalArgumentException(logging)
        {
            //super(logging);
            localizedMessage = display;
        }
        public:
        //@Override
        /*public*/ QString getLocalizedMessage() {
            return localizedMessage;
        }
    };

    /*public*/ class BadUserNameException : public BadNameException
    {
     QLocale locale;

        public:
        /**
         * Create an exception with no message to the user or for logging. Use
         * only when calling methods likely have alternate mechanism for
         * allowing user to understand why exception was thrown.
         */
        /*public*/ BadUserNameException() {
            //super();
        }

        /**
         * Create a localized exception, suitable for display to the user. This
         * takes the same arguments as
         * {@link jmri.Bundle#getMessage(java.util.Locale, java.lang.String, java.lang.Object...)}
         * as it uses that method to create both the localized and loggable
         * messages.
         * <p>
         * Use {@link #getLocalizedMessage()} to display the message to the
         * user, and use {@link #getMessage()} to record the message in logs.
         * <p>
         * <strong>Note</strong> the message must be accessible by
         * {@link jmri.Bundle}.
         *
         * @param locale  the locale to be used
         * @param message bundle key to be translated
         * @param subs    One or more objects to be inserted into the message
         */
        /*public*/ BadUserNameException(QLocale locale, QString message/*, Object... subs*/)
          : BadNameException(message,message)
        {
//            super(Bundle.getMessage(Locale.ENGLISH, message, subs),
//                    Bundle.getMessage(locale, message, subs));
          this->locale = locale;
        }

        /**
         * Create a localized exception, suitable for display to the user. This
         * takes the non-localized message followed by the localized message.
         * <p>
         * Use {@link #getLocalizedMessage()} to display the message to the
         * user, and use {@link #getMessage()} to record the message in logs.
         *
         * @param logging the English message for logging
         * @param display the localized message for display
         */
        /*public*/ BadUserNameException(QString logging, QString display) : BadNameException(logging, display){
            //super(logging, display);
        }
    };
    class BadSystemNameException : public BadNameException
    {
     QString name;
     QString prefix;
     QLocale locale;
    public:
     BadSystemNameException() {}
     BadSystemNameException(QLocale locale, QString msg, QString name, QString prefix = "") : BadNameException(msg, msg)
     {
      this->locale = locale;
      this->name = name;
      this->prefix = prefix;
     }
    };

    class DuplicateSystemNameException : public IllegalArgumentException
    {
     QString name;
     QLocale locale;
     QString prefix;
    public:
     DuplicateSystemNameException(QString msg) {this->msg=msg;}
     DuplicateSystemNameException(QLocale locale, QString msg, QString name, QString prefix = "") : IllegalArgumentException(msg)
     {
      //this->msg = msg;
      this->locale = locale;
      this->name = name;
      this->prefix = prefix;
     }
    };

    /**
     * Provides common services for classes representing objects
     * on the layout, and allows a common form of access by their Managers.
     * <P>
     * Each object has a two names.  The "user" name is entirely free form, and
     * can be used for any purpose.  The "system" name is provided by the system-specific
     * implementations, and provides a unique mapping to the layout control system
     * (e.g. LocoNet, NCE, etc) and address within that system.
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
     * @author	Bob Jacobsen  Copyright (C) 2001, 2002, 2003, 2004
     * @version	$Revision: 17977 $
     * @see         jmri.Manager
     */
    //public interface NamedBean {

        /**
         * Constant representing an "unknown" state, indicating that the
         * object's state is not necessarily that of the actual layout hardware.
         * This is the initial state of a newly created object before
         * communication with the layout.
         */
//#ifdef WIN32
//        const static int UNKNOWN      = 0x01;
//#else
//        const static int UNKNOWN;
//#endif

        /**
         * Constant representing an "inconsistent" state, indicating that
         * some inconsistency has been detected in the hardware readback.
         */
//#ifdef WIN32
//        const static int INCONSISTENT = 0x08;
//#else
//        const static int INCONSISTENT;
//#endif
    enum STATES
    {
     UNKNOWN = 1,
     INCONSISTENT= 0x08
    };
    Q_ENUM(STATES)
    /*public*/ static /*final*/ QString DISPLAY_NAME_FORMAT;// = "%1 (%2)";

    /**
     * Format used for {@link #getDisplayName(DisplayOptions)} when displaying
     * the user name and system name with quoation marks around the user name.
     */
    /*public*/ static /*final*/ QString QUOTED_NAME_FORMAT;// = "\"%1\" (%2)";
    /*public*/ static /*final*/ QString PROPERTY_STATE;// = "state";

    /**
     * Display options for {@link #getDisplayName(DisplayOptions)}. The quoted
     * forms are intended to be used in sentences and messages, while the
     * unquoted forms are intended for use in user interface elements like lists
     * and combo boxes.
     */
    /*public*/ enum DisplayOptions {
        /**
         * Display the user name; if the user name is null or empty, display the
         * system name.
         */
        DISPLAYNAME,
        /**
         * Display the user name in quotes; if the user name is null or empty,
         * display the system name in quotes.
         */
        QUOTED_DISPLAYNAME,
        /**
         * Display the user name; if the user name is null or empty, display the
         * system name.
         */
        USERNAME,
        /**
         * Display the user name in quotes; if the user name is null or empty,
         * display the system name in quotes.
         */
        QUOTED_USERNAME,
        /**
         * Display the system name. This should be used only when the context
         * would cause displaying the user name to be more confusing than not or
         * in text input fields for editing the system name.
         */
        SYSTEMNAME,
        /**
         * Display the system name in quotes. This should be used only when the
         * context would cause displaying the user name to be more confusing
         * than not or in text input fields for editing the system name.
         */
        QUOTED_SYSTEMNAME,
        /**
         * Display the user name followed by the system name in parenthesis. If
         * the user name is null or empty, display the system name without
         * parenthesis.
         */
        USERNAME_SYSTEMNAME,
        /**
         * Display the user name in quotes followed by the system name in
         * parenthesis. If the user name is null or empty, display the system
         * name in quotes.
         */
        QUOTED_USERNAME_SYSTEMNAME
    };
    Q_ENUM(DisplayOptions)
        // user identification, _bound_ parameter so manager(s) can listen
        virtual QString getUserName() const;
        virtual void setUserName(QString s);
        //virtual void setSysName(QString s);
        /**
         * Get a system-specific name.  This encodes the hardware addressing
         * information.
         */
        virtual QString getSystemName() const {return QString();}//=0;
        /*
        * return user name if it exists, otherwise return System name
        */
        virtual QString getDisplayName();
        virtual QString getDisplayName(DisplayOptions);
        virtual /*public*/ QString getFullyFormattedDisplayName() {return "";}


        /**
         * Request a call-back when a bound property changes.
         * Bound properties are the known state, commanded state, user and system names.
         * @param l - Listener
         * @param name - The name (either system or user) that the listener uses for
         *               this namedBean, this parameter is used to help determine when
         *               which listeners should be moved when the username is moved from
         *               one bean to another.
         * @param listenerRef - A textual reference for the listener, that can be
         *                      presented to the user when a delete is called
         */
        virtual void addPropertyChangeListener(PropertyChangeListener* /*l*/, QString /*name*/, const QString /*listenerRef*/);

        virtual void addPropertyChangeListener(PropertyChangeListener* /*l*/);
        virtual /*public*/ void addPropertyChangeListener(/*@Nonnull*/ QString /*propertyName*/, /*@Nonnull*/ PropertyChangeListener* /*listener*/,
                                                          QString /*name*/, QString /*listenerRef*/) {}

        virtual /*public*/ void addPropertyChangeListener(/*@CheckForNull*/ QString /*propertyName*/, /*@CheckForNull*/ PropertyChangeListener* /*listener*/) {}

        /**
         * Remove a request for a call-back when a bound property changes.
         */
        virtual void removePropertyChangeListener(PropertyChangeListener* /*l*/);

        virtual void removePropertyChangeListener(QString /*propertyName*/, PropertyChangeListener */*l*/) {}

        virtual void updateListenerRef(PropertyChangeListener* l, QString /*newName*/);
        /**
        * Get the textual reference for the specific listener
        *
        */
        virtual QString getListenerRef(PropertyChangeListener* /*l*/);

        /**
        * Returns a list of all the listerners references
        */
        virtual QList<QString>* getListenerRefs();

        /**
         * Number of current listeners. May return -1 if the
         * information is not available for some reason.
         */
        virtual int getNumPropertyChangeListeners();

        /**
         * Get a list of all the property change listeners that are registered using
         * a specific name
         *
         * @param name The name (either system or user) that the listener has
         *                 registered as referencing this namedBean
         * @return empty list if none
         */
        //@CheckReturnValue
        //@Nonnull
        virtual/*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name);

        /**
         * Deactivate this object, so that it releases as many
         * resources as possible and no longer effects others.
         *<P>
         * For example, if this object has listeners, after
         * a call to this method it should no longer notify
         * those listeners.  Any native or system-wide resources
         * it maintains should be released, including threads, files, etc.
         * <P>
         * It is an error to invoke any other methods on this
         * object once dispose() has been called.  Note, however,
         * that there is no guarantee about behavior in that case.
         * <P>
         * Afterwards, references to this object may still exist
         * elsewhere, preventing its garbage collection.  But it's formally
         * dead, and shouldn't be keeping any other objects alive.
         * Therefore, this method should null out any references to
         * other objects that this NamedBean contained.
         */
        virtual void dispose(); // remove _all_ connections!

        /**
         * Provide generic access to internal state.
         *<P>
         * This generally shouldn't be used by Java code; use
         * the class-specific form instead. (E.g. setCommandedState in Turnout)
         * This provided to make Jython
         * script access easier to read.
         * @throws JmriException general error when cant do the needed operation
         */
        virtual void setState(int /*s*/);  // throws JmriException;

        /**
         * Provide generic access to internal state.
         *<P>
         * This generally shouldn't be used by Java code; use
         * the class-specific form instead. (E.g. getCommandedState in Turnout)
         * This provided to make Jython
         * script access easier to read.
         */
        virtual int getState();

        /*public*/ virtual QString describeState(int /*state*/);

        /**
         * Get associated comment text.
         */
        virtual QString getComment();

        /**
         * Set associated comment text.
         * <p>
         * Comments can be any valid text.
         * @param comment Null means no comment associated.
         */
        virtual void setComment(QString /*comment*/);

        /**
         * Get a list of references for the specified bean.
         *
         * @param bean The bean to be checked.
         * @return a list of NamedBeanUsageReports or an empty ArrayList.
         */
        /*default*/ virtual QList<NamedBeanUsageReport*> getUsageReport(/*@CheckForNull*/ NamedBean* bean) { return (QList<NamedBeanUsageReport*>()); }

        /**
         * Attach a key/value pair to the
         * NamedBean, which can be retrieved later.
         * These are not bound properties as yet,
         * and don't throw events on modification.
         * Key must not be null.
         */
        virtual void setProperty(QString key, QVariant /*value*/);

        /**
         * Retrieve the value associated with a key.
         * If no value has been set for that key, returns null.
         */
        virtual QVariant getProperty(QString key);

    /**
     * Remove the key/value pair against the NamedBean.
     */
    /*public*/ virtual void removeProperty(/*@Nonnull*/ QString /*key*/) {}
    /**
     * Retrieve the complete current set of keys.
     */
    virtual QSet<QString> getPropertyKeys();
    /*public*/ virtual void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* /*evt*/) {}//throws java.beans.PropertyVetoException;


    virtual uint hashCode() {return 0;}

    /**
     * For instances in the code where we are dealing with just a bean and a
     * message needs to be passed to the user or in a log.
     *
     * @return a string of the bean type, eg Turnout, Sensor etc
     */
    //@CheckReturnValue
    //@Nonnull
    /*public*/ virtual QString getBeanType();

    /**
     * Enforces, and as a user convenience converts to, the standard form for a
     * user name.
     * <p>
     * This implementation just does a trim(), but later versions might e.g. do
     * more extensive things.
     *
     * @param inputName User name to be normalized
     * @throws BadUserNameException If the inputName can't be converted to
     *                              normalized form
     * @return A user name in standard normalized form or null if inputName was
     *         null
     */
    //@CheckReturnValue
    //@CheckForNull
    static /*public*/ QString normalizeUserName(/*@CheckForNull*/ QString /*inputName*/);// throw (BadUserNameException);

    /**
     * Provide a comparison between the system names of two beans.
     * This provides a implementation for e.g. {@link java.util.Comparator}.
     * @return 0 if the names are the same, -1 if the first argument orders before
     * the second argument's name, +1 if the first argument's name  orders after the second argument's name.
     * The comparison is alphanumeric on the system prefix, then alphabetic on the
     * type letter, then system-specific comparison on the two suffix parts
     * via the {@link compareSystemNameSuffix} method.
     *
     * @param n2 The second NamedBean in the comparison ("this" is the first one)
     * @return -1,0,+1 for ordering if the names are well-formed; may not provide proper ordering if the names are not well-formed.
     */
    //@CheckReturnValue
    /*public*/ virtual /*default*/ int compareTo(/*@Nonnull*/ NamedBean* n2);

    /*public*/ virtual bool equals(QObject* obj);

    /**
     * Compare the suffix of this NamedBean's name with the
     * suffix of the argument NamedBean's name for the {@link #compareTo} operation.
     * This is intended to be a system-specific comparison that understands the various formats, etc.
     *
     * @param suffix1 The suffix for the 1st bean in the comparison
     * @param suffix2 The suffix for the 2nd bean in the comparison
     * @param n2 The other (second) NamedBean in the comparison
     * @return -1,0,+1 for ordering if the names are well-formed; may not provide proper ordering if the names are not well-formed.
     */
    //@CheckReturnValue
    /*public*/ virtual int compareSystemNameSuffix(/*@Nonnull*/ QString suffix1,/* @Nonnull*/ QString suffix2, /*@Nonnull*/ NamedBean* n2);


signals:

public slots:

private:
// QObject* _parent;
// QString _name;
// int _state;
// QString _userName;
// QString _systemName;
// QString _displayName;
// QString _comment;
 friend class AbstractAudio;
};

Q_DECLARE_INTERFACE(NamedBean, "Named bean")
#endif // NAMEDBEAN_H
