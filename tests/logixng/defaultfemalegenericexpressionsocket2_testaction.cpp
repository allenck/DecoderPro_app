#include "defaultfemalegenericexpressionsocket2_testaction.h"
#include "defaultfemalegenericexpressionsocket2_test.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultFemaleGenericExpressionSocket2_TestAction::DefaultFemaleGenericExpressionSocket2_TestAction(QObject *parent)
 : AbstractAction(tr("FemaleGenericExpression 2"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}


void DefaultFemaleGenericExpressionSocket2_TestAction::actionPerformed()
{
 DefaultFemaleGenericExpressionSocket2_Test* test = new DefaultFemaleGenericExpressionSocket2_Test();
 try
 {
  QStringList testList = QStringList()

  // in DefaultFemaleGenericExpressionSocket1_Test
    << "testEvaluateGeneric"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultFemaleGenericExpressionSocket2_TestAction::log = LoggerFactory::getLogger("DefaultFemaleGenericExpressionSocket2_TestAction");
