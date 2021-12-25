#include "decoderfiletestaction.h"
#include "decoderfiletest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DecoderFileTestAction::DecoderFileTestAction(QObject* parent)
 : AbstractAction(tr("DecoderFile test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void DecoderFileTestAction::actionPerformed()
{
 DecoderFileTest* test = new DecoderFileTest();
 try
 {
  QStringList testList = QStringList()
    << "testSingleVersionNumber"
    << "testRangeVersionNumber"
    << "testCtorRange"
    << "testCtorLow"
    << "testCtorHigh"
    << "testSeveralSingleVersionNumber"
    << "testMfgName"
    << "testIncludeCheck"
    << "testIncludeCheckRippleDown"
    << "testIncludeCheckModel"
    << "testExcludeCheck"
    << "testExcludeCheckRippleDown"
    << "testExcludeCheckModel"
    << "testMinOut"
    << "testMinFn"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DecoderFileTestAction::log = LoggerFactory::getLogger("DecoderFileTestAction");
