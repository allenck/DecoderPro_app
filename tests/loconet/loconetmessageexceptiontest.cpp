#include "loconetmessageexceptiontest.h"
#include "junitutil.h"
#include "assert1.h"
#include "vptr.h"

LocoNetMessageExceptionTest::LocoNetMessageExceptionTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for LocoNetMessageException class.
 *
 * @author Paul Bender Copyright (C) 2016
 */

// /*public*/ class LocoNetMessageExceptionTest {

   //@Test
   /*public*/ void LocoNetMessageExceptionTest::ConstructorTest(){
      Assert::assertNotNull("LocoNetMessageException constructor",VPtr<LocoNetMessageException>::asQVariant(new LocoNetMessageException()), __FILE__, __LINE__);
   }

   //@Test
   /*public*/ void LocoNetMessageExceptionTest::StringConstructorTest(){
      Assert::assertNotNull("LocoNetMessageException string constructor",VPtr<LocoNetMessageException>::asQVariant(new LocoNetMessageException("test exception")), __FILE__, __LINE__);
   }

   //@Before
   /*public*/ void LocoNetMessageExceptionTest::setUp() {
        JUnitUtil::setUp();

        JUnitUtil::initDefaultUserMessagePreferences();
   }

   //@After
   /*public*/ void LocoNetMessageExceptionTest::tearDown(){
        JUnitUtil::tearDown();
   }
