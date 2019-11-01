#include "loconetsystemconnectionmemotest.h"
#include "junitutil.h"
#include "loconetinterfacescaffold.h"
#include "loconetsystemconnectionmemo.h"

LoconetSystemConnectionMemoTest::LoconetSystemConnectionMemoTest()
{

}
/**
 * JUnit tests for the LocoNetSystemConnectionMemo class
 *
 * @author Paul Bender Copyright (C) 2016
 */
// /*public*/ class LocoNetSystemConnectionMemoTest extends jmri.jmrix.SystemConnectionMemoTestBase {


    //@Override
    //@Before
    /*public*/ void LoconetSystemConnectionMemoTest::setUp(){
       JUnitUtil::setUp();
       memo = new LocoNetSystemConnectionMemo();
       LocoNetInterfaceScaffold* lnis = new LocoNetInterfaceScaffold(memo);
       memo->setLnTrafficController(lnis);
       //memo->configureCommandStation(LnCommandStationType::COMMAND_STATION_DCS100,false,false,false);
       memo->configureCommandStation(new LnCommandStationType("DCS100 (Chief)",true, false, true,true,"LnThrottleManager","SlotManager"),false,false,false);
       memo->configureManagers();
       scm = memo;
    }

    //@Override
    //@After
    /*public*/ void LoconetSystemConnectionMemoTest::tearDown(){
       memo->dispose();
       JUnitUtil::tearDown();
    }
