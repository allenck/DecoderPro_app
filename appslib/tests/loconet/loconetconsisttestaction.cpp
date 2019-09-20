#include "loconetconsisttestaction.h"
#include "loconetconsisttest.h"
#include "joptionpane.h"
#include "assert1.h"

LocoNetConsistTestAction::LocoNetConsistTestAction(QObject *parent) : AbstractAction(tr("LocoNetConsist"), parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LocoNetConsistTestAction::actionPerformed()
{
    LocoNetConsistTest* lct = new LocoNetConsistTest();
    lct->setUp();
    try
    {
     lct->testCtor2();
     lct->testGetConsistType();
     lct->testSetConsistTypeCS();
     lct->checkAddressAllowedBad();
     lct->checkAddressAllowedGoodAdvanced();
     lct->checkAddressAllowedBadAdvanced();
     lct->checkSizeLimitCS();
     lct->checkGetLocoDirectionCS();

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    lct->tearDown();
}
