#ifndef SIGNALGROUP_H
#define SIGNALGROUP_H

#include "namedbean.h"
#include "signalmast.h"
#include "signalhead.h"
#include "turnout.h"

/**
 * SignalGroup.java
 *
 * The Signal Group is used to represent European subsidary signals that would be sited with a
 * signal mast.  Such subsidary signals would be used to indicated routes, junctions and allowable
 * speeds.  Each such route/junction/speed would be represented by a single output signal, that
 * is either off or on.  Within the group on one such signal would be allowed on at any one time.
 *
 * The group is attached to a signal mast, and can be configured to be activated depending upon that
 * masts appearance.
 * The
 * Each signal head within the group is defined with a On and Off appearance, and a set of
 * criteria in the form of matching turnouts and sensor states, that must be met for the head to be
 * set On.
 * <P>
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
 * @author			Pete Cressman Copyright (C) 2009
 * @version			$Revision 1.0 $
 */


/*public*/ /*interface*/class LIBPR3SHARED_EXPORT SignalGroup : public AbstractNamedBean
{
 public:
    SignalGroup(QString systemName, QString userName, QObject* parent) : AbstractNamedBean(systemName, userName, parent) {}
    /**
     * Set enabled status.
     */

    /*public*/ virtual void setEnabled(bool boo) = 0;

    /**
     * Get enabled status
    */
    /*public*/ virtual bool getEnabled() = 0;

    /**
     *  Sets the main Signal Mast to which the Group belongs
     */

    /*public*/ virtual void setSignalMast(QString pName) = 0;

    /**
     *  Sets the main Signal Mast to which the Group belongs
     */

    /*public*/ virtual void setSignalMast(SignalMast* /*mMast*/, QString /*pName*/) {}

     /**
     *  Get the name of the main Signal Mast
     */
    /*public*/ virtual QString getSignalMastName() = 0;

     /**
     *  Get the SignalMast
     */
    /*public*/ virtual SignalMast* getSignalMast() = 0;

    /**
     *  Clear the list of SignalMast Aspects that trigger the group
     */
    /*public*/ virtual void clearSignalMastAspect() {}

     /**
     *  Add an appearance that can trigger the group activation
     */
    /*public*/ void virtual addSignalMastAspect(QString /*sppearance*/) {}

    /*public*/ virtual int getNumSignalMastAspects() = 0;

    /**
     * Method to get a SignalMast Appearance by Index
     *  Returns null if there are no Appearances with that index
     */
    /*public*/ virtual QString getSignalMastAspectByIndex(int x) = 0;

    /**
     * Inquire if a SignalMast Appearance is included.
     */
    /*public*/ virtual bool isSignalMastAspectIncluded(QString appearance) = 0;

    /**
    * Remove a SignalMast Appearance from the set of triggers.
    */
    /*public*/ virtual void deleteSignalMastAspect(QString appearance) = 0;

     /**
     * Add a Signal Head to the Group
     * @param sh The SignalHead as a Named Bean
     */
    /*public*/ virtual void addSignalHead(NamedBeanHandle<SignalHead*>* /*sh*/) {}

     /**
     * Add a Signal Head to the Group
     * @param mHead The SignalHead as a Named Bean
     */
    /*public*/ virtual void addSignalHead(SignalHead* /*mHead*/) {}

    /*public*/ virtual SignalHead* getSignalHeadItemBeanByIndex(int n) = 0;

    /**
     * Method to get a SignalHead by Index
     *  Returns null if there are no Signal Heads with that index
     */
    /*public*/ virtual QString getSignalHeadItemNameByIndex(int n) = 0;

    /**
     * Method to get the On State of a SignalState at Index n
     * <P>
     * @return -1 if there are less than 'n' SignalHeads defined
     */
    /*public*/ int virtual getSignalHeadOnStateByIndex(int n) = 0;

    /**
     * Method to get the Off State of a SignalState at Index n
     * <P>
     * @return -1 if there are less than 'n' SignalHeads defined
     */
    /*public*/ int virtual getSignalHeadOffStateByIndex(int n) = 0;

    /**
    * Delete Signal Head by Name
    */
    /*public*/ void virtual deleteSignalHead(SignalHead* /*pSignal*/) {}

    /**
    * Delete Signal Head by NamedBean
    */
    /*public*/ virtual void deleteSignalHead(NamedBeanHandle<SignalHead*>* /*sh*/) {}

    /*public*/ virtual int getNumSignalHeadItems() = 0;

    /**
     * Method to inquire if a Signal Head is included in this Group
     */
    /*public*/ virtual bool isSignalIncluded(SignalHead* signalHead) = 0;

     /**
     * Method to get the On State of Signal Head
     * @param signalHead The signal head object we are querying
     */
    /*public*/ virtual int getSignalHeadOnState(SignalHead* signalHead) = 0;

    /**
     * Method to get the Off State of Signal Head
     * @param signalHead The signal head bean object we are querying
     */
    /*public*/ int virtual getSignalHeadOffState(SignalHead* signalHead) = 0;

        /**
     * Sets the On State of the Signal in the Group
     * @param head The SignalHead Bean
     * @param state The Apperance that the SignalHead will change to
     *      when the conditions are met.
     */
    /*public*/ virtual void setSignalHeadOnState(SignalHead* head, int state) = 0;

    /**
     * Sets the Off State of the Signal in the Group
     * @param head The SignalHead Bean
     * @param state The Apperance that the SignalHead will change to
     *      when the conditions are NOT met.
     */
    /*public*/ virtual void setSignalHeadOffState(SignalHead* head, int state) = 0;

    /**
    * Sets whether the sensors and turnouts should be treated as seperate
    * calculations or as one, when determining if the signal head should be
    * on or off.
    */
    /*public*/ virtual void setSensorTurnoutOper(SignalHead* pSignal, bool boo) = 0;

    /*public*/ virtual bool getSensorTurnoutOperByIndex(int x) = 0;

    /**
     * Method to get the number of turnouts used to determine the On state
     * for the signalhead at index x
     * <P>
     * @return -1 if there are less than 'n' SignalHeads defined
     */
    /*public*/ virtual int getNumSignalHeadTurnoutsByIndex(int x) = 0;

    /**
    * Method to add a Turnout and its state to a signal head.
    * <p>
    * @param mHead SignalHead we are adding the turnout to
    * @param mTurn Turnout Bean
    * @param state The State that the turnout must be set to.
    */
    /*public*/ virtual void setSignalHeadAlignTurnout(SignalHead* mHead, Turnout* mTurn, int state) = 0;

    /**
     * Inquire if a Turnout is included in the Signal Head Calculation.
     * @param pSignal Signal Head Bean
     * @param pTurnout Turnout Bean
     */
    /*public*/ virtual bool isTurnoutIncluded(SignalHead* pSignal, Turnout* pTurnout) = 0;

    /**
    * Gets the state of the Turnout for the given Signal Head in the group
    * @param pSignal Signal Head Bean
    * @param pTurnout Name of the Turnout within the Group
    * @return -1 if the turnout or signal head is invalid
    */
    /*public*/ virtual int getTurnoutState(SignalHead* pSignal, Turnout* pTurnout) = 0;

    /**
    * Gets the state of the Turnout for the given Signal Head at index x
    * @param x Signal Head at index x
    * @param pTurnout Name of the Turnout within the Group
    * @return -1 if the turnout or signal head is invalid
    */
    /*public*/ virtual int getTurnoutStateByIndex(int x, Turnout* pTurnout) = 0;

    /**
    * Gets the state of the Turnout at index x, for the given Signal Head at index x
    * @param x Signal Head at index x
    * @param pTurnout Turnout at index pTurnout
    * @return -1 if the turnout or signal head is invalid
    */
    /*public*/ virtual int getTurnoutStateByIndex(int x, int pTurnout) = 0;

     /**
    * Gets the Name of the Turnout at index x, for the given Signal Head at index x
    * @param x Signal Head at index x
    * @param pTurnout Turnout at index pTurnout
    * @return null if the turnout or signal head is invalid
    */
    /*public*/ virtual QString getTurnoutNameByIndex(int x, int pTurnout) = 0;

    /**
    * Gets the Name of the Turnout at index x, for the given Signal Head at index x
    * @param x Signal Head at index x
    * @param pTurnout Turnout at index pTurnout
    * @return null if the turnout or signal head is invalid
    */
    /*public*/ virtual Turnout* getTurnoutByIndex(int x, int pTurnout) = 0;

    /**
    * Method to add a Sensor and its state to a signal head.
    * <p>
    * @param mHead SignalHead we are adding the sensor to
    * @param mSensor Sensor Bean
    * @param state The State that the sensor must be set to.
    */
    /*public*/ virtual void setSignalHeadAlignSensor(SignalHead* mHead, Sensor* mSensor, int state) = 0;

    /**
     * Inquire if a Sensor is included in the Signal Head Calculation.
     * @param pSignal Signal Head Bean
     * @param pSensor Sensor Bean
     */
    /*public*/ virtual bool isSensorIncluded(SignalHead* pSignal, Sensor* pSensor) = 0;

    /**
    * Gets the state of the Sensor for the given Signal Head in the group
    * @param pSignal Signal Head Bean
    * @param pSensor Name of the Sensor within the Group
    * @return -1 if the sensor or signal head is invalid
    */
    /*public*/ virtual int getSensorState(SignalHead* pSignal, Sensor* pSensor) = 0;

    /**
    * Gets the state of the Sensor for the given Signal Head at index x
    * @param x Signal Head at index x
    * @param pSensor Name of the Sensor within the Group
    * @return -1 if the sensor or signal head is invalid
    */
    /*public*/ virtual int getSensorStateByIndex(int x, int pSensor) = 0;

    /**
    * Gets the state of the Sensor at index x, for the given Signal Head at index x
    * @param x Signal Head at index x
    * @param pSensor Sensor at index pTurnout
    * @return null if the sensor or signal head is invalid
    */
    /*public*/ virtual QString getSensorNameByIndex(int x, int pSensor) = 0;

    /**
    * Gets the state of the Sensor at index x, for the given Signal Head at index x
    * @param x Signal Head at index x
    * @param pSensor Sensor at index pTurnout
    * @return null if the sensor or signal head is invalid
    */
    /*public*/ virtual Sensor* getSensorByIndex(int x, int pSensor) = 0;

    /*public*/ virtual bool getSensorTurnoutOper(SignalHead* pSignal) = 0;

    /**
     * Method to get the number of Sensors used to determine the On state
     * for the signalhead at index x
     * <P>
     * @return -1 if there are less than 'n' SignalHeads defined
     */
    /*public*/ virtual int getNumSignalHeadSensorsByIndex(int x) = 0;

    /**
     * Delete all Turnouts for a given SignalHead in the group
     * @param pSignal SignalHead Name
     */
    /*public*/ virtual void clearSignalTurnout(SignalHead* pSignal) = 0;

     /**
     * Delete all Sensors for a given SignalHead in the group
     * @param pSignal SignalHead Name
     */
    /*public*/ virtual void clearSignalSensor(SignalHead* pSignal) = 0;

    /*public*/ virtual int getState() = 0;

    /*public*/ virtual void setState(int state) = 0;

    enum STATES
    {
     ONACTIVE = 0,    // route fires if sensor goes active
     ONINACTIVE = 1,  // route fires if sensor goes inactive

     ONCLOSED = 2,    // route fires if turnout goes closed
     ONTHROWN = 4  // route fires if turnout goes thrown
    };
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SignalGroup.class.getName()) = 0;
};
#endif // SIGNALGROUP_H
