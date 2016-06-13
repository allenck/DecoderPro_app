#include "serverframe.h"
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QBoxLayout>
#include "server.h"
#include <QLabel>

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

/*private*/ ServerFrame::ServerFrame(QWidget *parent) :
JmriJFrame(QString("LocoNetOverTcp Server"), parent)
{
 //super("LocoNetOverTcp Server");
 portNumberLabel = new QLabel("  Port Number: ");
 serverStatus = new QLabel("Server Status:         ");
 clientStatus = new QLabel("   Client Count:  ");

 autoStartCheckBox = new QCheckBox(
         "Start Server at Application Startup");
 startButton = new QPushButton("Start Server");
 stopButton = new QPushButton("Stop Server");
 saveButton = new QPushButton("Save Settings");

 //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget();
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
 centralWidget->setLayout(centralWidgetLayout);
 setCentralWidget(centralWidget);

 portNumber = new QSpinBox();
 //portNumberModel = new SpinnerNumberModel(65535, 1, 65535, 1);
 //portNumber.setModel(portNumberModel);
 portNumber->setMinimum(1);
 portNumber->setMaximum(65535);
 portNumber->setSingleStep(1);

// portNumber->setFocusable(false);

 // add GUI items
 {
// JPanel panel = new JPanel();
// panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
  QHBoxLayout* panelLayout = new QHBoxLayout;
  panelLayout->addWidget(autoStartCheckBox);
  panelLayout->addWidget(portNumberLabel);
  panelLayout->addWidget(portNumber);
  //getContentPane().add(panel);
  centralWidgetLayout->addLayout(panelLayout);
 }
 {
// JPanel panel = new JPanel();
// panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
  QHBoxLayout* panelLayout = new QHBoxLayout;
  panelLayout->addWidget(startButton);
  panelLayout->addWidget(stopButton);
  panelLayout->addWidget(saveButton);
 //getContentPane().add(panel);
  centralWidgetLayout->addLayout(panelLayout);
 }

 {
// JPanel panel = new JPanel();
// panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
  QHBoxLayout* panelLayout = new QHBoxLayout;
  panelLayout->addWidget(serverStatus);
  panelLayout->addWidget(clientStatus);
  //getContentPane().add(panel);
  centralWidgetLayout->addLayout(panelLayout);
 }

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
 connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));

// autoStartCheckBox.addActionListener(new ActionListener() {
//     /*public*/ void actionPerformed(ActionEvent a) {
//         saveButton.setEnabled(true);
//     }
// });
 connect(autoStartCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_autoStartCheckBox_toggled(bool)));

 if (portNumber != NULL) {
//     portNumber.addChangeListener(new ChangeListener() {
//         /*public*/ void stateChanged(ChangeEvent e) {
//             saveButton.setEnabled(true);
//         }
//     });
  connect(portNumber, SIGNAL(valueChanged(int)), this, SLOT(on_portNumber_valueChanged(int)));
 }

 connect(Server::getInstance(), SIGNAL(serverStateChanged(Server*)), this, SLOT(notifyServerStateChanged(Server*)));

 updateClientStatus();

 adjustSize();
}
void ServerFrame::on_startButton_clicked()
{
 Server::getInstance()->enable();
}
void ServerFrame::on_stopButton_clicked()
{
 Server::getInstance()->disable();
}
void ServerFrame::on_saveButton_clicked()
{
 Server::getInstance()->setAutoStart(autoStartCheckBox->isChecked());
 Server::getInstance()->setPortNumber( portNumber->value());
 Server::getInstance()->saveSettings();
}
void ServerFrame::on_autoStartCheckBox_toggled(bool)
{
 saveButton->setEnabled(true);
}
void ServerFrame::on_portNumber_valueChanged(int)
{
 saveButton->setEnabled(true);
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//        justification = "Only used during system initialization")
/*public*/ void ServerFrame::windowClosing(QCloseEvent* e) {
    setVisible(false);
    self = NULL;
    Server::getInstance()->setStateListner(NULL);
    dispose();
    JmriJFrame::windowClosing(e);
}

/*public*/ void ServerFrame::dispose() {
    JmriJFrame::dispose();
}
ServerFrame* ServerFrame::self = NULL;

/*static*/ /*public*/ /*synchronized*/ ServerFrame* ServerFrame::getInstance()
{
 if (self == NULL)
 {
  self = new ServerFrame();
  Server* server = Server::getInstance();
  server->setStateListner((ServerListner*)self);
  server->updateServerStateListener();
  server->updateClientStateListener();
  connect(server, SIGNAL(clientStateChanged(Server*,int)), self, SLOT(notifyClientStateChanged(Server*,int)));
 }

 return self;
}

/*private*/ void ServerFrame::updateServerStatus()
{
 Server* server = Server::getInstance();
 autoStartCheckBox->setChecked(server->getAutoStart());
 autoStartCheckBox->setEnabled(!server->isEnabled());
 if (portNumber != NULL)
 {
  portNumber->setValue(server->getPortNumber());
  portNumber->setEnabled(!server->isEnabled());
  portNumberLabel->setEnabled(!server->isEnabled());
 }
 startButton->setEnabled(!server->isEnabled());
 stopButton->setEnabled(server->isEnabled());
 saveButton->setEnabled(server->isSettingChanged());
 serverStatus->setText(tr("Server Status: ") + (server->isEnabled() ? "Enabled" : "Disabled"));
}

/*private*/ void ServerFrame::updateClientStatus() {
    clientStatus->setText("   Client Count: " + QString::number(Server::getInstance()->getClientCount()));
}

/*public*/ void ServerFrame::notifyServerStateChanged(Server* s)
{
#if 0
    javax.swing.SwingUtilities.invokeLater(new Runnable() {
        /*public*/ void run() {
            updateServerStatus();
        }
    });
#else
 updateServerStatus();
#endif
}

/*public*/ void ServerFrame::notifyClientStateChanged(Server* s, int clients)
{
#if 0
    javax.swing.SwingUtilities.invokeLater(new Runnable() {
        /*public*/ void run() {
            updateClientStatus();
        }
    });

#endif
    clientStatus->setText("   Client Count: " + QString::number(clients));

}

