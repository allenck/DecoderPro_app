#include "lightcontroltestaction.h"
#include "lightcontroltest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
LightControlTestAction::LightControlTestAction(QObject* parent) : AbstractAction(tr("LightControlTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void LightControlTestAction::actionPerformed()
{
 LightControlTest* test = new LightControlTest();
 try
 {
  QStringList testList = QStringList()
    << "testCtor"
    << "testCLighttor"
    << "testLightControlCopyCtor"
    << "testEquals"
    << "testSetGetNames"
    << "testInvalidControlType"
    << "testActivateNoLight"
    << "testSingleSensorFollower"
    << "testNoSensor"
    << "testNoTurnout"
    << "testTurnoutFollower"
    << "testFastClockFollowingOneControl"
    << "testFastClockFollowingOneControlStartOn"
    << "testFastClockFollowingTwoControls"
    << "testFastClockFollowingTwoControlsOverlap"
    << "testTimedSensorFollowing"
    << "testNoTimedSensor"
    << "testTwoSensorFollowingNoSensorSet"
    << "testTwoSensorFollowing"
    << "testTwoSensorFollowingInactive"
    << "testUniqueTimes"
       ;


 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LightControlTestAction::log = LoggerFactory::getLogger("LightControlTestAction");
