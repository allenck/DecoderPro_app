#include "proxyturnoutmanagertestaction.h"
#include "proxyturnoutmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"


ProxyTurnoutManagerTestAction::ProxyTurnoutManagerTestAction(QObject* parent)
 : AbstractAction(tr("Proxy Turnout Manager test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


void ProxyTurnoutManagerTestAction::actionPerformed()
{
 ProxyTurnoutManagerTest* test = new ProxyTurnoutManagerTest();
     try
     {
      QStringList testList = QStringList()
        << "testDispose"
        << "testPutGet"
        << "testDefaultSystemName"
        << "testProvideFailure"
        << "testSingleObject"
        << "testMisses"
        << "testUpperLower"
        << "testRename"
        << "testTwoNames"
        << "testDefaultNotInternal"
        << "testProvideUser"
        << "testInstanceManagerIntegration";

      JUnitUtil::runTests(test, testList);
     }
     catch (AssertionError ex)
     {
         JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
     }
 }
 Logger* ProxyTurnoutManagerTestAction::log = LoggerFactory::getLogger("ProxyTurnoutManagerTestAction");
