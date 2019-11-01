#include "proxyreportmanagertestaction.h"
#include "proxyreportermanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
ProxyReporterManagerTestAction::ProxyReporterManagerTestAction(QObject* parent) : AbstractAction(tr("ProxyReporterManager test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void ProxyReporterManagerTestAction::actionPerformed()
{
 ProxyReporterManagerTest* test = new ProxyReporterManagerTest();
     try
     {
      QStringList testList = QStringList()
        // from AbstractManagerTestBase
        << "testManagerDataListenerAddAndRemove"
        << "testPropertyChangeListenerAddAndRemove"
        << "testVetoableChangeListenerAddAndRemove"
        << "testMakeSystemName"

        // from AbstractProvidingReporterManagerTestBase
        << "testProvideEmpty()"
        << "testRegisterDuplicateSystemName()"

           // from AbstractReporterMgrTestBase
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
         << "testRename"

         //   From ProxyReporterManagerTest
         << "testReporterPutGet"
         << "testTwoNames"
         << "testDefaultNotInternal"
         << "testProvideUser"
         << "testInstanceManagerIntegration"
        ;

      JUnitUtil::runTests(test, testList);
}
catch (AssertionError ex)
{
   JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
}
}
Logger* ProxyReporterManagerTestAction::log = LoggerFactory::getLogger("ProxyReporterManagerTestAction");
