#ifndef ADDRESSEDPROGRAMMERTESTBASE_H
#define ADDRESSEDPROGRAMMERTESTBASE_H
#include "programmertestbase.h"

class AddressedProgrammerTestBase : public ProgrammerTestBase
{
    Q_OBJECT
public:
    AddressedProgrammerTestBase();
    /*public*/ void testDefault();
    /*public*/ void testGetCanRead();
    /*public*/ void testSetGetMode();
    /*public*/ void testGetLongAddress();
    /*public*/ void testGetAddressNumber();
    /*public*/ void testGetAddress();
};

#endif // ADDRESSEDPROGRAMMERTESTBASE_H
