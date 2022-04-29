#include "abstractmemorymanager.h"
#include "internalsystemconnectionmemo.h"
#include "loggerfactory.h"
AbstractMemoryManager::AbstractMemoryManager(InternalSystemConnectionMemo* memo, QObject *parent) :
    AbstractManager(memo, parent)
{
 lastAutoMemoryRef = 0;
 //registerSelf();
 setProperty("JavaClassName", "jmri.managers.AbstractMemoryManager");
}
/**
 * Abstract partial implementation of a MemoryManager.
 *
 * @author			Bob Jacobsen Copyright (C) 2004
 * @version			$Revision: 18102 $
 */
///*public*/ abstract class AbstractMemoryManager extends AbstractManager
//    implements MemoryManager {

/*public*/ int AbstractMemoryManager::getXMLOrder() const{
    return Manager::MEMORIES;
}

/*public*/ QChar AbstractMemoryManager::typeLetter() const { return 'M'; }


/** {@inheritDoc} */
//@Nonnull
//@Override
/*public*/ Memory* AbstractMemoryManager::provideMemory(/*@Nonnull*/ QString sName)
{
 if(sName.isEmpty())
  throw new IllegalArgumentException(tr("required memory name is null"));
 Memory* m = getMemory(sName);
 if (m != nullptr) {
     return m;
 }
 if (sName.startsWith(getSystemNamePrefix())) {
     return newMemory(sName, nullptr);
 } else {
     return newMemory(makeSystemName(sName), nullptr);
 }
}

/*public*/ Memory* AbstractMemoryManager::getMemory(QString sName)  {

    Memory* m = getByUserName(sName);
    if (m != nullptr) {
        return m;
    }
    return getBySystemName(sName);
}

/*public*/ Memory* AbstractMemoryManager::getBySystemName(QString name)  {
    NamedBean* nb = getBeanBySystemName(name);
    if(nb)
     return (Memory*)nb->self();
    return nullptr;
}

/*public*/ Memory* AbstractMemoryManager::getByUserName(QString key)  {
    NamedBean* nb = getBeanByUserName(key);
    if(nb)
     return (Memory*)nb->self();
    return nullptr;
}

/*public*/ Memory* AbstractMemoryManager::newMemory(QString systemName, QString userName)
{
    if (log->isDebugEnabled()) log->debug("new Memory:"
                                        +( (systemName==NULL) ? "NULL" : systemName)
                                        +";"+( (userName==NULL) ? "NULL" : userName));
    if (systemName == NULL){
        log->error("SystemName cannot be NULL. UserName was "
                +( (userName==NULL) ? "NULL" : userName));
        throw new IllegalArgumentException("SystemName cannot be NULL. UserName was "
                +( (userName==NULL) ? "NULL" : userName));
    }
    // return existing if there is one
    Memory* s;
    if ( (userName!=NULL) && ((s = getByUserName(userName)) != NULL)) {
        if (getBySystemName(systemName)!=s)
            log->error("inconsistent user ("+userName+") and system name ("+systemName+") results; userName related to ("+s->getSystemName()+")");
        return s;
    }
    if ( (s = getBySystemName(systemName)) != NULL) {
        if ((s->getUserName() == NULL) && (userName != NULL))
            s->setUserName(userName);
        else if (userName != NULL) log->warn("Found memory via system name ("+systemName
                                +") with non-NULL user name ("+userName+")");
        return s;
    }

    // doesn't exist, make a new one
    s = createNewMemory(systemName, userName);

    // if that failed, blame it on the input arguements
    if (s == NULL) throw new IllegalArgumentException();

    // save in the maps
    Register(s);

    //emit newMemoryCreated(s);

    /*The following keeps trace of the last created auto system name.
    currently we do not reuse numbers, although there is nothing to stop the
    user from manually recreating them*/
    if (systemName.startsWith("IM:AUTO:")){
        try {
            bool bOk=false;
            int autoNumber = /*Integer.parseInt(*/systemName.mid(8).toInt(&bOk);
            if(!bOk) throw  NumberFormatException();
            if (autoNumber > lastAutoMemoryRef)
            {
                lastAutoMemoryRef = autoNumber;
            }
        } catch (NumberFormatException* e){
            log->warn("Auto generated SystemName "+ systemName + " is not in the correct format");
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


/**
 * Internal method to invoke the factory, after all the
 * logic for returning an existing method has been invoked.
 * @return never NULL
 */
// /*abstract protected*/ Memory* AbstractMemoryManager::createNewMemory(QString systemName, QString userName);

/** {@inheritDoc} */
//@Override
//@Nonnull
/*public*/ QString AbstractMemoryManager::getBeanTypeHandled(bool plural) const{
    return (plural ? tr("Memories") : tr("Memory"));
}

//@Override
//@Nonnull
/*public*/ Memory* AbstractMemoryManager::provide(/*@Nonnull*/ QString name) /* throw (IllegalArgumentException)*/ {
    return provideMemory(name);
}


/*static*/ Logger* AbstractMemoryManager::log = LoggerFactory::getLogger("AbstractMemoryManager");
//}
