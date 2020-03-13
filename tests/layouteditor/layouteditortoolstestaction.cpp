#include "layouteditortoolstestaction.h"
#include "layouteditortoolstest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LayoutEditorToolsTestAction::LayoutEditorToolsTestAction(QObject* parent)
 : AbstractAction(tr("LayoutEditorToolsTest"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LayoutEditorToolsTestAction::actionPerformed()
{
 LayoutEditorToolsTest* test = new LayoutEditorToolsTest();
 try
 {
  QStringList testList = QStringList()
    << "testCTor"
    << "testHitEndBumper"
    << "testSetSignalsAtTurnout"
    << "testSetSignalsAtTurnoutWithDone"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LayoutEditorToolsTestAction::log = LoggerFactory::getLogger("LayoutEditorToolsTestAction");
