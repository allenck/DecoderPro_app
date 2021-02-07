#include "throttlewindow.h"
#include "ui_throttlewindow.h"
#include "lnthrottlemanager.h"
#include "loconetthrottle.h"
#include "lnthrottlemanager.h"
#include "../Roster/roster.h"
#include "../Roster/rosterentry.h"
#include <QSettings>
//#include "listthrottles.h"
#include "panelmenu.h"
#include "editor.h"
#include "instancemanager.h"
#include "lnpowermanager.h"
#include "throttleframemanager.h"
#include "addresspanel.h"
#include "throttleframepropertyeditor.h"
#include "throttlespreferencesaction.h"
#include <QMenu>
#include <QMenuBar>
#include "throttleframemanager.h"
#include "throttlespreferences.h"
#include "throttlecreationaction.h"
#include "smallpowermanagerbutton.h"
#include "controlpanel.h"
#include "warrantframe.h"
#include "functionpanel.h"
#include "loconetsystemconnectionmemo.h"
#include "throttleslistpanel.h"
#include "throttlestablemodel.h"
#include "withrottlecreationaction.h"
#include "xmlfile.h"
#include "jfilechooser.h"
#include "storexmlconfigaction.h"
#include "windowpreferences.h"
#include "fileutil.h"
#include "loadxmlconfigaction.h"
#include "largepowermanagerbutton.h"
#include <QPalette>
#include "loadxmlthrottleslayoutaction.h"
#include "loaddefaultxmlthrottleslayoutaction.h"
#include "storexmlthrottleslayoutaction.h"
#include "storedefaultxmlthrottleslayoutaction.h"
#ifdef SCRIPTING_ENABLED
#include "jynstrument.h"
#endif
#include "joptionpane.h"

ThrottleWindow::ThrottleWindow(/*LocoNetSystemConnectionMemo* memo,*/ QWidget *parent) :
    JmriJFrame(parent),
    ui(new Ui::ThrottleWindow)
{
 ui->setupUi(this);
 this->parent = parent;
 log = new Logger("ThrottleWindow");
 addressPanel = new AddressPanel(this);
 addressPanel->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea);
 this->addDockWidget(static_cast<Qt::DockWidgetArea>(Qt::RightDockWidgetArea ), addressPanel,Qt::Horizontal);
 connect(this, SIGNAL(throttleWindowupdate(PropertyChangeEvent*)), addressPanel, SLOT(propertyChange(PropertyChangeEvent*)));

 controlPanel = new ControlPanel(this);
 controlPanel->setObjectName(QString::fromUtf8("controlPanel"));
 controlPanel->setWindowTitle(tr("Control Panel"));
 controlPanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
 this->addDockWidget(static_cast<Qt::DockWidgetArea>(Qt::LeftDockWidgetArea), controlPanel);
 connect(this, SIGNAL(throttleWindowupdate(PropertyChangeEvent*)), controlPanel, SLOT(propertyChange(PropertyChangeEvent*)));

 functionPanel = new FunctionPanel(this);
 functionPanel->setAllowedAreas(Qt::TopDockWidgetArea | Qt::RightDockWidgetArea);
 this->addDockWidget(static_cast<Qt::DockWidgetArea>(Qt::TopDockWidgetArea), functionPanel);
 connect(this, SIGNAL(throttleWindowupdate(PropertyChangeEvent*)), functionPanel, SLOT(propertyChange(PropertyChangeEvent*)));

 speedPanel = new SpeedPanel(this);
 speedPanel->setAllowedAreas(Qt::AllDockWidgetAreas);
 this->addDockWidget(static_cast<Qt::DockWidgetArea>(Qt::BottomDockWidgetArea), speedPanel);

 setWindowTitle(tr("Unassigned"));
 listViewDlg = NULL;
 throttle = NULL;
 rosterEntry = NULL;
 cardCounterID = 0; // to generate unique names for each card
 cardCounterNB = 1; // real counter
 willSwitch = false;
 titleTextType = "rosterID";
 BACKPANEL_LAYER = 0x80000000;

 getSettings();
 throttleFrames = new QMap<QString, ThrottleWindow*>(/*5*/);
 currentThrottleFrame = this;
 throttleFrames->insert("default",getCurrentThrottleFrame());
 mgr = (LnThrottleManager*)InstanceManager::throttleManagerInstance();
 addThrottle = new QAction(QIcon(":/resources/icons/throttles/add.png"),tr("Add Throttle"),this);
 ui->toolBar->addAction(addThrottle);
 connect(addThrottle, SIGNAL(triggered()), this, SLOT(on_actionNew_Throttle_triggered()));
 removeThrottle = new QAction(QIcon(":/resources/icons/throttles/remove.png"), tr("remove throttle"), this);
 removeThrottle->setDisabled(true);
 connect(removeThrottle, SIGNAL(triggered()), this, SLOT(removeThrottleFrame()));
 ui->toolBar->addAction(removeThrottle);
 ui->toolBar->addSeparator();
 previousRunning = new QAction(QIcon(":/resources/icons/throttles/previous-jump.png"), tr("Previous runninglocomotive"), this);
 ui->toolBar->addAction(previousRunning);
 previousRunning->setEnabled(true);
 previous = new QAction(QIcon(":/resources/icons/throttles/previous.png"), tr("Previous throttle"), this);
 ui->toolBar->addAction(previous);
 previous->setEnabled(true);
 next = new QAction(QIcon(":/resources/icons/throttles/next.png"), tr("Next Throttle"), this);
 ui->toolBar->addAction(next);
 next->setEnabled(true);
 nextRunning = new QAction(QIcon(":/resources/icons/throttles/next-jump.png"), tr("Next running Locomotive"), this);
 ui->toolBar->addAction(nextRunning);
 nextRunning->setEnabled(true);
 ui->toolBar->addSeparator();
 emergencyStop = new QAction(QIcon(":/resources/icons/throttles/estop.png"), tr("Emergency stop"), this);
 connect(emergencyStop, SIGNAL(triggered()), this, SLOT(on_emergencyStop_clicked()));
 ui->toolBar->addAction(emergencyStop);
 powerMgr = (PowerManager*)InstanceManager::getDefault("PowerManager");
 ui->toolBar->addWidget(new LargePowerManagerButton());
 ui->toolBar->addSeparator();
 editView = new QAction(QIcon(":/resources/icons/throttles/edit-view.png"),tr("Edit view"),this);
 ui->toolBar->addAction(editView);
 listViewAct = new QAction(QIcon(":/resources/icons/throttles/list.png"),tr("List manage throttles"),this);
 listViewAct->setToolTip("View Local Throttles table");
 ui->toolBar->addAction(listViewAct);
 throttleToolBar = ui->toolBar;
 connect(listViewAct, SIGNAL(triggered()), this, SLOT(on_listView_clicked()));
 //PanelMenu::instance()->addEditorPanel((Editor*)this);
 ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->addEditorPanel((Editor*)this);
 //connect(ui->menuWindow, SIGNAL(aboutToShow()), this, SLOT(on_menuWindow_aboutToShow()));
 bAltFunc = false;
 addressPanel->addAddressListener((AddressListener*)controlPanel);
 addressPanel->addAddressListener((AddressListener*)functionPanel);
 addressPanel->addAddressListener((AddressListener*)speedPanel);
 addressPanel->addAddressListener((AddressListener*)this);
 //addressPanel->addAddressListener((AddressListener*)((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesListPanel()->getTableModel());
 functionPanel->setAddressPanel(addressPanel);
 functionPanel->setEnabled(false);
 controlPanel->setAddressPanel(addressPanel);
 speedPanel->setAddressPanel(addressPanel);


#if 1
 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle())
 {
  /*         if ( InstanceManager.getDefault(ThrottleFrameManager.class).getThrottlesPreferences().isUsingTransparentCtl() ) {
              setTransparent(functionPanel);
              setTransparent(addressPanel);
              setTransparent(controlPanel);
              }*/
  if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingRosterImage())
  {
//   backgroundPanel = new BackgroundPanel();
//   backgroundPanel->setAddressPanel(addressPanel); // reusing same way to do it than existing thing in functionPanel
//   //   addComponentListener(backgroundPanel); // backgroudPanel warned when desktop resized
//   addressPanel->addAddressListener((AddressListener*)backgroundPanel);
//   addressPanel->setBackgroundPanel(backgroundPanel); // so that it's changeable when browsing through rosters
//   //add(backgroundPanel, BACKPANEL_LAYER);
//   ui->formLayout_2->addWidget(backgroundPanel);
   if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingRosterImage())
   {
    if(rosterEntry != NULL && rosterEntry->getImagePath() != "")
    {
     QPixmap bkgnd(rosterEntry->getImagePath());
     if (!((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isResizingWindow())
      bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatio);
     else
      bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
     QPalette palette;
     palette.setBrush(QPalette::Background, bkgnd);
     this->setPalette(palette);
    }
   }
  }
//  addComponentListener(this); // to force sub windows repositionning
 }
#endif
 initializeMenu();

 ThrottleFrameManager::instance()->getThrottlesListPanel()->getTableModel()->addThrottleFrame(this);
}

ThrottleWindow::~ThrottleWindow()
{
    delete ui;
    dispose();
}
/**
 *  Set up View, Edit and Power Menus
 */
/*private*/ void ThrottleWindow::initializeMenu()
{
 QMenu* fileMenu = new QMenu(tr("File"));

 QAction* fileMenuLoad = new QAction(tr("Open Throttle"),this);
//    fileMenuLoad.addActionListener(new AbstractAction() {

//        public void actionPerformed(ActionEvent e) {
//            getCurrentThrottleFrame().loadThrottle(NULL);
//        }
//    });
 connect(fileMenuLoad, SIGNAL(triggered()), this, SLOT(OnFileMenuLoad()));
 fileMenuSave = new QAction(tr("Save Current Throttle"),this);
//    fileMenuSave.addActionListener(new AbstractAction() {

//        public void actionPerformed(ActionEvent e) {
//            getCurrentThrottleFrame().saveThrottle();
//        }
//    });
 connect(fileMenuSave, SIGNAL(triggered()), this, SLOT(saveThrottle()));
 QAction* fileMenuSaveAs = new QAction(tr("Save Current Throttle As..."),this);
//    fileMenuSaveAs.addActionListener(new AbstractAction() {

//        public void actionPerformed(ActionEvent e) {
//            getCurrentThrottleFrame().saveThrottleAs();
//        }
//    });
 connect(fileMenuSaveAs, SIGNAL(triggered()), this, SLOT(saveThrottleAs()));

 fileMenu->addAction(new ThrottleCreationAction(tr("New Throttle..."),(WindowInterface*)this));
 fileMenu->addAction(fileMenuLoad);
 fileMenu->addAction(fileMenuSave);
 fileMenu->addAction(fileMenuSaveAs);
 fileMenu->addSeparator();
 fileMenu->addAction(new LoadXmlThrottlesLayoutAction(tr("Open Throttles Layout..."),this));
 fileMenu->addAction(new StoreXmlThrottlesLayoutAction(tr("Save Throttles Layout..." ),this));
 fileMenu->addSeparator();
 fileMenu->addAction(new LoadDefaultXmlThrottlesLayoutAction(tr("Load Default Throttles Layout" ),this));
 fileMenu->addAction(new StoreDefaultXmlThrottlesLayoutAction(tr("Save As Default Throttles Layout" ),this));
 fileMenu->addSeparator();
 fileMenu->addAction(new WiThrottleCreationAction(tr("Start WiThrottle"),this));

 QMenu* viewMenu = new QMenu(tr("View"));
 viewAddressPanel = new QAction(tr("Address Panel"),this);
 viewAddressPanel->setCheckable(true);
 viewAddressPanel->setChecked(true);
//    viewAddressPanel.addItemListener(new ItemListener() {

//        public void itemStateChanged(ItemEvent e) {
//            getCurrentThrottleFrame().getAddressPanel().setVisible(e.getStateChange() == ItemEvent.SELECTED);
//        }
//    });
 connect(viewAddressPanel,SIGNAL(toggled(bool)), this, SLOT(on_actionAddress_Panel_toggled(bool)));

 viewControlPanel = new QAction(tr("Control Panel"),this);
 viewControlPanel->setCheckable(true);
 viewControlPanel->setChecked(true);
//    viewControlPanel.addItemListener(new ItemListener() {

//        public void itemStateChanged(ItemEvent e) {
//            getCurrentThrottleFrame().getControlPanel().setVisible(e.getStateChange() == ItemEvent.SELECTED);
//        }
//    });
 connect(viewControlPanel, SIGNAL(toggled(bool)), this, SLOT(on_actionControl_Panel_toggled(bool)));
 viewFunctionPanel = new QAction(tr("Function Panel"),this);
 viewFunctionPanel->setCheckable(true);
 viewFunctionPanel->setChecked(true);
//    viewFunctionPanel.addItemListener(new ItemListener() {

//        public void itemStateChanged(ItemEvent e) {
//            getCurrentThrottleFrame().getFunctionPanel().setVisible(e.getStateChange() == ItemEvent.SELECTED);
//        }
//    });
 connect(viewFunctionPanel, SIGNAL(toggled(bool)), this, SLOT(on_actionFunction_Panel_toggled(bool)));

 viewSpeedPanel = new QAction(tr("Speed Panel"),this);
 viewSpeedPanel->setCheckable(true);
 viewSpeedPanel->setChecked(true);
//    viewFunctionPanel.addItemListener(new ItemListener() {

//        public void itemStateChanged(ItemEvent e) {
//            getCurrentThrottleFrame().getFunctionPanel().setVisible(e.getStateChange() == ItemEvent.SELECTED);
//        }
//    });
 connect(viewSpeedPanel, SIGNAL(toggled(bool)), this, SLOT(on_actionSpeed_Panel_toggled(bool)));


 viewAllButtons = new QAction(tr("Reset function buttons"),this);
//    viewAllButtons.addActionListener(new AbstractAction() {

//        public void actionPerformed(ActionEvent ev) {
//            getCurrentThrottleFrame().getFunctionPanel().resetFnButtons();
//            getCurrentThrottleFrame().getFunctionPanel().setEnabled();
//        }
//    });

 QAction* makeAllComponentsInBounds = new QAction(tr("Get all current throttle components in bounds"),this);
//    makeAllComponentsInBounds.addActionListener(new AbstractAction() {

//        public void actionPerformed(ActionEvent ev) {
//            getCurrentThrottleFrame().makeAllComponentsInBounds();
//        }
//    });

 QAction* switchViewMode = new QAction(tr("Switch throttle frame view mode"),this);
//    switchViewMode.addActionListener(new AbstractAction() {

//        public void actionPerformed(ActionEvent ev) {
//            switchMode();
//        }
//    });
 connect(switchViewMode, SIGNAL(triggered()), this, SLOT(switchMode()));
 QAction* viewThrottlesList = new QAction(tr("Show/Hide throttles list window"),this);
 //viewThrottlesList.addActionListener(new ThrottlesListAction());

 viewMenu->addAction(viewAddressPanel);
 viewMenu->addAction(viewControlPanel);
 viewMenu->addAction(viewFunctionPanel);
 viewMenu->addAction(viewSpeedPanel);
 viewMenu->addSeparator();
 viewMenu->addAction(viewAllButtons);
 viewMenu->addAction(makeAllComponentsInBounds);
 viewMenu->addSeparator();
 viewMenu->addAction(switchViewMode);
 viewMenu->addAction(viewThrottlesList);

 connect(viewThrottlesList, SIGNAL(triggered(bool)), this, SLOT(on_listView_clicked()));
 QMenu* editMenu = new QMenu(tr("Edit"));
 QAction* preferencesItem = new QAction(tr("Frame properties"),this);
 editMenu->addAction(preferencesItem);
//    preferencesItem.addActionListener(new ActionListener() {

//        public void actionPerformed(ActionEvent e) {
//            editPreferences();
//        }
//    });
 connect(preferencesItem, SIGNAL(triggered()), this, SLOT(editPreferences()));
 editMenuExportRoster = new QAction(tr("Export current throttle customization to roster"),this);
 editMenu->addAction(editMenuExportRoster);
//    editMenuExportRoster.addActionListener(new ActionListener() {

//        public void actionPerformed(ActionEvent e) {
 connect(editMenuExportRoster, &QAction::triggered, [=]{
   getCurrentThrottleFrame()->saveRosterChanges();
//        }
 });
 editMenu->addSeparator();
 editMenu->addAction(new ThrottlesPreferencesAction(tr("Throttles Preferences"),this)); // now in tabbed preferences

 if(this->menuBar() == nullptr)
  this->setMenuBar(new QMenuBar());
 else
  this->menuBar()->clear();
 this->menuBar()->addMenu(fileMenu);
 this->menuBar()->addMenu(editMenu);
 this->menuBar()->addMenu(viewMenu);

 if (powerMgr != nullptr)
 {
  QMenu* powerMenu = new QMenu(tr("Power"));
  QAction* powerOn = new QAction(tr("Power on"), this);
  powerMenu->addAction(powerOn);
  //powerOn.addActionListener(new ActionListener() {

  //    public void actionPerformed(ActionEvent e) {
  //        try {
  //            powerMgr.setPower(PowerManager.ON);
  //        } catch (JmriException e1) {
  //            log.error("Error when setting power " + e1);
  //        }
  //    }
  //});
  connect(powerOn, SIGNAL(triggered()), this, SLOT(on_actionPower_On_triggered()));

  QAction* powerOff = new QAction (tr("Power off"),this);
  powerMenu->addAction(powerOff);
  //powerOff.addActionListener(new ActionListener() {

  //    public void actionPerformed(ActionEvent e) {
  //        try {
  //            powerMgr.setPower(PowerManager.OFF);
  //        } catch (JmriException e1) {
  //            log.error("Error when setting power " + e1);
  //        }
  //    }
  //});
  connect(powerOn, SIGNAL(triggered()), this, SLOT(on_actionPower_On_triggered()));

  this->menuBar()->addMenu(powerMenu);

  if ((!ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingExThrottle())
        || (!ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingToolBar()))
  {
//    this->menuBar()->addAction(new SmallPowerManagerButton(this));
  }
 }

 // add help selection
 addHelpMenu("package.jmri.jmrit.throttle.ThrottleFrame", true);
}

//void ThrottleWindow::on_newThrottle_clicked() // not used?
//{

//}
//void ThrottleWindow::on_removeThrottle_clicked() // not used?
//{

//}
void ThrottleWindow::on_emergencyStop_clicked()
{
 LocoNetMessage* msg = new LocoNetMessage(2);
 msg->setOpCode(LnConstants::OPC_IDLE);
 ((LocoNetSystemConnectionMemo*)InstanceManager::getDefault("LocoNetSystemConnectionMemo"))->getLnTrafficController()->sendLocoNetMessage(msg);
}
#if 0
void ThrottleWindow::on_togglePower_clicked()
{
 //LnPowerManager* pmgr = memo->getPowerManager();
 if(powerMgr->isPowerOn())
  powerMgr->setPower(PowerManager::OFF);
 else
  powerMgr->setPower(PowerManager::ON);
}
#endif
void ThrottleWindow::on_actionPower_On_triggered()
{
 //LnPowerManager* pmgr = memo->getPowerManager();
 powerMgr->setPower(PowerManager::ON);
}
void ThrottleWindow::on_actionPower_Off_triggered()
{
 //LnPowerManager* pmgr = memo->getPowerManager();
 powerMgr->setPower(PowerManager::OFF);
}

void ThrottleWindow::propertyChange(PropertyChangeEvent *e)
{
#if 0
 if(e->getPropertyName() == "Power")
 {
  //LnPowerManager* pmgr = memo->getPowerManager();
  if(powerMgr->isPowerOn())
  {
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_green.png"));
   togglePower->setText(tr("Power on"));
  }
  else if (powerMgr->isPowerOff())
  {
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_red.png"));
   togglePower->setText(tr("Power off"));
  }
  else
  {
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_yellow.png"));
   togglePower->setText( tr("Power unknown"));
  }
 }

 else
#endif
  log->debug(tr("Property change '%1' %2").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
 emit throttleWindowupdate(e);
}

//@Override
/*public*/ void ThrottleWindow::notifyAddressChosen(LocoAddress* /*l*/) {
}

//@Override
/*public*/ void ThrottleWindow::notifyAddressReleased(LocoAddress* /*la*/) {
    setLastUsedSaveFile("");
    setFrameTitle();
    /*throttleWindow.*/updateGUI();
}

void ThrottleWindow::notifyAddressThrottleFound(DccThrottle*t) // SLOT[]
{
 if ((((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle())
         && (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isAutoLoading())
         && (addressPanel != NULL) && (addressPanel->getRosterEntry() != NULL)
         && ((getLastUsedSaveFile() == NULL) || (getLastUsedSaveFile() !=(getDefaultThrottleFolder() + addressPanel->getRosterEntry()->getId().trimmed() + ".xml") ))) {
     loadThrottle(getDefaultThrottleFolder() + addressPanel->getRosterEntry()->getId().trimmed() + ".xml");
 }
 setFrameTitle();
 /*throttleWindow*/ updateGUI();
 notifyThrottleFound(t);
}

void ThrottleWindow::notifyThrottleFound(DccThrottle *t)
{
 this->throttle = (LocoNetThrottle*)t;
 rosterEntry = (RosterEntry*)throttle->getRosterEntry();
 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingRosterImage())
 {
  if(rosterEntry != NULL && rosterEntry->getImagePath() != "")
  {
   QPixmap bkgnd(rosterEntry->getImagePath());
   if (!((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isResizingWindow())
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatio);
   else
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   QPalette palette;
   palette.setBrush(QPalette::Background, bkgnd);
   this->setPalette(palette);
  }
 }
 controlPanel->notifyAddressThrottleFound(t);
 functionPanel->setAddressPanel(addressPanel);
 functionPanel->notifyAddressThrottleFound(t);
 //throttle->addPropertyChangeListener((PropertyChangeListener*)this);
 connect((AbstractThrottle*)throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 //setWindowTitle(((RosterEntry*)throttle->getRosterEntry())->getId());
 setFrameTitle();
 setTitleText(title());

 emit throttleWindowupdate(new PropertyChangeEvent(this, "throttleFound", QVariant(), VPtr<Throttle>::asQVariant(throttle)));
 ThrottleFrameManager::instance()->getThrottlesListPanel()->getTableModel()->notifyAddressThrottleFound(t);
}

void ThrottleWindow::saveSettings()
{
 QSettings settings;
 settings.beginGroup("Throttle");
 settings.setValue("geometry", saveGeometry());
 settings.setValue("windowState",saveState());
// settings.setValue("address", ui->edAddress->text());
// settings.setValue("protocol", LocoAddress::DCC_SHORT);
 settings.endGroup();
}
void ThrottleWindow::getSettings()
{
 QSettings settings;
 settings.beginGroup("Throttle");
 restoreGeometry(settings.value("geometry").toByteArray());
 restoreState(settings.value("windowState").toByteArray());
 settings.endGroup();
}

void ThrottleWindow::closeEvent(QCloseEvent *)
{
 saveSettings();
 dispose();
}
//void ThrottleWindow::on_btnDispatch_clicked()
//{
// mgr->dispatchThrottle((DccThrottle*)throttle, (ThrottleListener*)this);
//}
//void ThrottleWindow::on_btnProgram_clicked()
//{

//}

void ThrottleWindow::notifyChangedSlot(LocoNetSlot * s)
{
 if(throttle->slot == s)
 {

 }
}

void ThrottleWindow::on_listView_clicked()
{
 ThrottleFrameManager::instance()->showThrottlesList();
}

//void ThrottleWindow::on_menuWindow_aboutToShow()
//{
// ui->menuWindow->clear();
// PanelMenu::instance()->updatePanelMenu(ui->menuWindow);
//}
QString ThrottleWindow::getTitle()
{
 return windowTitle();
}

Throttle* ThrottleWindow::getThrottle() {return (Throttle*)throttle;}

void ThrottleWindow::on_actionNew_Throttle_triggered()
{
 ThrottleWindow* newThrottle = ThrottleFrameManager::instance()->createThrottleWindow();
 newThrottle->show();
}
QString ThrottleWindow::id()
{
 if(rosterEntry != NULL) return rosterEntry->getId();
 return "";
}

void ThrottleWindow::on_actionAddress_Panel_toggled(bool bChecked)
{
 addressPanel->setVisible(bChecked);
}
void ThrottleWindow::on_actionControl_Panel_toggled(bool bChecked)
{
 controlPanel->setVisible(bChecked);
}

void ThrottleWindow::on_actionFunction_Panel_toggled(bool bChecked)
{
 functionPanel->setVisible(bChecked);
}

void ThrottleWindow::on_actionSpeed_Panel_toggled(bool bChecked)
{
 speedPanel->setVisible(bChecked);
}
RosterEntry* ThrottleWindow::getRosterEntry() { return rosterEntry;}

void ThrottleWindow::removeThrottleFrame()
{
 //removeThrottleFrame( getCurrentThrottleFrame() );
}

AddressPanel* ThrottleWindow::getAddressPanel() { return addressPanel;}
ControlPanel* ThrottleWindow::getControlPanel() { return controlPanel;}
FunctionPanel* ThrottleWindow::getFunctionPanel() { return functionPanel;}

void ThrottleWindow::OnFileMenuLoad()
{
 //            getCurrentThrottleFrame().loadThrottle(NULL);
 loadThrottle(NULL);
}
/*public*/ void ThrottleWindow::loadThrottle(QString sfile)
{
 if (sfile == "")
 {
  JFileChooser* fileChooser = XmlFile::userFileChooser(tr("Xml files"), "xml");
  fileChooser->setCurrentDirectory(new File(getDefaultThrottleFolder()));
  fileChooser->setDialogType(JFileChooser::OPEN_DIALOG);
  File* file = LoadXmlConfigAction::getFile(fileChooser);
  if (file == NULL) return;
  sfile = file->getAbsolutePath();
  if (sfile == NULL) return;
 }

 bool switchAfter = false;
 if (! isEditMode) {
     switchMode();
     switchAfter = true;
 }
 XmlFile* xf = new XmlFile();   // odd syntax is due to XmlFile being abstract
 File* f=new File(sfile);

 try
 {
  if(!f->exists())
   throw  FileNotFoundException(tr("file %1 not found").arg(sfile));
  if(f->exists())
  {
     QDomElement root = xf->rootFromFile(f);
     QDomElement conf = root.firstChildElement("ThrottleFrame");
     // File looks ok
     setLastUsedSaveFile(sfile);
     // close all existing Jynstruments
#if 0
     Component[] cmps = getComponents();
     for (int i=0; i<cmps.length; i++) {
         try {
             if (cmps[i] instanceof JInternalFrame) {
                 JInternalFrame jyf = (JInternalFrame) cmps[i];
                 Component[] cmps2 = jyf.getContentPane().getComponents();
                 for (int j=0; j<cmps2.length; j++) {
                     if (cmps2[j] instanceof Jynstrument) {
                         ((Jynstrument)cmps2[j]).exit();
                         jyf.dispose();
                     }
                 }
             }
         } catch (Exception ex) {
             log.debug("Got exception (no panic) "+ex);
         }
     }
#endif
     // and finally load all preferences
     setXml(conf);
  }
 }
 catch (FileNotFoundException ex)
 {
//           if (log->isDebugEnabled())
  log->debug("Loading throttle exception: " + ex.getMessage());
 }
 catch (Exception ex) {
     if (log->isDebugEnabled())
         log->debug("Loading throttle exception: " + ex.getMessage());
 }

//    	checkPosition();
 if (switchAfter) {
     switchMode();
 }
 return ;
}

/*private*/ void ThrottleWindow::editPreferences()
{
 ThrottleFramePropertyEditor* editor = new ThrottleFramePropertyEditor();
 editor->setThrottleFrame(this);
 editor->setLocation(this->getLocationOnScreen());
 //editor->setLocationRelativeTo(this);
 editor->setVisible(true);
}
/*public*/ QString ThrottleWindow::getTitleTextType() {
        return titleTextType;
    }

/*public*/ QString ThrottleWindow::getTitleText() {
    return titleText;
}

/*public*/ void ThrottleWindow::setTitleText(QString titleText) {
    this->titleText = titleText;
}
/*public*/ void ThrottleWindow::setTitleTextType(QString titleTextType) {
        this->titleTextType = titleTextType;
}
/*private*/ void ThrottleWindow::saveThrottle(QString sfile)
{
#if 1
 // Save throttle: title / window position
 // as strongly linked to extended throttles and roster presence, do not save function buttons and background window as they're stored in the roster entry
 XmlFile* xf = new XmlFile()/*{}*/;   // odd syntax is due to XmlFile being abstract
 xf->makeBackupFile(sfile);
 File* file=new File(sfile);
 try
 {
  //The file does not exist, create it before writing
  File* parentDir=file->getParentFile();
  if(!parentDir->exists())
      if (!parentDir->mkdir()) // make directory and check result
          log->error("could not make parent directory");
  if (!file->createNewFile()) // create file, check success
      log->error("createNewFile failed");
 } catch (Exception exp) {
     log->error("Exception while writing the throttle file, may not be complete: "+exp.getMessage());
 }

 try {
     //QDomElement root = doc.createElement("throttle-config");
     QDomElement root;
//     root.setTagName("throttle-config");
//     QDomDocument doc = XmlFile::newDocument(root, XmlFile::dtdLocation+"throttle-config.dtd");
  doc = QDomDocument("throttle-config");
  QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
  doc.appendChild(xmlProcessingInstruction);
  xmlProcessingInstruction = doc.createProcessingInstruction("throttle-config", XmlFile::dtdLocation+"throttle-config.dtd");
  doc.appendChild(xmlProcessingInstruction);
    // add XSLT processing instruction
     // <?xml-stylesheet type="text/xsl" href="XSLT/throttle.xsl"?>
     QDomProcessingInstruction inst = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\" href=\"/xml/XSLT/throttle.xsl\"");

     doc.appendChild(inst);
     root = doc.createElement("throttle-config");
/*			java.util.Map<String,String> m = new java.util.HashMap<String,String>();
     m.put("type", "text/xsl");
     m.put("href", jmri.jmrit.XmlFile.xsltLocation+"throttle.xsl");
     ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m);
     doc.addContent(0,p);*/
     doc.appendChild(root);
     QDomElement throttleElement = getXml();
     // don't save the loco address or consist address
//			throttleElement.getChild("AddressPanel").removeChild("locoaddress");
//			throttleElement.getChild("AddressPanel").removeChild("locoaddress");
     if ((this->getRosterEntry() != NULL) && (getDefaultThrottleFolder()+ addressPanel->getRosterEntry()->getId().trimmed() +".xml")== (sfile))
         // don't save function buttons labels, they're in roster entry
         throttleElement.firstChildElement("FunctionPanel").removeAttribute("FunctionButton");

     root.appendChild(throttleElement);
     xf->writeXML(file, doc);
     setLastUsedSaveFile(sfile);
 }
 catch (Exception ex){
     log->warn("Exception while storing throttle xml: "+ex.getMessage());
 }
#endif
}

/*public*/ void ThrottleWindow::saveThrottle()
{
#if 1
 if (getRosterEntry() != NULL)
     saveThrottle( getDefaultThrottleFolder()+ addressPanel->getRosterEntry()->getId().trimmed() +".xml" );
 else
 if (getLastUsedSaveFile() != NULL)
     saveThrottle( getLastUsedSaveFile() );
#endif
}

/*public*/ void ThrottleWindow::saveThrottleAs() {
#if 1
        JFileChooser* fileChooser = XmlFile::userFileChooser(tr("XML files"), "xml");
        fileChooser->setCurrentDirectory(new File(getDefaultThrottleFolder()));
        fileChooser->setDialogType(JFileChooser::SAVE_DIALOG);
        File* file = StoreXmlConfigAction::getFileName(fileChooser);
        if (file == NULL)
            return;
        saveThrottle( file->getAbsolutePath() );
#endif
    }
/*public*/ void ThrottleWindow::nextRunningThrottleFrame()
{
 if (! throttleFrames->isEmpty() )
 {
            //ThrottleFrame cf = this.getCurrentThrottleFrame();
  ThrottleWindow* cf = this;
            //ThrottleFrame nf = NULL;
  ThrottleWindow* nf = NULL;
  //for (Iterator<ThrottleFrame> tfi = throttleFrames.values().iterator(); tfi.hasNext(); )
  QListIterator<ThrottleWindow*> tfi(throttleFrames->values());
  while(tfi.hasNext())
  {
    //ThrottleFrame tf = tfi.next();
   ThrottleWindow* tf = tfi.next();
   if ((tf!=cf) && (tf->getAddressPanel() != NULL) && (tf->getAddressPanel()->getThrottle() != NULL) && (tf->getAddressPanel()->getThrottle()->getSpeedSetting() > 0))
    nf = tf;
   if ((tf==cf) && (nf != NULL)) // if we found something, then break, else go to end
    break;
  }
  if (nf != NULL)
   nf->toFront();
 }
}
/*public*/ void ThrottleWindow::nextThrottleFrame() {
//		throttlesLayout.next(throttlesPanel);
//		updateGUI();
    }
/*public*/ void ThrottleWindow::previousRunningThrottleFrame()
{
 if (! throttleFrames->isEmpty() )
 {
//        	ThrottleFrame cf = this.getCurrentThrottleFrame();
  ThrottleWindow* cf = this;
//        	ThrottleFrame nf = NULL;
  ThrottleWindow* nf = NULL;
  bool passed = false;
  //for (Iterator<ThrottleFrame> tfi = throttleFrames.values().iterator(); tfi.hasNext(); )
  QListIterator< ThrottleWindow*> tfi(throttleFrames->values());
  while(tfi.hasNext())
  {
   ThrottleWindow* tf = tfi.next();
   if (tf != cf)
   {
    if ((tf->getAddressPanel() != NULL) && (tf->getAddressPanel()->getThrottle() != NULL) && (tf->getAddressPanel()->getThrottle()->getSpeedSetting() > 0))
     if (passed)
     { // if we found something and passed current value, then break
      nf = tf;
      break;
     }
     else if (nf == NULL)
      nf = tf;
   }
   else
    passed = true;
  }
  if (nf != NULL)
   nf->toFront();
 }
}
/*public*/ void ThrottleWindow::previousThrottleFrame() {
//		throttlesLayout.previous(throttlesPanel);
//		updateGUI();
}

/*public*/ void ThrottleWindow::setEditMode(bool mode) {
    if (mode == isEditMode)
        return;
    isEditMode = mode;
    if (!throttleFrames->isEmpty()) {
        for (QListIterator<ThrottleWindow*> tfi(throttleFrames->values()); tfi.hasNext();) {
            tfi.next()->setEditMode(isEditMode);
        }
    }
    updateGUI();
}

/*public*/ bool ThrottleWindow::getEditMode() {
    return isEditMode;
}

/*private*/ void ThrottleWindow::switchMode()
{
 setEditMode(!isEditMode);
}


void ThrottleWindow::windowClosing(QCloseEvent *)
{
 dispose();
}

/**
 * Handle my own destruction.
 * <ol>
 * <li> dispose of sub windows.
 * <li> notify my manager of my demise.
 * </ol>
 *
 */
/*public*/ void ThrottleWindow::dispose()
{
 log->debug(tr("Disposing %1").arg(getTitle()));
 addressPanel->removeAddressListener(this);
 ThrottleFrameManager::instance()->getThrottlesListPanel()->getTableModel()->removeThrottleFrame(this, addressPanel->getCurrentAddress());
 // check for any special disposing in InternalFrames
 controlPanel->destroy();
 functionPanel->destroy();
 speedPanel->destroy();
 // dispose of this last because it will release and destroy throttle.
 addressPanel->destroy();

}

/*public*/ void ThrottleWindow::saveRosterChanges() {
    RosterEntry* rosterEntry = addressPanel->getRosterEntry();
    if (rosterEntry == nullptr) {
        JOptionPane::showMessageDialog(this, tr("Select loco using roster menu in Address Panel"), tr("No roster entry selected"), JOptionPane::ERROR_MESSAGE);
        return;
    }
    if (JOptionPane::showConfirmDialog(this, tr("Update roster entry with function buttons changes?"), tr("Update roster entry"), JOptionPane::YES_NO_OPTION) != JOptionPane::YES_OPTION) {
        return;
    }
    functionPanel->saveFunctionButtonsToRoster(rosterEntry);
    controlPanel->saveToRoster(rosterEntry);
}

/*public*/ void ThrottleWindow::removeThrottleFrame(ThrottleWindow* tf)
{
 if ( cardCounterNB > 1 ) // we don't like empty ThrottleWindow
 {
  cardCounterNB--;
  if (getCurrentThrottleFrame() == tf)
  {
   log->debug("Closing last created");
  }
  //throttlesPanel.remove( tf );
  throttleFrames->remove( tf->getTitle() );
  tf->dispose();
  //throttlesLayout.invalidateLayout(throttlesPanel);
 }
 updateGUI();
}
/*public*/ void ThrottleWindow::addThrottleFrame(ThrottleWindow* tp)
{
 cardCounterID++; cardCounterNB++;
 QString txt = tr("Card-%1").arg(cardCounterID);
 tp->setTitle(txt);
 throttleFrames->insert(txt,tp);
// throttlesPanel.add(tp,txt);
// throttlesLayout.show(throttlesPanel, txt);
 if (! isEditMode)
  tp->switchMode();
 updateGUI();
}

/*public*/ ThrottleWindow* ThrottleWindow::addThrottleFrame()
{
 setCurrentThrottleFrame ( new ThrottleWindow(this) );
//        KeyListenerInstaller.installKeyListenerOnAllComponents(throttlePanelsCyclingKeyListener, getCurrentThrottleFrame() );
 addThrottleFrame(getCurrentThrottleFrame());
 return getCurrentThrottleFrame();
}
/*public*/ void ThrottleWindow::setCurrentThrottleFrame(ThrottleWindow* tf)
{
 if (getCurrentThrottleFrame() != NULL)
  log->debug("setCurrentThrottleFrame from "+ getCurrentThrottleFrame()->getAddressPanel()->getCurrentAddress()->toString()+" to "+ tf->getAddressPanel()->getCurrentAddress()->toString());
 //pcs.firePropertyChange("ThrottleFrame", getCurrentThrottleFrame(), tf);
 emit propertyChange("ThrottleFrame", getCurrentThrottleFrame(), tf);
 currentThrottleFrame = tf;
}
/*public*/ ThrottleWindow* ThrottleWindow::getCurrentThrottleFrame()
{
 return currentThrottleFrame;
}
/*public*/ void ThrottleWindow::updateGUI()
{
 // title bar
 //getCurrentThrottleFrame()->setFrameTitle();
 // menu items
 viewAddressPanel->setEnabled(isEditMode);
 viewControlPanel->setEnabled(isEditMode);
 viewFunctionPanel->setEnabled(isEditMode);
 if (isEditMode)
 {
  viewAddressPanel->setChecked(getCurrentThrottleFrame()->getAddressPanel()->isVisible() );
  viewControlPanel->setChecked(getCurrentThrottleFrame()->getControlPanel()->isVisible() );
  viewFunctionPanel->setChecked(getCurrentThrottleFrame()->getFunctionPanel()->isVisible() );
 }
 fileMenuSave->setEnabled( getCurrentThrottleFrame()->getLastUsedSaveFile() != NULL || getCurrentThrottleFrame()->getRosterEntry() != NULL);
 editMenuExportRoster->setEnabled( getCurrentThrottleFrame()->getRosterEntry() != NULL);
 // toolbar items
 if (previous != NULL) // means toolbar enabled
 {
  if ( cardCounterNB > 1 )
  {
   previous->setEnabled( true );
   next->setEnabled( true );
//        jbClose.setEnabled( true );
   previousRunning->setEnabled( true );
   nextRunning->setEnabled( true );
  }
  else
  {
   previous->setEnabled( false );
   next->setEnabled( false );
//        jbClose.setEnabled( false );
   previousRunning->setEnabled( false );
   nextRunning->setEnabled( false );
  }
 }
}

/*public*/ QString ThrottleWindow::getLastUsedSaveFile()
{
    return lastUsedSaveFile;
}

/*public*/ void ThrottleWindow::setLastUsedSaveFile(QString lusf) {
        lastUsedSaveFile = lusf;
        /*throttleWindow.*/updateGUI();
    }

/**
 * setFrameTitle - set the frame title based on type, text and address
 */
/*public*/ void ThrottleWindow::setFrameTitle()
{
 QString addr = tr("Throttle");
 if (addressPanel->getThrottle() != NULL) {
     addr = addressPanel->getCurrentAddress()->toString();
 }
 if (getTitleTextType()==("address") ) {
     setTitle(addr);
 } else if (getTitleTextType() == ("text") ) {
     setTitle(getTitleText());
 } else if (getTitleTextType() == ("addressText") ) {
     setTitle(addr + " " + getTitleText());
 } else if (getTitleTextType() == ("textAddress") ) {
     setTitle(getTitleText() + " " + addr);
 }
 else if (getTitleTextType() == ("rosterID") )
 {
  if ((addressPanel->getRosterEntry() != NULL) && (addressPanel->getRosterEntry()->getId() != NULL)
          && (addressPanel->getRosterEntry()->getId().length() > 0)) {
      setTitle(addressPanel->getRosterEntry()->getId());
  } else {
      setTitle(addr);
  }
 }
}

void ThrottleWindow::on_address_released(LocoAddress *)
{
 setTitle(tr("Unassigned"));
}

/*public*/ QDomElement ThrottleWindow::getXml()
{

 QDomElement me =doc.createElement("ThrottleFrame");
 me.setAttribute("title", titleText);
 me.setAttribute("titleType", titleTextType);

 //java.util.ArrayList<Element> children = new java.util.ArrayList<Element>(1);
 //children.add(WindowPreferences.getPreferences(this));
 me.appendChild(WindowPreferences::getPreferences(this));
 if (!throttleFrames->isEmpty())
 {
  //ThrottleFrame* cf = this.getCurrentThrottleFrame();
  ThrottleWindow* cf = this;
  foreach (ThrottleWindow* tf, throttleFrames->values() )
  {
   //ThrottleFrame tf = tfi.next();
   if ((ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingExThrottle()) && (ThrottleFrameManager::instance()->getThrottlesPreferences()->isSavingThrottleOnLayoutSave()))
   {
    if(tf != this)
    {
     tf->toFront();
     tf->saveThrottle();
    }
   }
   QDomElement tfe = tf->getXmlFile();
   if (tfe == QDomElement()) {
       tfe = tf->getXml(tf);
   }
   //children.add(tfe);
   me.appendChild(tfe);
  }
  if (cf != NULL) {
      cf->toFront();
  }
 }
 me.appendChild(controlPanel->getXml());
 me.appendChild(functionPanel->getXml());
 me.appendChild(addressPanel->getXml());
 me.appendChild(speedPanel->getXml());

#ifdef SCRIPTING_ENABLED
 // Save Jynstruments
 QDomDocument doc = QDomDocument();
 if (throttleToolBar != NULL) {
     QObjectList cmps = throttleToolBar->children();
     if (!cmps.isEmpty()) {
         for (int i = 0; i < cmps.length(); i++) {
             try {
                 //if (cmps[i] instanceof Jynstrument)
           if(qobject_cast<Jynstrument*>(cmps.at(i)) != NULL)
                 {
                     Jynstrument* jyn = (Jynstrument*) cmps[i];
                     QDomElement elt = doc.createElement("Jynstrument");
                     elt.setAttribute("JynstrumentFolder", FileUtil::getPortableFilename(jyn->getFolder()));
                     QDomElement je = jyn->getXml();
//                     if (je != NULL) {
//                         java.util.ArrayList<Element> jychildren = new java.util.ArrayList<Element>(1);
//                         jychildren.add(je);
//                         elt.setContent(jychildren);
//                     }
//                     children.add(elt);
                     elt.appendChild(je);
                 }

             } catch (Exception ex) {
                 log->debug("Got exception (no panic) " + ex.getMessage());
             }
         }
     }
 }
#endif

 //me.setContent(children);
 return me;
}

/**
 * Collect the prefs of this object into XML Element
 * <ul>
 * <li> Window prefs
 * <li> ControlPanel
 * <li> FunctionPanel
 * <li> AddressPanel
 * </ul>
 *
 *
 * @return the XML of this object.
 */
/*public*/ QDomElement ThrottleWindow::getXml(ThrottleWindow* tf)
{
 bool switchAfter = false;
 if(tf != this)
 {
  if (!tf->isEditMode)
  {
     tf->switchMode();
     switchAfter = true;
  }
 }
    QDomElement me = doc.createElement("ThrottleFrame");
#if 0
    if (((javax.swing.plaf.basic.BasicInternalFrameUI) getControlPanel().getUI()).getNorthPane() != null) {
        Dimension bDim = ((javax.swing.plaf.basic.BasicInternalFrameUI) getControlPanel().getUI()).getNorthPane().getPreferredSize();
        me.setAttribute("border", Integer.toString(bDim.height));
    }
#endif
//    java.util.ArrayList<Element> children = new java.util.ArrayList<Element>(1);

//        children.add(WindowPreferences.getPreferences(this));  // not required as it is in ThrottleWindow

//    children.add(controlPanel.getXml());
    me.appendChild(tf->controlPanel->getXml());

//    children.add(functionPanel.getXml());
    me.appendChild(tf->functionPanel->getXml());

//    children.add(addressPanel.getXml());
    me.appendChild(tf->addressPanel->getXml());
#if 0
    // Save Jynstruments
    Component[] cmps = getComponents();
    for (int i = 0; i < cmps.length; i++) {
        try {
            if (cmps[i] instanceof JInternalFrame) {
                Component[] cmps2 = ((JInternalFrame) cmps[i]).getContentPane().getComponents();
                int j = 0;
                while ((j < cmps2.length) && (!(cmps2[j] instanceof Jynstrument))) {
                    j++;
                }
                if ((j < cmps2.length) && (cmps2[j] instanceof Jynstrument)) {
                    Jynstrument jyn = (Jynstrument) cmps2[j];
                    Element elt = new Element("Jynstrument");
                    elt.setAttribute("JynstrumentFolder", FileUtil.getPortableFilename(jyn.getFolder()));
                    java.util.ArrayList<Element> jychildren = new java.util.ArrayList<Element>(1);
                    jychildren.add(WindowPreferences.getPreferences((JInternalFrame) cmps[i]));
                    Element je = jyn.getXml();
                    if (je != null) {
                        jychildren.add(je);
                    }
                    elt.setContent(jychildren);
                    children.add(elt);
                }
            }
        } catch (Exception ex) {
            log.debug("Got exception (no panic) " + ex);
        }
    }
#endif
 if(tf != this)
 {
    //me.setContent(children);
    if (switchAfter) {
        tf->switchMode();
    }
 }
 return me;
}

/*public*/ QDomElement ThrottleWindow::getXmlFile()
{
 if (getLastUsedSaveFile() == NULL) // || (getRosterEntry()==null))
 {
     return QDomElement();
 }
 QDomElement me = doc.createElement("ThrottleFrame");
 me.setAttribute("ThrottleXMLFile", FileUtil::getPortableFilename(getLastUsedSaveFile()));
 return me;
}

//@SuppressWarnings("unchecked")
/*public*/ void ThrottleWindow::setXml(QDomElement e) {
    if (e.attribute("title") != NULL) {
        setTitle(e.attribute("title"));
    }
    if (e.attribute("title") != NULL) {
        setTitleText(e.attribute("title"));
    }
    if (e.attribute("titleType") != NULL) {
        setTitleTextType(e.attribute("titleType"));
    }

    QDomElement window = e.firstChildElement("window");
    if (window != QDomElement()) {
        WindowPreferences::setPreferences(this, window);
    }

    QDomNodeList tfes = e.elementsByTagName("ThrottleFrame");
    if (/*(tfes != QDomElement()) &&*/ (tfes.size() > 0))
    {
     for (int i = 0; i < tfes.size(); i++)
     {
      ThrottleWindow* tf;
      if (i == 0) {
          tf = getCurrentThrottleFrame();
      } else {
          tf = addThrottleFrame();
      }
      tf->setXml(tfes.at(i).toElement());
     }
    }
#if 0
    QDomNodeList jinsts = e.elementsByTagName("Jynstrument");
    if ((jinsts != NULL) && (jinsts.size() > 0)) {
        for (int i = 0; i < jinsts.size(); i++) {
            Jynstrument jyn = ynstrument(FileUtil.getExternalFilename(jinsts.get(i).attributeValue("JynstrumentFolder")));
            if ((jyn != NULL) && (jinsts.get(i) != NULL)) {
                jyn.setXml(jinsts.get(i));
            }
        }
    }
#endif
    updateGUI();
}

/*public*/ /*static*/ QString ThrottleWindow::getDefaultThrottleFolder() {
    return FileUtil::getUserFilesPath() + "throttle" + File::separator;
}

/*private*/ /*static*/ QString ThrottleWindow::DefaultThrottleFileName = "JMRI_ThrottlePreference.xml";

/*public*/ /*static*/ QString ThrottleWindow::getDefaultThrottleFilename() {
    return getDefaultThrottleFolder() + DefaultThrottleFileName;
}

// some utilities to turn a component background transparent
/*public*/ /*static*/ void ThrottleWindow::setTransparentBackground(QObject* jcomp) {
    //if (jcomp instanceof JPanel) //OS X: Jpanel components are enough
    if(qobject_cast<QWidget*>(jcomp) != NULL)
    {
        //jcomp.setBackground(new Color(0, 0, 0, 0));
     QPalette pal = ((QWidget*)jcomp)->palette();
     pal.setColor(QPalette::Background, QColor(0,0,0,0));
     ((QWidget*)jcomp)->setPalette(pal);

    }
    setTransparentBackground(((QWidget*)jcomp)->children());
}

/*public*/ /*static*/ void ThrottleWindow::setTransparentBackground(QObjectList comps) {
    for (QObject* comp : comps)
    {
     try {
//            if (comp instanceof JComponent)
      if(qobject_cast<QWidget*>(comp) != NULL)
      {
          setTransparentBackground((QWidget*) comp);
      }
     } catch (Exception e) {
         // Do nothing, just go on
     }
    }
}

// some utilities to turn a component background transparent
/*public*/ /*static*/ void ThrottleWindow::setTransparent(QWidget* jcomp) {
    setTransparent(jcomp, true);
}

/*public*/ /*static*/ void ThrottleWindow::setTransparent(QObject* jcomp, bool transparency) {
    //if (jcomp instanceof JPanel)
 if(qobject_cast<QWidget*>(jcomp) != NULL)
    { //OS X: Jpanel components are enough
        //jcomp.setOpaque(!transparency);
     ((QWidget*)jcomp)->setWindowOpacity(transparency?0.0:1.0);
    }
    setTransparent(((QWidget*)jcomp)->children(), transparency);
}

/*private*/ /*static*/ void ThrottleWindow::setTransparent(QObjectList comps, bool transparency) {
    for (QObject* comp : comps) {
        try {
            //if (comp instanceof JComponent)
      if(qobject_cast<QWidget*>(comp)!= NULL)
            {
                setTransparent((QWidget*) comp, transparency);
            }
        } catch (Exception e) {
            // Do nothing, just go on
        }
    }
}

/*public*/ QString ThrottleWindow::getClassName()
{
 // return name of Java's ThrottleFrame instead of 'ThrottleWindow'
 return "jmri.jmrit.throttle.ThrottleFrame";
}
