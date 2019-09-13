#include "profiletestaction.h"
#include "profiletest.h"
#include "assert1.h"
#include "joptionpane.h"

ProfileTestAction::ProfileTestAction(QObject *parent) : AbstractAction(tr("Profile Test"), parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

ProfileTestAction::ProfileTestAction(QString text, QObject *parent) : AbstractAction(text, parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void ProfileTestAction::actionPerformed()
{
    ProfileTest* pt = new ProfileTest();
    pt->setUpClass();
    try
    {
        pt->testProfileWithExtension();
        pt->testSave();
        pt->testGetName();
        pt->testSetName();
        pt->testGetId();
        pt->testGetPath();
        pt->testToString();
        pt->testHashCode();
        pt->testEquals();
        pt->testIsComplete();
        pt->testGetUniqueId();
        pt->testContainsProfile();
        pt->testInProfile();
        pt->testIsProfile();
        pt->testCompareTo();
    }
    catch (AssertionError ex)
    {
        JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
    pt->tearDownClass();
}
