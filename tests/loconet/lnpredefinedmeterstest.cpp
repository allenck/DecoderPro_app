#include "lnpredefinedmeterstest.h"
#include "junitutil.h"
#include "loconetsystemconnectionmemo.h"
#include "slotmanager.h"
#include "loconetinterfacescaffold.h"
#include "lnpredefinedmeters.h"
#include "assert1.h"
#include "instancemanager.h"
#include "connectionconfigmanager.h"
#include "lntcpdriveradapter.h"
#include "defaultmeter.h"
#include "meter.h"
#include "connectionconfig.h"
#include "LnOverTcp/lnovertcpconnectionconfig.h"
#include "proxymetermanager.h"
LnPredefinedMetersTest::LnPredefinedMetersTest(QObject *parent) : QObject(parent)
{

}
///*public*/ class LnPredefinedMetersTest {


    //@Test
    /*public*/ void LnPredefinedMetersTest::testLnMeter() {
        LnPredefinedMeters* lm = new LnPredefinedMeters(memo);
        Assert::assertNotNull("exists",lm, __FILE__, __LINE__);

        Assert::assertEquals("initial number of meters", 0,
                ((MeterManager*)InstanceManager::getDefault("MeterManager"))->getNamedBeanSet().size(), __FILE__, __LINE__);

        lm->requestUpdateFromLayout();
        // expect one messages
        Assert::assertEquals("sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
        // set CS
        Assert::assertEquals("message 1", "BB 79 41 00", lnis->outbound.at(0)->toString().toUpper(), __FILE__, __LINE__);
        QVector<int> ia ={0xE6, 0x15, 0x01, 0x79, 0x4B, 0x4D, 0x05, 0x32, 0x70, 0x00, 0x36, 0x00,
                0x33, 0x00, 0x00, 0x00, 0x1C, 0x7F, 0x68, 0x03, 0x38 };
        LocoNetMessage* msg = new LocoNetMessage(ia);
        lm->message(msg);

        Assert::assertEquals("number of meters after first query", 2,
                ((MeterManager*)InstanceManager::getDefault("MeterManager"))->getNamedBeanSet().size(), __FILE__, __LINE__);

        Assert::assertEquals("Check for correct system name and initial value for amperage bean",
                0.5f,
                getBeanValue(lm, "LVDCS240(s/n488)InputCurrent"),
                0, __FILE__, __LINE__);
        Assert::assertEquals("Check for correct system name and initial value for voltage bean",
                15.,
                getBeanValue(lm, "LVDCS240(s/n488)Voltage"),
                0, __FILE__, __LINE__);

        Assert::assertEquals("check current value of non-existant meter variable",-999.0f,
                getBeanValue(lm, "LvCommandStationCurrent"), 0, __FILE__, __LINE__);
        Assert::assertEquals("check voltage value of non-existant meter variable", -999.0f,
                getBeanValue(lm, "LvCommandStationVoltage"), 0, __FILE__, __LINE__);

        msg->setElement(4,12);
        lm->message(msg);

        Assert::assertEquals("number of meters after second response", 2,
                ((MeterManager*)InstanceManager::getDefault("MeterManager"))->getNamedBeanSet().size(), __FILE__, __LINE__);

        Assert::assertEquals("Check for correct system name and second value for amperage bean after 2nd reply",
                0.5f,
                getBeanValue(lm, "LVDCS240(s/n488)InputCurrent"),
                0, __FILE__, __LINE__);
        Assert::assertEquals("Check for correct system name and initial value for voltage bean after 2nd reply",
                2.4f,
                getBeanValue(lm, "LVDCS240(s/n488)Voltage"),
                0.001f, __FILE__, __LINE__);

        msg->setElement(6,20);
        lm->message(msg);

        Assert::assertEquals("number of meters after second response", 2,
                ((MeterManager*)InstanceManager::getDefault("MeterManager"))->getNamedBeanSet().size(), __FILE__, __LINE__);

        Assert::assertEquals("Check for correct system name and second value for amperage bean after 3rd reply",
                2.0f,
                getBeanValue(lm, "LVDCS240(s/n488)InputCurrent"),
                0, __FILE__, __LINE__);
        Assert::assertEquals("Check for correct system name and initial value for voltage bean after 3rd reply",
                2.4f,
                getBeanValue(lm, "LVDCS240(s/n488)Voltage"),
                0.001f, __FILE__, __LINE__);

        LocoNetMessage* msg2 = new LocoNetMessage(msg);
        msg2->setElement(4, 100);
        msg2->setElement(6, 31);
        msg2->setElement(16,0x1b);
        lm->message(msg2);

        Assert::assertEquals("number of meters after fourth response", 4,
                ((MeterManager*)InstanceManager::getDefault("MeterManager"))->getNamedBeanSet().size(), __FILE__, __LINE__);

        Assert::assertEquals("Check for correct system name and second value for amperage bean after 4th reply",
                2.0f,
                getBeanValue(lm, "LVDCS240(s/n488)InputCurrent"),
                0, __FILE__, __LINE__);
        Assert::assertEquals("Check for correct system name and initial value for voltage bean after 4th reply",
                2.4f,
                getBeanValue(lm, "LVDCS240(s/n488)Voltage"),
                0.001f, __FILE__, __LINE__);

        Assert::assertEquals("Check for correct 2nd system name and second value for amperage bean after 4th reply",
                3.1f,
                getBeanValue(lm, "LVDCS210(s/n488)InputCurrent"),
                0.001f, __FILE__, __LINE__);
        Assert::assertEquals("Check for correct 2nd system name and initial value for voltage bean after 4th reply",
                20.0f,
                getBeanValue(lm, "LVDCS210(s/n488)Voltage"),
                0.001f, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void LnPredefinedMetersTest::testSN() {

        LnPredefinedMeters* lm = new LnPredefinedMeters(memo);
        Assert::assertNotNull("exists",lm, __FILE__, __LINE__);
        MeterManager* mm = (MeterManager*)InstanceManager::getDefault("MeterManager");

        Assert::assertEquals("initial number of meters", 0,
                mm->getNamedBeanSet().size(), __FILE__, __LINE__);

        QVector<int> ia={0xE6, 0x15, 0x01, 0x79, 0x4B, 0x4D, 0x05, 0x32, 0x70, 0x00, 0x36, 0x00,
                0x33, 0x00, 0x00, 0x00, 0x34, 0x7F, 0x00, 0x00, 0x38 };
        LocoNetMessage* msg = new LocoNetMessage(ia);

        for (int oneBitPos = 0; oneBitPos<14; oneBitPos++) {
            int serNum = 2<<oneBitPos;
            msg->setElement(18,serNum & 0x7f);
            msg->setElement(19, serNum >>7);
            lm->message(msg);
            Assert::assertEquals("Number of beans at testSN() iteration "+QString::number(oneBitPos),
                    2*(oneBitPos+1), mm->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertNotNull("Bean Name (amps) at testSN() iteration"+QString::number(oneBitPos),
                    mm->getBySystemName("LVDCS52(s/n"+QString::number(serNum)+")InputCurrent"), __FILE__, __LINE__);
            Assert::assertNotNull("Bean Name (amps) at testSN() iteration"+QString::number(oneBitPos),
                    mm->getBySystemName("LVDCS52(s/n"+QString::number(serNum)+")Voltage"), __FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/ void LnPredefinedMetersTest::testAmps() {

        LnPredefinedMeters* lm = new LnPredefinedMeters(memo);
        Assert::assertNotNull("exists",lm, __FILE__, __LINE__);
        MeterManager* mm = (MeterManager*)InstanceManager::getDefault("MeterManager");

        Assert::assertEquals("initial number of meters", 0,
                mm->getNamedBeanSet().size(), __FILE__, __LINE__);

        QVector<int> ia={0xE6, 0x15, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x02, 0x01, 0x38 };
        LocoNetMessage* msg = new LocoNetMessage(ia);

        for (int oneBitPos = 0; oneBitPos<7; oneBitPos++) {
            int ampsVal = 1<<oneBitPos;
            msg->setElement(6, ampsVal & 0x7f);
            lm->message(msg);
            Assert::assertEquals("Number of beans at testAmps() iteration "+QString::number(oneBitPos),
                    2, mm->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertNotNull("Bean Name (amps) not null at testAmps() iteration "+QString::number(oneBitPos),
                    mm->getBySystemName("LVDCS52(s/n130)InputCurrent"), __FILE__, __LINE__);
            Assert::assertNotNull("Bean Name (volts) not null at testAmps() iteration "+QString::number(oneBitPos),
                    mm->getBySystemName("LVDCS52(s/n130)Voltage"), __FILE__, __LINE__);
            Assert::assertEquals("Bean current at testAmps() iteration "+QString::number(oneBitPos),
                    ampsVal*.1f, getBeanValue(lm, "LVDCS52(s/n130)InputCurrent"), 0.001, __FILE__, __LINE__);
            Assert::assertEquals("Bean voltage at testAmps() iteration "+QString::number(oneBitPos),
                    0.0f, getBeanValue(lm, "LVDCS52(s/n130)Voltage"), 0.001, __FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/ void LnPredefinedMetersTest::testVolts() {

        LnPredefinedMeters* lm = new LnPredefinedMeters(memo);
        Assert::assertNotNull("exists",lm, __FILE__, __LINE__);
        MeterManager* mm = (MeterManager*)InstanceManager::getDefault("MeterManager");

        Assert::assertEquals("initial number of meters", 0,
                mm->getNamedBeanSet().size(), __FILE__, __LINE__);

        QVector<int> ia={0xE6, 0x15, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x02, 0x01, 0x38 };
        LocoNetMessage* msg = new LocoNetMessage(ia);

        for (int oneBitPos = 0; oneBitPos<7; oneBitPos++) {
            int voltsVal = 1<<oneBitPos;
            msg->setElement(4, voltsVal & 0x7f);
            lm->message(msg);
            Assert::assertEquals("Number of beans at testVolts() iteration "+QString::number(oneBitPos),
                    2, mm->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertNotNull("Bean Name (amps) not null at testVolts() iteration "+QString::number(oneBitPos),
                    mm->getBySystemName("LVDCS52(s/n130)InputCurrent"), __FILE__, __LINE__);
            Assert::assertNotNull("Bean Name (volts) not null at testVolts() iteration "+QString::number(oneBitPos),
                    mm->getBySystemName("LVDCS52(s/n130)Voltage"), __FILE__, __LINE__);
            Assert::assertEquals("Bean current at testVolts() iteration "+QString::number(oneBitPos),
                    0.0f, getBeanValue(lm, "LVDCS52(s/n130)InputCurrent"), 0.001, __FILE__, __LINE__);
            Assert::assertEquals("Bean voltage at testVolts() iteration "+QString::number(oneBitPos),
                    voltsVal*.2f, getBeanValue(lm, "LVDCS52(s/n130)Voltage"), 0.001, __FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/ void LnPredefinedMetersTest::testSlotNum() {

        LnPredefinedMeters* lm = new LnPredefinedMeters(memo);
        MeterManager* mm = (MeterManager*)InstanceManager::getDefault("MeterManager");
        Assert::assertEquals("TestSlotNum initial number of meters", 0,
                mm->getNamedBeanSet().size(), __FILE__, __LINE__);

        QVector<int> ia={0xE6, 0x15, 0x01, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x34, 0x00, 0x02, 0x01, 0x38 };
        LocoNetMessage* msg = new LocoNetMessage(ia);
        int numBeans = 0;
        for (int slotNum = 0; slotNum < 512; slotNum++) {
            msg->setElement(2, slotNum >> 7);
            msg->setElement(3, slotNum & 0x7f);
            lm->message(msg);
            if (slotNum  == 249) {
                numBeans+=2;
            }
            Assert::assertEquals("Number of beans at testSlot() iteration "+QString::number(slotNum),
                    numBeans, mm->getNamedBeanSet().size(), __FILE__, __LINE__);
        }
    }

    /*public*/ double LnPredefinedMetersTest::getBeanValue(LnPredefinedMeters* lm, QString meterName) {
        Meter* meter = (DefaultMeter*)((MeterManager*)InstanceManager::getDefault("MeterManager"))->getBySystemName(meterName);
        if (meter == nullptr) {
            return -999.0f;
        }
        return ((DefaultMeter*)meter)->getKnownAnalogValue();
    }

    //@BeforeEach
    /*public*/ void LnPredefinedMetersTest::setUp() {
        JUnitUtil::setUp();

        // This test requires a registred connection config since ProxyMeterManager
        // auto creates system meter managers using the connection configs.
        InstanceManager::setDefault("ConnectionConfigManager", new ConnectionConfigManager());
        NetworkPortAdapter* pa = new LnTcpDriverAdapter();
        pa->setSystemPrefix("L");
        ConnectionConfig* cc = new LnOverTcpConnectionConfig(pa);
        ((ConnectionConfigManager*)InstanceManager::getDefault("ConnectionConfigManager"))->add(cc);

        lnis = new LocoNetInterfaceScaffold();
        slotmanager = new SlotManager(lnis);
        memo = new LocoNetSystemConnectionMemo(lnis,slotmanager);
    }

    //@AfterEach
    /*public*/ void LnPredefinedMetersTest::tearDown() {
        memo->dispose();
        lnis->dispose();
        JUnitUtil::tearDown();
    }
