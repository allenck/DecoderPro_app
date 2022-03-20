#include "digitalexpressionstestaction.h"
#include "digitalexpressionstest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"


DigitalExpressionsTestAction::DigitalExpressionsTestAction(QObject *parent) : AbstractAction(tr("Digital Expressions"),parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}


void DigitalExpressionsTestAction::actionPerformed()
{
 DigitalExpressionsTest* test = new DigitalExpressionsTest();
 try
 {
  QStringList testList = QStringList()
    << "testLoad"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DigitalExpressionsTestAction::log = LoggerFactory::getLogger("DigitalExpressionsTestAction");
