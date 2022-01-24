#include "hexfileframe.h"
#include <QPushButton>
#include <jtextfield.h>
#include <QLabel>
#include <QFileDialog>
#include "xmlfile.h"
#include <QBoxLayout>
#include "lnhexfileport.h"
#include "throttlemanager.h"
#include <QValidator>
#include <QThread>
#include "lnpacketizer.h"
#include "lnsensormanager.h"
#include "debugprogrammermanager.h"
#include "instancemanager.h"
#include "debugthrottlemanager.h"
#include "activeflag.h"
#include "fileutil.h"

HexFileFrame::HexFileFrame(QWidget *parent) :
    JmriJFrame(parent)
{
 //private static final long serialVersionUID = -2625562807572301674L;
 // member declarations
 openHexFileButton = new QPushButton();
 filePauseButton = new QPushButton();
 jButton1 = new QPushButton();
 delayField = new JTextField(5);
 delayField->setValidator(new QIntValidator(200, 10000));
 jLabel1 = new QLabel();
 connected = false;;
 port = NULL;
 log = new Logger("HexFileFrame");
 packets = NULL;
 setMinimumSize(300,200);
}
/**
 * Frame to inject LocoNet messages from a hex file
 * This is a sample frame that drives a test App.  It controls reading from
 * a .hex file, feeding the information to a LocoMonFrame (monitor) and
 * connecting to a LocoGenFrame (for sending a few commands).
 * @author			Bob Jacobsen  Copyright 2001, 2002
 * @version                     $Revision: 28493 $
 */
// /*public*/ class HexFileFrame extends JmriJFrame {

/**
 *
 */

// to find and remember the log file
//QFileDialog* inputFileChooser =
//        XmlFile::userFileChooser("Hex files", "hex");

///*public*/ HexFileFrame() {
//    super();
//}

//LocoNetSystemConnectionMemo adaptermemo = NULL;

/*public*/ void HexFileFrame::initComponents() //throw (Exception)
{
 if (port==NULL)
 {
  log->error("initComponents called before adapter has been set");
 }
 // the following code sets the frame's initial state

 openHexFileButton->setText("Open file");
 openHexFileButton->setVisible(true);
 openHexFileButton->setToolTip("run from hex file");

 filePauseButton->setText("Pause");
 filePauseButton->setVisible(true);
 filePauseButton->setToolTip("pauses the trace at the source");

 jButton1->setText("Continue");
 jButton1->setVisible(true);
 jButton1->setToolTip("continues the trace at the source");

 delayField->setText("200");
 delayField->setVisible(true);
 delayField->setToolTip("delay (in milliseconds) between commands");

 jLabel1->setText("Delay:");
 jLabel1->setVisible(true);

 setTitle("LocoNet Simulator");
 QWidget* centralWidget = new QWidget;
 QVBoxLayout* centralWidgetLayout;
 setCentralWidget(centralWidget);
 getContentPane()->setLayout(centralWidgetLayout = new QVBoxLayout); //(getContentPane(), BoxLayout.Y_AXIS));

 //QWidget* pane1 = new QWidget();
 QHBoxLayout* pane1Layout = new QHBoxLayout;
 //pane1.setLayout(new BoxLayout(pane1, BoxLayout.X_AXIS));
 pane1Layout->addWidget(openHexFileButton);
 pane1Layout->addWidget(new QWidget()); // dummy
 centralWidgetLayout->addLayout(pane1Layout);

 //JPanel pane2 = new JPanel();
 //pane2.setLayout(new BoxLayout(pane2, BoxLayout.X_AXIS));
 QHBoxLayout* pane2Layout = new QHBoxLayout;
 pane2Layout->addWidget(jLabel1);
 pane2Layout->addWidget(delayField);
 centralWidgetLayout->addLayout(pane2Layout);

 //JPanel pane3 = new JPanel();
 //pane3.setLayout(new BoxLayout(pane3, BoxLayout.X_AXIS));
 QHBoxLayout* pane3Layout = new QHBoxLayout;
 pane3Layout->addWidget(filePauseButton);
 pane3Layout->addWidget(jButton1);
 centralWidgetLayout->addLayout(pane3Layout);


//    openHexFileButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                openHexFileButtonActionPerformed(e);
//            }
//        });
 connect(openHexFileButton, SIGNAL(clicked()), this, SLOT(openHexFileButtonActionPerformed()));
//    filePauseButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                filePauseButtonActionPerformed(e);
//            }
//        });
 connect(filePauseButton, SIGNAL(clicked()), this, SLOT(filePauseButtonActionPerformed()));
//    jButton1.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                jButton1ActionPerformed(e);
//            }
//        });
 connect(jButton1, SIGNAL(clicked()), this, SLOT(jButton1ActionPerformed()));
//    delayField.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                delayFieldActionPerformed(e);
//            }
//        });
 connect(delayField, SIGNAL(editingFinished()), this, SLOT(delayFieldActionPerformed()));

 // create a new Hex file handler, set its delay
 //port = new LnHexFilePort();
 //port->setDelay(Integer.valueOf(delayField.getText()).intValue());

 // and make the connections
 //configure();
 resize(300, 200);
}


/*public*/ void HexFileFrame::dispose()
{
 // leaves the LocoNet Packetizer (e.g. the simulated connection)
 // running.
 JmriJFrame::dispose();
}


/*public*/ void HexFileFrame::openHexFileButtonActionPerformed(JActionEvent* /*e*/)
{
    // select the file
    // start at current file, show dialog
//    inputFileChooser.rescanCurrentDirectory();
//    int retVal = inputFileChooser->showOpenDialog(this);

//    // handle selection or cancel
//    if (retVal != /*JFileChooser::APPROVE_OPTION*/QFileDialog::Accepted) return;  // give up if no file selected
 setCursor(Qt::WaitCursor);
 QString filename = QFileDialog::getOpenFileName(this,tr("Select file"),FileUtil::getUserFilesPath(),"Hex files (, *.hex");
 setCursor(Qt::ArrowCursor);
 if(filename == "")
  return;

 // call load to process the file
//    port->load(inputFileChooser->selectedFiles.at(0));
 port->load(new QFile(filename));

 // wake copy
 //sourceThread.interrupt();
 sourceThread->exit();

 // reach here while file runs.  Need to return so GUI still acts,
 // but that normally lets the button go back to default.
}

/*public*/ void HexFileFrame::configure()
{
 if (port==NULL)
 {
  log->error("initComponents called before adapter has been set");
  return;
 }
 // connect to a packetizing LnTrafficController
 packets = new LnPacketizer((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo());
 packets->connectPort(port);
 connected = true;

 // create memo
 ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->setLnTrafficController(packets);

 // do the common manager config
 ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->configureCommandStation(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS100),   // full featured by default
                                        false, false, false);
 ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->configureManagers();
 LnSensorManager* lnSensorManager = (LnSensorManager*)((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getSensorManager();
 lnSensorManager->setDefaultSensorState(port->getOptionState("SensorDefaultState"));

 // Install a debug programmer, replacing the existing LocoNet one
 DefaultProgrammerManager* ep = ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getProgrammerManager();
 ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->setProgrammerManager(
         new DebugProgrammerManager(port->getSystemConnectionMemo()));
 if (((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getProgrammerManager()->isAddressedModePossible()) {
     InstanceManager::store(((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getProgrammerManager(), "addressedProgrammerManager");
 }
 if (((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getProgrammerManager()->isGlobalProgrammerAvailable()) {
     InstanceManager::store(((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getProgrammerManager(), "GlobalProgrammerManager");
 }
 InstanceManager::deregister(ep, "AddressedProgrammerManager");
 InstanceManager::deregister(ep, "GlobalProgrammerManager");

// Install a debug throttle manager, replacing the existing LocoNet one
((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->setThrottleManager(new DebugThrottleManager(port->getSystemConnectionMemo()));
InstanceManager::setThrottleManager(
    ((LocoNetSystemConnectionMemo*)port->getSystemConnectionMemo())->getThrottleManager());

 // start operation of packetizer
 packets->startThreads();
 sourceThread = new QThread(port);
 sourceThread->start();

 ActiveFlag::setActive();

}

//@SuppressWarnings("deprecation")
/*public*/ void HexFileFrame::filePauseButtonActionPerformed(JActionEvent* /*e*/)
{
 //sourceThread.suspend();
 sourceThread->quit();
 // sinkThread.suspend(); // allow sink to catch up
}

//@SuppressWarnings("deprecation")
/*public*/ void HexFileFrame::jButton1ActionPerformed(JActionEvent* /*e*/) {  // resume button
//sourceThread.resume();
    sourceThread->start();
    // sinkThread.resume();
}

/*public*/ void HexFileFrame::delayFieldActionPerformed(JActionEvent* /*e*/) {
    // if the hex file has been started, change its delay
    if (port!=NULL) port->setDelay(delayField->text().toInt());
}



//private Thread sinkThread;

/*public*/ void HexFileFrame::setAdapter(LnHexFilePort* adapter) { port = adapter; }
/*public*/ LnHexFilePort* HexFileFrame::getAdapter() { return port; }

/*public*/ QString HexFileFrame::getClassName()
{
 return "jmri.jmrix.loconet.hexfile.HexFileFrame";
}
