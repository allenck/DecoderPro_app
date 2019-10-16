#include "twoindextcsprogrammerfacadetestaction.h"
#include "twoindextcsprogrammerfacadetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

TwoIndexTcsProgrammerFacadeTestAction::TwoIndexTcsProgrammerFacadeTestAction(QObject* parent)
 : AbstractAction(tr("TwoIndexTcsProgrammerFacade test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

void TwoIndexTcsProgrammerFacadeTestAction::actionPerformed()
{
 TwoIndexTcsProgrammerFacadeTest* test = new TwoIndexTcsProgrammerFacadeTest();
 try
 {
  QStringList testList = QStringList()
    << "testWriteReadDirect"
    << "testWriteReadDoubleIndexed"
    << "testWriteReadTripleIndexed"
    << "testCvLimit"
    ;

  JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
 JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}

Logger* TwoIndexTcsProgrammerFacadeTestAction::log = LoggerFactory::getLogger("TwoIndexTcsProgrammerFacadeTestAction");
