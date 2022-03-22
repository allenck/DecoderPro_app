#include "recursivedescentparsertestaction.h"
#include "recursivedescentparsertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
RecursiveDescentParserTestAction::RecursiveDescentParserTestAction(QObject *parent) : AbstractAction(tr("RecursiveDescentParser"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void RecursiveDescentParserTestAction::actionPerformed()
{
 RecursiveDescentParserTest* test = new RecursiveDescentParserTest();
 try
 {
  QStringList testList = QStringList()
   << "testCtor"
   << "testParseAndCalculate"

       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* RecursiveDescentParserTestAction::log = LoggerFactory::getLogger("RecursiveDescentParserTestAction");
