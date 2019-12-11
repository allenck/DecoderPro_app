#include "lnopsmodeprogrammertestaction.h"
#include "assert1.h"
#include "lnopsmodeprogrammertest.h"
#include "joptionpane.h"
#include "loggerfactory.h"


LnOpsModeProgrammerTestAction::LnOpsModeProgrammerTestAction(QObject* parent) : AbstractAction(tr("LnOpsModeProgrammer Test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnOpsModeProgrammerTestAction::actionPerformed()
{
 LnOpsModeProgrammerTest* lomp = new LnOpsModeProgrammerTest();
 try
 {
  QStringList testList = QStringList()

    // in AbstractProgrammerModeTestBase
    << "testDefault"
    << "testGetCanRead"
    << "testSetGetMode"
    << "testGetLongAddress"
    << "testGetAddressNumber"
    << "testGetAddress"

    // in LnOpsModeProgrammerTest
    << "testGetCanWriteAddress"
    << "testSetMode"
    << "testGetMode"
    << "testGetCanReadWithTransponding"
    << "testSV2DataBytes"
    << "testSV2highBits"
    << "testSOps16001Read"
    << "testSv1Write"
    << "testBoardRead0"
    << "testBoardRead1"
    << "testBoardReadTimeout"
    << "testBoardWrite"
    << "testBoardWriteTimeout"
    << "testSv1ARead"
    << "testSv1BRead"
    << "testSv2Write"
    << "testSv2Read"
    << "testOpsReadDecoderTransponding"
    << "testOpsReadLocoNetMode";
//  foreach(QString test, testList)
//  {
//   log->info(tr("begin '%1'").arg(test));
//   QMetaObject::invokeMethod(lomp, test.toLocal8Bit(), Qt::AutoConnection);
//   log->info(tr("end '%1'").arg(test));
//  }
  JUnitUtil::runTests(lomp, testList);
 }
 catch (AssertionError er)
 {
     JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}

Logger* LnOpsModeProgrammerTestAction::log = LoggerFactory::getLogger("LnOpsModeProgrammerTestAction");
