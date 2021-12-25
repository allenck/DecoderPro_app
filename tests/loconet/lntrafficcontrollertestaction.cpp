#include "lntrafficcontrollertestaction.h"
#include "lntrafficcontrollertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnTrafficControllerTestAction::LnTrafficControllerTestAction(QObject *parent) : AbstractAction(tr("LnTrafficController Test"), parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void LnTrafficControllerTestAction::actionPerformed()
{
    LnTrafficControllerTest* ltct = new LnTrafficControllerTest();
    try
    {
        QStringList testList = QStringList()
        << "testCtor";
//        foreach(QString test, testList)
//        {
//         log->info(tr("begin '%1'").arg(test));
//         QMetaObject::invokeMethod(ltct, test.toLocal8Bit(), Qt::DirectConnection);
//         log->info(tr("end '%1'").arg(test));
//        }
        JUnitUtil::runTests(ltct, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* LnTrafficControllerTestAction::log = LoggerFactory::getLogger("LnTrafficControllerTestAction");
