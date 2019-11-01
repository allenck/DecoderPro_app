#include "proxylightmanagertestaction.h"
#include "proxylightmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

ProxyLightManagerTestAction::ProxyLightManagerTestAction(QObject *parent) :AbstractAction(tr("ProxyLightManager test"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void ProxyLightManagerTestAction::actionPerformed()
{
 ProxyLightManagerTest* test = new ProxyLightManagerTest();
     try
     {
      QStringList testList = QStringList()
        << "testDispose"
        << "testLightPutGet"
        << "testDefaultSystemName"
        << "testProvideFailure"
        << "testSingleObject"
        << "testMisses"
        << "testUpperLower"
        << "testRename"
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
Logger* ProxyLightManagerTestAction::log = LoggerFactory::getLogger("ProxyLightManagerTestAction");
