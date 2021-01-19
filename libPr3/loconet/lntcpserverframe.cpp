#include "lntcpserverframe.h"
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QBoxLayout>
#include "lntcpserver.h"
#include <QLabel>
#include "instancemanager.h"

//ServerFrame::ServerFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * Frame displaying and programming a LocoNet clock monitor.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Digitrax
 * Inc for separate permission.
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2004
 * @author Alex Shepherd Copyright (C) 2006
 * @version	$Revision: 28746 $
 */
// /*public*/ class ServerFrame extends jmri.util.JmriJFrame implements ServerListner {

/**
 *
 */
// /*private*/ static final long serialVersionUID = -3729652398213286613L;

/*public*/ LnTcpServerFrame::LnTcpServerFrame(LnTcpServer* server, QWidget *parent) :
JmriJFrame(QString("LocoNetOverTcp Server"), parent)
{
 this->server = server;
 //super("LocoNetOverTcp Server");
 portNumberLabel = new QLabel("  Port Number: ");
 statusLabel = new QLabel("Server Status:         ");
 clientStatus = new QLabel("   Client Count:  ");

 //autoStartCheckBox = new QCheckBox(
//         "Start Server at Application Startup");
 startButton = new QPushButton("Start Server");
 stopButton = new QPushButton("Stop Server");
 //saveButton = new QPushButton("Save Settings");

 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget();
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
 centralWidget->setLayout(centralWidgetLayout);
 setCentralWidget(centralWidget);

// portNumber = new QSpinBox();
// //portNumberModel = new SpinnerNumberModel(65535, 1, 65535, 1);
// //portNumber.setModel(portNumberModel);
// portNumber->setMinimum(1);
// portNumber->setMaximum(65535);
// portNumber->setSingleStep(1);

// portNumber->setFocusable(false);

 // add GUI items
 {
// JPanel panel = new JPanel();
// panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
  QHBoxLayout* panelLayout = new QHBoxLayout;
  //panelLayout->addWidget(autoStartCheckBox);
//  panelLayout->addWidget(portNumberLabel);
//  panelLayout->addWidget(portNumber);
  //getContentPane().add(panel);
  centralWidgetLayout->addLayout(panelLayout);
 }
 {
// JPanel panel = new JPanel();
// panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
  QHBoxLayout* panelLayout = new QHBoxLayout;
  panelLayout->addWidget(startButton);
  panelLayout->addWidget(stopButton);
  //panelLayout->addWidget(saveButton);
 //getContentPane().add(panel);
  centralWidgetLayout->addLayout(panelLayout);
 }

 {
// JPanel panel = new JPanel();
// panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
  QHBoxLayout* panelLayout = new QHBoxLayout;
  panelLayout->addWidget(statusLabel);
  panelLayout->addWidget(clientStatus);
  //getContentPane().add(panel);
  centralWidgetLayout->addLayout(panelLayout);
 }
 updateServerStatus();

// startButton.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent a) {
//         Server.getInstance().enable();
//     }
// });
 connect(startButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
// stopButton.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent a) {
//         Server.getInstance().disable();
//     }
// });
 connect(stopButton, SIGNAL(clicked()), this, SLOT(on_stopButton_clicked()));


// saveButton.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent a) {
//         Server.getInstance().setAutoStart(autoStartCheckBox.isSelected());
//         Server.getInstance().setPortNumber(((Integer) portNumber.getValue()).intValue());
//         Server.getInstance().saveSettings();
//     }
// });
// connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));

// autoStartCheckBox.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent a) {
//         saveButton.setEnabled(true);
//     }
// });
 //connect(autoStartCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_autoStartCheckBox_toggled(bool)));

// if (portNumber != NULL) {
//     portNumber.addChangeListener(new ChangeListener() {
//         /*public*/ void stateChanged(ChangeEvent e) {
//             saveButton.setEnabled(true);
//         }
//     });
//  connect(portNumber, SIGNAL(valueChanged(int)), this, SLOT(on_portNumber_valueChanged(int)));
// }

 connect(this->server, SIGNAL(serverStateChanged(LnTcpServer*)), this, SLOT(notifyServerStateChanged(LnTcpServer*)));
 connect(this->server, SIGNAL(clientStateChanged(LnTcpServer*,int)), this, SLOT(notifyClientStateChanged(LnTcpServer*,int)));

 updateClientStatus();

 adjustSize();
}

void LnTcpServerFrame::on_startButton_clicked()
{
 this->server->enable();
}

void LnTcpServerFrame::on_stopButton_clicked()
{
 this->server->disable();
}
//void ServerFrame::on_saveButton_clicked()
//{
// LnTcpServer::getInstance()->setAutoStart(autoStartCheckBox->isChecked());
// LnTcpServer::getInstance()->setPortNumber( portNumber->value());
// LnTcpServer::getInstance()->saveSettings();
//}
//void LnTcpServerFrame::on_autoStartCheckBox_toggled(bool)
//{
// saveButton->setEnabled(true);
//}
//void LnTcpServerFrame::on_portNumber_valueChanged(int)
//{
// saveButton->setEnabled(true);
//}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//        justification = "Only used during system initialization")
/*public*/ void LnTcpServerFrame::windowClosing(QCloseEvent* e) {
    setVisible(false);
    //this->server->removeStateListener(this->listener);
    disconnect(this->server, SIGNAL(serverStateChanged(LnTcpServer*)), this, SLOT(notifyServerStateChanged(LnTcpServer*)));
    dispose();
    JmriJFrame::windowClosing(e);
}

/*public*/ void LnTcpServerFrame::dispose() {
    JmriJFrame::dispose();
}


//@Deprecated
/*static*/ /*public*/ /*synchronized*/ LnTcpServerFrame* LnTcpServerFrame::getInstance()
{
 return getDefault();
}

/**
 * Get the server status window for the default LocoNet over TCP server.
 *
 * @return the default server frame instance, creating it if needed
 */
/*static*/ /*public*/ /*synchronized*/ LnTcpServerFrame* LnTcpServerFrame::getDefault()
{
 LnTcpServerFrame* frame = (LnTcpServerFrame*)InstanceManager::getOptionalDefault("LnTcpServerFrame");
 if(frame == NULL)
  frame = (LnTcpServerFrame*)InstanceManager::setDefault("LnTcpServerFrame", new LnTcpServerFrame(LnTcpServer::getDefault()));
 return frame;
}

/*private*/ void LnTcpServerFrame::updateServerStatus()
{
 LnTcpServer* server = LnTcpServer::getDefault();
// autoStartCheckBox->setChecked(server->getAutoStart());
// autoStartCheckBox->setEnabled(!server->isEnabled());
// if (portNumber != NULL)
// {
//  portNumber->setValue(server->getPortNumber());
//  portNumber->setEnabled(!server->isEnabled());
//  portNumberLabel->setEnabled(!server->isEnabled());
// }
 startButton->setEnabled(!server->isEnabled());
 stopButton->setEnabled(server->isEnabled());
 //saveButton->setEnabled(server->isSettingChanged());
 statusLabel->setText(tr("Server Status: ") + (server->isEnabled() ? tr("Enabled") : tr("Disabled")));
 updateClientStatus();
}

/*private*/ void LnTcpServerFrame::updateClientStatus() {
    clientStatus->setText(tr("   Client Count: ") + QString::number(LnTcpServer::getDefault()->getClientCount()));
}

/*public*/ void LnTcpServerFrame::notifyServerStateChanged(LnTcpServer* /*s*/)
{
 updateServerStatus();
}

/*public*/ void LnTcpServerFrame::notifyClientStateChanged(LnTcpServer* /*s*/, int clients)
{
    clientStatus->setText("   Client Count: " + QString::number(clients));
}

/*public*/ QString LnTcpServerFrame::getClassName()
{
 return "jmri.jmrix.loconet.loconetovertcp.LnTcpServerFrame";
}
