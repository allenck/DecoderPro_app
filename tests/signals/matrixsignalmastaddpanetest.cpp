#include "matrixsignalmastaddpanetest.h"
#include "assert1.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "matrixsignalmastaddpane.h"
#include "signalsystemmanager.h"
#include "turnoutsignalmast.h"
#include "junitappender.h"
#include "signalmastmanager.h"
#include "jframe.h"
#include <QVBoxLayout>
#include <QCheckBox>


MatrixSignalMastAddPaneTest::MatrixSignalMastAddPaneTest()
{

}
/**
 * @author	Bob Jacobsen Copyright 2018
 */
// /*public*/ class MatrixSignalMastAddPaneTest extends AbstractSignalMastAddPaneTestBase {

    /** {@inheritDoc} */
    //@Override
    /*protected*/ SignalMastAddPane* MatrixSignalMastAddPaneTest::getOTT() { return new MatrixSignalMastAddPane(); }

    //@Test
    //@SuppressWarnings("unused") // it1 etc. are indirectly used as NamedBeans IT1 etc.
    /*public*/ void MatrixSignalMastAddPaneTest::testSetMastOK() {
        MatrixSignalMast* s1 = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user name");
        Turnout* it1 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        Turnout* it2 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT2");
        Turnout* it3 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT3");
        Turnout* it4 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT4");
        Turnout* it5 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT5");
        Turnout* it6 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT666");
        // s1->setBitNum(6); // defaults to 6
        s1->setOutput("output1", "IT1");
        s1->setOutput("output2", "IT2");
        s1->setOutput("output3", "IT3");
        s1->setOutput("output4", "IT4");
        s1->setOutput("output5", "IT5");
        s1->setOutput("output6", "IT666");

        MatrixSignalMastAddPane* vp = new MatrixSignalMastAddPane();

        Assert::assertTrue(vp->canHandleMast(s1), __FILE__, __LINE__);

        vp->setMast(nullptr);
        vp->setMast(s1);

        vp->setAspectNames(
            new DefaultSignalAppearanceMapO1("IF$xsm:basic:one-low($0001)-3t", "", this)
//        {
//                @Override
//                /*public*/ Enumeration<String> getAspects() {
//                    return java.util.Collections.enumeration(
//                        java.util.Arrays.asList(
//                            new String[]{"Approach","Stop","Unlit"}));
//                    }
//            }
            , ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));
    }

    //@Test
    /*public*/ void MatrixSignalMastAddPaneTest::testSetMastReject() {
        TurnoutSignalMast* m1 = new TurnoutSignalMast("IF$tsm:basic:one-searchlight($1)", "user name");

        MatrixSignalMastAddPane* vp = new MatrixSignalMastAddPane();

        Assert::assertFalse(vp->canHandleMast(m1), __FILE__, __LINE__);

        vp->setMast(nullptr);

        vp->setAspectNames(m1->getAppearanceMap(), ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));
        vp->setMast(m1);
        JUnitAppender::assertErrorMessage("mast was wrong type: IF$tsm:basic:one-searchlight($1) jmri.implementation.TurnoutSignalMast", __FILE__, __LINE__);
    }

    //@Test
    //@SuppressWarnings("unused") // it1 etc. are indirectly used as NamedBeans IT1 etc.
    /*public*/ void MatrixSignalMastAddPaneTest::testEditAndDisableViaGui() {
//        Assume.assumeFalse(java.awt.GraphicsEnvironment.isHeadless());
        Assert::assertEquals(0, ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getObjectCount(), __FILE__, __LINE__);
        // create a mast
        Turnout* it1 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        Turnout* it2 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT2");
        Turnout* it3 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT3");

        MatrixSignalMast* mast = new MatrixSignalMastO1("IF$xsm:basic:one-low($0002)-3t", "user name 2", mast);
//        {
//            { setLastRef(3); } // reset references - this leads to $0003 below, just in case anybody else has created one
//        };
        mast->setBitNum(3);
        mast->setOutput("output1", "IT1");
        mast->setOutput("output2", "IT2");
        mast->setOutput("output3", "IT3");

        mast->setBitstring("Clear", QString("111")); // used for test below
        mast->setBitstring("Approach", QString("100"));
        mast->setBitstring("Stop", QString("001")); // used for test below
        mast->setBitstring("Unlit", QString("000"));

        ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->Register(mast);
        Assert::assertEquals(1, ((SignalSystemManager*)InstanceManager::getDefault("SignalMastManager"))->getObjectCount(), __FILE__, __LINE__);
        mast->setAspectDisabled("Unlit"); // we will reenable this below
        mast->setAllowUnLit(true);

        // set up a mast edit pane
        MatrixSignalMastAddPane* vp = new MatrixSignalMastAddPane();

        vp->setAspectNames(
                new DefaultSignalAppearanceMapO2("IM123", mast)
//        {
//            @Override
//            /*public*/ Enumeration<String> getAspects() { return mast.getAllKnownAspects().elements(); }
//        }
                , ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));
        vp->setMast(mast);

        JFrame* frame = new JFrame("Add/Edit Signal Mast");
        frame->getContentPane(true)->layout()->addWidget(vp);
        frame->pack();
        frame->setVisible(true);
#if 0
        JFrameOperator frameOp = new JFrameOperator("Add/Edit Signal Mast");
        JCheckBoxOperator rBox = new JCheckBoxOperator(frameOp, Bundle.getMessage("ResetPrevious"));

        // enable Reset
        jmri.util.ThreadingUtil.runOnGUI(() -> {
            rBox.push(); // this should set Reset enabled
            vp.createMast("basic", "appearance-one-searchlight.xml", "user name 2");
        });
#else
        QCheckBox* box;
        if((box =findBox(frame, tr("Reset previous Aspect"))))
        {
         box->click();
         vp->createMast("basic", "appearance-one-searchlight.xml", "user name 2");
        }
#endif
        // check list of SignalMasts
        Assert::assertEquals(1, ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getObjectCount(), __FILE__, __LINE__);
        Assert::assertNotNull(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 2"), __FILE__, __LINE__);
        // system name not checked, depends on history of how many MatrixSignalMast objects have been created

        // check correct aspect disabled
        Assert::assertFalse(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 2")->isAspectDisabled("Stop"), __FILE__, __LINE__);
        Assert::assertTrue(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 2")->isAspectDisabled("Unlit"), __FILE__, __LINE__);
        // check Reset setting in mast
        Assert::assertTrue(mast->resetPreviousStates(), __FILE__, __LINE__);

//        jmri.util.ThreadingUtil.runOnGUI(() -> {
            frame->dispose();
//        });
    }
QCheckBox* MatrixSignalMastAddPaneTest::findBox(QWidget* widget, QString text)
{
 QCheckBox* box = nullptr;
 QObjectList ol = widget->children();
 if(ol.size() == 0) return box;
 foreach(QObject* obj, ol)
 {
  if(qobject_cast<QCheckBox*>(obj))
  {
   if(((QCheckBox*)obj)->text() == text)
   {
    box = (QCheckBox*)obj;
    return box;
   }
  }
  if(qobject_cast<QWidget*>(obj))
  {
   box = findBox((QWidget*)obj, text);
   if(box)
    return box;
  }
 }
 return box;
}

    //@Before
    //@Override
    /*public*/ void MatrixSignalMastAddPaneTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::initDefaultUserMessagePreferences();
    }

    //@After
    //@Override
    /*public*/ void MatrixSignalMastAddPaneTest::tearDown() {
        JUnitUtil::tearDown();
    }
