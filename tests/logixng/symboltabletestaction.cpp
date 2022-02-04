#include "symboltabletestaction.h"
#include "symboltabletest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

SymbolTableTestAction::SymbolTableTestAction(QObject *parent) : AbstractAction(tr("SymbolTableTest"), parent)
{
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void SymbolTableTestAction::actionPerformed()
{
 SymbolTableTest* test = new SymbolTableTest();
 try
 {
  QStringList testList = QStringList()
    << "testValidateName"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* SymbolTableTestAction::log = LoggerFactory::getLogger("SymbolTableTestAction");
