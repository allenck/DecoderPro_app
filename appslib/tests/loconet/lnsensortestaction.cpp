#include "lnsensortestaction.h"
#include "lnsensortest.h"
#include "assert1.h"
#include "joptionpane.h"

LnSensorTestAction::LnSensorTestAction(QObject* parent) : AbstractAction(tr("LnSensor test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnSensorTestAction::actionPerformed()
{
  LnSensorTest* test = new LnSensorTest();
  test->setUp();
  try
  {
   // tests in AbstractSensorTestBase
   test->testCreate();
   test->testAddListener();
   test->testRemoveListener();
   test->testDispose();
   test->testCommandInactive();
   test->testCommandActive();
   test->testInvertAfterInactive() ;
   test->testInvertAfterActive();
   test->testDebounceSettings() ;
   test->testDebounce();
   test->testGetPullResistance();
   test->testGetBeanType();
   test->testSensorStatusRequest();
   test->testSensor();

   // tests in LnSensorTest
   test->testLnSensorStatusMsg();
  }
  catch (AssertionError er)
  {
      JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

  }
  test->tearDown();
}
