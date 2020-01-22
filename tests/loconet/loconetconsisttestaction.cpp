#include "loconetconsisttestaction.h"
#include "loconetconsisttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LocoNetConsistTestAction::LocoNetConsistTestAction(QObject *parent) : AbstractAction(tr("LocoNetConsist"), parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LocoNetConsistTestAction::actionPerformed()
{
    LocoNetConsistTest* test = new LocoNetConsistTest();
    try
    {

     QStringList testList = QStringList()
       // AbstractConsistTestBase
       << "testCtor"
       << "checkDisposeMethod"
       << "testGetConsistType"
       << "testSetConsistTypeAdvanced"
       << "testSetConsistTypeCS"
       << "checkAddressAllowedGood"
       << "checkAddressAllowedBad"
       << "checkSizeLimitAdvanced"
       << "checkContainsAdvanced"
       << "checkGetLocoDirectionAdvanced"
       << "checkGetSetLocoRosterIDAdvanced"
       << "checkRemoveWithGetRosterIDAdvanced"
       << "checkAddRemoveWithRosterUpdateAdvanced"
       // LoconetConsistTest
     << "testCtor2"
     << "testGetConsistType"
     << "testSetConsistTypeCS"
     << "checkAddressAllowedBad"
     << "checkAddressAllowedGoodAdvanced"
     << "checkAddressAllowedBadAdvanced"
     << "checkSizeLimitCS"
     << "checkGetLocoDirectionCS";

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* LocoNetConsistTestAction::log = LoggerFactory::getLogger("LocoNetConsistTestAction");
