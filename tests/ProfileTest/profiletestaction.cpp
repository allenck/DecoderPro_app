#include "profiletestaction.h"
#include "profiletest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"

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
    try
    {
        QStringList testList = QStringList()
        << "testProfileWithExtension"
        << "testSave"
        << "testGetName"
        << "testSetName"
        << "testGetId"
        << "testGetPath"
        << "testToString"
        << "testHashCode"
        << "testEquals"
        << "testIsComplete"
        << "testGetUniqueId"
        << "testContainsProfile"
        << "testInProfile"
        << "testIsProfile"
        << "testCompareTo";
        JUnitUtil::runTests(pt, testList);
    }
    catch (AssertionError* ex)
    {
        JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* ProfileTestAction::log = LoggerFactory::getLogger("ProfileTestAction");
