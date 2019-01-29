#include "userinterface.h"
#include "loggerfactory.h"
#include "logger.h"
#include <QMenuBar>
#include <QMenu>
#include <QLabel>
#include "jtable.h"
#include "userpreferencesmanager.h"
#include "rostergroupcombobox.h"
#include "instancemanager.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include <QToolBar>
#include "fileutil.h"
#include "imageicon.h"
#include <qdesktopwidget.h>
#include "deviceserver.h"
#include "largepowermanagerbutton.h"
#include "stopallbutton.h"
#include <QImageReader>
#include "withrottleslistmodel.h"
#include <QApplication>
#include "withrottlemanager.h"
#include "withrottlepreferences.h"
#include "serversocket.h"
#include "controllerfilteraction.h"
#include "tabbedpreferencesaction.h"
#include <QThread>
#include <QHeaderView>
#include "zeroconfservice.h"
#include "inet4address.h"

//UserInterface::UserInterface()
//{

//}
/**
 * UserInterface.java Create a window for WiThrottle information, advertise
 * service, and create a thread for it to run in.
 *
 *	listen() has to run in a separate thread.
 *
 * @author Brett Hoffman Copyright (C) 2009, 2010
 * @author Randall Wood Copyright (C) 2013
 */
// /*public*/ class UserInterface extends JmriJFrame implements DeviceListener, DeviceManager, ZeroConfServiceListener {

/*private*/ /*final*/ /*static*/ Logger* UserInterface::log = LoggerFactory::getLogger("UserInterface");
//    static /*final*/ ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.withrottle.WiThrottleBundle");

UserInterface::UserInterface(QWidget* parent) : JmriJFrame(false, false, parent)
{
 portLabel = new QLabel(tr("pending..."));
 manualPortLabel = new QLabel();
 userPreferences = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 rosterGroupSelectorPreferencesName = /*this.getClass().getName()*/ QString("jmri.jmrit.withrottle.UserInterface") + ".rosterGroupSelector";
 rosterGroupSelector = new RosterGroupComboBox(userPreferences->getComboBoxLastSelection(rosterGroupSelectorPreferencesName));
 isListen = true;
 //socket = NULL;
 deviceList = NULL;
 // TODO: task = NULL;

 if (deviceList == NULL) {
     deviceList = new QVector<WiDevice*>();
 }

 //show all IPv4 addresses in window, for use by manual connections
 addIPAddressesToUI();

 createWindow();

// setShutDownTask();
 createServerThread();
}	//	End of constructor

/*public*/ void UserInterface::createServerThread() {
#if 0
    ServerThread* s = new ServerThread(this);
    s->setName("WiThrottleGUIServer"); // NOI18N

    s->start();
#else
 listen(); // Do ZeroConf stuff
 device =  DeviceServer::instance();
 device->run();
#endif
}

/*private*/ void UserInterface::addIPAddressesToUI() {
 //get port# directly from prefs
 int port = static_cast<WiThrottlePreferences*>(InstanceManager::getDefault("WiThrottlePreferences"))->getPort();
 //list the local IPv4 addresses on the UI, for manual connections
 QList<InetAddress*> has = ZeroConfService::hostAddresses(); //get list of local, non-loopback addresses
 QString as = ""; //build multiline string of valid addresses
 for (InetAddress* ha : has) {
     //if (ha instanceof Inet4Address) { //ignore IPv6 addresses
  if(qobject_cast<Inet4Address*>(ha))
         this->portLabel->setText(ha->getHostName());
         as += ha->getHostAddress() + ":" + port + "<br />";
         this->manualPortLabel->setText("<html>" + as + "</html>"); // NOI18N
     }
}

/*protected*/ void UserInterface::createWindow() {
    panel = new QWidget();
    GridBagLayout* panelLayout;
    panel->setLayout(panelLayout = new GridBagLayout());
    GridBagConstraints con = GridBagConstraints();
    new QVBoxLayout(getContentPane());
    getContentPane()->layout()->addWidget(panel);
    con.fill = GridBagConstraints::NONE;
    con.weightx = 0.5;
    con.weighty = 0;

    QLabel* label = new QLabel(tr("Advertising WiThrottle v%1 on:").arg(DeviceServer::getWiTVersion()));
    con.gridx = 0;
    con.gridy = 0;
    con.gridwidth = 2;
    panelLayout->addWidget(label, con);

    con.gridx = 0;
    con.gridy = 1;
    con.gridwidth = 2;
    panelLayout->addWidget(portLabel, con);

    con.gridy = 2;
    panelLayout->addWidget(manualPortLabel, con);

    numConnected = new QLabel(tr("Clients") + " " + deviceList->size());
    con.weightx = 0;
    con.gridx = 2;
    con.gridy = 2;
    con.ipadx = 5;
    con.gridwidth = 1;
    panelLayout->addWidget(numConnected, con);

    QWidget* rgsPanel = new QWidget();
    QHBoxLayout* rgsPanelLayout = new QHBoxLayout(rgsPanel);
    rgsPanelLayout->addWidget(new QLabel(tr("Roster Group")));
    rgsPanelLayout->addWidget(rosterGroupSelector);
    rgsPanel->setToolTip(tr("Locomotives in this Roster Group will be selectable in Wi-Fi devices"));
    QToolBar* withrottleToolBar = new QToolBar();
    withrottleToolBar->setFloatable(false);
    withrottleToolBar->addWidget(new StopAllButton());
    withrottleToolBar->addWidget(new LargePowerManagerButton());
    withrottleToolBar->addWidget(rgsPanel);
    con.weightx = 0.5;
    con.ipadx = 0;
    con.gridx = 1;
    con.gridy = 3;
    con.gridwidth = 2;
    //panelLayout->addWidget(withrottleToolBar, con);
    addToolBar(withrottleToolBar);

    /*
     QLabel* vLabel = new QLabel("v"+DeviceServer.getWiTVersion());
     con.weightx = 0;
     con.gridx = 2;
     con.gridy = 3;
     panelLayout->addWidget(vLabel, con);
     */
    QLabel* icon;
    QUrl imageURL = FileUtil::findURL(":resources/IconForWiThrottle.gif");

    if (!imageURL.isEmpty()) {
//        ImageIcon* image = new ImageIcon(imageURL);
        icon = new QLabel(/*image*/);
        QImageReader* imageReader = new QImageReader(imageURL.path());
        icon->setPixmap(QPixmap::fromImageReader(imageReader));
        con.weightx = 0.5;
        con.gridx = 2;
        con.gridy = 0;
        con.ipady = 5;
        con.gridheight = 2;
        panelLayout->addWidget(icon, con);
    }
    int socketPort = WiThrottleManager::withrottlePreferencesInstance()->getPort();
    DeviceServer* server = new DeviceServer(socketPort, (DeviceManager*)this);

    connect(server, SIGNAL(serverStateChanged(DeviceServer*)), this, SLOT(on_serverStateChanged(DeviceServer*)));
    connect(server, SIGNAL(deviceConnected(WiDevice*)), this, SLOT(notifyDeviceConnected(WiDevice*)));
    connect(server, SIGNAL(deviceDisconnected(WiDevice*)), this, SLOT(notifyDeviceDisconnected(WiDevice*)));

//  Add a list of connected devices and the address they are set to.
    withrottlesListModel = new WiThrottlesListModel(deviceList);
    withrottlesList = new JTable(withrottlesListModel);
//    withrottlesList->setPreferredScrollableViewportSize(QSize(300, 80));

    withrottlesList->setRowHeight(20);
    withrottlesList->horizontalHeader()->setStretchLastSection(true);
    //scrollTable = new JScrollPane(withrottlesList);

    con.gridx = 0;
    con.gridy = 4;
    con.weighty = 1.0;
    con.ipadx = 10;
    con.ipady = 10;
    con.gridheight = 3;
    con.gridwidth = GridBagConstraints::REMAINDER;
    con.fill = GridBagConstraints::BOTH;
    panelLayout->addWidget(/*scrollTable*/withrottlesList, con);

//  Create the menu to use with WiThrottle window. Has to be before pack() for Windows.
    buildMenu();

//  Set window size & location
    this->setTitle("WiThrottle");
    this->adjustSize();

//    this->setResizable(true);
//    QRect screenRect = new Rectangle(GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds());
    QDesktopWidget* desktop = QApplication::desktop();
//    QSize screen = desktop->screen()->size();
    QRect screenRect = desktop->screen()->rect();

//  Centers on top edge of screen
    this->setLocation((screenRect.width() / 2) - (this->width() / 2), 0);

    this->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);

    setVisible(true);

    //setMinimumSize(size());
    resize(300,300);

//    rosterGroupSelector.addActionListener(new ActionListener() {

//        @SuppressWarnings("unchecked")
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            userPreferences.addComboBoxLastSelection(rosterGroupSelectorPreferencesName, (String) ((JComboBox<String>) e.getSource()).getSelectedItem());
////              Send new selected roster group to all devices
//            for (DeviceServer device : deviceList) {
//                device.sendPacketToDevice(device.sendRoster());
//            }
//        }
//    });
    connect(rosterGroupSelector, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_rosterGroupSelector(QString)));
}

void UserInterface::on_rosterGroupSelector(QString text)
{
 userPreferences->setComboBoxLastSelection(rosterGroupSelectorPreferencesName, text);
//                 facelessServer.setSelectedRosterGroup(s);
 //              Send new selected roster group to all devices
 foreach (WiDevice* device, *deviceList)
 {
  Q_UNUSED(device)
#if 1 // TODO:
  device->deviceServer->sendPacketToDevice(device->deviceServer->sendRoster());
#endif
 }
}

/*protected*/ void UserInterface::buildMenu()
{
    this->setMenuBar(_menuBar = new QMenuBar());

    QMenu* menu = new QMenu(tr("WiThrottle"));
    serverOnOff = new QAction(tr("Stop Server"), this);

//    serverOnOff.addActionListener(new AbstractAction() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            if (isListen) {	//	Stop server
//                disableServer();
//                serverOnOff.setText(tr("MenuMenuStart"));
//                portLabel.setText(tr("LabelNone"));
//                manualPortLabel.setText(NULL);
//            } else {	//	Restart server
//                serverOnOff.setText(tr("MenuMenuStop"));
//                isListen = true;

//                createServerThread();
//            }
//        }
//    });
    connect(serverOnOff, SIGNAL(triggered()), this, SLOT(on_serverOnOff()));

    menu->addAction(serverOnOff);

    menu->addAction(new ControllerFilterAction(this));

    Action* prefsAction = new TabbedPreferencesAction(
            tr("Preferences..."),
            "WITHROTTLE", this);

    menu->addAction(prefsAction);

    this->menuBar()->addMenu(menu);

    // add help menu
    addHelpMenu("package.jmri.jmrit.withrottle.UserInterface", true);
}

void UserInterface::on_serverOnOff()
{
 if (isListen)
 {	//	Stop server
     disableServer();
     serverOnOff->setText(tr("Start Server"));
     portLabel->setText(tr("none"));
     manualPortLabel->setText(NULL);
 }
 else
 {	//	Restart server
     serverOnOff->setText(tr("Stop Server"));
     isListen = true;

     createServerThread();
     addIPAddressesToUI();

 }
}

void UserInterface::on_serverStateChanged(DeviceServer */*s*/)
{

}

/*public*/ void UserInterface::listen()
{
 int socketPort = WiThrottleManager::withrottlePreferencesInstance()->getPort();
#if 0
 try {	//Create socket on available port
     socket = new ServerSocket(socketPort);
 } catch (IOException e1) {
     log->error("New ServerSocket Failed during /*static*/)");
     return;
 }

 port = socket->getLocalPort();
 if (log->isDebugEnabled()) {
     log->debug("WiThrottle listening on TCP port: " + port);
 }

#if 0 // TODO:
 service = ZeroConfService::create("_withrottle._tcp.local.", port);
 service.addEventListener(this);
 service.publish();
#endif
 while (isListen)
 { //Create DeviceServer threads
  DeviceServer* device;
#if 1 // TODO:
  try
  {
   log->info("Creating new WiThrottle DeviceServer(socket) on port " + QString::number(port) + ", waiting for incoming connection...");
   device = new DeviceServer(socket->accept(), this);  //blocks here until a connection is made

   //Thread t = new Thread(device);
   QThread* dThread = new QThread();
   connect(dThread, SIGNAL(started()), device, SLOT(run()));
   device->addDeviceListener(this);
   device->moveToThread(dThread);
   connect(device, SIGNAL(finished()), dThread, SLOT(quit()));
   connect(device, SIGNAL(finished()), dThread, SLOT(deleteLater()));
   dThread->setObjectName("WiThrottleUIDeviceServer"); // NOI18N
    log->debug("Starting WiThrottleUIDeviceServer thread");
   dThread->start();
  } catch (IOException e3)
  {
   if (isListen)
   {
    log->error("Listen Failed on port " + QString::number(port));
   }
   return;
  }
#endif
 }
#endif
 log->info("Creating new WiThrottle DeviceServer(socket) on port " + QString::number(socketPort) + ", waiting for incoming connection...");
 device = new DeviceServer(socketPort, (DeviceManager*)this);
 service = ZeroConfService::create("_withrottle._tcp.local.", socketPort);
 //service->addEventListener((ZeroConfServiceListener*)this);
 connect(service, SIGNAL(servicePublished(ZeroConfServiceEvent*)), this, SLOT(servicePublished(ZeroConfServiceEvent*)));
 service->publish();
}

//@Override
/*public*/ void UserInterface::notifyDeviceConnected(WiDevice* device) {

    deviceList->append(device);
    numConnected->setText(tr("Clients") + " " + QString::number(deviceList->size()));
    withrottlesListModel->updateDeviceList(deviceList);

    adjustSize();
}

//@Override
/*public*/ void UserInterface::notifyDeviceDisconnected(WiDevice* device) {
    if (deviceList->size() < 1) {
        return;
    }
    int i;
    for(i=0; i < deviceList->count(); i++)
    {
     if(deviceList->at(i)->address == device->address)
     if (!deviceList->removeOne(deviceList->at(i)))
     {
        return;
     }
     break;
    }

    numConnected->setText(tr("Clients") + " " + QString::number(deviceList->size()));
    withrottlesListModel->updateDeviceList(deviceList);
#if 0 // TODO:
    device->removeDeviceListener((DeviceListener*)this);
#endif
    adjustSize();
}

//@Override
/*public*/ void UserInterface::notifyDeviceAddressChanged(WiDevice* /*device*/)
{
    withrottlesListModel->updateDeviceList(deviceList);
}

/**
 * Received an UDID, filter out any duplicate.
 *
 */
//@Override
/*public*/ void UserInterface::notifyDeviceInfoChanged(WiDevice* device) {
 foreach(WiDevice* dev, *deviceList)
 {
  if(dev->address == device->address)
  {
   dev->name = device->name;
   return;
  }
 }
#if 0

    //  Filter duplicate connections
    if ((device->getUDID() != NULL) && (deviceList->size() > 0))
    {
        for (int i = 0; i < deviceList->size(); i++) {
            DeviceServer* listDevice = deviceList->at(i);
            if ((device != listDevice) && (listDevice->getUDID() != NULL) && (listDevice->getUDID() == (device->getUDID()))) {
                //  If in here, array contains duplicate of a device
                 log->debug("Has duplicate of device, clearing old one.");
                listDevice->closeThrottles();
                break;
            }
        }
    }
#endif
    withrottlesListModel->updateDeviceList(deviceList);
}

//	Clear out the deviceList array and close each device thread
/*private*/ void UserInterface::stopDevices()
{
#if 0
    DeviceServer* device;
    int cnt = 0;
    if (deviceList->size() > 0) {
        do {
            device = deviceList->at(0);
            if (device != NULL) {
                device->closeThrottles(); //Tell device to stop its throttles,
                device->closeSocket();   //close its sockets
                //close() will throw read error and it will be caught
                //and drop the thread.
                cnt++;
                if (cnt > 200) {
                    break;
                }
            }
        } while (!deviceList->isEmpty());
    }
    deviceList->clear();
    withrottlesListModel->updateDeviceList(deviceList);
    numConnected->setText(tr("LabelClients") + " " + QString::number(deviceList->size()));
#endif
}

#if 1
//@Override
/*protected*/ void UserInterface::setShutDownTask()
{
 if (InstanceManager::getNullableDefault("ShutDownManager") != nullptr)
 {
//     task = new jmri.implementation.AbstractShutDownTask(getTitle()) {
//         @Override
//         /*public*/ boolean execute() {
//             disableServer();
//             return true;
//         }
//     };
  task = new UIShutdownTask(getTitle(), this);
     static_cast<ShutDownManager*>(InstanceManager::getDefault("ShutDownManager"))->_register(task);
 }
}
#endif
UIShutdownTask::UIShutdownTask(QString title, UserInterface *ui) : AbstractShutDownTask(title)
{
 this->ui = ui;
}
bool UIShutdownTask::execute()
{
 ui->disableServer();
 return true;
}
/*private*/ void UserInterface::disableServer() {
    isListen = false;
//    stopDevices();
//    try {
//        socket->close();
//         log->debug("UI socket in ServerThread just closed");
////        service.stop();
//    } catch (IOException ex) {
//         log->error("socket in ServerThread won't close");
//    }
    DeviceServer::instance()->closeThrottles();
}

//@Override
/*public*/ QString UserInterface::getSelectedRosterGroup() {
    return rosterGroupSelector->getSelectedRosterGroup();
}
#if 0
@Override
/*public*/ void serviceQueued(ZeroConfServiceEvent se) {
    this.portLabel.setText(tr("LabelPending"));
    this.manualPortLabel.setText(NULL);
}

@Override
/*public*/ void servicePublished(ZeroConfServiceEvent se) {
    try {
        try {
            InetAddress addr = se.getDNS().getInetAddress();
            //output last good ipV4 address to the window to support manual entry
            if (addr instanceof Inet4Address) {
                this.portLabel.setText(addr.getHostName());
                this.manualPortLabel.setText(addr.getHostAddress() + ":" + port); // NOI18N
                 log->debug("Published IPv4 ZeroConf service for '{}' on {}:{}", se.getService().key(), addr.getHostAddress(), port); // NOI18N
            } else {
                 log->debug("Published IPv6 ZeroConf service for '{}' on {}:{}", se.getService().key(), addr.getHostAddress(), port); // NOI18N
            }
        } catch (NullPointerException | IOException ex) {
             log->error("Address is invalid: {}", ex.getLocalizedMessage());
            this.portLabel.setText(Inet4Address.getLocalHost().getHostName());
            this.manualPortLabel.setText(Inet4Address.getLocalHost().getHostAddress() + ":" + port); // NOI18N
        }
    } catch (UnknownHostException ex) {
         log->error("Failed to determine this system's IP address: {}", ex.getLocalizedMessage());
        this.portLabel.setText(tr("LabelUnknown")); // NOI18N
        this.manualPortLabel.setText(NULL);
    }
}

@Override
/*public*/ void serviceUnpublished(ZeroConfServiceEvent se) {
    this.portLabel.setText(tr("LabelNone"));
    this.manualPortLabel.setText(NULL);
}
#endif
//  listen() has to run in a separate thread.
//static class ServerThread extends Thread {

//    UserInterface UI;

    ServerThread::ServerThread(UserInterface* _UI) {
        UI = _UI;
        currentThread = new QThread();
        currentThread->setObjectName(name);
        connect(currentThread, SIGNAL(started()), this, SLOT(start()));
        moveToThread(currentThread);
        connect(this, SIGNAL(finished()), currentThread, SLOT(quit()));
        connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
        connect(currentThread, SIGNAL(finished()), currentThread, SLOT(deleteLater()));
    }

    void ServerThread::setName(QString name)
    {
     this->name = name;
     currentThread->setObjectName(name);
    }

    //@Override
    /*public*/ void ServerThread::start() {
        UI->listen();
        UI->log->debug("Leaving serverThread.run()");
    }

    //@Override
    /*public*/ void UserInterface::servicePublished(ZeroConfServiceEvent* se) {
        try {
            InetAddress* addr = se->getDNS()->getInetAddress();
            // most addresses are Inet6Address objects,
            if (!addr->isLoopbackAddress()) {
                log->info(tr("Published ZeroConf service for '%1' on %2:%3").arg(se->getService()->key()).arg( addr->getHostAddress()).arg(port)); // NOI18N
            }
        } catch (NullPointerException ex) {
            log->error(tr("NPE in FacelessServer.servicePublished(): %1").arg(ex.getLocalizedMessage()));
        } catch (IOException ex) {
            log->error(tr("IOException in FacelessServer.servicePublished(): %1").arg(ex.getLocalizedMessage()));
        }
    }
