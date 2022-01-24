#include "lnpacketizertestaction.h"
#include "lnpacketizertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnPacketizerTestAction::LnPacketizerTestAction(QObject* parent) : AbstractAction(tr("LnPacketizer Test"), parent)
{
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void LnPacketizerTestAction::actionPerformed()
{
    LnPacketizerTest* lnpct = new LnPacketizerTest();
    try
    {
     QStringList testList = QStringList()
     << "testCtor"
     << "testStatusWithoutInit"
     << "testStartThreads";
//     foreach(QString test, testList)
//     {
//      log->info(tr("begin '%1'").arg(test));
//      QMetaObject::invokeMethod(lnpct, test.toLocal8Bit(), Qt::DirectConnection);
//      log->info(tr("end '%1'").arg(test));
//     }
     JUnitUtil::runTests(lnpct, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* LnPacketizerTestAction::log = LoggerFactory::getLogger("LnPacketizerTestAction");

