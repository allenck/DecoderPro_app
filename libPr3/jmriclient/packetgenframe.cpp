#include "packetgenframe.h"
#include "jmriclienttrafficcontroller.h"
#include <QLabel>
#include <QPushButton>
#include "jtextfield.h"
#include <QBoxLayout>
#include "jmriclientmessage.h"

/**
 * Description: Frame for user input of JMRIClient messages
 *
 * @author Bob Jacobsen Copyright (C) 2008
 */
///*public*/ class PacketGenFrame extends jmri.util.JmriJFrame implements jmri.jmrix.jmriclient.JMRIClientListener {


    /*public*/ PacketGenFrame::PacketGenFrame(QWidget* parent) : JmriJFrame(parent){
        //super();
     // member declarations
     jLabel1 = new QLabel();
     sendButton = new QPushButton();
     packetTextField = new JTextField(12);

    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void PacketGenFrame::initComponents() {
        // the following code sets the frame's initial state

        jLabel1->setText("Command:");
        jLabel1->setVisible(true);

        sendButton->setText("Send");
        sendButton->setVisible(true);
        sendButton->setToolTip("Send packet");

        packetTextField->setText("");
        packetTextField->setToolTip("Enter command as ASCII string");
        packetTextField->setMaximumSize(
                QSize(packetTextField->maximumSize().width(),
                        packetTextField->sizeHint().height()
                )
        );

        setTitle("Send JMRI Client command");
        getContentPane()->setLayout(new QVBoxLayout());//getContentPane(), BoxLayout.Y_AXIS));

        getContentPane()->layout()->addWidget(jLabel1);
        getContentPane()->layout()->addWidget(packetTextField);
        getContentPane()->layout()->addWidget(sendButton);

//        sendButton.addActionListener(new java.awt.event.ActionListener() {
//            //@Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                sendButtonActionPerformed(e);
//            }
//        });
        connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(sendButtonActionPerformed()));

        // pack for display
        pack();
    }

    /*public*/ void PacketGenFrame::sendButtonActionPerformed(/*java.awt.event.ActionEvent e*/) {
        JMRIClientMessage* m = new JMRIClientMessage(packetTextField->text().length() + 1);
        for (int i = 0; i < packetTextField->text().length(); i++) {
            m->setElement(i, packetTextField->text().toLocal8Bit().at(i));
        }

        m->setElement(packetTextField->text().length(), '\n');
        tc->sendJMRIClientMessage(m, (JMRIClientListener*)this);
    }

    /**
     * {@inheritDoc}
     * Ignore messages.
     */
    //@Override
    /*public*/ void PacketGenFrame::message(JMRIClientMessage* m) {
    }

    /**
     * {@inheritDoc}
     * Ignore replies.
     */
    //@Override
    /*public*/ void PacketGenFrame::reply(JMRIClientReply* r) {
    }

    // connect to the TrafficController
    /*public*/ void PacketGenFrame::_connect(JMRIClientTrafficController* t) {
        tc = t;
    }

