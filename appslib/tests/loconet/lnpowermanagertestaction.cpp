#include "lnpowermanagertestaction.h"
#include "lnpowermanagertest.h"
#include "joptionpane.h"
#include "assert1.h"


LnPowerManagerTestAction::LnPowerManagerTestAction(QObject *parent) : AbstractAction(tr("LnPowerManagerTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnPowerManagerTestAction::actionPerformed()
{
    LnPowerManagerTest* lpmt = new LnPowerManagerTest();
    lpmt->setUp();
    try
    {
     lpmt-> testImplementsIdle();
     lpmt->testStateIdle();
     lpmt->testSetPowerIdle();
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    lpmt->tearDown();
}
