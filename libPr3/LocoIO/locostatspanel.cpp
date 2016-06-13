#include "locostatspanel.h"
#include "stringutil.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "loconetsystemconnectionmemo.h"
#include <jtextfield.h>
#include "instancemanager.h"
#include "jmrijframeinterface.h"

LocoStatsPanel::LocoStatsPanel(QWidget *parent) :
  LnPanel(parent)
{
 log = new Logger("LocoStatsPanel");
 r1 = new JTextField(5);
 r2 = new JTextField(5);
 r3 = new JTextField(5);
 r4 = new JTextField(5);
 r5 = new JTextField(5);
 r6 = new JTextField(5);
 r7 = new JTextField(5);
 r8 = new JTextField(5);

 serial = new JTextField(6);
 status = new JTextField(5);
 current = new JTextField(4);
 hardware = new JTextField(2);
 software = new JTextField(3);

 goodMsgCnt = new JTextField(5);
 badMsgCnt = new JTextField(5);
 ms100status = new JTextField(6);

 version = new JTextField(8);
 breaks = new JTextField(6);
 errors = new JTextField(6);

 updatePending = false;
 updateButton = new QPushButton("Update");

}
/**
 * Panel displaying LocoNet interface status information.
 * <P>
 * The LocoBuffer family from RR-CirKits and the PRn family from Digitrax use
 * different formats for the status message. This class detects this from the
 * reply contents, and displays different panes depending on which message was
 * received. If the format is not recognised, a raw display format is used.
 * <p>
 * Moved from loconet.locobuffer.LocoBufferStatsFrame
 * <p>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Digitrax
 * Inc for separate permission.
 *
 * @author	Alex Shepherd Copyright (C) 2003
 * @author	Bob Jacobsen Copyright (C) 2008, 2010
 * @version	$Revision: 28746 $
 * @since 2.1.5
 */
// /*public*/ class LocoStatsPanel extends LnPanel implements LocoNetListener {


/*public*/ QString LocoStatsPanel::getHelpTarget() {
    return "package.jmri.jmrix.loconet.locostats.LocoStatsFrame";
}

/*public*/ QString LocoStatsPanel::getTitle() {
    return LnPanel::getTitle(tr("Monitor LocoNet Stats"));
}

///*public*/ LocoStatsPanel() {
//    super();
//}

//static ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrix.loconet.locostats.LocoStatsBundle");

/*public*/ void LocoStatsPanel::initComponents()
{
 QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

    // add GUI items
    rawPanel = new QWidget();
    QHBoxLayout* rawPanelLayout;
    rawPanel->setLayout(rawPanelLayout = new QHBoxLayout); //(rawPanel, BoxLayout.X_AXIS));
    rawPanelLayout->addWidget(new QLabel(tr("Raw Data")));
    rawPanelLayout->addWidget(r1);
    rawPanelLayout->addWidget(r2);
    rawPanelLayout->addWidget(r3);
    rawPanelLayout->addWidget(r4);
    rawPanelLayout->addWidget(r5);
    rawPanelLayout->addWidget(r6);
    rawPanelLayout->addWidget(r7);
    rawPanelLayout->addWidget(r8);

    lb2Panel = new QWidget();
    QHBoxLayout* lb2PanelLayout;
    lb2Panel->setLayout(lb2PanelLayout = new QHBoxLayout); //(lb2Panel, BoxLayout.X_AXIS));
    lb2PanelLayout->addWidget(new QLabel(tr("Version")));
    lb2PanelLayout->addWidget(version);
    lb2PanelLayout->addWidget(new QLabel(" Breaks:"));
//    breaks.setPreferredSize(version.getPreferredSize());
    lb2PanelLayout->addWidget(breaks);
    lb2PanelLayout->addWidget(new QLabel(" Errors:"));
//    errors.setPreferredSize(version.getPreferredSize());
    lb2PanelLayout->addWidget(errors);

    pr2Panel = new QWidget();
    QHBoxLayout* pr2PanelLayout;
    pr2Panel->setLayout(pr2PanelLayout = new QHBoxLayout);//(pr2Panel, BoxLayout.X_AXIS));
    pr2PanelLayout->addWidget(new QLabel(tr("LabelSerialNumber")));
    pr2PanelLayout->addWidget(serial);
    pr2PanelLayout->addWidget(new QLabel(" PR2 Status:"));
    pr2PanelLayout->addWidget(status);
    pr2PanelLayout->addWidget(new QLabel(" Current:"));
    pr2PanelLayout->addWidget(current);
    pr2PanelLayout->addWidget(new QLabel(" Hardware Version:"));
    pr2PanelLayout->addWidget(hardware);
    pr2PanelLayout->addWidget(new QLabel(" Software Version:"));
    pr2PanelLayout->addWidget(software);

    ms100Panel = new QWidget();
    QHBoxLayout* ms100PanelLayout;
    ms100Panel->setLayout(ms100PanelLayout = new QHBoxLayout);//(ms100Panel //, BoxLayout.X_AXIS));
    ms100PanelLayout->addWidget(new QLabel(tr("LabelGoodCnt")));
    ms100PanelLayout->addWidget(goodMsgCnt);
    ms100PanelLayout->addWidget(new QLabel(tr("LabelBadCnt")));
    ms100PanelLayout->addWidget(badMsgCnt);
    ms100PanelLayout->addWidget(new QLabel(tr("LabelMS100Status")));
    ms100PanelLayout->addWidget(ms100status);

    thisLayout->addWidget(rawPanel);
    thisLayout->addWidget(lb2Panel);
    thisLayout->addWidget(pr2Panel);
    thisLayout->addWidget(ms100Panel);

    QWidget* panel = new QWidget();
    QHBoxLayout* panelLayout;
    panel->setLayout(panelLayout = new QHBoxLayout); //(panel, BoxLayout.X_AXIS));
    thisLayout->addWidget(updateButton);
    thisLayout->addWidget(panel);

    // install "update" button handler
//    updateButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            requestUpdate();
//        }
//    }
//    );
    connect(updateButton, SIGNAL(clicked()), this, SLOT(requestUpdate()));
    // and prep for display
    lb2Panel->setVisible(false);
    rawPanel->setVisible(true);
    pr2Panel->setVisible(false);
    ms100Panel->setVisible(false);
    revalidate();

    // will connect when memo is available
}

/*public*/ void LocoStatsPanel::initComponents(LocoNetSystemConnectionMemo* memo)
{
 LnPanel::initComponents(memo);

 // listen for LocoNet messages
 if (memo->getLnTrafficController() != NULL)
 {
  //memo->getLnTrafficController()->addLocoNetListener(~0, this);
  LnTrafficController* tc = memo->getLnTrafficController();
  connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 } else {
  report("No LocoNet connection available, can't function");
 }

 // request data
 requestUpdate();
}

void LocoStatsPanel::report(QString msg) {
    log->error(msg);
}

/*public*/ void LocoStatsPanel::message(LocoNetMessage* msg)
{
 if (updatePending
            && (msg->getOpCode() == LnConstants::OPC_PEER_XFER)
            && (msg->getElement(1) == 0x10)
            && (msg->getElement(2) == 0x50)
            && (msg->getElement(3) == 0x50)
            && (msg->getElement(4) == 0x01)
            && ((msg->getElement(5) & 0xF0) == 0x0)
            && ((msg->getElement(10) & 0xF0) == 0x0))
 {
  // LocoBuffer II form
  QVector<int> data = msg->getPeerXfrData();

  version->setText(StringUtil::twoHexFromInt(data[0]) + StringUtil::twoHexFromInt(data[4]));
  breaks->setText(QString::number((data[5] << 16) + (data[6] << 8) + data[7]));
  errors->setText(QString::number((data[1] << 16) + (data[2] << 8) + data[3]));

  lb2Panel->setVisible(true);
  rawPanel->setVisible(false);
  pr2Panel->setVisible(false);
  ms100Panel->setVisible(false);
  revalidate();

  updatePending = false;

 }
 else if (updatePending
            && (msg->getOpCode() == LnConstants::OPC_PEER_XFER)
            && (msg->getElement(1) == 0x10)
            && (msg->getElement(2) == 0x22)
            && (msg->getElement(3) == 0x22)
            && (msg->getElement(4) == 0x01))
 {  // Digitrax form, check PR2/PR3 or MS100/PR3 mode

  if ((msg->getElement(8) & 0x20) == 0)
  {
   // PR2 format
   QVector<int> data = msg->getPeerXfrData();
   serial->setText(QString::number(data[1] * 256 + data[0]));
   status->setText(StringUtil::twoHexFromInt(data[2]));
   current->setText(QString::number(data[3]));
   hardware->setText(QString::number(data[4]));
   software->setText(QString::number(data[5]));

   pr2Panel->setVisible(true);
  }
  else
  {
   // MS100 format
   QVector<int> data = msg->getPeerXfrData();
   goodMsgCnt->setText(QString::number(data[1] * 256 + data[0]));
   badMsgCnt->setText(QString::number(data[5] * 256 + data[4]));
   ms100status->setText(StringUtil::twoHexFromInt(data[2]));

   ms100Panel->setVisible(true);
  }
  lb2Panel->setVisible(false);
  rawPanel->setVisible(false);

  revalidate();
  updatePending = false;

 }
 else if (updatePending
            && (msg->getOpCode() == LnConstants::OPC_PEER_XFER))
 {
  try
  {
   QVector<int> data = msg->getPeerXfrData();
   r1->setText(StringUtil::twoHexFromInt(data[0]));
   r2->setText(StringUtil::twoHexFromInt(data[1]));
   r3->setText(StringUtil::twoHexFromInt(data[2]));
   r4->setText(StringUtil::twoHexFromInt(data[3]));
   r5->setText(StringUtil::twoHexFromInt(data[4]));
   r6->setText(StringUtil::twoHexFromInt(data[5]));
   r7->setText(StringUtil::twoHexFromInt(data[6]));
   r8->setText(StringUtil::twoHexFromInt(data[7]));

   lb2Panel->setVisible(false);
   rawPanel->setVisible(true);
   pr2Panel->setVisible(false);
   ms100Panel->setVisible(false);
   revalidate();

   updatePending = false;
  }
  catch (Exception e)
  {
   log->error("Error parsing update: " + msg->toString());
  }
 }
 else if (!updatePending && (msg->getOpCode() == LnConstants::OPC_GPBUSY))
 {
  updatePending = true;
 }
}

/*public*/ void LocoStatsPanel::requestUpdate()
{
 LocoNetMessage* msg = new LocoNetMessage(2);
 msg->setOpCode(LnConstants::OPC_GPBUSY);
 updatePending = true;
 memo->getLnTrafficController()->sendLocoNetMessage(msg);
}

/*public*/ void LocoStatsPanel::dispose() {
    // disconnect from the LnTrafficController
//    memo->getLnTrafficController()->removeLocoNetListener(~0, this);
 disconnect(memo->getLnTrafficController(), SIGNAL(messageProcessed(LocoNetMessage*)));

    // take apart the JFrame
//    LnPanel::dispose();
}


#if 0
/**
 * Nested class to create one of these using old-style defaults
 */
//static /*public*/ class Default extends jmri.jmrix.loconet.swing.LnNamedPaneAction {

//    /**
//     *
//     */
//    private static final long serialVersionUID = -5534308120479708337L;

    /*public*/ Default::Default() {
        LnNamedPaneAction(tr("LocoStats"),
                new JmriJFrameInterface(),
              "LocoStatsPanel",
              (LocoNetSystemConnectionMemo*)InstanceManager::getDefault("LocoNetSystemConnectionMemo"));
    }
//};
#endif
