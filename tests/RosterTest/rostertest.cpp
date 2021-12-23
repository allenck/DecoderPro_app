#include "rostertest.h"
#include "rostertestutil.h"
#include "file.h"
#include "fileutil.h"
#include "rosterentry.h"
#include "../assert1.h"
#include "rosterentrycombobox.h"
#include "instancemanager.h"
#include "rosterspeedprofile.h"
#include "../junitutil.h"
#include "myfileinputstream.h"
#include "nullprofile.h"
//#include "printstream.h"
#include "fileoutputstream.h"
#include "fileutil.h"

RosterTest::RosterTest(QObject *parent) : QObject(parent)
{
    folder = new TemporaryFolder();
}

/**
 * Tests for the jmrit.Roster::Roster class.
 *
 * This separates tests of the DefaultRoster functionality from tests of Roster
 * objects individually. Roster itself doesn't (yet) do go a good job of
 * separating, those, so this is somewhat arbitrary.
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2002, 2012
 */
// /*public*/ class RosterTest {


    //@Test
    /*public*/ void RosterTest::testDirty() {
        Roster* r = new Roster();
        Assert::assertEquals("new object ", false, r->isDirty(),__FILE__, __LINE__);
        r->addEntry(new RosterEntry());
        Assert::assertEquals("after add ", true, r->isDirty(),__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void RosterTest::testAdd() {
        Roster* r = new Roster();
        Assert::assertEquals("empty length ", 0, r->numEntries(),__FILE__, __LINE__);
        r->addEntry(new RosterEntry("file name Bob"));
        Assert::assertEquals("one item ", 1, r->numEntries(),__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void RosterTest::testDontAddNullEntriesLater() {
        // test as documentation...
        Roster* r = new Roster();
        r->addEntry(new RosterEntry());
        r->addEntry(new RosterEntry());

        bool pass = false;
        try {
            r->addEntry(nullptr);
        } catch (NullPointerException* e) {
            pass = true;
        }
        Assert::assertTrue("Adding nullptr entry should have caused NPE", pass,__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void RosterTest::testDontAddNullEntriesFirst() {
        // test as documentation...
        Roster* r = new Roster();

        bool pass = false;
        try {
            r->addEntry(nullptr);
        } catch (NullPointerException* e) {
            pass = true;
        }
        Assert::assertTrue("Adding nullptr entry should have caused NPE", pass,__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void RosterTest::testAddrSearch() {
        Roster* r = new Roster();
        RosterEntry* e = new RosterEntry("file name Bob");
        e->setRoadNumber("123");
        r->addEntry(e);
        Assert::assertEquals("search not OK ", false, r->checkEntry(0, nullptr, "321", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr),__FILE__, __LINE__);
        Assert::assertEquals("search OK ", true, r->checkEntry(0, nullptr, "123", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr),__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void RosterTest::testGetByDccAddress() {
        Roster* r = new Roster();
        RosterEntry* e = new RosterEntry("file name Bob");
        e->setDccAddress("456");
        r->addEntry(e);
        Assert::assertEquals("search not OK ", false, r->checkEntry(0, nullptr, nullptr, "123", nullptr, nullptr, nullptr, nullptr, nullptr),__FILE__, __LINE__);
        Assert::assertEquals("search OK ", true, r->checkEntry(0, nullptr, nullptr, "456", nullptr, nullptr, nullptr, nullptr, nullptr),__FILE__, __LINE__);

        QList<RosterEntry*> l;

        l = r->matchingList(nullptr, nullptr, "123", nullptr, nullptr, nullptr, nullptr);
        Assert::assertEquals("match 123", 0, l.size(),__FILE__, __LINE__);

        l = r->matchingList(nullptr, nullptr, "456", nullptr, nullptr, nullptr, nullptr);
        Assert::assertEquals("match 456", 1, l.size(),__FILE__, __LINE__);

        l = r->getEntriesByDccAddress("123");
        Assert::assertEquals("address 123", 0, l.size(),__FILE__, __LINE__);

        l = r->getEntriesByDccAddress("456");
        Assert::assertEquals("address 456", 1, l.size(),__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void RosterTest::testSearchList() {
        Roster* r = new Roster();
        RosterEntry* e;
        e = new RosterEntry("file name Bob");
        e->setRoadNumber("123");
        e->setRoadName("SP");
        r->addEntry(e);
        e = new RosterEntry("file name Bill");
        e->setRoadNumber("123");
        e->setRoadName("ATSF");
        e->setDecoderModel("81");
        e->setDecoderFamily("33");
        r->addEntry(e);
        e = new RosterEntry("file name Ben");
        e->setRoadNumber("123");
        e->setRoadName("UP");
        r->addEntry(e);

        QList<RosterEntry*> l;
        l = r->matchingList(nullptr, "321", nullptr, nullptr, nullptr, nullptr, nullptr);
        Assert::assertEquals("search for 0 ", 0, l.size(),__FILE__, __LINE__);

        l = r->matchingList("UP", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        Assert::assertEquals("search for 1 ", 1, l.size(),__FILE__, __LINE__);
        Assert::assertEquals("search for 1 ", "UP", l.at(0)->getRoadName(),__FILE__, __LINE__);
        Assert::assertEquals("search for 1 ", "123", l.at(0)->getRoadNumber(),__FILE__, __LINE__);

        l = r->matchingList(nullptr, "123", nullptr, nullptr, nullptr, nullptr, nullptr);
        Assert::assertEquals("search for 3 ", 3, l.size(),__FILE__, __LINE__);
        Assert::assertEquals("search for 3 ", "SP", l.at(2)->getRoadName(),__FILE__, __LINE__);
        Assert::assertEquals("search for 3 ", "123", l.at(2)->getRoadNumber(),__FILE__, __LINE__);
        Assert::assertEquals("search for 3 ", "UP", l.at(0)->getRoadName(),__FILE__, __LINE__);
        Assert::assertEquals("search for 3 ", "123", l.at(0)->getRoadNumber(),__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void RosterTest::testComboBox() {
        Roster* r = new Roster();
        RosterEntry* e1;
        RosterEntry* e2;
        RosterEntry* e3;
        e1 = new RosterEntry("file name Bob");
        e1->setRoadNumber("123");
        e1->setRoadName("SP");
        e1->setId("entry 1");
        r->addEntry(e1);
        e2 = new RosterEntry("file name Bill");
        e2->setRoadNumber("123");
        e2->setRoadName("ATSF");
        e2->setDecoderModel("81");
        e2->setDecoderFamily("33");
        e2->setId("entry 2");
        r->addEntry(e2);
        e3 = new RosterEntry("file name Ben");
        e3->setRoadNumber("123");
        e3->setRoadName("UP");
        e3->setId("entry 3");
        r->addEntry(e3);

        RosterEntryComboBox/*<Object>*/* box;

        // "Select Loco" is the first entry in the RosterEntryComboBox, so an
        // empty comboBox has 1 item, and the first item is not a RosterEntry
        box = new RosterEntryComboBox(r, nullptr, "321", nullptr, nullptr, nullptr, nullptr, nullptr);
        Assert::assertEquals("search for zero matches", 1, box->getItemCount(),__FILE__, __LINE__);
        delete box;

        box = new RosterEntryComboBox(r, "UP", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        Assert::assertEquals("search for one match", 2, box->getItemCount(),__FILE__, __LINE__);
        Assert::assertEquals("search for one match", e3, box->getItemAt(1),__FILE__, __LINE__);
        delete box;

        box = new RosterEntryComboBox(r, nullptr, "123", nullptr, nullptr, nullptr, nullptr, nullptr);
        Assert::assertEquals("search for three matches", 4, box->getItemCount(),__FILE__, __LINE__);
        Assert::assertEquals("search for three matches", e1, box->getItemAt(1),__FILE__, __LINE__);
        Assert::assertEquals("search for three matches", e2, box->getItemAt(2),__FILE__, __LINE__);
        Assert::assertEquals("search for three matches", e3, box->getItemAt(3),__FILE__, __LINE__);
        delete box;

    }

    //@Test
    /*public*/ void RosterTest::testBackupFile() throw (Exception) {
        // this test uses explicit filenames intentionally, to ensure that
        // the resulting files go into the test tree area.

        // create a file in "temp"
        File* rosterDir = folder->newFolder();
        folder->newFolder();
        FileUtil::createDirectory(rosterDir);
        File* f = new File(rosterDir, "roster.xml");

        // failure of test infrastructure if it exists already
        Assert::assertTrue("test roster.xml should not exist in new folder", !f->exists(),__FILE__, __LINE__);

        // load a new one to ensure it exists
        QString contents = QString("stuff") + "           ";
//        PrintStream* p = new PrintStream(new FileOutputStream(f));
//        p->println(contents);
//        p->close();
        FileUtil::appendTextToFile(f,contents);

        File* bf = new File(rosterDir, "rosterBackupTest");
        // failure of test infrastructure if backup exists already
        Assert::assertTrue("test backup file should not exist in new folder", !bf->exists(),__FILE__, __LINE__);

        // now do the backup
//        Roster* r = new Roster() {
//            //@Override
//            /*public*/ QString backupFileName(QString name) {
//                return new File(rosterDir, "rosterBackupTest").getAbsolutePath();
//            }
//        };
        RTRoster* r = new RTRoster(rosterDir);
        r->makeBackupFile((new File(rosterDir, "roster.xml"))->getAbsolutePath());

        // and check
        MyFileInputStream* in = new MyFileInputStream(new File(rosterDir, "rosterBackupTest"));
        Assert::assertEquals("read 0 ", contents.at(0), in->read(),__FILE__, __LINE__);
        Assert::assertEquals("read 1 ", contents.at(1), in->read(),__FILE__, __LINE__);
        Assert::assertEquals("read 2 ", contents.at(2), in->read(),__FILE__, __LINE__);
        Assert::assertEquals("read 3 ", contents.at(3), in->read(),__FILE__, __LINE__);
        in->close();

        // now see if backup works when a backup file already exists
        contents = QString("NEWER JUNK") + "           ";
#if 0   // done:
        p = new PrintStream(new FileOutputStream(f));
        p.println(contents);
        p.close();
#endif
        FileUtil::appendTextToFile(f,contents);

        // now do the backup
        r->makeBackupFile(f->getAbsolutePath());

        // and check
        in = new MyFileInputStream(new File(rosterDir, "rosterBackupTest"));
        Assert::assertEquals("read 4 ", contents.at(0), in->read(),__FILE__, __LINE__);
        Assert::assertEquals("read 5 ", contents.at(1), in->read(),__FILE__, __LINE__);
        Assert::assertEquals("read 6 ", contents.at(2), in->read(),__FILE__, __LINE__);
        Assert::assertEquals("read 7 ", contents.at(3), in->read(),__FILE__, __LINE__);
        in->close();
    }

/*public*/ QString RTRoster::backupFileName(QString name) const{
        return (new File(rosterDir, "rosterBackupTest"))->getAbsolutePath();
    }


    //@Test
    /*public*/ void RosterTest::testReadWrite() throw (Exception) {
        // create a test roster & store in file
        Roster* r = RosterTestUtil::createTestRoster(new File(Roster::getDefault()->getRosterLocation()),"rosterTest.xml");
        Assert::assertNotNull("exists", r,__FILE__, __LINE__);
        // write it
        r->writeFile(r->getRosterIndexPath());
        // create new roster & read
        Roster* t = new Roster();
        t->readFile(r->getRosterIndexPath());

        // check contents
        Assert::assertEquals("search for 0 ", 0, t->matchingList(nullptr, "321", nullptr, nullptr, nullptr, nullptr, nullptr).size(),__FILE__, __LINE__);
        Assert::assertEquals("search for 1 ", 1, t->matchingList("UP", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr).size(),__FILE__, __LINE__);
        Assert::assertEquals("search for 3 ", 3, t->matchingList(nullptr, "123", nullptr, nullptr, nullptr, nullptr, nullptr).size(),__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void RosterTest::testAttributeAccess() throw (Exception) {
        // create a test roster & store in file
        Roster* r = RosterTestUtil::createTestRoster(new File(Roster::getDefault()->getRosterLocation()),"rosterTest.xml");
        Assert::assertNotNull("exists", r,__FILE__, __LINE__);

        QList<RosterEntry*> l;

        l = r->getEntriesWithAttributeKey("key a");
        Assert::assertEquals("match key a", 2, l.size(),__FILE__, __LINE__);
        l = r->getEntriesWithAttributeKey("no match");
        Assert::assertEquals("no match", 0, l.size(),__FILE__, __LINE__);

    }

    //@Test
    /*public*/ void RosterTest::testAttributeValueAccess() throw (Exception) {
        // create a test roster & store in file
        Roster* r = RosterTestUtil::createTestRoster(new File(Roster::getDefault()->getRosterLocation()),"rosterTest.xml");
        Assert::assertNotNull("exists", r,__FILE__, __LINE__);

        QList<RosterEntry*> l;

        l = r->getEntriesWithAttributeKeyValue("key a", "value a");
        Assert::assertEquals("match key a", 2, l.size(),__FILE__, __LINE__);
        l = r->getEntriesWithAttributeKeyValue("key a", "none");
        Assert::assertEquals("no match key a", 0, l.size(),__FILE__, __LINE__);
        l = r->getEntriesWithAttributeKeyValue("no match", "none");
        Assert::assertEquals("no match", 0, l.size(),__FILE__, __LINE__);

    }

    //@Test
    /*public*/ void RosterTest::testAttributeList() throw (Exception) {
        // create a test roster & store in file
        Roster* r = RosterTestUtil::createTestRoster(new File(Roster::getDefault()->getRosterLocation()),"rosterTest.xml");
        Assert::assertNotNull("exists", r,__FILE__, __LINE__);

        QSet<QString> s;

        s = r->getAllAttributeKeys();

        Assert::assertTrue("contains right key", s.contains("key b"),__FILE__, __LINE__);
        Assert::assertTrue("not contains wrong key", !s.contains("no key"),__FILE__, __LINE__);
        Assert::assertEquals("length", 2, s.size(),__FILE__, __LINE__);

    }

    //@Test
    /*public*/ void RosterTest::testDefaultLocation() {
        Assert::assertTrue("creates a default", Roster::getDefault() != nullptr,__FILE__, __LINE__);
        Assert::assertEquals("always same", Roster::getDefault(), Roster::getDefault(),__FILE__, __LINE__);
        // Default roster not stored in InstanceManager
        Assert::assertNull("registered a default", InstanceManager::getNullableDefault("Roster"),__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void RosterTest::testProfileOnePointForward() {
        RosterEntry* r = new RosterEntry();
        RosterSpeedProfile* rp = new RosterSpeedProfile(r);
        rp->setSpeed(1000, 500, 5000);
        Assert::assertEquals(500.0f,rp->getForwardSpeed(1.0f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(375.0f,rp->getForwardSpeed(0.75f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(250.0f,rp->getForwardSpeed(0.5f), 0.0f,__FILE__, __LINE__);
        Assert::assertEquals(125.0f,rp->getForwardSpeed(0.25f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(4.0f,rp->getForwardSpeed(0.0078125f),0.0f,__FILE__, __LINE__); //routine will use 8 (round( value * 1000))
    }

    //@Test
    /*public*/ void RosterTest::testProfileTwoPointForward() {
        RosterEntry* r = new RosterEntry();
        RosterSpeedProfile* rp = new RosterSpeedProfile(r);
        rp->setSpeed(1000, 500, 5000);
        rp->setSpeed(500, 250, 2500);
        Assert::assertEquals(500.0f,rp->getForwardSpeed(1.0f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(375.0f,rp->getForwardSpeed(0.75f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(250.0f,rp->getForwardSpeed(0.5f), 0.0f,__FILE__, __LINE__);
        Assert::assertEquals(125.0f,rp->getForwardSpeed(0.25f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(4.0f,rp->getForwardSpeed(0.0078125f),0.0f,__FILE__, __LINE__); //routine will use 8 (round( value * 1000))
    }
    //@Test
    /*public*/ void RosterTest::testProfileOnePointReverse() {
        RosterEntry* r = new RosterEntry();
        RosterSpeedProfile* rp = new RosterSpeedProfile(r);
        rp->setSpeed(1000, 500, 5000);
        Assert::assertEquals(5000.0f,rp->getReverseSpeed(1.0f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(3750.0f,rp->getReverseSpeed(0.75f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(2500.0f,rp->getReverseSpeed(0.5f), 0.0f,__FILE__, __LINE__);
        Assert::assertEquals(1250.0f,rp->getReverseSpeed(0.25f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(40.0f,rp->getReverseSpeed(0.0078125f),0.0f,__FILE__, __LINE__);   //routine will use 8 (round( value * 1000))
    }

    //@Test
    /*public*/ void RosterTest::testProfileTwoPointReverse() {
        RosterEntry* r = new RosterEntry();
        RosterSpeedProfile* rp = new RosterSpeedProfile(r);
        rp->setSpeed(1000, 500, 5000);
        rp->setSpeed(500, 250, 2500);
        Assert::assertEquals(5000.0f,rp->getReverseSpeed(1.0f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(3750.0f,rp->getReverseSpeed(0.75f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(2500.0f,rp->getReverseSpeed(0.5f), 0.0f,__FILE__, __LINE__);
        Assert::assertEquals(1250.0f,rp->getReverseSpeed(0.25f),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(40.0f,rp->getReverseSpeed(0.0078125f),0.0f,__FILE__, __LINE__); //routine will use 8 (round( value * 1000))
    }

    //@Test
    /*public*/ void RosterTest::testProfileTwoPointForwardGetThrottleSetting() {
        RosterEntry* r = new RosterEntry();
        RosterSpeedProfile* rp = new RosterSpeedProfile(r);
        rp->setSpeed(1000, 500, 5000);
        rp->setSpeed(500, 250, 2500);
        Assert::assertEquals(1.0f,rp->getThrottleSetting(500,true),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(0.5f,rp->getThrottleSetting(250,true),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(0.25f,rp->getThrottleSetting(125,true),0.0f,__FILE__, __LINE__);
    }

   //@Test
    /*public*/ void RosterTest::testProfileTwoPointReverseGetThrottleSetting() {
        RosterEntry* r = new RosterEntry();
        RosterSpeedProfile* rp = new RosterSpeedProfile(r);
        rp->setSpeed(1000, 500, 5000);
        rp->setSpeed(500, 250, 2500);
        Assert::assertEquals(1.0f,rp->getThrottleSetting(5000,false),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(0.5f,rp->getThrottleSetting(2500,false),0.0f,__FILE__, __LINE__);
        Assert::assertEquals(0.25f,rp->getThrottleSetting(1250,false),0.0f,__FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void RosterTest::setUp() {
        JUnitUtil::setUp();
        try {
            JUnitUtil::resetProfileManager( new NullProfile(folder->newFolder("PROFILE")));
        } catch (IOException ioe){
            // failed to reset the profile relative to the temporary folder.
            // use the default reset.
            JUnitUtil::resetProfileManager();
        }
        JUnitUtil::initRosterConfigManager();
    }

    //@After
    /*public*/ void RosterTest::tearDown() {
        JUnitUtil::tearDown();
    }


