#include "connectionnamefromsystemname.h"
#include "instancemanager.h"
#include "dccmanufacturerlist.h"
#include "systemconnectionmemo.h"

//ConnectionNameFromSystemName::ConnectionNameFromSystemName(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Common utility method for returning the System Connection Name from
 * the System Name Prefix
 *
 * @author Kevin Dickerson  Copyright 2010
 * @version $Revision: 17977 $
 */
///*public*/ class ConnectionNameFromSystemName{

/**
 * Locates the connected systems name from a given prefix.
 * @param prefix
 * @return The Connection System Name
 */
/*static*/ /*public*/ QString ConnectionNameFromSystemName::getConnectionName(QString prefix)
{
 QObjectList* list
            = InstanceManager::getList("SystemConnectionMemo");
 if (list != NULL)
 {
   foreach (QObject* memo, *list)
   {
    if (((SystemConnectionMemo*)memo)->getSystemPrefix()==(prefix))
     return ((SystemConnectionMemo*)memo)->getUserName();
   }
  }
  //Fall through if the system isn't using the new SystemConnectionMemo registration
  return DCCManufacturerList::getDCCSystemFromType(prefix.at(0));
}
/*
 *  Returns the System prefix of a connection given the system name.
 */
/**
 * Locates the connected systems prefix from a given System name.
 * @param name
 * @return The system prefix
 */
/*static*/ /*public*/ QString ConnectionNameFromSystemName::getPrefixFromName(QString name)
{
 if (name==NULL)
        return NULL;
 QObjectList* list
            = InstanceManager::getList("SystemConnectionMemo");
 if (list != NULL)
 {

  foreach (QObject* memo, *list)
  {
   if (((SystemConnectionMemo*)memo)->getUserName()==(name))
   {
    return ((SystemConnectionMemo*)memo)->getSystemPrefix();
   }
  }
 }
 QString prefix = QString(DCCManufacturerList::getTypeFromDCCSystem(name));
    //Fall through if the system isn't using the new SystemConnectionMemo registration
 return prefix;

}
