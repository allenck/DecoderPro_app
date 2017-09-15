#ifndef NAMEDBEAN_H
#define NAMEDBEAN_H

#include <QObject>
#include "propertychangelistener.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT NamedBean : public  QObject
{
 //Q_OBJECT
public:
    explicit NamedBean(QObject *parent = 0);
    NamedBean(QString name, QObject *parent = 0);
    NamedBean(const NamedBean&);
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

        // user identification, _bound_ parameter so manager(s) can listen
        virtual QString getUserName();
        virtual void setUserName(QString s);
        //virtual void setSysName(QString s);
        /**
         * Get a system-specific name.  This encodes the hardware addressing
         * information.
         */
        virtual QString getSystemName();
        /*
        * return user name if it exists, otherwise return System name
        */
        virtual QString getDisplayName();
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
        virtual void addPropertyChangeListener(PropertyChangeListener* l, QString name, const QString listenerRef);

        virtual void addPropertyChangeListener(PropertyChangeListener* l);
        /**
         * Remove a request for a call-back when a bound property changes.
         */
        virtual void removePropertyChangeListener(PropertyChangeListener* l);

        virtual void updateListenerRef(PropertyChangeListener* l, QString newName);
        /**
        * Get the textual reference for the specific listener
        *
        */
        virtual QString getListenerRef(PropertyChangeListener* l);

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
        * @param name  - The name (either system or user) that the listener has registered as
        *           referencing this namedBean
        */
        virtual QList<PropertyChangeListener*>* getPropertyChangeListeners(QString name);

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
        virtual void setComment(QString comment);

        /**
         * Attach a key/value pair to the
         * NamedBean, which can be retrieved later.
         * These are not bound properties as yet,
         * and don't throw events on modification.
         * Key must not be null.
         */
        virtual void setProperty(QString key, QVariant value);

        /**
         * Retrieve the value associated with a key.
         * If no value has been set for that key, returns null.
         */
        virtual QVariant getProperty(QString key);

    /**
     * Remove the key/value pair against the NamedBean.
     */
    /*public*/ virtual void removeProperty(/*@Nonnull*/ QString key) {}
        /**
         * Retrieve the complete current set of keys.
         */
        virtual QList<QString> getPropertyKeys()  {return QList<QString>();}
    /*public*/ virtual void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) {}//throws java.beans.PropertyVetoException;


        virtual bool hashCode() {return false;}
signals:

public slots:

private:
 QObject* _parent;
 QString _name;
 int _state;
 QString _userName;
 QString _systemName;
 QString _displayName;
 QString _comment;
 friend class AbstractAudio;
};
Q_DECLARE_INTERFACE(NamedBean, "Named bean")
#endif // NAMEDBEAN_H
