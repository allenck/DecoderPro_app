#include "lnreportertestaction.h"
#include "joptionpane.h"
#include "junitutil.h"
#include "lnreportertest.h"
#include "assert1.h"
#include "loggerfactory.h"

LnReporterTestAction::LnReporterTestAction(QObject* parent) : AbstractAction(tr("LnReporter test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnReporterTestAction::actionPerformed()
{
 LnReporterTest* test = new LnReporterTest();

 try
 {
  QStringList testList = QStringList()
    // in AbstractReporterTestBase:
    << "testCtor"
    << "testReport"
    << "testGetBeanType"
    << "testPropertyChange"

    // in LnReporterTest:
    << "testLnReporterCreate"
    << "testTranspond3Enter146"
    << "testTranspond257Enter146"
    << "testTranspond257Exit146"
    << "testTranspond3Exits146"
    << "testTranspond1056Enter175"
    << "testLnReporterLissy1"
    << "testLnReporterLissy2"
    << "testMessageFromManagerFindReport"
    << "testGetBeanPhysicalLocation"
    << "testLnReporterGetLocoAddress"
    << "testIsTranspondingLocationReport"
    << "testIsTranspondingFindReport"
    << "testGetLocoAddrFromTranspondingMsg"
    << "testGetNumber"
    << "testGetPhysicalLocationAndAddress"
    << "testLnReporterLissyBad"
    << "testGetDriectionString"
    << "testCollectionAfterMessage";

    JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError er)
 {
    JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }

}
Logger* LnReporterTestAction::log = LoggerFactory::getLogger("LnPowerManagerTestAction");
