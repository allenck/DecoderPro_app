#include "lncvprogpanetestaction.h"
#include "lncvprogpanetest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"

LncvProgPaneTestAction::LncvProgPaneTestAction(QObject *parent) : AbstractAction(tr("LncvProgPaneTest "), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void LncvProgPaneTestAction::actionPerformed()
{
 LncvProgPaneTest* test = new LncvProgPaneTest();
 try
 {
  QStringList testList = QStringList()
    <<  "testCTor"
    <<  "testInitComponents"
    <<  "testGetHelpTarget"
    <<  "testGetTitle"
    <<  "testDispose"
    <<  "testPanel"
    ;
  JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError er)
 {
     JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}

Logger* LncvProgPaneTestAction::log = LoggerFactory::getLogger("LncvProgPaneTestAction");
