#ifndef LNTCPSERVERFRAME_H
#define LNTCPSERVERFRAME_H
#include "jmrijframe.h"

class LnTcpServer;
class CloseEvent;
class QPushButton;
class QCheckBox;
class QLabel;
class QSpinBox;
class LnTcpServerFrame : public JmriJFrame
{
 Q_OBJECT
public:
 /*public*/ LnTcpServerFrame(LnTcpServer* server, QWidget* parent = 0);
 /*public*/ void windowClosing(QCloseEvent* e);
 /*public*/ void dispose();
 QT_DEPRECATED static /*public*/ /*synchronized*/ LnTcpServerFrame* getInstance();
 static /*public*/ /*synchronized*/ LnTcpServerFrame* getDefault();
 /*public*/ QString getClassName();

signals:

public slots:
 void on_startButton_clicked();
 void on_stopButton_clicked();
 //void on_saveButton_clicked();
 //void on_autoStartCheckBox_toggled(bool);
 /*public*/ void notifyServerStateChanged(LnTcpServer* s);
 /*public*/ void notifyClientStateChanged(LnTcpServer* s, int clients);
 //void on_portNumber_valueChanged(int);
private:
 QSpinBox* portNumber;
 //SpinnerNumberModel portNumberModel;
 QLabel* portNumberLabel;// = new JLabel("  Port Number: ");
 QLabel* statusLabel;// = new JLabel("Server Status:         ");
 QLabel* clientStatus;// = new JLabel("   Client Count:  ");

// QCheckBox* autoStartCheckBox;// = new JCheckBox(
//         "Start Server at Application Startup");
 QPushButton* startButton;// = new JButton("Start Server");
 QPushButton* stopButton;// = new JButton("Stop Server");
 //QPushButton* saveButton;// = new JButton("Save Settings");

 /*private*/ void updateServerStatus();
 /*private*/ void updateClientStatus();
 LnTcpServer* server;

};

#endif // LNTCPSERVERFRAME_H
