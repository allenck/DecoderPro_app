#include "dccconsistmanager.h"

DccConsistManager::DccConsistManager(AddressedProgrammerManager *apm, QObject *parent) //:  ConsistManager(parent)
{
    consistTable = new DccLocoHash<DccConsist*>();
    changeListeners = new QList<ConsistListListener*>();
    opsProgManager = apm;
    setObjectName("DccConsistManager");
}
/**
 * DccConsistManager.java
 *
 * Description:           The Default Consist Manager which uses the
 *                        DccConsist class for the consists it builds
 *
 * @author                Paul Bender Copyright (C) 2003
 * @version               $Revision: 20642 $
 */



///*public*/ class DccConsistManager implements ConsistManager{


/**
 *    Find a Consist with this consist address, and return it.
 **/
///*public*/ Consist* DccConsistManager::getConsist(DccLocoAddress* address)
//{
//    if(consistTable->contains(address)) {
//        return(consistTable->value(address));
//    } else {
//        DccConsist* consist =NULL;
//        //consist = new DccConsist(address);
//        consistTable->insert(address,consist);
//        consistList->append(address);
//        return(consist);
//    }
//   }

//// remove the old Consist
///*public*/ void DccConsistManager::delConsist(DccLocoAddress* address)
//{
// consistTable->value(address)->dispose();
// consistTable->remove(address);
// consistList->removeAt(consistList->indexOf(address));
//}
//@Override
/*public*/ DccConsist *DccConsistManager::addConsist(DccLocoAddress* address) {
    if (! (qobject_cast<DccLocoAddress*>(address))) {
        throw new IllegalArgumentException("address is not a DccLocoAddress object");
    }
    if (consistTable->contains(address)) {
        return consistTable->value(address);
    }
    DccConsist* consist;
    consist = new DccConsist((DccLocoAddress*) address, opsProgManager);
    consistTable->insert(address, consist);
    return consist;
}
/**
     *    This implementation does NOT support Command Station
 *    consists, so return false.
     **/
    /*public*/ bool DccConsistManager::isCommandStationConsistPossible() { return false; }

    /**
     *    Does a CS consist require a seperate consist address?
 *    This implemenation does not support Command Station
 *    consists, so return false
     **/
    /*public*/ bool DccConsistManager::csConsistNeedsSeparateAddress() { return false; }

///**
// *  Return the list of consists we know about.
// **/
///*public*/QList<DccLocoAddress*>* DccConsistManager::getConsistList() { return consistList; }

///*public*/ QString DccConsistManager::decodeErrorCode(int ErrorCode){
//    QString buffer = "";
//    if ((ErrorCode & ConsistListener::NotImplemented) != 0)
//                buffer.append("Not Implemented ");
//    if ((ErrorCode & ConsistListener::OPERATION_SUCCESS) != 0)
//                buffer.append("Operation Completed Successfully ");
//    if ((ErrorCode & ConsistListener::CONSIST_ERROR) != 0)
//                buffer.append("Consist Error ");
//    if ((ErrorCode & ConsistListener::LOCO_NOT_OPERATED) != 0)
//                buffer.append("Address not controled by this device.");
//    if ((ErrorCode & ConsistListener::ALREADY_CONSISTED) != 0)
//                buffer.append("Locomotive already consisted");
//    if ((ErrorCode & ConsistListener::NOT_CONSISTED) != 0)
//                buffer.append("Locomotive Not Consisted ");
//    if ((ErrorCode & ConsistListener::NONZERO_SPEED) != 0)
//                buffer.append("Speed Not Zero ");
//    if ((ErrorCode & ConsistListener::NOT_CONSIST_ADDR) != 0)
//                buffer.append("Address Not Conist Address ");
//    if ((ErrorCode & ConsistListener::DELETE_ERROR) != 0)
//                buffer.append("Delete Error ");
//    if ((ErrorCode & ConsistListener::STACK_FULL) != 0)
//                buffer.append("Stack Full ");

//    QString  retval = buffer;
//    if (retval==(""))
//       return "Unknown Status Code: " + ErrorCode;
//    else return retval;
//}

   /* request an update from the layout, loading
    * Consists from the command station.
    */
//   /*public*/ void DccConsistManager::requestUpdateFromLayout(){}

//    /*
//     * register a ConsistListListener object with this Consist
//     * Manager
//     * @param listener a Consist List Listener object.
//     */
//    /*public*/ void DccConsistManager::addConsistListListener(ConsistListListener* l){
//       changeListeners->append(l);
//       disconnect(this, SIGNAL(consistListChanged()), l, SLOT(notifyConsistListChanged()));

//    }

//    /*
//     * remove a ConsistListListener object with this Consist
//     * Manager
//     * @param listener a Consist List Listener object.
//     */
//    /*public*/ void DccConsistManager::removeConsistListListener(ConsistListListener* l){
//       changeListeners->removeAt(changeListeners->indexOf(l));
//       disconnect(this, SIGNAL(notifyConsistListChanged()), l, SLOT(notifyConsistListChanged()));
//    }

//    /*
//     * Notify the registered Consist List Listener objects that the
//     * Consist List has changed.
//     */
//    /*public*/ void DccConsistManager::notifyConsistListChanged()
//{
////       foreach(ConsistListListener* l, *changeListeners)
////           l->notifyConsistListChanged();
//       emit consistListChanged();
//    }
