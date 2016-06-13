#include "loconetconsistmanager.h"
#include "lnthrottlemanager.h"

LocoNetConsistManager::LocoNetConsistManager(LocoNetSystemConnectionMemo* lm, QObject *parent) :
    AbstractConsistManager(parent)
{
 this->memo=lm;

}
/**
 * LocoNetConsistManager.java
 *
 * Description:           Consist Manager for use with the
 *                        LocoNetConsist class for the consists it builds
 *
 * @author                Paul Bender Copyright (C) 2011
 * @version               $Revision: 20662 $
 */


//package jmri.jmrix.loconet;

//import jmri.Consist;
//import jmri.DccLocoAddress;

//public class LocoNetConsistManager extends jmri.jmrix.AbstractConsistManager implements jmri.ConsistManager {


    /**
     *  Constructor - call the constructor for the superclass, and
     *  initilize the consist reader thread, which retrieves consist
     *  information from the command station
     **/
//    public LocoNetConsistManager(LocoNetSystemConnectionMemo lm){
//        super();
//    this.memo=lm;
//    }

/**
 *    This implementation does support command station assisted
 *     consists, so return true.
 **/
/*public*/ bool LocoNetConsistManager::isCommandStationConsistPossible() { return true; }

/**
 *    Does a CS consist require a seperate consist address?
 **/
/*public*/ bool LocoNetConsistManager::csConsistNeedsSeperateAddress() { return false; }

/**
 *    Add a new LocoNetConsist with the given address to
 *    consistTable/consistList
 */
/*public*/ Consist* LocoNetConsistManager::addConsist(DccLocoAddress* address){
    if(consistList->contains(address)) // no duplicates allowed.
       return consistTable->value(address);
#if 0 // TODO define LocoNetConsist
    LocoNetConsist consist;
    consist = new LocoNetConsist(address,memo);
    consistTable.put(address,consist);
    consistList.add(address);
    return consist;
#else
    return NULL;
#endif
}


/* request an update from the layout, loading
 * Consists from the command station.
 *
 * On a LocoNet command station, the consists are stored in the
 * slots in an array based tree.  Each node in a consist contains
 * a pointer to the "top" slot in the consist.  A top slot is
 * allowed to be a member of another consist.  When this occurs,
 * it is labeled as a "mid" locomotive.
 *
 * This function updates the list of consists by scanning the
 * slots and adding new "top" slot addresses and removing address
 * that are no longer "top" locomotives.
 */
/*public*/ void LocoNetConsistManager::requestUpdateFromLayout(){
   SlotManager* sm=memo->getSlotManager();

   // in the first pass, check for consists top addresses in the
   // command station slots.

   for(int i=0;i<128;i++){
      LocoNetSlot* s=sm->slot(i);
      DccLocoAddress* address=new DccLocoAddress(s->locoAddr(),LnThrottleManager::isLongAddress(s->locoAddr()));
      if(log.isDebugEnabled()) log.debug(" Slot " + QString("%1").arg(i) + " Address " +address->toString() + " consist status " + LnConstants::CONSIST_STAT(s->consistStatus()));
      if(s->consistStatus()==LnConstants::CONSIST_TOP || s->consistStatus()==LnConstants::CONSIST_MID)
{
         // this is a consist top, add it to the list, if it is not there
         // already.
         if(!consistList->contains(address)){
            if(log.isDebugEnabled()) log.debug("Adding Consist with Address " + address->toString() + " due to command station read");
            addConsist(address);
            getConsist(address)->add(address,true); // add the address to the consist.
         }
      } else {
         // this is not a consist top, so remove it from the list, if it
         // is currently there.
            if(log.isDebugEnabled()) log.debug("Removing Consist with Address " + address->toString() + " due to command station read");
            consistList->removeOne(address);
      }
   }

   // make a second pass, this time looking for locomotives in a consist.
   for(int i=0;i<128;i++){
      LocoNetSlot* s=sm->slot(i);
      DccLocoAddress* address=new DccLocoAddress(s->locoAddr(),LnThrottleManager::isLongAddress(s->locoAddr()));
      if(log.isDebugEnabled()) log.debug(" Slot " + QString("%1").arg(i) + " Address " +address->toString() + " consist status " + LnConstants::CONSIST_STAT(s->consistStatus()));
      if(s->consistStatus()==LnConstants::CONSIST_SUB || s->consistStatus()==LnConstants::CONSIST_MID)
{
         // this is a consist member, add it to the consist in the
         // slot which it has a pointer to (the slot pointer is stored in
         // the slot's speed).
         DccLocoAddress* lead= new DccLocoAddress(sm->slot(s->speed())->locoAddr(),LnThrottleManager::isLongAddress(sm->slot(s->speed())->locoAddr()));
         getConsist(lead)->add(address,s->isForward()==sm->slot(s->speed())->isForward());
      }
   }
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoNetConsistManager.class.getName());
