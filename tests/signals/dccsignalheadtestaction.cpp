#include "dccsignalheadtestaction.h"
#include "dccsignalheadtest.h""
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"


DccSignalHeadTestAction::DccSignalHeadTestAction(QObject* parent) : AbstractAction(tr("DccSignalHeadTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void DccSignalHeadTestAction::actionPerformed()
{
 DccSignalHeadTest* test = new DccSignalHeadTest();
 try
 {
  QStringList testList = QStringList()
    // AbstractSignalHeadTestBase
    << "testLit"
    << "testHeld"
    << "testLitDarkIndependent"
    << "testBaseAppearanceStop"
    << "testBaseAppearanceClearYellow"
    << "testBaseAppearanceClearGreen"
    << "testBaseAppearanceRestrictingFlashRed"
    << "testBaseAppearanceRestrictingLunar"
    << "testClearStopRestrictingOverlaps"
    << "testGetBeanType"

       // DccSignalHeadTest
     << "testCtor1"
     << "testRedAppearance"
     << "testDarkAppearance"
     << "testLunarAppearance"
     << "testYellowAppearance"
     << "testGreenAppearance"
     << "testFlashRedAppearance"
     << "testFlashLunarAppearance"
     << "testFlashYellowAppearance"
     << "testFlashGreenAppearance"
       ;

  JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError ex)
  {
   JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
 }
 Logger* DccSignalHeadTestAction::log = LoggerFactory::getLogger("DccSignalHeadTestAction");
