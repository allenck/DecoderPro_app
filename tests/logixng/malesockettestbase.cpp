#include "malesockettestbase.h"
#include "assert1.h"
#include "junitappender.h"
#include "malesocket.h"
#include "debugable.h"
#include "abstractnamedbean.h"
#include "abstractbase.h"


/**
 * Base class for test classes that tests MaleSockets
 */
// /*public*/  abstract class MaleSocketTestBase {


    //@Test
    /*public*/  void MaleSocketTestBase::testExists() /*throws JmriException*/ {
        Assert::assertNotNull("exists", maleSocketA->bself(), __FILE__, __LINE__);
        Assert::assertNotNull("exists", maleSocketB->bself(), __FILE__, __LINE__);
        Assert::assertNotEquals("not equals", maleSocketA->bself(), maleSocketB->bself(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testLock() {
        maleSocketA->setLocked(false);
        Assert::assertFalse(maleSocketA->isLocked(), __FILE__, __LINE__);
        maleSocketA->setLocked(true);
        Assert::assertTrue(maleSocketA->isLocked(), __FILE__, __LINE__);
        maleSocketA->setSystem(false);
        Assert::assertFalse(maleSocketA->isSystem(), __FILE__, __LINE__);
        maleSocketA->setSystem(true);
        Assert::assertTrue(maleSocketA->isSystem(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testCategory() /*throws JmriException*/ {
        Assert::assertEquals("category is correct",
                maleSocketA->getObject()->getCategory(), maleSocketA->getCategory(), __FILE__, __LINE__);
        Assert::assertEquals("category is correct",
                maleSocketB->getObject()->getCategory(), maleSocketB->getCategory(), __FILE__, __LINE__);
        Assert::assertNotEquals("categories are different",
                (QObject*)maleSocketA->getCategory(), (QObject*)maleSocketB->getCategory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testShortDescription() /*throws JmriException*/ {
        Assert::assertEquals("getShortDescription() is correct",
                maleSocketA->getObject()->getShortDescription(), maleSocketA->getShortDescription(), __FILE__, __LINE__);
        Assert::assertEquals("getShortDescription() is correct",
                maleSocketB->getObject()->getShortDescription(), maleSocketB->getShortDescription(), __FILE__, __LINE__);
        Assert::assertNotEquals("getShortDescription() are different",
                maleSocketA->getShortDescription(), maleSocketB->getShortDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testLongDescription() /*throws JmriException*/ {
        QString s1 = maleSocketA->getObject()->getLongDescription();
        QString s2 = maleSocketA->getLongDescription();

        Assert::assertEquals("getLongDescription() is correct",
                maleSocketA->getObject()->getLongDescription(), maleSocketA->getLongDescription(), __FILE__, __LINE__);
        Assert::assertEquals("getLongDescription() is correct",
                maleSocketB->getObject()->getLongDescription(), maleSocketB->getLongDescription(), __FILE__, __LINE__);
        Assert::assertNotEquals("getLongDescription() are different",
                maleSocketA->getLongDescription(), maleSocketB->getLongDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testGetSystemName() /*throws JmriException*/ {
        Assert::assertNotNull(maleSocketA->bself(), __FILE__, __LINE__);
        Assert::assertNotNull(maleSocketA->getSystemName(), __FILE__, __LINE__);
        Assert::assertNotNull(maleSocketA->getObject()->bself(), __FILE__, __LINE__);
        Assert::assertNotNull(maleSocketA->getObject()->getSystemName(), __FILE__, __LINE__);

QString sn1 = ((AbstractBase*)maleSocketA->getObject()->bself())->AbstractNamedBean::getSystemName();
QString sn2 = maleSocketA->getSystemName();

        Assert::assertEquals("getSystemName() is correct",
                ((AbstractBase*)maleSocketA->getObject()->bself())->AbstractNamedBean::getSystemName(), maleSocketA->getSystemName(), __FILE__, __LINE__);
        Assert::assertEquals("getSystemName() is correct",
                ((AbstractBase*)maleSocketB->getObject()->bself())->AbstractNamedBean::getSystemName(), maleSocketB->getSystemName(), __FILE__, __LINE__);
        Assert::assertNotEquals("getSystemName() are different",
                maleSocketA->getSystemName(), maleSocketB->getSystemName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testUserName() /*throws JmriException*/ {
        maleSocketA->setUserName("Test username Abc");
        Assert::assertEquals("getUserName() is correct",
                ((AbstractBase*)maleSocketA->getObject()->bself())->AbstractNamedBean::getUserName(), maleSocketA->getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("getUserName() is correct",
                ((AbstractBase*)maleSocketB->bself())->AbstractNamedBean::getUserName(), maleSocketB->getUserName(), __FILE__, __LINE__);

        QString un1 = maleSocketA->getUserName();
        QString un2 = maleSocketB->getUserName();
        Assert::assertNotEquals("getUserName() are different",
                maleSocketA->getUserName(), maleSocketB->getUserName(), __FILE__, __LINE__);

        ((AbstractBase*)maleSocketA->getObject()->bself())->AbstractNamedBean::setUserName("Abc");
        Assert::assertEquals("getUserName() is correct",
                "Abc", maleSocketA->getUserName(), __FILE__, __LINE__);

        ((AbstractBase*)maleSocketA->getObject()->bself())->AbstractNamedBean::setUserName("Def");
        Assert::assertEquals("getUserName() is correct",
                "Def", maleSocketA->getUserName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testDisplayName() /*throws JmriException*/ {
        maleSocketA->setUserName("Test username Abc");
        Assert::assertEquals("getUserName() is correct",
                ((AbstractBase*)maleSocketA->getObject()->bself())->AbstractNamedBean::getUserName(), maleSocketA->getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("getUserName() is correct",
                ((AbstractBase*)maleSocketB->getObject()->bself())->AbstractNamedBean::getUserName(), maleSocketB->getUserName(), __FILE__, __LINE__);
        Assert::assertNotEquals("getUserName() are different",
                maleSocketA->getUserName(), maleSocketB->getUserName(), __FILE__, __LINE__);

        ((AbstractBase*)maleSocketA->getObject()->bself())->AbstractNamedBean::setUserName("Abc");
        Assert::assertEquals("getUserName() is correct",
                "Abc", maleSocketA->getUserName(), __FILE__, __LINE__);

        ((AbstractBase*)maleSocketA->getObject()->bself())->AbstractNamedBean::setUserName("Def");
        Assert::assertEquals("getUserName() is correct",
                "Def", maleSocketA->getUserName(), __FILE__, __LINE__);

        QString dn1 = ((AbstractBase*)maleSocketA->getObject()->bself())->getDisplayName();
        QString dn2 = ((AbstractBase*)maleSocketA->bself())->getDisplayName();
        QString dn3 = ((AbstractNamedBean*)maleSocketA->bself())->getDisplayName();
        Assert::assertEquals("getDisplayName() is correct",
                ((AbstractBase*)maleSocketA->getObject()->bself())->getDisplayName(), ((AbstractBase*)maleSocketA->bself())->getDisplayName(), __FILE__, __LINE__);
        Assert::assertEquals("getDisplayName() is correct",
                ((AbstractBase*)maleSocketB->getObject()->bself())->getDisplayName(), ((AbstractBase*)maleSocketB->bself())->getDisplayName(), __FILE__, __LINE__);
        Assert::assertNotEquals("getDisplayName() are different",
               ((AbstractBase*)maleSocketA->bself())->getDisplayName(), ((AbstractBase*)maleSocketB->bself())->getDisplayName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testState() /*throws JmriException*/ {
     AbstractBase* ab =  ((AbstractBase*)maleSocketA->bself());
     ab->setState(NamedBean::UNKNOWN);
        ((AbstractBase*)maleSocketA->bself())->setState(NamedBean::UNKNOWN);
     int state = ab->getState();
        Assert::assertEquals("getState() is correct",
                NamedBean::UNKNOWN, ((AbstractBase*)maleSocketA->bself())->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessageStartingWith("Unexpected call to setState in ", __FILE__, __LINE__);
        JUnitAppender::assertWarnMessageStartingWith("Unexpected call to getState in ", __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testComment() /*throws JmriException*/ {
        ((AbstractBase*)maleSocketA->bself())->setComment("Abc");
        Assert::assertEquals("getComment() is correct",
                "Abc", ((AbstractBase*)maleSocketA->bself())->getComment(), __FILE__, __LINE__);

        ((AbstractBase*)maleSocketA->bself())->setComment("Def");
        Assert::assertEquals("getComment() is correct",
                "Def", ((AbstractBase*)maleSocketA->bself())->getComment(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testProperty() {
        // Remove all properties to be sure we don't hit any problem later
        for (QString property : ((AbstractBase*)maleSocketA->bself())->getPropertyKeys()) {
            ((AbstractBase*)maleSocketA->bself())->removeProperty(property);
        }

        // Test set property and read it
        ((AbstractBase*)maleSocketA->bself())->setProperty("Abc", "Something");
        Assert::assertEquals("getProperty() is correct",
                "Something", ((AbstractBase*)maleSocketA->bself())->getProperty("Abc"), __FILE__, __LINE__);
        // Test set property to something else and read it
        ((AbstractBase*)maleSocketA->bself())->setProperty("Abc", "Something else");
        Assert::assertEquals("getProperty() is correct",
                "Something else", ((AbstractBase*)maleSocketA->bself())->getProperty("Abc"), __FILE__, __LINE__);
        Assert::assertEquals("num properties", 1, ((AbstractBase*)maleSocketA->bself())->getPropertyKeys().size(), __FILE__, __LINE__);
        // Test set property with another key and read it
        ((AbstractBase*)maleSocketA->bself())->setProperty("Def", "Something different");
        Assert::assertEquals("getProperty() is correct",
                "Something different", ((AbstractBase*)maleSocketA->bself())->getProperty("Def"), __FILE__, __LINE__);
        // Test that the previous key hasn't been changed
        Assert::assertEquals("getProperty() is correct",
                "Something else", ((AbstractBase*)maleSocketA->bself())->getProperty("Abc"), __FILE__, __LINE__);
        Assert::assertEquals("num properties", 2, ((AbstractBase*)maleSocketA->bself())->getPropertyKeys().size(), __FILE__, __LINE__);
        // Test removing the property and read it
        ((AbstractBase*)maleSocketA->bself())->removeProperty("Abc");
        Assert::assertNull("getProperty() is null",
                ((AbstractBase*)maleSocketA->bself())->getProperty("Abc"), __FILE__, __LINE__);
        Assert::assertEquals("num properties", 1, ((AbstractBase*)maleSocketA->bself())->getPropertyKeys().size(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void MaleSocketTestBase::testDebugConfig() {
        Debugable::DebugConfig* debugConfig = maleSocketA->createDebugConfig();
        Assert::assertNotNull("debugConfig is not null", (QObject*)debugConfig, __FILE__, __LINE__);
        maleSocketA->setDebugConfig(debugConfig);
        Assert::assertTrue("debugConfig correct",
                debugConfig == maleSocketA->getDebugConfig(), __FILE__, __LINE__);
        maleSocketA->setDebugConfig(nullptr);
        Assert::assertNull("debugConfig is null", (QObject*)maleSocketA->getDebugConfig(), __FILE__, __LINE__);
    }

    //@BeforeEach
//    abstract /*public*/  void setUp();

    //@AfterEach
//    abstract /*public*/  void tearDown();
