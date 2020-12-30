#ifndef SENDPACKETFRAME_H
#define SENDPACKETFRAME_H

#include "jmrijframe.h"

class CommandStation;
class JActionEvent;
class JToggleButton;
class QCheckBox;
class QLabel;
class QPushButton;
class JTextField;
class SendPacketFrame : public JmriJFrame
{
 Q_OBJECT
public:
 explicit SendPacketFrame(QWidget *parent = 0);
 /*public*/ void initComponents() /*throws Exception*/;
 /*public*/ void dispose();
 /*public*/ QString getClassName();

signals:

public slots:
 /*public*/ void sendButtonActionPerformed(JActionEvent* /*e*/);
 /*public*/ void runButtonActionPerformed(JActionEvent* /*e*/);

private:
 // member declarations
 QLabel* jLabel1;// = new javax.swing.JLabel();
 QPushButton* sendButton;// = new javax.swing.JButton();
 JTextField* packetTextField;// = new javax.swing.JTextField(12);
 static /*final*/ int MAXSEQUENCE;// = 4;
 QVector<JTextField*>* mPacketField;// = new JTextField[MAXSEQUENCE];
 QVector<QCheckBox*>* mUseField;// = new JCheckBox[MAXSEQUENCE];
 QVector<JTextField*>* mDelayField;// = new JTextField[MAXSEQUENCE];
 JToggleButton* mRunButton;// = new JToggleButton("Go");
 Logger* log;
 // control sequence operation
 int mNextSequenceElement;// = 0;
 QByteArray mNextEcho;//= null;
 QTimer* timer;// = null;
 // /*private*/ data
 /*private*/ CommandStation* cs;// = null;
 void startSequenceDelay();
 QByteArray createPacket(QString s);

private slots:
 void sendNextItem();

protected:
 /*protected*/ void restartTimer(int delay);

};

#endif // SENDPACKETFRAME_H
