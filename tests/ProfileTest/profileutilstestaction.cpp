#include "profileutilstestaction.h"
#include "profileutilstest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

ProfileUtilsTestAction::ProfileUtilsTestAction(QObject *parent) :AbstractAction(tr("ProfileUtils"),parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
void ProfileUtilsTestAction::actionPerformed()
{
    ProfileUtilsTest* put = new ProfileUtilsTest();
    try
    {
        QStringList testList = QStringList()
         << "testCopy"
         << "testCopyToActive";
        JUnitUtil::runTests(put, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* ProfileUtilsTestAction::log = LoggerFactory::getLogger("ProfileUtilsTestAction");
