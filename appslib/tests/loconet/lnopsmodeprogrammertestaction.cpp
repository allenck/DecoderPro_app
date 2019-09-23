#include "lnopsmodeprogrammertestaction.h"
#include "assert1.h"
#include "lnopsmodeprogrammertest.h"
#include "joptionpane.h"

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
  lomp->testGetCanWriteAddress();
  lomp->testSetMode();
  lomp->testGetMode();
  lomp->testGetCanReadWithTransponding();
  lomp->testSV2DataBytes();
  lomp->testSV2highBits();
//   lomp->testSOps16001Read();
   lomp->testSv1Write();
   lomp->testBoardRead0();
   lomp->testBoardRead1();
   lomp->testBoardReadTimeout();
   lomp->testBoardWrite();
   lomp->testBoardWriteTimeout();
   lomp->testSv1ARead();
   lomp->testSv1BRead();
   lomp->testSv2Write();
   lomp->testSv2Read();
   lomp->testOpsReadDecoderTransponding();
   lomp->testOpsReadLocoNetMode();

 }
 catch (AssertionError er)
 {
     JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

 }
 lomp->tearDown();}
