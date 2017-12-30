#ifndef BASICROSTERENTRY_H
#define BASICROSTERENTRY_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "dcclocoaddress.h"
#include <QtXml>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT BasicRosterEntry : public QObject
{
    Q_OBJECT
public:
    explicit BasicRosterEntry(QObject *parent = 0);
    /**
     * RosterEntry represents a single element in a locomotive roster, including
     * information on how to locate it from decoder information.
     * <p>
     * The roster interface is too allow access to the Basic details of a Roster entry in the jmri.jmrit.roster package
     * from the jmri.jmrix package.
     * <p>
     * Primarily this only deals as a method to provide other packages with access to the information
     * rather than being able set or create items.  However access to set and get Attributes is allowed
     * so that attributes like running duration can be recorded, with the store option also avaiable.
     * <p>
     * For Full read/write and creation of RosterEntries use the @link jmri.jmrit.roster.RosterEntry
     * <p>
     * All properties, including the "Attributes", are bound.
     *
     * @author    Bob Jacobsen   Copyright (C) 2001, 2002, 2004, 2005, 2009
     * @author    Kevin Dickerson Copyright 2012
     * @version   $Revision: 20373 $
     * @see       jmri.jmrit.roster.RosterEntry
     *
     */
//    public interface BasicRosterEntry {
        virtual QString getId() = 0;

        virtual QString getDccAddress() = 0;

        virtual bool isLongAddress() = 0;

        virtual DccLocoAddress* getDccLocoAddress() = 0;

        virtual QString getShuntingFunction() = 0;

        virtual void setOpen(bool  boo) = 0;

        virtual bool isOpen() = 0;

        virtual void putAttribute(QString key, QString value) = 0;
        virtual QString getAttribute(QString /*key*/) {return "";}

        virtual void deleteAttribute(QString key) = 0;

        virtual QStringList getAttributeList() = 0;

        virtual int getMaxSpeedPCT() = 0;

        /**
         * Create an XML element to represent this Entry. This member has to remain synchronized with the
         * detailed DTD in roster-config.xml.
         * @return Contents in a JDOM Element
         */
        virtual QDomElement store() { return QDomElement();}

        virtual QString titleString() {return "";}

        virtual QString toString() = 0;

//        virtual void addPropertyChangeListener(java.beans.PropertyChangeListener l);

//        virtual void removePropertyChangeListener(java.beans.PropertyChangeListener l);


signals:
    
public slots:
    
};

#endif // BASICROSTERENTRY_H
