#ifndef PACKETGENFRAME_H
#define PACKETGENFRAME_H
#include "jmrijframe.h"

class JMRIClientMessage;
class JMRIClientReply;
class JMRIClientTrafficController;
class QLabel;
class QPushButton;
class JTextField;
class PacketGenFrame : public JmriJFrame
{
 Q_OBJECT
public:
 PacketGenFrame(QWidget* parent = nullptr);
 /*public*/ void initComponents();
 /*public*/ void message(JMRIClientMessage* m);
 /*public*/ void reply(JMRIClientReply* r);
 /*public*/ void _connect(JMRIClientTrafficController* t);

public slots:
 void sendButtonActionPerformed();

private:
 // member declarations
 QLabel* jLabel1;// = new javax.swing.JLabel();
 QPushButton* sendButton;// = new javax.swing.JButton();
 JTextField* packetTextField;// = new javax.swing.JTextField(12);
 // private data
 /*private*/ JMRIClientTrafficController* tc = nullptr;

};

#endif // PACKETGENFRAME_H
