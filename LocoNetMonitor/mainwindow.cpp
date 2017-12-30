#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QCloseEvent>
#include "lnsensormanager.h"
#include "lnportcontroller.h"
#include "lnpacketizer.h"
#include <QMessageBox>
#include <QSettings>
#include "querycvdialog.h"
#include "aboutdialog.h"
#include <QActionGroup>
#include "QStringList"
#include "language.h"
#include "loconetmsgdialog.h"
#include "lnturnoutmanager.h"
#include "ObjectViewer/objectviewerdialog.h"
#include "namedbeanhandle.h"
#include "defaultshutdownmanager.h"
#include "rfidreporter.h"
#include "../ftdilib/ftdilib_global.h"
#include "addpaneleditordialog.h"
#include "panelmenu.h"
#include "Throttle/throttlewindow.h"
#include "Throttle/listthrottles.h"
#include "Roster/rosterframe.h"
#include "connectionstatus.h"
#include "jmriuserpreferencesmanager.h"
#include "controlpaneleditor.h"
#include "simpleclockframe.h"
#include "nixieclockframe.h"
#include "lcdclockframe.h"
#include "analogclockframe.h"
#include "powerpanelframe.h"
#include "simpleturnoutctrlframe.h"
#include "helputil.h"
#include "../LayoutEditor/locomonpane.h"
#include "consoleinterface.h"
#include "jmrijframeinterface.h"
#include "Throttle/throttleframemanager.h"
#include "../libPr3/Roster/rostermenu.h"
#include "instancemanager.h"
#include "paneserviceprogframe.h"
#include "progservicemodecombobox.h"
#include "decoderindexfile.h"
#include "decoderfile.h"
#include "jtextfield.h"
#include "flowlayout.h"
#include <qtreeview.h>
#include "paneprogaction.h"
#include "paneopsprogaction.h"
#include "simpleprogaction.h"
#include "busyglasspane.h"
//#include "../libPr3/LocoIO/cmdstnconfigpane.h"
#include <QSettings>
#include "connectionconfigframe.h"
#include "jmrixconfigpane.h"
#include "tabbedpreferences.h"
#include "preferencespane.h"
#include <QMetaType>
#include "tabbedpreferencesaction.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfig.h"
#include "connectionstatus.h"
#include "../libPr3/loconet/Pr3/pr3connectionconfig.h"
#include "turnouttabletabaction.h"
#include "../libPr3/LocoIO/lnnamedpaneaction.h"
//#include "../libPr3/LocoIO/ds64panel.h"
#include "loconetmenu.h"

MainWindow::MainWindow(QWidget *parent) :
    Apps((JFrame*)this,parent),
    ui(new Ui::MainWindow)
{
 ui->setupUi(this);
 getSettings();
 create_Language_Menu();
 moduleDlg.clear();
 sql = NULL;
 lnMon = new LlnMon(this);
 f = NULL;
 log = new Logger("MainWindow");
 statusLabel = new QLabel("idle");
 //modePane = new ProgServiceModeComboBox();
 qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid pink; }");

 editor = NULL;
 panelEditor = NULL;
 frame = NULL;
 loconetTurnoutManager = NULL;
 connectionMemo = NULL;
 configFrame = NULL;
 locoBufferAdapter = NULL;
 ui->actionSlot_monitor->setDisabled(true);
 ConsoleInterface* cf = ConsoleInterface::instance();
 connect(cf, SIGNAL(message(QString)), this, SLOT(OnConsoleMessageReceived(QString)));
 instanceManager = InstanceManager::instance();
 InstanceManager::store(lnMon, lnMon->metaObject()->className());
// configXmlManager = new ConfigXmlManager(this);
// instanceManager->setConfigureManager((ConfigureManager*)configXmlManager);
// QFile file("/home/allen/.jmri/UserPrefsDecoderProConfig2.xml");
// configXmlManager->load(&file);
 ui->actionAuto_scroll_to_bottom->setChecked(bAutoScrollToBottom);

 locoBufferAdapter = NULL;
 //setWindowTitle("LocoNet Monitor");
 QStringList languages;
 languages << tr("German") << tr("English"); // present to provide string for Linquist to translate.

// thread = new MasterThread();
// dialog = new Dialog(thread,this);
// dialog->setWindowTitle(tr("Select Comm Port"));
// connect(thread,SIGNAL(timeout(QString)), this, SLOT(timeout(QString)));
// connect(thread, SIGNAL(error(QString)),this, SLOT(error(QString)));
// connect(dialog, SIGNAL(newPortInfo(QSerialPortInfo)), this, SLOT(onNewPortInfo(QSerialPortInfo)));
// onNewPortName(portName);

 ui->menuCommand_Station->clear();
 ui->menuFile->removeAction(ui->actionPreferences);
 ui->menuFile->addAction(new TabbedPreferencesAction(tr("Preferences"),this));
 //pr3 = new PR3Adapter(this);
// pr3 = NULL;
// QStringList list = pr3->commandStationOptions();
 QStringList list;
// list << "DCS100 (Chief)"<<
//         "DCS200"<<
//         "DCS50 (Zephyr)"<<
//         "DCS51 (Zephyr Xtra)"<<
//         "DB150 (Empire Builder)"<<
//         "Intellibox"<<
//         "LocoCentral" <<
//         "LocoBuffer (PS)"<<
//         "Mix-Master";
 QActionGroup*  actionGroup = new QActionGroup(this);
 //foreach (QString commandStationType,list)
 foreach(QString commandStation, LnCommandStationType::commandStationNames())
 {
  QAction* act = new QAction(commandStation,this);
  act->setCheckable(true);
  actionGroup->addAction(act);
  if(commandStationType == commandStation);
  {
   act->setChecked(true);
  }
  ui->menuCommand_Station->addAction(act);
 }
 connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(onCommandStationTypeSelected(QAction*)));
 //connect(ui->menuWindow, SIGNAL(aboutToShow()), this, SLOT(on_menuWindow_aboutToShow()));
 QMenuBar* mb = ui->menubar;
 scriptMenu(ui->menubar, (WindowInterface*)this);

 openRfid(); // enumerate and open Rfid sensors
 RosterMenu* rosterMenu = new RosterMenu(tr("Roster"),RosterMenu::MAINMENU,this);
 QMainWindow::menuBar()->addMenu(rosterMenu);
 addHelpMenu("package.apps.DecoderPro.DecoderPro", true);
 //menuBar()->addMenu(HelpUtil::instance()->makeHelpMenu("package.apps.DecoderPro.DecoderPro", true));
// locoMonPane = new LocoMonPane(this);
// if(checkActive())
// {
//  locoMonPane->initComponents(connectionMemo);
//  LnTrafficController* controller = connectionMemo->getLnTrafficController();
//  connect(controller, SIGNAL(messageProcessed(LocoNetMessage*)), locoMonPane, SLOT(message(LocoNetMessage*)));
// }
// ifc = new JmriJFrameInterface(this);


 owner = new JTextField(20);
 TurnoutTableTabAction* turnoutTableAction = new TurnoutTableTabAction("Turnout Table",this);
 ui->menuTools->addAction(turnoutTableAction);

// LnNamedPaneAction* lnNpA = new LnNamedPaneAction("Loconet Stats", (WindowInterface*)this,"LocoStatsPanel",connectionMemo);
// ui->menuLocoNet->addAction(lnNpA);
// lnNpA = new LnNamedPaneAction("Slot Monitor", (WindowInterface*)this,"SlotMonPane",connectionMemo);
// ui->menuLocoNet->insertAction(NULL,lnNpA);
// lnNpA = new LnNamedPaneAction("DS64 Config", (WindowInterface*)this,"DS64Panel",connectionMemo);
// ui->menuLocoNet->insertAction(ui->actionConfigure_Command_Station, lnNpA);
// lnNpA = new LnNamedPaneAction("Clock Monitor", (WindowInterface*)this,"ClockMonPane",connectionMemo);
// ui->menuLocoNet->insertAction(NULL, lnNpA);
// lnNpA = new LnNamedPaneAction("LocoNet Id", (WindowInterface*)this,"LocoIdPanel",connectionMemo);
// ui->menuLocoNet->addAction(lnNpA);

 if(connectionMemo == NULL)
  connectionMemo = (LocoNetSystemConnectionMemo*)InstanceManager::getDefault("LocoNetSystemConnectionMemo");
 ui->menubar->insertMenu(ui->menuLocoNet->menuAction(),  LocoNetMenu::instance(connectionMemo, this));
 ui->menuLocoNet->clear();
 ui->menubar->removeAction(ui->menuLocoNet->menuAction());

}

MainWindow::~MainWindow()
{
    delete ui;
//    delete dialog;
    thread->exit();
    delete thread;
}
void MainWindow::onMessageReceived(LocoNetMessage *msg, bool bOutput)
{
 //QMutexLocker locker(&mutex);
 //LlnMon mon;
  if(data->bProbing)
   data->message(msg);

 if(bOutput)
  return;
 signalMapper = NULL;
 QListWidgetItem* item = new QListWidgetItem();
 if(!lnMon->displayMessage(*msg).startsWith("LocoIO")) return;
 item->setText(lnMon->displayMessage(*msg));
 if((msg->getNumDataElements()> 2) &&(msg->getElement(2) == 0x50 || msg->getElement(2)==0))
  item->setTextColor(Qt::red);
 //item->setData(Qt::UserRole, msg);
 item->setToolTip(msg->toString());
 if(ui->listWidget->count() > 300)
 {
   QListWidgetItem* item1 = ui->listWidget->item(0);
   ui->listWidget->removeItemWidget(item1);
 }
 ui->listWidget->addItem(item);
 if(bAutoScrollToBottom)
  ui->listWidget->scrollToBottom();
}
void MainWindow::OnConsoleMessageReceived(QString s)
{
 QListWidgetItem* item = new QListWidgetItem(s);
 ui->listWidget->addItem(item);
}

//void MainWindow::on_actionConfig_triggered()
//{
// dialog->show();
//}
void MainWindow::timeout(const QString &s)
{
//    thread->run();
 ui->statusbar->showMessage(s);
}
void MainWindow::error(const QString &s)
{
 ui->statusbar->showMessage(s);
}
void MainWindow::on_actionClear_display_triggered()
{
 ui->listWidget->clear();
}
void MainWindow::on_actionExit_triggered()
{
 Apps::handleQuit();
 close();
}

// called when a new comm port is selected
void MainWindow::onNewPortInfo(QSerialPortInfo info)
{
 this->info = info;
 if(info.productIdentifier() == 0x000a)
  commandStationType = "LocoBuffer (PS)";
 if(info.productIdentifier() == 0x77FE)
  commandStationType = "PR3 standalone programmer";
 onNewPortName(info.portName());
}

bool  MainWindow::checkActive()
{
 if(ActiveFlag::isActive())
 {
  QObjectList* list = InstanceManager::getList("SystemConnectionMemo");
  int i = 0;
  foreach (QObject* memo, *list)
  {
   if(qobject_cast<LocoNetSystemConnectionMemo*>(memo) != NULL)
   {
    connectionMemo = (LocoNetSystemConnectionMemo*)memo;
    LnPacketizer* trafficController = (LnPacketizer*)connectionMemo->getLnTrafficController();
    if(trafficController != NULL)
    {
     //locoBufferAdapter = trafficController->controller;
     ConnectionStatus* connectionStatus = ConnectionStatus::instance();
     connect(connectionStatus->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(On_newConnection()));
     On_newConnection();
     return true;
    }
   }
   i++;
  }
  return true;
 }
 return false;
}

void MainWindow::onNewPortName(QString portName)
{

 this->portName = portName;  // TODO: use LocoBufferUsbAdapter

 //ConnectionStatus::instance()->setConnectionState(portName, ConnectionStatus::CONNECTION_);
 if(commandStationType == "LocoBuffer (PS)")
 {
  locoBufferAdapter = new LocoBufferUsbAdapter(this);
 }
 else
 {
  locoBufferAdapter =new PR3Adapter(this);
  locoBufferAdapter->setObjectName("PR3Adapter");
  locoBufferAdapter->configureOption2(commandStationType);
  Pr3ConnectionConfig* pr3ConnectionConfig = new Pr3ConnectionConfig((PR3Adapter*)locoBufferAdapter,this);
  InstanceManager::configureManagerInstance()->registerConfig(pr3ConnectionConfig);
 }

 connect(locoBufferAdapter, SIGNAL(error(QString)), this, SLOT(onPortOpenError(QString)));
 locoBufferAdapter->setPort(this->portName);
 //pr3->setThread(thread);o
 locoBufferAdapter->configureBaudRate("57,600 baud");
 if(locoBufferAdapter->openPort(portName, qApp->applicationName())!= "")
 {
   //on_actionConfig_triggered();
   //return;
 }

 QString optionName = locoBufferAdapter->getOption2Name();
 locoBufferAdapter->setOptionState(optionName, "MS100");
 locoBufferAdapter->configureOption2(commandStationType); // set current value
 locoBufferAdapter->setCommandStationType(LnCommandStationType::getByName(commandStationType));
 locoBufferAdapter->configure();
 ((LocoNetSystemConnectionMemo*)locoBufferAdapter->getSystemConnectionMemo())->getSlotManager()->setCommandStationType(LnCommandStationType::getByName(commandStationType));
 //On_newConnection();
}

void MainWindow::On_newConnection(PropertyChangeEvent* /*e*/)
{

 data = new LocoIOData(0x151, 1, connectionMemo->getLnTrafficController());
 if(!connect(connectionMemo->getLnTrafficController(),SIGNAL(messageProcessed(LocoNetMessage*,bool)),this, SLOT(onMessageReceived(LocoNetMessage*,bool))))
     qDebug() << "Connect failed ";
 //connectionMemo = new LocoNetSystemConnectionMemo((LnTrafficController*)locoBufferAdapter->packetizer(),slotManager,this);
 //connectionMemo = locoBufferAdapter->getSystemConnectionMemo();
 //connectionMemo->configureManagers();  // IS THIS Necessary?
 connectionMemo->getPowerManager();
 InstanceManager::store(connectionMemo->getProgrammerManager(),"ProgrammerManager");
 ui->actionSlot_monitor->setEnabled(true);
// loconetTurnoutManager = new LnTurnoutManager(locoBufferAdapter->packetizer(),locoBufferAdapter->packetizer(),"L",false);
 loconetTurnoutManager= connectionMemo->getTurnoutManager();
 lnMon->setLocoNetTurnoutManager(loconetTurnoutManager);

 // test code
// Turnout * turnout = loconetTurnoutManager->newTurnout("LT1", "1");
// turnout->setComment("Test turnout #1");

 //loconetSensorManager = new LnSensorManager(locoBufferAdapter->packetizer(),"L", this);
 loconetSensorManager = connectionMemo->getSensorManager();
 lnMon->setLocoNetSensorManager(loconetSensorManager);
// Sensor* sensor = loconetSensorManager->newSensor("LS1", "Block1");
// loconetSensorManager->newSensor("LS2", "Block2");
// loconetSensorManager->updateAll();
 loconetLightManager = connectionMemo->getLightManager();

 // Initialize SlotManager
 //slotManager = new SlotManager((LnTrafficController*)locoBufferAdapter->packetizer(),this);
 slotManager = connectionMemo->getSlotManager();
 //connect(locoBufferAdapter->packetizer(), SIGNAL(messageProcessed(LocoNetMessage*,bool)), slotManager, SLOT(message(LocoNetMessage*)));
 //connect(locoBufferAdapter->packetizer(), SIGNAL(messageProcessed(LocoNetMessage*,bool)), connectionMemo->getPowerManager(), SLOT(message(LocoNetMessage*)));

// QString pName = "LS1";
// NamedBeanHandleManager<Sensor*>* nbhm = new NamedBeanHandleManager<Sensor*>(this);
// InstanceManager::setDefault("NamedBeanHandleManager<Sensor*>", nbhm);
// NamedBeanHandleManager<Sensor*>* ss = (NamedBeanHandleManager<Sensor*>*)InstanceManager::getDefault("NamedBeanHandleManager<Sensor*>");
 //Sensor* ss = ((NamedBeanHandleManager<Sensor*>)InstanceManager::getDefault("NamedBeanHandleManager<Sensor*>"));//.getNamedBeanHandle(pName, sensor);

 lnMon->setLocoNetReporterManager(connectionMemo->getReporterManager());

InstanceManager::setShutDownManager(new DefaultShutDownManager(this));
((DefaultShutDownManager*)InstanceManager::shutDownManagerInstance())->_register(((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->getShutDownTask());

 connect(data, SIGNAL(probeCompleted(QList<ProbedAddress>)), this, SLOT(onProbeCompleted(QList<ProbedAddress>)));
 saveSettings();
 data->setLIOVersion(tr("<Not found>"));
 //LocoIO::probeLocoIOs(pr3);
 if(sql == NULL)\
 {
  sql = new Sql(data, this);
  connect(sql, SIGNAL(error(QString)),this, SLOT(error(QString)));
 }
 //LocoIO::discover((LnTrafficController*)locoBufferAdapter->packetizer());
 LocoIO::discover(connectionMemo->getLnTrafficController());
#if 0 // LocoIOModules now does this
 data->startProbe();
#endif
 //modePane = new ProgServiceModeComboBox();

 InstanceManager::store(data,data->metaObject()->className());
 //qDebug()<<InstanceManager::contentsToString();
// ui->menuProgrammer->clear();
// ui->menuProgrammer->addAction(new SimpleProgAction(this));
// PaneProgAction* serviceProg = new PaneProgAction("Service Mode (Programming Track) Programmer",this);
// ui->menuProgrammer->addAction(serviceProg);
// PaneOpsProgAction* opsProg = new PaneOpsProgAction("Operations Mode (Main Track) Programmer", this);
// ui->menuProgrammer->addAction(opsProg);

}
void MainWindow::onPortOpenError(QString s) // [slot]
{
 ui->statusbar->showMessage(s);
}
#if 0
void MainWindow::on_actionLocoIO_triggered(bool bNewAddress)
{
 Q_UNUSED(bNewAddress)
 foreach(LocoIODialog* dlg, moduleDlg)
 {
  if(dlg->Data()->getUnitAddress() == data->getUnitAddress() && dlg->Data()->getUnitSubAddress() == data->getUnitSubAddress())
  {
   dlg->show();
   return;
  }
 }
 LocoIODialog* dlg = new LocoIODialog(address, connectionMemo->getLnTrafficController(), bHexValues, sql, this);
 moduleDlg.append(dlg);
 dlg->setAddress(data->getUnitAddress(), data->getUnitSubAddress());
 dlg->show();
}
void MainWindow::onProbeCompleted(QList<ProbedAddress > list)
{
 //slotManager->update();

 if(list.isEmpty())
 {
  //QMessageBox::critical(this, tr("Error"), tr("No LocoIO modules found!"));
  ui->statusbar->showMessage(tr("No LocoIO modules found!"),20000);
 }
// signalMapper = new QSignalMapper(this);
// this->list = list;
// ui->menuLocoIO->clear();
// int i=0;
// foreach(probedAddress addr, list)
// {
//  QAction* act = new QAction(QString("0x%1/0x%2 (%4/%5) %6 %3").arg(addr.unitAddr, 0, 16).arg(addr.unitSubAddr,0,16).arg(addr.firmwareVersion).arg(addr.unitAddr, 0, 10).arg(addr.unitSubAddr,0,10).arg(addr.moduleType),this);
//  act->setToolTip(tr("Configure LocoIO module 0x%1/0x%2 %6 %3").arg(addr.unitAddr, 0, 16).arg(addr.unitSubAddr).arg(addr.firmwareVersion).arg(addr.moduleType));
//  if(!connect(act, SIGNAL(triggered()), signalMapper, SLOT(map())))
//   qDebug()<<"action mapping failed to connect";
//  signalMapper->setMapping(act,i++);
//  //connect(act, SIGNAL(triggered()), this, SLOT(on_actionLocoIO_triggered()));
//  ui->menuLocoIO->addAction(act);
// }
// if(!connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(onLocoIO_selected(int))))
//  qDebug()<<"signal mapping failed to connect";

}
void MainWindow::onLocoIO_selected(int index)
{
 ProbedAddress addr = list[index];
 bool bAddressChange = false;
 if(data->getUnitAddress() != addr.unitAddr || data->getUnitSubAddress() != addr.unitSubAddr)
 {
  bAddressChange = true;
  checkDirty();
 }
 data->setUnitAddress(addr.unitAddr);
 data->setUnitSubAddress(addr.unitSubAddr);
 data->setModuleType(addr.moduleType);
 on_actionLocoIO_triggered(bAddressChange);
}
#endif
void MainWindow::on_actionValues_in_Hex_toggled(bool bChecked)
{
 bHexValues = bChecked;
}
void MainWindow::getSettings()
{
 QSettings settings;
 settings.beginGroup("Main");
 bHexValues = settings.value("displayHex",true).toBool();
 portName = settings.value("portName", "ttyACM0").toString();
 QString defLocale = QLocale::system().name();       // e.g. "de_DE"
 defLocale.truncate(defLocale.lastIndexOf('_')); // e.g. "de" or "en"
 default_Locale = settings.value("locale",defLocale).toString();
 commandStationType = settings.value("commandStationType", "DCS51 (Zephyr Xtra)").toString();
 settings.endGroup();
}
void MainWindow::saveSettings()
{
 QSettings settings;
 settings.beginGroup("Main");
 settings.setValue("displayHex", bHexValues);
 settings.setValue("portName", portName);
 settings.setValue("commandStationType", commandStationType);
 settings.setValue("locale",default_Locale);
 settings.endGroup();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
 if(LocoMonPane::instance() != NULL)
  LocoMonPane::instance()->close();
//  if(checkDirty())
//  {
//   event->ignore();
//   return;
//  }
//  saveSettings();
//  event->accept();;
//  DefaultShutDownManager* mgr = (DefaultShutDownManager*)InstanceManager::shutDownManagerInstance();
//  mgr->shutdown();
 Apps::windowClosing(event);
}
#if 0
void MainWindow::on_actionProbe_triggered()
{
 data->startProbe();
}
#endif
void MainWindow::on_actionQuery_Cv_triggered()
{
 QueryCvDialog* dlg = new QueryCvDialog(data, pr3, bHexValues);
 dlg->show();
}
bool MainWindow::checkDirty()
{
 foreach(LocoIODialog* dlg, moduleDlg)
 {
  if(dlg->Data()->dirty() || dlg->Data()->x2Dirty() ||(dlg->Data()->servoDirty()))
  {
   int base = bHexValues?16:10;
   switch(QMessageBox::warning(this,tr("Warning"),tr("Cv values for %1 %2/%3 have been changed and not written. Do you want to change your changes?").arg(dlg->Data()->getModuleType()).arg(dlg->Data()->getUnitAddress(),0,base).arg(dlg->Data()->getUnitSubAddress(),0,base),QMessageBox::Save | QMessageBox::Cancel| QMessageBox::Discard))
   {
   case QMessageBox::Save:
    dlg->on_btnWriteAll_clicked();
    break;
   case QMessageBox::Discard:
    break;
   case QMessageBox::Cancel:
    return true;
   default:
    return true;
   }
  }
 }
 return false;
}
void MainWindow::on_actionAbout_triggered()
{
 AboutDialog dlg(this);
 dlg.exec();
}
void MainWindow::onCommandStationTypeSelected(QAction * action)
{
 commandStationType = action->text();
}
//http://developer.qt.nokia.com/wiki/How_to_create_a_multi_language_application#870b564bf23d3f9264d0f68036405cde
// we create the menu entries dynamically,dependant on the existing translations.
void MainWindow::create_Language_Menu(void)
{
// format systems language
 //QString default_Locale = QLocale::system().name();       // e.g. "de_DE"
 //default_Locale.truncate(default_Locale.lastIndexOf('_')); // e.g. "de"
 m_langPath = ":/languages";
 load_Language(default_Locale);
 recalculateLanguageMenu(default_Locale);
}
void MainWindow::recalculateLanguageMenu(QString default_Locale)
{
 ui->menuLanguage->clear();
 QActionGroup* lang_Group = new QActionGroup(ui->menuLanguage);
 lang_Group->setExclusive(true);
 connect(lang_Group,SIGNAL(triggered(QAction *)),this,SLOT(slot_Language_Changed(QAction *)));

 QDir dir(m_langPath);
 dir = QDir(m_langPath);
 QStringList fileNames = dir.entryList(QStringList("loconetmonitor_*.qm"));
 for (int i = 0; i<fileNames.size(); ++i)
 {
  // get locale extracted by filename
  QString s_locale;
  s_locale = fileNames[i];                  // "TranslationExample_de.qm"
  s_locale.truncate(s_locale.lastIndexOf('.'));   // "TranslationExample_de"
  s_locale.remove(0,s_locale.lastIndexOf('_') + 1);   // "de"
  QString lang = QLocale::languageToString(QLocale(s_locale).language());
  QAction *action = new QAction(tr(lang.toLatin1().data()),this);
  action->setCheckable(true);
  action->setData(s_locale);
  ui->menuLanguage->addAction(action);
  lang_Group->addAction(action);
  // set default translators and language checked
  if (default_Locale == s_locale)
  {
   action->setChecked(true);
  }
 }
}
// Called every time,when a menu entry of the language menu is called
void MainWindow::slot_Language_Changed(QAction* action)
{
 if (0 != action)
 {
  // load the language dependant on the action content
  load_Language(action->data().toString());
  //setWindowIcon(action->icon());
  language::loadLanguage(action->data().toString()); // libPr3
  emit retranslateControls();
 }
}
void MainWindow::switch_Translator(QTranslator& this_translator,const QString& s_filename,QString s_icon_Name)
{
 Q_UNUSED(s_icon_Name)
// remove the old translator
 qApp->removeTranslator(&this_translator);
// load the new translator
 QString s_path =  ":/languages/";
 if(s_filename.startsWith("qt_"))
  s_path = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
 if (this_translator.load(s_filename, s_path))
 {
  qApp->installTranslator(&this_translator);
 }
 else
  qDebug()<<QString("-E-> MainWindow::switch_Translator: load failed for [%1]").arg(s_path+s_filename);

}
void MainWindow::load_Language(const QString& s_Language)
{
 if (m_currLang != s_Language)
 {
  m_currLang = default_Locale = s_Language;
  QLocale this_locale = QLocale(m_currLang);
  QLocale::setDefault(this_locale);
  QString s_language_Name = QLocale::languageToString(this_locale.language());
  switch_Translator(m_translator,QString("loconetmonitor_%1.qm").arg(s_Language),QString("%1.png").arg(s_Language));
  switch_Translator(m_translatorQt,QString("qt_%1.qm").arg(s_Language));
  ui->statusbar->showMessage(tr("Current Language changed to %1").arg(s_language_Name));
 }
}
void MainWindow::changeEvent(QEvent* event)
{
 if (event != 0)
 {
  switch(event->type())
  {
   // this event is sent if a translator is loaded
  case QEvent::LanguageChange:
   ui->retranslateUi(this);
   retranslate_Menus();
   recalculateLanguageMenu(m_currLang);
   foreach(LocoIODialog* dlg, moduleDlg)
    dlg->retranslate_Controls();
   break;
    // this event is send,if the system,language changes
  case QEvent::LocaleChange:
   {
    QString s_locale = QLocale::system().name();
    s_locale.truncate(s_locale.lastIndexOf('_'));
    load_Language(s_locale);
   }
   break;
  default:
   break;
  }
 }
 QMainWindow::changeEvent(event);
}
void MainWindow::retranslate_Menus()
{
 ui->retranslateUi(this);
}
#ifdef HAVE_FTDI
void MainWindow::OnRfidRcvd(ftdiMsg * msg) // [slot]
{

// if(sql == NULL)
// {
//  sql = new Sql(data, this);
// }
// if(!sql->rfidPortExists(msg->serial))
// {
//  sql->updateRfidPort(msg->serial, -1, "not defined");
// }
 AbstractReporter* r = rfidReporterManager->getBySystemName("FR"+msg->serial);
 IdTag* tag = rfidTagManager->getBySystemName("ID"+msg->rfid);
 if(tag == NULL)
 tag = rfidTagManager->newIdTag("ID"+msg->rfid, msg->rfid);
 ((RfidReporter*)r)->notify(tag);
}
#endif
void MainWindow::on_actionLocoNet_Message_triggered()
{
 LocoNetMsgDialog dlg;
// if(dlg.exec() == QDialog::Accepted)
//  locoBufferAdapter->packetizer()->sendLocoNetMessage(dlg.locoNetMessage());
}
void MainWindow::on_actionObject_View_triggered()
{
 ObjectViewerDialog dlg;
 QList<ItemData>* list = new QList<ItemData>();
 if(loconetTurnoutManager == NULL)
  return;
 QHash<QString, NamedBean*>* turnoutList = loconetTurnoutManager->getSystemNameHash();
 QHashIterator<QString, NamedBean*> it(*turnoutList);
 while(it.hasNext())
 {
  it.next();
  ItemData itemData;
  itemData.systemName = it.key();
  itemData.type = "Turnout";
  itemData.userName = it.value()->getUserName();
  itemData.comment = it.value()->getComment();
  list->append(itemData);
 }
 QHash<QString, NamedBean*>* sensorList = loconetSensorManager->getSystemNameHash();
 QHashIterator<QString, NamedBean*> is(*sensorList);
 while(is.hasNext())
 {
  is.next();
  ItemData itemData;
  itemData.systemName = is.key();
  itemData.type = "Sensor";
  itemData.userName = is.value()->getUserName();
  itemData.comment = is.value()->getComment();
  list->append(itemData);
 }
 QHash<QString, NamedBean*>* reporterList = connectionMemo->getReporterManager()->getSystemNameHash();
 QHashIterator<QString, NamedBean*> ir(*reporterList);
 while(is.hasNext())
 {
  ir.next();
  ItemData itemData;
  itemData.systemName = ir.key();
  itemData.type = "Reporter";
  itemData.userName = ir.value()->getUserName();
  itemData.comment = ir.value()->getComment();
  list->append(itemData);
 }
 dlg.setData(list);
 dlg.exec();
}
void MainWindow::on_actionLayout_Editor_triggered()
{
 QString name = "My Layout";
 setCursor(Qt::WaitCursor);
 qApp->processEvents();
 if(editor == NULL)
 {
  if(!PanelMenu::instance()->isPanelNameUsed(name))
   editor = new LayoutEditor(connectionMemo, name, false, this);
  else
   editor = (LayoutEditor*)PanelMenu::instance()->getEditorByName(name);
 }
 editor->show();
 setCursor(Qt::ArrowCursor);
}
void MainWindow::on_actionTables_triggered()
{
 if(libTables == NULL)
  libTables = new LibTables();
 libTables->show();
}
void MainWindow::on_actionPanel_Editor_triggered()
{
 if(!PanelMenu::instance()->isPanelNameUsed("My Layout") && editor == NULL)
 {
  setCursor(Qt::WaitCursor);
  editor = new LayoutEditor(connectionMemo, "My Layout", false, this);
  setCursor(Qt::ArrowCursor);
 }
 AddPanelEditorDialog* dlg = new AddPanelEditorDialog(this);
 dlg->show();
}
void MainWindow::on_actionControl_Panel_Editor_triggered()
{
 if(frame == NULL)
 {
    frame = new ControlPanelEditor(tr("Control Panel Editor"));
    PanelMenu::instance()->addEditorPanel(frame);
    frame->setLocation(20,20);
    frame->setTitle();
    frame->initView();

    frame->pack();
 }
 frame->show();
}

void MainWindow::on_actionNew_Throttle_triggered()
{
// ThrottleWindow* throttleWindow = new ThrottleWindow(/*connectionMemo,*/this);
// throttleWindow->show();
 ThrottleWindow* throttleWindow = ThrottleFrameManager::instance()->createThrottleWindow();
 throttleWindow->show();
}
void MainWindow::on_actionThrottle_Windows_triggered()
{
 ListThrottles* tw = NULL;
// QList<Editor*>* list = PanelMenu::instance()->getEditorPanelList();
// foreach (Editor* panel, *list)
// {
//  QString cName = panel->metaObject()->className();
//  if( cName == "ListThrottles")
//  {
//   tw = (ListThrottles*)panel;
//   break;
//  }
// }
 tw = ThrottleFrameManager::instance()->getThrottlesListPanel();
 if(tw == NULL)
  tw = new ListThrottles(/*connectionMemo,*/ this);
 tw->show();
}
//void MainWindow::on_menuWindow_aboutToShow()
//{
// ui->menuWindow->clear();
// PanelMenu::instance()->updatePanelMenu(ui->menuWindow);
//}
//void MainWindow::on_actionRoster_triggered()
//{
// RosterFrame* rosterTable = new RosterFrame(connectionMemo,this);
// rosterTable->show();
//}

void MainWindow::on_actionSlot_monitor_triggered()
{

 if(slotMonitor == NULL)
  slotMonitor = new SlotMonitor(connectionMemo, this);
 slotMonitor->show();
}
void MainWindow::on_actionAuto_scroll_to_bottom_triggered(bool bChecked)
{
 bAutoScrollToBottom = bChecked;
}

void MainWindow::openRfid()
{
#ifdef HAVE_FTDI
 rfidSensorManager = NULL;
 rfidReporterManager=NULL;
 rfidTagManager = NULL;
 libTables = NULL;
 slotMonitor = NULL;
 bAutoScrollToBottom = true;

 ftdilib = new Ftdilib();
 if(ftdilib->availPorts.count() > 0)
 {

  rfidSensorManager = (RfidSensorManager*)InstanceManager::getDefault("RfidSensorManager");
  ProxySensorManager* mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
  mgr->addManager(rfidSensorManager);

  rfidReporterManager =(RfidReporterManager*)InstanceManager::getDefault("RfidReporterManager");
  ProxyReporterManager* rMgr = (ProxyReporterManager*)InstanceManager::reporterManagerInstance();
  rMgr->addManager(rfidReporterManager);
  rfidTagManager = (DefaultIdTagManager*)InstanceManager::getDefault("DefaultIdTagManager");

  int rfidSensor = 1;
  foreach(QString serial, ftdilib->availPorts)
  {
   ftdilib->openPort(serial);
   Sensor* sensor = rfidSensorManager->newSensor(rfidSensorManager->getSystemPrefix()+"S"+QString::number(rfidSensor), serial);
   Q_UNUSED(sensor);
   AbstractReporter* reporter = rfidReporterManager->newReporter("FR"+serial, serial);
   Q_UNUSED(reporter);
  }
  connect(ftdilib, SIGNAL(rfidMsg(ftdiMsg*)), this, SLOT(OnRfidRcvd(ftdiMsg*)));
 }
#else
 rfidPort = new RfidUsb((QWidget*)parent());
 if(rfidPort->availPorts.count()> 0)
 {
  QSerialPortInfo info = rfidPort->availPorts.at(0);
  rfidPort->openPort(info.portName());
 }
 else
 {
#ifdef WIN32
 rfidPort->openPort("com17");
#else
 rfidPort->openPort("ttyUSB0");
#endif
 }
#endif

}
void MainWindow::on_actionSetup_Fast_Clock_triggered()
{
 SimpleClockFrame* f = new SimpleClockFrame();
//    try {
 f->initComponents();
//    } catch (Exception E) {
//        log.error("Exception in Simple Clock: "+e);
//    }
 f->setVisible(true);
}
void MainWindow::on_actionNixie_Clock_triggered()
{
    NixieClockFrame* f = new NixieClockFrame();
    f->setVisible(true);
}
void MainWindow::on_actionLCD_Clock_triggered()
{
    LcdClockFrame* f = new LcdClockFrame();
    f->setVisible(true);
}
void MainWindow::on_actionAnalog_Clock_triggered()
{
    AnalogClockFrame* f = new AnalogClockFrame();
    f->setVisible(true);
}
void MainWindow::on_actionPower_Control_triggered()
{
 PowerPanelFrame* frame = new PowerPanelFrame();
 frame->initComponents();
 frame->pack();
 frame->show();
}
void MainWindow::on_actionTurnouts_triggered()
{
 SimpleTurnoutCtrlFrame* dlg = new SimpleTurnoutCtrlFrame();
    dlg->show();
}
void MainWindow::on_actionMonitor_triggered()
{
 ifc->show(locoMonPane,NULL);
}
void MainWindow::on_actionService_Mode_Programmer_Programmer_track_triggered()
{
 if (log->isDebugEnabled()) log->debug("Pane programmer requested");

 if(f==NULL)
 {
  // create the initial frame that steers
  f = new JmriJFrame("Create New Loco"); //tr("FrameServiceProgrammerSetup")
  //f.getContentPane().setLayout(new BorderLayout());
  QWidget* contentPane = new QWidget;
  QVBoxLayout* contentPaneLayout = new QVBoxLayout();
  contentPane->setLayout(contentPaneLayout);
  f->setCentralWidget(contentPane);
//    // ensure status line is cleared on close so it is normal if re-opened
//    f.addWindowListener(new WindowAdapter(){
//        @Override
//        public void windowClosing(WindowEvent we){
//            statusLabel.setText(tr("StateIdle"));
//            f.windowClosing(we);}});

  // add the Roster menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* j = new QMenu(tr("File"));
//  j.add(new jmri.jmrit.decoderdefn.PrintDecoderListAction(tr("MenuPrintDecoderDefinitions"), f, false));
//  j.add(new jmri.jmrit.decoderdefn.PrintDecoderListAction(tr("MenuPrintPreviewDecoderDefinitions"), f, true));
  menuBar->addMenu(j);
  menuBar->addMenu(new RosterMenu(tr("Roster"), RosterMenu::MAINMENU, f));
  QVBoxLayout* bottomPanelLayout;
  f->setMenuBar(menuBar);
  /*final*/ QWidget* bottomPanel = /*new JPanel(new BorderLayout());*/ new QWidget;
  bottomPanel->setLayout(bottomPanelLayout = new QVBoxLayout);
  // new Loco on programming track
  combinedLocoSelTree = new CombinedLocoSelTreePane(statusLabel);
  // load primary frame
  QWidget* topPanel = new QWidget();
  QVBoxLayout* topPanelLayout = new QVBoxLayout;
  topPanel->setLayout(topPanelLayout);
  topPanelLayout->addWidget(modePane);
//  topPanelLayout->addSpacerItem(new JSeparator(javax.swing.SwingConstants.HORIZONTAL));
  contentPaneLayout->addWidget(topPanel, Qt::AlignTop);
      //f.getContentPane().add(modePane);
      //f.getContentPane().add(new JSeparator(javax.swing.SwingConstants.HORIZONTAL));

  //    combinedLocoSelTree.setAlignmentX(JLabel.CENTER_ALIGNMENT);
  contentPaneLayout->addWidget(combinedLocoSelTree, Qt::AlignCenter);

  //f.getContentPane().add(new JSeparator(javax.swing.SwingConstants.HORIZONTAL));
  //basicRoster.setEnabled(false);
  statusLabel->setAlignment(Qt::AlignHCenter);
  bottomPanelLayout->addWidget(statusLabel, Qt::AlignBottom);
  contentPaneLayout->addWidget(bottomPanel, Qt::AlignBottom);

  f->pack();
  if (log->isDebugEnabled()) log->debug("Tab-Programmer setup created");
 }
 else
 {
  combinedLocoSelTree->resetSelections();
 }
 f->setVisible(true);
}

void MainWindow::on_actionTest_glass_pane_triggered()
{
 QList<QWidget*> components;
 QList<QRect> rects;
 BusyGlassPane* pane = new BusyGlassPane(components, rects, centralWidget(), this);
 pane->setVisible(true);
}
//void MainWindow::on_actionConfigure_Command_Station_triggered()
//{
//  JmriJFrame* f = new JmriJFrame(tr("Configure Command Station"));
//    //f.getContentPane().setLayout(new BorderLayout());
//  QWidget* contentPane = new QWidget;
//  QVBoxLayout* contentPaneLayout = new QVBoxLayout();
//  contentPane->setLayout(contentPaneLayout);
//  f->setCentralWidget(contentPane);
//  CmdStnConfigPane* pane = new CmdStnConfigPane;
//  contentPaneLayout->addWidget(pane);
//  pane->initComponents(connectionMemo);
//  f->addHelpMenu(pane->getHelpTarget(),true);
//  f->pack();
//  f->setVisible(true);
//}
void MainWindow::on_actionPreferences_triggered()
{
 PreferencesPane* preferencesPane = new PreferencesPane;
}
//void MainWindow::on_actionConnection_Config_triggered()
//{
// if(configFrame == NULL)
// {
//  configFrame = new ConnectionConfigFrame();
//  configFrame->pack();
// }
// configFrame->setVisible(true);
//}
//The connection process is placed into its own thread so that it doens't hog the swingthread while waiting for the connections to open.
// /*protected*/ class Connect : public Runnable {
Connect::Connect(MainWindow* parent)
{
 this->parent = parent;
 setObjectName("Connect");
}

/*public*/ void Connect::run()
{
//    Cursor hourglassCursor = new Cursor(Cursor.WAIT_CURSOR);
//    parent.setCursor(hourglassCursor);
 QObject* connect = JmrixConfigPane::instance(0)->getCurrentObject();
 InstanceManager::configureManagerInstance()->registerPref(connect);
 //if(connect instanceof jmri.jmrix.AbstractConnectionConfig)
 if(qobject_cast<AbstractConnectionConfig*>(connect) != NULL)
 {
  ((AbstractConnectionConfig*)connect)->updateAdapter();
  PortAdapter* adp = ((AbstractConnectionConfig*)connect)->getAdapter();
  try
  {
   adp->_connect();
   adp->configure();
  }
  catch (Exception ex)
  {
   //Logger::error(ex.getLocalizedMessage(), ex);
//   Cursor normalCursor = new Cursor(Cursor.DEFAULT_CURSOR);
//   parent.setCursor(normalCursor);
  // JOptionPane.showMessageDialog(null, "An error occured while trying to connect to " + ((jmri.jmrix.AbstractConnectionConfig)connect).getConnectionName() + ", press the back button and check the connection details","Error Opening Connection" , JOptionPane.ERROR_MESSAGE);
   return;
  }
 }
 RosterEntry::setDefaultOwner(parent->owner->text());
 InstanceManager::tabbedPreferencesInstance()->init();
 InstanceManager::tabbedPreferencesInstance()->saveContents();
 /*We have to double register the connection as when the saveContents is called is removes the original pref and
    replaces it with the jmrixconfigpane, which is not picked up by the DP3 window*/
 InstanceManager::configureManagerInstance()->registerPref(connect);
 //dispose();
}
//};
//void MainWindow::on_actionConnect_triggered()
//{
// Connect* connection = new Connect(this);
// connection->start();
//}
