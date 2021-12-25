#ifndef LNOPSMODEPROGRAMMERTEST_H
#define LNOPSMODEPROGRAMMERTEST_H
#include "addressedprogrammertestbase.h"
#include "junitutil.h"
#include "proglistenerscaffold.h"


class LocoNetInterfaceScaffold;
class SlotManager;
class LocoNetSystemConnectionMemo;
class ProgListenerScaffold;
class LnOpsModeProgrammer;
class LnOpsModeProgrammerTest : public AddressedProgrammerTestBase
{
    Q_OBJECT
public:
    LnOpsModeProgrammerTest();
    Q_INVOKABLE/*public*/ void setUp();
    Q_INVOKABLE/*public*/ void tearDown();
public slots:
    /*public*/ void testGetCanWriteAddress();
    /*public*/ void testSetMode();
    /*public*/ void testGetMode();
    /*public*/ void testGetCanReadWithTransponding();
    /*public*/ void testSV2DataBytes();
    /*public*/ void testSV2highBits();
     /*public*/ void testSOps16001Read() throw (ProgrammerException);
     /*public*/ void testSv1Write() throw (ProgrammerException);
     /*public*/ void testBoardRead0() throw (ProgrammerException);
     /*public*/ void testBoardRead1() throw (ProgrammerException);
     /*public*/ void testBoardReadTimeout() throw (ProgrammerException);
     /*public*/ void testBoardWrite() throw (ProgrammerException);
     /*public*/ void testBoardWriteTimeout() throw (ProgrammerException);
     /*public*/ void testSv1ARead() throw (ProgrammerException);
     /*public*/ void testSv1BRead() throw (ProgrammerException);
     /*public*/ void testSv2Write() throw (ProgrammerException);
     /*public*/ void testSv2Read() throw (ProgrammerException);
     /*public*/ void testOpsReadDecoderTransponding() throw (ProgrammerException);
     /*public*/ void testOpsReadLocoNetMode() throw (ProgrammerException);

private:
    LocoNetInterfaceScaffold* lnis;
    SlotManager* sm;
    LocoNetSystemConnectionMemo* memo;
    ProgListenerScaffold* pl;
    LnOpsModeProgrammer* lnopsmodeprogrammer;

    friend class ReleaseUntil05;
};

class ReleaseUntil05 : public ReleaseUntil
{
    Q_OBJECT
    LnOpsModeProgrammerTest* lompt;
public:
    ReleaseUntil05(LnOpsModeProgrammerTest* lompt) {this->lompt = lompt;}
    bool ready() /*throw (Exception)*/
 {return lompt->pl->getRcvdInvoked() == 1;}
};

#endif // LNOPSMODEPROGRAMMERTEST_H
