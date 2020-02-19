#include "defaultcabsignaltest.h"
#include "loggerfactory.h"
#include "assert1.h"
#include "blockmanager.h"
//#include "defaultrailcom.h"
#include "layoutblockmanager.h"
#include "configuremanager.h"
#include "panelmenu.h"
#include "signalmastlogicmanager.h"
#include "signalmastlogic.h"
#include "logixmanager.h"
#include "layoutblockmanager.h"
#include "signalmastmanager.h"
#include "sleeperthread.h"
#include "vptr.h"
#include "connectivityutil.h"

DefaultCabSignalTest::DefaultCabSignalTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2019
 */
///*public*/ class DefaultCabSignalTest {


    //@Test
    /*public*/ void DefaultCabSignalTest::testCTor() {
        Assert::assertNotNull("exists",cs, __FILE__, __LINE__);
        //check the defaults.
        Assert::assertEquals("Address",new DccLocoAddress(1234,true),cs->getCabSignalAddress(), __FILE__, __LINE__);
        Assert::assertNull("current block",cs->getBlock(), __FILE__, __LINE__);
        Assert::assertNull("next block",cs->getNextBlock(), __FILE__, __LINE__);
        Assert::assertNull("next mast",cs->getNextMast(), __FILE__, __LINE__);
        Assert::assertTrue("cab signal active",cs->isCabSignalActive(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DefaultCabSignalTest::testSetBlock() {
//        DefaultCabSignal* acs = new DefaultCabSignal(new DccLocoAddress(1234,true)){
//            @Override
//            /*public*/ jmri.SignalMast getNextMast(){
//               // don't check for signal masts, they aren't setup for this
//               // test.
//               return null;
//            }
//        };
        DefaultCabSignal* acs = new DefaultCabSignalO1(new DccLocoAddress(1234,true), this);

        Block* b1 = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->provideBlock("IB12");
        // set the block contents to our locomotive address.
        b1->setValue(VPtr<DccLocoAddress>::asQVariant(new DccLocoAddress(1234,true)));
        // call setBlock() for the cab signal.
        acs->setBlock();
        // and verify getBlock returns the block we set.
        Assert::assertEquals("Block set",b1,acs->getBlock(), __FILE__, __LINE__);

        acs->dispose(); // verify no exceptions
    }

    //@Test
    /*public*/ void DefaultCabSignalTest::testSignalSequence() throw (JmriException) {
        runSequence(VPtr<DccLocoAddress>::asQVariant(new DccLocoAddress(1234,true)));
    }

    //@Test
//    /*public*/ void DefaultCabSignalTest::testSignalSequenceIdTag() throw (JmriException) {
//        runSequence(new DefaultRailCom("ID1234","Test Tag"));
//    }

    /*protected*/ void DefaultCabSignalTest::runSequence(QVariant initialBlockContents) throw (JmriException) {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        // load and display test panel file
        ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->setStabilisedSensor("IS_ROUTING_DONE");

        File* f = new File("java/test/jmri/jmrit/cabsignals/SimpleCabSignalTestPanel.xml");
        ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->load(f);

        // Find new window by name (should be more distinctive, comes from sample file)
        EditorFrameOperator* to = new EditorFrameOperator("Cab Signal Test");
        LayoutEditor* le = (LayoutEditor*) JmriJFrame::getFrame("Cab Signal Test");
        ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->addEditorPanel(le);
        SignalMastLogicManager* smlm = (SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager");
        smlm->initialise();
        for(SignalMastLogic* sml:smlm->getSignalMastLogicList()) {
            sml->setupLayoutEditorDetails();
        }

        // Panel is up, continue set up for tests.
        ConnectivityUtil* cu = new ConnectivityUtil(le);
        Assert::assertNotNull("connectivity util",cu, __FILE__, __LINE__);

        ((LogixManager*)InstanceManager::getDefault("LogixManager"))->activateAllLogixs();
        // make sure the block paths are initialized.
        ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->initializeLayoutBlockPaths();
//        JUnitUtil::waitFor(() -> {
//            return InstanceManager::sensorManagerInstance()->provideSensor("IS_ROUTING_DONE")->getKnownState() == Sensor::ACTIVE;
//        },
//                "LayoutEditor stabilized sensor went ACTIVE");
        ReleaseUntil* r1 = new ReleaseUntil_dcst1(this);
        JUnitUtil::waitFor(r1, __FILE__, __LINE__);

        BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
        SensorManager* sm = (SensorManager*)InstanceManager::getDefault("SensorManager");
        TurnoutManager* tm = (TurnoutManager*)InstanceManager::getDefault("TurnoutManager");

//        ThreadingUtil.runOnLayout( ()-> {
             try{
                tm->provideTurnout("EastTurnout")->setState(Turnout::CLOSED);
                tm->provideTurnout("WestTurnout")->setState(Turnout::CLOSED);

                sm->provideSensor("Mainline")->setState(Sensor::ACTIVE);
                sm->provideSensor("Siding")->setState(Sensor::ACTIVE);
                sm->provideSensor("EastTurnoutOS")->setState(Sensor::INACTIVE);
                sm->provideSensor("East1")->setState(Sensor::INACTIVE);
                sm->provideSensor("East2")->setState(Sensor::INACTIVE);
                sm->provideSensor("WestTurnoutOS")->setState(Sensor::INACTIVE);
                sm->provideSensor("West1")->setState(Sensor::INACTIVE);
                sm->provideSensor("West2")->setState(Sensor::INACTIVE);
             } catch (JmriException je) {
                log->error("Expected error setting up test", je);
             }
//        });

        Block* b1 = bm->provideBlock("MainlineBlock");
        // set the block contents to a railcom address for our locomotive.
        b1->setValue(initialBlockContents);

        // get the initial block for the cab signal.
        cs->setBlock();

        // and verify getBlock returns the block we set.
        checkBlock(cs,"MainlineBlock","EastTurnoutOSBlock","IF$vsm:AAR-1946:PL-1-high-abs($0005)");
        moveBlock("Mainline","EastTurnoutOS");
        checkBlock(cs,"EastTurnoutOSBlock","East1Block","IF$vsm:AAR-1946:PL-1-high-pbs($0002)");
        moveBlock("EastTurnoutOS","East1");
        checkBlock(cs,"East1Block","East2Block","IF$vsm:AAR-1946:PL-1-high-pbs($0002)");
        moveBlock("East1","East2");
        checkBlock(cs,"East2Block","","");

        moveBlock("East2","West2");
        checkBlock(cs,"West2Block","","");
        moveBlock("West2","West1");
        checkBlock(cs,"West1Block","WestTurnoutOSBlock","IF$vsm:AAR-1946:SL-2-high-abs($0008)");
        moveBlock("West1","WestTurnoutOS");
        checkBlock(cs,"WestTurnoutOSBlock","MainlineBlock","IF$vsm:AAR-1946:PL-1-high-abs($0005)");
        moveBlock("WestTurnoutOS","Mainline");
        checkBlock(cs,"MainlineBlock","EastTurnoutOSBlock","IF$vsm:AAR-1946:PL-1-high-abs($0005)");

        //throw the turnout behind the train.
//        ThreadingUtil.runOnLayout( ()-> {
             try{
              tm->provideTurnout("WestTurnout")->setState(Turnout::THROWN);
             } catch (JmriException je) {
             }
//        });
        // and verify the state does not change.
        checkBlock(cs,"MainlineBlock","EastTurnoutOSBlock","IF$vsm:AAR-1946:PL-1-high-abs($0005)");

        // throw the turnout in front of the train
//        ThreadingUtil.runOnLayout( ()-> {
             try{
              tm->provideTurnout("EastTurnout")->setState(Turnout::THROWN);
             } catch (JmriException je) {
             }
//        });
        // and verify the state changes.
        checkBlock(cs,"MainlineBlock","","");

        cs->dispose(); // verify no exceptions

        // and close the editor window
        to->closeFrameWithConfirmations();
    }

    /*private*/ void DefaultCabSignalTest::moveBlock(QString startingBlock,QString endingBlock) {
        // use sensors to move to the next block.
//        ThreadingUtil.runOnLayout( ()-> {
             try{
                 SensorManager* sm = (SensorManager*)InstanceManager::getDefault("SensorManager");
                 sm->provideSensor(endingBlock)->setState(Sensor::ACTIVE);
                 sm->provideSensor(startingBlock)->setState(Sensor::INACTIVE);
             } catch (JmriException je) {
             }
//        });
    }

    /*protected*/ void DefaultCabSignalTest::checkBlock(CabSignal* lcs,QString currentBlock,QString nextBlock,QString mastName){
        BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
        SignalMastManager* smm = (SignalMastManager*)InstanceManager::getDefault("SignalMastManager");
        Assert::assertEquals("Block set",bm->getBlock(currentBlock),lcs->getBlock(), __FILE__, __LINE__);
        Assert::assertEquals("next Block set",bm->getBlock(nextBlock),lcs->getNextBlock(), __FILE__, __LINE__);
        Assert::assertEquals("Mast set",smm->getSignalMast(mastName),lcs->getNextMast(), __FILE__, __LINE__);
        if(mastName!="") {
//           new org.netbeans.jemmy.QueueTool().waitEmpty(100); // wait for signal to settle.
         SleeperThread::msleep(100);
           // mast expected, so check the aspect.
//           JUnitUtil::waitFor( () -> { return "Clear".equals(lcs->getNextMast().getAspect().toString());});
         ReleaseUntil* r2 = new ReleaseUntil_dcst2(lcs, this);
         JUnitUtil::waitFor(r2, __FILE__, __LINE__);
           Assert::assertEquals("Mast " + mastName + " Aspect clear","Clear",lcs->getNextMast()->getAspect(), __FILE__, __LINE__);
        }
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void DefaultCabSignalTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initMemoryManager();
        InstanceManager::setDefault("BlockManager",new BlockManager());
        JUnitUtil::initLayoutBlockManager();
        JUnitUtil::initDefaultSignalMastManager();
        JUnitUtil::initSignalMastLogicManager();
        InstanceManager::setDefault("PanelMenu",new PanelMenu());
        cs = new DefaultCabSignal(new DccLocoAddress(1234,true));
    }

    //@After
    /*public*/ void DefaultCabSignalTest::tearDown() {
        cs->dispose(); // verify no exceptions
        cs = nullptr;
        JUnitUtil::tearDown();
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultCabSignalTest::log = LoggerFactory::getLogger("DefaultCabSignalTest");
