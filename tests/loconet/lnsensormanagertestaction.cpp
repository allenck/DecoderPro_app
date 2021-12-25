#include "lnsensormanagertestaction.h"
#include "lnsensormanagertest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"


LnSensorManagerTestAction::LnSensorManagerTestAction(QObject *parent) :AbstractAction(tr("LnSensorManager test"), parent)
{

}

void LnSensorManagerTestAction::actionPerformed()
{
 LnSensorManagerTest* test = new LnSensorManagerTest();
 try
 {
  QStringList testList = QStringList()
    // in AbstractManagerTestBase
    << "testManagerDataListenerAddAndRemove"
    << "testPropertyChangeListenerAddAndRemove"
    << "testVetoableChangeListenerAddAndRemove"
    <<" testMakeSystemName"

    // in AbstractSensorMrgrTestBase
    << "testCreate"
    << "testDispose"
    << "testSensorPutGet"
    << "testDelete"
    << "testProvideName"
    << "testDefaultSystemName"
    << "testProvideFailure"
    << "testSettings"
    << "testSingleObject"
    << "testMisses"
    << "testMoveUserName"
    << "testUpperLower"
    << "testRename"
    << "testPullResistanceConfigurable"

    // in LnSensorManagerTest
    << "testLnSensorCreate"
    << "testByAddress"
    << "testMisses"
    << "testLocoNetMessages"
    << "testAsAbstractFactory"
    << "testDeprecationWarningSensorNumberFormat";

    JUnitUtil::runTests(test, testList);
   }
   catch (AssertionError* er)
   {
       JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
   }
 }
 Logger* LnSensorManagerTestAction::log = LoggerFactory::getLogger("LnSensorManagerTestAction");

