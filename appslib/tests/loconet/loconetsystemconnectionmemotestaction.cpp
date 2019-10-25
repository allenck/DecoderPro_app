#include "loconetsystemconnectionmemotestaction.h"
#include "loconetsystemconnectionmemotest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
LoconetSystemConnectionMemoTestAction::LoconetSystemConnectionMemoTestAction(QObject* parent)
 : AbstractAction(tr("LoconetSystemConnectionMemoTest"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void LoconetSystemConnectionMemoTestAction::actionPerformed()
{
 LoconetSystemConnectionMemoTest* test = new LoconetSystemConnectionMemoTest();
 try
 {
  QStringList testList = QStringList()
    << "getPowerManager"
    << "getTurnoutManager"
    << "getThrottleManager"
    << "getSensorManager"
    << "getLightManager"
    << "getReporterManager"
    << "testCtor"
    << "testProvidesConsistManager"
    << "testGetAndSetPrefix"
    << "testMultipleMemosSamePrefix"

 ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LoconetSystemConnectionMemoTestAction::log = LoggerFactory::getLogger("LoconetSystemConnectionMemoTestAction");
