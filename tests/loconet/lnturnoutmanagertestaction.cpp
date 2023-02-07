#include "lnturnoutmanagertestaction.h"
#include "lnturnoutmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnTurnoutManagerTestAction::LnTurnoutManagerTestAction(QObject* parent) : AbstractAction(tr("LnTurnout Manager"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnTurnoutManagerTestAction::actionPerformed()
{
   LnTurnoutManagerTest* test = new LnTurnoutManagerTest();
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

      // from LnTurnoutManagerTest
      << "testMisses"
      << "testLocoNetMessages"
      << "testCreateFromMessage1 "
      << "testCreateFromMessage2 "
      << "testCreateFromMessage3 "
      << "testCreateFromMessage4 "
      << "testAsAbstractFactory"
      << "testOpcLongAck"
      ;

    JUnitUtil::runTests(test, testList);
   }
   catch (AssertionError* er)
   {
       JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
   }
}
Logger* LnTurnoutManagerTestAction::log = LoggerFactory::getLogger("LnTurnoutManagerTestAction");
