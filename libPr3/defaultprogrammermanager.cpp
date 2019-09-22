#include "defaultprogrammermanager.h"
#include "programmingmode.h"
#include "programmer.h"

DefaultProgrammerManager::DefaultProgrammerManager(QObject* parent) :ProgrammerManager(parent)
{
 setObjectName("DefaultProgrammerManager");
 mProgrammer = NULL;
}

/**
 * Provides a very-basic implementation of ProgrammerManager.  You give it
 * a service-mode Programmer at construction time; Ops Mode requests
 * get a null in response.
 *
 * @see             jmri.ProgrammerManager
 * @author			Bob Jacobsen Copyright (C) 2001
 * @version			$Revision: 18841 $
 */
//public class DefaultProgrammerManager implements ProgrammerManager {
/**
 * NMRA "Paged" mode
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::PAGEMODE =  new ProgrammingMode("PAGEMODE");

/**
 * NMRA "Operations" or "Programming on the main" mode, using only the bit-wise operations
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::OPSBITMODE = new ProgrammingMode("OPSBITMODE");

/**
 * NMRA "Programming on the main" mode for stationary decoders,
 * using only the byte-wise operations and "extended" addressing.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::OPSACCEXTBYTEMODE = new ProgrammingMode("OPSACCEXTBYTEMODE");

/**
 * NMRA "Programming on the main" mode for stationary decoders,
 * using only the bit-wise operations. Note that this is
 * defined as using the "normal", not "extended" addressing.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::OPSACCBITMODE =  new ProgrammingMode("OPSACCBITMODE");

/**
 * NMRA "Programming on the main" mode for stationary decoders,
 * using only the bit-wise operations and "extended" addressing.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::OPSACCEXTBITMODE =  new ProgrammingMode("OPSACCEXTBITMODE");

/**
 * NMRA "Programming on the main" mode for stationary decoders,
 * using only the byte-wise operations. Note that this is
 * defined as using the "normal", not "extended" addressing.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::OPSACCBYTEMODE =  new ProgrammingMode("OPSACCBYTEMODE");

///**
// * No programming mode available
// */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::NONE =  new ProgrammingMode("NONE");

/**
 * NMRA "Address-only" mode. Often implemented as
 * a proper subset of "Register" mode, as the
 * underlying operation is the same.
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::ADDRESSMODE = new ProgrammingMode("ADDRESSMODE");

/**
 * NMRA "Operations" or "Programming on the main" mode, using only the byte-wise operations
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::OPSBYTEMODE =  new ProgrammingMode("OPSBYTEMODE");

/**
 * NMRA "Direct" mode, using only the byte-wise operations
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::DIRECTBYTEMODE =  new ProgrammingMode("DIRECTBYTEMODE");

/**
 * NMRA "Register" mode
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::REGISTERMODE =  new ProgrammingMode("REGISTERMODE");

/**
 * NMRA "Direct" mode, using only the bit-wise operations
 */
/*public*/ /*static*/ /*final*/ ProgrammingMode* DefaultProgrammerManager::DIRECTBITMODE =  new ProgrammingMode("DIRECTBITMODE");

/*public*/ DefaultProgrammerManager::DefaultProgrammerManager(Programmer* pProgrammer, QObject* parent)
    : ProgrammerManager(parent)
{
 mProgrammer = pProgrammer;
 userName = "Internal";
}

/*public*/ DefaultProgrammerManager::DefaultProgrammerManager(Programmer* pProgrammer, SystemConnectionMemo* memo, QObject* parent)
    : ProgrammerManager(parent)
{
 //this(pProgrammer);
 mProgrammer = pProgrammer;
 userName = "Internal";

 this->userName = memo->getUserName();
}


/*public*/ QString DefaultProgrammerManager::getUserName() { return userName; }

/*public*/ Programmer* DefaultProgrammerManager::getGlobalProgrammer()
{
 if (log.isDebugEnabled()) log.debug(tr("return default service-mode programmer of type %1").arg(mProgrammer != NULL ? mProgrammer->metaObject()->className() : "(null)"));
  return mProgrammer;
}
/*public*/ AddressedProgrammer* DefaultProgrammerManager::getAddressedProgrammer(bool pLongAddress, int pAddress) {
Q_UNUSED(pLongAddress)
Q_UNUSED(pAddress)
    return NULL;
}

/*public*/ Programmer* DefaultProgrammerManager::reserveGlobalProgrammer() {
    return mProgrammer;
}
/*public*/ void DefaultProgrammerManager::releaseGlobalProgrammer(Programmer* p) {
Q_UNUSED(p)
}

/*public*/ AddressedProgrammer* DefaultProgrammerManager::reserveAddressedProgrammer(bool pLongAddress, int pAddress) {
Q_UNUSED(pAddress)
Q_UNUSED(pLongAddress)
return NULL;
}

/*public*/ void DefaultProgrammerManager::releaseAddressedProgrammer(Programmer* p) {
Q_UNUSED(p)
}

/**
 * Default programmer does not provide Ops Mode
 * @return false if there's no chance of getting one
 */
/*public*/ bool DefaultProgrammerManager::isAddressedModePossible() {return false;}

/**
 * Allow for implementations that do not support Service mode programming
 * @return false if there's no chance of getting one
 */
/*public*/ bool DefaultProgrammerManager::isGlobalProgrammerAvailable() {return true;}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultProgrammerManager.class.getName());
