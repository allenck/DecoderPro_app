#include "rosterframe.h"
#include "ui_rosterframe.h"
#include "rosterentry.h"
#include "roster.h"
#include "dcclocoaddress.h"
//#include "functionlabelsmediadlg.h"
#include "../LayoutEditor/panelmenu.h"
#include "../LayoutEditor/editor.h"

#include "decoderfile.h"
#include <QDir>
#include "fileutil.h"
#include "decoderindexfile.h"
#include "paneopsprogframe.h"
#include "connectionstatus.h"
#include <QMessageBox>
#include <QToolButton>
#include "optionsdialog.h"
#include <QComboBox>
#include "defaultprogrammermanager.h"
//#include "programmermanager.h"
#include "Throttle/throttlewindow.h"
#include "paneserviceprogframe.h"
#include "progmodeselector.h"
#include "progservicemodecombobox.h"
#include "connectionconfig.h"
#include "globalprogrammermanager.h"
#include "addressedprogrammermanager.h"
#include "../LayoutEditor/configxmlmanager.h"
#include "../loconet/Pr3/pr3connectionconfig.h"
#include "pr3adapter.h"
#include "loconet/Pr3/pr3connectionconfig.h"
#include <QSignalMapper>
#include "panenewprogaction.h"
#include "../libPr3/loconet/loconetmenu.h"
#include "jmenuutil.h"
#include "jtoolbarutil.h"
#include "rostergroupspanel.h"
#include "rosterframeaction.h"
#include "userpreferencesmanager.h"
#include <QCheckBox>
#include "appsbase.h"
#include <QHeaderView>
#include "activesystemsmenu.h"
#include "windowmenu.h"
#include "printrosterentry.h"
#include "apps3.h"
#include "largepowermanagerbutton.h"
#include "rostergroupspanel.h"
#include "jmriuserpreferencesmanager.h"
#include "rostertablemodel.h"
#include <QSortFilterProxyModel>
#include "rostergroupselector.h"
#include "imagedelegate.h"
#include "helputil.h"
#include "throttleframemanager.h"
#include "throttlewindow.h"
#include "addresspanel.h"
#include "rosterentryselectorpanel.h"
#include "deleterosteritemaction.h"
#include "tabbedpreferencesaction.h"
#include "activesystemsmenu.h"
#include "joptionpane.h"
#include "connectionconfigmanager.h"
#include "addressedprogrammermanager.h"
#include "abstractpowermanager.h"
#include "programmerconfigmanager.h"
#include "throttlewindow.h"

QList<RosterFrame*> RosterFrame::frameInstances =  QList<RosterFrame*>();

// See original Java Class RosterFrame
//int RosterFrame::openWindowInstances = 0;
RosterFrame::RosterFrame( QWidget *parent) :
    JmriJFrame(parent),
    ui(new Ui::RosterFrame)
{
 common();
 addHelpMenu("package.apps.gui3.dp3.DecoderPro3", true);

}

/*public*/ RosterFrame::RosterFrame(QString name, QWidget *parent) :
  JmriJFrame(name, parent),
  ui(new Ui::RosterFrame)
{
 common();
 //this->name = name;
 buildGUI("xml/config/parts/jmri/jmrit/roster/swing/RosterFrameMenu.xml",
                "xml/config/parts/jmri/jmrit/roster/swing/RosterFrameToolBar.xml");
}

 RosterFrame::RosterFrame(QString name, QString menubarFile, QString toolbarFile, QWidget *parent) :
  JmriJFrame(name, parent),
  ui(new Ui::RosterFrame)
{
 common();
 //this->name = name;
 buildGUI(menubarFile,toolbarFile );
 systemsMenu();
 addHelpMenu("package.apps.gui3.dp3.DecoderPro3", true);
}

void RosterFrame::common()
{
 setObjectName("RosterFrame");
 ui->setupUi(this);
 menuBar = new QMenuBar();
 baseTitle = "Roster";
 model = new RosterTableModel();
 sorter = new QSortFilterProxyModel();
 sorter->setSourceModel(model);
 ui->rtable->setModel(sorter);
 ui->rtable->setSortingEnabled(true);
 ui->rtable->setContextMenuPolicy(Qt::CustomContextMenu);
 ui->rtable->setSelectionBehavior(QAbstractItemView::SelectRows);
 ui->rtable->resizeColumnsToContents();
 ui->rtable->horizontalHeader()->setStretchLastSection(true);
 connect(ui->rtable, SIGNAL(customContextMenuRequested(QPoint)),
 SLOT(showPopup(QPoint)));
 connect(ui->rtable, SIGNAL(clicked(QModelIndex)), this, SLOT(on_tableClicked(QModelIndex)));
// rosterGroupSource = new RosterGroupSelector();
// if (this->rosterGroupSource != NULL)
// {
//  this->rosterGroupSource->removePropertyChangeListener(SELECTED_ROSTER_GROUP, dataModel);
//  //disconnect(rosterGroupSource, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
// }
// this->rosterGroupSource = rosterGroupSource;
// if (this->rosterGroupSource != NULL) {
//     this->rosterGroupSource->addPropertyChangeListener(SELECTED_ROSTER_GROUP, dataModel);
//  //connect(rosterGroupSource, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
// }
 ui->rtable->setItemDelegateForColumn(RosterTableModel::ICONCOL, new ImageDelegate(this));

 progFrame = NULL;
 _allowQuit = false;
 serModeProCon = NULL;
 opsModeProCon = NULL;
 programmer1 = tr("Comprehensive");
 programmer2 = tr("Basic");
 pcs = new PropertyChangeSupport(this);
 inStartProgrammer = false;
 re = NULL;
 bUpdating =false;
 _hideBottomPane = false;
 _hideGroups = false;
 _hideRosterImage = false;
// ui->verticalLayout->removeWidget(ui->summaryPanel);
// ui->splitter->addWidget(ui->summaryPanel);
 //toolBar = ui->toolBar;
 _hideBottomPane = false;
 contextService = new QAction(tr("Programming Track"),this);
 contextService->setCheckable(true);
 contextService->setProperty("action", "setprogservice");
 contextOps = new QAction(tr("Programming On Main"),this);
 contextOps->setCheckable(true);
 contextOps->setProperty("action", "setprogops");
 contextEdit = new QAction(tr("Edit"),this);
 contextEdit->setCheckable(true);
 contextEdit->setProperty("action", "setprogedit");
 selectedRosterEntries = NULL;


 QActionGroup* actionGroup = new QActionGroup(this);
 actionGroup->addAction(ui->actionProgramming_Track);
 actionGroup->addAction(ui->actionProgramming_On_Main);
 actionGroup->addAction(ui->actionEdit_Only);
 ui->actionProgramming_Track->setChecked(true);

 serviceModeProgrammerLabel = new QLabel(tr("Service Mode Programmer: idle"));
 operationsModeProgrammerLabel = new QLabel(tr("Ops Mode Programmer: idle"));

// rosterEntryUpdateListener = new RosterEntryUpdateListener(this);
 currentMapper = new QSignalMapper();
 connect(currentMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_currentMapped(QObject*)));

 log = new Logger("RosterFrame");
// newLoco = new QToolButton(this);
// newLoco->setIcon(QIcon(":/resources/icons/misc/gui3/NewLocoButton.png"));
// newLoco->setText(tr("New Loco"));
// newLoco->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
// connect(newLoco, SIGNAL(clicked()), this, SLOT(On_newLoco_clicked()));
// ui->toolBar->addWidget(newLoco);
 newLocoAct = ui->toolBar->addAction(QIcon(":/resources/icons/misc/gui3/NewLocoButton.png"), tr("New Loco"));
 connect(newLocoAct, SIGNAL(triggered()), this, SLOT(On_newLoco_clicked()));

 identifyLoco = new QToolButton(this);
 identifyLoco->setIcon(QIcon(":/resources/icons/misc/gui3/IdentifyButton.png"));
 identifyLoco->setText(tr("Identify Loco"));
 identifyLoco->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
 ui->toolBar->addWidget(identifyLoco);
 connect(identifyLoco, SIGNAL(clicked()), this, SLOT(startIdentifyLoco()));

 PowerManager* pmgr = (PowerManager*) InstanceManager::getDefault("PowerManager");
 //pmgr->addPropertyChangeListener(new PwrListener(this));
 togglePower = new QToolButton( this);
 togglePower->setIcon(QIcon(":/resources/icons/throttles/power_yellow.png"));
 togglePower->setText(tr("Power unknown"));
 if(pmgr != NULL)
 {
  AbstractPowerManager* apm = (AbstractPowerManager*)pmgr;
  connect(apm->pcs,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  if(pmgr->getPower()== PowerManager::ON)
  {
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_green.png") );
   togglePower->setText(tr("Power on"));
  }
  else if (pmgr->getPower()== PowerManager::OFF)
  {
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_red.png"));
   togglePower->setText(tr("Power off"));
  }
  else
   log->warn("Power state unknown!");
 }
// else
// {
//  togglePower = new QToolButton( this);
//  togglePower->setIcon(QIcon(":/resources/icons/throttles/power_yellow.png"));
//  togglePower->setText(tr("Power unknown"));
// }
 ui->toolBar->addWidget(togglePower);
 togglePower->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
 connect(togglePower, SIGNAL(clicked()), this, SLOT(on_togglePower_clicked()));

 modePanel = new ProgServiceModeComboBox();
 programmerStatusLabel = new QLabel(tr("Programmer Status: "));
 statusField = new QLabel("Idle");
 QWidget* statusWidget = new QWidget();
 QHBoxLayout* statusWidgetLayout = new QHBoxLayout();
 statusWidget->setLayout(statusWidgetLayout);
 statusWidgetLayout->addWidget(programmerStatusLabel);
 statusWidgetLayout->addWidget(statusField);
 ui->statusBar->addPermanentWidget(statusWidget);
 ui->statusBar->addWidget(serviceModeProgrammerLabel);
 ui->statusBar->addWidget(operationsModeProgrammerLabel);
 ui->toolBar->addWidget(modePanel);
 ui->toolBar->addSeparator();
// ui->toolBar->addWidget(new QLabel(tr("Programmer")));
// ui->toolBar->addWidget(cbProgrammers=new QComboBox());
// cbProgrammers->addItem("Advanced");
// cbProgrammers->addItem("Basic");
// cbProgrammers->addItem("Comprehensive");
// cbProgrammers->addItem("Custom");
// cbProgrammers->addItem("ESU");
// cbProgrammers->addItem("Registers");
// cbProgrammers->addItem("Sample Club");
// cbProgrammers->addItem("TrainShowBasic");
// cbProgrammers->addItem("Tutorial");
// cbProgrammers->addItem("Zimo");
// connect(cbProgrammers, SIGNAL(currentIndexChanged(QString)), this, SLOT(On_cbProgrammers_currentIndexChanged(QString)));
 roster = Roster::getDefault();
 //roster->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(roster->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 list = roster->getEntriesMatchingCriteria("","","","","","","","");
// ui->rtable->setColumnCount(10);
// ui->rtable->setRowCount(list.count());
// for(int row=0; row < list.count(); row++)
// {
//  RosterEntry* re = list.at(row);
//  rows.append(re);
//  updateRow(row, re);
// }
 ui->btnRosterMedia->setEnabled(false);
 ui->throttleLaunch->setEnabled(false);
 ui->prog1Button->setEnabled(false);
 ui->lblID->setText("");
 ui->lblRoadName->setText("");
 ui->lblRoadNumber->setText("");
 ui->lblManufacturer->setText("");
 ui->lblOwner->setText("");
 ui->lblModel->setText("");
 ui->lblDCCAddress->setText("");
 ui->lblDecoderFamily->setText("");
 ui->lblDecoderModel->setText("");
 ui->lblFileName->setText("");

 ui->btnRosterMedia->setEnabled(false);
 ui->throttleLaunch->setEnabled(false);

#if 1
// PanelMenu::instance()->addEditorPanel((Editor*)this);
// connect(ui->menuWindow, SIGNAL(aboutToShow()), this, SLOT(on_menuWindow_aboutToShow()));
 //connect(ui->actionProgram, SIGNAL(triggered()), this, SLOT(on_prog1Button_clicked()));
 connect(ui->actionProgram, &QAction::triggered, [=]{
  log->debug("Open programmer pressed");
              startProgrammer(nullptr, re, programmer1);
 });
 QTimer::singleShot(10, this, SLOT(buildWindow()));
#endif
// ConnectionStatus::instance().addPropertyChangeListener(new PropertyChangeListener()
// {
//     @Override
//     public void propertyChange(PropertyChangeEvent e) {
//         if ((e.getPropertyName()==("change")) || (e.getPropertyName()==("add"))) {
//             updateProgrammerStatus();
//         }
//     }
// });
 ConnectionStatus* connectionStatus = ConnectionStatus::instance();
 connect(connectionStatus->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(On_ConnectionStatusPropertyChange(PropertyChangeEvent*)));
 connect(ui->actionPreferences, SIGNAL(triggered(bool)), this, SLOT(On_actionPreferences_triggered()));

// InstanceManager.addPropertyChangeListener(new PropertyChangeListener() {
//     @Override
//     public void propertyChange(PropertyChangeEvent e) {
//         if (e.getPropertyName()==("programmermanager")) {
//             updateProgrammerStatus();
//         }
//     }
// });
 InstanceManager* instanceManager = InstanceManager::getDefault();
 connect(instanceManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(On_InstanceManagerPropertyChange(PropertyChangeEvent*)));
 signalMapper = new QSignalMapper(this);
 signalMapper->setMapping(ui->service, 0);
 connect(ui->service, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
 signalMapper->setMapping(ui->ops,1);
 connect(ui->ops, SIGNAL(clicked(bool)),signalMapper, SLOT(map()));
 signalMapper->setMapping(ui->edit,2);
 connect(ui->edit, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
 connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(updateProgMode()));

// LocoNetSystemConnectionMemo* connectionMemo = (LocoNetSystemConnectionMemo*)InstanceManager::getDefault("LocoNetSystemConnectionMemo");
// Q_UNUSED(connectionMemo);
 //ui->menubar->insertMenu(ui->menuLocoNet->menuAction(),  LocoNetMenu::instance(connectionMemo, this));
 ActiveSystemsMenu::addItems(ui->menubar, this);
 ui->menuLocoNet->clear();
 ui->menubar->removeAction(ui->menuLocoNet->menuAction());
}

void RosterFrame::On_ConnectionStatusPropertyChange(PropertyChangeEvent *e)
{
 if ((e->getPropertyName()==("change")) || (e->getPropertyName()==("add")))
 {
  updateProgrammerStatus(e);
 }
}
void RosterFrame::On_InstanceManagerPropertyChange(PropertyChangeEvent * e)
{
 if ((e->getPropertyName() == ("change")) || (e->getPropertyName() == ("add")))
 {
  log->debug(tr("Received property %1 with value %2 ").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
  updateProgrammerStatus(e);
 }
}

RosterFrame::~RosterFrame()
{
 delete ui;
}
#if 0
void RosterFrame::updateRow(int row, RosterEntry* re)
{
 bUpdating= true;
 QTableWidgetItem* id = new QTableWidgetItem(re->getId());
 ui->rtable->setItem(row,0,id);
 QTableWidgetItem* dccAddr = new QTableWidgetItem(re->getDccAddress());
 ui->rtable->setItem(row,1,dccAddr);
 QTableWidgetItem* decoderModel = new QTableWidgetItem(re->getDecoderModel());
 ui->rtable->setItem(row, 3, decoderModel);
 QTableWidgetItem* roadName = new QTableWidgetItem(re->getRoadName());
 ui->rtable->setItem(row, 4, roadName);
 QTableWidgetItem* roadNumber = new QTableWidgetItem(re->getRoadNumber());
 ui->rtable->setItem(row, 5, roadNumber);
 QTableWidgetItem* manufacturer = new QTableWidgetItem(re->getMfg());
 ui->rtable->setItem(row, 6, manufacturer);
 QTableWidgetItem* model = new QTableWidgetItem(re->getModel());
 ui->rtable->setItem(row, 7, model);
 QTableWidgetItem* owner = new QTableWidgetItem(re->getOwner());
 ui->rtable->setItem(row, 8, owner);
 QTableWidgetItem* dateModified = new QTableWidgetItem(re->getDateUpdated());
 ui->rtable->setItem(row, 9, dateModified);
 bUpdating = false;
 connect(re, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

void RosterFrame::updateDetails()
{
 for(int row =0; row < ui->rtable->rowCount(); row++)
 {
  if(ui->rtable->item(row,0)->text() == rosterEntry->getId())
  {
   updateRow(row, rosterEntry);
   ui->rtable->selectRow(row);
   on_tableWidget_cellClicked(row,0);
   break;
  }
 }
}

void RosterFrame::on_tableWidget_cellClicked(int row, int /*col*/)
{
 rosterEntry = list.at(row);
 updateInfo();
}
#endif
void RosterFrame::updateDetails()
{
 if(re == nullptr)
  return;
 ui->lblID->setText(re->getId());
 ui->lblRoadName->setText(re->getRoadName());
 ui->lblRoadNumber->setText(re->getRoadNumber());
 ui->lblManufacturer->setText(re->getMfg());
 ui->lblOwner->setText(re->getOwner());
 ui->lblModel->setText(re->getModel());
 ui->lblDCCAddress->setText(re->getDccAddress());
 ui->lblDecoderFamily->setText(re->getDecoderFamily());
 ui->lblDecoderModel->setText(re->getDecoderModel());
 ui->lblFileName->setText(re->getFileName());

 ui->btnRosterMedia->setEnabled(true);
 ui->prog1Button->setEnabled(true);
 ui->throttleLaunch->setEnabled(true);


 if(QFileInfo(re->getImagePath()).exists())
 {
  QImage img(re->getImagePath());
  ui->locoImage->setPixmap(QPixmap::fromImage(img).scaledToWidth(ui->locoImage->width()));
 }
 else
  ui->locoImage->clear();

}
void RosterFrame::on_btnRosterMedia_clicked()
{
 log->debug("Open programmer pressed");
 ui->edit->setChecked(true);
 startProgrammer(nullptr, re, "dp3" + File::separator + "MediaPane");
}

void RosterFrame::on_throttleLaunch_clicked()
{

 QList<Editor*>* list = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getEditorPanelList();
 //int row = 0;
 foreach(Editor* panel, *list)
 {
  QString pName = panel->metaObject()->className();
  if(pName == "ThrottleWindow")
  {
   ThrottleWindow* tw = (ThrottleWindow*)panel;
   QString id = tw->id();
   if(id == re->getId())
   {
    // Throttle is already created.
    tw->show();
    return;
   }
  }
 }
 // Throttle window not found; create a new one.
 ThrottleWindow* tw = new ThrottleWindow(/*memo,*/this);
 log->debug("throttleLaunch clicked");
 tw->getAddressPanel()->setRosterEntry(re);
 tw->show();
}
//void RosterFrame::on_menuWindow_aboutToShow()
//{
// ui->menuWindow->clear();
// PanelMenu::instance()->updatePanelMenu(ui->menuWindow);
//}
void RosterFrame::on_prog1Button_clicked()
{

 log->debug("Open programmer pressed");
 startProgrammer(nullptr, re, programmer1);
}

//void RosterFrame::On_cbProgrammers_currentIndexChanged(QString /*text*/)
//{
// if(progFrame != NULL)
// {
//  progFrame->close();
//  delete progFrame;
//  progFrame = NULL;
//  on_prog1Button_clicked();
// }
//}

QString RosterFrame::getTitle()
{
 return windowTitle();
}
void RosterFrame::on_actionHide_Show_Summary_Panel_triggered()
{
 ui->summaryPanel->setVisible(!ui->summaryPanel->isVisible());
 _hideBottomPane = !ui->summaryPanel->isVisible();
}
void RosterFrame::on_actionHide_Show_Roster_Image_triggered()
{
 ui->locoImage->setVisible(!ui->locoImage->isVisible());
 _hideRosterImage = !ui->locoImage->isVisible();
}
void RosterFrame::on_actionProgramming_Track_triggered()
{
 ui->service->setChecked(true);
 ui->actionProgramming_Track->setChecked(true);
}
void RosterFrame::on_actionProgramming_On_Main_triggered()
{
 ui->ops->setChecked(true);
 ui->actionProgramming_On_Main->setChecked(true);
}
void RosterFrame::On_actionPreferences_triggered()
{
 TabbedPreferencesAction* p = new TabbedPreferencesAction();
 p->actionPerformed();
}
void RosterFrame::on_actionEdit_Only_triggered()
{
 ui->edit->setChecked(true);
 ui->actionEdit_Only->setChecked(true);
}
void RosterFrame::on_actionLabels_and_Media_triggered()
{
 on_btnRosterMedia_clicked();
}
void RosterFrame::on_actionNew_Throttle_triggered()
{
 on_throttleLaunch_clicked();
}
//void RosterFrame::propertyChange(PropertyChangeEvent *e)
//{
//    qDebug()<< e->getPropertyName();
//}

/*protected*/ /*final*/ void RosterFrame::buildWindow()
{
 //Additions to the toolbar need to be added first otherwise when trying to hide bits up during the initialisation they remain on screen
 //additionsToToolBar();
 frameInstances.append(this);

#if 1
 prefsMgr = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
//    getTop().add(createTop());
 QVariant selectedRosterGroup = prefsMgr->getProperty(getWindowFrameRef(), RosterGroupsPanel::SELECTED_ROSTER_GROUP);
 groups = new RosterGroupsPanel((selectedRosterGroup != QVariant()) ? selectedRosterGroup.toString() : "");
 groups->setNewWindowMenuAction(this->getNewWindowAction());
 setTitle(groups->getSelectedRosterGroup());
 ui->groupsPlaceholder->hide();
 ui->splitter_2->insertWidget(0, groups);
// ui->groupsPlaceholder->layout()->addWidget(groups);
// ui->groupsPlaceholder->show();

//    getBottom().setMinimumSize(summaryPaneDim);
//    getBottom().add(createBottom());
//    statusBar();
//    systemsMenu();
 helpMenu(getMenu(), this);
 //Set all the sort and width details of the table first.
 QString rostertableref = getWindowFrameRef() + ":roster";
#if 0
 for(int i=0; i < ui->rtable->columnCount(); i++)
 {
  QString columnName = ui->rtable->horizontalHeader()->model()->headerData(i, Qt::Horizontal).toString();
  int w = prefsMgr->getTableColumnWidth(rostertableref, columnName);
  if(w > 0)
   ui->rtable->setColumnWidth(i,w);
 }
#endif
 // for debugging:
 QVector<QString> rosterGroupList = Roster::getDefault()->getRosterGroupList();
 bool bHide = prefsMgr->getSimplePreferenceState(this->getClassName() + ".hideGroups");

    if ((!prefsMgr->getSimplePreferenceState(this->getClassName() + ".hideGroups")) && !Roster::getDefault()->getRosterGroupList().isEmpty())
    {
     hideGroupsPane(false);
    }
    else
    {
     hideGroupsPane(true);
    }
    if (prefsMgr->getSimplePreferenceState(this->getClassName() + ".hideSummary"))
    {
     //We have to set it to display first, then we can hide it.
     hideBottomPane(false);
     ui->summaryPanel->setVisible(true);
     hideBottomPane(true);
     ui->summaryPanel->setVisible(false);
     _hideBottomPane = true;
    }
    if (prefsMgr->getSimplePreferenceState(this->getClassName() + ".hideRosterImage")) {
     ui->locoImage->setVisible(false);
     _hideRosterImage = true;
    }
    if (prefsMgr->getSimplePreferenceState(this->getClassName() + ".hideRosterImage"))
    {
     ui->locoImage->setVisible(false);
     _hideRosterImage = true;
    }
//    groups.addPropertyChangeListener(SELECTED_ROSTER_GROUP, new PropertyChangeListener() {
//        @Override
//        public void propertyChange(PropertyChangeEvent pce) {
//            prefsMgr.setProperty(this.getClass().getName(), SELECTED_ROSTER_GROUP, pce.getNewValue());
//            setTitle((String) pce.getNewValue());
//        }
//    });
    connect(groups, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_groupChange(PropertyChangeEvent*)));

//      Roster.instance().addPropertyChangeListener((PropertyChangeEvent e) -> {
//                  if (e.getPropertyName() == ("RosterGroupAdded") && Roster.instance().getRosterGroupList().size() == 1) {
//                      // if the pane is hidden, show it when 1st group is created
//                      hideGroupsPane(false);
//                      enableRosterGroupMenuItems(true);
//                  } else if (!rtable.isVisible() && (e.getPropertyName() == ("saved"))) {
//                      if (firstHelpLabel != null) {
//                          firstHelpLabel.setVisible(false);
//                      }
//                      rtable.setVisible(true);
//                      rtable.resetColumnWidths();
//                  }
//              });
    connect(Roster::getDefault()->pcs, SIGNAL(propertyChange(PropertyChangeEvent* )), this, SLOT(on_RosterChange(PropertyChangeEvent*)));
#if 0
    PropertyChangeListener* propertyChangeListener = new PropertyChangeListener() {
        @Override
        public void propertyChange(PropertyChangeEvent changeEvent) {
            JSplitPane sourceSplitPane = (JSplitPane) changeEvent.getSource();
            String propertyName = changeEvent.getPropertyName();
            if (propertyName==(JSplitPane.LAST_DIVIDER_LOCATION_PROPERTY)) {
                int current = sourceSplitPane.getDividerLocation() + sourceSplitPane.getDividerSize();
                int panesize = (int) (sourceSplitPane.getSize().getHeight());
                if (panesize - current <= 1) {
                    hideBottomPane = true;
                } else {
                    hideBottomPane = false;
                    //p.setSimplePreferenceState(DecoderPro3Window.class.getName()+".hideSummary",hideSummary);
                }
            }
        }
    };
#endif
    QVariant splitterSizes = prefsMgr->getProperty(this->getClassName(), "splitterSizes");
    if(splitterSizes != QVariant())
    {
     QList<int> list = QList<int>();
     QString str = splitterSizes.toString();
     QStringList sl = str.split(",");
     foreach (QString s, sl)
     {
      list.append(s.toInt());
     }
     ui->splitter->setSizes(list);
    }
    QVariant splitter2Sizes = prefsMgr->getProperty("DecoderPro3Window", "splitter2Sizes");
    if(splitter2Sizes != QVariant())
    {
     QList<int> list = QList<int>();
     QString str = splitter2Sizes.toString();
     QStringList sl = str.split(",");
     foreach (QString s, sl)
     {
      list.append(s.toInt());
     }

     ui->splitter_2->setSizes(list);
    }


    connect(ui->splitter, SIGNAL(splitterMoved(int,int)), this, SLOT(On_splitterMoved(int, int)));
    connect(ui->splitter_2, SIGNAL(splitterMoved(int,int)), this, SLOT(On_splitter2Moved(int, int)));

#endif
 updateProgrammerStatus(NULL);
// ConnectionStatus::instance()->addPropertyChangeListener(new PropertyChangeListener());
//    {
////        @Override
//        public void propertyChange(PropertyChangeEvent e) {
//            if ((e.getPropertyName()==("change")) || (e.getPropertyName()==("add"))) {
//                updateProgrammerStatus();
//            }
//        }
//    });
 ConnectionStatus* connectionStatus = ConnectionStatus::instance();
 connect(connectionStatus->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(On_ConnectionStatusPropertyChange(PropertyChangeEvent*)));

// InstanceManager::addPropertyChangeListener(new PropertyChangeListener());
//    {
////        @Override
//        public void propertyChange(PropertyChangeEvent e) {
//            if (e.getPropertyName()==("programmermanager")) {
//                updateProgrammerStatus();
//            }
//        }
//    });
 connect(InstanceManager::getDefault(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(On_InstanceManagerPropertyChange(PropertyChangeEvent*)));
// getSplitPane().addPropertyChangeListener(propertyChangeListener);
 if (this->getProgrammerConfigManager()->getDefaultFile() != "") {
     programmer1 = this->getProgrammerConfigManager()->getDefaultFile();
 }
 //this->getProgrammerConfigManager()->addPropertyChangeListener(ProgrammerConfigManager::DEFAULT_FILE, (PropertyChangeEvent evt) -> {
 connect(this->getProgrammerConfigManager()->propertyChangeSupport, &PropertyChangeSupport::propertyChange, [=]{
     if (this->getProgrammerConfigManager()->getDefaultFile() != "") {
         programmer1 = this->getProgrammerConfigManager()->getDefaultFile();
     }
 });

 QString lastProg = (QString) prefsMgr->getProperty(getWindowFrameRef(), "selectedProgrammer").toString();
 if (lastProg != "")
 {
  if (lastProg==("service") && ui->service->isEnabled())
  {
   ui->service->setChecked(true);
   updateProgMode();
  }
  else if (lastProg==("ops") && ui->ops->isEnabled())
  {
   ui->ops->setChecked(true);
   updateProgMode();
  }
  else if (lastProg==("edit") && ui->edit->isEnabled())
  {
   ui->edit->setChecked(true);
   updateProgMode();
  }
 }
 if (frameInstances.size() > 1)
 {
  firePropertyChange("closewindow", "setEnabled", true);
//  allowQuit(frameInstances.at(0)->isAllowQuit());
 }
 else
 {
  firePropertyChange("closewindow", "setEnabled", false);
 }
}
void DefaultFilePropertyChangeListener::propertyChange(PropertyChangeEvent *evt)
{
 if (frame->getProgrammerConfigManager()->getDefaultFile() != "") {
       frame->programmer1 = frame->getProgrammerConfigManager()->getDefaultFile();
   }
}

/*protected*/ void RosterFrame::firePropertyChange(QString p, QVariant old, QVariant n)
{
 if (pcs==NULL)
  return;
 pcs->firePropertyChange(p,old,n);
}
/*
 * this handles setting up and updating the GUI for the types of programmer
 * available.
 */
/*protected*/ void RosterFrame::updateProgrammerStatus(/*@Nullable*/ PropertyChangeEvent* evt)
{
 ConnectionConfig* oldServMode = serModeProCon;
 ConnectionConfig* oldOpsMode = opsModeProCon;

 GlobalProgrammerManager* gpm = NULL;
 AddressedProgrammerManager* apm = NULL;

 // Find the connection that goes with the global programmer
 // test that IM has a default GPM, or that event is not the removal of a GPM
 if (InstanceManager::containsDefault("GlobalProgrammerManager")
                 || (evt != NULL
                 && evt->getPropertyName() == (InstanceManager::getDefaultsPropertyName("GlobalProgrammerManager"))
                 && evt->getNewValue() == QVariant()))
 {
  gpm = (DefaultProgrammerManager*)InstanceManager::getNullableDefault("GlobalProgrammerManager");
 }
 if (gpm!=NULL)
 {
  QString serviceModeProgrammerName = gpm->getUserName();
  log->debug(tr("GlobalProgrammerManager found of class %1 name %2 ").arg(gpm->toString()).arg(serviceModeProgrammerName));
  QVector<ConnectionConfig*> ccm = ((ConnectionConfigManager*)InstanceManager::getOptionalDefault("ConnectionConfigManager"))->getConnections();
  foreach (ConnectionConfig* connection, ccm)
  {
   log->debug(tr("Checking connection name %1").arg(connection->getConnectionName()));
   if (connection->getConnectionName() != NULL && connection->getConnectionName()==(serviceModeProgrammerName))
   {
       log->debug("Connection found for GlobalProgrammermanager");
       serModeProCon = connection;
   }
  }
 }

 // Find the connection that goes with the addressed programmer
 // test that IM has a default APM, or that event is not the removal of an APM
 if (InstanceManager::containsDefault("AddressedProgrammerManager")
         || (evt != NULL
         && evt->getPropertyName() == (InstanceManager::getDefaultsPropertyName("AddressedProgrammerManager"))
         && evt->getNewValue() == QVariant()))
 {
     apm = (DefaultProgrammerManager*)InstanceManager::getNullableDefault("AddressedProgrammerManager");
 }
 if (apm!=NULL)
 {
  QString opsModeProgrammerName = apm->getUserName();
  log->debug(tr("AddressedProgrammerManager found of class %1 name %2 ").arg(apm->self()->metaObject()->className()).arg(opsModeProgrammerName));
  //InstanceManager.getOptionalDefault(ConnectionConfigManager.class).ifPresent((ccm) ->
  if(InstanceManager::getOptionalDefault("ConnectionConfigManager")!= NULL)
  {
   QVector<ConnectionConfig*> ccm = ((ConnectionConfigManager*)InstanceManager::getOptionalDefault("ConnectionConfigManager"))->getConnections();
   foreach (ConnectionConfig* connection, ccm)
   {
    log->debug(tr("Checking connection name %1").arg(connection->getConnectionName()));
    if (connection->getConnectionName() != NULL && connection->getConnectionName() == (opsModeProgrammerName)) {
        log->debug("Connection found for AddressedProgrammermanager");
        opsModeProCon = connection;
    }
   }
  }
 }

 if (serModeProCon != NULL)
 {
  //PR3Adapter* adapter = (PR3Adapter*)serModeProCon->getAdapter();
  if (ConnectionStatus::instance()->isConnectionOk(serModeProCon->getInfo()/*adapter->getCurrentPortName()*/)
                && gpm != NULL)
  {
   serviceModeProgrammerLabel->setText(
            tr("Service Mode Programmer %1 Is Online").arg( serModeProCon->getConnectionName()));
   serviceModeProgrammerLabel->setStyleSheet("QLabel { color: rgb(0, 128, 0); }");
  }
  else
  {
   serviceModeProgrammerLabel->setText(
            tr("Service Mode Programmer %1 Is Offline").arg( serModeProCon->getConnectionName()));
   serviceModeProgrammerLabel->setStyleSheet("QLabel { color: rgb(128, 0, 0); }");
  }
  if (oldServMode == NULL)
  {
//    contextService.setEnabled(true);
//    contextService.setVisible(true);
    ui->service->setEnabled(true);
    ui->service->setVisible(true);
    firePropertyChange("setprogservice", "setEnabled", true);
  }
 }
 else
 {
  serviceModeProgrammerLabel->setText(tr("No Service Mode Programmer Available"));
  serviceModeProgrammerLabel->setStyleSheet("QLabel { color: rgb(128, 0, 0); }");
  if (oldServMode != NULL)
  {
//   contextService.setEnabled(false);
//   contextService.setVisible(false);
   ui->service->setEnabled(false);
   ui->service->setVisible(false);
   firePropertyChange("setprogservice", "setEnabled", false);
  }
 }

 if (opsModeProCon != NULL)
 {
  //PR3Adapter* adapter = (PR3Adapter*)opsModeProCon->getAdapter();
  if (ConnectionStatus::instance()->isConnectionOk(opsModeProCon->getInfo()) && apm!=NULL )
  {
   operationsModeProgrammerLabel->setText(
            tr("Operations Mode Programmer %1 Is Online").arg( opsModeProCon->getConnectionName()));
    operationsModeProgrammerLabel->setStyleSheet("QLabel { color: rgb(0,128,0); }");
  }
  else
  {
    operationsModeProgrammerLabel->setText(
            tr("Operations Mode Programmer %1 Is Offline").arg(opsModeProCon->getConnectionName()));
    operationsModeProgrammerLabel->setStyleSheet("QLabel { color: rgb(128,0,0); }");
  }
  if (oldOpsMode == NULL)
  {
//   contextOps.setEnabled(true);
//   contextOps.setVisible(true);
   ui->ops->setEnabled(true);
   ui->ops->setVisible(true);
   firePropertyChange("setprogops", "setEnabled", true);
  }
 }
 else
 {
  operationsModeProgrammerLabel->setText(tr("No Ops Programmer Available"));
  operationsModeProgrammerLabel->setStyleSheet("QLabel { color: rgb(128,0,0); }");
  if (oldOpsMode != NULL)
  {
//   contextOps.setEnabled(false);
//   contextOps.setVisible(false);
   ui->ops->setEnabled(false);
   ui->ops->setVisible(false);
   firePropertyChange("setprogops", "setEnabled", false);
  }
 }
 QString strProgMode;
 if (ui->service->isEnabled())
 {
//  contextService.setSelected(true);
  ui->service->setChecked(true);
  strProgMode = "setprogservice";
  modePanel->setVisible(true);
 }
 else if (ui->ops->isEnabled())
 {
//  contextOps.setSelected(true);
  ui->ops->setChecked(true);
  strProgMode = "setprogops";
  modePanel->setVisible(false);
 }
 else
 {
//  contextEdit.setSelected(true);
  ui->edit->setChecked(true);
  modePanel->setVisible(false);
  strProgMode = "setprogedit";
 }
 firePropertyChange(strProgMode, "setSelected", true);
}

void RosterFrame::updateProgMode() // SLOT
{
 QString progMode;
 if (ui->service->isChecked())
 {
  progMode = "setprogservice";
  ui->actionProgramming_Track->setChecked(true);
 }
 else if (ui->ops->isChecked())
 {
  progMode = "setprogops";
  ui->actionProgramming_On_Main->setChecked(true);
 }
 else
 {
  progMode = "setprogedit";
  ui->actionEdit_Only->setChecked(true);
 }
 firePropertyChange(progMode, QVariant("setSelected"), QVariant(true));
}
/**
 * Identify loco button pressed, start the identify operation This defines
 * what happens when the identify is done.
 */
//taken out of CombinedLocoSelPane
/*protected*/ void RosterFrame::startIdentifyLoco()
{
 /*final*/ RosterFrame* me = this;
 Programmer* programmer = NULL;
 if (modePanel->isSelected())
 {
     programmer = modePanel->getProgrammer();
 }
 if (programmer == NULL)
 {
  GlobalProgrammerManager* gpm = (DefaultProgrammerManager*)InstanceManager::getNullableDefault("GlobalProgrammerManager");
  if (gpm != NULL)
  {
   programmer = gpm->getGlobalProgrammer();
   log->warn(tr("Selector did not provide a programmer, attempt to use GlobalProgrammerManager default: %1").arg(programmer->self()->metaObject()->className()));
} else {
   log->warn("Selector did not provide a programmer, and no ProgramManager found in InstanceManager");
  }
 }

 // if failed to get programmer, tell user and stop
 if (programmer == NULL) {
     log->error("Identify loco called when no service mode programmer is available; button should have been disabled");
     JOptionPane::showMessageDialog(NULL, tr("Identify loco called when no service mode programmer is available"));
     return;
 }

 // and now do the work
#if 0
    // start identifying a loco
    /*final*/ RosterFrame* me = this;
    IdentifyLoco ident = new IdentifyLoco() {
        private RosterFrame who = me;

        //@Override
        protected void done(int dccAddress) {
            // if Done, updated the selected decoder
            who.selectLoco(dccAddress, !shortAddr, cv8val, cv7val);
        }

        //@Override
        protected void message(String m) {
            statusField.setText(m);
        }

        //@Override
        protected void error() {
            // raise the button again
            //idloco.setSelected(false);
        }
    };
#endif
    MyIdentifyLoco* ident = new MyIdentifyLoco(programmer, me);
    connect(ident, SIGNAL(doneSignal(int,bool,int,int)), this, SLOT(selectLoco(int,bool,int,int)));
    ident->start();
}
/**
 * Identify locomotive complete, act on it by setting the GUI. This will
 * fire "GUI changed" events which will reset the decoder GUI.
 *
 * @param dccAddress
 */
/*protected*/ void RosterFrame::selectLoco(int dccAddress, bool isLong, int mfgId, int modelId)
{
    // raise the button again
    //idloco.setSelected(false);
    // locate that loco
 inStartProgrammer = false;

 if (re != NULL)
 {
  //We remove the propertychangelistener if we had a previously selected entry;
  re->removePropertyChangeListener(rosterEntryUpdateListener);
 }
 QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, QString::number(dccAddress), NULL, NULL, NULL, NULL);
 if (log->isDebugEnabled())
 {
  log->debug("selectLoco found " + QString::number(l.size()) + " matches");
 }
 if (l.size() > 0)
 {
  if (l.size() > 1)
  {
   //More than one possible loco, so check long flag
   QList<RosterEntry*> l2 =  QList<RosterEntry*>();
   foreach (RosterEntry* _re,  l)
   {
    if (_re->isLongAddress() == isLong)
    {
     l2.append(_re);
    }
   }
   if (l2.size() == 1)
   {
    re = l2.at(0);
   }
   else
   {
    if (l2.isEmpty())
    {
     l2 = l;
    }
    //Still more than one possible loco, so check against the decoder family
    QList<RosterEntry*> l3 =  QList<RosterEntry*>();
    QList<DecoderFile*> temp = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList("", "", QString::number(mfgId), QString::number( modelId), "", "");
    QStringList* decoderFam = new QStringList();
    foreach (DecoderFile* f, temp)
    {
     if (!decoderFam->contains(f->getModel()))
     {
      decoderFam->append(f->getModel());
     }
    }
    foreach (RosterEntry* _re, l2)
    {
     if (decoderFam->contains(_re->getDecoderModel()))
     {
      l3.append(_re);
     }
    }
    if (l3.isEmpty())
    {
     //Unable to determine the loco against the manufacture therefore will be unable to further identify against decoder.
     re = l2.at(0);
    }
    else
    {
     //We have no other options to match against so will return the first one we come across;
     re = l3.at(0);
    }
   }
  }
  else
  {
   re = l.at(0);
  }
  re->addPropertyChangeListener(rosterEntryUpdateListener);
//  connect(rosterEntry, SIGNAL(propertyChange(PropertyChangeEvent*)), rosterEntryUpdateListener,SLOT(propertyChange(PropertyChangeEvent*)));
//  connect(rosterEntry->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), rosterEntryUpdateListener, SLOT(propertyChange(PropertyChangeEvent*)));
  updateDetails();
  //rtable.moveTableViewToSelected();
  int row = Roster::getDefault()->getGroupIndex(model->getRosterGroup(), re);
  QModelIndex index = model->index(row, 0, QModelIndex());
  QModelIndex ixSort = sorter->mapFromSource(index);
  ui->rtable->selectRow(ixSort.row());
 }
 else
 {
  log->warn("Read address " + QString::number(dccAddress) + ", but no such loco in roster"); //"No roster entry found"
    QMessageBox::warning(this, "No roster entry found", "Address " + QString::number(dccAddress) + " was read from the decoder\nbut has not been found in the Roster"/*, JOptionPane.INFORMATION_MESSAGE*/);
 }
}

void RosterFrame::on_togglePower_clicked()
{
 PowerManager* pmgr = ( PowerManager*)InstanceManager::getDefault("PowerManager");
 if(pmgr->getPower() == PowerManager::ON)
  pmgr->setPower(PowerManager::OFF);
 else
  pmgr->setPower(PowerManager::ON);
}

void RosterFrame::on_actionDelete_Loco_triggered()
{
 Roster* roster = Roster::getDefault();
 QString rosterGroup = Roster::getDefault()->getDefaultRosterGroup();
 QVector<RosterEntry*> entries;
 // rosterGroup may legitimately be NULL
 // but getProperty returns NULL if the property cannot be found, so
 // we test that the property exists before attempting to get its value
// if (Beans.hasProperty(wi, "selectedRosterGroup"))
// {
//    rosterGroup = (QString) Beans.getProperty(wi, "selectedRosterGroup");
// }
// if (Beans.hasProperty(wi, "selectedRosterEntries")) {
//    entries = (RosterEntry[]) Beans.getProperty(wi, "selectedRosterEntries");
// }
// else
 {
  entries = selectRosterEntry(rosterGroup);
 }
 if (entries.isEmpty())
 {
    return;
 }
 // get parent object if there is one
 //Component parent = NULL;
 //if ( event.getSource() instanceof Component) parent = (Component)event.getSource();

 // find the file for the selected entry
 foreach (RosterEntry* re,  entries)
 {
  QString filename = roster->fileFromTitle(re->titleString());
  QString fullFilename = LocoFile::getFileLocation() + filename;
  if (log->isDebugEnabled())
  {
   log->debug("resolves to \"" + filename + "\", \"" + fullFilename + "\"");
  }

  // prompt for one last chance
  if (rosterGroup == "")
  {
//  if (!userOK(re->titleString(), filename, fullFilename))
//  {
//   return;
//  }
      switch(QMessageBox::question(this, tr("Delete entry (%1)?").arg(filename), tr("Delete entry (%1) and file (%2)?").arg(filename).arg(fullFilename)))
      {
       case QMessageBox::No:
        return;
      default:
       break;
      }

  // delete it from roster
        roster->removeEntry(re);
 }
 else
  {
   QString group = Roster::getRosterGroupProperty(rosterGroup);
   re->deleteAttribute(group);
   re->updateFile();
  }
  Roster::getDefault()->writeRoster();

  // backup the file & delete it
  if (rosterGroup == "")
  {
   try
   {
            // ensure preferences will be found
    FileUtil::createDirectory(LocoFile::getFileLocation());

    // do backup
    LocoFile* df = new LocoFile();   // need a dummy object to do this operation in next line
    df->makeBackupFile(LocoFile::getFileLocation() + filename);

    // locate the file and delete
    QFile* f = new QFile(fullFilename);
    if (!f->remove())
    { // delete file and check success
     log->error("failed to delete file \"" + fullFilename + "\"");
    }

   }
   catch (Exception ex)
   {
    log->error("error during locomotive file output: " + ex.msg);
   }
  }
 }
}
/*protected*/ QVector<RosterEntry*> RosterFrame::selectRosterEntry(QString rosterGroup)
{
   // create a dialog to select the roster entry
   //JComboBox selections = new RosterEntryComboBox(rosterGroup);
   QComboBox* selections = new QComboBox();
   Roster* roster = Roster::getDefault();
   QList<RosterEntry*> list = roster->getEntriesInGroup(rosterGroup);
   foreach (RosterEntry* re, list) \
   {
    selections->addItem(re->getId(),VPtr<RosterEntry>::asQVariant(re));
   }

//   int retval = JOptionPane.showOptionDialog(_who,
//                                             "Select one roster entry", "Delete roster entry",
//                                             0, JOptionPane.INFORMATION_MESSAGE, NULL,
//                                             new Object[]{"Cancel", "OK", selections}, NULL );
   OptionsDialog dlg(tr("Delete rosterEntry"), tr("Select one roster entry"), selections,this);
   int rtn = dlg.exec();
   if(rtn == QDialog::Rejected)
       return QVector<RosterEntry*>();
   if(selections->currentIndex() < 0)
       return QVector<RosterEntry*>();

   log->debug("Dialog value  selected "+QString::number(selections->currentIndex())+":"
             +selections->currentText());
   //if (retval != 1) return NULL;
   QVector<RosterEntry*> entries = QVector<RosterEntry*>(1);
   entries.replace(0, (RosterEntry*) VPtr<RosterEntry>::asPtr(selections->itemData(selections->currentIndex())));
   return entries;
}
/**
 * Can provide some mechanism to prompt for user for one
 * last chance to change his/her mind
 * @return true if user says to continue
 */
//bool userOK(String entry, String filename, String fullFileName) {
//    return ( JOptionPane.YES_OPTION ==
//             JOptionPane.showConfirmDialog(_who,
//                    java.text.MessageFormat.format(ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("DeletePrompt"),
//                                    entry,fullFileName),
//                    java.text.MessageFormat.format(ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("DeleteTitle"),
//                                    entry),
//                    JOptionPane.YES_NO_OPTION));
//}

void RosterFrame::propertyChange(PropertyChangeEvent *e)
{
#if 0
 if(e->getPropertyName() == "change")
 {
  QVariant pvOld =e->getOldValue();
  QVariant pvNew =e->getNewValue();
  RosterEntry* re = VPtr<RosterEntry>::asPtr(pvNew);
  //qDebug() << e->getPropertyName();
  for(int row =0; row < rows.count(); row++)
  {
   if(re == rows.at(row));
   {
    updateRow(row,re);
    if(re == this->rosterEntry)
     updateInfo();
    return;
   }
  }
 }
 if(e->getPropertyName() == "delete")
 {
  RosterEntry* re = VPtr<RosterEntry>::asPtr(e->getNewValue());
  for(int row =0; row < rows.count(); row++)
  {
   if(re->getId() == ui->rtable->item(row, 0)->text())
   {
    ui->rtable->removeRow(row);
    rows.remove(row);
    return;
   }
  }
 }
 if(e->getPropertyName() == "add")
 {
  int row = ui->rtable->rowCount();
  ui->rtable->setRowCount(row+1);
  RosterEntry* re = VPtr<RosterEntry>::asPtr(e->getNewValue());
  updateRow(row, re);
  rows.append(re);
  return;
 }
 else
#endif
 if(e->getPropertyName() == "Power")
 {
  PowerManager* pmgr = (PowerManager*)InstanceManager::getDefault("PowerManager");
  if(pmgr->getPower()== PowerManager::ON)
  {
   //parent->togglePower = new QToolButton();
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_green.png") );
   togglePower->setText(tr("Power on"));
  }
  else if (pmgr->getPower()== PowerManager::OFF)
  {
   //parent->togglePower = new QToolButton( );
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_red.png"));
   togglePower->setText(tr("Power off"));
  }
  else
  {
   //parent->togglePower = new QToolButton( );
   togglePower->setIcon(QIcon(":/resources/icons/throttles/power_yellow.png"));
   togglePower->setText(tr("Power unknown"));
  }
 }
 if (e->getPropertyName()==("programmermanager"))
 {
  updateProgrammerStatus(e);
 }
}
void RosterFrame::on_groupChange(PropertyChangeEvent * pce)
{
  prefsMgr->setProperty(getClassName(), RosterGroupsPanel::SELECTED_ROSTER_GROUP, pce->getNewValue().toString());
  setTitle( pce->getNewValue().toString());

  // this is cheating ACK
 if(pce->getNewValue().toString() == "ALL ENTRIES")
  model->setRosterGroup("");
 else
  model->setRosterGroup(pce->getNewValue().toString());
}

void RosterFrame::on_RosterChange(PropertyChangeEvent * e)
{
 if (e->getPropertyName() == ("RosterGroupAdded") && Roster::getDefault()->getRosterGroupList().size() == 1)
 {
  // if the pane is hidden, show it when 1st group is created
  hideGroupsPane(false);
  enableRosterGroupMenuItems(true);
 }
 else if (!ui->rtable->isVisible() && (e->getPropertyName() == ("saved")))
 {
// TODO:    if (firstHelpLabel != NULL) {
//         firstHelpLabel.setVisible(false);
//     }
     ui->rtable->setVisible(true);
     //ui->rtable->resetColumnWidths();
 }
}
#if 0
void  RosterFrame::on_tableWidget_cellChanged(int row, int col)
{
 if(bUpdating) return;
 QTableWidgetItem* item = ui->rtable->item(row, col);
 RosterEntry* re = rows.at(row);
 if(item == NULL) return;
 switch(col)
 {
 case 0:  // id
  re->setId(item->text());
  break;
 case 1:
 case 2:
  break;
 case 4:  // road name
  re->setRoadName(item->text());
  break;
 case 5:  //road number
  re->setRoadNumber(item->text());
  break;
 case 6: // manufacturer
  re->setMfg(item->text());
  break;
 case 7: // model
  re->setModel(item->text());
  break;
 case 8: // owner
  re->setOwner(item->text());
  break;
default:
  break;

 }
}
#endif
void RosterFrame::on_tableClicked(QModelIndex index)
{
 QModelIndex ix = sorter->mapToSource(index);
 int row = ix.row();
 re = Roster::getDefault()->getGroupEntry(model->getRosterGroup(), row);
 updateDetails();
}

void RosterFrame::On_newLoco_clicked()
{
 PaneNewProgAction* act = new PaneNewProgAction(this);
 act->actionPerformed();
}
/**
 * @param newWindowAction the newWindowAction to set
 */
/*protected*/ void RosterFrame::setNewWindowAction(JmriAbstractAction* newWindowAction) {
    this->newWindowAction = newWindowAction;
    this->groups->setNewWindowMenuAction(newWindowAction);
}
//@Override
/*public*/ void RosterFrame::setTitle(QString title) {
    if (title == NULL || title.isEmpty()) {
        title = Roster::ALLENTRIES;
    }
    if (this->baseTitle != NULL) {
        if (title != (this->baseTitle) && !title.startsWith(this->baseTitle)) {
            JmriJFrame::setTitle(this->baseTitle + ": " + title);
        }
    } else {
        JmriJFrame::setTitle(title);
    }
}

//@Override
/*public*/ QVariant RosterFrame::getProperty(QString key) {
    if (key.toLower() == (RosterGroupSelector::SELECTED_ROSTER_GROUP.toLower())) {
        return getSelectedRosterGroup();
    } else if (key.toLower() == QString("hideSummary").toLower()) {
        return _hideBottomPane;
    }
    // call parent getProperty method to return any properties defined
    // in the class heirarchy.
    return JmriJFrame::getProperty(key);
}
#if 1
RosterEntryUpdateListener::RosterEntryUpdateListener(RosterFrame* f)
{
 this->f = f;
 connect(Roster::getDefault(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

void RosterEntryUpdateListener::propertyChange(PropertyChangeEvent * e)
{
// if(e->getPropertyName() == "add")
// {
//  int row = f->ui->rtable->model()-> rowCount();
//  //f->ui->rtable->setRowCount(row++);
//  RosterEntry* re = VPtr<RosterEntry>::asPtr(e->getNewValue());
//  f->rows.append(re);
//  f->updateRow(row, re);
// }
// else if(e->getPropertyName() == "remove")
// {
//  RosterEntry* re = VPtr<RosterEntry>::asPtr(e->getNewValue());
//  for(int i = 0; i < f->rows.count(); i++)
//  {
//   if(f->rows.at(i) == re)
//   {
//    f->ui->rtable->removeRow(i);
//    f->rows.remove(i);
//    break;
//   }
//  }
// }
// else if(e->getPropertyName() == "change")
// {
//  RosterEntry* re = VPtr<RosterEntry>::asPtr(e->getNewValue());
//  for(int i = 0; i < f->rows.count(); i++)
//  {
//   if(f->rows.at(i) == re)
//   {
//    f->updateRow(i, re);
//   }
//  }
// }
 f->updateDetails();
}
#endif
/*protected*/ void  RosterFrame::buildGUI(QString menubarFile, QString toolbarFile)
{
    //configureFrame();
// slotTable = new QHash<QString, NoParm>();
// slotTable->insert("quit", (NoParm)&RosterFrame::On_Quit);

 addMainMenuBar(menubarFile );
 addMainToolBar(toolbarFile);
 addMainStatusBar();
 additionsToToolBar();
}

/*protected*/ void  RosterFrame::addMainMenuBar(QString menuFile)
{
 if (menuFile == NULL)
 {
  return;
 }

 QList<QMenu*> menus = JMenuUtil::loadMenu(menuFile, (WindowInterface*)this, this);
 if(menus.count() > 0)
 {
  foreach (QMenu* j,  menus)
  {
   if(j != NULL)
   {
    menuBar->addMenu(j);
    log->debug(tr("menu '%1'added ").arg(j->title()));
   }
  }

  //ui->setMenuBar(menuBar);
  this->setMenuBar(menuBar);
 }
}

/*public*/ QMenuBar*  RosterFrame::getMenu()
{
 return menuBar;
}

/*protected*/ void  RosterFrame::addMainToolBar(QString toolBarFile)
{
 if (toolBarFile == NULL)
 {
  return;
 }
 QMainWindow::removeToolBar(ui->toolBar);
 ui->toolBar = NULL;
 QMainWindow::addToolBar(ui->toolBar = JToolBarUtil::loadToolBar(toolBarFile, (WindowInterface*)this, this));


 connect(ui->toolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(on_currentMapped(QAction*)));

    // this takes up space at the top until pulled to floating
//    add(toolBar, BorderLayout.NORTH);
}

///*abstract*/ /*public*/ void  RosterFrame::remoteCalls(QStringList args) {}

/**
 * @param allowQuit Set state to either close JMRI or just the roster window
 */
/*public*/ void  RosterFrame::setAllowQuit(bool _allowQuit)
{
 allowQuit(_allowQuit);
}

void RosterFrame::additionsToToolBar()
{
    //This value may return null if the DP3 window has been called from a the traditional JMRI menu frame
    if (Apps3::buttonSpace() != NULL)
    {
        //((QToolBar*)getToolBar())->addWidget(Apps3::buttonSpace());
     ui->toolBar->addWidget(Apps3::buttonSpace());
    }
    //((QToolBar*)getToolBar())->addWidget(new LargePowerManagerButton(true));
    ui->toolBar->addWidget(new LargePowerManagerButton(true));
    //((QToolBar*)getToolBar())->addWidget(modePanel);
    ui->toolBar->addWidget(modePanel = new ProgServiceModeComboBox());
}

/**
* For use when the DP3 window is called from another JMRI instance, set
* this to prevent the DP3 from shutting down JMRI when the window is
* closed.
*/
/*protected*/ void  RosterFrame::allowQuit(bool quitAllowed)
{
 if (_allowQuit != quitAllowed)
 {
  newWindowAction = NULL;
  _allowQuit = quitAllowed;
  groups->setNewWindowMenuAction(this->getNewWindowAction());
 }

 firePropertyChange("quit", "setEnabled", _allowQuit);
 //if we are not allowing quit, ie opened from JMRI classic
 //then we must at least allow the window to be closed
 if (!_allowQuit)
 {
  firePropertyChange("closewindow", "setEnabled", true);
 }
}

/*protected*/ void RosterFrame::addMainStatusBar() {
#if 0
    ui->statusBar.setLayout(new FlowLayout(FlowLayout.LEFT, 2, 0));
    ui->statusBar.setBorder(new BevelBorder(BevelBorder.LOWERED));

    ui->statusBox = Box.createHorizontalBox();
    ui->statusBox.add(Box.createHorizontalGlue());
    statusBar.add(statusBox);
    add(statusBar, BorderLayout.SOUTH);
#endif
}
/**
 * @return the newWindowAction
 */
/*protected*/ JmriAbstractAction* RosterFrame::getNewWindowAction() {
    if (newWindowAction == NULL) {
        newWindowAction = new RosterFrameAction("newWindow", (WindowInterface*)this, _allowQuit);
    }
    return newWindowAction;
}
/*protected*/ void RosterFrame::helpMenu(QMenuBar* menuBar, /*final*/ JFrame* /*frame*/)
{
//    try {
        // create menu and standard items
        QMenu* helpMenu = HelpUtil::makeHelpMenu("package.apps.gui3.dp3.DecoderPro3", true,this);
        // tell help to use default browser for external types
        //SwingHelpUtilities.setContentViewerUI("jmri.util.ExternalLinkContentViewerUI");
        // use as main help menu
        menuBar->addMenu(helpMenu);
//    } catch (Throwable e3) {
//        log.error("Unexpected error creating help: " + e3);
//    }
}

/*protected*/ ProgrammerConfigManager* RosterFrame::getProgrammerConfigManager() {
    return (ProgrammerConfigManager*)InstanceManager::getDefault("ProgrammerConfigManager");
}

void RosterFrame::handleQuit(QCloseEvent* e)
{
 if (e != NULL && frameInstances.size() == 1)
 {
  /*final*/ QString rememberWindowClose = this->getClassName() + ".closeDP3prompt";
  if (!prefsMgr->getSimplePreferenceState(rememberWindowClose))
  {
   QWidget* message = new QWidget();
   QLabel* question = new QLabel(tr("Closing this window will quit the program. Close?"));
   /*final*/ QCheckBox* remember = new QCheckBox(tr("Remember this setting for next time?"));
   QFont f = remember->font();
   f.setPointSizeF(10.0);
   remember->setFont(f);
   QBoxLayout* msgLayout;
   message->setLayout(msgLayout =new QVBoxLayout); //(message, BoxLayout.Y_AXIS));
   msgLayout->addWidget(question);
   msgLayout->addWidget(remember);
//      int result = JOptionPane.showConfirmDialog(NULL,
//              message,
//              tr("MessageShortCloseWarning"),
//              JOptionPane.YES_NO_OPTION);
   QMessageBox* box = new QMessageBox();
   box->setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
   box->setDefaultButton(QMessageBox::No);
   box->layout()->addWidget(message);
   int result = box->exec();
   if (remember->isChecked())
   {
    prefsMgr->setSimplePreferenceState(rememberWindowClose, true);
   }
   if (result == QMessageBox::Yes)
   {
    AppsBase::handleQuit();
   }
  }
  else
  {
   AppsBase::handleQuit();
  }
 }
 else if (frameInstances.size() > 1)
 {
  /*final*/ QString rememberWindowClose = this->getClassName() + ".closeMultipleDP3prompt";
  if (!prefsMgr->getSimplePreferenceState(rememberWindowClose))
  {
   QWidget* message = new QWidget();
   QLabel* question = new QLabel(tr("You have Multiple Roster Windows Open. Are you sure that you want to quit?"));
   /*final*/ QCheckBox* remember = new QCheckBox(tr("Remember Setting"));
   QFont f = remember->font();
   f.setPointSizeF(10.0);
   remember->setFont(f);
   QBoxLayout* msgLayout;
   message->setLayout(msgLayout =new QVBoxLayout); //(message, BoxLayout.Y_AXIS));
   msgLayout->addWidget(question);
   msgLayout->addWidget(remember);
//   int result = JOptionPane.showConfirmDialog(NULL,
//           message,
//           tr("MessageShortCloseWarning"),
//           JOptionPane.YES_NO_OPTION);
   QMessageBox* box = new QMessageBox();
   box->setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
   box->setDefaultButton(QMessageBox::No);
   box->layout()->addWidget(message);
   int result = box->exec();
   if (remember->isChecked())
   {
    prefsMgr->setSimplePreferenceState(rememberWindowClose, true);
   }
   if (result == QMessageBox::Yes)
   {
    AppsBase::handleQuit();
   }
  }
  else
  {
   AppsBase::handleQuit();
  }
//closeWindow(NULL);
 }
}
QString /*private*/ RosterFrame::getClassName()
{
 return "jmri.jmrit.roster.swing.RosterFrame";
}

void RosterFrame::saveWindowDetails()
{
 prefsMgr->setSimplePreferenceState(this->getClassName() + ".hideSummary", _hideBottomPane);
 prefsMgr->setSimplePreferenceState(this->getClassName()  + ".hideGroups", _hideGroups);
 prefsMgr->setSimplePreferenceState(this->getClassName() + ".hideRosterImage", _hideRosterImage);
// p.setProperty(getWindowFrameRef(), "selectedRosterGroup", groups.getSelectedRosterGroup());
 QString selectedProgMode = "edit";
 if (ui->service->isChecked())
 {
  selectedProgMode = "service";
 }
 if (ui->ops->isChecked()) {
     selectedProgMode = "ops";
 }
 prefsMgr->setProperty(getWindowFrameRef(), "selectedProgrammer", selectedProgMode);
 //Method to save table sort, width and column order status
 QString rostertableref = getWindowFrameRef() + ":roster";
#if 0 // TODO: ?? maybe implement XTableColumn model?
 XTableColumnModel tcm = rtable.getXTableColumnModel();
 Enumeration<TableColumn> en = tcm.getColumns(false);
 while (en.hasMoreElements()) {
     TableColumn tc = en.nextElement();

     try {
         String columnName = (String) tc.getHeaderValue();
         int index = tcm.getColumnIndex(tc.getIdentifier(), false);
         p.setTableColumnPreferences(rostertableref, columnName, index, tc.getPreferredWidth(), rtable.getModel().getSortingStatus(tc.getModelIndex()), !tcm.isColumnVisible(tc));
     } catch (Exception e) {
         log.warn("unable to store settings for table column " + tc.getHeaderValue(), e);
     }
 }
 for(int index =0; index < ui->rtable->columnCount(); index++)
 {
  QString columnName = ui->rtable->horizontalHeader()->model()->headerData(index,Qt::Horizontal).toString();
  prefsMgr->setTableColumnPreferences(rostertableref, columnName, index, ui->rtable->columnWidth(index),index, !ui->rtable->isColumnHidden(index));
 }
 if (rosterGroupSplitPane.getDividerLocation() > 2) {
     p.setProperty(getWindowFrameRef(), "rosterGroupPaneDividerLocation", rosterGroupSplitPane.getDividerLocation());
 } else if (groupSplitPaneLocation > 2) {
     p.setProperty(getWindowFrameRef(), "rosterGroupPaneDividerLocation", groupSplitPaneLocation);
 }
#endif
}

//@TODO The disabling of the closewindow menu item doesn't quite work as this in only invoked on the closing window, and not the one that is left
//    void closeWindow(WindowEvent e) {
void RosterFrame::closeEvent(QCloseEvent * e)
{
 saveWindowDetails();
 //Save any changes made in the roster entry details
 Roster::getDefault()->writeRoster();
 if (_allowQuit && frameInstances.size() == 1)
 {
  handleQuit(e);
 }
 else
 {
  //As we are not the last window open or we are not allowed to quit the application then we will just close the current window
  frameInstances.removeOne(this);
  JmriJFrame::windowClosing(e);
  if ((frameInstances.size() == 1) && (_allowQuit)) {
      frameInstances.at(0)->firePropertyChange("closewindow", "setEnabled", false);
  }
  dispose();
 }
}
void RosterFrame::On_splitterMoved(int pos, int)
{

 int current = /*sourceSplitPane.getDividerLocation() + sourceSplitPane.getDividerSize()*/pos;
 int panesize = /*(int) (sourceSplitPane.getSize().getHeight())*/ ui->splitter->size().height();
 if (panesize - current <= 1) {
     _hideBottomPane = true;
 } else {
     _hideBottomPane = false;
 }
     //p.setSimplePreferenceState(DecoderPro3Window.class.getName()+".hideSummary",hideSummary);
 QList<int> splitter2Sizes = ui->splitter->sizes();
 QString str;
 foreach (int i, splitter2Sizes) {
  if(!str.isEmpty())
   str.append(",");
  str.append(QString::number(i));
 }
 prefsMgr->setProperty(getClassName(), "splitterSizes", str);
}

void RosterFrame::On_splitter2Moved(int pos, int)
{

 int current = /*sourceSplitPane.getDividerLocation() + sourceSplitPane.getDividerSize()*/pos;
 int panesize = /*(int) (sourceSplitPane.getSize().getHeight())*/ ui->splitter_2->size().height();
 if (panesize - current <= 1) {
     _hideGroups = true;
 } else {
     _hideGroups = false;
 }
     //p.setSimplePreferenceState(DecoderPro3Window.class.getName()+".hideSummary",hideSummary);
 QList<int> splitter2Sizes = ui->splitter_2->sizes();
 QString str;
 foreach (int i, splitter2Sizes)
 {
  if(!str.isEmpty())
   str.append(",");
  str.append(QString::number(i));
 }
 prefsMgr->setProperty(getClassName(), "splitter2Sizes", str);
}

/*protected*/ void RosterFrame::systemsMenu() {
    ActiveSystemsMenu::addItems(getMenu(),this);
    getMenu()->addMenu(new WindowMenu(this));
}
void RosterFrame::On_Quit()
{
 close();
}
/*protected*/ void RosterFrame::exportLoco()
{
 ExportRosterItem* act = new ExportRosterItem(tr("Export"), this, re);
 act->actionPerformed(NULL);
}
/*protected*/ void RosterFrame::copyLoco()
{
    CopyRosterItem* act = new CopyRosterItem("Copy", this, re);
    act->actionPerformed(NULL);
}

/*protected*/ void RosterFrame::printLoco(bool boo)
{
 PrintRosterEntry* pre = new PrintRosterEntry(re, this, "programmers" + File::separator + programmer2 + ".xml");
 pre->printPanes(boo);
}

//Matches the first argument in the array against a locally-known method
//@Override
/*public*/ void RosterFrame::remoteCalls(QStringList args)
{
 QString args0 = args.at(0).toLower();
 args.replace(0, args0);
 if (args.at(0)==("identifyloco"))
 {
  startIdentifyLoco();
 }
 else if (args.at(0)==("printloco"))
 {
  if (checkIfEntrySelected())
  {
   printLoco(false);
  }
 }
 else if (args.at(0)==("printpreviewloco"))
 {
  if (checkIfEntrySelected())
  {
   printLoco(true);
  }
 }
 else if (args.at(0)==("exportloco"))
 {
  if (checkIfEntrySelected())
  {
   exportLoco();
  }
 }
 else if (args.at(0)==("basicprogrammer"))
 {
  if (checkIfEntrySelected())
  {
   startProgrammer(NULL, re, programmer2);
  }
 }
 else if (args.at(0)==("comprehensiveprogrammer"))
 {
  if (checkIfEntrySelected())
  {
      startProgrammer(NULL, re, programmer1);
  }
 } else if (args.at(0)==("editthrottlelabels"))
 {
  if (checkIfEntrySelected())
  {
      startProgrammer(NULL, re, "dp3" + File::separator + "ThrottleLabels");
  }
 } else if (args.at(0)==("editrostermedia"))
 {
  if (checkIfEntrySelected())
  {
      startProgrammer(NULL, re, "dp3" + File::separator + "MediaPane");
  }
 }
 else if (args.at(0)==("hiderosterimage"))
 {
  on_actionHide_Show_Roster_Image_triggered();
 }
 else if (args.at(0)==("summarypane"))
 {
  //hideSummary();
  on_actionHide_Show_Summary_Panel_triggered();
 }
 else if (args.at(0)==("copyloco"))
 {
  if (checkIfEntrySelected())
  {
      copyLoco();
  }
 } else if (args.at(0)==("deleteloco")) // deletefromroster
 {
  if (checkIfEntrySelected())
  {
   //deleteLoco();
   on_actionDelete_Loco_triggered();
  }
 }
 else if (args.at(0)==("setprogservice"))
 {
  //service.setSelected(true);
  ui->service->setChecked(true);
 }
 else if (args.at(0)==("setprogops"))
 {
  //ops.setSelected(true);
  ui->ops->setChecked(true);
 }
 else if (args.at(0)==("setprogedit"))
 {
  //edit.setSelected(true);
  ui->edit->setChecked(true);
 }
 else if (args.at(0)==("groupspane"))
 {
  hideGroups();
 }
 else if (args.at(0)==("quit"))
 {
  saveWindowDetails();
  //handleQuit(new WindowEvent(this, frameInstances.size()));
  handleQuit(new QCloseEvent());

 }
 else if (args.at(0)==("closewindow"))
 {
  //closeWindow(NULL);
  close();
 }
 else if (args.at(0)==("newwindow"))
 {
  newWindow();
 } else if (args.at(0)==("resettablecolumns"))
 {
//     rtable.resetColumnWidths();
 }
 else
 {
  log->error("remote calls method " + args.at(0) + " not found");
 }
}

bool RosterFrame::checkIfEntrySelected()
{
 //if(ui->rtable->selectedItems().isEmpty())
 if(ui->rtable->selectionModel()->selectedRows().isEmpty())
  return false;
 return true;
}

/*protected*/ void RosterFrame::startProgrammer(DecoderFile* decoderFile, RosterEntry* re, QString filename)
{
 if (inStartProgrammer)
 {
  log->debug("Call to start programmer has been called twice when the first call hasn't opened");
  return;
 }
 if (!checkIfEntrySelected())
  return;

 //try
 {
  setCursor(Qt::WaitCursor);
  inStartProgrammer = true;
  QString title = re->getId();
  JFrame* progFrame = NULL;
  if (ui->edit->isChecked())
  {
   progFrame = new PaneProgFrameO1(decoderFile, re, title, FileUtil::getProgramPath()+ File::separator+ "xml" + File::separator + "programmers" + File::separator + filename + ".xml", NULL, false);
//         {
//             /**
//              *
//              */
//             private static final long serialVersionUID = -5406468334024223092L;

//             @Override
//             protected JPanel getModePane() {
//                 return null;
//             }
//         };
  }
  else if (ui->service->isChecked())
  {
   progFrame = new PaneServiceProgFrame(decoderFile, re, title, FileUtil::getProgramPath()+ File::separator+ "xml" + File::separator + "programmers" + File::separator + filename + ".xml", modePanel->getProgrammer());
//   {

//       /**
//        *
//        */
//       private static final long serialVersionUID = 1953980697520737653L;
//   };
  }
  else if (ui->ops->isChecked())
  {
   int address = re->getDccAddress().toInt();
   bool longAddr = re->isLongAddress();
   Programmer* pProg = (Programmer*)((DefaultProgrammerManager*) InstanceManager::getDefault("AddressedProgrammerManager"))->getAddressedProgrammer(longAddr, address);
   progFrame = new PaneOpsProgFrame(decoderFile, re, title, "programmers" + File::separator + filename + ".xml", pProg);
  }
  if (progFrame == NULL)
  {
   return;
  }
  progFrame->adjustSize();
  progFrame->setVisible(true);
 }
// finally
// {
  setCursor(Qt::ArrowCursor);
// }
 inStartProgrammer = false;
}
/*protected*/ void RosterFrame::newWindow()
{
 this->newWindow(this->getNewWindowAction());
}

/*protected*/ void RosterFrame::newWindow(JmriAbstractAction* action)
{
 action->setWindowInterface((WindowInterface*)this);
 action->actionPerformed();
 firePropertyChange("closewindow", "setEnabled", true);
}

void RosterFrame::on_currentMapped(QObject *act)
{
 on_currentMapped((QAction*)act);
}

void RosterFrame::on_currentMapped(QAction *act) //SLOT[]
{
 QStringList l;
 QString p = act->property("current").toString();
 l << p;
 if(!l.isEmpty())
  remoteCalls(l);
}

/*protected*/ void RosterFrame::hideGroups() {
        bool boo = !_hideGroups;
        hideGroupsPane(boo);
    }

    /*public*/ void RosterFrame::hideGroupsPane(bool hide) {
        if (_hideGroups == hide) {
            return;
        }
        _hideGroups = hide;
        if (hide) {
//            groupSplitPaneLocation = rosterGroupSplitPane.getDividerLocation();
//            rosterGroupSplitPane.setDividerLocation(1);
//            rosterGroupSplitPane.getLeftComponent().setMinimumSize(new Dimension());
//            if (Roster.instance().getRosterGroupList().isEmpty()) {
//                rosterGroupSplitPane.setOneTouchExpandable(false);
//                rosterGroupSplitPane.setDividerSize(0);
//            }
         //ui->groupsPlaceholder->hide();
         groups->hide();
        } else {
//            rosterGroupSplitPane.setDividerSize(UIManager.getInt("SplitPane.dividerSize"));
//            rosterGroupSplitPane.setOneTouchExpandable(true);
//            if (groupSplitPaneLocation >= 2) {
//                rosterGroupSplitPane.setDividerLocation(groupSplitPaneLocation);
//            } else {
//                rosterGroupSplitPane.resetToPreferredSizes();
//            }
         //ui->groupsPlaceholder->show();
         groups->show();
        }
     prefsMgr->setSimplePreferenceState(this->getClassName() + ".hideGroups", hide);
    }

/*protected*/ void RosterFrame::hideRosterImage() {
    _hideRosterImage = !_hideRosterImage;
    //p.setSimplePreferenceState(DecoderPro3Window.class.getName()+".hideRosterImage",hideRosterImage);
    if (_hideRosterImage) {
        ui->locoImage->setVisible(false);
    } else {
        ui->locoImage->setVisible(true);
    }
}

/*protected*/ void RosterFrame::hideSummary()
{
 bool boo = !_hideBottomPane;
 hideBottomPane(boo);
}

/*public*/ void RosterFrame::hideBottomPane(bool hide)
{
    if (_hideBottomPane == hide) {
        return;
    }
    _hideBottomPane = hide;
    if (hide) {
//        upDownSplitPane.setDividerLocation(1.0d);
     ui->summaryPanel->hide();
    } else {
//        resetTopToPreferredSizes();
     ui->summaryPanel->show();
    }
}
/*protected*/ void RosterFrame::enableRosterGroupMenuItems(bool enable) {
    firePropertyChange("groupspane", "setEnabled", enable);
    firePropertyChange("grouptable", "setEnabled", enable);
    firePropertyChange("deletegroup", "setEnabled", enable);
}

/**
 * Simple method to change over the programmer buttons.
 * <p>
 * TODO This should be implemented with the buttons in their own class etc.
 * but this will work for now.
 *
 * @param buttonId   1 or 2; use 1 for basic programmer; 2 for comprehensive
 *                   programmer
 * @param programmer name of programmer
 * @param buttonText button title
 */
/*public*/ void RosterFrame::setProgrammerLaunch(int buttonId, QString programmer, QString buttonText) {
    if (buttonId == 1) {
        programmer1 = programmer;
        ui->prog1Button->setText(buttonText);
    } else if (buttonId == 2) {
        programmer2 = programmer;
        prog2Button->setText(buttonText);
    }
}

/*public*/ void RosterFrame::setSelectedRosterGroup(QString rosterGroup) {
    groups->setSelectedRosterGroup(rosterGroup);
}

/*protected*/ void RosterFrame::showPopup(QPoint pos)
{
 QModelIndex index=ui->rtable->indexAt(pos);

//         if (!rtable.getTable().isRowSelected(row)) {
//             rtable.getTable().changeSelection(row, 0, false, false);
//         }
 QModelIndexList list = ui->rtable->selectionModel()->selectedRows();
 int row = ui->rtable->rowAt(pos.y());
 bool bSelected = false;
 QModelIndex selectedIndex = QModelIndex();
 foreach (QModelIndex ix, list)
 {
  if(ix.row() == row)
  {
   bSelected = true;
   selectedIndex = ix;
   break;
  }
 }
 if(!bSelected)
 {
  ui->rtable->selectRow(row);
 }
 {
  QModelIndex ix = sorter->mapToSource(sorter->index(row,0));
  int row = ix.row();
  re = Roster::getDefault()->getGroupEntry(model->getRosterGroup(), row);
  updateDetails();
}
     QMenu* popupMenu = new QMenu();
     QAction* menuItem = new QAction("Program", this);
     QSignalMapper* mapper = new QSignalMapper();
     connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(actionPerformed(QObject*)));

//        menuItem.addActionListener((ActionEvent e1) -> {
//            startProgrammer(null, re, programmer1);
//        });
     menuItem->setProperty("action", "comprehensiveprogrammer");
     mapper->setMapping(menuItem, menuItem);
     connect(menuItem, SIGNAL(triggered(bool)), mapper, SLOT(map()));
     if (re == NULL) {
         menuItem->setEnabled(false);
     }
     popupMenu->addAction(menuItem);

     QActionGroup* group = new QActionGroup(this);
     group->addAction(contextService);
     group->addAction(contextOps);
     group->addAction(contextEdit);
     QMenu* progMenu = new QMenu("Programmer type");
//        contextService.addActionListener((ActionEvent e1) -> {
//            service.setSelected(true);
//            updateProgMode();
//        });
     progMenu->addAction(contextService);
     mapper->setMapping(contextService, contextService);
     connect(contextService, SIGNAL(triggered(bool)), mapper, SLOT(map()));
//        contextOps.addActionListener((ActionEvent e1) -> {
//            ops.setSelected(true);
//            updateProgMode();
//        });
     progMenu->addAction(contextOps);
     mapper->setMapping(contextOps, contextOps);
     connect(contextOps, SIGNAL(triggered(bool)), mapper, SLOT(map()));

//        contextEdit.addActionListener((ActionEvent e1) -> {
//            edit.setSelected(true);
//            updateProgMode();
//        });
     if (ui->service->isChecked()) {
         contextService->setChecked(true);
     } else if (ui->ops->isChecked()) {
         contextOps->setChecked(true);
     } else {
         contextEdit->setChecked(true);
     }
     progMenu->addAction(contextEdit);
     mapper->setMapping(contextEdit, contextEdit);
     connect(contextEdit, SIGNAL(triggered(bool)), mapper, SLOT(map()));
     popupMenu->addMenu(progMenu);
     popupMenu->addSeparator();
     menuItem = new QAction("Labels and Media",this);
//        menuItem.addActionListener((ActionEvent e1) -> {
     connect(menuItem, &QAction::triggered, [=]{
            editMediaButton();
        });
     popupMenu->addAction(menuItem);
     menuItem = new QAction("Throttle", this);
     menuItem->setProperty("action", "throttle");
//        menuItem.addActionListener((ActionEvent e1) -> {
     connect(menuItem, &QAction::triggered, [=] {
            ThrottleWindow* tf = ThrottleFrameManager::instance()->createThrottleFrame();
            tf->toFront();
            tf->getAddressPanel()->getRosterEntrySelector()->setSelectedRosterGroup(getSelectedRosterGroup());
            tf->getAddressPanel()->setRosterEntry(re);
        });
     if (re == NULL) {
         menuItem->setEnabled(false);
     }
     popupMenu->addAction(menuItem);
     popupMenu->addSeparator();


     menuItem = new QAction(tr("Print Entry..."),this);
     //menuItem.addActionListener((ActionEvent e1) -> printLoco(false));
     connect(menuItem, &QAction::triggered, [=] {printLoco(false);});
     if (re == nullptr) {
         menuItem->setEnabled(false);
     }
     popupMenu->addAction(menuItem);
     menuItem = new QAction(tr("Preview Entry..."));
     //menuItem.addActionListener((ActionEvent e1) -> printLoco(true));
     connect(menuItem, &QAction::triggered, [=]{printLoco(true);});
     if (re == nullptr) {
         menuItem->setEnabled(false);
     }
     popupMenu->addAction(menuItem);
     popupMenu->addSeparator();

     menuItem = new QAction("Duplicate", this);
//        menuItem.addActionListener((ActionEvent e1) -> {
//            copyLoco();
//        });
     menuItem->setProperty("action", "duplicate");
     mapper->setMapping(menuItem, menuItem);
     connect(menuItem, SIGNAL(triggered(bool)), mapper, SLOT(map()));
     if (re == NULL) {
         menuItem->setEnabled(false);
     }
     popupMenu->addAction(menuItem);
     menuItem = new QAction((this->getSelectedRosterGroup() != "" ? tr("Delete From Group") : tr("Delete From Roster")),this); // NOI18N
//        menuItem.addActionListener((ActionEvent e1) -> {
//            deleteLoco();
//        });
     mapper->setMapping(menuItem, menuItem);
     popupMenu->addAction(menuItem);
     menuItem->setEnabled(this->getSelectedRosterEntries()->length() > 0);
     menuItem->setProperty("action", this->getSelectedRosterGroup() != "" ? "deletefromgroup" : "deletefromroster");
     connect(menuItem, SIGNAL(triggered(bool)), mapper, SLOT(map()));
     popupMenu->exec(QCursor::pos());
}

void RosterFrame::actionPerformed(QObject* o)
{
 QAction* act = (QAction*)o;
 QString action = act->property("action").toString();
 Q_ASSERT(!action.isEmpty());
 QStringList l = QStringList();
 l << action;
 remoteCalls(l);
}

/*public*/ QList<RosterEntry*>* RosterFrame::getSelectedRosterEntries()
{
 if (selectedRosterEntries == NULL)
 {
  //int[] rows = dataTable.getSelectedRows();
  QModelIndexList rows = ui->rtable->selectionModel()->selectedRows();
  selectedRosterEntries = new QList<RosterEntry*>(); //[rows.length()];
  for (int idx = 0; idx < rows.length(); idx++)
  {
   QModelIndex sourceIx = sorter->mapToSource(rows.at(idx));
   QModelIndex ix = model->index(sourceIx.row(), sourceIx.column());
   selectedRosterEntries->append( Roster::getDefault()->getEntryForId(model->data(ix,Qt::DisplayRole).toString()));
  }
 }
 return selectedRosterEntries;
}
/*public*/ QString RosterFrame::getSelectedRosterGroup()
{
    return groups->getSelectedRosterGroup();
}

void RosterFrame::editMediaButton() {
    //Because of the way that programmers work, we need to use edit mode for displaying the media pane, so that the read/write buttons do not appear.
    bool serviceSelected = ui->service->isChecked();
    bool opsSelected = ui->ops->isChecked();
    ui->edit->setChecked(true);
    startProgrammer(NULL, re, "dp3" + File::separator + "MediaPane");
    ui->service->setChecked(serviceSelected);
    ui->ops->setChecked(opsSelected);
}

/*protected*/ void RosterFrame::deleteLoco() {
    DeleteRosterItemAction* act = new DeleteRosterItemAction("Delete", (WindowInterface*) this);
    act->actionPerformed(0);
}
