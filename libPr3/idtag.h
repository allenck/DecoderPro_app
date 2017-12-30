#ifndef IDTAG_H
#define IDTAG_H
#include <QDateTime>
#include "abstractnamedbean.h"
#include "reporter.h"
#include <QDomElement>
#include "libPr3_global.h"
/**
 * IdTag represents a tag that might be attached to a specific piece of
 * rolling stock to uniquely identify it.
 * <P>
 * An example would be an RFID-tag.
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
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @since       2.11.4
 */

class LIBPR3SHARED_EXPORT IdTag : public AbstractNamedBean
{
    Q_OBJECT
public:
    explicit IdTag(QObject *parent = 0) : AbstractNamedBean(parent) {}
    IdTag(QString systemName, QObject *parent) : AbstractNamedBean(systemName, parent) {}
    IdTag(QString systemName, QString userName, QObject *parent) : AbstractNamedBean(systemName, userName, parent) {}
    /**
     * Constant representing an "unseen" state, indicating that the
     * ID tag has not yet been seen.
     */
    /*public*/ static /*final*/const int UNSEEN;// = 0x02;
    /**
     * Constant representing a "seen" state, indicating that the
     * tag has been seen.
     * <p>
     * To determine where this object was last seen, use:
     * <ul>
     * <li>{@link #getWhereLastSeen()}
     * </ul>
     * To determine when this object was last seen, use:
     * <ul>
     * <li>{@link #getWhenLastSeen()}
     * </ul>
     */
    /*public*/ static /*final*/const int SEEN;// = 0x03;
    /**
     * Retrieve a string representation of this tag ID
     * <p>
     * This is the system name without the identifier
     * @return the tag ID
     */
    /*public*/ virtual QString getTagID() = 0;

    /**
     * Set the Reporter that last saw this tag.
     * <p>
     * Also sets the Date/Time when last seen
     * @param reporter Reporter object where last seen
     * @see #getWhereLastSeen()
     * @see #getWhenLastSeen()
     */
    /*public*/ virtual void setWhereLastSeen(Reporter* /*reporter*/) {}

    /**
     * Return the Reporter that last saw this tag, or null if not yet seen
     * @return Reporter object where last seen, or null
     */
    /*public*/ virtual Reporter* getWhereLastSeen() {return NULL;}

    /**
     * Return the Date/Time when this tag was last seen, or null if not yet seen
     * @return Date object when last seen, or null
     */
    /*public*/ virtual QDateTime getWhenLastSeen() {return QDateTime();}

    /**
     * Store the contents of this IdTag object as an XML element
     * @param storeState Determine if the state of this IdTag should be stored
     * @return Element with IdTag contents
     */
 /*public*/ virtual QDomElement store(bool /*storeState*/) {return QDomElement();}

    /**
     * Load contents of IdTag object from an XML element
     * @param e Element containing IdTag details
     */
    /*public*/ virtual void load(QDomElement /*e*/) {}
 /*public*/ virtual QString  toString() {return "";}
signals:
    
public slots:
    
};
//const int IdTag::UNSEEN = 0x02;
//const int IdTag::SEEN = 0x03;

#endif // IDTAG_H
