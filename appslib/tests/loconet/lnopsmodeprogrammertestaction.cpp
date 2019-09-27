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
 lomp->setUp();
 try
 {
  QStringList testList = QStringList()
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
  foreach(QString test, testList)
  {
   log->info(tr("begin '%1'").arg(test));
   QMetaObject::invokeMethod(lomp, test.toLocal8Bit(), Qt::DirectConnection);
   log->info(tr("end '%1'").arg(test));
  }

 }
 catch (AssertionError er)
 {
     JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

 }
 lomp->tearDown();
}

Logger* LnOpsModeProgrammerTestAction::log = LoggerFactory::getLogger("LnOpsModeProgrammerTestAction");
