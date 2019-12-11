#include "signalmasticontest.h"
#include "signalmasticon.h"
#include "signalmast.h"
#include "signalmastmanager.h"
#include "instancemanager.h"
#include "paneleditor.h"
#include "signalheadmanager.h"

SignalMastIconTest::SignalMastIconTest()
{

}
/**
 * Test the SignalMastIcon.
 * <p>
 * Description:
 *
 * @author Bob Jacobsen Copyright 2009
 */
// /*public*/ class SignalMastIconTest extends PositionableIconTest {


    //@Test
    /*public*/ void SignalMastIconTest::testShowText() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        // this one is for Layout editor, which for now
        // is still in text form.
        JFrame* jf = new JFrame("SignalMast Icon Text Test");
        FlowLayout* jfLayout;
        jf->getContentPane()->setLayout(jfLayout = new FlowLayout());

        jfLayout->addWidget(new JLabel("Should say Approach: "));
        jfLayout->addWidget(to);

        s->setAspect("Clear");
        s->setAspect("Approach");

        jf->pack();
        jf->setVisible(true);

        // close
        JUnitUtil::dispose(jf);

    }

    //@Test
    /*public*/ void SignalMastIconTest::testShowIcon() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        JFrame* jf = new JFrame("SignalMastIcon Icon Test");
        FlowLayout* jfLayout;
        jf->getContentPane()->setLayout(jfLayout = new FlowLayout());

        SignalMastIcon* to = new SignalMastIcon(editor);
        to->setShowAutoText(false);

        jfLayout->addWidget(new JLabel("Should be yellow/red: "));
        jfLayout->addWidget(to);

        s = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))
                ->provideSignalMast("IF$shsm:basic:two-searchlight:IH1:IH2");

        s->setAspect("Clear");

        to->setSignalMast(s->getSystemName());

        s->setAspect("Clear");
        s->setAspect("Approach");

        jf->pack();
        jf->setVisible(true);

        // close
        JUnitUtil::dispose(jf);
    }


\
    // The minimal setup for log4J
    //@Before
    //@Override
    /*public*/ void SignalMastIconTest::setUp() {
        PositionableIconTest::setUp();
        //if (!GraphicsEnvironment.isHeadless()) {
            editor = new PanelEditor("Test SignalMastIcon Panel");
            p = new SignalMastIcon(editor);
            to = new SignalMastIcon(editor);
            to->setShowAutoText(true);

            // reset instance manager & create test heads
            ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(new IH1SignalHead());
//                    new DefaultSignalHead("IH1") {
//                        //@Override
//                        /*protected*/ void updateOutput() {
//                        }
//                    });
            ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(new IH2SignalHead());
//                    new DefaultSignalHead("IH2") {
//                        //@Override
//                        /*protected*/ void updateOutput() {
//                        }
//                    });
            ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(new IH3SignalHead());
//                    new DefaultSignalHead("IH3") {
//                        //@Override
//                        protected void updateOutput() {
//                        }
//                    });

            s = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->
                    provideSignalMast("IF$shsm:basic:one-searchlight:IH1");

            to->setSignalMast(new NamedBeanHandle<SignalMast*>(s->getSystemName(), s));
//        }
    }

    //@After
    //@Override
    /*public*/ void SignalMastIconTest::tearDown() {
        to = nullptr;
        PositionableIconTest::tearDown();
    }
