#include "sprogmessagetestaction.h"
#include "sprogmessagetest.h"
#include "joptionpane.h"
#include "assert1.h"

SprogMessageTestAction::SprogMessageTestAction(QObject *parent) : AbstractAction(tr("SprogMessage test"), parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void SprogMessageTestAction::actionPerformed()
{
    Sprog::SprogMessageTest* smt = new Sprog::SprogMessageTest();
    smt->setUp();
    try
    {
     smt->testReadCv();
     smt->testWriteCV();
     smt->testReadCvLarge();
     smt->testWriteCVLarge();

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    smt->tearDown();
}

