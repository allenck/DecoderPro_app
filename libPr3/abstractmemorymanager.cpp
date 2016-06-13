#include "abstractmemorymanager.h"

AbstractMemoryManager::AbstractMemoryManager(QObject *parent) :
    MemoryManager(parent)
{
 lastAutoMemoryRef = 0;
 registerSelf();
}
/**
 * Abstract partial implementation of a MemoryManager.
 *
 * @author			Bob Jacobsen Copyright (C) 2004
 * @version			$Revision: 18102 $
 */
///*public*/ abstract class AbstractMemoryManager extends AbstractManager
//    implements MemoryManager {

/*public*/ int AbstractMemoryManager::getXMLOrder(){
    return Manager::MEMORIES;
}

/*public*/ char AbstractMemoryManager::typeLetter() { return 'M'; }

/*public*/ Memory* AbstractMemoryManager::provideMemory(QString sName)
{
 Memory* t = getMemory(sName);
 if (t!=NULL) return t;
 if (sName.startsWith(getSystemPrefix()+typeLetter()))
  return newMemory(sName, NULL);
 else
  return newMemory(makeSystemName(sName), NULL);
}

/*public*/ Memory* AbstractMemoryManager::getMemory(QString name) {
    Memory* t = getByUserName(name);
    if (t!=NULL) return t;

    return getBySystemName(name);
}

/*public*/ Memory* AbstractMemoryManager::getBySystemName(QString name) {
    return (Memory*)_tsys->value(name);
}

/*public*/ Memory* AbstractMemoryManager::getByUserName(QString key) {
    return (Memory*)_tuser->value(key);
}

/*public*/ Memory* AbstractMemoryManager::newMemory(QString systemName, QString userName)
{
    if (log.isDebugEnabled()) log.debug("new Memory:"
                                        +( (systemName==NULL) ? "NULL" : systemName)
                                        +";"+( (userName==NULL) ? "NULL" : userName));
    if (systemName == NULL){
        log.error("SystemName cannot be NULL. UserName was "
                +( (userName==NULL) ? "NULL" : userName));
        throw new IllegalArgumentException("SystemName cannot be NULL. UserName was "
                +( (userName==NULL) ? "NULL" : userName));
    }
    // return existing if there is one
    Memory* s;
    if ( (userName!=NULL) && ((s = getByUserName(userName)) != NULL)) {
        if (getBySystemName(systemName)!=s)
            log.error("inconsistent user ("+userName+") and system name ("+systemName+") results; userName related to ("+s->getSystemName()+")");
        return s;
    }
    if ( (s = getBySystemName(systemName)) != NULL) {
        if ((s->getUserName() == NULL) && (userName != NULL))
            s->setUserName(userName);
        else if (userName != NULL) log.warn("Found memory via system name ("+systemName
                                +") with non-NULL user name ("+userName+")");
        return s;
    }

    // doesn't exist, make a new one
    s = createNewMemory(systemName, userName);

    // if that failed, blame it on the input arguements
    if (s == NULL) throw new IllegalArgumentException();

    // save in the maps
    Register(s);

    emit newMemoryCreated(s);

    /*The following keeps trace of the last created auto system name.
    currently we do not reuse numbers, although there is nothing to stop the
    user from manually recreating them*/
    if (systemName.startsWith("IM:AUTO:")){
        try {
            bool bOk=false;
            int autoNumber = /*Integer.parseInt(*/systemName.mid(8).toInt(&bOk);
            if(!bOk) throw new NumberFormatException();
            if (autoNumber > lastAutoMemoryRef)
            {
                lastAutoMemoryRef = autoNumber;
            }
        } catch (NumberFormatException e){
            log.warn("Auto generated SystemName "+ systemName + " is not in the correct format");
        }
    }
    return s;
}

/*public*/ Memory* AbstractMemoryManager::newMemory(QString userName)
{
    int nextAutoMemoryRef = lastAutoMemoryRef+1;
    QString b =  QString("IM:AUTO:");
    //QString nextNumber = paddedNumber.format(nextAutoMemoryRef);
    QString s = QString("%1").arg(nextAutoMemoryRef);
    QString nextNumber = QString("0000").mid(4-s.length());
    b.append(nextNumber);
    return newMemory(b/*.toQString()*/, userName);
}

//DecimalFormat paddedNumber = new DecimalFormat("0000");

int lastAutoMemoryRef = 0;

/**
 * Internal method to invoke the factory, after all the
 * logic for returning an existing method has been invoked.
 * @return never NULL
 */
/*abstract protected*/ Memory* createNewMemory(QString systemName, QString userName);

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractMemoryManager.class.getName());
//}
