#include "carstableframe.h"
#include "operationsxml.h"
#include <jtextfield.h>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include "carmanager.h"
#include <QLabel>
#include "setup.h"
#include <QBoxLayout>
#include "carstablemodel.h"
#include <QSortFilterProxyModel>
#include "jtable.h"
#include <QGroupBox>
#include "flowlayout.h"
#include <QScrollArea>
#include <QMenu>
#include <QMenuBar>
#include "operationsmenu.h"
#include "rollingstock.h"
#include <QMessageBox>
#include "logger.h"
#include "careditframe.h"
#include "carrostermenu.h"
#include "showcheckboxescarstableaction.h"
#include "resetcheckboxescarstableaction.h"
#include "carsetframe.h"
#include <QStatusBar>
#include "schedulemanager.h"
#include "carssetframeaction.h"
#include "jtable.h"
#include "modifylocationsaction.h"
#include "trainsbycartypeaction.h"
#include "instancemanager.h"
#include "joptionpane.h"
#include "borderfactory.h"

//CarsTableFrame::CarsTableFrame()
//{

//}
namespace Operations
{
/**
 * Frame for adding and editing the car roster for operations.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013,
 * 2014
 * @version $Revision: 29493 $
 */
///*public*/ class CarsTableFrame extends OperationsFrame implements TableModelListener {



 /*public*/ CarsTableFrame::CarsTableFrame(bool showAllCars, QString locationName, QString trackName, QWidget* parent)
 : OperationsFrame(tr("Cars"), parent)
 {
  setObjectName("CarsTableFrame");
  log = new Logger("CarsTableFrame");
  carManager = ((CarManager*)InstanceManager::getDefault("CarManager"));
  setStatusBar(new QStatusBar());
  statusBar()->setSizeGripEnabled(true);

  // labels
  numCars = new QLabel();
  textCars = new QLabel(tr("cars"));
  textSep1 = new QLabel("      ");

  // radio buttons
  sortByNumber = new QRadioButton(tr("Number"));
  sortByRoad = new QRadioButton(tr("Road"));
  sortByType = new QRadioButton(tr("Type"));
  sortByColor = new QRadioButton(tr("Color"));
  sortByLoad = new QRadioButton(tr("Load"));
  sortByKernel = new QRadioButton(tr("Kernel"));
  sortByLocation = new QRadioButton(tr("Location"));
  sortByDestination = new QRadioButton(tr("Destination"));
  sortByFinalDestination = new QRadioButton(tr("FD"));
  sortByRwe = new QRadioButton(tr("RWE"));
  sortByTrain = new QRadioButton(tr("Train"));
  sortByMoves = new QRadioButton(tr("Moves"));
  sortByBuilt = new QRadioButton(tr("Built"));
  sortByOwner = new QRadioButton(tr("Owner"));
  sortByValue = new QRadioButton(Setup::getValueLabel());
  sortByRfid = new QRadioButton(Setup::getRfidLabel());
  sortByWait = new QRadioButton(tr("Wait"));
  sortByPickup = new QRadioButton(tr("Pickup"));
  sortByLast = new QRadioButton(tr("Last"));
  group = new QButtonGroup();

  // major buttons
  addButton = new QPushButton(tr("Add"));
  findButton = new QPushButton(tr("Find"));
  saveButton = new QPushButton(tr("Save"));

  findCarTextBox = new JTextField(6);
  f = NULL;
  //super(tr("TitleCarsTable"));
  this->showAllCars = showAllCars;
  this->locationName = locationName;
  this->trackName = trackName;
  // general GUI configuration
  //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
  // Set up the table in a Scroll Pane..
  carsTableModel = new CarsTableModel(showAllCars, locationName, trackName);
  //TableSorter sorter = new TableSorter(carsTableModel);
  QSortFilterProxyModel* sorter = new QSortFilterProxyModel();
  sorter->setSourceModel(carsTableModel);
  carsTable = new JTable(sorter);
  //sorter.setTableHeader(carsTable.getTableHeader());
  //JScrollPane carsPane = new JScrollPane(carsTable);
  //carsPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  carsTableModel->initTable(carsTable, this);
  // load the number of cars and listen for changes


  carsTableModel->addTableModelListener((TableModelListener*)this);

  // Set up the control panel
  // row 1
  JPanel* cp1 = new JPanel();
  cp1->setBorder(BorderFactory::createTitledBorder(tr("Sort by")));
  QHBoxLayout* cp1Layout = new QHBoxLayout(cp1);
  cp1Layout->addWidget(sortByNumber);
  cp1Layout->addWidget(sortByRoad);
  cp1Layout->addWidget(sortByType);

  JPanel* clp = new JPanel();
  clp->setBorder(BorderFactory::createTitledBorder(""));
  QHBoxLayout* clpLayout = new QHBoxLayout(clp);
  clpLayout->addWidget(sortByColor);
  clpLayout->addWidget(sortByLoad);
  cp1Layout->addWidget(clp);
  cp1Layout->addWidget(sortByKernel);
  cp1Layout->addWidget(sortByLocation);

  JPanel* destp = new JPanel();
  destp->setBorder(BorderFactory::createTitledBorder(""));
  QHBoxLayout* destpLayout = new QHBoxLayout(destp);
  destpLayout->addWidget(sortByDestination);
  destpLayout->addWidget(sortByFinalDestination);
  destpLayout->addWidget(sortByRwe);
  cp1Layout->addWidget(destp);
  cp1Layout->addWidget(sortByTrain);

  JPanel* movep = new JPanel();
  movep->setBorder(BorderFactory::createTitledBorder(""));
  QHBoxLayout* movepLayout = new QHBoxLayout(movep);
  movepLayout->addWidget(sortByMoves);
  movepLayout->addWidget(sortByBuilt);
  movepLayout->addWidget(sortByOwner);
  if (Setup::isValueEnabled()) {
      movepLayout->addWidget(sortByValue);
  }
  if (Setup::isRfidEnabled()) {
      movepLayout->addWidget(sortByRfid);
  }

     if (((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"))->numEntries() > 0) {
         movepLayout->addWidget(sortByWait);
         movepLayout->addWidget(sortByPickup);
     }

  movepLayout->addWidget(sortByLast);
  cp1Layout->addWidget(movep);

  // row 2
  QWidget* cp2 = new QWidget();
  //cp2.setLayout(new BoxLayout(cp2, BoxLayout.X_AXIS));
  QHBoxLayout* cp2Layout = new QHBoxLayout(cp2);

  JPanel* cp2Add = new JPanel();
  FlowLayout* cp2AddLayout = new FlowLayout(cp2Add);
  cp2Add->setBorder(BorderFactory::createTitledBorder(""));
  cp2AddLayout->addWidget(numCars);
  cp2AddLayout->addWidget(textCars);
  cp2AddLayout->addWidget(textSep1);
  cp2AddLayout->addWidget(addButton);
  cp2Layout->addWidget(cp2Add);

  JPanel* cp2Find = new JPanel();
  cp2Find->setBorder(BorderFactory::createTitledBorder(""));
  FlowLayout * cp2FindLayout = new FlowLayout(cp2Find);
  findButton->setToolTip(tr("Find car by road number. Asterisk \"*\" = wild card."));
  findCarTextBox->setToolTip(tr("Find car by road number. Asterisk \"*\" = wild card."));
  cp2FindLayout->addWidget(findButton);
  cp2FindLayout->addWidget(findCarTextBox);
  cp2Layout->addWidget(cp2Find);

  JPanel* cp2Save = new JPanel();
  cp2Save->setBorder(BorderFactory::createTitledBorder(""));
  FlowLayout* cp2SaveLayout = new FlowLayout(cp2Save);
  cp2SaveLayout->addWidget(saveButton);
  cp2Layout->addWidget(cp2Save);

  // place controls in scroll pane
  QWidget* controlPanel = new QWidget();
  //controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.Y_AXIS));
  QVBoxLayout* controlPanelLayout = new QVBoxLayout(controlPanel);
  controlPanelLayout->addWidget(cp1);
  controlPanelLayout->addWidget(cp2);

  // some tool tips
  sortByFinalDestination->setToolTip(tr("Final Destination"));
  sortByRwe->setToolTip(tr("Return When Empty"));
  sortByLast->setToolTip(tr("Last Moved"));

  QScrollArea* controlPane = new QScrollArea(/*controlPanel*/);
  controlPane->setWidget(controlPanel);

  thisLayout->addWidget(carsTable);
  thisLayout->addWidget(controlPane);

  // setup buttons
  addButtonAction(addButton);
  addButtonAction(findButton);
  addButtonAction(saveButton);

  sortByNumber->setChecked(true);
  addRadioButtonAction(sortByNumber);
  addRadioButtonAction(sortByRoad);
  addRadioButtonAction(sortByType);
  addRadioButtonAction(sortByColor);
  addRadioButtonAction(sortByLoad);
  addRadioButtonAction(sortByKernel);
  addRadioButtonAction(sortByLocation);
  addRadioButtonAction(sortByDestination);
  addRadioButtonAction(sortByFinalDestination);
  addRadioButtonAction(sortByRwe);
  addRadioButtonAction(sortByTrain);
  addRadioButtonAction(sortByMoves);
  addRadioButtonAction(sortByBuilt);
  addRadioButtonAction(sortByOwner);
  addRadioButtonAction(sortByValue);
  addRadioButtonAction(sortByRfid);
  addRadioButtonAction(sortByWait);
  addRadioButtonAction(sortByPickup);
  addRadioButtonAction(sortByLast);

  group->addButton(sortByNumber);
  group->addButton(sortByRoad);
  group->addButton(sortByType);
  group->addButton(sortByColor);
  group->addButton(sortByLoad);
  group->addButton(sortByKernel);
  group->addButton(sortByLocation);
  group->addButton(sortByDestination);
  group->addButton(sortByFinalDestination);
  group->addButton(sortByRwe);
  group->addButton(sortByTrain);
  group->addButton(sortByMoves);
  group->addButton(sortByBuilt);
  group->addButton(sortByOwner);
  group->addButton(sortByValue);
  group->addButton(sortByRfid);
  group->addButton(sortByWait);
  group->addButton(sortByPickup);
  group->addButton(sortByLast);

  // sort by location
  if (!showAllCars) {
      sortByLocation->click();
      if (locationName != "") {
          QString title = tr("Cars") + " " + locationName;
          if (trackName != "") {
              title = title + " " + trackName;
          }
          setTitle(title);
      }
  }

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu(tr("Tools"));

     toolMenu->addMenu(new CarRosterMenu(tr("Car Roster"), CarRosterMenu::MAINMENU, this));
     toolMenu->addAction(new ShowCheckboxesCarsTableAction(carsTableModel,this));
     toolMenu->addAction(new ResetCheckboxesCarsTableAction(carsTableModel,this));
     toolMenu->addAction(new ModifyLocationsAction(this));
     toolMenu->addAction(new TrainsByCarTypeAction(this));
     toolMenu->addAction(new CarsSetFrameAction(carsTable,this));

     menuBar->addMenu(toolMenu);
     menuBar->addMenu(new OperationsMenu());
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_Cars", true); // NOI18N

     initMinimumSize();

//     addHorizontalScrollBarKludgeFix(controlPane, controlPanel);

     // create ShutDownTasks
     createShutDownTask();

 }

 /*public*/ void CarsTableFrame::radioButtonActionPerformed(QWidget* ae)
{
 QRadioButton* source = (QRadioButton*)ae;
     log->debug("radio button activated");
     if (source == sortByNumber) {
         carsTableModel->setSort(CarsTableModel::SORTBY_NUMBER);
     }
     if (source == sortByRoad) {
         carsTableModel->setSort(CarsTableModel::SORTBY_ROAD);
     }
     if (source == sortByType) {
         carsTableModel->setSort(CarsTableModel::SORTBY_TYPE);
     }
     if (source == sortByColor) {
         carsTableModel->setSort(CarsTableModel::SORTBY_COLOR);
     }
     if (source == sortByLoad) {
         carsTableModel->setSort(CarsTableModel::SORTBY_LOAD);
     }
     if (source == sortByKernel) {
         carsTableModel->setSort(CarsTableModel::SORTBY_KERNEL);
     }
     if (source == sortByLocation) {
         carsTableModel->setSort(CarsTableModel::SORTBY_LOCATION);
     }
     if (source == sortByDestination) {
         carsTableModel->setSort(CarsTableModel::SORTBY_DESTINATION);
     }
     if (source == sortByFinalDestination) {
         carsTableModel->setSort(CarsTableModel::SORTBY_FINALDESTINATION);
     }
     if (source == sortByRwe) {
         carsTableModel->setSort(CarsTableModel::SORTBY_RWE);
     }
     if (source == sortByTrain) {
         carsTableModel->setSort(CarsTableModel::SORTBY_TRAIN);
     }
     if (source == sortByMoves) {
         carsTableModel->setSort(CarsTableModel::SORTBY_MOVES);
     }
     if (source == sortByBuilt) {
         carsTableModel->setSort(CarsTableModel::SORTBY_BUILT);
     }
     if (source == sortByOwner) {
         carsTableModel->setSort(CarsTableModel::SORTBY_OWNER);
     }
     if (source == sortByValue) {
         carsTableModel->setSort(CarsTableModel::SORTBY_VALUE);
     }
     if (source == sortByRfid) {
         carsTableModel->setSort(CarsTableModel::SORTBY_RFID);
     }
     if (source == sortByWait) {
         carsTableModel->setSort(CarsTableModel::SORTBY_WAIT);
     }
     if (source == sortByPickup) {
         carsTableModel->setSort(CarsTableModel::SORTBY_PICKUP);
     }
     if (source == sortByLast) {
         carsTableModel->setSort(CarsTableModel::SORTBY_LAST);
     }
     // clear any sorts by column
     clearTableSort(carsTable);
 }

 /*public*/ QList<RollingStock*>* CarsTableFrame::getSortByList() {
     return carsTableModel->sysList;
 }


 // add, find or save button
 /*public*/ void CarsTableFrame::buttonActionPerformed(QWidget* ae)
 {
  // log.debug("car button activated");
  if (ae == findButton) {
      int rowindex = carsTableModel->findCarByRoadNumber(findCarTextBox->text());
      if (rowindex < 0) {
          JOptionPane::showMessageDialog(this, tr("Car with road number \"%1\" not found ").arg(
                  findCarTextBox->text()),tr("Could not find car!"),
                  JOptionPane::INFORMATION_MESSAGE);
          return;
      }
      // clear any sorts by column
      clearTableSort(carsTable);
      carsTable->changeSelection(rowindex, 0, false, false);
      return;
  }
  if (ae == addButton) {
      if (f != nullptr) {
          f->dispose();
      }
      f = new CarEditFrame();
      f->initComponents(); // default is add car
  }
  if (ae == saveButton) {
//      if (carsTable->isEditing()) {
//          log.debug("cars table edit true");
//          carsTable.getCellEditor().stopCellEditing();
//      }
      OperationsXml::save();
      if (Setup::isCloseWindowOnSaveEnabled()) {
          dispose();
      }
  }
 }
#if 0
 /*protected*/ int[] getCurrentTableColumnWidths() {
     TableColumnModel tcm = carsTable.getColumnModel();
     int[] widths = new int[tcm.getColumnCount()];
     for (int i = 0; i < tcm.getColumnCount(); i++) {
         widths[i] = tcm.getColumn(i).getWidth();
     }
     return widths;
 }

 /*public*/ void dispose() {
     CarsTableModel::removeTableModelListener(this);
     CarsTableModel::dispose();
     if (f != NULL) {
         f.dispose();
     }
     super.dispose();
 }

 /*public*/ void tableChanged(TableModelEvent e) {
     if (Control.showProperty) {
         log->debug("Table changed");
     }
     updateNumCars();
 }
#endif
 /*private*/ void CarsTableFrame::updateNumCars() {
     QString totalNumber = QString::number(((CarManager*)InstanceManager::getDefault("CarManager"))->getNumEntries());
     if (showAllCars) {
         numCars->setText(totalNumber);
         return;
     }
     QString showNumber = QString::number(getSortByList()->size());
     numCars->setText(showNumber + "/" + totalNumber);
 }
/*public*/ QString CarsTableFrame::getClassName()
{
 return "jmri.jmrit.operations.rollingstock.cars.CarsTableFrame";
}

}
