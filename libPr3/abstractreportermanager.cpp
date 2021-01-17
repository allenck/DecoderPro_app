#include "abstractreportermanager.h"
#include <QMessageBox>
#include "reportermanager.h"
#include "loggerfactory.h"

AbstractReporterManager::AbstractReporterManager(SystemConnectionMemo* memo, QObject *parent) :
    ReporterManager(memo, parent)
{
 setProperty("JavaClassName", "jmri.managers.AbstractReporterManager");

 //registerSelf();
}

/**
 * Abstract partial implementation of a ReporterManager.
 *
 * @author			Bob Jacobsen Copyright (C) 2004
 * @version			$Revision: 21455 $
 */
//public abstract class AbstractReporterManager extends AbstractManager
//    implements ReporterManager {

int AbstractReporterManager::getXMLOrder() const{
    return Manager::REPORTERS;
}

char AbstractReporterManager::typeLetter() const  { return 'R'; }

Reporter* AbstractReporterManager::provideReporter(QString sName) {
    Reporter* t = getReporter(sName);
    if (t!=nullptr) return t;
    if (sName.startsWith(getSystemPrefix()+typeLetter()))
        return newReporter(sName, nullptr);
    else
        return newReporter(makeSystemName(sName), "");
}

Reporter* AbstractReporterManager::getReporter(QString name) const {
    Reporter* t = (Reporter*)getByUserName(name);
    if (t!=nullptr) return t;

    return (Reporter*)getBySystemName(name);
}
#if 1
NamedBean *AbstractReporterManager::getBySystemName(QString name) const
{
    return (Reporter*)_tsys->value(name);
}

NamedBean *AbstractReporterManager::getByUserName(QString key) const{
    return _tuser->value(key);
}
#endif
/** {@inheritDoc} */
//@Override
/*public*/ QString AbstractReporterManager::getBeanTypeHandled(bool plural) const {
    return (plural ? tr("Reporters") : tr("Reporter"));
}

Reporter* AbstractReporterManager::getByDisplayName(QString key) const {
// First try to find it in the user list.
// If that fails, look it up in the system list
Reporter* retv = (Reporter*)this->getByUserName(key);
if (retv == nullptr) {
    retv = (Reporter*)this->getBySystemName(key);
}
// If it's not in the system list, go ahead and return NULL
return(retv);
}

Reporter* AbstractReporterManager::newReporter(QString systemName, QString userName) const throw(IllegalArgumentException) {
 if (log->isDebugEnabled()) log->debug(tr("new Reporter:")
                                        +( (systemName==NULL) ? "NULL" : systemName)
                                        +";"+( (userName==NULL) ? "NULL" : userName));
    if (systemName == NULL){
        log->error("SystemName cannot be NULL. UserName was "
                +( (userName==NULL) ? "NULL" : userName));
        throw  IllegalArgumentException("SystemName cannot be NULL. UserName was "
                +( (userName==NULL) ? "NULL" : userName));
    }
    // return existing if there is one
    Reporter* r;
    if ( (userName!=NULL) && ((r = (Reporter*)getByUserName(userName)) != NULL)) {
        if (getBySystemName(systemName)!=r)
            log->error("inconsistent user ("+userName+") and system name ("+systemName+") results; userName related to ("+r->getSystemName()+")");
        return r;
    }
    if ( (r = (Reporter*)getBySystemName(systemName)) != NULL) {
        if ((r->getUserName() == NULL) && (userName != NULL))
            r->setUserName(userName);
        else if (userName != NULL) log->warn("Found reporter via system name ("+systemName
                                +") with non-NULL user name ("+userName+")");
        return r;
    }

    // doesn't exist, make a new one
    r = createNewReporter(systemName, userName);

    //emit newReporterCreated(this, r);
    // save in the maps
    Register(r);


    // if that failed, blame it on the input arguements
    if (r == nullptr) throw  IllegalArgumentException();

    return r;
}

/**
 * Internal method to invoke the factory, after all the
 * logic for returning an existing method has been invoked.
 * @return never NULL
 */
//abstract protected Reporter createNewReporter(QString systemName, QString userName);

/**
* A temporary method that determines if it is possible to add a range
* of turnouts in numerical order eg 10 to 30
**/

bool AbstractReporterManager::allowMultipleAdditions(QString systemName) const { return false;  }

QString AbstractReporterManager::getNextValidAddress(QString curAddress, QString prefix) const
{
 //If the hardware address past does not already exist then this can
 //be considered the next valid address.
 Reporter* r = (Reporter*)getBySystemName(prefix+'R'+curAddress);
 if(r==nullptr)
 {
  return curAddress;
 }

 // This bit deals with handling the curAddress, and how to get the next address.
 int iName = 0;
//        try {
//            iName = Integer.parseInt(curAddress);
//        } catch (NumberFormatException ex) {
//            log->error("Unable to convert " + curAddress + " Hardware Address to a number");
//            jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class).
//                                showInfoMessage("Error","Unable to convert " + curAddress + " to a valid Hardware Address",""+ex, "",true, false, org.apache.log4j.Level.ERROR);
//            return NULL;
//        }
 bool bOk=false;
 iName = curAddress.toInt(&bOk);
 if(!bOk)
 {
  log->error("Unable to convert " + curAddress + " Hardware Address to a number");
  QMessageBox::critical(0,tr("Error"), QString(tr("Unable to convert %1 to a valid hardware address")).arg(curAddress));
  return NULL;
 }

 char tl = 'R';
 //Check to determine if the systemName is in use, return NULL if it is,
 //otherwise return the next valid address.
 r = (Reporter*)getBySystemName(prefix+tl+QString("%1").arg(iName));
 if(r!=NULL)
 {
  for(int x = 1; x<10; x++)
  {
   iName++;
   r = (Reporter*)getBySystemName(prefix+'R'+QString("%1").arg(iName));
   if(r==NULL)
    return QString("%1").arg(iName);
  }
  return NULL;
 }
 else
 {
  return QString("%1").arg(iName);
 }
}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractReporterManager.class.getName());
// Utility method to create a concrete AbstractReporter
///*private*/ Reporter* AbstractReporterManager::createNewReporter(QString systemName, QString userName)
//{
// Reporter* reporter = new Reporter(systemName, userName);
// return (Reporter*)reporter;
//  {
//            public int getState() { return state; }
//            public void setState(int s) { state = s; }
//            int state = 0;
//        };
//}
/*private*/ /*final*/ /*static*/ Logger* AbstractReporterManager::log = LoggerFactory::getLogger("AbstractReporterManager");
