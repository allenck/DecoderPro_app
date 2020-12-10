#ifndef SIGNALMAST_H
#define SIGNALMAST_H
#include "namedbean.h"
#include "signalsystem.h"
#include "signalappearancemap.h"

/**
 * Represent a signal mast.  A signal mast is one or more signal heads
 * that are treated as a single signal.  (Imagine several heads
 * attached to a single mast, though other implementations are possible)
 * <P>
 * A mast presents an Aspect, as that's a composite of the appearance
 * of the entire signal.
 * <P>
 * This class has three bound parameters:
 *<DL>
 *<DT>aspect<DD>The specific aspect being shown.
 * <p>
 * Aspects are named by a user defined QString name.
 *
 *<DT>lit<DD>Whether the head's lamps are lit or left dark.
 *<P>
 * This differs from the DARK color defined for the appearance
 * parameter, in that it's independent of that.  Lit is
 * intended to allow you to extinquish a signal head for
 * approach lighting, while still allowing it's color to be
 * set to a definite value for e.g. display on a panel or
 * evaluation in higher level logic.
 *
 *<DT>held<DD>Whether the head's lamps should be forced to the RED position
 * in higher-level logic.
 *<P>
 * For use in signaling systems, this is a convenient
 * way of storing whether a higher-level of control (e.g. non-vital
 * system or dispatcher) has "held" the signal at stop. It does
 * not effect how this signal head actually works; any appearance can
 * be set and will be displayed even when "held" is set.
 *</dl>
 * The integer state (getState(), setState()) is the index of the
 * current aspect in the list of all defined aspects.
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
 * @author			Bob Jacobsen Copyright (C) 2002, 2008
 * @author			Pete Cressman Copyright (C) 2009
 * @version			$Revision: 20673 $
 */
/*public*/ /*interface*/ class LIBPR3SHARED_EXPORT SignalMast : public AbstractNamedBean
{
    Q_OBJECT
public:
    SignalMast(QString systemName, QString userName, QObject* parent) : AbstractNamedBean(systemName, userName, parent) {}
    SignalMast(QString systemName, QObject* parent) : AbstractNamedBean(systemName, parent) {}
    ~SignalMast() {}
    SignalMast(const SignalMast&) :AbstractNamedBean() {}
    /**
     * Set aspect to a valid name in the current
     * signal system definition.
     * @throws IllegalArgumentException if not a valid aspect name
     */
    /*public*/ virtual void setAspect(QString /*aspect*/) {}

    /**
     * Get current aspect name. This is a bound property.
     *
     * @return null if not yet set
     */
    /*public*/ virtual QString getAspect() {return"";}

    /*public*/ virtual QVector<QString> getValidAspects() { return QVector<QString>();}

    /*public*/ virtual SignalSystem* getSignalSystem() {return NULL;}

    /*public*/ virtual SignalAppearanceMap* getAppearanceMap() {return NULL;}

    /**
     * Set the specific mast type for this mast.
     * This is the
     * type that appears in the SystemName and filename, i.e. "SL-3-high"
     * for the
     * <a href="http://jmri.org/xml/signals/AAR-1946/appearance-SL-3-high.xml">AAR-1946/appearance-SL-3-high.xml</a>
     * definition.
     */
    /*public*/ virtual void setMastType(/*@Nonnull*/ QString /*type*/) {}

    /**
     * Get the specific mast type for this mast.
     * This is the
     * type that appears in the SystemName and filename, i.e. "SL-3-high"
     * for the
     * <a href="http://jmri.org/xml/signals/AAR-1946/appearance-SL-3-high.xml">AAR-1946/appearance-SL-3-high.xml</a>
     * definition.
     */
    /*public*/ virtual QString getMastType() {return "";}

    /**
     * Lit is a bound parameter. It controls
     * whether the signal head's lamps are lit or left dark.
     */
    /*public*/ virtual bool getLit() {return false;}
    /*public*/ virtual void setLit(bool /*newLit*/) {}

    /**
     * Held is a bound parameter. It controls
     * what mechanisms can control the head's appearance.
     * The actual semantics are defined by those external mechanisms.
     */
    /*public*/ virtual bool getHeld() {return false;}
    /*public*/ virtual void setHeld(bool /*newHeld*/) {}

    /**
     * Determine if the permissive SML logic should be disabled.  The default will be
     * false which means that automatic permissive processing is allowed.  Prototypical
     * CTC designs frequently require an additional action, such as Call-On, to enable permissive aspects.
     * @return true if permissive SML is disabled.
     */
    /*public*/ virtual bool isPermissiveSmlDisabled() {return false;}

    /*public*/ virtual void setPermissiveSmlDisabled(bool /*disabled*/) {}

    /*public*/ virtual bool isAspectDisabled(QString /*aspect*/) {return false;}

    /*public*/ virtual QString className() =0;

    friend class SignalMastIcon;
    friend class DefaultSignalMastLogic;
    friend class DestinationMast;
};
#endif // SIGNALMAST_H
