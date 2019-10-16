#include "opsmodedelayedprogrammerfacadetestaction.h"
#include "opsmodedelayedprogrammerfacadetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

OpsModeDelayedProgrammerFacadeTestAction::OpsModeDelayedProgrammerFacadeTestAction(QObject* parent)
 : AbstractAction(tr("OpsModeDelayedProgrammerFacade test"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void OpsModeDelayedProgrammerFacadeTestAction::actionPerformed()
{
 OpsModeDelayedProgrammerFacadeTest* test = new OpsModeDelayedProgrammerFacadeTest();
 try
 {
  QStringList testList = QStringList()
    << "testWrite4Val12Delay0"
    << "testWrite37Val102Delay1000"
    << "testWrite1024Val255Delay2000"
    << "testWrite0Val23Delay100"
    << "testCvLimit"
    ;

  JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
 JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}

Logger* OpsModeDelayedProgrammerFacadeTestAction::log = LoggerFactory::getLogger("OpsModeDelayedProgrammerFacadeTestAction");
