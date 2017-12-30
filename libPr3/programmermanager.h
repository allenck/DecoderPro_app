#ifndef PROGRAMMERMANAGER_H
#define PROGRAMMERMANAGER_H

#include <QObject>
#include "programmer.h"
#include "addressedprogrammer.h"
#include "libPr3_global.h"
#include "addressedprogrammermanager.h"
#include "globalprogrammermanager.h"

class LIBPR3SHARED_EXPORT ProgrammerManager : public AddressedProgrammerManager
{
    Q_OBJECT
public:
    explicit ProgrammerManager(QObject *parent = 0) : AddressedProgrammerManager(parent) {}
#if 0 //@Deprecated
    /**
     * Gain access to the Global Mode Programmer without reservation.
     * @return null only if there isn't a Global Mode Programmer available
     * via this Manager.
     */
    virtual Programmer* getGlobalProgrammer() { return NULL;}
    /**
     * Gain access to a Addressed Mode Programmer without reservation.
     * @param pLongAddress true if this is a long (14 bit) address, else false
     * @param pAddress Specific decoder address to use.
     * @return null only if there isn't an Ops Mode Programmer in the system
     */
//    virtual Programmer* getAddressedProgrammer(bool /*pLongAddress*/, int /*pAddress*/) {return NULL;}
    /**
     * Gain access to the Global Mode Programmer, in the process reserving it
     * for yourself.
     * @return null if the existing Global Mode programmer is in use
     */
//    virtual Programmer* reserveGlobalProgrammer() {return NULL;}
    /**
     * Return access to the Global Mode Programmer, so that it can
     * be used elsewhere.
     */
    virtual void releaseGlobalProgrammer(Programmer* /*p*/) {}
    /**
     * Gain access to a (the) Addressed Mode Programmer, in the process
     * reserving it for yourself.
     * @param pLongAddress true if this is a long (14 bit) address, else false
     * @param pAddress Specific decoder address to use.
     * @return null if the address is in use by a reserved programmer
     */
    virtual AddressedProgrammer* reserveAddressedProgrammer(bool /*pLongAddress*/, int /*pAddress*/) {return NULL;}
    /**
     * Return access to the Global Mode Programmer, so that it can
     * be used elsewhere.
     */
    virtual void releaseAddressedProgrammer(Programmer* /*p*/) {}
    /**
     * Convenience method to check whether you'll be able to get
     * a Global Mode programmer.
     * @return false if there's no chance of getting one
     */
    virtual bool isGlobalProgrammerAvailable() {return false;}
    /**
     * Convenience method to check whether you'll be able to get
     * an Addressed Mode programmer.
     * @return false if there's no chance of getting one
     */
    virtual bool isAddressedModePossible() {return false;}

    virtual QString getUserName() {return "";}

signals:
    
public slots:
#endif
};

#endif // PROGRAMMERMANAGER_H
