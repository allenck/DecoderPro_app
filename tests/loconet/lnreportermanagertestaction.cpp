#include "lnreportermanagertestaction.h"
#include "lnreportermanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnReporterManagerTestAction::LnReporterManagerTestAction(QObject* parent) : AbstractAction(tr("LnReporterManagerTest"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void LnReporterManagerTestAction::actionPerformed()
{
 LnReporterManagerTest* test = new LnReporterManagerTest();
 try
 {
  QStringList testList = QStringList()
  << "testCreate"
  << "testDispose"
  << "testProvideName"
  << "testReporterProvideReporter"
  << "testProvideFailure"
  << "testReporterGetBySystemName"
  << "testReporterGetByUserName"
  << "testReporterGetByDisplayName"
  << "testReporterProvideByNumber"
  << "testDefaultSystemName"
  << "testSingleObject"
  << "testMisses"
  << "testUpperLower"
  << "testRename";


 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LnReporterManagerTestAction::log = LoggerFactory::getLogger("LnReporterManagerTestAction");
