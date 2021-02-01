#include "identifydecodertestaction.h"
#include "identifydecodertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

IdentifyDecoderTestAction::IdentifyDecoderTestAction(QObject *parent)
 : AbstractAction(tr("IdentifyDecoderTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void IdentifyDecoderTestAction::actionPerformed()
{
 IdentifyDecoderTest* test = new IdentifyDecoderTest();
 try
 {
  QStringList testList = QStringList()
    << "testIdentifyStandard"
    << "testIdentifyHarman"
    << "testIdentifyTsu2"
    << "testIdentifyHornby1"
    << "testIdentifyHornby2"
    << "testIdentifyHornby3"
    << "testIdentifyHornby4"
    << "testIdentifyHornby5"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* IdentifyDecoderTestAction::log = LoggerFactory::getLogger("IdentifyDecoderTestAction");
