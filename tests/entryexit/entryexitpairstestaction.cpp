#include "entryexitpairstestaction.h"
#include "entryexitpairstest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

EntryExitPairsTestAction::EntryExitPairsTestAction(QObject* parent) : AbstractAction(tr("EntryExipPairs Test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void EntryExitPairsTestAction::actionPerformed()
{
 EntryExitPairsTest* test = new EntryExitPairsTest();
 try
 {
  QStringList testList = QStringList()
    << "testCTor"
    << "testAddNxSourcePoint"
    << "testGetSourceList"
    << "testSetSingleSegmentRoute"
    << "testDiscoverPairs"
    << "testNxPairDelete"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* EntryExitPairsTestAction::log = LoggerFactory::getLogger("EntryExitPairsTestAction");
