#include "verifywriteprogrammerfacadetestaction.h"
#include "verifywriteprogrammerfacadetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

VerifyWriteProgrammerFacadeTestAction::VerifyWriteProgrammerFacadeTestAction(QObject* parent)
 : AbstractAction(tr("VerifyWriteProgrammerFacade test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void VerifyWriteProgrammerFacadeTestAction::actionPerformed()
{
 VerifyWriteProgrammerFacadeTest* test = new VerifyWriteProgrammerFacadeTest();
 try
 {
  QStringList testList = QStringList()
    << "testWriteReadDirect"
    << "testWriteReadVerify"
    << "testCvLimit"
    ;

  JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
 JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}

Logger* VerifyWriteProgrammerFacadeTestAction::log = LoggerFactory::getLogger("VerifyWriteProgrammerFacadeTestAction");
