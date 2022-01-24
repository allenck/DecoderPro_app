#include "identifydecodertest.h"
#include "junitutil.h"
#include "assert1.h"
#include "instancemanager.h"
#include "identifydecoder.h"
#include "junitappender.h"
#include "programmingmode.h"
#include "defaultprogrammermanager.h"

IdentifyDecoderTest::IdentifyDecoderTest(QObject *parent) : QObject(parent)
{

}
/**
 * IdentifyDecoderTest.java.
 * <p>
 * Test for the jmrit.roster.IdentifyDecoder class
 *
 * @author Bob Jacobsen
 */
///*public*/ class IdentifyDecoderTest {

    /*static*/ int IdentifyDecoderTest::cvRead = -1;

    /**
     * Test standard decoder without productID.
     */
    //@Test
    /*public*/ void IdentifyDecoderTest::testIdentifyStandard() {
        // create our test object
        IdentifyDecoder* i = new IDIdentifyDecoder(p, this);
//        {
//            @Override
//            /*public*/ void done(int mfgID, int modelID, int productID) {
//            }

//            @Override
//            /*public*/ void message(String m) {
//            }

//            @Override
//            /*public*/ void error() {
//            }
//        };

        i->start();
        Assert::assertEquals("step 1 reads CV ", 8, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 1 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete
        i->programmingOpReply(0x12, 0);
        Assert::assertEquals("step 2 reads CV ", 7, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 2 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete, ending check
        i->programmingOpReply(123, 0);
        Assert::assertEquals("running after 2 ", false, i->isRunning(), __FILE__, __LINE__);
        Assert::assertEquals("found mfg ID ", 0x12, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", 123, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", -1, i->productID, __FILE__, __LINE__);

    }

    /**
     * Test Harman decoder with productID in CV112 and CV113.
     */
    //@Test
    /*public*/ void IdentifyDecoderTest::testIdentifyHarman() {
        // create our test object
        IdentifyDecoder* i = new IDIdentifyDecoder(p, this);
//            @Override
//            /*public*/ void done(int mfgID, int modelID, int productID) {
//            }

//            @Override
//            /*public*/ void message(String m) {
//            }

//            @Override
//            /*public*/ void error() {
//            }
//        };

        i->start();
        Assert::assertEquals("step 1 reads CV ", 8, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 1 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV8, start 7
        i->programmingOpReply(98, 0);
        Assert::assertEquals("step 2 reads CV ", 7, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 2 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV7, start 112
        i->programmingOpReply(123, 0);
        Assert::assertEquals("step 3 reads CV ", 112, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 3 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV7, does 113 and ends
        i->programmingOpReply(0xAB, 0);
        Assert::assertEquals("step 4 reads CV ", 113, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 4 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV113, ends
        i->programmingOpReply(0xCD, 0);
        Assert::assertEquals("running after 5 ", false, i->isRunning(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 98, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", 123, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", 0xABCD, i->productID, __FILE__, __LINE__);

    }

    /**
     * Test Tsunami2 decoder with productID in CV253 and CV256.
     */
    //@Test
    /*public*/ void IdentifyDecoderTest::testIdentifyTsu2() {
        // create our test object
        IdentifyDecoder* i = new IDIdentifyDecoder(p, this);
//            @Override
//            /*public*/ void done(int mfgID, int modelID, int productID) {
//            }

//            @Override
//            /*public*/ void message(String m) {
//            }

//            @Override
//            /*public*/ void error() {
//            }
//        };

        i->start();
        Assert::assertEquals("step 1 reads CV ", 8, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 1 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV8, start 7
        i->programmingOpReply(141, 0);
        Assert::assertEquals("step 2 reads CV ", 7, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 2 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV7, start 253
        i->programmingOpReply(71, 0);
        Assert::assertEquals("step 3 reads CV ", 253, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 3 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV253, does 256 and ends
        i->programmingOpReply(1, 0);
        Assert::assertEquals("step 4 reads CV ", 256, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 4 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV256, ends
        i->programmingOpReply(29, 0);
        Assert::assertEquals("running after 5 ", false, i->isRunning(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 141, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", 71, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", 285, i->productID, __FILE__, __LINE__);

    }

    /**
     * Test Hornby decoder with CV159 = 143, productIDlow in CV159 and
     * productIDhigh in CV153.
     */
    //@Test
    /*public*/ void IdentifyDecoderTest::testIdentifyHornby1() {
        // create our test object
        IdentifyDecoder* i = new IDIdentifyDecoder(p, this);
//            @Override
//            /*public*/ void done(int mfgID, int modelID, int productID) {
//            }

//            @Override
//            /*public*/ void message(String m) {
//            }

//            @Override
//            /*public*/ void error() {
//            }
//        };

        i->start();
        Assert::assertEquals("step 1 reads CV ", 8, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 1 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV8, start 7
        i->programmingOpReply(48, 0);
        Assert::assertEquals("step 2 reads CV ", 7, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 2 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV7, start 159
        i->programmingOpReply(4, 0);
        Assert::assertEquals("step 3 reads CV ", 159, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 3 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV159, does 158 and ends
        i->programmingOpReply(143, 0);
        Assert::assertEquals("step 4 reads CV ", 158, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 4 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on 158, ends
        i->programmingOpReply(2, 0);
        Assert::assertEquals("running after 5 ", false, i->isRunning(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 48, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", 4, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", (2 * 256) + 143, i->productID, __FILE__, __LINE__);
    }

    /**
     * Test Hornby decoder with CV159 &lt; 143, hence productID in CV159.
     */
    //@Test
    /*public*/ void IdentifyDecoderTest::testIdentifyHornby2() {
        // create our test object
        IdentifyDecoder* i = new IDIdentifyDecoder(p, this);
//            @Override
//            /*public*/ void done(int mfgID, int modelID, int productID) {
//            }

//            @Override
//            /*public*/ void message(String m) {
//            }

//            @Override
//            /*public*/ void error() {
//            }
//        };

        i->start();
        Assert::assertEquals("step 1 reads CV ", 8, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 1 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV8, start 7
        i->programmingOpReply(48, 0);
        Assert::assertEquals("step 2 reads CV ", 7, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 2 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV7, start 159
        i->programmingOpReply(77, 0);
        Assert::assertEquals("step 3 reads CV ", 159, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 3 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV159, ends
        i->programmingOpReply(142, 0);
        Assert::assertEquals("running after 4 ", false, i->isRunning(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 48, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", 77, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", 142, i->productID, __FILE__, __LINE__);
    }

    /**
     * Test Hornby decoder with CV159 &gt; 143, hence productID in CV159.
     */
    //@Test
    /*public*/ void IdentifyDecoderTest::testIdentifyHornby3() {
        // create our test object
        IdentifyDecoder* i = new IDIdentifyDecoder(p, this);
//            @Override
//            /*public*/ void done(int mfgID, int modelID, int productID) {
//            }

//            @Override
//            /*public*/ void message(String m) {
//            }

//            @Override
//            /*public*/ void error() {
//            }
//        };

        i->start();
        Assert::assertEquals("step 1 reads CV ", 8, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 1 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV8, start 7
        i->programmingOpReply(48, 0);
        Assert::assertEquals("step 2 reads CV ", 7, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 2 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV7, start 159
        i->programmingOpReply(88, 0);
        Assert::assertEquals("step 3 reads CV ", 159, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 3 ", true, i->isRunning(), __FILE__, __LINE__);

        // simulate CV read complete on CV159, ends
        i->programmingOpReply(144, 0);
        Assert::assertEquals("running after 4 ", false, i->isRunning(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 48, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", 88, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", 144, i->productID, __FILE__, __LINE__);
    }

    /**
     * Test Hornby decoder with CV159 not available, hence productID is -1.
     * Test with 5 fails on CV8 to trigger PAGEMODE and not abort.
     */
    //@Test
    /*public*/ void IdentifyDecoderTest::testIdentifyHornby4() { // CV159 not available hence productID is -1
        // create our test object
        IdentifyDecoder* i = new IDIdentifyDecoder(p, this);
//            @Override
//            /*public*/ void done(int mfgID, int modelID, int productID) {
//            }

//            @Override
//            /*public*/ void message(String m) {
//            }

//            @Override
//            /*public*/ void error() {
//            }
//        };

        Assert::assertEquals("found mfg ID ", -1, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", -1, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", -1, i->productID, __FILE__, __LINE__);
        Assert::assertEquals("Test isOptionalCv() before start", i->isOptionalCv(), false, __FILE__, __LINE__);
        Assert::assertEquals("Programming mode before start", ProgrammingMode::DIRECTMODE, p->getMode(), __FILE__, __LINE__);

        i->start();
        Assert::assertEquals("step 1 reads CV ", 8, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 1 ", true, i->isRunning(), __FILE__, __LINE__);
        Assert::assertEquals("Test isOptionalCv() after 1", i->isOptionalCv(), false, __FILE__, __LINE__);

        // simulate 5 failures on CV8 to trigger swap to PAGEMODE, start 7
        i->programmingOpReply(21, 2);
        i->programmingOpReply(31, 2);
        i->programmingOpReply(41, 2);
        i->programmingOpReply(51, 2);
        i->programmingOpReply(61, 2);
        i->programmingOpReply(48, 0);
        Assert::assertEquals("step 2 reads CV ", 7, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 2 ", true, i->isRunning(), __FILE__, __LINE__);
        Assert::assertEquals("Test isOptionalCv() after 2", i->isOptionalCv(), false, __FILE__, __LINE__);
        Assert::assertEquals("Programming mode after 2", ProgrammingMode::PAGEMODE, p->getMode(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 48, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", -1, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", -1, i->productID, __FILE__, __LINE__);

        // simulate 2 failures on CV7, start 159
        i->programmingOpReply(22, 2);
        i->programmingOpReply(32, 2);
        i->programmingOpReply(88, 0);
        Assert::assertEquals("step 3 reads CV ", 159, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 3 ", true, i->isRunning(), __FILE__, __LINE__);
        Assert::assertEquals("Test isOptionalCv() after 3", i->isOptionalCv(), true, __FILE__, __LINE__);
        Assert::assertEquals("Programming mode after 3", ProgrammingMode::PAGEMODE, p->getMode(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 48, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", 88, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", -1, i->productID, __FILE__, __LINE__);

        // simulate CV read read fail on CV159, ends
        i->programmingOpReply(145, 2);
        i->programmingOpReply(145, 2);
        i->programmingOpReply(145, 2);
        Assert::assertEquals("running after 4 ", false, i->isRunning(), __FILE__, __LINE__);
        Assert::assertEquals("Test isOptionalCv() after 4", i->isOptionalCv(), true, __FILE__, __LINE__);
        Assert::assertEquals("Programming mode after 4", ProgrammingMode::DIRECTMODE, p->getMode(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 48, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", 88, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", -1, i->productID, __FILE__, __LINE__);

        JUnitAppender::assertWarnMessage("error 2 readng CV 8, trying Paged mode", __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Restoring Direct mode", __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("CV 159 is optional. Will assume not present...", __FILE__, __LINE__);
    }

    /**
     * Test Hornby decoder with only 2 failures on CV8 but 3 on CV7.
     * Should fail as shouldn't switch to PAGEMODE.
     */
    //@Test
    /*public*/ void IdentifyDecoderTest::testIdentifyHornby5() { // CV159 not available hence productID is -1
        // create our test object
        IdentifyDecoder* i = new IDIdentifyDecoder(p, this);
//            @Override
//            /*public*/ void done(int mfgID, int modelID, int productID) {
//            }

//            @Override
//            /*public*/ void message(String m) {
//            }

//            @Override
//            /*public*/ void error() {
//            }
//        };

        Assert::assertEquals("found mfg ID ", -1, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", -1, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", -1, i->productID, __FILE__, __LINE__);
        Assert::assertEquals("Test isOptionalCv() before start", i->isOptionalCv(), false, __FILE__, __LINE__);
        Assert::assertEquals("Programming mode before start", ProgrammingMode::DIRECTMODE, p->getMode(), __FILE__, __LINE__);

        i->start();
        Assert::assertEquals("step 1 reads CV ", 8, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 1 ", true, i->isRunning(), __FILE__, __LINE__);
        Assert::assertEquals("Test isOptionalCv() after 1", i->isOptionalCv(), false, __FILE__, __LINE__);

        // simulate 2 failures on CV8, start 7
        i->programmingOpReply(21, 2);
        i->programmingOpReply(31, 2);
        i->programmingOpReply(48, 0);
        Assert::assertEquals("step 2 reads CV ", 7, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 2 ", true, i->isRunning(), __FILE__, __LINE__);
        Assert::assertEquals("Test isOptionalCv() after 2", i->isOptionalCv(), false, __FILE__, __LINE__);
        Assert::assertEquals("Programming mode after 2", ProgrammingMode::DIRECTMODE, p->getMode(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 48, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", -1, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", -1, i->productID, __FILE__, __LINE__);

        // simulate 3 failures on CV7, to create fail since not switched to PAGEMODE
        i->programmingOpReply(22, 2);
        i->programmingOpReply(32, 2);
        i->programmingOpReply(42, 2);
        Assert::assertEquals("step 2 reads CV ", 7, cvRead, __FILE__, __LINE__);
        Assert::assertEquals("running after 2 ", false, i->isRunning(), __FILE__, __LINE__);
        Assert::assertEquals("Programming mode after 3", ProgrammingMode::DIRECTMODE, p->getMode(), __FILE__, __LINE__);

        Assert::assertEquals("found mfg ID ", 48, i->mfgID, __FILE__, __LINE__);
        Assert::assertEquals("found model ID ", -1, i->modelID, __FILE__, __LINE__);
        Assert::assertEquals("found product ID ", -1, i->productID, __FILE__, __LINE__);

        JUnitAppender::assertWarnMessage("Stopping due to error: "
                            + p->decodeErrorCode(2), __FILE__, __LINE__);
    }

    /**
     * Initialize the system.
     */
    //@BeforeEach
    /*public*/ void IdentifyDecoderTest::setUp() {
        JUnitUtil::setUp();
        p = new IDProgDebugger(this);
//        {
//            @Override
//            /*public*/ void readCV(String CV, jmri->ProgListener p) throws jmri->ProgrammerException {
//                cvRead = Integer.parseInt(CV);
//            }
//        };
        p->setMode(ProgrammingMode::DIRECTMODE);
        DefaultProgrammerManager* dpm = new DefaultProgrammerManager(p, this);
        InstanceManager::store(dpm, "AddressedProgrammerManager");
        InstanceManager::store(dpm, "GlobalProgrammerManager");
    }

    /**
     * Tear down the system.
     */
    //@AfterEach
    /*public*/ void IdentifyDecoderTest::tearDown() {
        p = nullptr;
        JUnitUtil::tearDown();
    }

