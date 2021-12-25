#include "lnpowermanagertestaction.h"
#include "lnpowermanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnPowerManagerTestAction::LnPowerManagerTestAction(QObject *parent) : AbstractAction(tr("LnPowerManagerTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnPowerManagerTestAction::actionPerformed()
{
    LnPowerManagerTest* test = new LnPowerManagerTest();
    try
    {
        QStringList testList = QStringList()
            // tests in AbstractPowerManagerTestBase
            << "testCreate"
            << "testSetPowerOn"
            << "testSetPowerOff"
            << "testSetPowerIdle"
            << "testStateOn"
            << "testStateOff"
            << "testStateIdle"
            << "testAddListener"
            << "testRemoveListener"
            << "testDispose1"
            << "testDispose2"
            << "testImplementsIdle"

            // tests in LnPowerManagerTest
            << "testImplementsIdle"
            << "testStateIdle"
            << "testSetPowerIdle";
//        foreach(QString testName, testList)
//        {
//         log->info(tr("begin '%1'").arg(testName));
//         QMetaObject::invokeMethod(test, testName.toLocal8Bit(), Qt::DirectConnection);
//         log->info(tr("end '%1'").arg(testName));
//        }
        JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* LnPowerManagerTestAction::log = LoggerFactory::getLogger("LnPowerManagerTestAction");
