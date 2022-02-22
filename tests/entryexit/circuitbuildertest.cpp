#include "circuitbuildertest.h"
#include "loggerfactory.h"
#include "controlpaneleditor.h"
#include "circuitbuilder.h"
#include "assert1.h"
#include "junitutil.h"
#include "file.h"
#include "jframeoperator.h"
#include "instancemanager.h"
#include "configuremanager.h"
#include "oblock.h"
#include "oblockmanager.h"
#include "jemmyutil.h"
#include "portalmanager.h"

CircuitBuilderTest::CircuitBuilderTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test simple functioning of the CircuitBuilder class.
 *
 * @author  Paul Bender Copyright (C) 2017
 * @author  Pete Cressman Copyright (C) 2019
 */
///*public*/ class CircuitBuilderTest {


    //@Test
    /*public*/ void CircuitBuilderTest::testCtor() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        ControlPanelEditor* f = new ControlPanelEditor();
        CircuitBuilder* builder = new CircuitBuilder(f);
        Assert::assertNotNull("exists", builder, __FILE__, __LINE__);
        f->dispose();
        JUnitUtil::dispose(f);
    }

    //@Test
    /*public*/ void CircuitBuilderTest::testEditCircuitFrame() {
        getCPEandCB();

        OBlock* ob3 = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock("OB3");
        cb->setCurrentBlock(ob3);

        cb->editCircuit(tr("Edit Circuit OBlock"), false);
        Assert::assertNotNull("exists", (QWidget*)cb->getEditFrame(), __FILE__, __LINE__);
/*
        cb.editCircuit("editCircuitItem", true);
        JDialogOperator jdo = new JDialogOperator(Bundle.getMessage("editCircuitItem"));
        JTableOperator table = new JTableOperator(jdo);
        table.clickOnCell(3, 2);
        JButtonOperator button = new JButtonOperator(table, Bundle.getMessage("ButtonOpenCircuit"));
        button.doClick();
      */

        JFrameOperator* editFrame = new JFrameOperator((JmriJFrame*)cb->getEditFrame());
        JemmyUtil::pressButton(editFrame, tr("Done"));
    }

    //@Test
    /*public*/ void CircuitBuilderTest::testEditCircuitError() {
        getCPEandCB();

        cb->editCircuitError("OB1");

        JFrameOperator* nfo = new JFrameOperator((JmriJFrame*)cb->getEditFrame());
        JemmyUtil::pressButton(nfo, tr("Done"));
    }

    //@Test
    /*public*/ void CircuitBuilderTest::testEditPortals() {
        getCPEandCB();

        OBlock* ob3 = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock("OB2");
        cb->setCurrentBlock(ob3);

        cb->editPortals(tr("Add/Edit Circuit Portals"), false);

        JFrameOperator* nfo = new JFrameOperator((JmriJFrame*)cb->getEditFrame());
        JemmyUtil::pressButton(nfo, tr("Done"));
    }
#if 1
    //@Test
    /*public*/ void CircuitBuilderTest::testEditCircuitPaths() {
        getCPEandCB();

        OBlock* ob3 = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock("OB3");
        cb->setCurrentBlock(ob3);

        cb->editCircuitPaths("editCircuitPathsItem", false);

        JFrameOperator* nfo = new JFrameOperator((JmriJFrame*)cb->getEditFrame());
        JemmyUtil::pressButton(nfo, tr("Done"));
    }

    //@Test
    /*public*/ void CircuitBuilderTest::testEditPortalDirection() {
        getCPEandCB();

        OBlock* ob3 = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock("OB5");
        cb->setCurrentBlock(ob3);

        cb->editPortalDirection("editDirectionItem", false);

        JFrameOperator* nfo = new JFrameOperator((JmriJFrame*)cb->getEditFrame());
        JemmyUtil::pressButton(nfo, tr("Done"));
    }

    //@Test
    /*public*/ void CircuitBuilderTest::testEditSignalFrame() {
        getCPEandCB();

        OBlock* ob3 = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock("OB4");
        cb->setCurrentBlock(ob3);

        cb->editSignalFrame("editSignalItem", false);

        JFrameOperator* nfo = new JFrameOperator((JmriJFrame*)cb->getEditFrame());
        JemmyUtil::pressButton(nfo, tr("Done"));
    }

    //@Test
//    @org.junit.Ignore ("'OK' button does not dismiss dialog.")
    /*public*/ void CircuitBuilderTest::testEditPortalError() {
        getCPEandCB();

//        new Thread(() -> {
            JFrameOperator* jfo = new JFrameOperator("Edit \"WestSiding\" Portals");
            JDialogOperator* jdo = new JDialogOperator(jfo, tr("Track Circuit Incomplete"));
            JButtonOperator* jbo = new JButtonOperator(jdo, "OK");
            jbo->push();
//        }).start();

        cb->editPortalError("EastExit-EastJunction");

        JFrameOperator* nfo = new JFrameOperator((JmriJFrame*)cb->getEditFrame());
        JemmyUtil::pressButton(nfo, tr("Done"));
//        new org.netbeans.jemmy.QueueTool().waitEmpty(100);
        cpe->dispose();
    }

    //@Test
    /*public*/ void CircuitBuilderTest::testEditPortalErrorIcon() throw (Exception){
        getCPEandCB();

        OBlock* block = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getByUserName("WestSiding")->self();
        Portal* portal = ((PortalManager*)InstanceManager::getDefault("PortalManager"))->getPortal("Crapolla");
//        new Thread(() -> {
            JFrameOperator* jfo = new JFrameOperator("Edit \"WestSiding\" Portals");
            JDialogOperator* jdo = new JDialogOperator(jfo, tr("Track Circuit Incomplete"));
            JButtonOperator* jbo = new JButtonOperator(jdo, "OK");
            jbo->push();
//        }).start();

        cb->editPortalError(block, portal, nullptr);

        JFrameOperator* nfo = new JFrameOperator((JmriJFrame*)cb->getEditFrame());
        JemmyUtil::pressButton(nfo, tr("Done"));
    }

    //@Test
    //@org.junit.Ignore("Cannot get button pushed!")
    /*public*/ void CircuitBuilderTest::testNoBlock() {
        getCPEandCB();
        cb->editCircuitPaths("editCircuitPathsItem", false);

//        JFrameOperator frame = new JFrameOperator(cb.getEditFrame());
//        JDialogOperator jdo = new JDialogOperator(frame, Bundle.getMessage("NeedDataTitle"));
        JDialogOperator* jdo = new JDialogOperator(tr("Please enter Data"));
        JButtonOperator* ok = new JButtonOperator(jdo, "OK");
        ok->push();
    }
#endif
    void CircuitBuilderTest::getCPEandCB() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        File* f = new File("java/test/jmri/jmrit/display/controlPanelEditor/valid/CircuitBuilderTest.xml");
        try {
            ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->load(f);
        } catch(JmriException* je) {
            log->error("CircuitBuilderTest can't load CircuitBuilderTester.xml %1", je);
        }
        cpe = (ControlPanelEditor*) JmriJFrame::getFrame("CircuitBuilderTest Editor");
        Assert::assertNotNull("exists", cpe , __FILE__, __LINE__);
        cb = cpe->getCircuitBuilder();
        Assert::assertNotNull("exists", cb , __FILE__, __LINE__);
    }

    //@Before
    /*public*/ void CircuitBuilderTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initOBlockManager();
    }

    //@After
    /*public*/ void CircuitBuilderTest::tearDown() {
        if (cpe != nullptr) {
            cpe->dispose();
        }
        JUnitUtil::tearDown();
    }
    /*private*/ /*final*/ /*static*/ Logger* CircuitBuilderTest::log = LoggerFactory::getLogger("CircuitBuilderTest");
