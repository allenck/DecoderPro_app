#include "ds64panel.h"

DS64Panel::DS64Panel(QWidget *parent) :
  AbstractBoardProgPanel(1, parent)
{
 common(1);
}
/**
 * Panel displaying and programming a DS64 configuration.
 * <P>
 * The read and write require a sequence of operations, which we handle with a
 * state variable.
 * <P>
 * Programming of the BDL16 is done via configuration messages, so the BDL16
 * should not be put into programming mode via the built-in pushbutton while
 * this tool is in use.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Digitrax
 * Inc for separate permission.
 *
 * @author	Bob Jacobsen Copyright (C) 2002, 2004, 2005, 2007, 2010
 * @version	$Revision: 28746 $
 */
///*public*/ class DS64Panel extends jmri.jmrix.loconet.AbstractBoardProgPanel {

//    /**
//     *
//     */
//    private static final long serialVersionUID = -8039300267592456122L;

//    /*public*/ DS64Panel() {
//        this(1);
//    }

/*public*/ DS64Panel::DS64Panel(int boardNum, QWidget* parent) : AbstractBoardProgPanel(1, parent)
{
 //super(boardNum);
 common(boardNum);
}
void DS64Panel::common(int boardNum)
{
 log = new Logger("DS64Panel");
 opsw1 = new QCheckBox("OpSw 01: Static Output Type (Pulse if off)");
 opsw2 = new QCheckBox("OpSw 02: Pulse Timeout  200ms");
 opsw3 = new QCheckBox("OpSw 03: Pulse Timeout  400ms");
 opsw4 = new QCheckBox("OpSw 04: Pulse Timeout  800ms");
 opsw5 = new QCheckBox("OpSw 05: Pulse Timeout 1600ms");
 opsw6 = new QCheckBox("OpSw 06: Output Power Management - Wait for 1st command");
 opsw7 = new QCheckBox("OpSw 07: Reset Functions to Factory Default");
 opsw8 = new QCheckBox("OpSw 08: Double normal startup delay");
 opsw9 = new QCheckBox("OpSw 09: Turn off static outputs after 16sec");
 opsw10 = new QCheckBox("OpSw 10: DS64 accepts computer commands only");
 opsw11 = new QCheckBox("OpSw 11: Routes work from input lines");
 opsw12 = new QCheckBox("OpSw 12: Either input high causes toggle");
 opsw13 = new QCheckBox("OpSw 13: All eight inputs send sensor messages");
 opsw14 = new QCheckBox("OpSw 14: Switch commands from track only");
 opsw15 = new QCheckBox("OpSw 15: Outputs ignore inputs");
 opsw16 = new QCheckBox("OpSw 16: Disable routes");
 opsw17 = new QCheckBox("OpSw 17: Output 1 is crossing gate");
 opsw18 = new QCheckBox("OpSw 18: Output 2 is crossing gate");
 opsw19 = new QCheckBox("OpSw 19: Output 3 is crossing gate");
 opsw20 = new QCheckBox("OpSw 20: Output 4 is crossing gate");
 opsw21 = new QCheckBox("OpSw 21: Send turnout sensor messages (general sensor messages if off)");

 appendLine(provideAddressing("DS64"));  // add read/write buttons, address

 appendLine(opsw1);
 appendLine(opsw2);
 appendLine(opsw3);
 appendLine(opsw4);
 appendLine(opsw5);
 appendLine(opsw6);
 appendLine(opsw7);
 appendLine(opsw8);
 appendLine(opsw9);
 appendLine(opsw10);
 appendLine(opsw11);
 appendLine(opsw12);
 appendLine(opsw13);
 appendLine(opsw14);
 appendLine(opsw15);
 appendLine(opsw16);
 appendLine(opsw17);
 appendLine(opsw18);
 appendLine(opsw19);
 appendLine(opsw20);
 appendLine(opsw21);

 appendLine(provideStatusLine());
 setStatus("The DS64 should be in normal mode (Don't push the buttons on the DS64!)");
 // add status
 appendLine(provideStatusLine());

 setTypeWord(0x73);  // configure DS64 message type
}

/*public*/ QString DS64Panel::getHelpTarget() {
    return "package.jmri.jmrix.loconet.ds64.DS64Frame";
}

/*public*/ QString DS64Panel::getTitle()
{
 return LnPanel::getTitle(tr("DS64 Programmer"));
}

/**
 * Copy from the GUI to the opsw array.
 * <p>
 * Used before write operations start
 */
/*protected*/ void DS64Panel::copyToOpsw()
{
  // copy over the display
  opsw[1] = opsw1->isChecked();
  opsw[2] = opsw2->isChecked();
  opsw[3] = opsw3->isChecked();
  opsw[4] = opsw4->isChecked();
  opsw[5] = opsw5->isChecked();
  opsw[6] = opsw6->isChecked();
  opsw[7] = opsw7->isChecked();
  opsw[8] = opsw8->isChecked();
  opsw[9] = opsw9->isChecked();
  opsw[10] = opsw10->isChecked();
  opsw[11] = opsw11->isChecked();
  opsw[12] = opsw12->isChecked();
  opsw[13] = opsw13->isChecked();
  opsw[14] = opsw14->isChecked();
  opsw[15] = opsw15->isChecked();
  opsw[16] = opsw16->isChecked();
  opsw[17] = opsw17->isChecked();
  opsw[18] = opsw18->isChecked();
  opsw[19] = opsw19->isChecked();
  opsw[20] = opsw20->isChecked();
  opsw[21] = opsw21->isChecked();

}

/*protected*/ void DS64Panel::updateDisplay()
{
 opsw1->setChecked(opsw[1]);
 opsw2->setChecked(opsw[2]);
 opsw3->setChecked(opsw[3]);
 opsw4->setChecked(opsw[4]);
 opsw5->setChecked(opsw[5]);
 opsw6->setChecked(opsw[6]);
 opsw7->setChecked(opsw[7]);
 opsw8->setChecked(opsw[8]);
 opsw9->setChecked(opsw[9]);
 opsw10->setChecked(opsw[10]);
 opsw11->setChecked(opsw[11]);
 opsw12->setChecked(opsw[12]);
 opsw13->setChecked(opsw[13]);
 opsw14->setChecked(opsw[14]);
 opsw15->setChecked(opsw[15]);
 opsw16->setChecked(opsw[16]);
 opsw17->setChecked(opsw[17]);
 opsw18->setChecked(opsw[18]);
 opsw19->setChecked(opsw[19]);
 opsw20->setChecked(opsw[20]);
 opsw21->setChecked(opsw[21]);
}

/*protected*/ int DS64Panel::nextState(int state)
{
 switch (state)
 {
  case 1:
      return 2;
  case 2:
      return 3;
  case 3:
      return 4;
  case 4:
      return 5;
  case 5:
      return 6;
  case 6:
      return 8;   // 7 has to be done last, as it's reset
  case 8:
      return 9;
  case 9:
      return 10;
  case 10:
      return 11;
  case 11:
      return 12;
  case 12:
      return 13;
  case 13:
      return 14;
  case 14:
      return 15;
  case 15:
      return 16;
  case 16:
      return 17;
  case 17:
      return 18;
  case 18:
      return 19;
  case 19:
      return 20;
  case 20:
      return 21;
  case 21:
      return 7;
  case 7:
      return 0;       // done!
  default:
      log->error("unexpected state " + QString::number(state));
      return 0;
 }
}

