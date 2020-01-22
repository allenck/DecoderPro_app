#include "controllerfilterframetestaction.h"
#include "controllerfilterframetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
ControllerFilterFrameTestAction::ControllerFilterFrameTestAction(QObject* parent)
 : AbstractAction(tr("ControllerFilterFrameTest"), parent)

{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
void ControllerFilterFrameTestAction::actionPerformed()
{
 ControllerFilterFrameTest* test = new ControllerFilterFrameTest();
 try
 {
  QStringList testList = QStringList()
    // in JmriJFrameTestBase
    << "testCTor"
    << "testShowAndClose"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* ControllerFilterFrameTestAction::log = LoggerFactory::getLogger("ControllerFilterFrameTestAction");
