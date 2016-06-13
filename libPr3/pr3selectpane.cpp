#include "pr3selectpane.h"
#include "flowlayout.h"
#include "QPushButton"
#include "loconetsystemconnectionmemo.h"
#include <QLabel>

//Pr3SelectPane::Pr3SelectPane(QWidget *parent) :
//  LnPanel(parent)
//{
//}
/**
 * Pane for downloading software updates to PRICOM products
 *
 * @author	Bob Jacobsen Copyright (C) 2005
 * @version	$Revision: 28746 $
 */
// /*public*/ class Pr3SelectPane extends jmri.jmrix.loconet.swing.LnPanel implements LocoNetListener {

/**
 *
 */
//private static final long serialVersionUID = 8933317271320213820L;
//static ResourceBundle res = ResourceBundle.getBundle("jmri.jmrix.loconet.pr3.Pr3Bundle");

/*public*/ QString Pr3SelectPane::getHelpTarget() {
    return "package.jmri.jmrix.loconet.pr3.swing.Pr3Select";
}

/*public*/ QString Pr3SelectPane::getTitle() {
    return LnPanel::getTitle(tr("Select PR3 Mode"));
}

/*public*/ Pr3SelectPane::Pr3SelectPane(QWidget *parent) :
  LnPanel(parent)
{
 log = new Logger("Pr3SelectPane");
 status = new QLabel(tr("PR3 Mode Unknown"));

 // first build GUI
 FlowLayout* thisLayout;
 setLayout(thisLayout = new FlowLayout());

 QPushButton* b = new QPushButton(tr("Select PR3 Mode"));
// b.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent event) {
//         selectPR2mode();
//     }
// });
 connect(b, SIGNAL(clicked()), this, SLOT(selectPR2mode()));
 thisLayout->addWidget(b);

 b = new QPushButton(tr("Set Interface Mode"));
// b.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent event) {
//         selectMS100mode();
//     }
// });
 thisLayout->addWidget(b);
 thisLayout->addWidget(status);
 connect(b, SIGNAL(clicked()), this, SLOT(selectMS100mode()));
}

/*public*/ void Pr3SelectPane::initComponents(LocoNetSystemConnectionMemo* memo)
{
 LnPanel::initComponents(memo);

 // listen for LocoNet messages
 if (memo->getLnTrafficController() != NULL)
 {
  //memo->getLnTrafficController().addLocoNetListener(~0, this);
  connect(memo->getLnTrafficController(), SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 } else {
     log->error(tr("No LocoNet connection available, can't function"));
 }

 // request status
 LocoNetMessage* msg = new LocoNetMessage(2);
 msg->setOpCode(LnConstants::OPC_GPBUSY);
 memo->getLnTrafficController()->sendLocoNetMessage(msg);
}


void Pr3SelectPane::selectPR2mode()
{
  // set to PR2 mode
  status->setText(tr("Programmer Mode"));
  LocoNetMessage* msg = new LocoNetMessage(6);
  msg->setOpCode(0xD3);
  msg->setElement(1, 0x10);
  msg->setElement(2, 1);  // set PR2
  msg->setElement(3, 0);
  msg->setElement(4, 0);
  memo->getLnTrafficController()->sendLocoNetMessage(msg);
}

void Pr3SelectPane::selectMS100mode()
{
 // set to MS100 mode
 status->setText(tr("Interface Mode"));
 LocoNetMessage* msg = new LocoNetMessage(6);
 msg->setOpCode(0xD3);
 msg->setElement(1, 0x10);
 msg->setElement(2, 0);  // set MS100
 msg->setElement(3, 0);
 msg->setElement(4, 0);
 memo->getLnTrafficController()->sendLocoNetMessage(msg);
}

/*public*/ void Pr3SelectPane::message(LocoNetMessage* msg)
{
 if ((msg->getOpCode() == LnConstants::OPC_PEER_XFER)
         && (msg->getElement(1) == 0x10)
         && (msg->getElement(2) == 0x22)
         && (msg->getElement(3) == 0x22)
         && (msg->getElement(4) == 0x01))
 {  // Digitrax form, check PR2/PR3 or MS100/PR3 mode
  int mode = msg->getElement(8) & 0x0C;
  if (mode == 0x00) {
      // PR2 format
      status->setText(tr("Programmer Mode"));
  } else {
      // MS100 format
      status->setText(tr("Interface Mode"));
  }
 }
}
#if 0
/**
 * Nested class to create one of these using old-style defaults
 */
static /*public*/ class Default extends jmri.jmrix.loconet.swing.LnNamedPaneAction {

    /**
     *
     */
    private static final long serialVersionUID = -3595956373670767395L;

    /*public*/ Default() {
        super(LocoNetBundle.bundle().getString("MenuItemPr3ModeSelect"),
                new jmri.util.swing.sdi.JmriJFrameInterface(),
                Pr3SelectPane.class.getName(),
                jmri.InstanceManager.getDefault(LocoNetSystemConnectionMemo.class));
    }
}
#endif
