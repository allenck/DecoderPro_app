#include "lncvprogpanetest.h"
#include "assert1.h"
#include "loconetmessage.h"
#include "loconet/loconetinterfacescaffold.h"
#include "instancemanager.h"
#include "rosterconfigmanager.h"
#include "slotmanager.h"
#include "lncvdevice.h"


LncvProgPaneTest::LncvProgPaneTest()
{

}
/**
 * Test of the LNCV Programming Pane tool.
 *
 * @author Egbert Broerse   Copyright 2021
 * @author Paul Bender Copyright (C) 2017
 */
// /*public*/ class LncvProgPaneTest extends jmri.util.swing.JmriPanelTest {


    //@Test
    /*public*/ void LncvProgPaneTest::testCTor() {
        //Assumptions.assumeFalse(GraphicsEnvironment.isHeadless());
        LncvProgPane* p = new LncvProgPane();
        Assertions::assertNotNull((QObject*)p, "exists", __FILE__, __LINE__);
    }

    //@Override
    //@Test
    /*public*/ void LncvProgPaneTest::testInitComponents() //throw (Exception)
    {
        // for now, just makes sure there isn't an exception.
        panel->initComponents(memo);
    }

    //@Test
    //@Override
    /*public*/ void LncvProgPaneTest::testGetHelpTarget(){
        Assertions::assertEquals(helpTarget, panel->getHelpTarget(), "help target", __FILE__, __LINE__);
    }

    //@Test
    //@Override
    /*public*/ void LncvProgPaneTest::testGetTitle(){
        Assertions::assertEquals(title, panel->getTitle(), "title", __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LncvProgPaneTest::testDispose() {
        //Assumptions.assumeFalse(GraphicsEnvironment.isHeadless());
        LncvProgPane* p = new LncvProgPane();
        p->initComponents(memo);
        Assertions::assertTrue(p->isVisible(), "LNCV running = visible", __FILE__, __LINE__);
        Assertions::assertNotNull(p, "exists", __FILE__, __LINE__);
        p->dispose();
        Assertions::assertFalse(p->isVisible(), "disposed = invisible", __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LncvProgPaneTest::testPanel() {
        //Assumptions.assumeFalse(GraphicsEnvironment.isHeadless());
        LncvDevicesManager* lcdm = memo->getLncvDevicesManager();
        panel->initComponents(memo); // set up stuff
        panel->initComponents();
        // test list
        Assertions::assertNull((QObject*)panel->getModule(0), "Get LncvModule 0 from empty list", __FILE__, __LINE__);
#if 0
        QThread* dialog_thread1 = new QThread([=]() -> void{
            JDialogOperator* jfo = new JDialogOperator(tr("Warning") );
            (new JButtonOperator(jfo, tr("Proceed")))->doClick();
        });
#endif
        QThread* dialog_thread1 = new QThread();
        Work1* wrk = new Work1(dialog_thread1);
        dialog_thread1->setObjectName("BroadcastAll Dialog button Proceed clicked");
        dialog_thread1->start();

        panel->allProgButtonActionPerformed();

//        //JUnitUtil::waitFor([=]()-> bool {return !(dialog_thread1->isRunning());}, "BroadcastAll Warning Dialog closed", __FILE__, __LINE__);
//        auto ready = [=]()-> bool {return !(dialog_thread1->isRunning());};
        JUnitUtil::waitFor(new Lncvppt_ready(dialog_thread1), "BroadcastAll Warning Dialog closed", __FILE__, __LINE__);

        Assertions::assertEquals("locked", panel->getAddressEntry(), "AddressField locked", __FILE__, __LINE__);

        panel->allProgButtonActionPerformed(); // second click "Stop" will release buttons
        Assertions::assertEquals("1", panel->getAddressEntry(), "AddressField unlocked", __FILE__, __LINE__);

        lcdm->message(new LocoNetMessage(QVector<int>{0xE5, 0x0F, 0x05, 0x49, 0x4B, 0x1F, 0x11, 0x29, 0x13, 0x00, 0x00, 0x08, 0x00, 0x00, 0x4D}));
        Assertions::assertEquals(1, lcdm->getDeviceCount(), "modules in devman list after add", __FILE__, __LINE__);
        Assertions::assertEquals(5033, panel->getModule(0)->getProductID(), "ProductID of LncvModule at index 0 after adding", __FILE__, __LINE__);
        // add same module to monitor, adding it to table and filling in texts entry fields
        panel->message(new LocoNetMessage(QVector<int>{0xE5, 0x0F, 0x05, 0x49, 0x4B, 0x1F, 0x11, 0x29, 0x13, 0x00, 0x00, 0x08, 0x00, 0x00, 0x4D}));
        Assertions::assertEquals("", panel->getArticleEntry(), "Article field still empty", __FILE__, __LINE__);

        panel->copyEntry(8888, 77);
        Assertions::assertEquals("8888", panel->getArticleEntry(), "ProductID copied to Article field", __FILE__, __LINE__);

        panel->modProgButtonActionPerformed();
        Assertions::assertEquals("locked", panel->getAddressEntry(), "AddressField locked", __FILE__, __LINE__);

        panel->setCvFields(1, 100); // enter some values for read
        panel->readButtonActionPerformed();
        // no feedback, just confirm no exception is thrown
        panel->writeButtonActionPerformed();
        LocoNetMessage* l = new LocoNetMessage(QVector<int>{0xB4, 0x6D, 0x7F, 0x59}); // OPC_LONG_ACK
        panel->message(l); // check in monitor
        Assertions::assertEquals("confirmed by module 77\n", panel->getMonitorContents().mid(panel->getMonitorContents().length() - 23), "Write confirmed in Monitor", __FILE__, __LINE__);

        panel->modProgButtonActionPerformed(); // to turn programming off
        Assertions::assertEquals("77", panel->getAddressEntry(), "AddressField 77", __FILE__, __LINE__);
    }

    //@Override
    //@BeforeEach
    /*public*/ void LncvProgPaneTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initDefaultUserMessagePreferences();

        // prepare an interface, register
        LnTrafficController* lnis = new LocoNetInterfaceScaffold();
        SlotManager* slotmanager = new SlotManager(lnis);
        memo = new LocoNetSystemConnectionMemo(lnis, slotmanager);

        InstanceManager::setDefault("LocoNetSystemConnectionMemo", memo);
        InstanceManager::setDefault("RosterConfigManager", new RosterConfigManager());

        // pane for LncvProg
        panel = new LncvProgPane();
        //panel->initComponents(memo);
        helpTarget = "package.jmri.jmrix.loconet.swing.lncvprog.LncvProgPane";
        title = tr("Configure LNCV Modules");
        panel->pack();
        panel->setVisible(true);
    }

    //@Override
    //@AfterEach
    /*public*/ void LncvProgPaneTest::tearDown() {
        panel = nullptr;

        JUnitUtil::tearDown();
    }
