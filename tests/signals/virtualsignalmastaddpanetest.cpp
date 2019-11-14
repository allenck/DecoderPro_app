#include "virtualsignalmastaddpanetest.h"
#include "junitutil.h"
#include "assert1.h"
#include "matrixsignalmast.h"
#include "virtualsignalmastaddpane.h"
#include "junitappender.h"
#include "instancemanager.h"
#include "signalsystemmanager.h"
#include "signalmastmanager.h"
#include "jframe.h"
#include <QBoxLayout>
#include <qcheckbox.h>

VirtualSignalMastAddPaneTest::VirtualSignalMastAddPaneTest()
{

}
/**
 * @author	Bob Jacobsen Copyright 2018
 */
///*public*/ class VirtualSignalMastAddPaneTest extends AbstractSignalMastAddPaneTestBase {

    /** {@inheritDoc} */
    //@Override
    /*protected*/ SignalMastAddPane* VirtualSignalMastAddPaneTest::getOTT() { return new VirtualSignalMastAddPane(); }

    //@Test
    /*public*/ void VirtualSignalMastAddPaneTest::testSetMast() {
        VirtualSignalMast* s1 = new VirtualSignalMast("IF$vsm:basic:one-searchlight($1)", "user name");
        MatrixSignalMast* m1 = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");

        VirtualSignalMastAddPane* vp = new VirtualSignalMastAddPane();

        Assert::assertTrue(vp->canHandleMast(s1), __FILE__, __LINE__);
        Assert::assertFalse(vp->canHandleMast(m1), __FILE__, __LINE__);

        vp->setMast(nullptr);

        vp->setAspectNames(s1->getAppearanceMap(), ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));
        vp->setMast(s1);

        vp->setAspectNames(m1->getAppearanceMap(), ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));
        vp->setMast(m1);
        JUnitAppender::assertErrorMessage("mast was wrong type: IF$xsm:basic:one-low($0001)-3t jmri.implementation.MatrixSignalMast", __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void VirtualSignalMastAddPaneTest::testCreateMast() {
        VirtualSignalMastAddPane* vp = new VirtualSignalMastAddPane();
        new VirtualSignalMastO1("IF$vsm:basic:one-searchlight($1)", "no user name", 4);
//        {
//            { setLastRef(4); } // reset references - this leads to $0005 below, just in case anybody else has created one
//        };

        vp->createMast("AAR-1946", "appearance-PL-2-high.xml", "user name");

        Assert::assertNotNull(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name"), __FILE__, __LINE__);
        Assert::assertEquals("PL-2-high", ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name")->getMastType(), __FILE__, __LINE__);
        Assert::assertNotNull(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getBySystemName("IF$vsm:AAR-1946:PL-2-high($0005)"), __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void VirtualSignalMastAddPaneTest::testCreateAndDisableViaGui() {
//        Assume.assumeFalse(java.awt.GraphicsEnvironment.isHeadless());
        Assert::assertEquals(0, ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getObjectCount(), __FILE__, __LINE__);

        VirtualSignalMastAddPane* vp = new VirtualSignalMastAddPane();

        vp->setAspectNames(
            new DefaultSignalAppearanceMapO3("IM123", this)
//        {
//                @Override
//                /*public*/ Enumeration<String> getAspects() {
//                    return java.util.Collections.enumeration(
//                        java.util.Arrays.asList(
//                            new String[]{"Clear","Approach Medium","Advance Approach"}));
//                    }
//            }
                , ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));

        JFrame* frame = new JFrame("Add/Edit Signal Mast");
        frame->getContentPane(true)->layout()->addWidget(vp);
        frame->pack();
        frame->setVisible(true);
#if 0
        JFrameOperator frameOp = new JFrameOperator("Add/Edit Signal Mast");
        JCheckBoxOperator bBox = new JCheckBoxOperator(frameOp, "Approach Medium");

        // disable Approach Medium
        jmri.util.ThreadingUtil.runOnGUI(() -> {
            bBox.push();
            vp->createMast("AAR-1946", "appearance-PL-2-high.xml", "user name 1");
        });
#else
        QCheckBox* box;
        if((box =findBox(frame, tr("Approach Medium"))))
        {
         box->click();
         vp->createMast("AAR-1946", "appearance-PL-2-high.xml", "user name 1");
        }

#endif
        // check list of SignalMasts
        Assert::assertEquals(1, ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getObjectCount(), __FILE__, __LINE__);
        Assert::assertNotNull(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 1"), __FILE__, __LINE__);
        // system name not checked, depends on history of how many VirtualSignalMast objects have been created

        // check aspect disabled
        Assert::assertTrue(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 1")->isAspectDisabled("Approach Medium"), __FILE__, __LINE__);
        Assert::assertFalse(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 1")->isAspectDisabled("Clear"), __FILE__, __LINE__);

//        jmri.util.ThreadingUtil.runOnGUI(() -> {
            frame->dispose();
//        });
    }
QCheckBox* VirtualSignalMastAddPaneTest::findBox(QWidget* widget, QString text)
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

    //@Test
    /*public*/ void VirtualSignalMastAddPaneTest::testEditAndDisableViaGui() {
//        Assume.assumeFalse(java.awt.GraphicsEnvironment.isHeadless());
        Assert::assertEquals(0, ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getObjectCount(), __FILE__, __LINE__);
        VirtualSignalMast* mast = new VirtualSignalMastO1("IF$vsm:basic:one-searchlight($1)", "user name 2", 7);
//        {
//            { setLastRef(7); } // reset references - this leads to $0007 below, just in case anybody else has created one
//        };
        ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->Register(mast);
        Assert::assertEquals(1, ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getObjectCount(), __FILE__, __LINE__);
        mast->setAspectDisabled("Stop");
        mast->setAspectDisabled("Unlit"); // we will reenable this below

        VirtualSignalMastAddPane* vp = new VirtualSignalMastAddPane();

        vp->setAspectNames(
            new DefaultSignalAppearanceMapO4("IM123", mast)
//        {
//                @Override
//                /*public*/ Enumeration<String> getAspects() { return mast.getAllKnownAspects().elements(); }
//            }
                , ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));
        vp->setMast(mast);

        JFrame* frame = new JFrame("Add/Edit Signal Mast");
        frame->getContentPane(true)->layout()->addWidget(vp);
        frame->pack();
        frame->setVisible(true);
#if 0
        JFrameOperator frameOp = new JFrameOperator("Add/Edit Signal Mast");
        JCheckBoxOperator aBox = new JCheckBoxOperator(frameOp, "Approach");
        JCheckBoxOperator uBox = new JCheckBoxOperator(frameOp, "Unlit");

        // disable Approach
        jmri.util.ThreadingUtil.runOnGUI(() -> {
            aBox.push(); // this should set disabled
            uBox.push(); // this should set enabled
            vp->createMast("basic", "appearance-one-searchlight.xml", "user name 2");
        });
#else
        QCheckBox* aBox = findBox(frame, "Approach");
        if(aBox)
         aBox->click();
        QCheckBox* uBox = findBox(frame, "Unlit");
        if(uBox)
         uBox->click();
        vp->createMast("basic", "appearance-one-searchlight.xml", "user name 2");
#endif
        // check list of SignalMasts
        Assert::assertEquals(1, ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getObjectCount(), __FILE__, __LINE__);
        Assert::assertNotNull(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 2"), __FILE__, __LINE__);
        // system name not checked, depends on history of how many VirtualSignalMast objects have been created

        // check correct aspect disabled
        Assert::assertFalse(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 2")->isAspectDisabled("Clear"), __FILE__, __LINE__);
        Assert::assertTrue(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 2")->isAspectDisabled("Approach"), __FILE__, __LINE__);
        Assert::assertTrue(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 2")->isAspectDisabled("Stop"), __FILE__, __LINE__);
        Assert::assertFalse(((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getByUserName("user name 2")->isAspectDisabled("Unlit"), __FILE__, __LINE__);

//        jmri.util.ThreadingUtil.runOnGUI(() -> {
            frame->dispose();
//        });
    }

    //@Before
    //@Override
    /*public*/ void VirtualSignalMastAddPaneTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::initDefaultUserMessagePreferences();
    }

    //@After
    //@Override
    /*public*/ void VirtualSignalMastAddPaneTest::tearDown() {
        JUnitUtil::tearDown();
    }
