#include "internalturnoutmanagertestaction.h"
#include "internalturnoutmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
InternalTurnoutManagerTestAction::InternalTurnoutManagerTestAction(QObject* parent) : AbstractAction(tr("InternalTurnout Manager"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void InternalTurnoutManagerTestAction::actionPerformed()
{
   InternalTurnoutManagerTest* test = new InternalTurnoutManagerTest();
   try
   {

    QStringList testList = QStringList()
      // from AbstractProvidingTurnoutManagerTestBase
      << "testProvideEmpty"
      << "testRegisterDuplicateSystemName"

      // from AbstractTurnoutMgrTestBase
      << "testCreate"
      << "testDispose"
      << "testProvideFailure"
      << "testTurnoutPutGet"
      << "testProvideName"
      << "testProvideWithoutWithPrefix"
      << "void testProvideWithWithoutPrefix"
      << "testProvideFailWithPrefix"
      << "testDefaultSystemName"
      << "testSingleObject"
      << "testMisses"
      << "testUpperLower"
      << "testRename"
      << "testThrownText"
      << "testClosedText"
      << "testSetAndGetOutputInterval"
      << "testAutoSystemNames"
      << "testGetEntryToolTip"
      << "testGetNextValidAddress"
      << "testIncorrectGetNextValidAddress"

      // from InternalTurnoutManagerTest
      << "testAsAbstractFactory"
      << "testCaseMatters"
      << "testFollowingTurnouts"
      << "testSetAndGetOutputInterval"
      << "testMakeSystemNameWithNoPrefixNotASystemName"
      << "testMakeSystemNameWithPrefixNotASystemName"
      << "testIncorrectGetNextValidAddress"


      ;

    JUnitUtil::runTests(test, testList);
   }
   catch (AssertionError* er)
   {
       JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
   }
}
Logger* InternalTurnoutManagerTestAction::log = LoggerFactory::getLogger("InternalTurnoutManagerTestAction");
