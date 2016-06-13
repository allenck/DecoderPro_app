#ifndef DEFAULTPROGRAMMERMANAGER_H
#define DEFAULTPROGRAMMERMANAGER_H
#include "programmermanager.h"
#include "systemconnectionmemo.h"

class DefaultProgrammerManager : public ProgrammerManager
{
public:
    /**
     * NMRA "Paged" mode
     */
    /*public*/ static /*final*/ ProgrammingMode* PAGEMODE;// = new ProgrammingMode("PAGEMODE");

    /**
     * NMRA "Operations" or "Programming on the main" mode, using only the bit-wise operations
     */
    /*public*/ static /*final*/ ProgrammingMode* OPSBITMODE;// = new ProgrammingMode("OPSBITMODE");

    /**
     * NMRA "Programming on the main" mode for stationary decoders,
     * using only the byte-wise operations and "extended" addressing.
     */
    /*public*/ static /*final*/ ProgrammingMode* OPSACCEXTBYTEMODE;// = new ProgrammingMode("OPSACCEXTBYTEMODE");

    /**
     * NMRA "Programming on the main" mode for stationary decoders,
     * using only the bit-wise operations. Note that this is
     * defined as using the "normal", not "extended" addressing.
     */
    /*public*/ static /*final*/ ProgrammingMode* OPSACCBITMODE;// = new ProgrammingMode("OPSACCBITMODE");

    /**
     * NMRA "Programming on the main" mode for stationary decoders,
     * using only the bit-wise operations and "extended" addressing.
     */
    /*public*/ static /*final*/ ProgrammingMode* OPSACCEXTBITMODE;// = new ProgrammingMode("OPSACCEXTBITMODE");

    /**
     * NMRA "Programming on the main" mode for stationary decoders,
     * using only the byte-wise operations. Note that this is
     * defined as using the "normal", not "extended" addressing.
     */
    /*public*/ static /*final*/ ProgrammingMode* OPSACCBYTEMODE;// = new ProgrammingMode("OPSACCBYTEMODE");

    /**
     * No programming mode available
     */
    /*public*/ static /*final*/ ProgrammingMode* NONE;// = new ProgrammingMode("NONE");

    /**
     * NMRA "Address-only" mode. Often implemented as
     * a proper subset of "Register" mode, as the
     * underlying operation is the same.
     */
    /*public*/ static /*final*/ ProgrammingMode* ADDRESSMODE;// = new ProgrammingMode("ADDRESSMODE");

    /**
     * NMRA "Operations" or "Programming on the main" mode, using only the byte-wise operations
     */
    /*public*/ static /*final*/ ProgrammingMode* OPSBYTEMODE;// = new ProgrammingMode("OPSBYTEMODE");

    /**
     * NMRA "Direct" mode, using only the byte-wise operations
     */
    /*public*/ static /*final*/ ProgrammingMode* DIRECTBYTEMODE;// = new ProgrammingMode("DIRECTBYTEMODE");

    /**
     * NMRA "Register" mode
     */
    /*public*/ static /*final*/ ProgrammingMode* REGISTERMODE;// = new ProgrammingMode("REGISTERMODE");

    /**
     * NMRA "Direct" mode, using only the bit-wise operations
     */
    /*public*/ static /*final*/ ProgrammingMode* DIRECTBITMODE;// = new ProgrammingMode("DIRECTBITMODE");

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
    DefaultProgrammerManager(QObject* parent = 0);
    /*public*/ DefaultProgrammerManager(Programmer* pProgrammer,QObject* parent = 0);
    /*public*/ DefaultProgrammerManager(Programmer* pProgrammer, SystemConnectionMemo* memo,QObject* parent = 0);
    /*public*/ QString getUserName();
    /*public*/ Programmer* getGlobalProgrammer();
    /*public*/ virtual Programmer* getAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ Programmer* reserveGlobalProgrammer();
    /*public*/ void releaseGlobalProgrammer(Programmer* p);
    /*public*/ AddressedProgrammer* reserveAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ void releaseAddressedProgrammer(Programmer* p);
    /**
     * Default programmer does not provide Ops Mode
     * @return false if there's no chance of getting one
     */
    /*public*/ bool isAddressedModePossible();

    /**
     * Allow for implementations that do not support Service mode programming
     * @return false if there's no chance of getting one
     */
    /*public*/ bool isGlobalProgrammerAvailable();

private:
    /*private*/ Programmer* mProgrammer;
    QString userName;// = "Internal";
Logger log;
};

#endif // DEFAULTPROGRAMMERMANAGER_H
