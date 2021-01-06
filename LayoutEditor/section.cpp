#include "section.h"
#include "instancemanager.h"
#include "scale.h"
#include "layoutturnout.h"
#include "layoutblock.h"
#include "tracksegment.h"
#include "signalhead.h"
#include "block.h"
#include "layouteditor.h"
#include "connectivityutil.h"
#include "abstractsignalheadmanager.h"
#include "vptr.h"
#include "jmrijframe.h"
#include "path.h"

const /*static*/ /*final*/ int Section::UNOCCUPIED = 0x04;

Section::Section(QObject *parent) :
    AbstractNamedBean(parent)
{
//    /*public*/ const /*static*/ /*final*/ int Section::OCCUPIED;// = Block::OCCUPIED;
//    /*public*/ const /*static*/ /*final*/ int Section::UNOCCUPIED;// = Block::UNOCCUPIED;
}
/**
 * Sections represent a group of one or more connected Blocks that may be
 *	allocated to a train travelling in a given direction.
 * <P>
 * A Block may be in multiple Sections. All Blocks contained in a given
 *	section must be unique. Blocks are kept in order--the first block is
 *	connected to the second, the second is connected to the third, etc.
 * <P>
 * A Block in a Section must be connected to the Block before it (if there is
 *	one) and to the Block after it (if there is one), but may not be connected
 *	to any other Block in the Section. This restriction is enforced when a
 *  Section is created, and checked when a Section is loaded from disk.
 * <P>
 * A Section has a "direction" defined by the sequence in which Blocks are
 *	added to the Section. A train may run through a Section in either the
 *	forward direction (from first block to last block) or reverse direction
 *	(from last block to first block).
 * <P>
 * A Section has one or more EntryPoints. Each EntryPoint is a Path of one
 *	of the Blocks in the Section that defines a connection to a Block outside
 *	of the Section. EntryPoints are grouped into two lists:
 *		"forwardEntryPoints" - entry through which will result in a train
 *				travelling in the "forward" direction
 *		"reverseEntryPoints" - entry through which will result in a train
 *				travelling in the "reverse" direction
 *  Note that "forwardEntryPoints" are also reverse exit points, and vice versa.
 * <P>
 * A Section has one of the following states"
 *		FREE - available for allocation by a dispatcher
 *		FORWARD - allocated for travel in the forward direction
 *		REVERSE - allocated for travel in the reverse direction
 * <P>
 * A Section has an occupancy.  A Section is OCCUPIED if any of its Blocks is
 *  OCCUPIED. A Section is UNOCCUPIED if all  of its Blocks are UNOCCUPIED
 * <P>
 * A Section of may be allocated to only one train at a time, even if the trains are
 *  travelling in the same direction. If a Section has sufficient space for multiple
 *  trains travelling in the same direction it should be broken up into multiple
 *  Sections so the trains can follow each other through the original Section.
 * <P>
 * A Section may not contain any reverse loops. The track that is reversed in a
 *	reverse loop must be in a separate Section.
 * <P>
 * Each Section optionally carries two direction sensors, one for the forward direction
 *	and one for the reverse direction. These sensors force signals for travel in their
 *	respective directions to "RED" when they are active. When the Section is free,
 *	both the sensors are Active. These internal sensors follow the state of the
 *	Section, permitting signals to function normally in the direction of allocation.
 * <P>
 * Each Section optionally carries two stopping sensors, one for the forward direction
 *  and one for the reverse direction.  These sensors change to active when a train
 *  traversing the Section triggers its sensing device. Stopping sensors are
 *  physical layout sensors, and may be either point sensors or occupancy sensors for
 *  short blocks at the end of the Section. A stopping sensor is used during automatic
 *  running to stop a train that has reached the end of its allocated Section. This is
 *  needed, for example, to allow a train to enter a passing siding and clear the
 *  track behind it. When not running automatically, these sensors may be used to light
 *  panel lights to notify the dispatcher that the train has reached the end of the
 *  Section.
 * <P>
 * This Section implementation provides for delayed initialization of blocks and
 *	direction sensors to be independent of order of items in panel files.
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation. See the "COPYING" file for
 * a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Dave Duchamp Copyright (C) 2008,2010
 *
 * @version			$Revision: 21280 $
 */
//public class Section extends AbstractNamedBean
//    implements  java.io.Serializable {

/*public*/ /*const static*/ /*final*/ int Section::UNKNOWN = 0x01;
/*public*/ /*const static*/ /*final*/ int Section::FREE = 0x02;
/*public*/ /*const static*/ /*final*/ int Section::FORWARD = 0x04;
/*public*/ /*const static*/ /*final*/ int Section::REVERSE = 0X08;

/*final public static*/ int Section::USERDEFINED = 0x01; //Default Save all the information
/*final public static*/ int Section::SIGNALMASTLOGIC = 0x02; //Save only the name, blocks will be added by the signalmast logic
/*final public static*/ int Section::DYNAMICADHOC = 0x00;  //created on an as required basis, not to be saved.

/*public*/ Section::Section(QString systemName, QString userName, QObject *parent)
    : AbstractNamedBean(systemName.toUpper(), userName, parent)
{
 //super(systemName.toUpperCase(), userName);
 mBlockEntries = new QList<Block*>();
 mForwardEntryPoints = new QVector<EntryPoint*>();
 mReverseEntryPoints = new QVector<EntryPoint*>();
 mState = FREE;
 mOccupancy = UNOCCUPIED;
 mOccupancyInitialized = false;
 mFirstBlock = nullptr;
//    OCCUPIED = Block::OCCUPIED;
//    UNOCCUPIED = Block::UNOCCUPIED;
 mBlockListeners = new QList<PropertyChangeListener*>();
 nbhm = (NamedBeanHandleManager*)(InstanceManager::getDefault("NamedBeanHandleManager"));
 initializationNeeded = false;
 blockNameList = new QVector<QString>();
 initializationNeeded = false;
 blockNameList = new QVector<QString>();
 tempSensorName = "";
 listener = nullptr;
 blockIndex = 0;  // index of last block returned
 mForwardBlockingSensorName = "";
 mForwardBlockingSensorName = "";
 mLastBlock = nullptr;
 mReverseBlockingSensorName = "";
 mForwardBlockingNamedSensor = nullptr;
 mForwardStoppingNamedSensor = nullptr;
 mReverseStoppingNamedSensor = nullptr;
 mReverseBlockingNamedSensor = nullptr;
 sectionType = USERDEFINED;
}

///*public*/ Section::Section(QString systemName) : AbstractNamedBean(systemName)
//{
//    //super(systemName.toUpperCase());
//    mBlockEntries = new QList<Block>();
//    mForwardEntryPoints = new QList<EntryPoint>();
//    mReverseEntryPoints = new QList<EntryPoint>();
//    mState = FREE;
//    mOccupancy = UNOCCUPIED;
//    mFirstBlock = nullptr;
//    OCCUPIED = Block::OCCUPIED;
//    UNOCCUPIED = Block::UNOCCUPIED;
//    nbhm = InstanceManager::getDefault("NamedBeanHandleManager");
//    initializationNeeded = false;
//    blockNameList = new QVector<QString>();
// tempSensorName = "";
// listener = nullptr;
// blockIndex = 0;  // index of last block returned
//}


/**
 * Query the state of the Section
 */
/*public*/ int Section::getState() { return mState; }
//#if 1
/**
 * Set the state of the Section
 */
/*public*/ void Section::setState(int state) {
    if ( (state==Section::FREE) || (state==FORWARD) || (state==Section::REVERSE) ) {
        int old = mState;
        mState = state;
        firePropertyChange("state", (old), (mState));
        // update the forward/reverse blocking sensors as needed
        if (state==FORWARD) {
            try {
                if ( (getForwardBlockingSensor()!=nullptr) && (getForwardBlockingSensor()->getState()!=Sensor::INACTIVE) )
                    getForwardBlockingSensor()->setState(Sensor::INACTIVE);
                if ( (getReverseBlockingSensor()!=nullptr) && (getReverseBlockingSensor()->getState()!=Sensor::ACTIVE) )
                    getReverseBlockingSensor()->setKnownState(Sensor::ACTIVE);
            } catch (JmriException* reason) {
                log.error ("Exception when setting Sensors for Section "+getSystemName());
            }
        }
        else if (state==REVERSE) {
            try {
                if ( (getReverseBlockingSensor()!=nullptr) && (getReverseBlockingSensor()->getState()!=Sensor::INACTIVE) )
                    getReverseBlockingSensor()->setKnownState(Sensor::INACTIVE);
                if ( (getForwardBlockingSensor()!=nullptr) && (getForwardBlockingSensor()->getState()!=Sensor::ACTIVE) )
                    getForwardBlockingSensor()->setKnownState(Sensor::ACTIVE);
            } catch (JmriException reason) {
                log.error ("Exception when setting Sensors for Section "+getSystemName());
            }
        }
        else if (state==FREE) {
            try {
                if ( (getForwardBlockingSensor()!=nullptr) && (getForwardBlockingSensor()->getState()!=Sensor::ACTIVE) )
                    getForwardBlockingSensor()->setKnownState(Sensor::ACTIVE);
                if ( (getReverseBlockingSensor()!=nullptr) && (getReverseBlockingSensor()->getState()!=Sensor::ACTIVE) )
                    getReverseBlockingSensor()->setKnownState(Sensor::ACTIVE);
            } catch (JmriException reason) {
                log.error ("Exception when setting Sensors for Section "+getSystemName());
            }
        }
    }
    else
        log.error("Attempt to set state of Section "+getSystemName()+" to illegal value - "+state);
}

/**
 * Query the occupancy of a section
 */
/*public*/ int Section::getOccupancy() {
    if (mOccupancyInitialized) return mOccupancy;
    // initialize occupancy
    mOccupancy = UNOCCUPIED;
    for (int i=0;i<mBlockEntries->size();i++) {
        if (mBlockEntries->at(i)->getState() == OCCUPIED) {
            mOccupancy = OCCUPIED;
        }
        else if (mBlockEntries->at(i)->getState() != UNOCCUPIED) {
            log.warn("Occupancy of block "+mBlockEntries->at(i)->getSystemName()+
                        " is not OCCUPIED or UNOCCUPIED in Section - "+getSystemName());
            return (mBlockEntries->at(i)->getState());
        }
    }
    mOccupancyInitialized = true;
    return mOccupancy;
}
/*private*/ void Section::setOccupancy(int occupancy) {
    int old = mOccupancy;
    mOccupancy = occupancy;
    firePropertyChange("occupancy", (old), (mOccupancy));
}

/**
 * Access methods for forward and reverse blocking sensors
 *	The set methods return a Sensor object if successful, or else they
 *		return "nullptr";
 */
/*public*/ QString Section::getForwardBlockingSensorName() {
    if(mForwardBlockingNamedSensor!=nullptr)
        return mForwardBlockingNamedSensor->getName();
    return mForwardBlockingSensorName;

}
/*public*/ Sensor* Section::getForwardBlockingSensor() {
    if(mForwardBlockingNamedSensor!=nullptr){
        return mForwardBlockingNamedSensor->getBean();
    }
    if ((mForwardBlockingSensorName!=nullptr) &&
                        (!mForwardBlockingSensorName.isEmpty()) ) {
        Sensor* s = (Sensor*)InstanceManager::sensorManagerInstance()->
                                            getSensor(mForwardBlockingSensorName);
        if (s==nullptr) {
            log.error("Missing Sensor - "+mForwardBlockingSensorName+" - when initializing Section - "+
                                getSystemName());
            return nullptr;
        }
        mForwardBlockingNamedSensor = nbhm->getNamedBeanHandle(mForwardBlockingSensorName, s);
        return s;
    }
    return nullptr;
}

/*public*/ Sensor* Section::setForwardBlockingSensorName(QString forwardSensor) {
    if ( (forwardSensor==nullptr) || (forwardSensor.length()<=0) ) {
        mForwardBlockingSensorName = "";
        mForwardBlockingNamedSensor = nullptr;
        return nullptr;
    }
    tempSensorName = forwardSensor;
    Sensor* s = validateSensor();
    if (s==nullptr) {
        // sensor name not correct or not in sensor table
        log.error("Sensor name - "+forwardSensor+" invalid when setting forward sensor in Section "+getSystemName());
        return nullptr;
    }
    nbhm->getNamedBeanHandle(tempSensorName, s);
    mForwardBlockingSensorName = tempSensorName;
    return s;
}


/*public*/ void Section::delayedSetForwardBlockingSensorName(QString forwardSensor) {
    mForwardBlockingSensorName = forwardSensor;
}
/*public*/ QString Section::getReverseBlockingSensorName() {
    if(mReverseBlockingNamedSensor!=nullptr)
        return mReverseBlockingNamedSensor->getName();
    return mReverseBlockingSensorName;
}
/*public*/ Sensor* Section::setReverseBlockingSensorName(QString reverseSensor) {
    if ( (reverseSensor==nullptr) || (reverseSensor.length()<=0) ) {
        mReverseBlockingNamedSensor = nullptr;
        mReverseBlockingSensorName = "";
        return nullptr;
    }
    tempSensorName = reverseSensor;
    Sensor* s = validateSensor();
    if (s==nullptr) {
        // sensor name not correct or not in sensor table
        log.error("Sensor name -"+reverseSensor+"invalid when setting reverse sensor in Section "+getSystemName());
        return nullptr;
    }
    mReverseBlockingNamedSensor = nbhm->getNamedBeanHandle(tempSensorName, s);
    mReverseBlockingSensorName = tempSensorName;
    return s;
}

/*public*/ void Section::delayedSetReverseBlockingSensorName(QString reverseSensor) {
    mReverseBlockingSensorName = reverseSensor;
}
/*public*/ Sensor* Section::getReverseBlockingSensor() {
    if(mReverseBlockingNamedSensor!=nullptr){
        return mReverseBlockingNamedSensor->getBean();
    }
    if ((mReverseBlockingSensorName!=nullptr) &&
                        (mReverseBlockingSensorName!=("")) ) {
        Sensor* s = InstanceManager::sensorManagerInstance()->
                                            getSensor(mReverseBlockingSensorName);
        if (s==nullptr) {
            log.error("Missing Sensor - "+mReverseBlockingSensorName+" - when initializing Section - "+
                                getSystemName());
            return nullptr;
        }
        mReverseBlockingNamedSensor = nbhm->getNamedBeanHandle(mReverseBlockingSensorName, s);
        return s;
    }
    return nullptr;
}
/*public*/ Block* Section::getLastBlock() {
    return mLastBlock;
}

/*private*/ Sensor* Section::validateSensor() {
    // check if anything entered
    if (tempSensorName.length()<1) {
        // no sensor specified
        return nullptr;
    }
    // get the sensor corresponding to this name
    Sensor* s = InstanceManager::sensorManagerInstance()->getSensor(tempSensorName);
    if (s==nullptr) return nullptr;
    if ( tempSensorName!=(s->getUserName()) ) {
        tempSensorName = tempSensorName.toUpper();
    }
    return s;
}

/**
 * Access methods for forward and reverse stopping sensors
 *	The set methods return a Sensor object if successful, or else they
 *		return "nullptr";
 */
/*public*/ QString Section::getForwardStoppingSensorName() {
    if(mForwardStoppingNamedSensor!=nullptr)
        return mForwardStoppingNamedSensor->getName();
    return mForwardStoppingSensorName;
}
/*public*/ Sensor* Section::getForwardStoppingSensor() {
    if(mForwardStoppingNamedSensor!=nullptr){
        return mForwardStoppingNamedSensor->getBean();
    }
    if (( mForwardStoppingSensorName!=nullptr) &&
                        (mForwardStoppingSensorName!=("")) ) {
        Sensor* s = InstanceManager::sensorManagerInstance()->
                                            getSensor(mForwardStoppingSensorName);
        if (s==nullptr) {
            log.error("Missing Sensor - "+mForwardStoppingSensorName+" - when initializing Section - "+
                                getSystemName());
            return nullptr;
        }
        mForwardStoppingNamedSensor = nbhm->getNamedBeanHandle(mForwardStoppingSensorName, s);
        return s;
    }
    return nullptr;
}
/*public*/ Sensor* Section::setForwardStoppingSensorName(QString forwardSensor) {
    if ( (forwardSensor==nullptr) || (forwardSensor.length()<=0) ) {
        mForwardStoppingNamedSensor = nullptr;
        mForwardStoppingSensorName = "";
        return nullptr;
    }
    tempSensorName = forwardSensor;
    Sensor* s = validateSensor();
    if (s==nullptr) {
        // sensor name not correct or not in sensor table
        log.error("Sensor name -"+forwardSensor+"invalid when setting forward sensor in Section "+getSystemName());
        return nullptr;
    }
    mForwardStoppingNamedSensor = nbhm->getNamedBeanHandle(tempSensorName, s);
    mForwardStoppingSensorName = tempSensorName;
    return s;
}
/*public*/ void Section::delayedSetForwardStoppingSensorName(QString forwardSensor) {
    mForwardStoppingSensorName = forwardSensor;
}
/*public*/ QString Section::getReverseStoppingSensorName() {
    if(mReverseStoppingNamedSensor!=nullptr)
        return mReverseStoppingNamedSensor->getName();
    return mReverseStoppingSensorName;
}
/*public*/ Sensor* Section::setReverseStoppingSensorName(QString reverseSensor) {
    if ( (reverseSensor==nullptr) || (reverseSensor.length()<=0) ) {
        mReverseStoppingNamedSensor = nullptr;
        mReverseStoppingSensorName = "";
        return nullptr;
    }
    tempSensorName = reverseSensor;
    Sensor* s = validateSensor();
    if (s==nullptr) {
        // sensor name not correct or not in sensor table
        log.error("Sensor name -"+reverseSensor+"invalid when setting reverse sensor in Section "+getSystemName());
        return nullptr;
    }
    mReverseStoppingNamedSensor = nbhm->getNamedBeanHandle(tempSensorName, s);
    mReverseStoppingSensorName = tempSensorName;
    return s;
}
/*public*/ void Section::delayedSetReverseStoppingSensorName(QString reverseSensor) {
    mReverseStoppingSensorName = reverseSensor;
}
/*public*/ Sensor* Section::getReverseStoppingSensor() {
    if(mReverseStoppingNamedSensor!=nullptr){
        return mReverseStoppingNamedSensor->getBean();
    }
    if ( (mReverseStoppingSensorName!=nullptr) &&
                        (mReverseStoppingSensorName!=("")) ) {
        Sensor* s = InstanceManager::sensorManagerInstance()->
                                            getSensor(mReverseStoppingSensorName);
        if (s==nullptr) {
            log.error("Missing Sensor - "+mReverseStoppingSensorName+" - when initializing Section - "+
                                getSystemName());
            return nullptr;
        }
        mReverseStoppingNamedSensor = nbhm->getNamedBeanHandle(mReverseStoppingSensorName, s);
        return s;
    }
    return nullptr;
}

/**
 *  Add a Block to the Section
 *  Block and sequence number must be unique within the Section.
 *  Block sequence numnbers are set automatically as blocks are added.
 *	Returns "true" if Block was added.  Returns "false" if Block does not connect to
 *		the current Block, or the Block is not unique.
 */
/*public*/ bool Section::addBlock( Block* b ) {
    // validate that this entry is unique, if not first.
    if (mBlockEntries->isEmpty()) {
        mFirstBlock = b;
    }
    else {
        // check that block is unique
        for (int i=0;i<mBlockEntries->size();i++) {
            if (mBlockEntries->at(i) == b) {
             return false; // already present
         }            // Note: connectivity to current block is assumed to have been checked
        }
    }
    // a lot of this code searches for blocks by their user name.
    // warn if there isn't one.
    if (b->getUserName() == "")
    {
     log.warn(tr("Block %1 does not have a user name, may not work correctly in Section %2").arg(
                b->getSystemName()).arg(getSystemName()));
    }
    // add Block to the Block list
    mBlockEntries->append(b);
    mLastBlock = b;
    // check occupancy
    if (b->getState() == OCCUPIED) {
        if (mOccupancy!=OCCUPIED) {
            setOccupancy(OCCUPIED);
        }
    }
    b->addPropertyChangeListener(listener = (PropertyChangeListener*)this);// {
//#if 0
//// TODO::
//            public void propertyChange(PropertyChangeEvent* e)
//                { handleBlockChange(e); }
//        });
//#endif
//connect(b, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    mBlockListeners->append(listener);
    return true;
}

/*public*/ void Section::delayedAddBlock(QString blockName) {
    initializationNeeded = true;
    blockNameList->append(blockName);
}
/*private*/ void Section::initializeBlocks()
{
 for (int i = 0; i<blockNameList->size(); i++)
 {
  Block* b = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(blockNameList->at(i));
  if (b==nullptr)
  {
   log.error("Missing Block - "+blockNameList->at(i)+" - when initializing Section - "+
                       getSystemName());
  }
  else {
      if (mBlockEntries->size()==0) {
          mFirstBlock = b;
      }
      mBlockEntries->append(b);
      mLastBlock = b;
      PropertyChangeListener* listener = nullptr;
      b->addPropertyChangeListener(listener = (PropertyChangeListener*)this );//{
//#if 0
//                    // TODO::

//                    public void propertyChange(java.beans.PropertyChangeEvent e)
//                        { handleBlockChange(e); }
//                });
//#endif
   //connect(b, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   mBlockListeners->append(listener);
  }
 }
 initializationNeeded = false;
}
/**
 * Handle change in occupancy of a Block in the Section
 */
void Section::propertyChange(PropertyChangeEvent* e)
{
 Q_UNUSED(e);

 int o = UNOCCUPIED;
 for (int i = 0; i<mBlockEntries->size(); i++)
 {
  if (mBlockEntries->at(i)->getState() == OCCUPIED)
  {
   o = OCCUPIED;
   break;
  }
 }
 if (mOccupancy!=o)
  setOccupancy(o);
}

/**
 * Get a Copy of this Section's Block List
 */
/*public*/ QVector<Block*>* Section::getBlockList() {
    if (initializationNeeded) initializeBlocks();
    QVector<Block*>* a = new QVector<Block*>();
    for (int i = 0; i<mBlockEntries->size(); i++) {
        a->append(mBlockEntries->at(i));
    }
    return a;
}

/**
 * Gets the number of Blocks in this Section
 */
/*public*/ int Section::getNumBlocks() {
    if (initializationNeeded) initializeBlocks();
    return mBlockEntries->size();
}

/**
 * Gets length of Section in scale feet or scale meters.
 *    Length of the Section is calculated by summing the lengths of
 *        all Blocks in the section.  If all Block lengths have not been
 *        entered, length will not be correct.
 *    If meters = true, units of returned length is scale meters
 *    If meters = false, units of returned length is scale feet
 *	  scale = layout scale according to definitions in jmri.Scale.java
 */
/*public*/ float Section::getLengthF(bool meters, Scale* scale) {
    if (initializationNeeded) initializeBlocks();
    float length = 0.0f;
    for (int i = 0; i<mBlockEntries->size(); i++) {
        length = length + mBlockEntries->at(i)->getLengthMm();
    }
    length = length/(float)(scale->getScaleFactor());
    if (meters) return (length*0.001f);
    return (length*0.00328084f);
}
/*public*/ int Section::getLengthI(bool meters, Scale* scale) {
    return ((int)((getLengthF(meters,scale)+0.5f)));
}

/**
 * Gets the actual length of the Seciton in mm without any scaling
 */
/*public*/ int Section::getActualLength()
{
 if (initializationNeeded) {
     initializeBlocks();
 }
 int len = 0;
 foreach (Block* b, *mBlockEntries)
 {
     len = len + ((int) b->getLengthMm());
 }
 return len;
}
/**
 * Get Block by its Sequence number in the Block list
 *  Blocks are numbered 0 to size-1;
 */
/*public*/ Block* Section::getBlockBySequenceNumber (int seqNumber) {
    if (initializationNeeded) initializeBlocks();
    if ( (seqNumber<mBlockEntries->size()) && (seqNumber>=0) )
        return mBlockEntries->at(seqNumber);
    return nullptr;
}
/**
 * Get the sequence number of a Block
 * Returns -1 if Block is not in the Section
 */
/*public*/ int Section::getBlockSequenceNumber(Block* b) {
    for (int i = 0; i<mBlockEntries->size(); i++) {
        if (b==mBlockEntries->at(i)) return i;
    }
    return -1;
}
/**
 * Remove all Blocks, Block Listeners,  and Entry Points
 */
/*public*/ void Section::removeAllBlocksFromSection () {
    for (int i = mBlockEntries->size();i>0;i--) {
        Block* b = mBlockEntries->at(i-1);
        if (b!=nullptr) {
            b->removePropertyChangeListener(mBlockListeners->at(i-1));
        }
        mBlockListeners->removeAt(i-1);
        mBlockEntries->removeAt(i-1);
    }
    for (int i = mForwardEntryPoints->size();i>0;i--) {
        mForwardEntryPoints->remove(i-1);
    }
    for (int i = mReverseEntryPoints->size();i>0;i--) {
        mReverseEntryPoints->remove(i-1);
    }
    initializationNeeded = false;
}
/**
 * Gets Blocks in order
 *	If state is FREE or FORWARD, returns Blocks in forward order
 *  If state is REVERSE, returns Blocks in reverse order
 *	First call getEntryBlock, then call getNextBlock until nullptr is returned.
 */
/*public*/ Block* Section::getEntryBlock() {
    if (initializationNeeded) initializeBlocks();
    if (mBlockEntries->size() <=0) return nullptr;
    if (mState==REVERSE) blockIndex=mBlockEntries->size();
    else blockIndex = 1;
    return mBlockEntries->at(blockIndex-1);
}
/*public*/ Block* Section::getNextBlock() {
    if (initializationNeeded) initializeBlocks();
    if (mState==REVERSE) blockIndex --;
    else blockIndex ++;
    if ( (blockIndex>mBlockEntries->size()) || (blockIndex<=0) ) return nullptr;
    return mBlockEntries->at(blockIndex-1);
}
/*public*/ bool Section::containsBlock(Block* b) {
    for (int i = 0; i<mBlockEntries->size(); i++) {
        if (b == mBlockEntries->at(i)) return true;
    }
    return false;
}
/*public*/ bool Section::connectsToBlock(Block* b) {
    EntryPoint* ep = nullptr;
    for (int i = 0; i<mForwardEntryPoints->size(); i++) {
        ep = mForwardEntryPoints->at(i);
        if (ep->getFromBlock()==b) return true;
    }
    for (int i = 0; i<mReverseEntryPoints->size(); i++) {
        ep = mReverseEntryPoints->at(i);
        if (ep->getFromBlock()==b) return true;
    }
    return false;
}

/**
 * Access methods for beginning and ending block names
 */
/*public*/ QString Section::getBeginBlockName() {
 if (initializationNeeded) {
     initializeBlocks();
 }
 if (mFirstBlock == nullptr) {
     return "unknown";
 }
 return mFirstBlock->getDisplayName();
}

/*public*/ QString Section::getEndBlockName() {
 if (initializationNeeded) {
     initializeBlocks();
 }
 if (mLastBlock == nullptr) {
     return "unknown";
 }
 return mLastBlock->getDisplayName();
}

/**
 * Access methods for EntryPoints within the Section
 */
/*public*/ void Section::addToForwardList(EntryPoint* ep) {
    if (ep!=nullptr) mForwardEntryPoints->append(ep);
}
/*public*/ void Section::addToReverseList(EntryPoint* ep) {
    if (ep!=nullptr) mReverseEntryPoints->append(ep);
}
/*public*/ void Section::removeEntryPoint(EntryPoint* ep) {
    for (int i = mForwardEntryPoints->size();i>0;i--) {
        if (mForwardEntryPoints->at(i-1)== ep)
            mForwardEntryPoints->remove(i-1);
    }
    for (int i = mReverseEntryPoints->size();i>0;i--) {
        if (mReverseEntryPoints->at(i-1)== ep)
            mReverseEntryPoints->remove(i-1);
    }
}
/*public*/ QList<EntryPoint*>* Section::getForwardEntryPointList()
{
 QList<EntryPoint*>* list = new QList<EntryPoint*>();
 for (int i = 0; i<mForwardEntryPoints->size(); i++)
 {
  list->append(mForwardEntryPoints->at(i));
 }
 return list;
}
/*public*/ QList<EntryPoint*>* Section::getReverseEntryPointList() {
    QList<EntryPoint*>* list = new QList<EntryPoint*>();
    for (int i = 0; i<mReverseEntryPoints->size(); i++) {
        list->append(mReverseEntryPoints->at(i));
    }
    return list;
}
/*public*/ QList<EntryPoint*>* Section::getEntryPointList() {
    QList<EntryPoint*>* list = new QList<EntryPoint*>();
    for (int i = 0; i<mForwardEntryPoints->size(); i++) {
        list->append(mForwardEntryPoints->at(i));
    }
    for (int j = 0; j<mReverseEntryPoints->size(); j++) {
        list->append(mReverseEntryPoints->at(j));
    }
    return list;
}
/*public*/ bool Section::isForwardEntryPoint(EntryPoint* ep) {
    for (int i = 0; i<mForwardEntryPoints->size(); i++) {
        if (ep == mForwardEntryPoints->at(i)) return true;
    }
    return false;
}
/*public*/ bool Section::isReverseEntryPoint(EntryPoint* ep) {
    for (int i = 0; i<mReverseEntryPoints->size(); i++) {
        if (ep == mReverseEntryPoints->at(i)) return true;
    }
    return false;
}
/**
 * Returns the EntryPoint for entry from specified Section for travel in specified direction
 *   Returns 'nullptr' if not found.
 */
/*public*/ EntryPoint* Section::getEntryPointFromSection(Section* s, int dir) {
    EntryPoint* ep = nullptr;
    if (dir == FORWARD) {
        for (int i = 0; i<mForwardEntryPoints->size(); i++) {
            ep = mForwardEntryPoints->at(i);
            if (s->containsBlock(ep->getFromBlock())) return ep;
        }
    }
    else if (dir == REVERSE) {
        for (int i = 0; i<mReverseEntryPoints->size(); i++) {
            ep = mReverseEntryPoints->at(i);
            if (s->containsBlock(ep->getFromBlock())) return ep;
        }
    }
    return nullptr;
}
/**
 * Returns the EntryPoint for exit to specified Section for travel in specified direction
 *   Returns 'nullptr' if not found.
 */
/*public*/ EntryPoint* Section::getExitPointToSection(Section* s, int dir) {
    EntryPoint* ep = nullptr;
    if (dir == REVERSE) {
        for (int i = 0; i<mForwardEntryPoints->size(); i++) {
            ep = mForwardEntryPoints->at(i);
            if (s->containsBlock(ep->getFromBlock())) return ep;
        }
    }
    else if (dir == FORWARD) {
        for (int i = 0; i<mReverseEntryPoints->size(); i++) {
            ep = mReverseEntryPoints->at(i);
            if (s->containsBlock(ep->getFromBlock())) return ep;
        }
    }
    return nullptr;
}
/**
 * Returns the EntryPoint for entry from specified Block for travel in specified direction
 *   Returns 'nullptr' if not found.
 */
/*public*/ EntryPoint* Section::getEntryPointFromBlock(Block* b, int dir) {
    EntryPoint* ep = nullptr;
    if (dir == FORWARD) {
        for (int i = 0; i<mForwardEntryPoints->size(); i++) {
            ep = mForwardEntryPoints->at(i);
            if (b == ep->getFromBlock()) return ep;
        }
    }
    else if (dir == REVERSE) {
        for (int i = 0; i<mReverseEntryPoints->size(); i++) {
            ep = mReverseEntryPoints->at(i);
            if (b == ep->getFromBlock()) return ep;
        }
    }
    return nullptr;
}
/**
 * Returns the EntryPoint for exit to specified Block for travel in specified direction
 *   Returns 'nullptr' if not found.
 */
/*public*/ EntryPoint* Section::getExitPointToBlock(Block* b, int dir) {
    EntryPoint* ep = nullptr;
    if (dir == REVERSE) {
        for (int i = 0; i<mForwardEntryPoints->size(); i++) {
            ep = mForwardEntryPoints->at(i);
            if (b == ep->getFromBlock()) return ep;
        }
    }
    else if (dir == FORWARD) {
        for (int i = 0; i<mReverseEntryPoints->size(); i++) {
            ep = mReverseEntryPoints->at(i);
            if (b == ep->getFromBlock()) return ep;
        }
    }
    return nullptr;
}
//#if LAYOUTS
/**
 * Returns EntryPoint::FORWARD if proceeding from the throat to the other end is movement in the forward
 *	direction.  Returns EntryPoint::REVERSE if proceeding from the throat to the other end is movement in
 *  the reverse direction.
 * Returns EntryPoint::UNKNOWN if cannot determine direction. This should only happen if blocks are not
 *	set up correctly--if all connections go to the same Block, or not all Blocks set.
 * An error message is logged if EntryPoint::UNKNOWN is returned.
 */
/*private*/ int Section::getDirectionStandardTurnout(LayoutTurnout* t, ConnectivityUtil* cUtil)
{
 LayoutBlock* aBlock = ((TrackSegment*)t->getConnectA())->getLayoutBlock();
 LayoutBlock* bBlock = ((TrackSegment*)t->getConnectB())->getLayoutBlock();
 LayoutBlock* cBlock = ((TrackSegment*)t->getConnectC())->getLayoutBlock();
 if ( (aBlock==nullptr) || (bBlock==nullptr) || (cBlock==nullptr) )
 {
  log.error("All blocks not assigned for track segments connecting to turnout - "+
                                    t->getTurnout()->getSystemName()+".");
  return EntryPoint::UNKNOWN;
 }

 Block* exBlock = checkDualDirection(aBlock,bBlock,cBlock);
 if ( (exBlock!=nullptr) || ( (aBlock==bBlock) && (aBlock==cBlock) ) )
 {
  // using Entry Points directly will lead to a problem, try following track - first from A following B
  int dir = EntryPoint::UNKNOWN;
  Block* tBlock = nullptr;
  TrackNode* tn = new TrackNode(t, LayoutEditor::TURNOUT_A, (TrackSegment*)t->getConnectA(),false, Turnout::CLOSED);
  while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) )
  {
   tn = cUtil->getNextNode(tn, 0);
   tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock);
  }
  if (tBlock==nullptr)
  {
   // try from A following C
   tn = new TrackNode(t, LayoutEditor::TURNOUT_A, (TrackSegment*)t->getConnectA(), false, Turnout::THROWN);
   while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) )
   {
    tn = cUtil->getNextNode(tn, 0);
    tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock);
   }
  }
  if (tBlock!=nullptr)
  {
   LayoutBlock* lb =(LayoutBlock*) static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
   if (lb!=nullptr) dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, lb);
  }
  if (dir == EntryPoint::UNKNOWN)
  {
   // try from B following A
   tBlock = nullptr;
   tn = new TrackNode(t, LayoutEditor::TURNOUT_B, (TrackSegment*)t->getConnectB(),
                                    false, Turnout::CLOSED);
   while ( (tBlock==nullptr) && (tn!=nullptr && (!tn->reachedEndOfTrack())) )
   {
    tn = cUtil->getNextNode(tn, 0);
    tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock);
   }
   if (tBlock!=nullptr)
   {
    LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
    if (lb!=nullptr) dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, lb);
   }
  }
  if (dir == EntryPoint::UNKNOWN)
  {
    log.error("Block definition ambiguity - cannot determine direction of Turnout "+
                        t->getTurnout()->getSystemName()+" in Section "+getSystemName()+".");
  }
  return dir;
 }
 if ( (aBlock!=bBlock) && containsBlock(aBlock->getBlock()) && containsBlock(bBlock->getBlock()) )
 {
  // both blocks are different, but are in this Section
  if (getBlockSequenceNumber(aBlock->getBlock()) < getBlockSequenceNumber(bBlock->getBlock()))
  {
   return EntryPoint::FORWARD;
  }
   else
  {
   return EntryPoint::REVERSE;
  }
 }
 else if ( (aBlock!=cBlock) && containsBlock(aBlock->getBlock()) && containsBlock(cBlock->getBlock()) )
 {
  // both blocks are different, but are in this Section
  if (getBlockSequenceNumber(aBlock->getBlock()) < getBlockSequenceNumber(cBlock->getBlock()))
  {
   return EntryPoint::FORWARD;
  }
  else
  {
   return EntryPoint::REVERSE;
  }
 }
 LayoutBlock* tBlock = t->getLayoutBlock();
 if (tBlock==nullptr)
 {
  log.error("Block not assigned for turnout "+t->getTurnout()->getSystemName());
  return EntryPoint::UNKNOWN;
 }
 if ( containsBlock(aBlock->getBlock()) && (!containsBlock(bBlock->getBlock())) )
 {
  // aBlock is in Section, bBlock is not
  int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, bBlock);
  if (dir!=EntryPoint::UNKNOWN) return dir;
  if ( (tBlock!=bBlock) && (!containsBlock(tBlock->getBlock())) )
  {
   dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, tBlock);
   if (dir!=EntryPoint::UNKNOWN) return dir;
  }
 }
 if ( containsBlock(aBlock->getBlock()) && (!containsBlock(cBlock->getBlock())) )
 {
  // aBlock is in Section, cBlock is not
  int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, cBlock);
  if (dir!=EntryPoint::UNKNOWN) return dir;
  if ( (tBlock!=cBlock) && (!containsBlock(tBlock->getBlock())) )
  {
   dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, tBlock);
   if (dir!=EntryPoint::UNKNOWN) return dir;
  }
 }
 if ( (containsBlock(bBlock->getBlock()) || containsBlock(cBlock->getBlock())) &&
                                            (!containsBlock(aBlock->getBlock())) )
 {
  // bBlock or cBlock is in Section, aBlock is not
  int dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, aBlock);
  if (dir!=EntryPoint::UNKNOWN) return dir;
  if ( (tBlock!=aBlock) && (!containsBlock(tBlock->getBlock())) )
  {
   dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, tBlock);
   if (dir!=EntryPoint::UNKNOWN) return dir;
  }
 }
 // should never get here
 log.error("Unexpected error in getDirectionStandardTurnout when working with turnout "+
                        t->getTurnout()->getSystemName());
 return EntryPoint::UNKNOWN;
}

/**
 * Returns EntryPoint::FORWARD if proceeding from A to B (or D to C) is movement in the forward
 *	direction.  Returns EntryPoint::REVERSE if proceeding from A to B (or D to C)  is movement in
 *  the reverse direction.
 * Returns EntryPoint::UNKNOWN if cannot determine direction. This should only happen if blocks are not
 *	set up correctly--if all connections go to the same Block, or not all Blocks set.
 * An error message is logged if EntryPoint::UNKNOWN is returned.
 */
/*private*/ int Section::getDirectionXoverTurnout(LayoutTurnout* t, ConnectivityUtil* cUtil) {
    LayoutBlock* aBlock = ((TrackSegment*)t->getConnectA())->getLayoutBlock();
    LayoutBlock* bBlock = ((TrackSegment*)t->getConnectB())->getLayoutBlock();
    LayoutBlock* cBlock = ((TrackSegment*)t->getConnectC())->getLayoutBlock();
    LayoutBlock* dBlock = ((TrackSegment*)t->getConnectD())->getLayoutBlock();
    if ( (aBlock==nullptr) || (bBlock==nullptr) || (cBlock==nullptr) || (dBlock==nullptr) ) {
        log.error("All blocks not assigned for track segments connecting to crossover turnout - "+
                                    t->getTurnout()->getSystemName()+".");
        return EntryPoint::UNKNOWN;
    }
    if ( (aBlock==bBlock) && (aBlock==cBlock) && (aBlock==dBlock) ) {
        log.error("Block setup problem - All track segments connecting to crossover turnout - "+
                        t->getTurnout()->getSystemName()+" are assigned to the same Block::");
        return EntryPoint::UNKNOWN;
    }
    if ( (containsBlock(aBlock->getBlock())) || (containsBlock(bBlock->getBlock())) ) {
        LayoutBlock* exBlock = nullptr;
        if (aBlock==bBlock) {
            if ( (t->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) && (cBlock==dBlock) ) exBlock = cBlock;
        }
        if (exBlock!=nullptr) {
            // set direction by tracking from a or b
            int dir = EntryPoint::UNKNOWN;
            Block* tBlock = nullptr;
            TrackNode* tn = new TrackNode(t, LayoutEditor::TURNOUT_A, (TrackSegment*)t->getConnectA(), false, Turnout::CLOSED);
            while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
                tn = cUtil->getNextNode(tn, 0);
                tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock->getBlock());
            }
            if (tBlock!=nullptr) {
                LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
                if (lb!=nullptr) dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, lb);
            }
            else {
                tn = new TrackNode(t, LayoutEditor::TURNOUT_B, (TrackSegment*)t->getConnectB(),
                                    false, Turnout::CLOSED);
                while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
                    tn = cUtil->getNextNode(tn, 0);
                    tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock->getBlock());
                }
                if (tBlock!=nullptr) {
                    LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
                    if (lb!=nullptr) dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, lb);
                }
            }
            if (dir == EntryPoint::UNKNOWN) {
                log.error("Block definition ambiguity - cannot determine direction of crossover Turnout "+
                        t->getTurnout()->getSystemName()+" in Section "+getSystemName()+".");
            }
            return dir;
        }
        if ( (aBlock!=bBlock) && containsBlock(aBlock->getBlock()) && containsBlock(bBlock->getBlock()) ) {
            if (getBlockSequenceNumber(aBlock->getBlock()) < getBlockSequenceNumber(bBlock->getBlock())) {
                return EntryPoint::FORWARD;
            }
            else {
                return EntryPoint::REVERSE;
            }
        }
        if ( containsBlock(aBlock->getBlock()) && (!containsBlock(bBlock->getBlock())) ) {
            int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, bBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        if ( containsBlock(bBlock->getBlock()) && (!containsBlock(aBlock->getBlock())) ) {
            int dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, aBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        if ( (t->getTurnoutType()!=LayoutTurnout::LH_XOVER) && containsBlock(aBlock->getBlock()) &&
                                                (!containsBlock(cBlock->getBlock())) ) {
            int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, cBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        if ( (t->getTurnoutType()!=LayoutTurnout::RH_XOVER) && containsBlock(bBlock->getBlock()) &&
                                                (!containsBlock(dBlock->getBlock())) ) {
            int dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, dBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
    }
    if ( (containsBlock(dBlock->getBlock())) || (containsBlock(cBlock->getBlock())) ) {
        LayoutBlock* exBlock = nullptr;
        if (dBlock==cBlock) {
            if ( (t->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) && (bBlock==aBlock) ) exBlock = aBlock;
        }
        if (exBlock!=nullptr) {
            // set direction by tracking from c or d
            int dir = EntryPoint::UNKNOWN;
            Block* tBlock = nullptr;
            TrackNode* tn = new TrackNode(t, LayoutEditor::TURNOUT_D, (TrackSegment*)t->getConnectD(),  false, Turnout::CLOSED);
            while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
                tn = cUtil->getNextNode(tn, 0);
                tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock->getBlock());
            }
            if (tBlock!=nullptr) {
                LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
                if (lb!=nullptr) dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, lb);
            }
            else {
                tn = new TrackNode(t, LayoutEditor::TURNOUT_C, (TrackSegment*)t->getConnectC(),
                                    false, Turnout::CLOSED);
                while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
                    tn = cUtil->getNextNode(tn, 0);
                    tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock->getBlock());
                }
                if (tBlock!=nullptr) {
                    LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
                    if (lb!=nullptr) dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, lb);
                }
            }
            if (dir == EntryPoint::UNKNOWN) {
                log.error("Block definition ambiguity - cannot determine direction of crossover Turnout "+
                        t->getTurnout()->getSystemName()+" in Section "+getSystemName()+".");
            }
            return dir;
        }
        if ( (dBlock!=cBlock) && containsBlock(dBlock->getBlock()) && containsBlock(cBlock->getBlock()) ) {
            if (getBlockSequenceNumber(dBlock->getBlock()) < getBlockSequenceNumber(cBlock->getBlock())) {
                return EntryPoint::FORWARD;
            }
            else {
                return EntryPoint::REVERSE;
            }
        }
        if ( containsBlock(dBlock->getBlock()) && (!containsBlock(cBlock->getBlock())) ) {
            int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, cBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        if ( containsBlock(cBlock->getBlock()) && (!containsBlock(dBlock->getBlock())) ) {
            int dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, dBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        if ( (t->getTurnoutType()!=LayoutTurnout::RH_XOVER) && containsBlock(dBlock->getBlock()) &&
                                                (!containsBlock(bBlock->getBlock())) ) {
            int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, bBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        if ( (t->getTurnoutType()!=LayoutTurnout::LH_XOVER) && containsBlock(cBlock->getBlock()) &&
                                                (!containsBlock(aBlock->getBlock())) ) {
            int dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, aBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
    }
    return EntryPoint::UNKNOWN;
}
#if 1
/**
 * Returns EntryPoint::FORWARD if proceeding from A to C or D (or B to D or C) is movement in the forward
 *	direction.  Returns EntryPoint::REVERSE if proceeding from C or D to A (or D or C to B)  is movement in
 *  the reverse direction.
 * Returns EntryPoint::UNKNOWN if cannot determine direction. This should only happen if blocks are not
 *	set up correctly--if all connections go to the same Block, or not all Blocks set.
 * An error message is logged if EntryPoint::UNKNOWN is returned.
 */
/*private*/ int Section::getDirectionSlip(LayoutSlip* t, ConnectivityUtil* cUtil) {
    LayoutBlock* aBlock = ((TrackSegment*)t->getConnectA())->getLayoutBlock();
    LayoutBlock* bBlock = ((TrackSegment*)t->getConnectB())->getLayoutBlock();
    LayoutBlock* cBlock = ((TrackSegment*)t->getConnectC())->getLayoutBlock();
    LayoutBlock* dBlock = ((TrackSegment*)t->getConnectD())->getLayoutBlock();
    if ( (aBlock==nullptr) || (bBlock==nullptr) || (cBlock==nullptr) || (dBlock==nullptr) ) {
        log.error("All blocks not assigned for track segments connecting to crossover turnout - "+
                                    t->getTurnout()->getSystemName()+".");
        return EntryPoint::UNKNOWN;
    }
    if ( (aBlock==bBlock) && (aBlock==cBlock) && (aBlock==dBlock) ) {
        log.error("Block setup problem - All track segments connecting to crossover turnout - "+
                        t->getTurnout()->getSystemName()+" are assigned to the same Block::");
        return EntryPoint::UNKNOWN;
    }
    if ( (containsBlock(aBlock->getBlock())) || (containsBlock(cBlock->getBlock())) ) {
        LayoutBlock* exBlock = nullptr;
        if (aBlock==cBlock) {
            if ( (t->getTurnoutType()==LayoutTurnout::DOUBLE_SLIP) && (bBlock==dBlock) ) exBlock = bBlock;
        }
        if (exBlock!=nullptr) {
            // set direction by tracking from a or b
            int dir = EntryPoint::UNKNOWN;
            Block* tBlock = nullptr;
            TrackNode* tn = new TrackNode(t, LayoutEditor::SLIP_A, (TrackSegment*)t->getConnectA(),
                                    false, LayoutSlip::STATE_AC);
            while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
                tn = cUtil->getNextNode(tn, 0);
                tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock->getBlock());
            }
            if (tBlock!=nullptr) {
                LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
                if (lb!=nullptr) dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, lb);
            }
            else {
                tn = new TrackNode(t, LayoutEditor::SLIP_C, (TrackSegment*)t->getConnectC(),
                                    false, LayoutSlip::STATE_AC);
                while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
                    tn = cUtil->getNextNode(tn, 0);
                    tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock->getBlock());
                }
                if (tBlock!=nullptr) {
                    LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
                    if (lb!=nullptr) dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, lb);
                }
            }
            if (dir == EntryPoint::UNKNOWN) {
                log.error("Block definition ambiguity - cannot determine direction of crossover slip "+
                        t->getTurnout()->getSystemName()+" in Section "+getSystemName()+".");
            }
            return dir;
        }
        if ( (aBlock!=cBlock) && containsBlock(aBlock->getBlock()) && containsBlock(cBlock->getBlock()) ) {
            if (getBlockSequenceNumber(aBlock->getBlock()) < getBlockSequenceNumber(cBlock->getBlock())) {
                return EntryPoint::FORWARD;
            }
            else {
                return EntryPoint::REVERSE;
            }
        }
        if ( containsBlock(aBlock->getBlock()) && (!containsBlock(cBlock->getBlock())) ) {
            int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, cBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        if ( containsBlock(cBlock->getBlock()) && (!containsBlock(aBlock->getBlock())) ) {
            int dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, aBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, dBlock);
        if (dir!=EntryPoint::UNKNOWN) return dir;
    }

    if ( (containsBlock(dBlock->getBlock())) || (containsBlock(bBlock->getBlock())) ) {
        LayoutBlock* exBlock = nullptr;
        if (dBlock==bBlock) {
            if ( (t->getTurnoutType()==LayoutTurnout::DOUBLE_SLIP) && (cBlock==aBlock) ) exBlock = aBlock;
        }
        if (exBlock!=nullptr) {
            // set direction by tracking from c or d
            int dir = EntryPoint::UNKNOWN;
            Block* tBlock = nullptr;
            TrackNode* tn = new TrackNode(t, LayoutEditor::SLIP_D, (TrackSegment*)t->getConnectD(),
                                    false, LayoutSlip::STATE_BD);
            while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
                tn = cUtil->getNextNode(tn, 0);
                tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock->getBlock());
            }
            if (tBlock!=nullptr) {
                LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
                if (lb!=nullptr) dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, lb);
            }
            else {
                tn = new TrackNode(t, LayoutEditor::TURNOUT_B, (TrackSegment*)t->getConnectB(),
                                    false, LayoutSlip::STATE_BD);
                while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
                    tn = cUtil->getNextNode(tn, 0);
                    tBlock = cUtil->getExitBlockForTrackNode(tn, exBlock->getBlock());
                }
                if (tBlock!=nullptr) {
                    LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(tBlock->getUserName());
                    if (lb!=nullptr) dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, lb);
                }
            }
            if (dir == EntryPoint::UNKNOWN) {
                log.error("Block definition ambiguity - cannot determine direction of slip "+
                        t->getTurnout()->getSystemName()+" in Section "+getSystemName()+".");
            }
            return dir;
        }
        if ( (dBlock!=bBlock) && containsBlock(dBlock->getBlock()) && containsBlock(bBlock->getBlock()) ) {
            if (getBlockSequenceNumber(dBlock->getBlock()) < getBlockSequenceNumber(bBlock->getBlock())) {
                return EntryPoint::FORWARD;
            }
            else {
                return EntryPoint::REVERSE;
            }
        }
        if ( containsBlock(dBlock->getBlock()) && (!containsBlock(bBlock->getBlock())) ) {
            int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, bBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        if ( containsBlock(bBlock->getBlock()) && (!containsBlock(dBlock->getBlock())) ) {
            int dir = checkLists(mForwardEntryPoints, mReverseEntryPoints, dBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
        if(t->getTurnoutType()==LayoutTurnout::DOUBLE_SLIP){
            int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, aBlock);
            if (dir!=EntryPoint::UNKNOWN) return dir;
        }
    }
    //If all else fails the slip must be in a block of its own so we shall work it out from there.
    if(t->getLayoutBlock()!=aBlock){
        //Block is not the same as that connected to A
        int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, aBlock);
        if(dir!=EntryPoint::UNKNOWN){
            return dir;
        }
    }
    if (t->getLayoutBlock()!=bBlock){
        //Block is not the same as that connected to B
        int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, bBlock);
        if(dir!=EntryPoint::UNKNOWN){
            return dir;
        }
    }
    if (t->getLayoutBlock()!=cBlock){
        //Block is not the same as that connected to C
        int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, cBlock);
        if(dir!=EntryPoint::UNKNOWN){
            return dir;
        }
    }
    if (t->getLayoutBlock()!=dBlock){
        //Block is not the same as that connected to D
        int dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, dBlock);
        if(dir!=EntryPoint::UNKNOWN){
            return dir;
        }
    }
    return EntryPoint::UNKNOWN;
}
#endif
/*private*/ bool Section::placeSensorInCrossover(QString b1Name, QString b2Name, QString c1Name, QString c2Name,  int direction, ConnectivityUtil* cUtil)
{
 #if 1 // TODO:
    SignalHead* b1Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(b1Name);
    SignalHead* b2Head = nullptr;
    SignalHead* c1Head = nullptr;
    SignalHead* c2Head = nullptr;
    bool success = true;
    if ( (b2Name!=nullptr) && (b2Name!=("")) ) {
        b2Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(b2Name);
    }
    if ( (c1Name!=nullptr) && (c1Name!=("")) ) {
        c1Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(c1Name);
    }
    if ( (c2Name!=nullptr) && (c2Name!=("")) ) {
        c2Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(c2Name);
    }
    if (b2Head!=nullptr) {
        if (!checkDirectionSensor(b1Head, direction, ConnectivityUtil::OVERALL, cUtil)) success = false;
    }
    else {
        if (!checkDirectionSensor(b1Head, direction, ConnectivityUtil::CONTINUING, cUtil)) success = false;
    }
    if (c2Head!=nullptr) {
        if (!checkDirectionSensor(c2Head, direction, ConnectivityUtil::OVERALL, cUtil)) success = false;
    }
    else if (c1Head!=nullptr) {
        if (!checkDirectionSensor(c1Head, direction, ConnectivityUtil::DIVERGING, cUtil)) success = false;
    }
    return success;
#else
 return false;
#endif
    }
/*private*/ int Section::checkLists (QVector<EntryPoint*>* forwardList, QVector<EntryPoint*>* reverseList, LayoutBlock* lBlock) {
    for (int i = 0; i<forwardList->size(); i++) {
        if (forwardList->at(i)->getFromBlock() == lBlock->getBlock()) {
            return EntryPoint::FORWARD;
        }
    }
    for (int i = 0; i<reverseList->size(); i++) {
        if (reverseList->at(i)->getFromBlock() == lBlock->getBlock() ) {
            return EntryPoint::REVERSE;
        }
    }
    return EntryPoint::UNKNOWN;
}
/*private*/ Block* Section::checkDualDirection(LayoutBlock* aBlock, LayoutBlock* bBlock, LayoutBlock* cBlock) {
    for (int i = 0; i<mForwardEntryPoints->size(); i++) {
        Block* b = mForwardEntryPoints->at(i)->getFromBlock();
        for (int j = 0; j<mReverseEntryPoints->size(); j++) {
            if (mReverseEntryPoints->at(j)->getFromBlock() == b ) {
                // possible dual direction
                if (aBlock->getBlock() == b) return b;
                else if (bBlock->getBlock() == b) return b;
                else if ( (cBlock->getBlock() == b) && (aBlock==bBlock) ) return b;
            }
        }
    }
    return nullptr;
}

/**
 * Returns the direction for proceeding from LayoutBlock b to LayoutBlock a.  LayoutBlock a must be
 *		in the Section. LayoutBlock b may be in this Section or may be an Entry Point to the Section.
 */
/*private*/ int Section::getDirectionForBlocks(LayoutBlock* a, LayoutBlock* b) {
    if (containsBlock(b->getBlock())) {
        // both blocks are within this Section
        if (getBlockSequenceNumber(a->getBlock()) > getBlockSequenceNumber(b->getBlock())) {
            return EntryPoint::FORWARD;
        }
        else {
            return EntryPoint::REVERSE;
        }
    }
    // bBlock must be an entry point
    for (int i = 0; i<mForwardEntryPoints->size(); i++) {
        if (mForwardEntryPoints->at(i)->getFromBlock() == b->getBlock()) {
            return EntryPoint::FORWARD;
        }
    }
    for (int j = 0; j<mReverseEntryPoints->size(); j++) {
        if (mReverseEntryPoints->at(j)->getFromBlock() == b->getBlock()) {
            return EntryPoint::REVERSE;
        }
    }
    // should never get here
    log.error("Unexpected error in getDirectionForBlocks when working with LevelCrossing in Section "+
                        getSystemName());
    return EntryPoint::UNKNOWN;
}
/*
 * Returns 'true' if successfully checked direction sensor by follow connectivity from specified
 *		track node.  Returns 'false' if an error occurred.
 */
/*private*/ bool Section::setDirectionSensorByConnectivity(TrackNode* tNode, TrackNode* altNode, SignalHead* sh, Block* cBlock, ConnectivityUtil* cUtil) {
    bool successful = false;
    TrackNode* tn = tNode;
    if ( (tn!=nullptr) && (sh!=nullptr) ) {
        Block* tBlock = nullptr;
        LayoutBlock* lb = nullptr;
        int dir = EntryPoint::UNKNOWN;
        while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
            tn = cUtil->getNextNode(tn, 0);
            tBlock = cUtil->getExitBlockForTrackNode(tn, nullptr);
        }
        if (tBlock!=nullptr) {
            lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->
                                                        getByUserName(tBlock->getUserName());
            if (lb!=nullptr)
                dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, lb);
        }
        else {
            tn = altNode;
            while ( (tBlock==nullptr) && (tn!=nullptr) && (!tn->reachedEndOfTrack()) ) {
                tn = cUtil->getNextNode(tn, 0);
                tBlock = cUtil->getExitBlockForTrackNode(tn, nullptr);
            }
            if (tBlock!=nullptr) {
                lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->
                                                        getByUserName(tBlock->getUserName());
                if (lb!=nullptr) {
                    dir = checkLists(mReverseEntryPoints, mForwardEntryPoints, lb);
                    if (dir == EntryPoint::REVERSE) dir = EntryPoint::FORWARD;
                    else if (dir == EntryPoint::FORWARD) dir = EntryPoint::REVERSE;
                }
            }
        }
        if (dir!=EntryPoint::UNKNOWN) {
            if (checkDirectionSensor(sh, dir, ConnectivityUtil::OVERALL, cUtil)) successful = true;
        }
        else {
            log.error("Trouble following track in Block "+
                                    cBlock->getSystemName()+" in Section "+getSystemName()+".");
        }
    }
    return successful;
}
#if 1
/**
 * Places direction sensors in SSL for all Signal Heads in this Section if the Sensors
 *		are not already present in the SSL.
 * Only anchor point block boundaries that have assigned signals are considered.
 * Only turnouts that have assigned signals are considered.
 * Only level crossings that have assigned signals are considered.
 * Turnouts and anchor points without signals are counted, and reported in warning messages
 *		during this procedure, if there are any missing signals.
 * If this method has trouble, an error message is placed in the log describing the trouble.
 * If a direction sensor has not been defined for this Section, a message to that
 *		effect is issued to the log, and an error count of 1 is returned.
 * Returns an an error count of 0, if no errors occurred.
 */
/*public*/ int Section::placeDirectionSensors(LayoutEditor* panel)
{
 int missingSignalsBB = 0;
 int missingSignalsTurnouts = 0;
 int missingSignalsLevelXings = 0;
 int errorCount = 0;
 if (panel==nullptr)
 {
  log.error("Null Layout Editor panel on call to 'placeDirectionSensors'");
  return 1;
 }
 if (initializationNeeded) initializeBlocks();
 if ( (mForwardBlockingSensorName==nullptr) || (mForwardBlockingSensorName==("")) ||
            (mReverseBlockingSensorName==nullptr) || (mReverseBlockingSensorName==("")) )
 {
  log.error("Missing direction sensor in Section "+getSystemName());
  return 1;
 }
 LayoutBlockManager* layoutBlockManager = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
 ConnectivityUtil* cUtil = panel->getConnectivityUtil();
 for (int i = 0; i<mBlockEntries->size(); i++)
 {
  Block* cBlock = mBlockEntries->at(i);
  LayoutBlock* lBlock = (LayoutBlock*)layoutBlockManager->getByUserName(cBlock->getUserName());
  QVector<PositionablePoint*>* anchorList = cUtil->getAnchorBoundariesThisBlock(cBlock);
  for (int j = 0; j<anchorList->size(); j++)
  {
   PositionablePoint* p = anchorList->at(j);
   if ( (p->getEastBoundSignal()!=nullptr) && (p->getWestBoundSignal()!=nullptr) &&
                    (p->getEastBoundSignal()!=("")) && (p->getWestBoundSignal()!=("")) )
   {
    // have a signalled block boundary
    SignalHead* sh = cUtil->getSignalHeadAtAnchor(p, cBlock, false);
    if (sh==nullptr)
    {
     log.warn("Unexpected missing signal head at boundary of Block "+cBlock->getUserName());
     errorCount ++;
    }
    else
    {
     int direction = cUtil->getDirectionFromAnchor(mForwardEntryPoints,
                mReverseEntryPoints, p);
     if (direction==EntryPoint::UNKNOWN)
     {
      // anchor is at a Block boundary within the Section
      sh = cUtil->getSignalHeadAtAnchor(p, cBlock, true);
      Block* otherBlock = ((p->getConnect1())->getLayoutBlock())->getBlock();
      if (otherBlock==cBlock) otherBlock = ((p->getConnect2())->getLayoutBlock())->getBlock();
      if (getBlockSequenceNumber(cBlock) < getBlockSequenceNumber(otherBlock)) {
            direction = EntryPoint::FORWARD;
     }
     else
     {
      direction = EntryPoint::REVERSE;
     }
    }
    if (!checkDirectionSensor(sh, direction, ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
  }
  }
  else
  {
   errorCount++;
   missingSignalsBB ++;
  }
 }
 QVector<LevelXing*>* xingList = cUtil->getLevelCrossingsThisBlock(cBlock);
 for (int k = 0; k<xingList->size(); k++)
 {
  LevelXing* x = xingList->at(k);
  LayoutBlock* alBlock = ((TrackSegment*)x->getConnectA())->getLayoutBlock();
  LayoutBlock* blBlock = ((TrackSegment*)x->getConnectB())->getLayoutBlock();
  LayoutBlock* clBlock = ((TrackSegment*)x->getConnectC())->getLayoutBlock();
  LayoutBlock* dlBlock = ((TrackSegment*)x->getConnectD())->getLayoutBlock();
  if (cUtil->isInternalLevelXingAC(x, cBlock))
  {
         // have an internal AC level crossing - is it signaled?
         if ( ((x->getSignalAName()!=nullptr) && (x->getSignalAName()!=(""))) ||
                 ((x->getSignalCName()!=nullptr) && (x->getSignalCName()!=(""))) ) {
             // have a signaled AC level crossing internal to this block
             if ( (x->getSignalAName()!=nullptr) && (x->getSignalAName()!=("")) ) {
                 // there is a signal at A in the level crossing
                 TrackNode* tn = new TrackNode(x, LayoutEditor::LEVEL_XING_A,
                                     (TrackSegment*)x->getConnectA(), false, 0);
                 TrackNode* altNode = new TrackNode(x, LayoutEditor::LEVEL_XING_C,
                                     (TrackSegment*)x->getConnectC(), false, 0);
                 SignalHead* sh = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                 x->getSignalAName());
                 if (!setDirectionSensorByConnectivity(tn, altNode, sh, cBlock, cUtil)) errorCount ++;
             }
             if ( (x->getSignalCName()!=nullptr) && (x->getSignalCName()!=("")) ) {
                 // there is a signal at C in the level crossing
                 TrackNode* tn = new TrackNode(x, LayoutEditor::LEVEL_XING_C,
                                     (TrackSegment*)x->getConnectC(), false, 0);
                 TrackNode* altNode = new TrackNode(x, LayoutEditor::LEVEL_XING_A,
                                     (TrackSegment*)x->getConnectA(), false, 0);
                 SignalHead* sh = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                 x->getSignalCName());
                 if (!setDirectionSensorByConnectivity(tn, altNode, sh, cBlock, cUtil)) errorCount ++;
             }
         }
     }
     else if (alBlock == lBlock) {
         // have a level crossing with AC spanning a block boundary, with A in this Block
         int direction = getDirectionForBlocks(alBlock, clBlock);
         if (direction != EntryPoint::UNKNOWN) {
             if ( (x->getSignalCName()!=nullptr) && (x->getSignalCName()!=("")) ) {
                 SignalHead* sh = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                 x->getSignalCName());
                 if (!checkDirectionSensor(sh, direction, ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
             }
         }
         else {
             errorCount++;
         }
     }
     else if (clBlock == lBlock) {
         // have a level crossing with AC spanning a block boundary, with C in this Block
         int direction = getDirectionForBlocks(clBlock, alBlock);
         if (direction != EntryPoint::UNKNOWN) {
             if ( (x->getSignalAName()!=nullptr) && (x->getSignalAName()!=("")) ) {
                 SignalHead* sh = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                 x->getSignalAName());
                 if (!checkDirectionSensor(sh, direction, ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
             }
         }
         else {
             errorCount++;
         }
     }
     if (cUtil->isInternalLevelXingBD(x, cBlock)) {
         // have an internal BD level crossing - is it signaled?
         if ( ((x->getSignalBName()!=nullptr) && (x->getSignalBName()!=(""))) ||
                 ((x->getSignalDName()!=nullptr) && (x->getSignalDName()!=(""))) ) {
             // have a signaled BD level crossing internal to this block
             if ( (x->getSignalBName()!=nullptr) && (x->getSignalBName()!=("")) ) {
                 // there is a signal at B in the level crossing
                 TrackNode* tn = new TrackNode(x, LayoutEditor::LEVEL_XING_B,
                                     (TrackSegment*)x->getConnectB(), false, 0);
                 TrackNode* altNode = new TrackNode(x, LayoutEditor::LEVEL_XING_D,
                                     (TrackSegment*)x->getConnectD(), false, 0);
                 SignalHead* sh = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                 x->getSignalBName());
                 if (!setDirectionSensorByConnectivity(tn, altNode, sh, cBlock, cUtil)) errorCount ++;
             }
             if ( (x->getSignalDName()!=nullptr) && (x->getSignalDName()!=("")) ) {
                 // there is a signal at C in the level crossing
                 TrackNode* tn = new TrackNode(x, LayoutEditor::LEVEL_XING_D,
                                     (TrackSegment*)x->getConnectD(), false, 0);
                 TrackNode* altNode = new TrackNode(x, LayoutEditor::LEVEL_XING_B,
                                     (TrackSegment*)x->getConnectB(), false, 0);
                 SignalHead* sh = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                 x->getSignalDName());
                 if (!setDirectionSensorByConnectivity(tn, altNode, sh, cBlock, cUtil)) errorCount ++;
             }
         }
     }
     else if (blBlock == lBlock) {
         // have a level crossing with BD spanning a block boundary, with B in this Block
         int direction = getDirectionForBlocks(blBlock, dlBlock);
         if (direction != EntryPoint::UNKNOWN) {
             if ( (x->getSignalDName()!=nullptr) && (x->getSignalDName()!=("")) ) {
                 SignalHead* sh = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                 x->getSignalDName());
                 if (!checkDirectionSensor(sh, direction, ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
             }
         }
         else {
             errorCount++;
         }
     }
     else if (dlBlock == lBlock) {
         // have a level crossing with BD spanning a block boundary, with D in this Block
         int direction = getDirectionForBlocks(dlBlock, blBlock);
         if (direction != EntryPoint::UNKNOWN) {
             if ( (x->getSignalBName()!=nullptr) && (x->getSignalBName()!=("")) ) {
                 SignalHead* sh = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                 x->getSignalBName());
                 if (!checkDirectionSensor(sh, direction, ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
             }
         }
         else {
             errorCount++;
         }
     }
     }
        QVector<LayoutTurnout*>* turnoutList = cUtil->getLayoutTurnoutsThisBlock(cBlock);
        for (int m = 0; m<turnoutList->size(); m++) {
            LayoutTurnout* t = turnoutList->at(m);
            if ( cUtil->layoutTurnoutHasRequiredSignals(t) ) {
                // have a signalled turnout
                if ( (t->getLinkType()==LayoutTurnout::NO_LINK) &&
                    ( (t->getTurnoutType()==LayoutTurnout::RH_TURNOUT) ||
                        (t->getTurnoutType()==LayoutTurnout::LH_TURNOUT) ||
                            (t->getTurnoutType()==LayoutTurnout::WYE_TURNOUT) ) ) {
                    // standard turnout - nothing special
                    // Note: direction is for proceeding from the throat to either other track
                    int direction = getDirectionStandardTurnout(t,cUtil);
                    int altDirection = EntryPoint::FORWARD;
                    if (direction == EntryPoint::FORWARD) altDirection = EntryPoint::REVERSE;
                    if (direction==EntryPoint::UNKNOWN) errorCount ++;
                    else {
                        SignalHead* aHead = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                        t->getSignalA1Name());
                        SignalHead* a2Head = nullptr;
                        QString a2Name = t->getSignalA2Name();
                        if ( (a2Name!=nullptr) && (a2Name!=("")) ) {
                            a2Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(a2Name);
                        }
                        SignalHead* bHead = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                        t->getSignalB1Name());
                        SignalHead* cHead = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                        t->getSignalC1Name());
                        if (t->getLayoutBlock()->getBlock()==cBlock) {
                            // turnout is in this block, set direction sensors on all signal heads
                            // Note: need allocation to traverse this turnout
                            if (!checkDirectionSensor(aHead, direction,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                            if (a2Head!=nullptr) {
                                if (!checkDirectionSensor(a2Head, direction,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                            }
                            if (!checkDirectionSensor(bHead, altDirection,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                            if (!checkDirectionSensor(cHead, altDirection,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                        }
                        else {
                            if (((TrackSegment*)t->getConnectA())->getLayoutBlock()->getBlock()==cBlock) {
                                // throat Track Segment is in this Block
                                if (!checkDirectionSensor(bHead, altDirection,
                                                    ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                if (!checkDirectionSensor(cHead, altDirection,
                                                    ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                            }
                            else if ( ( (t->getContinuingSense()==Turnout::CLOSED) &&
                                    (((TrackSegment*)t->getConnectB())->getLayoutBlock()->getBlock()==cBlock) ) ||
                                    ( (t->getContinuingSense()==Turnout::THROWN) &&
                                    (((TrackSegment*)t->getConnectC())->getLayoutBlock()->getBlock()==cBlock) )	) {
                                // continuing track segment is in this block, normal continuing sense - or -
                                //		diverging track segment is in this block, reverse continuing sense.
                                if (a2Head==nullptr) {
                                    // single head at throat
                                    if (!checkDirectionSensor(aHead, direction,
                                                ConnectivityUtil::CONTINUING, cUtil)) errorCount ++;
                                }
                                else {
                                    // two heads at throat
                                    if (!checkDirectionSensor(aHead, direction,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                }
                                if (!checkDirectionSensor(bHead, altDirection,
                                                    ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                            }
                            else if ( ( (t->getContinuingSense()==Turnout::CLOSED) &&
                                    (((TrackSegment*)t->getConnectC())->getLayoutBlock()->getBlock()==cBlock) ) ||
                                    ( (t->getContinuingSense()==Turnout::THROWN) &&
                                    (((TrackSegment*)t->getConnectB())->getLayoutBlock()->getBlock()==cBlock) )	) {
                                // diverging track segment is in this block, normal continuing sense - or -
                                //		continuing track segment is in this block, reverse continuing sense.
                                if (a2Head==nullptr) {
                                    // single head at throat
                                    if (!checkDirectionSensor(aHead, direction,
                                                ConnectivityUtil::DIVERGING, cUtil)) errorCount ++;
                                }
                                else {
                                    // two heads at throat
                                    if (!checkDirectionSensor(a2Head, direction,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                }
                                if (!checkDirectionSensor(cHead, altDirection,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                            }
                        }
                    }
                }
                else if (t->getLinkType()!=LayoutTurnout::NO_LINK) {
                    // special linked turnout
                    LayoutTurnout* tLinked = getLayoutTurnoutFromTurnoutName(t->getLinkedTurnoutName(),panel);
                    if (tLinked==nullptr) log.error("nullptr Layout Turnout linked to turnout "+t->getTurnout()->getSystemName());
                    else if (t->getLinkType()==LayoutTurnout::THROAT_TO_THROAT) {
                        SignalHead* b1Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                                            t->getSignalB1Name());
                        SignalHead* b2Head = nullptr;
                        QString hName = t->getSignalB2Name();
                        if ( (hName!=nullptr) && (hName!=("")) ) {
                            b2Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(hName);
                        }
                        SignalHead* c1Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                                            t->getSignalC1Name());
                        SignalHead* c2Head = nullptr;
                        hName = t->getSignalC2Name();
                        if ( (hName!=nullptr) && (hName!=("")) ) {
                            c2Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(hName);
                        }
                        int direction = getDirectionStandardTurnout(t,cUtil);
                        int altDirection = EntryPoint::FORWARD;
                        if (direction==EntryPoint::FORWARD) altDirection = EntryPoint::REVERSE;
                        if (direction!=EntryPoint::UNKNOWN)  {
                            if (t->getLayoutBlock()->getBlock()==cBlock) {
                                // turnout is in this block, set direction sensors on all signal heads
                                // Note: need allocation to traverse this turnout
                                if (!checkDirectionSensor(b1Head, altDirection,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                if (b2Head!=nullptr)
                                    if (!checkDirectionSensor(b2Head, altDirection,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                if (!checkDirectionSensor(c1Head, altDirection,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                if (c2Head!=nullptr)
                                    if (!checkDirectionSensor(c2Head, altDirection,
                                                ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                            }
                            else {
                                // turnout is not in this block, switch to heads of linked turnout
                                b1Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                                            tLinked->getSignalB1Name());
                                hName = tLinked->getSignalB2Name();
                                b2Head = nullptr;
                                if ( (hName!=nullptr) && (hName!=("")) ) {
                                    b2Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(hName);
                                }
                                c1Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                                            tLinked->getSignalC1Name());
                                c2Head = nullptr;
                                hName = tLinked->getSignalC2Name();
                                if ( (hName!=nullptr) && (hName!=("")) ) {
                                    c2Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(hName);
                                }
                                if ( ((t->getContinuingSense()==Turnout::CLOSED) &&
                                    (((TrackSegment*)t->getConnectB())->getLayoutBlock()->getBlock()==cBlock)) ||
                                        ((t->getContinuingSense()==Turnout::THROWN) &&
                                        (((TrackSegment*)t->getConnectC())->getLayoutBlock()->getBlock()==cBlock)) ) {
                                    // continuing track segment is in this block
                                    if (b2Head!=nullptr) {
                                        if (!checkDirectionSensor(b1Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                    }
                                    else {
                                        if (!checkDirectionSensor(b1Head, direction,
                                                        ConnectivityUtil::CONTINUING, cUtil)) errorCount ++;
                                    }
                                    if (c2Head!=nullptr) {
                                        if (!checkDirectionSensor(c1Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                    }
                                    else {
                                        if (!checkDirectionSensor(c1Head, direction,
                                                        ConnectivityUtil::CONTINUING, cUtil)) errorCount ++;
                                    }
                                }
                                else if ( ((t->getContinuingSense()==Turnout::CLOSED) &&
                                    (((TrackSegment*)t->getConnectC())->getLayoutBlock()->getBlock()==cBlock)) ||
                                        ((t->getContinuingSense()==Turnout::THROWN) &&
                                        (((TrackSegment*)t->getConnectB())->getLayoutBlock()->getBlock()==cBlock)) ) {
                                    // diverging track segment is in this block
                                    if (b2Head!=nullptr) {
                                        if (!checkDirectionSensor(b2Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                    }
                                    else {
                                        if (!checkDirectionSensor(b1Head, direction,
                                                        ConnectivityUtil::DIVERGING, cUtil)) errorCount ++;
                                    }
                                    if (c2Head!=nullptr) {
                                        if (!checkDirectionSensor(c2Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                    }
                                    else {
                                        if (!checkDirectionSensor(c1Head, direction,
                                                        ConnectivityUtil::DIVERGING, cUtil)) errorCount ++;
                                    }
                                }
                            }
                        }
                    }
                    else if (t->getLinkType()==LayoutTurnout::FIRST_3_WAY) {
                        SignalHead* a1Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                                            t->getSignalA1Name());
                        SignalHead* a2Head = nullptr;
                        QString hName = t->getSignalA2Name();
                        if ( (hName!=nullptr) && (hName!=("")) ) {
                            a2Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(hName);
                        }
                        SignalHead* a3Head = nullptr;
                        hName = t->getSignalA3Name();
                        if ( (hName!=nullptr) && (hName!=("")) ) {
                            a3Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(hName);
                        }
                        SignalHead* cHead = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                                            t->getSignalC1Name());
                        int direction = getDirectionStandardTurnout(t,cUtil);
                        int altDirection = EntryPoint::FORWARD;
                        if (direction==EntryPoint::FORWARD) altDirection = EntryPoint::REVERSE;
                        if (direction!=EntryPoint::UNKNOWN) {
                            if (t->getLayoutBlock()->getBlock()==cBlock) {
                                // turnout is in this block, set direction sensors on all signal heads
                                // Note: need allocation to traverse this turnout
                                if (!checkDirectionSensor(a1Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                if ( (a2Head!=nullptr) && (a3Head!=nullptr) ) {
                                    if (!checkDirectionSensor(a2Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                    if (!checkDirectionSensor(a3Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                }
                                if (!checkDirectionSensor(cHead, altDirection,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                            }
                            else {
                                // turnout is not in this block
                                if (((TrackSegment*)t->getConnectA())->getLayoutBlock()->getBlock()==cBlock) {
                                    // throat Track Segment is in this Block
                                    if (!checkDirectionSensor(cHead, altDirection,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                }
                                else if (((TrackSegment*)t->getConnectC())->getLayoutBlock()->getBlock()==cBlock) {
                                    // diverging track segment is in this Block
                                    if (a2Head!=nullptr) {
                                        if (!checkDirectionSensor(a2Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                    }
                                    else {
                                        if (!checkDirectionSensor(a1Head, direction,
                                                        ConnectivityUtil::DIVERGING, cUtil)) errorCount ++;
                                    }
                                }
                            }
                        }
                    }
                    else if (t->getLinkType()==LayoutTurnout::SECOND_3_WAY) {
                        SignalHead* bHead = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                                            t->getSignalB1Name());
                        SignalHead* cHead = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                                            t->getSignalC1Name());
                        SignalHead* a1Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(
                                                                        tLinked->getSignalA1Name());
                        SignalHead* a3Head = nullptr;
                        QString hName = tLinked->getSignalA3Name();
                        if ( (hName!=nullptr) && (hName!=("")) ) {
                            a3Head = ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(hName);
                        }
                        int direction = getDirectionStandardTurnout(t,cUtil);
                        int altDirection = EntryPoint::FORWARD;
                        if (direction==EntryPoint::FORWARD) altDirection = EntryPoint::REVERSE;
                        if (direction!=EntryPoint::UNKNOWN) {
                            if (t->getLayoutBlock()->getBlock()==cBlock) {
                                // turnout is in this block, set direction sensors on b and c signal heads
                                // Note: need allocation to traverse this turnout
                                if (!checkDirectionSensor(bHead, altDirection,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                if (!checkDirectionSensor(cHead, altDirection,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                            }
                            if (((TrackSegment*)t->getConnectC())->getLayoutBlock()->getBlock()==cBlock) {
                                // diverging track segment is in this Block
                                if (a3Head!=nullptr) {
                                    if (!checkDirectionSensor(a3Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                }
                                else {
                                    log.warn("Turnout "+tLinked->getTurnoutName()+" - SSL for head "+a1Head->getSystemName()+
                                        " cannot handle direction sensor for second diverging track.");
                                    errorCount ++;
                                }
                            }
                            else if (((TrackSegment*)t->getConnectB())->getLayoutBlock()->getBlock()==cBlock) {
                                // continuing track segment is in this Block
                                if (a3Head!=nullptr) {
                                    if (!checkDirectionSensor(a1Head, direction,
                                                        ConnectivityUtil::OVERALL, cUtil)) errorCount ++;
                                }
                                else {
                                    if (!checkDirectionSensor(a1Head, direction,
                                                        ConnectivityUtil::CONTINUING, cUtil)) errorCount ++;
                                }
                            }
                        }
                    }
                }
                else if ( (t->getTurnoutType()==LayoutTurnout::RH_XOVER) ||
                        (t->getTurnoutType()==LayoutTurnout::LH_XOVER) ||
                            (t->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ) {
                    // crossover turnout
                    // Note: direction is for proceeding from A to B (or D to C)
                    int direction = getDirectionXoverTurnout(t,cUtil);
                    int altDirection = EntryPoint::FORWARD;
                    if (direction==EntryPoint::FORWARD) altDirection = EntryPoint::REVERSE;
                    if (direction==EntryPoint::UNKNOWN) errorCount ++;
                    else {
                        if (((TrackSegment*)t->getConnectA())->getLayoutBlock()->getBlock()==cBlock) {
                            if ( (t->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
                                    (t->getTurnoutType()==LayoutTurnout::RH_XOVER) ) {
                                if (!placeSensorInCrossover(t->getSignalB1Name(),t->getSignalB2Name(),
                                        t->getSignalC1Name(),t->getSignalC2Name(),altDirection,cUtil)) errorCount ++;
                            }
                            else {
                                if (!placeSensorInCrossover(t->getSignalB1Name(),t->getSignalB2Name(),
                                        nullptr,nullptr,altDirection,cUtil)) errorCount ++;
                            }
                        }
                        if (((TrackSegment*)t->getConnectB())->getLayoutBlock()->getBlock()==cBlock) {
                            if ( (t->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
                                    (t->getTurnoutType()==LayoutTurnout::LH_XOVER) ) {
                                if (!placeSensorInCrossover(t->getSignalA1Name(),t->getSignalA2Name(),
                                        t->getSignalD1Name(),t->getSignalD2Name(),direction,cUtil)) errorCount ++;
                            }
                            else {
                                if (!placeSensorInCrossover(t->getSignalA1Name(),t->getSignalA2Name(),
                                        nullptr,nullptr,direction,cUtil)) errorCount ++;
                            }
                        }
                        if (((TrackSegment*)t->getConnectC())->getLayoutBlock()->getBlock()==cBlock) {
                            if ( (t->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
                                    (t->getTurnoutType()==LayoutTurnout::RH_XOVER) ) {
                                if (!placeSensorInCrossover(t->getSignalD1Name(),t->getSignalD2Name(),
                                        t->getSignalA1Name(),t->getSignalA2Name(),direction,cUtil)) errorCount ++;
                            }
                            else {
                                if (!placeSensorInCrossover(t->getSignalD1Name(),t->getSignalD2Name(),
                                        nullptr,nullptr,direction,cUtil)) errorCount ++;
                            }
                        }
                        if (((TrackSegment*)t->getConnectD())->getLayoutBlock()->getBlock()==cBlock) {
                            if ( (t->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
                                    (t->getTurnoutType()==LayoutTurnout::LH_XOVER) ) {
                                if (!placeSensorInCrossover(t->getSignalC1Name(),t->getSignalC2Name(),
                                        t->getSignalB1Name(),t->getSignalB2Name(),altDirection,cUtil)) errorCount ++;
                            }
                            else {
                                if (!placeSensorInCrossover(t->getSignalC1Name(),t->getSignalC2Name(),
                                        nullptr,nullptr,altDirection,cUtil)) errorCount ++;
                            }
                        }
                    }
                }
                else if (t->getTurnoutType()==LayoutTurnout::SINGLE_SLIP || t->getTurnoutType()==LayoutTurnout::DOUBLE_SLIP){
                    int direction = getDirectionSlip((LayoutSlip*)t,cUtil);
                    int altDirection = EntryPoint::FORWARD;
                    if (direction==EntryPoint::FORWARD) altDirection = EntryPoint::REVERSE;
                    if (direction==EntryPoint::UNKNOWN) errorCount++;
                    else {
                        if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalA1Name()), altDirection, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                        if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalA2Name()), altDirection, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                        if(t->getTurnoutType()==LayoutTurnout::SINGLE_SLIP){
                            if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalB1Name()), altDirection, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                        } else {
                            if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalB1Name()), altDirection, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                            if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalB2Name()), altDirection, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                        }
                        if(t->getTurnoutType()==LayoutTurnout::SINGLE_SLIP){
                            if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalC1Name()), direction, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                        } else {
                            if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalC1Name()), direction, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                            if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalC2Name()), direction, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                        }
                        if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalD1Name()), direction, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                        if(!checkDirectionSensor(((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(t->getSignalD2Name()), direction, ConnectivityUtil::OVERALL, cUtil)) errorCount++;
                    }
                }
                else {
                    log.error("Unknown turnout type for turnout "+t->getTurnout()->getSystemName()+
                                    " in Section "+getSystemName()+".");
                    errorCount ++;
                }
            }
            else {
                // signal heads missing in turnout
                missingSignalsTurnouts ++;
   }
  }
 }
 // set up missing signal head message, if any
 if ( (missingSignalsBB+missingSignalsTurnouts+missingSignalsLevelXings) > 0 )
 {
  QString s = "Section - "+getSystemName();
  if ( (getUserName()!=nullptr) && (getUserName()!=("")) )
    s = s+"("+getUserName()+")";
  if (missingSignalsBB>0)
  {
   s = s+", "+(missingSignalsBB)+" anchor point signal heads missing";
  }
  if (missingSignalsTurnouts>0)
  {
   s = s+", "+(missingSignalsTurnouts)+" turnouts missing signals";
  }
  if (missingSignalsLevelXings>0)
  {
   s = s+", "+(missingSignalsLevelXings)+" level crossings missing signals";
  }
  log.warn(s);
 }
 return errorCount;
}
/*private*/ bool Section::checkDirectionSensor(SignalHead* sh, int direction, int where,
                                                            ConnectivityUtil* cUtil) {
    QString sensorName = "";
    if (direction == EntryPoint::FORWARD) {
        sensorName = getForwardBlockingSensorName();
    }
    else if (direction == EntryPoint::REVERSE) {
        sensorName = getReverseBlockingSensorName();
    }
    return (cUtil->addSensorToSignalHeadLogic(sensorName, sh, where));
}
/*private*/ LayoutTurnout* Section::getLayoutTurnoutFromTurnoutName(QString turnoutName, LayoutEditor* panel) {
    Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(turnoutName);
    if (t==nullptr) return nullptr;
    for (LayoutTurnout* lt : panel->getLayoutTurnouts()) {
        if (lt->getTurnout()==t) return lt;
    }
    return nullptr;
}
//#endif // LAYOUTS
#if 1
/**
 * Checks that there are Signal Heads at all Entry Points to this Section.
 * This method will warn if it finds unsignalled internal turnouts, but will continue
 *		checking.  Unsignalled entry points except for those at unsignalled internal
 *		turnouts will be considered errors, and will be reported to the user.  This
 *		method stops searching when it find the first missing Signal Head.
 * Returns 'true' if successful, 'false' otherwise.
 */
/*public*/ bool Section::checkSignals(JmriJFrame* /*frame*/, LayoutEditor* panel) {
    if (panel==nullptr) {
        log.error("Null Layout Editor panel on call to 'checkSignals'");
        return false;
    }
    if (initializationNeeded) initializeBlocks();
    Block* eBlock = getEntryBlock();
    QVector<EntryPoint*>* epList = getListOfForwardBlockEntryPoints(eBlock);
    if (epList->size() > 0) {

// djd debugging - need code to fully implement checkSignals
    }
    return true;
}
#endif
/*private*/ QVector<EntryPoint*>* Section::getListOfForwardBlockEntryPoints(Block* b) {
    if (initializationNeeded) initializeBlocks();
    QVector<EntryPoint*>* a = new QVector<EntryPoint*>();
    for (int i = 0; i<mForwardEntryPoints->size(); i++) {
        if ( b == (mForwardEntryPoints->at(i))->getBlock() ){
            a->append(mForwardEntryPoints->at(i));
        }
    }
    return a;
}
#if 1
/**
 * Validate the Section.
 * This checks block connectivity, warns of redundant EntryPoints,
 *		and otherwise checks internal consistency of the Section.
 * An appropriate error message is logged if a problem is found.
 * This method assumes that Block Paths are correctly initialized.
 * If a Layout Editor panel is available, lePanel!=nullptr, the initialization
 *		of Blocks is checked.
 * Returns an empty string "", if everything checks out.  Returns
 *		a string describing the error if an error is found.
 */
/*public*/ QString Section::validate(LayoutEditor* lePanel) {
    if (initializationNeeded) initializeBlocks();
    // validate Paths and Bean Settings if a Layout Editor panel is available
    if (lePanel!=nullptr) {
        for (int i=0; i<(mBlockEntries->size()-1); i++) {
            LayoutBlock* lBlock = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(
                            getBlockBySequenceNumber(i)->getUserName());
            if (lBlock==nullptr) {
                log.error("Layout Block "+getBlockBySequenceNumber(i)->getUserName()+
                                " not found.  Paths not checked.");
            }
            else {
                lBlock->updatePathsUsingPanel(lePanel);
            }
        }
    }
    // check connectivity between internal blocks
    if (mBlockEntries->size()>1) {
        for (int i=0; i<(mBlockEntries->size()-1); i++) {
            if (!connected(getBlockBySequenceNumber(i), getBlockBySequenceNumber(i+1))) {
                QString s = "Sequential Blocks - "+getBlockBySequenceNumber(i)->getSystemName()+
                    ", "+getBlockBySequenceNumber(i+1)->getSystemName()+
                    " - are not connected in Section "+getSystemName()+".";
                return s;
            }
            if (!connected(getBlockBySequenceNumber(i+1), getBlockBySequenceNumber(i))) {
                QString s = "Sequential Blocks - "+getBlockBySequenceNumber(i)->getSystemName()+
                    ", "+getBlockBySequenceNumber(i+1)->getSystemName()+
                    " - Paths are not consistent - Section "+getSystemName()+".";
                return s;
            }
        }
    }
    // validate entry points
    if ((mForwardEntryPoints->size() == 0) && (mReverseEntryPoints->size()==0)) {
        QString s = "Section "+getSystemName()+ "has no Entry Points.";
        return s;
    }
    if (mForwardEntryPoints->size()>0) {
        for (int i = 0; i<mForwardEntryPoints->size(); i++) {
            EntryPoint* ep = mForwardEntryPoints->at(i);
            if (!containsBlock(ep->getBlock())) {
                QString s = "Entry Point Block, "+ep->getBlock()->getSystemName()+
                        ", is not a Block in Section "+getSystemName()+".";
                return s;
            }
            if (!connectsToBlock(ep->getFromBlock())) {
                QString s = "Entry Point From Block, "+ep->getBlock()->getSystemName()+
                        ", is not connected to a Block in Section "+getSystemName()+".";
                return s;
            }
            if (!ep->isForwardType()) {
                QString s = "Direction of FORWARD Entry Point From Block "+
                        ep->getFromBlock()->getSystemName()+" to Section "+
                        getSystemName()+" is incorrectly set.";
                return s;
            }
            if (!connected(ep->getBlock(), ep->getFromBlock())) {
                QString s = "Entry Point Blocks, "+ep->getBlock()->getSystemName()+
                        " and "+ep->getFromBlock()->getSystemName()+
                        ", are not connected in Section "+getSystemName()+".";
                return s;
            }
        }
    }
    if (mReverseEntryPoints->size()>0) {
        for (int i = 0; i<mReverseEntryPoints->size(); i++) {
            EntryPoint* ep = mReverseEntryPoints->at(i);
            if (!containsBlock(ep->getBlock())) {
                QString s = "Entry Point Block, "+ep->getBlock()->getSystemName()+
                        ", is not a Block in Section "+getSystemName()+".";
                return s;
            }
            if (!connectsToBlock(ep->getFromBlock())) {
                QString s = "Entry Point From Block, "+ep->getBlock()->getSystemName()+
                        ", is not connected to a Block in Section "+getSystemName()+".";
                return s;
            }
            if (!ep->isReverseType()) {
                QString s = "Direction of REVERSE Entry Point From Block "+
                        ep->getFromBlock()->getSystemName()+" to Section "+
                        getSystemName()+" is incorrectly set.";
                return s;
            }
            if (!connected(ep->getBlock(), ep->getFromBlock())) {
                QString s = "Entry Point Blocks, "+ep->getBlock()->getSystemName()+
                        " and "+ep->getFromBlock()->getSystemName()+
                        ", are not connected in Section "+getSystemName()+".";
                return s;
            }
        }
    }
    return "";
}
#endif
/*private*/ bool Section::connected(Block* b1, Block* b2) {
    if ( (b1!=nullptr) && (b2!=nullptr) ) {
        QList<Path*> paths = b1->getPaths()->toList();
        for (int i = 0; i<paths.size(); i++) {
            if (paths.at(i)->getBlock() == b2) return true;
        }
    }
    return false;
}

/**
 * This function sets/resets the display to use alternate color for unoccupied blocks in this section.
 *    If 'set' is true, the alternate unoccupied color will be used.
 *    If 'set' is false, the unoccupied color will be used.
 *    If Layout Editor panel is not present, Layout Blocks will not be present, and nothing will be set.
 */
/*public*/ void Section::setAlternateColor(bool set) {
    for (int i=0; i<mBlockEntries->size(); i++) {
        Block* b = mBlockEntries->at(i);
        LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(b->getUserName());
        if (lb!=nullptr) lb->setUseExtraColor(set);
    }
}

/**
 * This function sets/resets the display to use alternate color for
 * unoccupied blocks in this section. If the section already contains an
 * active block, then the alternative colour will be set from the active
 * block, if no active block is found or we are clearing the alternative
 * colour then all the blocks in the section will be set. If Layout Editor
 * panel is not present, Layout Blocks will not be present, and nothing will
 * be set.
 *
 * @param set true to use alternate unoccupied color; false otherwise
 */
/*public*/ void Section::setAlternateColorFromActiveBlock(bool set) {
    LayoutBlockManager* lbm = (LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager");
    bool beenSet = false;
    if (!set || getState() == FREE || getState() == UNKNOWN) {
        setAlternateColor(set);
    } else if (getState() == FORWARD) {
        for (Block* b : *mBlockEntries) {
            if (b->getState() == Block::OCCUPIED) {
                beenSet = true;
            }
            if (beenSet) {
                LayoutBlock* lb = (LayoutBlock*)lbm->getByUserName(b->getUserName());
                if (lb != nullptr) {
                    lb->setUseExtraColor(set);
                }
            }
        }
    } else if (getState() == REVERSE) {
        for (Block* b : *mBlockEntries) {
            if (b->getState() == Block::OCCUPIED) {
                beenSet = true;
            }
            if (beenSet) {
                LayoutBlock* lb = (LayoutBlock*)lbm->getByUserName(b->getUserName());
                if (lb != nullptr) {
                    lb->setUseExtraColor(set);
                }
            }
        }
    }
    if (!beenSet) {
        setAlternateColor(set);
    }
}
/**
 * Set the block values for blocks in this section.
 *
 * @param name the value to set all blocks to
 */
/*public*/ void Section::setNameInBlocks(QString name) {
    for (Block* b : *mBlockEntries) {
        b->setValue(name);
    }
}

/**
 * This function sets the block values for blocks in this section.
 *
 * @param value the name to set block values to
 */
/*public*/ void Section::setNameInBlocks(QVariant value) {
    for (Block* b : *mBlockEntries) {
        b->setValue(value);
    }
}

/*public*/ void Section::setNameFromActiveBlock(QVariant value) {
    bool beenSet = false;
    if (value == QVariant() || getState() == FREE || getState() == UNKNOWN) {
        setNameInBlocks(value);
    } else if (getState() == FORWARD) {
        for (Block* b : *mBlockEntries) {
            if (b->getState() == Block::OCCUPIED) {
                beenSet = true;
            }
            if (beenSet) {
                b->setValue(value);
            }
        }
    } else if (getState() == REVERSE) {
        for (Block* b : *mBlockEntries) {
            if (b->getState() == Block::OCCUPIED) {
                beenSet = true;
            }
            if (beenSet) {
                b->setValue(value);
            }
        }
    }
    if (!beenSet) {
        setNameInBlocks(value);
    }
}

/**
 * This function clears the block values for blocks in this section.
 */
/*public*/ void Section::clearNameInUnoccupiedBlocks() {
 for (Block* b : *mBlockEntries) {
     if (b->getState() == Block::UNOCCUPIED) {
         b->setValue("  ");
     }
 }
}

/**
 * This function suppresses the update of a memory variable when a block goes to unoccupied, so the
 *	text set above doesn't get wiped out.
 */
/*public*/ void Section::suppressNameUpdate(bool set) {
    for (int i=0; i<mBlockEntries->size(); i++) {
        Block* b = mBlockEntries->at(i);
        LayoutBlock* lb = (LayoutBlock*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getByUserName(b->getUserName());
        if (lb!=nullptr) lb->setSuppressNameUpdate(set);
    }
}
#endif
/*public*/ void Section::setSectionType(int type) {
    sectionType = type;
}

/*public*/ int Section::getSectionType() {
    return sectionType;
}

/*public*/ QString Section::getBeanType() {
    return tr("Section");
}

/*public*/ void Section::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException)
{
    if ("CanDelete" == (evt->getPropertyName())) { //IN18N
        NamedBean* nb = (NamedBean*) VPtr<NamedBean*>::asPtr( evt->getOldValue());
        //if (nb instanceof Sensor) {
        if(qobject_cast<Sensor*>(nb)!= nullptr)
        {
            if (nb == (getForwardBlockingSensor())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                //throw new java.beans.PropertyVetoException(Bundle.getMessage("VetoBlockingSensor", nb.getBeanType(), Bundle.getMessage("Forward"), Bundle.getMessage("Blocking"), getDisplayName()), e); //IN18N
            }
            if (nb == (getForwardStoppingSensor())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                //throw new java.beans.PropertyVetoException(Bundle.getMessage("VetoBlockingSensor", nb.getBeanType(), Bundle.getMessage("Forward"), Bundle.getMessage("Stopping"), getDisplayName()), e);
            }
            if (nb == (getReverseBlockingSensor())) {
             PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                //throw new java.beans.PropertyVetoException(Bundle.getMessage("VetoBlockingSensor", nb.getBeanType(), Bundle.getMessage("Reverse"), Bundle.getMessage("Blocking"), getDisplayName()), e);
            }
            if (nb == (getReverseStoppingSensor())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                //throw new java.beans.PropertyVetoException(Bundle.getMessage("VetoBlockingSensor", nb.getBeanType(), Bundle.getMessage("Reverse"), Bundle.getMessage("Stopping"), getDisplayName()), e);
            }
        }
        //if (nb instanceof Block) {
        if(qobject_cast<Block*>(nb) != nullptr)
        {
            if (getBlockList()->contains((Block*)nb)) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw  PropertyVetoException(tr("Block is in use with Section \"%1\"").arg( getDisplayName()), e);
            }
        }
    } else if ("DoDelete" == (evt->getPropertyName())) { //IN18N

    }
}


//    static final org.apache.log4j.Logger log = org.apache.log4j.Logger->atLogger(Section.class->atName());
