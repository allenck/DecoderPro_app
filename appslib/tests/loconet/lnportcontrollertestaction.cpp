#include "lnportcontrollertestaction.h"
#include "lnportcontrollertest.h"
#include "joptionpane.h"
#include "assert1.h"

LnPortControllerTestAction::LnPortControllerTestAction(QObject* parent) : AbstractAction(tr("LnPortController Test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
void LnPortControllerTestAction::actionPerformed()
{
    LnPortControllerTest* lnpct = new LnPortControllerTest();
    lnpct->setUp();
    try
    {
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    lnpct->tearDown();
}
