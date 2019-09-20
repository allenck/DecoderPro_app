#include "profileutilstestaction.h"
#include "profileutilstest.h"
#include "joptionpane.h"
#include "assert1.h"

ProfileUtilsTestAction::ProfileUtilsTestAction(QObject *parent) :AbstractAction(tr("ProfileUtils"),parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
void ProfileUtilsTestAction::actionPerformed()
{
    ProfileUtilsTest* put = new ProfileUtilsTest();
    put->setUp();
    try
    {
     put->testCopy();
     put->testCopyToActive();
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    put->tearDown();
}
