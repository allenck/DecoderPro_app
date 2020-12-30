#include "sendpacketframe.h"
#include <QLabel>
#include <QPushButton>
#include <QByteArray>
#include "jtextfield.h"
#include <QCheckBox>
#include "jtogglebutton.h"
#include <QBoxLayout>
#include "box.h"
#include "jseparator.h"
#include "instancemanager.h"
#include "commandstation.h"
#include "stringutil.h"

//SendPacketFrame::SendPacketFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * User interface for sending DCC packets.
 * <P>
 * This was originally made from jmrix.loconet.logogen, but note that the logic
 * is somewhat different here. The LocoNet version waited for the sent (LocoNet)
 * packet to be echo'd, while this starts the timeout immediately.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2003
 * @version	$Revision: 28746 $
 */
///*public*/ class SendPacketFrame extends jmri.util.JmriJFrame {

/**
 *
 */
///*private*/ static final long serialVersionUID = 1094279262803359342L;

/*public*/ SendPacketFrame::SendPacketFrame(QWidget *parent) :
    JmriJFrame(parent)
{
 //super();
 jLabel1 = new QLabel();
 sendButton = new QPushButton();
 packetTextField = new JTextField(12);
 mPacketField = new QVector<JTextField*>(MAXSEQUENCE);
 mUseField = new QVector<QCheckBox*>(MAXSEQUENCE);
 mDelayField = new QVector<JTextField*>(MAXSEQUENCE);
 mRunButton = new JToggleButton("Go");
 log = new Logger("SendPacketFrame");
 mNextEcho= nullptr;
 timer = nullptr;
 cs = nullptr;
}

// internal members to hold sequence widgets
/*static final*/ int SendPacketFrame::MAXSEQUENCE = 4;

/*public*/ void SendPacketFrame::initComponents() /*throws Exception*/ {

    setTitle("Send DCC Packet");
    //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // handle single-packet part
    centralWidgetLayout->addWidget(new QLabel(tr("Send one packet:")));
    {
        //JPanel pane1 = new JPanel();
        //pane1.setLayout(new BoxLayout(pane1, BoxLayout.Y_AXIS));
     QVBoxLayout* pane1Layout = new QVBoxLayout();

        jLabel1->setText("Packet:");
        jLabel1->setVisible(true);

        sendButton->setText("Send");
        sendButton->setVisible(true);
        sendButton->setToolTip("Send packet");

        packetTextField->setToolTip("Enter packet as hex pairs, e.g. 82 7D");

        pane1Layout->addWidget(jLabel1);
        pane1Layout->addWidget(packetTextField);
        pane1Layout->addWidget(sendButton);
        pane1Layout->addWidget(Box::createVerticalGlue());

//        sendButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                sendButtonActionPerformed(e);
//            }
//        });
        connect(sendButton, SIGNAL(clicked()), this, SLOT(sendButtonActionPerformed()));

        centralWidgetLayout->addLayout(pane1Layout);
    }

    centralWidgetLayout->addWidget(new JSeparator());

    // Configure the sequence
    centralWidgetLayout->addWidget(new QLabel("Send sequence of packets:"));
//    JPanel pane2 = new JPanel();
//    pane2.setLayout(new GridLayout(MAXSEQUENCE + 2, 4));
    QGridLayout* pane2Layout = new QGridLayout();
    pane2Layout->addWidget(new QLabel(""),0, 0);
    pane2Layout->addWidget(new QLabel("Send"),0,1);
    pane2Layout->addWidget(new QLabel("packet"),0, 2);
    pane2Layout->addWidget(new QLabel("wait (msec)"),0, 3);
    for (int i = 0; i < MAXSEQUENCE; i++)
    {
        pane2Layout->addWidget(new QLabel(QString::number(i + 1)),i+1, 0);
        mUseField->replace(i, new QCheckBox());
          mPacketField->replace(i, new JTextField(10));
        mDelayField->replace(i,  new JTextField(10));
        pane2Layout->addWidget(mUseField->at(i),i+1,1);
        pane2Layout->addWidget(mPacketField->at(i),i+1,2);
        pane2Layout->addWidget(mDelayField->at(i), i+1,3);
    }
    pane2Layout->addWidget(mRunButton); // starts a new row in layout
    centralWidgetLayout->addLayout(pane2Layout);

//    mRunButton.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            runButtonActionPerformed(e);
//        }
//    });
    connect(mRunButton, SIGNAL(), this, SLOT(runButtonActionPerformed()));

    // get the CommandStation reference
    cs = qobject_cast<CommandStation*>(InstanceManager::getDefault("CommandStation"));
    if (cs == nullptr) {
        log->error("No CommandStation object available");
    }

    // add help menu
    addHelpMenu("package.jmri.jmrit.sendpacket.SendPacketFrame", true);

    // pack to cause display
    adjustSize();
}

/*public*/ void SendPacketFrame::sendButtonActionPerformed(JActionEvent* /*e*/) {
    cs->sendPacket(createPacket(packetTextField->text()), 1);
}


/**
 * Internal routine to handle timer starts & restarts
 */
/*protected*/ void SendPacketFrame::restartTimer(int delay) {
    if (timer == nullptr) {
        timer = new QTimer; //(delay, new java.awt.event.ActionListener() {

//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                sendNextItem();
//            }
//        });
        connect(timer, SIGNAL(timeout()), this, SLOT(sendNextItem()));
    }
    timer->stop();
    timer->setInterval(delay);
    timer->setSingleShot(true);
    timer->start();
}

/**
 * Run button pressed down, start the sequence operation
 *
 * @param e
 */
/*public*/ void SendPacketFrame::runButtonActionPerformed(JActionEvent* /*e*/)
{
    if (!mRunButton->isChecked()) {
        return;
    }
    // make sure at least one is checked
    bool ok = false;
    for (int i = 0; i < MAXSEQUENCE; i++) {
        if (mUseField->at(i)->isChecked()) {
            ok = true;
        }
    }
    if (!ok) {
        mRunButton->setChecked(false);
        return;
    }
    // start the operation
    mNextSequenceElement = 0;
    sendNextItem();
}

/**
 * Echo has been heard, start delay for next packet
 */
void SendPacketFrame::startSequenceDelay() {
    // at the start, mNextSequenceElement contains index we're
    // working on
    int delay = 500;   // default delay if non specified, or format bad
    try {
        delay = mDelayField->at(mNextSequenceElement)->text().toInt();
    } catch (NumberFormatException e) {
    }

    // increment to next line at completion
    mNextSequenceElement++;
    // start timer
    restartTimer(delay);
}

/**
 * Send next item; may be used for the first item or when a delay has
 * elapsed.
 */
void SendPacketFrame::sendNextItem() {
    // check if still running
    if (!mRunButton->isSelected()) {
        return;
    }
    // have we run off the end?
    if (mNextSequenceElement >= MAXSEQUENCE) {
        // past the end, go back
        mNextSequenceElement = 0;
    }
    // is this one enabled?
    if (mUseField->at(mNextSequenceElement)->isChecked()) {
        // make the packet
        QByteArray m = createPacket(mPacketField->at(mNextSequenceElement)->text());
        // send it
        mNextEcho = m;
        if (m != nullptr) {
            cs->sendPacket(m, 1);
        } else {
            log->warn("Message invalid: " + mPacketField->at(mNextSequenceElement)->text());
        }
        // and queue the rest of the sequence if we're continuing
        if (mRunButton->isSelected()) {
            startSequenceDelay();
        }
    } else {
        // ask for the next one
        mNextSequenceElement++;
        sendNextItem();
    }
}

/**
 * Create a well-formed DCC packet from a String
 *
 * @param s
 * @return The packet, with contents filled-in
 */
QByteArray SendPacketFrame::createPacket(QString s) {
    // gather bytes in result
    QByteArray b = StringUtil::bytesFromHexString(s);
    if (b.length() == 0) {
        return nullptr;  // no such thing as a zero-length message
    }
    return b;
}

/**
 * When the window closes, stop any sequences running
 */
/*public*/ void SendPacketFrame::dispose() {
    mRunButton->setChecked(false);
    JmriJFrame::dispose();
}
/*public*/ QString SendPacketFrame::getClassName()
{
 return "jmri.jmrit.sendpacket.SendPacketFrame";
}

