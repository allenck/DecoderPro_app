#include "lnpacketizertestaction.h"
#include "lnpacketizertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"


LnPacketizerTestAction::LnPacketizerTestAction(QObject* parent) : AbstractAction(tr("LnPacketizer Test"), parent)
{
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void LnPacketizerTestAction::actionPerformed()
{
    LnPacketizerTest* lnpct = new LnPacketizerTest();
    lnpct->setUp();
    try
    {
     QStringList testList = QStringList()
     << "testCtor"
     << "testStatusWithoutInit"
     << "testStartThreads";
     foreach(QString test, testList)
     {
      log->info(tr("begin '%1'").arg(test));
      QMetaObject::invokeMethod(lnpct, test.toLocal8Bit(), Qt::DirectConnection);
      log->info(tr("end '%1'").arg(test));
     }
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    lnpct->tearDown();
}
Logger* LnPacketizerTestAction::log = LoggerFactory::getLogger("LnPacketizerTestAction");

