#include "profilemanagertestaction.h"
#include "profilemanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

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
    ProfileManagerTest* test = new ProfileManagerTest();
    try
    {
     QStringList testList = QStringList()
         << "testCTor"
         << "testSetActiveProfile_Profile"
         << "testSetActiveProfile_String";
     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* ex)
    {
        JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* ProfileManagerTestAction::log = LoggerFactory::getLogger("ProfileManagerTestAction");

