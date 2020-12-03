#include "meterframetest.h"
#include "junitutil.h"
#include "defaultmeter.h"
#include "instancemanager.h"
#include "metermanager.h"
#include "meterframe.h"
#include "proxymetermanager.h"

MeterFrameTest::MeterFrameTest(QObject *parent) : JmriJFrameTestBase(parent)
{

}
/**
 *
 * @author Paul Bender       Copyright (C) 2017
 * @author Andrew Crosland   Copyright (C) 2020
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
// /*public*/ class MeterFrameTest extends util.JmriJFrameTestBase {
#if 0
    //QTest
    /*public*/ void testVoltageChange1Digit() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        runOnLayout(() -> {
            frame.initComponents();
            ((MeterManager*)InstanceManager::getDefault("MeterManager"))
                    ->getNamedBeanSet().first()
                    .setCommandedAnalogValue(2.1f);
        });
    }

    //QTest
    /*public*/ void testVoltageChange2Digit() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        runOnLayout(() -> {
            frame.initComponents();
            ((MeterManager*)InstanceManager::getDefault("MeterManager"))
                    .getNamedBeanSet().first()
                    .setCommandedAnalogValue(32.1f);
        });
    }

    //QTest
    /*public*/ void testVoltageChange3Digit() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        runOnLayout(() -> {
            frame.initComponents();
            ((MeterManager*)InstanceManager::getDefault("MeterManager"))
                    ->getNamedBeanSet().first()
                    .setCommandedAnalogValue(432.1f);
        });
    }

    //QTest
    /*public*/ void testVoltageChange4Digit() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        runOnLayout(() -> {
            frame.initComponents();
            ((MeterManager*)InstanceManager::getDefault("MeterManager"))
                    ->getNamedBeanSet().first()
                    .setCommandedAnalogValue(5432.1f);
        });
    }
#endif
    //@BeforeEach
    //@Override
    /*public*/ void MeterFrameTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();

//        Meter* voltageMeter = new /*DefaultMeter::*/DefaultVoltageMeter("IVVoltageMeter", Meter.Unit.Milli, 0.0, 1000.0, 1.0, new MeterUpdateTask(-1) {
//            @Override
//            /*public*/ void requestUpdateFromLayout() {
//                // Do nothing
//            }
//        });
//        Meter* voltageMeter = new /*DefaultMeter::*/MFT_DefaultVoltageMeter("IVVoltageMeter", Meter::Unit::Milli, 0.0, 1000.0, 1.0, new MeterUpdateTask(-1), this);

//        ((ProxyMeterManager*)InstanceManager::getDefault("MeterManager"))->Register((NamedBean*)voltageMeter);

//        if (!GraphicsEnvironment.isHeadless()) {
            frame = new MeterFrame();
//        }
    }

    //@AfterEach
    //@Override
    /*public*/ void MeterFrameTest::tearDown() {
        JmriJFrameTestBase::tearDown();
    }
#if 0
    /*private*/ void runOnLayout(RunnableWithException* r) {
//        ThreadingUtil.runOnLayout(() -> {
            try {
                r.run();
            } catch (JmriException e) {
                throw RuntimeException(e);
            }
//        });
    }

    /*private*/ interface RunnableWithException {
        /*public*/ void run() throws JmriException;
    }
#endif
