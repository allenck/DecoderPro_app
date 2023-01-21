#include "configxmlmanagertest.h"
#include "junitutil.h"
#include "assert1.h"
#include "tripleturnoutsignalhead.h"
#include "fileutil.h"
#include "manager.h"
#include "class.h"
#include "file.h"
#include "printstream.h"

ConfigXmlManagerTest::ConfigXmlManagerTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for ConfigXmlManager.
 * <p>
 * Uses the local preferences for test files.
 *
 * @author Bob Jacobsen Copyright 2003
 */
// /*public*/ class ConfigXmlManagerTest {


    //@Test
    /*public*/ void ConfigXmlManagerTest::testRegisterOK() {
        ConfigXmlManager* configxmlmanager = new ConfigXmlManagerO1();
//        {
//            @SuppressWarnings("unused")
//            void locateFailed(Throwable ex, String adapterName, Object o) {
//            }
//        };

        QObject* o1 = new TripleTurnoutSignalHead("", "", nullptr, nullptr, nullptr);
        configxmlmanager->registerConfig(o1);
        Assert::assertTrue("stored in clist", configxmlmanager->clist.size() == 1, __FILE__, __LINE__);
        configxmlmanager->deregister(o1);
        Assert::assertTrue("removed from clist", configxmlmanager->clist.isEmpty(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ConfigXmlManagerTest::testLogErrorOnStore() {
        ConfigXmlManager* configxmlmanager = new ConfigXmlManager();
        innerFlag = false;
        ConfigXmlManager::setErrorHandler(new ErrorHandlerO1(this));
//        {
//            @Override
//            /*public*/ void handle(ErrorMemo e) {
//                innerFlag = true;
//            }
//        });

        QObject* o1 = new ConfigXmlHandle();
        configxmlmanager->registerUser(o1);

        // this will fail before reaching file
        try {
            configxmlmanager->storeAll(new File(FileUtil::getUserFilesPath(), "none"));
        } catch (Exception* e) {
            // check that the handler was invoked
            Assert::assertTrue(innerFlag, __FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/ void ConfigXmlManagerTest::testFind() throw (ClassNotFoundException) {
        ConfigXmlManager* configxmlmanager = new ConfigXmlManagerO1();
//        {
//            @SuppressWarnings("unused")
//            void locateFailed(Throwable ex, String adapterName, Object o) {
//                innerFlag = true;
//            }
//        };
        QObject* o1 = new TripleTurnoutSignalHead("SH1", "", nullptr, nullptr, nullptr);
        QObject* o2 = new TripleTurnoutSignalHead("SH2", "", nullptr, nullptr, nullptr);
        QObject* o3 = new TripleTurnoutSignalHead("SH3", "", nullptr, nullptr, nullptr);
        innerFlag = false;
        configxmlmanager->registerConfig(o1, Manager::SIGNALHEADS);
        Assert::assertTrue("find found it", configxmlmanager->findInstance(o1->metaObject()->className(), 0) == o1, __FILE__, __LINE__);
        Assert::assertTrue("find only one so far", configxmlmanager->findInstance(o1->metaObject()->className(), 1) == nullptr, __FILE__, __LINE__);
        configxmlmanager->deregister(o1);
        Assert::assertTrue("find none", configxmlmanager->findInstance(o1->metaObject()->className(), 0) == nullptr, __FILE__, __LINE__);
        configxmlmanager->registerConfig(o1, Manager::SIGNALHEADS);
        configxmlmanager->registerConfig(o2, Manager::SIGNALHEADS);
        configxmlmanager->registerConfig(o3, Manager::SIGNALHEADS);
        QObject* ot = configxmlmanager->findInstance(o1->metaObject()->className(), 1);
        Assert::assertNotNull("findInstance(class, 1) not null", ot, __FILE__, __LINE__);
        Assert::assertEquals("findInstance(class, 1) equals o2",o2, ot, __FILE__, __LINE__);
        Assert::assertTrue("find found 2nd", configxmlmanager->findInstance(o1->metaObject()->className(), 1) == o2, __FILE__, __LINE__);
        Assert::assertTrue("find found subclass", configxmlmanager->findInstance("jmri.SignalHead", 1) == o2, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void ConfigXmlManagerTest::testDeregister() {
    }

    //@Test
    /*public*/ void ConfigXmlManagerTest::testAdapterName() {
        //ConfigXmlManager c = new ConfigXmlManager();
//        Assert::assertEquals("String class adapter", "java.lang.configurexml.StringXml",
//                ConfigXmlManager::adapterName(""), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ConfigXmlManagerTest::testCurrentClassName() {
        Assert::assertEquals("unmigrated", "jmri.managers.configurexml.DccSignalHeadXml",
                ConfigXmlManager::currentClassName("jmri.managers.configurexml.DccSignalHeadXml"), __FILE__, __LINE__);
        Assert::assertEquals("migrated", "jmri.managers.configurexml.DccSignalHeadXml",
                ConfigXmlManager::currentClassName("jmri.configurexml.DccSignalHeadXml"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ConfigXmlManagerTest::testFindFile() throw (FileNotFoundException, IOException) {
        ConfigXmlManager* configxmlmanager = new ConfigXmlManagerO2(this);
//        {
//            @Override
//            void locateClassFailed(Throwable ex, String adapterName, Object o) {
//                innerFlag = true;
//            }

//            @Override
//            void locateFileFailed(String f) {
//                // suppress warning during testing
//            }
//        };
        QUrl* result;
        result = configxmlmanager->find("foo.biff");
        Assert::assertTrue("dont find foo.biff", result->isEmpty(), __FILE__, __LINE__);

        // make sure no test file exists in "layout"
        FileUtil::createDirectory(FileUtil::getUserFilesPath() + "layout");
        File* f = new File(FileUtil::getUserFilesPath() + "layout" + File::separator + "testConfigXmlManagerTest.xml");
        if (f->_delete()) {  // remove it if its there
            // nothing to do if delete failed
        }

        // if file is at top level, remove that too
        f = new File("testConfigXmlManagerTest.xml");
        if (f->exists()) {
            if (f->_delete()) {
                // nothing to do if delete failed
            }
        }

        // check for not found if doesn't exist
        result = configxmlmanager->find("testConfigXmlManagerTest.xml");
        Assert::assertTrue("should not find testConfigXmlManagerTest.xml", result->isEmpty(), __FILE__, __LINE__);

        // put file back and find
        QFile* qf = new QFile(f->getPath());
        PrintStream* p = new PrintStream(new QDataStream(qf));
        p->println("stuff"); // load a new one
        qf->close();

        result = configxmlmanager->find("testConfigXmlManagerTest.xml");
        Assert::assertTrue("should find testConfigXmlManagerTest.xml", !result->isEmpty(), __FILE__, __LINE__);
        f->_delete();  // make sure it's gone again

        // check file in the current app dir
        f = new File("testConfigXmlManagerTest.xml");
        f->_delete();  // remove it if its there
        qf = new QFile(f->getPath());
        p = new PrintStream(new QDataStream(qf));
        p->println("stuff"); // load a new one
        p->device()->close();

        result = configxmlmanager->find("testConfigXmlManagerTest.xml");
        Assert::assertTrue("should find testConfigXmlManagerTest.xml in app dir", result->isValid(), __FILE__, __LINE__);
        f->_delete();  // make sure it's gone again
    }

    //@Before
    /*public*/ void ConfigXmlManagerTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();
    }

    //@After
    /*public*/ void ConfigXmlManagerTest::tearDown() {
        JUnitUtil::tearDown();
    }
