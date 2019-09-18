#include "lntrafficcontrollertestaction.h"
#include "lntrafficcontrollertest.h"
#include "joptionpane.h"
#include "assert1.h"

LnTrafficControllerTestAction::LnTrafficControllerTestAction(QObject *parent) : AbstractAction(tr("LnTrafficController Test"), parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void LnTrafficControllerTestAction::actionPerformed()
{
    LnTrafficControllerTest* ltct = new LnTrafficControllerTest();
    ltct->setUp();
    try
    {
        ltct->testCtor();
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    ltct->tearDown();
}
