#include "lnpacketizertestaction.h"
#include "lnpacketizertest.h"
#include "joptionpane.h"
#include "assert1.h"

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
     lnpct->testCtor();
     lnpct->testStatusWithoutInit();
     lnpct->testStartThreads();
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    lnpct->tearDown();
}
