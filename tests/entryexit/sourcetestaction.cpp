#include "sourcetestaction.h"
#include "sourcetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

SourceTestAction::SourceTestAction(QObject* parent) : AbstractAction(tr("SourceTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void SourceTestAction::actionPerformed()
{
 SourceTest* test = new SourceTest();
 try
 {
  QStringList testList = QStringList()
    << "testCTor"
    << "testDestinationPoints"
    << "testSourceMethods"

       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* SourceTestAction::log = LoggerFactory::getLogger("SourceTestAction");
