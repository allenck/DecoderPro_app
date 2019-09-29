#include "rosterentrypanetest.h"
#include "assert1.h"
#include "junitutil.h"
#include "rosterentrypane.h"
#include "instancemanager.h"
#include "roster.h"
#include "loggerfactory.h"
#include <QApplication>

RosterEntryPaneTest::RosterEntryPaneTest(QObject *parent) : QObject(parent)
{
    // statics for test objects
    eOld = QDomElement();
    eNew = QDomElement();
}
/**
 * Tests for the jmrit.roster.RosterEntryPane class.
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2002
 */
///*public*/ class RosterEntryPaneTest {


    //@Before
/*public*/ void RosterEntryPaneTest::setUp() {
    JUnitUtil::setUp();
    JUnitUtil::resetProfileManager();
    JUnitUtil::initRosterConfigManager();
    doc = QDomDocument();
    // create Element
    eOld = doc.createElement("locomotive");
    eOld.setAttribute("id", "id info");
    eOld.setAttribute("fileName", "file here");
    eOld.setAttribute("roadNumber", "431");
    eOld.setAttribute("roadName", "SP");
    eOld.setAttribute("mfg", "Athearn");
    eOld.setAttribute("dccAddress", "1234");
    QDomElement e1, e2, e3;
    eOld.appendChild(e1 = doc.createElement("decoder"));
    e1.setAttribute("family", "91");
    e1.setAttribute("model", "33");

    eOld.appendChild(e1 = doc.createElement("locoaddress"));
    e1.appendChild(e2 = doc.createElement("number"));
    e2.appendChild(doc.createTextNode("1234"));
    //As there is no throttle manager available all protocols default to dcc short
    e1.appendChild(e3=doc.createElement("protocol"));
    e3.appendChild(doc.createTextNode("dcc_short"));
    doc.appendChild(eOld);
    log->info(tr("eOld doc: %1").arg(doc.toString()));
//        rOld = new RosterEntry(eOld) {
//            @Override
//            protected void warnShortLong(String s) {
//            }
//        };

    rOld = new RosterEntryO2(eOld);

    doc = QDomDocument();
    eNew = doc.createElement("locomotive");
    eNew.setAttribute("id", "id info");
    eNew.setAttribute("fileName", "file here");
    eNew.setAttribute("roadNumber", "431");
    eNew.setAttribute("roadName", "SP");
    eNew.setAttribute("mfg", "Athearn");
    eNew.appendChild(e1 =doc.createElement("decoder"));
            e1.setAttribute("family", "91");
            e1.setAttribute("model", "33");
    doc.appendChild(eNew);
//        rNew = new RosterEntry(eNew) {
//            @Override
//            protected void warnShortLong(String s) {
//            }
//        };
    log->info(tr("eNew doc: %1").arg(doc.toString()));

    rNew = new RosterEntryO2(eNew);
}

//@After
/*public*/ void RosterEntryPaneTest::tearDown() {
    JUnitUtil::tearDown();
}

//@Test
/*public*/ void RosterEntryPaneTest::testCreate() {
    RosterEntryPane* p = new RosterEntryPane(rOld);

    // copy to a new entry
//        RosterEntry* n = new RosterEntry() {
//            @Override
//            protected void warnShortLong(String s) {
//            }
//        };
    RosterEntryO2* n = new RosterEntryO2();
    p->update(n);

    p->show();

    qApp->processEvents();

    // check for field text contents
    Assert::assertEquals("file name returned", "", n->getFileName(),__FILE__, __LINE__);
    Assert::assertEquals("DCC Address ", "1234", n->getDccAddress(),__FILE__, __LINE__);
    Assert::assertEquals("road name ", "SP", n->getRoadName(),__FILE__, __LINE__);
    Assert::assertEquals("road number ", "431", n->getRoadNumber(),__FILE__, __LINE__);
    Assert::assertEquals("manufacturer ", "Athearn", n->getMfg(),__FILE__, __LINE__);
    Assert::assertEquals("model ", "33", n->getDecoderModel(),__FILE__, __LINE__);
    Assert::assertEquals("family ", "91", n->getDecoderFamily(),__FILE__, __LINE__);

    p->hide();
}

void RosterEntryO2::warnShortLong(QString s) {
}

//@Test
/*public*/ void RosterEntryPaneTest::testGuiChanged1() {
    RosterEntryPane* p = new RosterEntryPane(rOld);
    p->show();


    // copy to a new entry
    // check for unchanged
    Assert::assertTrue("initially unchanged", !p->guiChanged(rOld),__FILE__, __LINE__);

    // change the roster road name entry and check
    rOld->setRoadName("changed value");
    Assert::assertTrue("detects change", p->guiChanged(rOld),__FILE__, __LINE__);

}

//@Test
/*public*/ void RosterEntryPaneTest::testGuiChanged2() {
    RosterEntryPane* p = new RosterEntryPane(rOld);

    // copy to a new entry
    // check for unchanged
    Assert::assertTrue("initially unchanged", !p->guiChanged(rOld),__FILE__, __LINE__);

    // change the roster road name entry and check
    rOld->setDccAddress("4321");
    Assert::assertTrue("detects change", p->guiChanged(rOld),__FILE__, __LINE__);

}

//@Test
/*public*/ void RosterEntryPaneTest::testGuiChanged3() {

    RosterEntryPane* p = new RosterEntryPane(rNew);
    // copy to a new entry

    // check for unchanged
    Assert::assertTrue("initially unchanged", !p->guiChanged(rNew),__FILE__, __LINE__);

    // change the roster address type entry and check
    rNew->setDccAddress("1234");
    Assert::assertTrue("detects change", p->guiChanged(rNew),__FILE__, __LINE__);

}

//@Test
/*public*/ void RosterEntryPaneTest::testGuiChanged4() {
    RosterEntryPane* p = new RosterEntryPane(rNew);
    // copy to a new entry

    // check for unchanged
    Assert::assertTrue("initially unchanged", !p->guiChanged(rNew),__FILE__, __LINE__);

    // change the roster address type entry and check
    rNew->setDccAddress("4321");
    Assert::assertTrue("detects change", p->guiChanged(rNew),__FILE__, __LINE__);

}

//@Test
/*public*/ void RosterEntryPaneTest::testGuiChanged5() {
    RosterEntryPane* p = new RosterEntryPane(rNew);
    // copy to a new entry

    // check for unchanged
    Assert::assertTrue("initially unchanged", !p->guiChanged(rNew),__FILE__, __LINE__);

    // change the roster address type entry and check
    rNew->setDccAddress("12");
    p->setDccAddressLong(false);
    Assert::assertTrue("detects change", p->guiChanged(rNew),__FILE__, __LINE__);

}

//@Test
/*public*/ void RosterEntryPaneTest::testNotDuplicate() {
    RosterEntryPane* p = new RosterEntryPane(rNew);
    // reset Roster
    InstanceManager::reset("Roster");
    InstanceManager::setDefault("Roster", new Roster(nullptr));
    Assert::assertTrue(!p->checkDuplicate(),__FILE__, __LINE__);
}

//@Test
/*public*/ void RosterEntryPaneTest::testIsDuplicate() {
    RosterEntryPane* p = new RosterEntryPane(rNew);
    // reset Roster
    InstanceManager::reset("Roster");
    InstanceManager::setDefault("Roster", new Roster(nullptr));
    Roster::getDefault()->addEntry(rNew);

    Assert::assertTrue(!p->checkDuplicate(),__FILE__, __LINE__);
}

//@Test
/*public*/ void RosterEntryPaneTest::testRenamedDuplicate() {
    RosterEntryPane* p = new RosterEntryPane(rOld);
    // reset Roster
    InstanceManager::reset("Roster");
    InstanceManager::setDefault("Roster", new Roster(""));
    Roster::getDefault()->addEntry(rNew);

    // reset entry
    p->id()->setText("new id");
    p->update(rNew);

    Assert::assertTrue(p->checkDuplicate(),__FILE__, __LINE__);
}

Logger* RosterEntryPaneTest::log = LoggerFactory::getLogger("RosterEntryPaneTest");
