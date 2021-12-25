#include "proxysensormanagertestaction.h"
#include "proxysensormanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
ProxySensorManagerTestAction::ProxySensorManagerTestAction(QObject* parent)
 : AbstractAction(tr("Proxy SensorManager test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

void ProxySensorManagerTestAction::actionPerformed()
{
 ProxySensorManagerTest* test = new ProxySensorManagerTest();
     try
     {
      QStringList testList = QStringList()
        << "testDispose"
        << "testPutGetJ"
        << "testSensorNameCase"
        << "testPutGetI"
        << "testPutGetK"
        << "testDefaultSystemName"
        << "testProvideFailure"
        << "testSingleObject"
        << "testMisses"
        << "testUpperLower"
        << "testRename"
        << "testTwoNames"
        << "testDefaultNotInternal"
        << "testProvideUser"
        << "testAddTracking"
        << "testRemoveTrackingI"
        << "testRemoveTrackingJ"
        << "testGetObjectCount"
        << "testRemoveTrackingJMute"
        << "testOrderVsSorted"
        << "testUnmodifiable"
        << "testInstanceManagerIntegration";

      JUnitUtil::runTests(test, testList);
     }
     catch (AssertionError* ex)
     {
         JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
     }
 }
 Logger* ProxySensorManagerTestAction::log = LoggerFactory::getLogger("ProxySensorManagerTestAction");
