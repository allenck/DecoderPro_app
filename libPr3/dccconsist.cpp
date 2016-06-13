#include "dccconsist.h"
#include "dcclocoaddress.h"
#include "exceptions.h"
#include "programmer.h"
#include "instancemanager.h"
#include "globalprogrammermanager.h"
#include "addressedprogrammermanager.h"

DccConsist::DccConsist(int address, QObject *parent) //: Consist(parent)
{
 consistAddress = new DccLocoAddress(address,false);
 ConsistDir = new QHash<DccLocoAddress*, bool>();
 ConsistList = new QList<DccLocoAddress*>();
 ConsistPosition = new QHash<DccLocoAddress*, int>();
 ConsistID = consistAddress->toString();
 log =new Logger("DccConsist");
 listeners = new QVector<ConsistListener*>();
 ConsistType = ADVANCED_CONSIST;
}
/**
 * This is the Default DCC consist.
 * It utilizes the fact that IF a Command Station supports OpsMode
 * Programing, you can write the consist information to CV19, so ANY
 * Command Station that supports Ops Mode Programing can write this
 * address to a Command Station that supports it.
 *
 * @author                      Paul Bender Copyright (C) 2003-2008
 * @version                     $Revision: 20032 $
 */
///*public*/ class DccConsist implements Consist, ProgListener{


    // Initialize a consist for the specific address.
        // In this implementation, we can safely assume the address is a
    // short address, since Advanced Consisting is only possible with
    // a short address.
        // The Default consist type is an advanced consist


// Initialize a consist for a specific DccLocoAddress.
    // The Default consist type is an advanced consist
/*public*/ DccConsist::DccConsist(DccLocoAddress* address, QObject* parent) //: Consist(parent)
{
 consistAddress = address;
 ConsistDir = new QHash<DccLocoAddress*, bool>();
 ConsistList = new QList<DccLocoAddress*>();
 ConsistPosition = new QHash<DccLocoAddress*, int>();
 ConsistID = consistAddress->toString();
 log =new Logger("DccConsist");
 listeners = new QVector<ConsistListener*>();
 ConsistType = ADVANCED_CONSIST;
}

// Clean Up local Storage.
/*public*/ void DccConsist::dispose()
{
 for(int i=(ConsistList->size()-1);i>=0;i--)
 {
  DccLocoAddress* loco=ConsistList->at(i);
  if(log->isDebugEnabled()) log->debug("Deleting Locomotive: " + loco->toString());
  try
  {
   remove(loco);
  }
  catch (Exception ex)
  {
   log->error("Error removing loco: " + loco->toString() + " from consist: " + consistAddress->toString());
  }
 }
 ConsistList = NULL;
 ConsistDir = NULL;
 ConsistPosition = NULL;
}

// Set the Consist Type
/*public*/ void DccConsist::setConsistType(int consist_type){
      if(consist_type==ADVANCED_CONSIST) {
    ConsistType = consist_type;
    return;
      }
      else {
    log->error("Consist Type Not Supported");
    notifyConsistListeners(new DccLocoAddress(0,false),ConsistListener::NotImplemented);
      }
}

// get the Consist Type
/*public*/ int DccConsist::getConsistType(){
    return ConsistType;
}

// get the Consist Address
/*public*/ DccLocoAddress* DccConsist::getConsistAddress(){
    return consistAddress;
}

/* is this address allowed?
     * Since address 00 is an analog locomotive, we can't program CV19
 * to include it in a consist, but all other addresses are ok.
     */
    /*public*/ bool DccConsist::isAddressAllowed(DccLocoAddress* address) {
            if(address->getNumber()!=0) return(true);
            else return(false);
    }

/* is there a size limit for this consist?
     * For Decoder Assisted Consists, returns -1 (no limit)
     * return 0 for any other consist type.
     */
    /*public*/ int DccConsist::sizeLimit(){
       if(ConsistType==ADVANCED_CONSIST) {
            return -1;
       } else return 0;
    }


// get a list of the locomotives in the consist
    /*public*/ QList<DccLocoAddress*>* DccConsist::getConsistList() { return ConsistList; }

// does the consist contain the specified address?
/*public*/ bool DccConsist::contains(DccLocoAddress* address) {
   if(ConsistType==ADVANCED_CONSIST) {
    //String Address = Integer.toString(address);
    return(ConsistList->contains(address));
   } else {
    log->error("Consist Type Not Supported");
    notifyConsistListeners(new DccLocoAddress(0,false),ConsistListener::NotImplemented);
      }
   return false;
}

// get the relative direction setting for a specific
// locomotive in the consist
/*public*/ bool DccConsist::getLocoDirection(DccLocoAddress* address) {
   if(ConsistType==ADVANCED_CONSIST) {
    //String Address= Integer.toString(address);
    bool Direction = ConsistDir->value(address);
    return( Direction);
   } else {
    Logger::error("Consist Type Not Supported");
    notifyConsistListeners(address,ConsistListener::NotImplemented);
      }
   return false;
}

    /*
 * Add a Locomotive to an Advanced Consist
 *  @param address is the Locomotive address to add to the locomotive
 *  @param directionNormal is True if the locomotive is traveling
     *        the same direction as the consist, or false otherwise.
     */
/*public*/ void DccConsist::add(DccLocoAddress* LocoAddress,bool directionNormal) {
      if(ConsistType==ADVANCED_CONSIST) {
     //String Address= Integer.toString(LocoAddress);
         bool Direction = (directionNormal);
     if(!(ConsistList->contains(LocoAddress))) ConsistList->append(LocoAddress);
     ConsistDir->insert(LocoAddress,Direction);
         addToAdvancedConsist(LocoAddress, directionNormal);
      }
      else {
    log->error("Consist Type Not Supported");
    notifyConsistListeners(LocoAddress,ConsistListener::NotImplemented);
      }
}

    /*
 * Restore a Locomotive to an Advanced Consist, but don't write to
     * the command station.  This is used for restoring the consist
     * from a file or adding a consist read from the command station.
 *  @param address is the Locomotive address to add to the locomotive
 *  @param directionNormal is True if the locomotive is traveling
     *        the same direction as the consist, or false otherwise.
     */
/*public*/ void DccConsist::restore(DccLocoAddress* LocoAddress,bool directionNormal) {
      if(ConsistType==ADVANCED_CONSIST) {
     //String Address= Integer.toString(LocoAddress);
         bool Direction = (directionNormal);
     if(!(ConsistList->contains(LocoAddress))) ConsistList->append(LocoAddress);
     ConsistDir->insert(LocoAddress,Direction);
      }
      else {
    log->error("Consist Type Not Supported");
    notifyConsistListeners(LocoAddress,ConsistListener::NotImplemented);
      }
}

    /*
 *  Remove a Locomotive from this Consist
 *  @param address is the Locomotive address to add to the locomotive
     */
/*public*/ void DccConsist::remove(DccLocoAddress* LocoAddress)
{
 if(ConsistType==ADVANCED_CONSIST)
 {
  //String Address= Integer.toString(LocoAddress);
  ConsistDir->remove(LocoAddress);
  ConsistList->removeAt(ConsistList->indexOf(LocoAddress));
  ConsistPosition->remove(LocoAddress);
  removeFromAdvancedConsist(LocoAddress);
 }
 else
 {
  log->error("Consist Type Not Supported");
  notifyConsistListeners(LocoAddress,ConsistListener::NotImplemented);
 }
}


    /*
 *  Add a Locomotive to an Advanced Consist
 *  @param address is the Locomotive address to add to the locomotive
 *  @param directionNormal is True if the locomotive is traveling
     *        the same direction as the consist, or false otherwise.
     */
/*protected*/ void DccConsist::addToAdvancedConsist(DccLocoAddress* LocoAddress, bool directionNormal)
{
 Programmer* opsProg = ((AddressedProgrammerManager*)InstanceManager::programmerManagerInstance())->getAddressedProgrammer(LocoAddress->isLongAddress(), LocoAddress->getNumber());
 if(directionNormal)
 {
  try
  {
   opsProg->writeCV(19,consistAddress->getNumber(), (ProgListener*)this);
  }
  catch(ProgrammerException e)
  {
   // Don't do anything with this yet
  }
 }
 else
 {
  try
  {
   opsProg->writeCV(19,consistAddress->getNumber() + 128 ,(ProgListener*)this);
  }
  catch(ProgrammerException e)
  {
   // Don't do anything with this yet
  }
 }
 InstanceManager::programmerManagerInstance()->releaseAddressedProgrammer(opsProg);
}

    /*
 *  Remove a Locomotive from an Advanced Consist
 *  @param address is the Locomotive address to remove from the consist
     */
/*protected*/ void DccConsist::removeFromAdvancedConsist(DccLocoAddress* LocoAddress) {
    Programmer* opsProg = ((AddressedProgrammerManager*)InstanceManager::programmerManagerInstance())->getAddressedProgrammer(LocoAddress->isLongAddress(),
                        LocoAddress->getNumber());
    try {
        opsProg->writeCV(19,0,(ProgListener*)this);
    } catch(ProgrammerException e) {
        // Don't do anything with this yet
    }
    InstanceManager::programmerManagerInstance()->releaseAddressedProgrammer(opsProg);
}

    /*
     *  Set the position of a locomotive within the consist
     *  @param address is the Locomotive address
     *  @param position is a constant representing the position within
     *         the consist.
     */
    /*public*/ void DccConsist::setPosition(DccLocoAddress* address,int position){
            ConsistPosition->insert(address,(position));
    }

    /*
     * Get the position of a locomotive within the consist
     * @param address is the Locomotive address of interest
     */
    /*public*/ int DccConsist::getPosition(DccLocoAddress* address){
        if(ConsistPosition->contains(address))
            return(ConsistPosition->value(address));
        // if the consist order hasn't been set, we'll use default
        // positioning based on index in the arraylist.  Lead locomotive
        // is position 0 in the list and the trail is the last locomtoive
        // in the list.
        int index=ConsistList->indexOf(address);
        if(index==0)
            return(Consist::POSITION_LEAD);
        else if(index==(ConsistList->size()-1))
            return(Consist::POSITION_TRAIL);
        else return index;
    }



/*
     * Add a Listener for consist events
     * @param Listener is a consistListener object
     */
    /*public*/ void DccConsist::addConsistListener(ConsistListener* Listener){
    if(!listeners->contains(Listener))
        listeners->append(Listener);
}

    /*
     * Remove a Listener for consist events
     * @param Listener is a consistListener object
     */
    /*public*/ void DccConsist::removeConsistListener(ConsistListener* Listener){
    if(listeners->contains(Listener))
        listeners->remove(listeners->indexOf(Listener));
}

    // Get and set the
    /*
     * Set the text ID associated with the consist
     * @param String is a string identifier for the consist
     */
    /*public*/ void DccConsist::setConsistID(QString ID){
    ConsistID=ID;
    }

    /*
     * Get the text ID associated with the consist
     * @return String identifier for the consist
     *         default value is the string Identifier for the
     *         consist address.
     */
    /*public*/ QString DccConsist::getConsistID(){
    return ConsistID;
    }

/*
     * Reverse the order of locomotives in the consist and flip
     * the direction bits of each locomotive.
     */
/*public*/ void DccConsist::reverse()
{
 // save the old lead locomotive direction.
 bool oldDir=ConsistDir->value(ConsistList->at(0));
 // reverse the direction of the list
 //Collections.reverse(ConsistList);
 QList<DccLocoAddress*>* newList = new QList<DccLocoAddress*>();
 for (int i= ConsistList->size()-1; i >= 0; i --)
 {
  DccLocoAddress* a = ConsistList->at(i);
  newList->append(a);
 }
 ConsistList = newList;
 // and then save the new lead locomotive direction
 bool newDir=ConsistDir->value(ConsistList->at(0));
 // and itterate through the list to reverse the directions of the
 // individual elements of the list.
 //java.util.Iterator<DccLocoAddress> i= ConsistList.iterator();
 QListIterator<DccLocoAddress*> i(*ConsistList);
 while(i.hasNext()){
        DccLocoAddress* locoaddress=i.next();
        if(oldDir==newDir)
      add(locoaddress,getLocoDirection(locoaddress));
        else
      add(locoaddress,!getLocoDirection(locoaddress));
    if(ConsistPosition->contains(locoaddress))
    {
    if(getPosition(locoaddress)==Consist::POSITION_LEAD)
       setPosition(locoaddress,Consist::POSITION_TRAIL);
    else if(getPosition(locoaddress)==Consist::POSITION_TRAIL)
       setPosition(locoaddress,Consist::POSITION_LEAD);
    else
       setPosition(locoaddress,
                        ConsistList->size()-getPosition(locoaddress));
    }
      }
}


/*
 * Notify all listener objects of a status change.
 * @param LocoAddress is the address of any specific locomotive the
 *       status refers to.
 * @param ErrorCode is the status code to send to the
 *       consistListener objects
 */
//@SuppressWarnings("unchecked")
/*protected*/ void DccConsist::notifyConsistListeners(DccLocoAddress*  LocoAddress, int ErrorCode)
{
 // make a copy of the listener vector to  notify.
 QVector<ConsistListener*>* v = new QVector<ConsistListener*>();
 //synchronized(this)
 {
  //v = (Vector<ConsistListener>)listeners.clone();
  QMutexLocker locker(&mutex);
  foreach (ConsistListener* l, *listeners)
  {
   v->append(l);
  }
 }
 if (log->isDebugEnabled()) log->debug("Sending Status code: " +
                (QString("%1").arg(ErrorCode)) + " to "  +
                (QString("%1").arg(v->size())) +
                                        " listeners for Address "
                                        + LocoAddress->toString());
 // forward to all listeners
 int cnt = v->size();
 for (int i=0; i < cnt; i++)
 {
  ConsistListener* client = v->at(i);
  client->consistReply(LocoAddress,ErrorCode);
 }
}

// This class is to be registerd as a programmer listener, so we
    // include the programmingOpReply() function
/*public*/ void DccConsist::programmingOpReply(int value, int status) {
    if(log->isDebugEnabled()) log->debug("Programming Operation reply received, value is " + QString("%1").arg(value) + " ,status is " +QString("%1").arg(status));
    notifyConsistListeners(new DccLocoAddress(0,false),ConsistListener::OPERATION_SUCCESS);
}

//	static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DccConsist.class.getName());

//}
