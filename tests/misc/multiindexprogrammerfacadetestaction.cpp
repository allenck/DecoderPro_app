#include "multiindexprogrammerfacadetestaction.h"
#include "multiindexprogrammerfacadetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
MultiIndexProgrammerFacadeTestAction::MultiIndexProgrammerFacadeTestAction(QObject* parent)
 : AbstractAction(tr("MultiIndexProgrammerFacade test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


void MultiIndexProgrammerFacadeTestAction::actionPerformed()
{
 MultiIndexProgrammerFacadeTest* test = new MultiIndexProgrammerFacadeTest();
 try
 {
  QStringList testList = QStringList()
    << "testWriteReadDirect"
    << "testWriteReadDirectSkip"
    << "testWriteReadSingleIndexed"
    << "testWriteReadSingleIndexedSkip"
    << "testWriteReadSingleIndexedCvLast"
    << "testWriteReadSingleIndexedCvLastSkip"
    << "testWriteWriteSingleIndexedCvLastSkip"
    << "testWriteWriteSingleIndexedCvFirstSkip"
    << "testWriteReadDoubleIndexed"
    << "testWriteReadDoubleIndexedAltPiSi"
    << "testWriteReadDoubleIndexedSkip"
    << "testWriteReadDoubleIndexedCvListAltPiSi"
    << "testWriteReadDoubleIndexedCvListSkip"
    << "testWriteReadDoubleIndexedCvListSkipAltPiSi"
    << "testWriteReadDoubleIndexedCvListDelayedSkip"
    << "testCvLimit"
 ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* MultiIndexProgrammerFacadeTestAction::log = LoggerFactory::getLogger("MultiIndexProgrammerFacadeTestAction");
