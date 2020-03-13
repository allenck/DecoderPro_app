#include "sectiontest.h"
#include "junitappender.h"
#include "junitutil.h"
#include "section.h"
#include "assert1.h"

SectionTest::SectionTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for Section class.
 *
 * @author Bob Jacobsen Copyright (C) 2017
 * @author Paul Bender Copyright (C) 2016
 **/

// /*public*/ class SectionTest {

   //@Test
   /*public*/ void SectionTest::SysNameConstructorTest(){
      Assert::assertNotNull("Constructor", new Section("TS1"), __FILE__, __LINE__);
   }

   //@Test
   /*public*/ void SectionTest::TwoNameStringConstructorTest(){
      Assert::assertNotNull("Constructor", new Section("TS1", "user name"), __FILE__, __LINE__);
   }

   //@Test
   /*public*/ void SectionTest::warnOnBlockAdd() {
    Section*  s = new Section("TS1");
    Assert::assertEquals(0, s->getBlockList()->size(), __FILE__, __LINE__);
    s->addBlock(new Block("IB1", "user"));
    Assert::assertEquals(1, s->getBlockList()->size(), __FILE__, __LINE__);
   }

   //@Test
   /*public*/ void SectionTest::warnOnBlockAddWithNoUserName() {
    Section*  s = new Section("TS1");
    Assert::assertEquals(0, s->getBlockList()->size(), __FILE__, __LINE__);
    s->addBlock(new Block("IB1"));
    JUnitAppender::assertWarnMessage("Block IB1 does not have a user name, may not work correctly in Section TS1", __FILE__, __LINE__);
    Assert::assertEquals(1, s->getBlockList()->size(), __FILE__, __LINE__);
   }

   //@Before
   /*public*/ void SectionTest::setUp() {
    JUnitUtil::setUp();

    JUnitUtil::initDefaultUserMessagePreferences();
   }

   //@After
   /*public*/ void SectionTest::tearDown(){
        JUnitUtil::tearDown();
   }
