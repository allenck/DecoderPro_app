#include "paneprogframetestaction.h"
#include "paneprogframetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

PaneProgFrameTestAction::PaneProgFrameTestAction(QObject* parent) : AbstractAction(tr("PaneProgFrame test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

void PaneProgFrameTestAction::actionPerformed()
{
 PaneProgFrameTest* test = new PaneProgFrameTest();
 try
 {
  QStringList testList = QStringList()
    << "testPane"
    << "testFrame"
    ;

  JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
 JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}

Logger* PaneProgFrameTestAction::log = LoggerFactory::getLogger("PaneProgFrameTestAction");

