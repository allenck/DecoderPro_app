#include "profilemanagertestaction.h"
#include "profilemanagertest.h"
#include "joptionpane.h"
#include "assert1.h"

ProfileManagerTestAction::ProfileManagerTestAction(QObject *parent) : AbstractAction(tr("Profile Manager Test"), parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

ProfileManagerTestAction::ProfileManagerTestAction(QString text, QObject *parent) : AbstractAction(text, parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void ProfileManagerTestAction::actionPerformed()
{
    ProfileManagerTest* pmt = new ProfileManagerTest();
    pmt->setUp();
    try
    {
     pmt->testCTor();
     pmt->testSetActiveProfile_Profile();
     pmt-> testSetActiveProfile_String();
    }
    catch (AssertionError ex)
    {
        JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
}

