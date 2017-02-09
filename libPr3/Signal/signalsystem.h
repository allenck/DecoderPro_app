#ifndef SIGNALSYSTEM_H
#define SIGNALSYSTEM_H
#include "abstractnamedbean.h"
#include "libPr3_global.h"
/**
 * A SignalSystem defines a signaling system by
 * representing the properties of various signal aspects it contains.
 *<p>
 * At present, the signal aspects are denumerated by QStrings,
 * not by specific objects; this table exists to attach properties
 * to those QStrings.
 * <p>
 * Setting or getting the "state" of one of these will throw an error.
 * <p>
 * You'll have one of these objects for each signaling _system_ on
 * your railroad.  In turn, these will be used by 1 to N
 * specific mappings to appearances, see
 * e.g. {@link jmri.implementation.DefaultSignalAppearanceMap}.
 * <p>
 * Insertion order is preserved when retrieving keys.
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
 * @author			Bob Jacobsen Copyright (C) 2009
 * @version			$Revision: 21153 $
 */
/*public*/ /*interface*/class  LIBPR3SHARED_EXPORT SignalSystem : public AbstractNamedBean
{
 Q_OBJECT
public:
    SignalSystem(QString systemName, QString userName="", QObject* parent = 0) : AbstractNamedBean(systemName, userName, parent) {}
    /*public*/ virtual void setProperty(QString aspect, QString key, QVariant value) = 0;
    /*public*/ virtual QVariant getProperty(QString aspect, QString key) = 0;

    /**
    * Add an image or icon type available for use with this signalling system
    */
    /*public*/ virtual void setImageType(QString type) = 0;

    /**
    * Returns a list of the image/icon sets available for use with this signalling
    * system.  If no specific image types are provided for then an empty list is
    * returned.
    */
//    /*public*/ java.util.Enumeration<QString> getImageTypeList();
    virtual QStringList getImageTypeList() = 0;

    /**
     * Get all aspects currently defined.
     */
//    /*public*/ java.util.Enumeration<QString> getAspects();
    virtual QStringList getAspects() = 0;

    /**
     * Get all keys currently defined on any aspect.
     * <p>
     * Each key only appears once, even if used on more than one
     * aspect.
     * <p>
     * Note that a given key may or may not appear on a given
     * aspect.
     */
//    /*public*/ java.util.Enumeration<QString> getKeys();
    virtual QStringList getKeys() = 0;

    /**
     * Is this aspect known?
     */
    /*public*/ virtual bool checkAspect(QString aspect) = 0;

    /*public*/ virtual QString getAspect(QVariant obj, QString key) = 0;

    /*public*/ virtual float getMaximumLineSpeed() = 0;
friend class DefaultSignalMastLogic;
friend class SignalSpeedMap;
};
#endif // SIGNALSYSTEM_Hvirtual
