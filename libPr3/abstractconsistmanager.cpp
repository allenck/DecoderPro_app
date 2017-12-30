#include "abstractconsistmanager.h"

AbstractConsistManager::AbstractConsistManager(QObject *parent) /*:
    ConsistManager(parent)*/
{
    consistTable = new QHash<DccLocoAddress*,Consist*>();
    consistList = new QList<DccLocoAddress*>();
    ChangeListeners = new QList<ConsistListListener*>();

}
/**
 * An Abstract Consist Manager on top of which
 * system specific consist managers can be built.
 *
 * @author                Paul Bender Copyright (C) 2004
 * @version               $Revision: 20642 $
 */
//abstract public class AbstractConsistManager implements jmri.ConsistManager{



//    public AbstractConsistManager(){
//          consistTable = new Hashtable<DccLocoAddress,Consist>();
//          consistList = new ArrayList<DccLocoAddress>();
//              ChangeListeners = new ArrayList<ConsistListListener>();
//    }

/**
*    Find a Consist with this consist address, and return it.
**/
/*public*/ Consist* AbstractConsistManager::getConsist(DccLocoAddress* address){
 if(consistTable->contains(address)) {
    return(consistTable->value(address));
 } else {
    return(addConsist(address));
 }
}

/**
*     Add a new Consist with the given address to the consistTable/consistList
**/
//abstract public Consist addConsist(DccLocoAddress address);

// remove the old Consist
/*public*/ void AbstractConsistManager::delConsist(DccLocoAddress* address){
 consistTable->remove(address);
 consistList->removeAt(consistList->indexOf(address));
}

/**
 *    Does this implementation support a command station consist?
 **/
///*abstract public*/ bool AbstractConsistManager::isCommandStationConsistPossible();

/**
 *    Does a CS consist require a seperate consist address?
*    (or is the lead loco to be used for the consist address)
 **/
//abstract public bool csConsistNeedsSeperateAddress();

/**
*  Return the list of consists we know about.
**/
/*public*/ QList<DccLocoAddress*>* AbstractConsistManager::getConsistList() { return consistList; }

/*public*/ QString AbstractConsistManager::decodeErrorCode(int ErrorCode){
 QString buffer;
 if ((ErrorCode & ConsistListener::NotImplemented) != 0)
            buffer.append("Not Implemented ");
 if ((ErrorCode & ConsistListener::OPERATION_SUCCESS) != 0)
            buffer.append("Operation Completed Successfully ");
 if ((ErrorCode & ConsistListener::CONSIST_ERROR) != 0)
            buffer.append("Consist Error ");
 if ((ErrorCode & ConsistListener::LOCO_NOT_OPERATED) != 0)
            buffer.append("Address not controled by this device.");
 if ((ErrorCode & ConsistListener::ALREADY_CONSISTED) != 0)
            buffer.append("Locomotive already consisted");
 if ((ErrorCode & ConsistListener::NOT_CONSISTED) != 0)
            buffer.append("Locomotive Not Consisted ");
 if ((ErrorCode & ConsistListener::NONZERO_SPEED) != 0)
            buffer.append("Speed Not Zero ");
 if ((ErrorCode & ConsistListener::NOT_CONSIST_ADDR) != 0)
            buffer.append("Address Not Conist Address ");
 if ((ErrorCode & ConsistListener::DELETE_ERROR) != 0)
            buffer.append("Delete Error ");
 if ((ErrorCode & ConsistListener::STACK_FULL) != 0)
            buffer.append("Stack Full ");

 QString  retval = buffer/*.toString()*/;
 if (retval.isEmpty())
   return "Unknown Status Code: " + QString("%1").arg(ErrorCode);
 else return retval;
}

/* request an update from the layout, loading
* Consists from the command station.
*/
/*public*/ void AbstractConsistManager::requestUpdateFromLayout(){}

/*
 * register a ConsistListListener object with this Consist
 * Manager
 * @param listener a Consist List Listener object.
 */
/*public*/ void AbstractConsistManager::addConsistListListener(ConsistListListener* l){
   ChangeListeners->append(l);
}

/*
 * remove a ConsistListListener object with this Consist
 * Manager
 * @param listener a Consist List Listener object.
 */
/*public*/ void AbstractConsistManager::removeConsistListListener(ConsistListListener* l){
   ChangeListeners->removeAt(ChangeListeners->indexOf(l));
}

/*
 * Notify the registered Consist List Listener objects that the
 * Consist List has changed.
 */
/*public*/ void AbstractConsistManager::notifyConsistListChanged()
{
#if 0
   foreach(ConsistListListener* l ,*ChangeListeners)
       l->notifyConsistListChanged();
#else
 emit consistListChanged();
#endif
}
