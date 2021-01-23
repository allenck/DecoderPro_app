#ifndef SIGNALMASTLOGIC_H
#define SIGNALMASTLOGIC_H
#include <QHash>
#include <QString>
#include <QList>
#include "namedbeanhandle.h"
#include "exceptions.h"
#include "libPr3_global.h"
#include "propertychangesupport.h"
#include "section.h"

class Block;
class SignalMast;
class Turnout;
//class NamedBeanHandle;
class LevelXing;
class Sensor;
class LayoutBlock;
class PropertyChangeListener;

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
 * @version			$Revision: 21218 $
 */
/*public*/ /*interface*/class LIBPR3SHARED_EXPORT SignalMastLogic //: public QObject
{
    //Q_OBJECT
public:
    SignalMastLogic(){}
    /**
     * Constant representing that all the user entered details relating to a
     * signal logic are stored.
     * Automatically generated details that have been entered via the setAutoBean
     * are not stored.
     */
    /*public*/ static const int STOREALL;// = 0;
    /**
     * Constant representing that only the basic signal mast logic details are stored.
     * All details that determine the triggering of the logic are not stored.
     */
    /*public*/ static const int STOREMASTSONLY;// = 2;
    /**
     * Constant representing that this signal mast logic is not stored with the
     * panel file.
     * This is used where another piece of code uses handles the dynamic creation
     * of signalmast logic
     */
    /*public*/ static const int STORENONE;// = 4;

    /**
     * Query if we are allowing the system to automatically generated a list of
     * conflicting SignalMast*that have a direct effect on our logic.
     *
     * @param destination Destination SignalMast.
     * @return true if this is allowed.
     */
    /*public*/ bool virtual allowAutoMaticSignalMastGeneration(SignalMast* destination) = 0;

    /**
     * Sets whether we should allow the system to automatically generate a list of
     * signal masts that could cause a conflicting route.
     *
     * @param destination Destination SignalMast.
     * @param allow set true if we are to allow automatic generation.
     */
    /*public*/ void virtual allowAutoMaticSignalMastGeneration(bool allow, SignalMast* destination) = 0;

    /**
     * Sets whether we should lock all turnouts between the source and destination
     * signal masts when the logic goes active, to prevent them from being changed.
     * This is dependant upon the hardware allowing for this.
     *
     * @param destination Destination SignalMast.
     * @param lock set true if the system should lock the turnout.
     */
    /*public*/ void virtual allowTurnoutLock(bool lock, SignalMast* destination) = 0;

    /**
     * Returns true if any of the blocks in the supplied list are included in any
     * of the logics that set this signal.
     */
    /*public*/ bool virtual areBlocksIncluded(QList<Block*> blks) = 0;

    /**
     * This will replace the existing source SignalMast*with a new signal mast instance.
     * This is for use with such tools as the layout editor
     * where a signalmast can at a certain location can be replaced with another, while the
     * remainder of the configuration stays the same.
     */
    /*public*/ void virtual replaceSourceMast(SignalMast* oldMast, SignalMast* newMast) = 0;
    
    /**
     * This will replace the existing destination SignalMast*with a new signal mast instance.
     * This is for use with such tools as the layout editor
     * where a signalmast can at a certain location can be replaced with another, while the
     * remainder of the configuration stays the same.
     */
     /*public*/ void virtual replaceDestinationMast(SignalMast* oldMast, SignalMast* newMast) = 0;
    
    /*public*/ void virtual dispose() = 0;

    /*public*/ virtual Section* getAssociatedSection(SignalMast* /*destination*/) {return NULL;}

    /*public*/ virtual void setAssociatedSection(Section* /*sec*/, SignalMast* /*destination*/) {}

    /*public*/ int virtual getAutoBlockState(Block* /*block*/, SignalMast* /*destination*/) {return 0;}

    /**
    * returns all the blocks that have been detected as being in use for this logic,
    * this includes blocks on level xings that are not directly in the path but do
    * have an affect on the logic
    */
    /*public*/ virtual QList<Block*> getAutoBlocks(SignalMast* destination) = 0;
    
    /**
    * returns only the blocks that have been detected as being directly between
    * the source and destination mast.  The order of the block in the list, is the 
    * order that they are connected.
    */
    /*public*/ virtual QList<Block*> getAutoBlocksBetweenMasts(SignalMast*destination) = 0;

    /*public*/ virtual QList<SignalMast*> getAutoMasts(SignalMast* destination) = 0;

    /*public*/ virtual QString getAutoSignalMastState(SignalMast* mast, SignalMast* destination) = 0;

    /*public*/ virtual int getAutoTurnoutState(Turnout* turnout, SignalMast* destination) = 0;

    /*public*/ virtual QList<Turnout*> getAutoTurnouts(SignalMast* destination) = 0;

    /*public*/ virtual int getBlockState(Block* block, SignalMast* destination) = 0;

    /*public*/ virtual QList<Block*> getBlocks(SignalMast* destination) = 0;

    /*public*/ virtual QString getComment(SignalMast* dest) = 0;

    /*public*/ virtual QList<SignalMast*> getDestinationList() = 0;

    /*public*/ virtual float getMaximumSpeed(SignalMast* destination) = 0;

    /*public*/ virtual int getNumPropertyChangeListeners() = 0;

    /*public*/ virtual int getSensorState(Sensor* sensor, SignalMast* destination) = 0;

    /*public*/ virtual QList<Sensor*> getSensors(SignalMast* destination) = 0;
    
    /*public*/ virtual QList<NamedBeanHandle<Sensor*>* > getNamedSensors(SignalMast* destination) = 0;

    /*public*/ virtual QString getSignalMastState(SignalMast* mast, SignalMast* destination) = 0;

    /*public*/ virtual QList<SignalMast*> getSignalMasts(SignalMast*destination) = 0;

    /*public*/ virtual SignalMast* getSourceMast() = 0;

    /**
     * returns where the signalmast logic should be stored, if so how much.
     */
    /*public*/ virtual int getStoreState(SignalMast* destination) = 0;

    /*public*/ virtual int getTurnoutState(Turnout* turnout, SignalMast* destination) = 0;

    virtual QList<Turnout*> getTurnouts(SignalMast* destination) = 0;
    
    /*public*/ virtual QList<NamedBeanHandle<Turnout*>* > getNamedTurnouts(SignalMast* destination) = 0;

    /*public*/ virtual void initialise() = 0;

    /**
     * Initialise the signalmast after all the parameters have been set.
     */
    /*public*/ virtual void initialise(SignalMast* destination) = 0;

    /**
     * Query if the signalmast logic to the destination signal mast is active.
     */
    /*public*/ virtual bool isActive(SignalMast* dest) = 0;

    /**
     * Get the active destination Signal Mast for this Signal Mast Logic.
     *
     * @return the active signal mast or null if none
     */
    //@CheckForNull
    /*public*/virtual SignalMast* getActiveDestination() {return NULL;}

    /*public*/ virtual bool isBlockIncluded(Block* block, SignalMast* destination) = 0;
    /**
     * Check if signal mast is a destination signal mast in one of the logics
     *
     * @param destination controlled signal mast
     * @return true if destination is a destination mast in this object
     */
    /*public*/ virtual bool isDestinationValid(SignalMast* destination) =0;

    /**
     * Query if the signalmast logic to the destination signal mast is enabled or disabled.
     */
    /*public*/ virtual bool isEnabled(SignalMast* dest) = 0;

    /*public*/ virtual bool isSensorIncluded(Sensor* sensor, SignalMast* destination) = 0;

    /*public*/ virtual bool isSignalMastIncluded(SignalMast* signal, SignalMast* destination) = 0;

    /*public*/ virtual bool isTurnoutIncluded(Turnout* turnout, SignalMast* destination) = 0;

    /**
     * Query if we are allowing the system to lock turnouts when the logic goes
     * active.
     *
     * @param destination Destination SignalMast.
     * @return true if locking is allowed.
     */
    /*public*/ virtual bool isTurnoutLockAllowed(SignalMast* destination) = 0;

    /*public*/ virtual void removeConflictingLogic(SignalMast* sm, LevelXing* lx) = 0;

    /**
     *
     * @param dest Destination SignalMast.
     * @return true if there are no more destination signal masts
     */
    /*public*/ virtual bool removeDestination(SignalMast* dest) = 0;

    /**
     * Sets which blocks must be inactive for the signal not to be set at a stop aspect
     * These blocks are not stored in the panel file.
     * @param blocks
     */
    /*public*/ virtual void setAutoBlocks(/*LinkedHashMap*/QMap<Block*, int> blocks, SignalMast* destination) = 0;

    /**
     * Sets which masts must be in a given state before our mast can be set.
     * These masts are not stored in the panel file.
     * @param masts
     */
    /*public*/ virtual void setAutoMasts(QHash<SignalMast*, QString>* masts, SignalMast* destination) = 0;

    /**
     * Sets which blocks must be inactive for the signal not to be set at a stop aspect
     * These Turnouts are not stored in the panel file.
     */
    /*public*/ virtual void setAutoTurnouts(QHash<Turnout*, int> turnouts, SignalMast* destination) = 0;

    /**
     * Sets which blocks must be inactive for the signal not to be set at a stop aspect
     * @param blocks
     */
    /*public*/ virtual void setBlocks(QHash<Block*, int> blocks, SignalMast* destination) = 0;

    /*public*/ virtual void setComment(QString comment, SignalMast* dest) = 0;

    /*public*/ virtual void setConflictingLogic(SignalMast* sm, LevelXing* lx) = 0;

    /*public*/ virtual void setDestinationMast(SignalMast* dest) = 0;

    /**
     * Sets the logic to the destination signal mast to be disabled.
     */
    /*public*/ virtual void setDisabled(SignalMast* dest) = 0;

    /**
     * Sets the logic to the destination signal mast to be enabled.
     */
    /*public*/ virtual void setEnabled(SignalMast* dest) = 0;

    /*public*/ virtual void setFacingBlock(LayoutBlock* facing) = 0;

    /**
     * Sets which masts must be in a given state before our mast can be set.
     * @param masts
     */
    /*public*/ virtual void setMasts(QHash<SignalMast*, QString> masts, SignalMast* destination) = 0;

//    /*public*/ virtual void setProtectingBlock(LayoutBlock* protecting) = 0;

    /**
     * Sets which sensors must be in a given state before our mast can be set.
     * @param sensors
     */
    /*public*/ virtual void setSensors(QHash<NamedBeanHandle<Sensor*>*, int> sensors, SignalMast* destination) = 0;
    
    /**
	 * Add an individual sensor and its state to the logic
     */
    /*public*/ virtual void addSensor(QString sensorName, int state, SignalMast* destination) = 0;
    
    /**
	 * Remove an individual sensor from the logic
     */    
    /*public*/ virtual void removeSensor(QString sensorName, SignalMast* destination) = 0;
    
    /**
     * Use this to determine if the signalmast logic is stored in the panel file
     * and if all the information is stored.
     * @param store
     */
    /*public*/ virtual void setStore(int store, SignalMast* destination) = 0;

    /**
     * Sets the states that each turnout must be in for signal not to be set at a stop aspect
     * @param turnouts
     */
    /*public*/ virtual void setTurnouts(QHash<NamedBeanHandle<Turnout*>*, int> turnouts, SignalMast* destination) = 0;

    /*public*/ virtual void setupLayoutEditorDetails() = 0;

    /**
     * Sets whether this logic should use the details stored in the layout editor
     * to determine the which blocks, turnouts will make up the logic between
     * the source and destination signal mast.
     *
     * @param boo Use the layout editor details to determine logic details.
     * @param destination Destination SignalMast.
     *
     */
    /*public*/ virtual void useLayoutEditor(bool boo, SignalMast* destination) throw (JmriException) = 0;

    /**
     * Query if we are using the layout editor panels to build the signal mast
     * logic, blocks, turnouts .
     *
     * @param destination Destination SignalMast.
     * @return true if we are using the layout editor to build the signal mast logic.
     */
    /*public*/ virtual bool useLayoutEditor(SignalMast* destination) = 0;

    /**
     * Query if we are using the layout editor block information in the
     * signal mast logic.
     *
     * @param destination Destination SignalMast.
     * @return true if we are using the block information from the layout editor.
     */
    /*public*/ virtual bool useLayoutEditorBlocks(SignalMast* destination) = 0;

    /**
     * Sets whether we should use the information from the layout editor for either
     * blocks or turnouts.
     *
     * @param destination Destination SignalMast.
     * @param blocks set false if not to use the block information gathered from the layouteditor
     * @param turnouts set false if not to use the turnout information gathered from the layouteditor
     */
    /*public*/ virtual void useLayoutEditorDetails(bool turnouts, bool blocks, SignalMast* destination) throw (JmriException) = 0;

    /**
     * Query if we are using the layout editor turnout information in the
     * signal mast logic.
     *
     * @param destination Destination SignalMast.
     * @return true if we are using the turnout information from the layout editor.
     */
    /*public*/ virtual bool useLayoutEditorTurnouts(SignalMast* destination) = 0;
    
    /**
     * Set direction sensors in SML need to autoActiveTrains.
     * @return number of errors
     */
    /*public*/ virtual int setupDirectionSensors() =0;

    /**
     * remove direction sensors from SML need to autoActiveTrains.
     */
    /*public*/ virtual void removeDirectionSensors() = 0;

    /*public*/ virtual void disableLayoutEditorUse() = 0;

    /*public*/ virtual void removePropertyChangeListener(PropertyChangeListener* l) = 0;

    /*public*/ virtual void addPropertyChangeListener(PropertyChangeListener* l) = 0;
    
    /*public*/ virtual LayoutBlock* getFacingBlock() = 0;
    
    /*public*/ virtual LayoutBlock* getProtectingBlock(SignalMast* /*destination*/) = 0;

    virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(SignalMastLogic, "SignalMastLogic")
#endif // SIGNALMASTLOGIC_H
