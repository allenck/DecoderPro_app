#include "dccconsist.h"
#include "dcclocoaddress.h"
#include "exceptions.h"
#include "programmer.h"
#include "instancemanager.h"
#include "globalprogrammermanager.h"
#include "addressedprogrammermanager.h"
#include "consistpreferencesmanager.h"
#include "rosterentry.h"
#include "variabletablemodel.h"
#include "decoderfile.h"
#include "decoderindexfile.h"
#include  "roster.h"
#include "addressedprogrammer.h"
#include "defaultprogrammermanager.h"

DccConsist::DccConsist(int address) : Consist()
{
 common(new DccLocoAddress(address, false), qobject_cast<DefaultProgrammerManager*>(InstanceManager::getDefault("AddressedProgrammerManager")));
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
/*public*/ DccConsist::DccConsist(DccLocoAddress* address) : Consist()
{
 common(address, qobject_cast<DefaultProgrammerManager*>(InstanceManager::getDefault("AddressedProgrammerManager")));
}

// Initialize a consist for a specific DccLocoAddress.
// The Default consist type is an advanced consist
/*public*/ DccConsist::DccConsist(DccLocoAddress* address, AddressedProgrammerManager* apm) : Consist()
{
 common(address, apm);
}

void DccConsist::common(DccLocoAddress *address, AddressedProgrammerManager* apm)
{
 setObjectName("DccConsist");
 opsProgManager = apm;
 this->listeners = new QVector<ConsistListener*>();
 consistAddress = address;
 //consistDir = QHash<DccLocoAddress*, bool>();
 consistDir = new DccLocoHash<bool>();
 //consistList = QList<DccLocoAddress*>();
 consistList = new DccLocoAddressList();
 //consistPosition = QHash<DccLocoAddress*, int>();
 consistPosition = new DccLocoHash<int>();
 //consistRoster = QMap<DccLocoAddress*, QString>();
 consistRoster = new DccLocoHash<QString>();
 ConsistID = consistAddress->toString();
 log =new Logger("DccConsist");
 consistType = ADVANCED_CONSIST;
}

// Clean Up local Storage.
/*public*/ void DccConsist::dispose()
{
 for(int i=(consistList->size()-1);i>=0;i--)
 {
  DccLocoAddress* loco=consistList->at(i);
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
 //consistList = NULL;
 //delete consistList;
 //consistDir = NULL;
 //delete consistDir;
 //consistPosition = NULL;
 //delete consistPosition;
}

// Set the Consist Type
/*public*/ void DccConsist::setConsistType(int consist_type)
{
      if(consist_type==ADVANCED_CONSIST) {
    consistType = consist_type;
    return;
      }
      else {
    log->error("Consist Type Not Supported");
    notifyConsistListeners(new DccLocoAddress(0,false),ConsistListener::NotImplemented);
      }
}

// get the Consist Type
/*public*/ int DccConsist::getConsistType()
{
    return consistType;
}

// get the Consist Address
/*public*/ DccLocoAddress* DccConsist::getConsistAddress()
{
    return consistAddress;
}

/* is this address allowed?
 * Since address 00 is an analog locomotive, we can't program CV19
* to include it in a consist, but all other addresses are ok.
 */
/*public*/ bool DccConsist::isAddressAllowed(DccLocoAddress* address)
{
  if(address->getNumber()!=0)
   return(true);
  else return(false);
}

/* is there a size limit for this consist?
 * For Decoder Assisted Consists, returns -1 (no limit)
 * return 0 for any other consist type.
 */
/*public*/ int DccConsist::sizeLimit()
{
   if(consistType==ADVANCED_CONSIST) {
        return -1;
   } else return 0;
}


// get a list of the locomotives in the consist
    /*public*/ QList<DccLocoAddress*> DccConsist::getConsistList()  { return *consistList->toList(); }

// does the consist contain the specified address?
/*public*/ bool DccConsist::contains(DccLocoAddress* address)  {
   if(consistType==ADVANCED_CONSIST) {
    //String Address = Integer.toString(address);
    return(consistList->contains(address));
   } else {
    log->error("Consist Type Not Supported");
    notifyConsistListeners(new DccLocoAddress(0,false),ConsistListener::NotImplemented);
      }
   return false;
}

// get the relative direction setting for a specific
// locomotive in the consist
/*public*/ bool DccConsist::getLocoDirection(DccLocoAddress* address)   {
   if(consistType==ADVANCED_CONSIST) {
    //String Address= Integer.toString(address);
    bool Direction = consistDir->value(address);
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
/*public*/ void DccConsist::add(DccLocoAddress* locoAddress,bool directionNormal)
{
 if(consistType==ADVANCED_CONSIST)
 {
  //String Address= Integer.toString(LocoAddress);
  bool Direction = (directionNormal);
  if(!(consistList->contains(locoAddress)))
   consistList->append(locoAddress);
  consistDir->insert(locoAddress,Direction);
  addToAdvancedConsist(locoAddress, directionNormal);
  //set the value in the roster entry for CV19
  setRosterEntryCVValue(locoAddress);
 }
 else
 {
  log->error("Consist Type Not Supported");
  notifyConsistListeners(locoAddress,ConsistListener::NotImplemented);
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
/*public*/ void DccConsist::restore(DccLocoAddress* locoAddress,bool directionNormal) {
      if(consistType==ADVANCED_CONSIST) {
     //String Address= Integer.toString(LocoAddress);
         bool Direction = (directionNormal);
     if(!(consistList->contains(locoAddress))) consistList->append(locoAddress);
     consistDir->insert(locoAddress,Direction);
      }
      else {
    log->error("Consist Type Not Supported");
    notifyConsistListeners(locoAddress,ConsistListener::NotImplemented);
      }
}

    /*
 *  Remove a Locomotive from this Consist
 *  @param address is the Locomotive address to add to the locomotive
     */
/*public*/ void DccConsist::remove(DccLocoAddress* locoAddress)
{
 if(consistType==ADVANCED_CONSIST)
 {
  //String Address= Integer.toString(LocoAddress);
  consistDir->remove(locoAddress);
  consistList->removeAt(consistList->indexOf(locoAddress));
  consistPosition->remove(locoAddress);
  removeFromAdvancedConsist(locoAddress);
 }
 else
 {
  log->error("Consist Type Not Supported");
  notifyConsistListeners(locoAddress,ConsistListener::NotImplemented);
 }
}


    /*
 *  Add a Locomotive to an Advanced Consist
 *  @param address is the Locomotive address to add to the locomotive
 *  @param directionNormal is True if the locomotive is traveling
     *        the same direction as the consist, or false otherwise.
     */
/*protected*/ void DccConsist::addToAdvancedConsist(DccLocoAddress* locoAddress, bool directionNormal)
{
 if (opsProgManager == nullptr) {
     log->error("Can't make consisting change because no programmerManager exists; this is probably a configuration error in the preferences");
     return;
 }

 AddressedProgrammer* opsProg = opsProgManager
         ->getAddressedProgrammer(locoAddress->isLongAddress(),
                 locoAddress->getNumber());
 if (opsProg == nullptr) {
     log->error("Can't make consisting change because no programmer exists; this is probably a configuration error in the preferences");
     return;
 }
 if(directionNormal)
 {
  try
  {
   opsProg->writeCV("19",consistAddress->getNumber(), (ProgListener*)this);
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
   opsProg->writeCV("19",consistAddress->getNumber() + 128 ,(ProgListener*)this);
  }
  catch(ProgrammerException e)
  {
   // Don't do anything with this yet
  }
 }
 ((DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))
                 ->releaseAddressedProgrammer(opsProg);
}

/*
 *  Remove a Locomotive from an Advanced Consist
 *  @param address is the Locomotive address to remove from the consist
 */
/*protected*/ void DccConsist::removeFromAdvancedConsist(DccLocoAddress* locoAddress)
{
 QObjectList* list = InstanceManager::getList("AddressedProgrammerManager");
 AddressedProgrammer* opsProg = nullptr;
 if(!list->isEmpty())
 {
  //AddressedProgrammerManager* mgr = qobject_cast<AddressedProgrammerManager*>(InstanceManager::getDefault("AddressedProgrammerManager"));
  AddressedProgrammerManager* mgr  = qobject_cast<DefaultProgrammerManager*>(list->at(0));
  opsProg = mgr->getAddressedProgrammer(locoAddress->isLongAddress(),
                         locoAddress->getNumber());
 }
 try
 {
  if(opsProg == nullptr)
   throw ProgrammerException("No Addressed Programmer!");
  opsProg->writeCV("19",0,(ProgListener*)this);
 } catch(ProgrammerException e) {
     // Don't do anything with this yet
  return;
 }
 ((DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->releaseAddressedProgrammer(opsProg);
}

/*
 *  Set the position of a locomotive within the consist
 *  @param address is the Locomotive address
 *  @param position is a constant representing the position within
 *         the consist.
 */
/*public*/ void DccConsist::setPosition(DccLocoAddress* address,int position)
{
 consistPosition->insert(address,(position));
}

/*
 * Get the position of a locomotive within the consist
 * @param address is the Locomotive address of interest
 */
/*public*/ int DccConsist::getPosition(DccLocoAddress* address) {
    if(consistPosition->contains(address))
        return(consistPosition->value(address));
    // if the consist order hasn't been set, we'll use default
    // positioning based on index in the arraylist.  Lead locomotive
    // is position 0 in the list and the trail is the last locomtoive
    // in the list.
    int index=consistList->indexOf(address);
    if(index==0)
        return(Consist::POSITION_LEAD);
    else if(index==(consistList->size()-1))
        return(Consist::POSITION_TRAIL);
    else return index;
}

/**
 * Set the roster entry of a locomotive within the consist
 *
 * @param address  is the Locomotive address
 * @param rosterId is the roster Identifer of the associated roster entry.
 */
//@Override
/*public*/ void DccConsist::setRosterId(DccLocoAddress* address, QString rosterId) {
    consistRoster->insert(address, rosterId);
}

/**
 * Get the rosterId of a locomotive within the consist
 *
 * @param address is the Locomotive address of interest
 * @return string roster Identifier associated with the given address
 *         in the consist.  Returns null if no roster entry is associated
 *         with this entry.
 */
//@Override
/*public*/ QString DccConsist::getRosterId(DccLocoAddress* address) {
    if (consistRoster->contains(address)) {
        return (consistRoster->value(address));
    } else {
        return NULL;
    }
}
/**
 * Update the value in the roster entry for CV19 for the specified
 * address
 *
 * @param address is the Locomotive address we are updating.
 */
/*protected*/ void DccConsist::setRosterEntryCVValue(DccLocoAddress* address){
   updateRosterCV(address,getLocoDirection(address),this->consistAddress->getNumber());
}

/**
 * Set the value in the roster entry's value for for CV19 to 0
 *
 * @param address is the Locomotive address we are updating.
 */
/*protected*/ void DccConsist::resetRosterEntryCVValue(DccLocoAddress* address){
   updateRosterCV(address,getLocoDirection(address),0);
}

/**
 * If allowed by the preferences, Update the CV19 value in the
 * specified address's roster entry, if the roster entry is known.
 *
 * @param address is the Locomotive address we are updating.
 * @param direction the direction to set.
 * @param value the numeric value of the consist address.
 */
/*protected*/ void DccConsist::updateRosterCV(DccLocoAddress* address,bool direction,int value){
     if(!((ConsistPreferencesManager*)InstanceManager::getDefault("ConsistPreferencesManager"))->isUpdateCV19()){
        log->trace("Consist Manager updates of CV19 are disabled in preferences");
        return;
     }
     if(getRosterId(address)==nullptr){
        // roster entry unknown.
        log->trace(tr("No RosterID for address %1 in consist %2.  Skipping CV19 update.").arg(address->toString()).arg(consistAddress->toString()));
        return;
     }
     RosterEntry* entry = Roster::getDefault()->getEntryForId(getRosterId(address));

     if(entry==nullptr || entry->getFileName()==nullptr || entry->getFileName() ==("")){
        // roster entry unknown.
        log->trace(tr("No file name available for RosterID %1,address %2, in consist %3.  Skipping CV19 update.").arg(getRosterId(address)).arg(address->toString()).arg(consistAddress->toString()));
        return;
     }
     CvTableModel*  cvTable = new CvTableModel(nullptr, nullptr);  // will hold CV objects
     VariableTableModel* varTable = new VariableTableModel(nullptr,QStringList()<<"Name"<<"Value",cvTable);
     entry->readFile();  // read, but don’t yet process

     // load from decoder file
     loadDecoderFromLoco(entry,varTable);

     entry->loadCvModel(varTable, cvTable);
     CvValue* cv19Value = cvTable->getCvByNumber("19");
     cv19Value->setValue((value & 0xff) | (direction?0x00:0x80 ));

     entry->writeFile(cvTable,varTable);
}

 // copied from PaneProgFrame
 /*protected*/ void DccConsist::loadDecoderFromLoco(RosterEntry* r,VariableTableModel* varTable) {
     // get a DecoderFile from the locomotive xml
     QString decoderModel = r->getDecoderModel();
     QString decoderFamily = r->getDecoderFamily();
     if (log->isDebugEnabled()) {
         log->debug(tr("selected loco uses decoder %1 %2").arg(decoderFamily).arg(decoderModel));
     }
     // locate a decoder like that.
     QList<DecoderFile*> l = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList("", decoderFamily, "", "", "", decoderModel);
     if (log->isDebugEnabled()) {
         log->debug(tr("found %1 matches").arg(l.size()));
     }
     if (l.isEmpty()) {
         log->debug(tr("Loco uses %1 %2 decoder, but no such decoder defined").arg(decoderFamily).arg(decoderModel ));
         // fall back to use just the decoder name, not family
         l = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList("", "", "", "", "", decoderModel);
         if (log->isDebugEnabled()) {
             log->debug(tr("found %1 matches without family key").arg(l.size()));
         }
     }
     if (!l.isEmpty()) {
         DecoderFile* d = l.at(0);
         loadDecoderFile(d, r, varTable);
     } else {
         if (decoderModel ==("")) {
             log->debug("blank decoderModel requested, so nothing loaded");
         } else {
             log->warn(tr("no matching \"%1\" decoder found for loco, no decoder info loaded").arg(decoderModel ));
         }
     }
 }
/*protected*/ void DccConsist::loadDecoderFile(DecoderFile* df, RosterEntry* re,VariableTableModel* variableModel) {
    if (df == nullptr) {
        log->warn("loadDecoder file invoked with null object");
        return;
    }
    if (log->isDebugEnabled()) {
        log->debug("loadDecoderFile from " + DecoderFile::fileLocation
                + " " + df->getFileName());
    }

    QDomElement decoderRoot = QDomElement();

    try {
        decoderRoot = df->rootFromName(DecoderFile::fileLocation + df->getFileName());
    }
    catch (JDOMException  e) {
        log->error("Exception while loading decoder XML file: " + df->getFileName(), e);
    }
    catch (IOException e) {
        log->error("Exception while loading decoder XML file: " + df->getFileName(), e);
    }
    // load variables from decoder tree
    df->getProductID();
    if(!decoderRoot.isNull()) {
       df->loadVariableModel(decoderRoot.firstChildElement("decoder"), variableModel);
       // load function names
       re->loadFunctions(decoderRoot.firstChildElement("decoder").firstChildElement("family").firstChildElement("functionlabels"));
    }
}

/*
 * Add a Listener for consist events
 * @param Listener is a consistListener object
 */
/*public*/ void DccConsist::addConsistListener(ConsistListener* Listener)
{
if(!listeners->contains(Listener))
    listeners->append(Listener);
}

/*
 * Remove a Listener for consist events
 * @param Listener is a consistListener object
 */
/*public*/ void DccConsist::removeConsistListener(ConsistListener* Listener)
{
if(listeners->contains(Listener))
    listeners->remove(listeners->indexOf(Listener));
}

// Get and set the
/*
 * Set the text ID associated with the consist
 * @param String is a string identifier for the consist
 */
/*public*/ void DccConsist::setConsistID(QString ID) {
ConsistID=ID;
}

/*
 * Get the text ID associated with the consist
 * @return String identifier for the consist
 *         default value is the string Identifier for the
 *         consist address.
 */
/*public*/ QString DccConsist::getConsistID()
{
 return ConsistID;
}

/*
     * Reverse the order of locomotives in the consist and flip
     * the direction bits of each locomotive.
     */
/*public*/ void DccConsist::reverse()
{
 // save the old lead locomotive direction.
 bool oldDir=consistDir->value(consistList->at(0));
 // reverse the direction of the list
 //Collections.reverse(ConsistList);
 DccLocoAddressList* newList = new DccLocoAddressList();
 for (int i= consistList->size()-1; i >= 0; i --)
 {
  DccLocoAddress* a = consistList->at(i);
  newList->append(a);
 }
 consistList = newList;
 // and then save the new lead locomotive direction
 bool newDir = consistDir->value(consistList->at(0));
 // and itterate through the list to reverse the directions of the
 // individual elements of the list.
 //java.util.Iterator<DccLocoAddress> i= consistList->iterator();
 QList<DccLocoAddress*>* l = consistList->toList();
 QListIterator<DccLocoAddress*> i(*l);
 while(i.hasNext())
 {
  DccLocoAddress* locoaddress = i.next();
  if(oldDir == newDir)
   add(locoaddress,getLocoDirection(locoaddress));
  else
   add(locoaddress,!getLocoDirection(locoaddress));
  if(consistPosition->contains(locoaddress))
  {
   if(getPosition(locoaddress)==Consist::POSITION_LEAD)
      setPosition(locoaddress,Consist::POSITION_TRAIL);
   else if(getPosition(locoaddress)==Consist::POSITION_TRAIL)
      setPosition(locoaddress,Consist::POSITION_LEAD);
   else
      setPosition(locoaddress, consistList->size()-getPosition(locoaddress));
  }
 }
}

/*
 * Restore the consist to the command station.
 */
//@Override
/*public*/ void DccConsist::restore() {
    // itterate through the list to re-add the addresses to the
    // command station.
 QList<DccLocoAddress*>* l = consistList->toList();

    QListIterator<DccLocoAddress*> i (*l);
    while (i.hasNext())
    {
     DccLocoAddress* locoaddress = i.next();
     add(locoaddress, getLocoDirection(locoaddress));
    }
    // notify any listeners that the consist changed
    this->notifyConsistListeners(consistAddress, ConsistListener::OK);
}

/*
 * Notify all listener objects of a status change.
 * @param LocoAddress is the address of any specific locomotive the
 *       status refers to.
 * @param ErrorCode is the status code to send to the
 *       consistListener objects
 */
//@SuppressWarnings("unchecked")
/*protected*/ void DccConsist::notifyConsistListeners(DccLocoAddress*  locoAddress, int ErrorCode)
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
                                        + locoAddress->toString());
 // forward to all listeners
 int cnt = v->size();
 for (int i=0; i < cnt; i++)
 {
  ConsistListener* client = v->at(i);
  client->consistReply(locoAddress,ErrorCode);
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
