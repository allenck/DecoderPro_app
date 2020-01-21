#ifndef SPROGPACKETGENFRAME_H
#define SPROGPACKETGENFRAME_H
#include "jmrijframe.h"
#include "sprogsystemconnectionmemo.h"
#include <QLabel>
#include <QPushButton>
#include "jtextfield.h"

namespace Sprog
{
 class SprogPacketGenFrame : public JmriJFrame
 {
  Q_OBJECT

 public:
  SprogPacketGenFrame(SprogSystemConnectionMemo*, QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void sendButtonActionPerformed(/*ActionEvent* e*/);

 private:
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;
  // member declarations
  QLabel* jLabel1;// = new javax.swing.JLabel();
  QPushButton* sendButton;// = new javax.swing.JButton();
  JTextField* packetTextField;// = new javax.swing.JTextField(12);

 };
}
#endif // SPROGPACKETGENFRAME_H
