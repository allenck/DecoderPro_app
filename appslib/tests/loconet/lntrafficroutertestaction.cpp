#include "lntrafficroutertestaction.h"
#include "lntrafficroutertest.h"
#include "joptionpane.h"
#include "assert1.h"

LnTrafficRouterTestAction::LnTrafficRouterTestAction(QObject *parent) : AbstractAction(tr("LnTrafficRouter"), parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

void LnTrafficRouterTestAction::actionPerformed()
{
    LnTrafficRouterTest* ltrt = new LnTrafficRouterTest();
    ltrt->setUp();
    try
    {
     ltrt->testReceiveAndForward();
     ltrt->testConnectAndDisconnect();
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    ltrt->tearDown();

}
