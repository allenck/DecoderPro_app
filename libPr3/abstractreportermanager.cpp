#include "abstractreportermanager.h"
#include <QMessageBox>
#include "abstractreporter.h"

AbstractReporterManager::AbstractReporterManager(QObject *parent) :
    AbstractManager(parent)
{
 log = new Logger("AbstractReporterManager");
 registerSelf();
}
/**
 * Abstract partial implementation of a ReporterManager.
 *
 * @author			Bob Jacobsen Copyright (C) 2004
 * @version			$Revision: 21455 $
 */
//public abstract class AbstractReporterManager extends AbstractManager
//    implements ReporterManager {

int AbstractReporterManager::getXMLOrder(){
    return Manager::REPORTERS;
}

char AbstractReporterManager::typeLetter() { return 'R'; }

AbstractReporter* AbstractReporterManager::provideReporter(QString sName) {
    AbstractReporter* t = getReporter(sName);
    if (t!=NULL) return t;
    if (sName.startsWith(getSystemPrefix()+typeLetter()))
        return newReporter(sName, NULL);
    else
        return newReporter(makeSystemName(sName), NULL);
}

AbstractReporter* AbstractReporterManager::getReporter(QString name) {
    AbstractReporter* t = getByUserName(name);
    if (t!=NULL) return t;

    return getBySystemName(name);
}

AbstractReporter* AbstractReporterManager::getBySystemName(QString name) {
    return (AbstractReporter*)_tsys->value(name);
}

AbstractReporter* AbstractReporterManager::getByUserName(QString key) {
    return (AbstractReporter*)_tuser->value(key);
}

AbstractReporter* AbstractReporterManager::getByDisplayName(QString key) {
// First try to find it in the user list.
// If that fails, look it up in the system list
AbstractReporter* retv = this->getByUserName(key);
if (retv == NULL) {
    retv = this->getBySystemName(key);
}
// If it's not in the system list, go ahead and return NULL
return(retv);
}

AbstractReporter* AbstractReporterManager::newReporter(QString systemName, QString userName) throw(IllegalArgumentException) {
 if (log->isDebugEnabled()) log->debug(tr("new Reporter:")
                                        +( (systemName==NULL) ? "NULL" : systemName)
                                        +";"+( (userName==NULL) ? "NULL" : userName));
    if (systemName == NULL){
        log->error("SystemName cannot be NULL. UserName was "
                +( (userName==NULL) ? "NULL" : userName));
        throw new IllegalArgumentException("SystemName cannot be NULL. UserName was "
                +( (userName==NULL) ? "NULL" : userName));
    }
    // return existing if there is one
    AbstractReporter* r;
    if ( (userName!=NULL) && ((r = getByUserName(userName)) != NULL)) {
        if (getBySystemName(systemName)!=r)
            log->error("inconsistent user ("+userName+") and system name ("+systemName+") results; userName related to ("+r->getSystemName()+")");
        return r;
    }
    if ( (r = getBySystemName(systemName)) != NULL) {
        if ((r->getUserName() == NULL) && (userName != NULL))
            r->setUserName(userName);
        else if (userName != NULL) log->warn("Found reporter via system name ("+systemName
                                +") with non-NULL user name ("+userName+")");
        return r;
    }

    // doesn't exist, make a new one
    r = createNewReporter(systemName, userName);

    emit newReporterCreated(this, r);
    // save in the maps
    Register(r);


    // if that failed, blame it on the input arguements
    if (r == NULL) throw new IllegalArgumentException();

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

bool AbstractReporterManager::allowMultipleAdditions(QString systemName) { return false;  }

QString AbstractReporterManager::getNextValidAddress(QString curAddress, QString prefix)
{
 //If the hardware address past does not already exist then this can
 //be considered the next valid address.
 AbstractReporter* r = getBySystemName(prefix+typeLetter()+curAddress);
 if(r==NULL)
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

 //Check to determine if the systemName is in use, return NULL if it is,
 //otherwise return the next valid address.
 r = getBySystemName(prefix+typeLetter()+QString("%1").arg(iName));
 if(r!=NULL)
 {
  for(int x = 1; x<10; x++)
  {
   iName++;
   r = getBySystemName(prefix+typeLetter()+QString("%1").arg(iName));
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
/*private*/ AbstractReporter* AbstractReporterManager::createNewReporter(QString systemName, QString userName)
{
 AbstractReporter* reporter = new AbstractReporter(systemName, userName);
 return (AbstractReporter*)reporter;
//  {
//            public int getState() { return state; }
//            public void setState(int s) { state = s; }
//            int state = 0;
//        };
}
