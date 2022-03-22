#include "tokenizertestaction.h"
#include "tokenizertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

TokenizerTestAction::TokenizerTestAction(QObject *parent) : AbstractAction(tr("Tokenizer"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void TokenizerTestAction::actionPerformed()
{
 TokenizerTest* test = new TokenizerTest();
 try
 {
  QStringList testList = QStringList()
    << "testCtor"
    << "testGetTokens"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* TokenizerTestAction::log = LoggerFactory::getLogger("TokenizerTestAction");

