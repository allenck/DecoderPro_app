#include "sprogpacketgenframe.h"
#include <QBoxLayout>

using namespace Sprog;

/**
 * Frame for user input of Sprog messages.
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2010
 */
///*public*/ class SprogPacketGenFrame extends jmri.util.JmriJFrame {


/*public*/ SprogPacketGenFrame::SprogPacketGenFrame(SprogSystemConnectionMemo* memo, QWidget* parent) : JmriJFrame(parent
                                                                                                                   ){
    //super();
 jLabel1 = new QLabel();
 sendButton = new QPushButton();
 packetTextField = new JTextField(12);
    _memo = memo;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void SprogPacketGenFrame::initComponents() {
    // the following code sets the frame's initial state

    jLabel1->setText(tr("Command:"));
    jLabel1->setVisible(true);

    sendButton->setText(tr("Send"));
    sendButton->setVisible(true);
    sendButton->setToolTip(tr("Send Packet to SPROG"));

    packetTextField->setText("");
    packetTextField->setToolTip(tr("Send Packet to SPROG"));
    packetTextField->setMaximumSize(
            QSize(packetTextField->maximumSize().width(),
                    packetTextField->sizeHint().height()
            )
    );

    setTitle(tr("Send Command"));
    //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
    QVBoxLayout* contentPaneLayout = new QVBoxLayout(getContentPane());

    contentPaneLayout->addWidget(jLabel1);
    contentPaneLayout->addWidget(packetTextField);
    contentPaneLayout->addWidget(sendButton);

//    sendButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            sendButtonActionPerformed(e);
//        }
//    });
    connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(sendButtonActionPerformed()));

    // pack for display
    pack();
}

/*public*/ void SprogPacketGenFrame::sendButtonActionPerformed(/*ActionEvent* e*/) {
    SprogMessage* m = new SprogMessage(packetTextField->text());
    _memo->getSprogTrafficController()->sendSprogMessage(m);
}
