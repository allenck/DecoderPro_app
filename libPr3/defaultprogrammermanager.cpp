#include "defaultprogrammermanager.h"
#include "programmingmode.h"
#include "programmer.h"
#include "loggerfactory.h"

/**
 * Provides a very-basic implementation of ProgrammerManager.  You give it
 * a service-mode Programmer at construction time; Ops Mode requests
 * get a null in response.
 *
 * @see             jmri.ProgrammerManager
 * @author			Bob Jacobsen Copyright (C) 2001
 * @version			$Revision: 18841 $
 */
// For the record, these were the original numerical definitions:
    //     public static final ProgrammingMode NONE	    =  new ProgrammingMode("NONE", 0);
    //     public static final ProgrammingMode REGISTERMODE    = new ProgrammingMode("REGISTERMODE", 11);
    //     public static final ProgrammingMode PAGEMODE        = new ProgrammingMode("PAGEMODE", 21);
    //     public static final ProgrammingMode DIRECTBITMODE   = new ProgrammingMode("DIRECTBITMODE", 31);
    //     public static final ProgrammingMode DIRECTBYTEMODE  = new ProgrammingMode("DIRECTBYTEMODE", 32);
    //     public static final ProgrammingMode ADDRESSMODE     = new ProgrammingMode("ADDRESSMODE", 41);
    //     public static final ProgrammingMode OPSBYTEMODE     = new ProgrammingMode("OPSBYTEMODE", 101);
    //     public static final ProgrammingMode OPSBITMODE      = new ProgrammingMode("OPSBITMODE", 102);
    //     public static final ProgrammingMode OPSACCBYTEMODE  = new ProgrammingMode("OPSACCBYTEMODE", 111);
    //     public static final ProgrammingMode OPSACCBITMODE   = new ProgrammingMode("OPSACCBITMODE", 112);
    //     public static final ProgrammingMode OPSACCEXTBYTEMODE = new ProgrammingMode("OPSACCEXTBYTEMODE", 121);
    //     public static final ProgrammingMode OPSACCEXTBITMODE  = new ProgrammingMode("OPSACCEXTBITMODE", 122);
/**
 * Constructor when no global programmer is available.
 */
DefaultProgrammerManager::DefaultProgrammerManager(QObject* parent) :QObject(parent)
{
 setObjectName("DefaultProgrammerManager");
 programmer = NULL;
 userName = "<Default>";

}
/**
 * Constructor with a programmer.
 *
 * @param programmer the programmer to use; if null, acts as if no
 *                   programmer is available
 */
/*public*/ DefaultProgrammerManager::DefaultProgrammerManager(Programmer* pProgrammer, QObject* parent)
    : QObject(parent)
{
 programmer = pProgrammer;
 userName = "<Default>";
}
/**
 * Constructor with a programmer and associated connection.
 *
 * @param programmer the programmer to use; if null, acts as if no
 *                   programmer is available
 * @param memo       the associated connection
 */
/*public*/ DefaultProgrammerManager::DefaultProgrammerManager(Programmer* pProgrammer, SystemConnectionMemo* memo, QObject* parent)
    : QObject(parent)
{
 //this(pProgrammer);
 programmer = pProgrammer;
 this->userName = memo->getUserName();
}

/**
 * Provides the human-readable representation for including
 * ProgrammerManagers directly in user interface components, so it should
 * return a user-provided name for this particular one.
 */
//@Override
/*public*/ QString DefaultProgrammerManager::getUserName() {
    return userName;
}

/**
 * Provides the human-readable representation for including
 * ProgrammerManagers directly in user interface components, so it should
 * return a user-provided name for this particular one.
 */
//@Override
/*public*/ QString DefaultProgrammerManager::toString() {
    return getUserName();
}

/*public*/ Programmer* DefaultProgrammerManager::getGlobalProgrammer()
{
 if (log->isDebugEnabled()) log->debug(tr("return default service-mode programmer of type %1").arg(programmer->self() != NULL ? programmer->self()->metaObject()->className() : "(null)"));
  return programmer;
}

/*public*/ AddressedProgrammer* DefaultProgrammerManager::getAddressedProgrammer(bool pLongAddress, int pAddress) {
Q_UNUSED(pLongAddress)
Q_UNUSED(pAddress)
    return NULL;
}

/*public*/ Programmer* DefaultProgrammerManager::reserveGlobalProgrammer() {
    return programmer;
}

/*public*/ void DefaultProgrammerManager::releaseGlobalProgrammer(Programmer* p) {
Q_UNUSED(p)
}

/*public*/ AddressedProgrammer* DefaultProgrammerManager::reserveAddressedProgrammer(bool pLongAddress, int pAddress) {
Q_UNUSED(pAddress)
Q_UNUSED(pLongAddress)
return NULL;
}

/*public*/ void DefaultProgrammerManager::releaseAddressedProgrammer(AddressedProgrammer* p) {
Q_UNUSED(p)
}

/**
 * Default programmer does not provide Ops Mode
 * @return false if there's no chance of getting one
 */
/*public*/ bool DefaultProgrammerManager::isAddressedModePossible()
{
 return false;
}
/**
 * {@inheritDoc}
 *
 * @return always false in this implementation
 */
//@Override
/*public*/ bool DefaultProgrammerManager::isAddressedModePossible(/*@Nonnull*/ DccLocoAddress* l) {
    return isAddressedModePossible();
}

/**
 * Allow for implementations that do not support Service mode programming
 * @return false if there's no chance of getting one
 */
/*public*/ bool DefaultProgrammerManager::isGlobalProgrammerAvailable() {return true;}

/**
 * {@inheritDoc}
 *
 * @return a default list of programming modes that most
 *         {@link jmri.AddressedProgrammer}s make available
 */
//@Override
/*public*/ QList<QString> DefaultProgrammerManager::getDefaultModes()
{
    QList<QString> retval = QList<QString>();
    retval.append("OPSBYTEMODE");
    return retval;
}


/*private*/ /*static*/ Logger* DefaultProgrammerManager::log = LoggerFactory::getLogger("DefaultProgrammerManager");
