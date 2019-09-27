#include "loconetconsisttestaction.h"
#include "loconetconsisttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"


LocoNetConsistTestAction::LocoNetConsistTestAction(QObject *parent) : AbstractAction(tr("LocoNetConsist"), parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LocoNetConsistTestAction::actionPerformed()
{
    LocoNetConsistTest* test = new LocoNetConsistTest();
    test->setUp();
    try
    {

     QStringList testList = QStringList()
     << "testCtor2"
     << "testGetConsistType"
     << "testSetConsistTypeCS"
     << "checkAddressAllowedBad"
     << "checkAddressAllowedGoodAdvanced"
     << "checkAddressAllowedBadAdvanced"
     << "checkSizeLimitCS"
     << "checkGetLocoDirectionCS";
     foreach(QString testName, testList)
     {
      log->info(tr("begin '%1'").arg(testName));
      QMetaObject::invokeMethod(test, testName.toLocal8Bit(), Qt::DirectConnection);
      log->info(tr("end '%1'").arg(testName));
     }

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    test->tearDown();
}
Logger* LocoNetConsistTestAction::log = LoggerFactory::getLogger("LocoNetConsistTestAction");
