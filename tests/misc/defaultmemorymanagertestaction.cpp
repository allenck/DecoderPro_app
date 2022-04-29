#include "defaultmemorymanagertestaction.h"
#include "defaultmemorymanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultMemoryManagerTestAction::DefaultMemoryManagerTestAction(QObject* parent)
 : AbstractAction(tr("DefaultMemoryManagerTest"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DefaultMemoryManagerTestAction::actionPerformed()
{
 DefaultMemoryManagerTest* test = new DefaultMemoryManagerTest();
 try
 {
  QStringList testList = QStringList()
  // from AbstractManagerTestBase
    << "testManagerDataListenerAddAndRemove"
    << "testPropertyChangeListenerAddAndRemove"
    << "testVetoableChangeListenerAddAndRemove"
    << "testMakeSystemName"

  // from AbstractProvidingMemoryManagerTestBase
    << "testProvideEmpty"
    << "testRegisterDuplicateSystemName"

  // from DefaultMemoryManagerTest
    << "testIMthrows"
    << "testBlankThrows"
    << "testCreatesiM"

    ;


 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultMemoryManagerTestAction::log = LoggerFactory::getLogger("DefaultMemoryManagerTestAction");
