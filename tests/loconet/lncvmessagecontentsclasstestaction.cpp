#include "lncvmessagecontentsclasstestaction.h"
#include "lncvmessagecontentsclasstest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LncvMessageContentsClassTestAction::LncvMessageContentsClassTestAction(QObject* parent)
 : AbstractAction(tr("LncvMessageContentsClassTest"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void LncvMessageContentsClassTestAction::actionPerformed()
{
 LncvMessageContentsClassTest* test = new LncvMessageContentsClassTest();
 try
 {
  QStringList testList = QStringList()
    << "testCTorIllegalArgument"
    << "testIsLnMessageASpecificLncvCommand"
    << "testGetModuleNum"
    << "testGetProdId"
    << "testExtractMessageType"
 ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LncvMessageContentsClassTestAction::log = LoggerFactory::getLogger("LncvMessageContentsClassTestAction");
