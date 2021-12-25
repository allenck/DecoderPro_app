#include "cabsignaltablemodeltestaction.h"
#include "cabsignaltablemodeltest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

CabSignalTableModelTestAction::CabSignalTableModelTestAction(QObject *parent) : AbstractAction(tr("CabSignalTableModel test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void CabSignalTableModelTestAction::actionPerformed()
{
 CabSignalTableModelTest* test = new CabSignalTableModelTest();
 try
 {
  QStringList testList = QStringList()
    <<  "testCTor()"
    <<  "testColumns"
   ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* CabSignalTableModelTestAction::log = LoggerFactory::getLogger("CabSignalTableModelTestAction");
