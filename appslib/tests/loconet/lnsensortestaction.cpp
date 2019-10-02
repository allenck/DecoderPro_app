#include "lnsensortestaction.h"
#include "lnsensortest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnSensorTestAction::LnSensorTestAction(QObject* parent) : AbstractAction(tr("LnSensor test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnSensorTestAction::actionPerformed()
{
  LnSensorTest* test = new LnSensorTest();
  try
  {
   QStringList testList = QStringList()

   // tests in AbstractSensorTestBase
   << "testCreate"
   << "testAddListener"
   << "testRemoveListener"
   << "testDispose"
   << "testCommandInactive"
   << "testCommandActive"
   << "testInvertAfterInactive"
   << "testInvertAfterActive"
   << "testDebounceSettings"
   << "testDebounce"
   << "testGetPullResistance"
   << "testGetBeanType"
   << "testSensorStatusRequest"
   << "testSensor"

   // tests in LnSensorTest
   << "testLnSensorStatusMsg";
//      foreach(QString testName, testList)
//      {
//       log->info(tr("begin '%1'").arg(testName));
//       QMetaObject::invokeMethod(test, testName.toLocal8Bit(), Qt::DirectConnection);
//       log->info(tr("end '%1'").arg(testName));
//      }
   JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError er)
  {
      JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
}
Logger* LnSensorTestAction::log = LoggerFactory::getLogger("LnSensorTestAction");
