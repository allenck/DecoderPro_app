#ifndef SERVERFRAME_H
#define SERVERFRAME_H
#include "jmrijframe.h"

class Server;
class CloseEvent;
class QPushButton;
class QCheckBox;
class QLabel;
class QSpinBox;
class ServerFrame : public JmriJFrame
{
 Q_OBJECT
public:
 /*public*/ void windowClosing(QCloseEvent* e);
 /*public*/ void dispose();
 static /*public*/ /*synchronized*/ ServerFrame* getInstance();

signals:

public slots:
 void on_startButton_clicked();
 void on_stopButton_clicked();
 void on_saveButton_clicked();
 void on_autoStartCheckBox_toggled(bool);
 /*public*/ void notifyServerStateChanged(Server* s);
 /*public*/ void notifyClientStateChanged(Server* s, int clients);
 void on_portNumber_valueChanged(int);
private:
 QSpinBox* portNumber;
 //SpinnerNumberModel portNumberModel;
 QLabel* portNumberLabel;// = new JLabel("  Port Number: ");
 QLabel* serverStatus;// = new JLabel("Server Status:         ");
 QLabel* clientStatus;// = new JLabel("   Client Count:  ");

 QCheckBox* autoStartCheckBox;// = new JCheckBox(
//         "Start Server at Application Startup");
 QPushButton* startButton;// = new JButton("Start Server");
 QPushButton* stopButton;// = new JButton("Stop Server");
 QPushButton* saveButton;// = new JButton("Save Settings");
 explicit ServerFrame(QWidget *parent = 0);

 static ServerFrame* self;
 /*private*/ void updateServerStatus();
 /*private*/ void updateClientStatus();

};

#endif // SERVERFRAME_H
