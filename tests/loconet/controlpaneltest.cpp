#include "controlpaneltest.h"
#include "junitutil.h"
#include "assert1.h"
#include "jpanel.h"
#include "instancemanager.h"
#include "throttleframemanager.h"
#include "throttlespreferences.h"
#include "controlpanel.h"
#include "jslider.h"
#include "jdesktoppane.h"
#include "component.h"

ControlPanelTest::ControlPanelTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test simple functioning of ControlPanel
 *
 * @author Paul Bender Copyright (C) 2016
 */
///*public*/ class ControlPanelTest {

    /*private*/ void ControlPanelTest::setupControlPanel() {
        panel = new ControlPanel();
        Assert::assertNotNull("exists", panel, __FILE__, __LINE__);

        frame = new JFrame("ControlPanelTest");
        frame->setLayout(new QVBoxLayout());
        frame->setDefaultCloseOperation(JFrame::EXIT_ON_CLOSE);
        frame->setVisible(true);
        frame->resize(200, 400);

        JPanel* mainPanel = new JPanel();
        mainPanel->setLayout(new QVBoxLayout());
        mainPanel->setOpaque(true);
        mainPanel->layout()->addWidget(new JDesktopPane());
        mainPanel->layout()->addWidget(panel);

        panel->toFront();
        panel->setVisible(true);

        frame->layout()->addWidget(mainPanel);
    }

    /*private*/ void ControlPanelTest::checkFrameOverlap(QWidget* f) {
#if 0
//        /*synchronized(f.getTreeLock())*/ {
            int count = f->getComponentCount();
            for (int i1 =0 ; i1 < count; i1++) {
                Component* c1 = f->getComponent(i1);
                for (int i2 = i1+1; i2 < count; i2++ ) {
                    Component c2 = f.getComponent(i2);
                    if (c1 == c2) {
                        continue;
                    }
                    if (!c1->isVisible()) {
                        continue;
                    }
                    if (!c2.isVisible()) {
                        continue;
                    }
                    QRect r1 = c1.getBounds();
                    QRect r2 = c2.getBounds();
                    if (r1.intersects(r2)) {
                        System.out.printf("Components %s(%s) and %s(%s) overlap%n",
                            c1.getName(), c1.getClass().getName(),
                            c2.getName(), c2.getClass().getName());
                    }
                    Assert::assertFalse(r1.intersects(r2), __FILE__, __LINE__);
                }

                if (c1 instanceof Container) {
                    checkFrameOverlap((Container)c1);
                }
            }
//        }
#endif
    }

    //@Test
    /*public*/ void ControlPanelTest::testCtor() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        setupControlPanel();

        checkFrameOverlap(panel->getContentPane());
    }

    //@Test
    /*public*/ void ControlPanelTest::testExtendedThrottle() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->setUsingFunctionIcon(false);
        setupControlPanel();

        checkFrameOverlap(panel->getContentPane());

        panel->setSpeedController(ControlPanel::STEPDISPLAY);
        checkFrameOverlap(panel->getContentPane());

        panel->setSpeedController(ControlPanel::SLIDERDISPLAY);
        checkFrameOverlap(panel->getContentPane());

        panel->setSpeedController(ControlPanel::SLIDERDISPLAYCONTINUOUS);
        checkFrameOverlap(panel->getContentPane());
    }

    //@Test
    /*public*/ void ControlPanelTest::testIconThrottle() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        InstanceManager::throttleManagerInstance()->supportedSpeedModes();
        ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->setUsingFunctionIcon(true);
        setupControlPanel();

        checkFrameOverlap(panel->getContentPane());

        panel->setSpeedController(ControlPanel::STEPDISPLAY);
        checkFrameOverlap(panel->getContentPane());

        panel->setSpeedController(ControlPanel::SLIDERDISPLAY);
        checkFrameOverlap(panel->getContentPane());

        panel->setSpeedController(ControlPanel::SLIDERDISPLAYCONTINUOUS);
        checkFrameOverlap(panel->getContentPane());
    }

//    @ParameterizedTest
//    @EnumSource(SpeedStepMode.class)
    /*public*/ void ControlPanelTest::testSpeedStepModes(SpeedStepMode::SSMODES mode) {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->setUsingFunctionIcon(true);
        setupControlPanel();
        throttle = nullptr;
//        InstanceManager::throttleManagerInstance()->requestThrottle(3,
//            new ThrottleListener(){
//              @Override
//              /*public*/ void notifyThrottleFound(DccThrottle* t) {
//                throttle = t;
//                throttle.setSpeedStepMode(mode);
//                panel.notifyAddressThrottleFound(t);
//              }

//              @Override
//              /*public*/ void notifyFailedThrottleRequest(LocoAddress address,
//                  String reason) {
//              }
//              @Override
//              /*public*/ void notifyDecisionRequired(LocoAddress address,
//                  DecisionType question) {
//              }
//            });
        InstanceManager::throttleManagerInstance()->requestThrottle(3, new CPTThrottleListener(mode, this));
        Assert::assertTrue(throttle != nullptr, __FILE__, __LINE__);
        Assert::assertEquals(throttle->getSpeedSetting(), 0.0, 1.0e-7, __FILE__, __LINE__);
        Assert::assertEquals(throttle->getSpeedStepMode(), mode, __FILE__, __LINE__);

        // Set the speed controller mode to slider.
        panel->setSpeedController(ControlPanel::SLIDERDISPLAY);
        JSlider* speedSlider = panel->getSpeedSlider();

        // Test that the throttle speed defaults to 0, the maximum is
        // greater than zero and the minimum is zero.
        panel->setSpeedStepsMode(mode);
        Assert::assertEquals(speedSlider->getValue(), 0, __FILE__, __LINE__);
        Assert::assertTrue(speedSlider->maximum() > 0, __FILE__, __LINE__);
        Assert::assertEquals(speedSlider->minimum(), 0, __FILE__, __LINE__);
        Assert::assertEquals(throttle->getSpeedSetting(), 0.0, 1e-7, __FILE__, __LINE__);

        // Set the speed controller mode to shunting slider.
        panel->setSpeedController(ControlPanel::SLIDERDISPLAYCONTINUOUS);
        JSlider* speedSliderContinuous = panel->getSpeedSliderContinuous();

        // Test that the throttle speed defaults to 0, the maximum is
        // greater than zero and the minimum is zero.
        Assert::assertEquals(speedSliderContinuous->getValue(), 0, __FILE__, __LINE__);
        Assert::assertTrue(speedSliderContinuous->maximum() > 0, __FILE__, __LINE__);
        Assert::assertTrue(speedSliderContinuous->minimum() < 0, __FILE__, __LINE__);
        Assert::assertTrue(speedSliderContinuous->maximum() ==
            -speedSliderContinuous->minimum(), __FILE__, __LINE__);
        Assert::assertEquals(throttle->getSpeedSetting(), 0.0, 1e-7, __FILE__, __LINE__);
    }

    //@BeforeEach
    /*public*/ void ControlPanelTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initDebugThrottleManager();
//        if (!GraphicsEnvironment.isHeadless()) {
            ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->setUseExThrottle(true);
//        }
    }

    //@AfterEach
    /*public*/ void ControlPanelTest::tearDown() {
        if( frame != nullptr ) {
            JUnitUtil::dispose(frame);
            frame = nullptr;
        }

        JUnitUtil::resetWindows(false,false);
        JUnitUtil::tearDown();
    }
