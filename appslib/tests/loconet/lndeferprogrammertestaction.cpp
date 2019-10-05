#include "lndeferprogrammertestaction.h"
#include "lndeferprogranmmertest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnDeferProgrammerTestAction::LnDeferProgrammerTestAction(QObject* parent) : AbstractAction(tr("LnDeferProgrammer test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnDeferProgrammerTestAction::actionPerformed()
{
 LnDeferProgrammerTest* test = new LnDeferProgrammerTest();
 try
 {
  QStringList testList = QStringList()
    << "testCTor"
    << "testReadCVPaged"
    << "testReadCVRegister"
    << "testReadCVDirect"
    << "testReadCVOpsModeLong"
    << "testReadCVOpsModeShort"
    << "testWriteCVPaged"
    << "testWriteCVPagedString"
    << "testWriteCVRegister"
    << "testWriteCVDirect"
    << "testWriteCVDirectStringDCS240"
    ;
  JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError er)
 {
     JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}

Logger* LnDeferProgrammerTestAction::log = LoggerFactory::getLogger("LnDeferProgrammerTestAction");

