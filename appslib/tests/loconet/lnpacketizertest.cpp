#include "lnpacketizertest.h"
#include "lnpacketizer.h"
#include "loconetsystemconnectionmemo.h"
#include "assert1.h"
#include "junitutil.h"
#
LnPacketizerTest::LnPacketizerTest(QObject *parent) : QObject(parent)
{

}
/**
 * JUnit tests for the LnPacketizerTest class.
 *
 * @author Bob Jacobsen Copyright (C) 2002
 * @author Paul Bender Copyright (C) 2018
 */
///*public*/ class LnPacketizerTest {


//@Test
/*public*/ void LnPacketizerTest::testCtor() {
   Assert::assertNotNull("exists", lnp );
}

//@Test
/*public*/ void LnPacketizerTest::testStatusWithoutInit() {
   Assert::assertFalse("not connected", lnp->status() );
}

//@Test
//@Ignore("may be causing hang on travis and appveyor")
/*public*/ void LnPacketizerTest::testStartThreads() {
   lnp->connectPort(new LnPortControllerO1(memo, this));
//   {
//        @Override
//        /*public*/ boolean status(){
//          return true;
//        }
//        @Override
//        /*public*/ void configure(){
//        }
//        @Override
//        /*public*/ java.io.DataInputStream getInputStream(){
//            return new DataInputStream(new ByteArrayInputStream(new byte[0]));
//        }
//        @Override
//        /*public*/ java.io.DataOutputStream getOutputStream(){
//            return new DataOutputStream(new ByteArrayOutputStream());
//        }

//        @Override
//        /*public*/ String[] validBaudRates(){
//           String[] retval = {"9600"};
//           return retval;
//        }

//        /**
//         * Open a specified port. The appName argument is to be provided to the
//         * underlying OS during startup so that it can show on status displays, etc
//         */
//        @Override
//        /*public*/ String openPort(String portName, String appName){
//           return "";
//        }

//     });
   lnp->startThreads();
   memo->dispose();
}

//@Before
/*public*/ void LnPacketizerTest::setUp() {
    JUnitUtil::setUp();
    memo = new LocoNetSystemConnectionMemo();
    lnp = new LnPacketizer(memo);
}

//@After
/*public*/ void LnPacketizerTest::tearDown() {
    lnp = nullptr;
    memo = nullptr;
    JUnitUtil::tearDown();
}
