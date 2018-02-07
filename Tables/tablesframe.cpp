#include "tablesframe.h"
#include "ui_tablesframe.h"
#include "../LayoutEditor/jmrijframe.h"
#include "../LayoutEditor/savemenu.h"
#include "logixtableaction.h"
#include "../LayoutEditor/maintenance.h"
#include <QAction>
#include "sectiontableaction.h"
#include "audiotablepanel.h"
#include "audiotableaction.h"
//#include "audiowidget.h"
#include "turnouttabletabaction.h"
#include "sensortabletabaction.h"

TablesFrame::TablesFrame(QString type, QWidget *parent) :
    JmriJFrame(parent),
    ui(new Ui::TablesFrame)
{
 ui->setupUi(this);
 jFrame = (JmriJFrame*)this;
 //jFrame->init();

 currWidget = NULL;
 toWidget = NULL;
 sensorWidget = NULL;
// reporterWidget = NULL;
// memoryWidget = NULL;
// blockWidget = NULL;
// idTagsWidget = NULL;
// routeWidget = NULL;
// lightWidget = NULL;
// logixWidget = NULL;
// lRouteWidget = NULL;
// signalHeadWidget = NULL;
// signalMastWidget = NULL;
// signalGroupsWidget = NULL;
// signalMastLogicWidget = NULL;
// sectionWidget = NULL;
// transitWidget = NULL;
 audioTablePanel = NULL;
 //audioWidget = NULL;
 audioTableAction = NULL;
 fileMenu = NULL;
 viewMenu = NULL;
 optionsMenu = NULL;
 windowMenu = NULL;
 helpMenu = NULL;
 toWidget = NULL;
 curType = QString();
 setupType(type);
}

TablesFrame::~TablesFrame()
{
 delete ui;
}

QMenuBar* TablesFrame::getMenuBar() {return ui->menubar;}

void TablesFrame::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem */*previous*/)
{
  menuBar()->clear();

 setupType(current->text());

}
void TablesFrame::setupType(QString type)
{
 if(currWidget != NULL)
 {
  currWidget->setHidden(true);
 }
 if(type == tr("Turnouts"))
 {
  defaultsMenu = new QAction(tr("Defaults..."),this);

  if(toWidget == NULL)
  {
   //toWidget = new TurnoutWidget(this);
   ttact =  new TurnoutTableTabAction(this);
//      act->createModel();
    toWidget = ttact->getPane();

    //ui->menubar->clear();
    ttact->setCurrFrame((BeanTableFrame*)this);
//    act->buildMenus((BeanTableFrame*)this);
//    act->setMenuBar((BeanTableFrame*)this);
    toWidget->setProperty("type", QVariant("BeanTableFrame"));

//      act->setCurrFrame(toWidget);
//      act->addToFrame(toWidget);
   ui->splitter->insertWidget(1,toWidget);
  }
//  fileMenu = new QMenu(tr("File"));
//  SaveMenu* saveMenu = new SaveMenu();
//  QMenu* opsMenu = new QMenu(tr("Automation"));
//  QAction* item = new QAction(tr("Edit..."), this);
//  connect(item, SIGNAL(triggered()), toWidget, SLOT(on_automation_triggered()));
//  opsMenu->addAction(item);
//  speedMenu = new QMenu(tr("Speeds"));
//  speedMenu->addAction(defaultsMenu);
//  connect(defaultsMenu, SIGNAL(triggered()), toWidget, SLOT(on_defaultSpeeds_triggered()));
//  fileMenu->addMenu(saveMenu);
//  ui->menubar->addMenu(fileMenu);
//  ui->menubar->addMenu(createViewMenu());
//  ui->menubar->addMenu(opsMenu);
//  ui->menubar->addMenu(speedMenu);
//  jFrame->addHelpMenu("package.jmri.jmrit.beantable.TurnoutTable", true);
  menuBar()->clear();
  ttact->buildMenus((BeanTableFrame*)this);
  ttact->setMenuBar((BeanTableFrame*)this);

  // TODO: speed menu and automation menu
  this->curType = type;
  toWidget->show();
  currWidget = toWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(0);
  return;
 }
 else if(type == tr("Sensors"))
 {
  if(sensorWidget == NULL)
  {
   sensorWidget = new SensorWidget(this);
   //stAct =  new SensorTableTabAction(this);
   //sensorWidget = stAct->getPane();
   //stAct->setCurrFrame((BeanTableFrame*)this);
   ui->splitter->insertWidget(1, sensorWidget);
  }
//  stAct->buildMenus((BeanTableFrame*)this);
//  stAct->setMenuBar((BeanTableFrame*)this);

  fileMenu = new QMenu(tr("File"));
  QMenu* debounceMenu = new QMenu(tr("Debounce"));
  QAction* defaultsAct = new QAction(tr("Defaults..."),this);
  connect(defaultsAct, SIGNAL(triggered()), sensorWidget, SLOT(setDefaults_triggered()));
  debounceMenu->addAction(defaultsAct);
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  ui->menubar->addMenu(debounceMenu);
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.SensorTable", true);
  sensorWidget->show();
  this->curType = type;
  currWidget = sensorWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(1);
  return;
 }
 else if(type == tr("Lights"))
 {
  if(lightWidget == NULL)
  {
   lightWidget = new LightWidget(this);
   ui->splitter->insertWidget(1, lightWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.LightTable", true);lightWidget->show();
  this->curType = type;
  currWidget = lightWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(2);

  return;
 }
 else if(type == tr("Signal Heads"))
 {
  if(signalHeadWidget == NULL)
  {
   signalHeadWidget = new SignalHeadWidget(this);
   ui->splitter->insertWidget(1, signalHeadWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.SignalHeadTable", true);signalHeadWidget->show();
  this->curType = type;
  currWidget = signalHeadWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(3);

  return;
 }
 else if(type == tr("Signal Masts"))
 {
  if(signalMastWidget == NULL)
  {
   signalMastWidget = new SignalMastWidget(this);
   ui->splitter->insertWidget(1, signalMastWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.SignalMastTable", true);signalMastWidget->show();
  this->curType = type;
  currWidget = signalMastWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(4);

  return;
 }
 else if(type == tr("Signal Groups"))
 {
  if(signalGroupsWidget == NULL)
  {
   signalGroupsWidget = new SignalGroupsWidget(this);
   ui->splitter->insertWidget(1, signalGroupsWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.SignalGroupTable", true);signalGroupsWidget->show();
  this->curType = type;
  currWidget = signalGroupsWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(5);
  return;
 }
 else if(type == tr("Signal Mast Logic"))
 {
  if(signalMastLogicWidget == NULL)
  {
   signalMastLogicWidget = new SignalMastLogicWidget(this);
   ui->splitter->insertWidget(1, signalMastLogicWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.SignalMastLogicTable", true);signalMastLogicWidget->show();
  this->curType = type;
  currWidget = signalMastLogicWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(6);
  return;
 }
 else if(type == tr("Reporters"))
 {
  if(reporterWidget == NULL)
  {
   reporterWidget = new ReporterWidget(this);
   ui->splitter->insertWidget(1, reporterWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.ReporterTable", true);reporterWidget->show();
  this->curType = type;
  currWidget = reporterWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(7);
  return;
 }
 else if(type == tr("Blocks"))
 {
  if(blockWidget == NULL)
  {
   blockWidget = new BlockWidget(this);
   ui->splitter->insertWidget(1, blockWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.BlockTable", true);blockWidget->show();
  this->curType = type;
  currWidget = blockWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(12);
  return;
 }
 else if(type == tr("Memory Variables"))
 {
  if(memoryWidget == NULL)
  {
   memoryWidget = new MemoryWidget(this);
   ui->splitter->insertWidget(1, memoryWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.MemoryTable", true);memoryWidget->show();
  this->curType = type;
  currWidget = memoryWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(8);
  return;
 }
 else if(type == tr("Id Tags"))
 {
  if(idTagsWidget == NULL)
  {
   idTagsWidget = new IdTagsWidget(this);
   ui->splitter->insertWidget(1, idTagsWidget);
  }
  idTagsWidget->show();
  this->curType = type;
  currWidget = idTagsWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(16);
  return;
 }
 else if(type == tr("Routes"))
 {
  if(routeWidget == NULL)
  {
   routeWidget = new RouteWidget(this);
   ui->splitter->insertWidget(1, routeWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.RouteTable", true);routeWidget->show();
  this->curType = type;
  currWidget = routeWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(9);
  return;
 }
 else if(type == tr("LRoutes"))
 {
  if(lRouteWidget == NULL)
  {
   lRouteWidget = new LRouteWidget(this);
   ui->splitter->insertWidget(1, lRouteWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.LRouteTable", true);
  lRouteWidget->show();
  this->curType = type;
  currWidget = lRouteWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(10);
  return;
 }
 else if(type == tr("Logix"))
 {
  if(logixWidget == NULL)
  {
   logixWidget = new LogixWidget(this);
   ui->splitter->insertWidget(1, logixWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  optionsMenu = new QMenu(tr("Options"));
  QActionGroup* grp = new QActionGroup(this);
  QAction* act = new QAction(tr("Enable All Logix"),this);
  grp->addAction(act);
  act->setCheckable(true);
  act->setChecked(true);
  optionsMenu->addAction(act);
  connect(act, SIGNAL(toggled(bool)), this, SLOT(on_logixOptions_triggered(bool)));
  act = new QAction(tr("Disable All Logix"), this);
  grp->addAction(act);
  act->setCheckable(true);
  optionsMenu->addAction(act);
  ui->menubar->addMenu(optionsMenu);
  toolsMenu = new QMenu(tr("Tools"));
  act = new QAction(tr("Open Picklist Tables"), this);
  connect(act, SIGNAL(triggered()), this, SLOT(on_openPickListTables()));
  toolsMenu->addAction(act);
  act = new QAction(tr("Find Orphaned Items"), this);
  connect(act, SIGNAL(triggered()), this, SLOT(on_findOrphans_triggered()));
  toolsMenu->addAction(act);
  act = new QAction(tr("Find Empty Conditionals"), this);
  connect(act, SIGNAL(triggered()), this, SLOT(on_findEmpty_triggered()));
  toolsMenu->addAction(act);
  act = new QAction(tr("Find Cross References"),this);
  connect(act, SIGNAL(triggered()), logixWidget->logixTableAction(), SLOT(crossReference_requested()));
  toolsMenu->addAction(act);
  ui->menubar->addMenu(toolsMenu);
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.LogixTable", true);
  logixWidget->show();
  this->curType = type;
  currWidget = logixWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(11);
  return;
 }
 else if(type == tr("Sections"))
 {
  if(sectionWidget == NULL)
  {
   sectionWidget = new SectionWidget(this);
   ui->splitter->insertWidget(1, sectionWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  // TODO: add tools menu
  ui->menubar->addMenu(sectionWidget->act->createToolsMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.SectionTable", true);
  sectionWidget->show();
  this->curType = type;
  currWidget = sectionWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(13);
  return;
 }
 else if(type == tr("Transits"))
 {
  if(transitWidget == NULL)
  {
   transitWidget = new TransitWidget(this);
   ui->splitter->insertWidget(1, transitWidget);
  }
  fileMenu = new QMenu(tr("File"));
  SaveMenu* saveMenu = new SaveMenu();
  fileMenu->addMenu(saveMenu);
  ui->menubar->addMenu(fileMenu);
  ui->menubar->addMenu(createViewMenu());
  jFrame->addHelpMenu("package.jmri.jmrit.beantable.TransitTable", true);
  transitWidget->show();
  this->curType = type;
  currWidget = transitWidget;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(14);
  return;
 }
 else if(type == tr("Audio"))
 {
  //if(audioWidget == NULL)
  if(audioTableAction == NULL)
  {
   //audioWidget = new AudioWidget;
   audioTableAction = new AudioTableAction(this);
   audioTablePanel = (AudioTablePanel*)audioTableAction->getPanel();
   //audioWidget->setPanel(audioTablePanel);
   QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   sizePolicy.setHorizontalStretch(0);
   sizePolicy.setVerticalStretch(0);
   sizePolicy.setHeightForWidth(audioTablePanel->sizePolicy().hasHeightForWidth());
   audioTablePanel->setSizePolicy(sizePolicy);
//   connect(audioWidget->addSourceButton(), SIGNAL(clicked()), audioTableAction, SLOT(addSourcePressed()));
//   connect(audioWidget->addBufferButton(), SIGNAL(clicked()), audioTableAction, SLOT(addBufferPressed()));
   audioTableAction->addToFrame(NULL);
   ui->splitter->insertWidget(1, audioTablePanel);
  }
  audioTablePanel->show();
  this->curType = type;
  currWidget = audioTablePanel;
  setWindowTitle(curType);
  ui->listWidget->setCurrentRow(15);
  return;
 }
 else
  Logger::error(tr("Unrecognized table type '%1'").arg(type));
 setWindowTitle(curType);
}

QMenu* TablesFrame::createViewMenu()
{
 QMenu* menu = new QMenu("View");
 QActionGroup* grp = new QActionGroup(this);
 QAction* act = new QAction("Turnouts", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Sensors", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Lights", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Signal Heads", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Signal Masts", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Signal Groups", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Signal Mast Logic", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Reporters", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Memory Variables", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Routes", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("LRoutes", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Logix", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Blocks", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Sections", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Transits", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Audio", this);
 menu->addAction(act);
 grp->addAction(act);
 act = new QAction("Id Tags", this);
 menu->addAction(act);
 grp->addAction(act);
 connect(grp, SIGNAL(triggered(QAction*)), this, SLOT(on_viewMenu_triggered(QAction*)));
 return menu;
}
void TablesFrame::on_viewMenu_triggered(QAction* act)
{
 QString text = act->text();
 setupType(text);
}
void TablesFrame::on_logixOptions_triggered(bool bState)
{
 logixWidget->logixTableAction()->setEnabled(bState);
}
void TablesFrame::on_findOrphans_triggered()
{
 Maintenance::findOrphansPressed(this);
}
void TablesFrame::on_findEmpty_triggered()
{
 Maintenance::findEmptyPressed(this);
}
void TablesFrame::on_openPickListTables()
{
 logixWidget->logixTableAction()->OpenPickListTable();
}
