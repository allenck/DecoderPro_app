#include "rosterentrytest.h"
#include "../assert.h"
#include "rosterentry.h"
#include "instancemanager.h"
#include "../junitutil.h"
#include "file.h"
#include "loggerfactory.h"
#include "roster.h"
#include "fileutil.h"
#include "rosterconfigmanager.h"

RosterEntryTest::RosterEntryTest(QObject *parent) : QObject(parent)
{

}

/**
 * Tests for the jmrit.roster.RosterEntry class.
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2002, 2018
 */
///*public*/ class RosterEntryTest {

    //@Test
    /*public*/ void RosterEntryTest::testCreate() {
        RosterEntry* r = new RosterEntry("file here");
        Assert::assertEquals("file name ", "file here", r->getFileName());
        Assert::assertEquals("DCC Address ", "3", r->getDccAddress());
        Assert::assertEquals("road name ", "", r->getRoadName());
        Assert::assertEquals("road number ", "", r->getRoadNumber());
        Assert::assertEquals("manufacturer ", "", r->getMfg());
        Assert::assertEquals("model ", "", r->getDecoderModel());
        Assert::assertEquals("family ", "", r->getDecoderFamily());
    }

    //@Test
    /*public*/ void RosterEntryTest::testPartialLoad() {
        // create Element
        QDomElement e =  QDomElement(); e.setTagName("locomotive");
                e.setAttribute("id", "our id 1");
                e.setAttribute("fileName", "file here");
                e.setAttribute("roadNumber", "431");
                e.setAttribute("roadName", "SP");
                e.setAttribute("mfg", "Athearn");
                e.setAttribute("dccAddress", "1234");
                QDomElement e1, e2;
                e.appendChild(
                e1 =  QDomElement()); e1.setTagName("locoaddress");
                e1.appendChild(
                                e2 = QDomElement());
                        e2.setTagName("dcclocoaddress");
                                e2.setAttribute("number", "1234");
                                e2.setAttribute("longaddress", "yes");

        RosterEntry* r = new RosterEntry(e);
        // check
        Assert::assertEquals("file name ", "file here", r->getFileName());
        Assert::assertEquals("DCC Address ", "1234", r->getDccAddress());
        Assert::assertEquals("road name ", "SP", r->getRoadName());
        Assert::assertEquals("road number ", "431", r->getRoadNumber());
        Assert::assertEquals("manufacturer ", "Athearn", r->getMfg());
        Assert::assertEquals("model ", "", r->getDecoderModel());
        Assert::assertEquals("family ", "", r->getDecoderFamily());
    }

    //@Test
    /*public*/ void RosterEntryTest::testEmptyLoad() {
        // create Element
        QDomElement e =  QDomElement();
        e.setTagName("locomotive");
                e.setAttribute("id", "our id 2");
                e.setAttribute("fileName", "file here"); // end create element

//        RosterEntry* r = new RosterEntry(e) {
//            //@Override
//            protected void warnShortLong(QString s) {
//            }
//        };
        RosterEntryO1* r = new RosterEntryO1();
        // check
        Assert::assertEquals("file name ", "file here", r->getFileName());
        Assert::assertEquals("DCC Address ", "3", r->getDccAddress());
        Assert::assertEquals("road name ", "", r->getRoadName());
        Assert::assertEquals("road number ", "", r->getRoadNumber());
        Assert::assertEquals("manufacturer ", "", r->getMfg());
        Assert::assertEquals("model ", "", r->getDecoderModel());
        Assert::assertEquals("family ", "", r->getDecoderFamily());
    }

    //@Test
    /*public*/ void RosterEntryTest::testFullLoad() {
        // create Element
        QDomElement e =  QDomElement(); e.setTagName("locomotive");
                e.setAttribute("id", "our id 3");
                e.setAttribute("fileName", "file here");
                e.setAttribute("roadNumber", "431");
                e.setAttribute("roadName", "SP");
                e.setAttribute("mfg", "Athearn");
                e.setAttribute("dccAddress", "1234");
                QDomElement e1;
                e.appendChild(e1= QDomElement()); e1.setTagName("decoder");
                        e1.setAttribute("family", "91");
                        e1.setAttribute("model", "33");

//        RosterEntry r = new RosterEntry(e) {
//            @Override
//            protected void warnShortLong(QString s) {
//            }
//        };
                RosterEntryO1* r = new RosterEntryO1();


        // check
        Assert::assertEquals("file name ", "file here", r->getFileName());
        Assert::assertEquals("DCC Address ", "1234", r->getDccAddress());
        Assert::assertEquals("road name ", "SP", r->getRoadName());
        Assert::assertEquals("road number ", "431", r->getRoadNumber());
        Assert::assertEquals("manufacturer ", "Athearn", r->getMfg());
        Assert::assertEquals("model ", "33", r->getDecoderModel());
        Assert::assertEquals("family ", "91", r->getDecoderFamily());
    }

    //@Test
    /*public*/ void RosterEntryTest::testFromSchemaFile() throw (JDOMException, IOException) {

        // Create a RosterEntry from a test xml file
        // This one references the Schema version
        RosterEntry* r = RosterEntry::fromFile(new File("java/test/jmri/jmrit/roster/ACL1012-Schema.xml"));

        // check for various values
        Assert::assertEquals("file name ", "ACL1012-Schema.xml", r->getFileName());
        Assert::assertEquals("DCC Address ", "1012", r->getDccAddress());
        Assert::assertEquals("road name ", "Atlantic Coast Line", r->getRoadName());
        Assert::assertEquals("road number ", "1012", r->getRoadNumber());
        Assert::assertEquals("model ", "Synch Diesel Sound 1812 - N Scale Atlas Short Board Dropin", r->getDecoderModel());
        Assert::assertEquals("family ", "Brilliance Sound Decoders", r->getDecoderFamily());
    }

    //@Test
    /*public*/ void RosterEntryTest::testFromDtdFile() throw (JDOMException, IOException) {

        // Create a RosterEntry from a test xml file
        // This one references the DTD to make sure that still works
        // post migration
        RosterEntry* r = RosterEntry::fromFile(new File("java/test/jmri/jmrit/roster/ACL1012-DTD.xml"));

        // check for various values
        Assert::assertEquals("file name ", "ACL1012-DTD.xml", r->getFileName());
        Assert::assertEquals("DCC Address ", "1012", r->getDccAddress());
        Assert::assertEquals("road name ", "Atlantic Coast Line", r->getRoadName());
        Assert::assertEquals("road number ", "1012", r->getRoadNumber());
        Assert::assertEquals("model ", "Synch Diesel Sound 1812 - N Scale Atlas Short Board Dropin", r->getDecoderModel());
        Assert::assertEquals("family ", "Brilliance Sound Decoders", r->getDecoderFamily());
    }

    //@Test
    /*public*/ void RosterEntryTest::testStoreFunctionLabel() {
        RosterEntry* r = new RosterEntry("file here");

        r->setFunctionLabel(3, "tree");
        Assert::assertEquals("tree", r->getFunctionLabel(3));
        Assert::assertEquals("", r->getFunctionLabel(4));

    }

    //@Test
    /*public*/ void RosterEntryTest::testModifyDateUnparseable() {
        RosterEntry* r = new RosterEntry("file here");

        r->setId("test Id");
        r->setDateUpdated("unparseable date");
#if 0
        JUnitAppender::assertWarnMessage("Unable to parse \"unparseable date\" as a date in roster entry \"test Id\".");
#else
        log->warn("Unable to parse \"unparseable date\" as a date in roster entry \"test Id\".");
#endif
    }

    //@Test
    /*public*/ void RosterEntryTest::testDateFormatHistoric() {
        RosterEntry* r = new RosterEntry("file here");

        r->setId("test Id");
#if 0
        TimeZone tz = TimeZone.getDefault();
        try {
            TimeZone.setDefault(TimeZone.getTimeZone("GMT-7"));
            r->setDateUpdated("03-Oct-2015 11:19:12"); // this is in local time
        } finally {
            TimeZone.setDefault(tz);
        }
#endif
#if 0
        Assert::assertTrue(jmri.util.JUnitAppender.verifyNoBacklog());
#endif
        Assert::assertEquals("2015-10-03T18:19:12.000+0000", r->getDateUpdated());
    }

    //@Test
    /*public*/ void RosterEntryTest::testDateFormatISO() {
        RosterEntry* r = new RosterEntry("file here");

        r->setId("test Id");
        r->setDateUpdated("2018-03-05T02:34:55Z");
#if 0
        Assert::assertTrue(jmri.util.JUnitAppender.verifyNoBacklog());
#endif
        Assert::assertEquals("2018-03-05T02:34:55.000+0000", r->getDateUpdated());
    }

    //@Test
    /*public*/ void RosterEntryTest::testDateFormatTraditional() throw (ParseException) {
        RosterEntry* r = new RosterEntry("file here");

        r->setId("test Id");
#if 0
        TimeZone tz = TimeZone.getDefault();
        try {
            TimeZone.setDefault(TimeZone.getTimeZone("GMT-7"));
            r->setDateUpdated("Mar 2, 2016 9:57:04 AM"); // this is in local time
        } finally {
            TimeZone.setDefault(tz);
        }
#endif
#if 0
        Assert::assertTrue(jmri.util.JUnitAppender.verifyNoBacklog());
#endif

        // convert that same local time in ISO format and compare
        Assert::assertEquals("2016-03-02T16:57:04.000+0000", r->getDateUpdated());
    }

    //@Test
    /*public*/ void RosterEntryTest::testStoreFunctionLockable() {
        RosterEntry* r = new RosterEntry("file here");

        r->setFunctionLabel(3, "tree");
        r->setFunctionLockable(3, true);

        r->setFunctionLabel(4, "fort");
        r->setFunctionLockable(4, false);

        Assert::assertEquals("tree", r->getFunctionLabel(3));
        Assert::assertEquals(true, r->getFunctionLockable(3));
        Assert::assertEquals("fort", r->getFunctionLabel(4));
        Assert::assertEquals(false, r->getFunctionLockable(4));
        Assert::assertEquals("", r->getFunctionLabel(5));

    }

    //@Test
    /*public*/ void RosterEntryTest::testXmlLoadStore() {
        // create Element
        QDomElement e =  QDomElement(); e.setTagName("locomotive");
                e.setAttribute("id", "our id 4");
                e.setAttribute("fileName", "file here");
                e.setAttribute("roadNumber", "431");
                e.setAttribute("mfg", "Athearn");
                e.setAttribute("dccAddress", "1234");
                QDomElement e1;
                e.appendChild(e1 = QDomElement()); e1.setTagName("decoder");
                        e1.setAttribute("family", "91");
                        e1.setAttribute("model", "33");

//        RosterEntry r = new RosterEntry(e) {
//            @Override
//            protected void warnShortLong(String s) {
//            }
//        };
        RosterEntryO1* r = new RosterEntryO1();

        QDomDocument doc;
        QDomElement o = r->store(doc);
        // check
#if 0
        Assert::assertEquals("XML Element ", e.toString(), o.toString());
#endif
        Assert::assertEquals("family ", "91", o.firstChildElement("decoder").attribute("family"));
        Assert::assertEquals("model ", "33", o.firstChildElement("decoder").attribute("model"));
    }

    //@Test
    /*public*/ void RosterEntryTest::testXmlFunctionLabelsLoadStore() {
        QDomDocument doc;
        // create Element
        QDomElement e =  doc.createElement("locomotive");
                e.setAttribute("id", "our id 4");
                e.setAttribute("fileName", "file here");
                e.setAttribute("roadNumber", "431");
                e.setAttribute("roadName", "SP");
                e.setAttribute("mfg", "Athearn");
                e.setAttribute("dccAddress", "1234");
                QDomElement e1, e2;
                e.appendChild(e1 = doc.createElement("decoder"));
                        e1.setAttribute("family", "91");
                        e1.setAttribute("model", "33");
                e.appendChild(e1 = doc.createElement("functionlabels"));
                        e1.appendChild(e2 = doc.createElement("functionlabel"));
                                e2.setAttribute("num", "2");
                                e2.setAttribute("lockable", "true");
                                e2.appendChild(doc.createTextNode("label 2"));
                        e1.appendChild(e2 = doc.createElement("functionlabel"));
                                e2.setAttribute("num", "3");
                                e2.setAttribute("lockable", "false");
                                e2.appendChild(doc.createTextNode("label 3"));

//        RosterEntry* r = new RosterEntry(e) {
//            @Override
//            protected void warnShortLong(String s) {
//            }
//        };
        RosterEntryO1* r = new RosterEntryO1();

        // check loaded
        Assert::assertEquals("", r->getFunctionLabel(1));
        Assert::assertEquals("label 2", r->getFunctionLabel(2));
        Assert::assertEquals("lockable 2", true, r->getFunctionLockable(2));
        Assert::assertEquals("label 3", r->getFunctionLabel(3));
        Assert::assertEquals("lockable 2", false, r->getFunctionLockable(3));
        Assert::assertEquals("", r->getFunctionLabel(4));

        QDomElement o = r->store(doc);

        // check stored element
        Assert::assertEquals("num 2", "2", o.firstChildElement("functionlabels").firstChildElement("functionlabel").attribute("num"));
        Assert::assertEquals("lockable 2", "true", o.firstChildElement("functionlabels").firstChildElement("functionlabel").attribute("lockable"));
        Assert::assertEquals("label 2", "label 2", o.firstChildElement("functionlabels").firstChildElement("functionlabel").text());
    }

    //@Test
    /*public*/ void RosterEntryTest::testEnsureFilenameExistsNew() {
        RosterEntry* r = new RosterEntry();
        Assert::assertEquals("initial filename ", "", r->getFileName());
        r->setId("test Roster Entry 123456789ABC");
        Assert::assertEquals("initial ID ", "test Roster Entry 123456789ABC", r->getId());
        File* f = new File(Roster::getDefault()->getRosterFilesLocation() + "test_Roster_Entry_123456789ABC.xml");
        if (f->exists()) {
            f->_delete();
        }
        r->ensureFilenameExists();
        Assert::assertEquals("final filename ", "test_Roster_Entry_123456789ABC.xml", r->getFileName());
        if (f->exists()) {
            f->_delete();  // clean up afterwards
        }
    }

    //@Test
    /*public*/ void RosterEntryTest::testEnsureFilenameExistsOld() throw (IOException) {
        FileUtil::createDirectory(Roster::getDefault()->getRosterFilesLocation());
        RosterEntry* r = new RosterEntry();
        Assert::assertEquals("initial filename ", "", r->getFileName());
        r->setId("test Roster Entry 123456789ABC");
        Assert::assertEquals("initial ID ", "test Roster Entry 123456789ABC", r->getId());
        File* f1 = new File(Roster::getDefault()->getRosterFilesLocation() + "test_Roster_Entry_123456789ABC.xml");
        if (!f1->exists()) {
            // create a dummy
#if 0
            FileOutputStream f = new FileOutputStream(f1);
            f.write(0);
            f.close();
#endif
        }
        File* f2 = new File(Roster::getDefault()->getRosterFilesLocation() + "test_Roster_Entry_123456789ABC0.xml");
        if (!f2->exists()) {
            // create a dummy
#if 0
            FileOutputStream f = new FileOutputStream(f2);
            f.write(0);
            f.close();
#endif
        }
        r->ensureFilenameExists();
        Assert::assertEquals("final filename ", "test_Roster_Entry_123456789ABC1.xml", r->getFileName());
        if (f1->exists()) {
            f1->_delete();  // clean up afterwards
        }
        if (f2->exists()) {
            f2->_delete();
        }
    }

    //@Test
    /*public*/ void RosterEntryTest::testNoAttribute() {
        RosterEntry* r = new RosterEntry();
        Assert::assertNull(r->getAttribute("foo"));
    }

    //@Test
    /*public*/ void RosterEntryTest::testOneAttribute() {
        RosterEntry* r = new RosterEntry();
        r->putAttribute("foo", "bar");
        Assert::assertEquals("bar", r->getAttribute("foo"));
    }

    //@Test
    /*public*/ void RosterEntryTest::testReplaceAttribute() {
        RosterEntry* r = new RosterEntry();
        r->putAttribute("foo", "bar");
        r->putAttribute("foo", "a nicer bar");
        Assert::assertEquals("a nicer bar", r->getAttribute("foo"));
    }

    //@Test
    /*public*/ void RosterEntryTest::testNullAttributeValue() {
        RosterEntry* r = new RosterEntry();
        r->putAttribute("foo", "bar");
        r->putAttribute("foo", "");
        Assert::assertNull(r->getAttribute("foo"));
    }

    //@Test
    /*public*/ void RosterEntryTest::testAttributeList() {
        RosterEntry* r = new RosterEntry();
        r->putAttribute("key 2", "value 2");
        r->putAttribute("key 3", "value 3");
        r->putAttribute("key 1", "value 1");
        QSet<QString> l = r->getAttributes();
        Assert::assertEquals("number returned", 3, l.size());
       QSetIterator<QString> i(l);
        Assert::assertEquals("1st item", "key 1", i.next());
        Assert::assertEquals("2nd item", "key 2", i.next());
        Assert::assertEquals("3rd item", "key 3", i.next());
        Assert::assertTrue(!i.hasNext());
    }

    //@Test
    /*public*/ void RosterEntryTest::testXmlAttributesLoadStore() {
        // create Element
    QDomDocument doc;
        QDomElement e = doc.createElement("locomotive");
                e.setAttribute("id", "our id 4");
                e.setAttribute("fileName", "file here");
                e.setAttribute("roadNumber", "431");
                e.setAttribute("roadName", "SP");
                e.setAttribute("mfg", "Athearn");
                e.setAttribute("dccAddress", "1234");
                QDomElement e1, e2, e3;
                e.appendChild(e1 =doc.createElement("decoder"));
                        e1.setAttribute("family", "91");
                        e1.setAttribute("model", "33");
                e.appendChild(e1 = doc.createElement("attributepairs"));
                        e1.appendChild(e2 = doc.createElement("keyvaluepair"));
                                e2.appendChild(e3 = doc.createElement("key"));
                                        e3.appendChild(doc.createTextNode("key 1"));
                                e2.appendChild(e3 = doc.createElement("value"));
                                        e3.appendChild(doc.createTextNode("value 1"));
                        e1.appendChild(e2 = doc.createElement("keyvaluepair"));
                                e2.appendChild(e3 = doc.createElement("key"));
                                        e3.appendChild(doc.createTextNode("key 2"));
                                e2.appendChild(e3 = doc.createElement("value"));
                                        e3.appendChild(doc.createTextNode("value 2"));

//        RosterEntry* r = new RosterEntry(e) {
//            @Override
//            protected void warnShortLong(QString s) {
//            }
//        };
        RosterEntryO1* r = new RosterEntryO1();


        Assert::assertEquals("value 1", r->getAttribute("key 1"));
        Assert::assertEquals("value 2", r->getAttribute("key 2"));
        Assert::assertEquals("", r->getAttribute("key 4"));
    }

    //@Test
    /*public*/ void RosterEntryTest::testStoreAttribute() {
        RosterEntry* r = new RosterEntry("dummy filename");
        r->putAttribute("foo", "bar");

        QDomDocument doc;
        QDomElement e = r->store(doc);
        Assert::assertNotNull(e);
        Assert::assertNotNull(e.firstChildElement("attributepairs"));
        Assert::assertNotNull(e.firstChildElement("attributepairs")
                .firstChildElement("keyvaluepair"));
        Assert::assertNotNull(e.firstChildElement("attributepairs")
                .firstChildElement("keyvaluepair")
                .firstChildElement("key"));
        Assert::assertNotNull(e.firstChildElement("attributepairs")
                .firstChildElement("keyvaluepair")
                .firstChildElement("value"));
        Assert::assertEquals("foo", e.firstChildElement("attributepairs")
                .firstChildElement("keyvaluepair")
                .firstChildElement("key").text());
        Assert::assertNotNull("bar", e.firstChildElement("attributepairs"));
                e.firstChildElement("keyvaluepair");
                e.firstChildElement("value").text();
    }

    //@Before
    /*public*/ void RosterEntryTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();
        InstanceManager::setDefault("RosterConfigManager", (new RosterConfigManager()));
    }

    //@After
    /*public*/ void RosterEntryTest::tearDown() {
        JUnitUtil::tearDown();
    }

/*static*/ Logger* RosterEntryTest::log = LoggerFactory::getLogger("RosterEntryTest");
