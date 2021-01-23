#ifndef SIGNALMASTLOGICMANAGER_H
#define SIGNALMASTLOGICMANAGER_H
#include "abstractmanager.h"
#include "exceptions.h"
#include "libPr3_global.h"
#include "propertychangesupport.h"

/**
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
 * @author			Kevin Dickerson Copyright (C) 2011
 * @version			$Revision: 20228 $
 */
class SignalMast;
class LayoutEditor;
class SignalMastLogic;
/*public*/ /*interface*/class LIBPR3SHARED_EXPORT SignalMastLogicManager : public AbstractManager
{
 Q_OBJECT
public:
 SignalMastLogicManager(QObject* parent=0) : AbstractManager(parent) {}
    /*public void addDestinationMastToLogic(SignalMastLogic src, SignalMast destination) = 0;*/

    /**
     * This will replace all instances of an old SignalMast (either source or destination)
     * with the new signal mast instance.  This is for use with such tools as the layout editor
     * where a signalmast can at a certain location can be replaced with another, while the
     * remainder of the configuration stays the same.
     */
    /*public*/ virtual void replaceSignalMast(SignalMast* oldMast, SignalMast* newMast) = 0;

    /**
     * Discover all possible valid source and destination signalmasts past pairs
     * on all layout editor panels.
     */
    /*public*/ virtual void automaticallyDiscoverSignallingPairs() throw (JmriException) = 0;

    /**
     * This uses the layout editor to check if the destination signalmast is
     * reachable from the source signalmast
     *
     * @param sourceMast Source SignalMast
     * @param destMast Destination SignalMast
     * @return true if valid, false if not valid.
     */
   // /*public*/ boolean checkValidDest(SignalMast sourceMast, SignalMast destMast) throws JmriException;

    /**
     * Discover valid destination signalmasts for a given source signal on a
     * given layout editor panel.
     * @param source Source SignalMast
     * @param layout Layout Editor panel to check.
     */
    /*public*/ virtual void discoverSignallingDest(SignalMast* source, LayoutEditor* layout) throw (JmriException) = 0;

    /*public*/ virtual void dispose() = 0;

    /**
     * Gather a list of all the signal mast logics, by destination signal mast
     */
    /*public*/ virtual QList<SignalMastLogic*> getLogicsByDestination(SignalMast* destination) = 0;

    /*public*/ virtual long getSignalLogicDelay() = 0;

    /*public*/ virtual SignalMastLogic* getSignalMastLogic(SignalMast* source) = 0;

    /**
     * Returns an arraylist of signalmastlogic
     * @return An ArrayList of SignalMast logics
     */
    /*public*/ virtual QList<SignalMastLogic*> getSignalMastLogicList() = 0;

    /**
     * Used to initialise all the signalmast logics. primarily used after loading.
     */
    /*public*/ virtual void initialise() = 0;

    /*public*/ virtual SignalMastLogic* newSignalMastLogic(SignalMast* source) = 0;

    ///*public*/ void removeDestinationMastToLogic(SignalMastLogic src, SignalMast destination) = 0;

    /**
     * Remove a destination mast from the signalmast logic
     * @param sml The signalmast logic of the source signal
     * @param dest The destination mast
     */
    /*public*/ virtual void removeSignalMastLogic(SignalMastLogic* sml, SignalMast* dest) = 0;

    /**
     * Completely remove the signalmast logic.
     */
    /*public*/ virtual void removeSignalMastLogic(SignalMastLogic* sml) = 0;

    /**
     * Completely remove the signalmast logic, for a specific signal mast
     */
    /*public*/ virtual void removeSignalMast(SignalMast* mast) = 0;

    /*public*/ virtual void disableLayoutEditorUse(SignalMast* /*mast*/) {}

    /*public*/ virtual void swapSignalMasts(SignalMast* mastA, SignalMast* mastB) = 0;

    /*public*/ virtual bool isSignalMastUsed(SignalMast* mast) = 0;

    /*public*/ virtual void setSignalLogicDelay(long l) = 0;
    //PropertyChangeSupport* pcs;
    /**
     * Iterate over the signal masts setting up direction Section sensors.
     * @return error count
     */
    /*public*/ virtual int setupSignalMastsDirectionSensors() = 0;

    /**
     * Iterate over the signal masts setting up direction Section sensors.
     */
    /*public*/ virtual void removeSignalMastsDirectionSensors() = 0;

 friend class RunnableThis;
 friend class DestinationMast;
 friend class LevelXing;
 friend class DefaultSignalMastLogicManagerXml;
 friend class SignallingGuiTools;
 friend class SignallingSourcePanel;
 friend class SignalMastAppearanceModel;
 friend class LayoutTurnout;
 friend class LayoutSlip;
};
#endif // SIGNALMASTLOGICMANAGER_H
