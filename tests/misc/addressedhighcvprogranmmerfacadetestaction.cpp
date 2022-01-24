#include "addressedhighcvprogranmmerfacadetestaction.h"
#include "addressedhighcvprogranmmerfacadetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

AddressedHighCvProgranmmerFacadeTestAction::AddressedHighCvProgranmmerFacadeTestAction(QObject* parent)
 : AbstractAction(tr("AddressedHighCvProgranmmerFacadeTest test"), parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void AddressedHighCvProgranmmerFacadeTestAction::actionPerformed()
{
 AddressedHighCvProgranmmerFacadeTest* test = new AddressedHighCvProgranmmerFacadeTest();
 try
 {
  QStringList testList = QStringList()
    << "testWriteReadDirect"
    << "testWriteReadDirectHighCV"
    << "testWriteReadDirectHighCVRightSide"
    <<"testWriteReadIndexed"
   << "testCvLimit"

       ;

  JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError* ex)
  {
   JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
 }
 Logger* AddressedHighCvProgranmmerFacadeTestAction::log = LoggerFactory::getLogger("AddressedHighCvProgranmmerFacadeTestAction");
