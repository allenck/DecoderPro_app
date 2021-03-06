#include "enginestableframe.h"
#include "enginemanager.h"
#include "setup.h"
#include <QBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include "jtextfield.h"
#include "enginestablemodel.h"
#include "jtable.h"
#include <QSortFilterProxyModel>
#include <QGroupBox>
#include "flowlayout.h"
#include <QScrollArea>
#include <QMenuBar>
#include <QMenu>
#include "operationsmenu.h"
#include <QFrame>
#include "engineeditframe.h"
#include "control.h"
#include "enginemodels.h"
#include <QMessageBox>
#include "logger.h"
#include <QStatusBar>
#include "operationsxml.h"
#include "enginerostermenu.h"
#include "instancemanager.h"
#include "propertychangelistener.h"

//EnginesTableFrame::EnginesTableFrame(QObject *parent) :
//  OperationsFrame(parent)
//{
//}
namespace Operations
{
/**
 * Frame for adding and editing the engine roster for operations.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008, 2011, 2012, 2013
 * @version $Revision: 29493 $
 */
///*public*/ class EnginesTableFrame extends OperationsFrame implements PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -3672037911597893323L;

 /*public*/ EnginesTableFrame::EnginesTableFrame(QWidget* parent) :
 OperationsFrame(tr("Engines Table"), parent)
 {
        //super(tr("Engines Table"));
        // general GUI config
 setObjectName("EnginesTableFrame");
 log = new Logger("EnginesTableFrame");
  engineManager = ((EngineManager*)InstanceManager::getDefault("EngineManager"));
  // labels
  numEngines = new QLabel();
  textEngines = new QLabel();
  textSep1 = new QLabel("          ");
  f = NULL;
  setStatusBar(new QStatusBar());
  statusBar()->setSizeGripEnabled(true);

  // radio buttons
  sortByNumber = new QRadioButton(tr("Number"));
  sortByRoad = new QRadioButton(tr("Road"));
  sortByModel = new QRadioButton(tr("Model"));
  sortByConsist = new QRadioButton(tr("Consist"));
  sortByLocation = new QRadioButton(tr("Location"));
  sortByDestination = new QRadioButton(tr("Destination"));
  sortByTrain = new QRadioButton(tr("Train"));
  sortByMoves = new QRadioButton(tr("Moves"));
  sortByBuilt = new QRadioButton(tr("Built"));
  sortByOwner = new QRadioButton(tr("Owner"));
  sortByValue = new QRadioButton(Setup::getValueLabel());
  sortByRfid = new QRadioButton(Setup::getRfidLabel());
  sortByLast = new QRadioButton(tr("Last"));
  QButtonGroup* group = new QButtonGroup();

  // major buttons
  addButton = new QPushButton(tr("Add"));
  findButton = new QPushButton(tr("Find"));
  saveButton = new QPushButton(tr("Save"));

  findEngineTextBox = new JTextField(6);
  QVBoxLayout* thisLayout;
  log->debug(tr("getContentPane returned %1").arg(getContentPane()->objectName()));
  getContentPane()->setLayout(thisLayout = new QVBoxLayout); //(getContentPane(), BoxLayout.Y_AXIS));

  // Set up the jtable in a Scroll Pane..
  enginesModel = new EnginesTableModel();
  //sorter = new TableSorter(enginesModel);
  sorter = new QSortFilterProxyModel();
  sorter->setSourceModel(enginesModel);
  enginesTable = new JTable(sorter);
  //sorter.setTableHeader(enginesTable.getTableHeader());
//        enginesPane = new JScrollPane(enginesTable);
//        enginesPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  enginesModel->initTable(enginesTable, this);

  // load the number of engines and listen for changes
  numEngines->setText(QString::number(engineManager->getNumEntries()));
  engineManager->addPropertyChangeListener(this);
  textEngines->setText(tr("engines"));

  // Set up the control panel
  // row 1
  QGroupBox* cp1 = new QGroupBox();
  //cp1.setBorder(BorderFactory.createTitledBorder(tr("SortBy")));
  QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
  cp1->setStyleSheet(gbStyleSheet);
  FlowLayout * cp1Layout = new FlowLayout(cp1);
  cp1->setTitle(tr("Sort By"));
  cp1Layout->addWidget(sortByNumber);
  cp1Layout->addWidget(sortByRoad);
  cp1Layout->addWidget(sortByModel);
  cp1Layout->addWidget(sortByConsist);
  cp1Layout->addWidget(sortByLocation);
  cp1Layout->addWidget(sortByDestination);
  cp1Layout->addWidget(sortByTrain);
  QFrame* movep = new QFrame();
  //movep.setBorder(BorderFactory.createTitledBorder(""));
  FlowLayout * movepLayout = new FlowLayout(movep);
  movepLayout->addWidget(sortByMoves);
  movepLayout->addWidget(sortByBuilt);
  movepLayout->addWidget(sortByOwner);
  if (Setup::isValueEnabled()) {
      movepLayout->addWidget(sortByValue);
  }
  if (Setup::isRfidEnabled()) {
      movepLayout->addWidget(sortByRfid);
  }
  movepLayout->addWidget(sortByLast);
  cp1Layout->addWidget(movep);

  // row 2
  QWidget* cp2 = new QWidget();
  //cp2.setLayout(new BoxLayout(cp2, BoxLayout.X_AXIS));
  QHBoxLayout* cp2Layout = new QHBoxLayout(cp2);

  QFrame* cp2Add = new QFrame();
  //cp2Add.setBorder(BorderFactory.createTitledBorder(""));
  cp2Add->setFrameShape(QFrame::StyledPanel);
  cp2Add->setFrameShadow(QFrame::Raised);
  QHBoxLayout* cp2AddLayout = new QHBoxLayout(cp2Add);

  cp2AddLayout->addWidget(numEngines);
  cp2AddLayout->addWidget(textEngines);
  cp2AddLayout->addWidget(textSep1);
  cp2AddLayout->addWidget(addButton);
  cp2Layout->addWidget(cp2Add);

  QGroupBox* cp2Find = new QGroupBox();
  //cp2Find.setBorder(BorderFactory.createTitledBorder(""));
  cp2Find->setStyleSheet(gbStyleSheet);
  cp2Find->setTitle("");
  FlowLayout* cp2FindLayout = new FlowLayout(cp2Find);
  findButton->setToolTip(tr("Find locomotive by road number. Asterisk \"*\" = wild card."));
  findEngineTextBox->setToolTip(tr("Find locomotive by road number. Asterisk \"*\" = wild card."));
  cp2FindLayout->addWidget(findButton);
  cp2FindLayout->addWidget(findEngineTextBox);
  cp2Layout->addWidget(cp2Find);

  QWidget* cp2Save = new QWidget();
  //cp2Save.setBorder(BorderFactory.createTitledBorder(""));
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
  sortByLast->setToolTip(tr("Last Moved"));

  QScrollArea* controlPane = new QScrollArea();
  controlPane->setWidget(controlPanel);
  controlPane->setWidgetResizable(true);

  thisLayout->addWidget(/*enginesPane*/enginesTable);
  thisLayout->addWidget(controlPane);

  // setup buttons
  addButtonAction(addButton);
  addButtonAction(findButton);
  addButtonAction(saveButton);

  sortByNumber->setChecked(true);

  addRadioButtonAction(sortByNumber);
  addRadioButtonAction(sortByRoad);
  addRadioButtonAction(sortByModel);
  addRadioButtonAction(sortByConsist);
  addRadioButtonAction(sortByLocation);
  addRadioButtonAction(sortByDestination);
  addRadioButtonAction(sortByTrain);
  addRadioButtonAction(sortByMoves);
  addRadioButtonAction(sortByBuilt);
  addRadioButtonAction(sortByOwner);
  addRadioButtonAction(sortByValue);
  addRadioButtonAction(sortByRfid);
  addRadioButtonAction(sortByLast);

  group->addButton(sortByNumber);
  group->addButton(sortByRoad);
  group->addButton(sortByModel);
  group->addButton(sortByConsist);
  group->addButton(sortByLocation);
  group->addButton(sortByDestination);
  group->addButton(sortByTrain);
  group->addButton(sortByMoves);
  group->addButton(sortByBuilt);
  group->addButton(sortByOwner);
  group->addButton(sortByValue);
  group->addButton(sortByRfid);
  group->addButton(sortByLast);

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu(tr("Tools"));
  toolMenu->addMenu(new EngineRosterMenu(tr("Engine Roster"), EngineRosterMenu::MAINMENU, this));
//        toolMenu.add(new NceConsistEngineAction(tr("MenuItemNceSync"), this));
  menuBar->addMenu(toolMenu);
  menuBar->addMenu(new OperationsMenu());
  setMenuBar(menuBar);
  addHelpMenu("package.jmri.jmrit.operations.Operations_Locomotives", true); // NOI18N

  initMinimumSize();

  //addHorizontalScrollBarKludgeFix(controlPane, controlPanel);

  // create ShutDownTasks
  createShutDownTask();

 }

 /*public*/ void EnginesTableFrame::radioButtonActionPerformed(QWidget* source)
 {
  log->debug("radio button activated");
  if (source == sortByNumber) {
      enginesModel->setSort(EnginesTableModel::SORTBYNUMBER);
  }
  if (source == sortByRoad) {
      enginesModel->setSort(EnginesTableModel::SORTBYROAD);
  }
  if (source == sortByModel) {
      enginesModel->setSort(EnginesTableModel::SORTBYMODEL);
  }
  if (source == sortByConsist) {
      enginesModel->setSort(EnginesTableModel::SORTBYCONSIST);
  }
  if (source == sortByLocation) {
      enginesModel->setSort(EnginesTableModel::SORTBYLOCATION);
  }
  if (source == sortByDestination) {
      enginesModel->setSort(EnginesTableModel::SORTBYDESTINATION);
  }
  if (source == sortByTrain) {
      enginesModel->setSort(EnginesTableModel::SORTBYTRAIN);
  }
  if (source == sortByMoves) {
      enginesModel->setSort(EnginesTableModel::SORTBYMOVES);
  }
  if (source == sortByBuilt) {
      enginesModel->setSort(EnginesTableModel::SORTBYBUILT);
  }
  if (source == sortByOwner) {
      enginesModel->setSort(EnginesTableModel::SORTBYOWNER);
  }
  if (source == sortByValue) {
      enginesModel->setSort(EnginesTableModel::SORTBYVALUE);
  }
  if (source == sortByRfid) {
      enginesModel->setSort(EnginesTableModel::SORTBYRFID);
  }
  if (source == sortByLast) {
      enginesModel->setSort(EnginesTableModel::SORTBYLAST);
  }
  // clear any sorts by column
  clearTableSort(enginesTable);
 }

 /*public*/ QList<RollingStock*>*EnginesTableFrame::getSortByList() {
  return enginesModel->getSelectedEngineList();
 }


 // add, save or find button
 /*public*/ void EnginesTableFrame::buttonActionPerformed(QWidget* obj) {
  // log->debug("engine button activated");
 QPushButton* source = (QPushButton*)obj;
  if ((QPushButton*)source == findButton)
  {
      int rowindex = enginesModel->findEngineByRoadNumber(findEngineTextBox->text());
      if (rowindex < 0) {
 //                JOptionPane.showMessageDialog(this, MessageFormat.format(
 //                        tr("engineWithRoadNumNotFound"), new Object[]{findEngineTextBox.getText()}),
 //                        tr("engineCouldNotFind"), JOptionPane.INFORMATION_MESSAGE);
 //                return;
       QMessageBox::warning(this, tr("Could not find locomotive!"), tr("Locomotive with railway number \"%1\" not found").arg(findEngineTextBox->text()));

     }
     // clear any sorts by column
     clearTableSort(enginesTable);
     //enginesTable->changeSelection(rowindex, 0, false, false);
// TODO:            enginesTable->setCurrentIndex(QModelIndex(rowindex,0,NULL,enginesModel));
     return;
 }
 if (source == addButton)
 {
   if (f != NULL) {
       f->dispose();
   }
   f = new EngineEditFrame();
   f->initComponents();
   f->setTitle(tr("Add Locomotive"));
 }

 if (source == saveButton)
 {
//            if (enginesTable->isEditing()) {
//                log->debug("locomotives table edit true");
//                //enginesTable->getCellEditor().stopCellEditing();
//            }
   OperationsXml::save();
   saveTableDetails(enginesTable);
   if (Setup::isCloseWindowOnSaveEnabled())
   {
    dispose();
   }
  }
 }

 /* public*/ void EnginesTableFrame::addButton_clicked() {
    if (f != NULL) {
        f->dispose();
    }
    f = new EngineEditFrame();
    f->initComponents();
    f->setTitle(tr("Add Locomotive"));
}

#if 0
    /*protected*/ int[] getCurrentTableColumnWidths() {
        TableColumnModel tcm = enginesTable.getColumnModel();
        int[] widths = new int[tcm.getColumnCount()];
        for (int i = 0; i < tcm.getColumnCount(); i++) {
            widths[i] = tcm.getColumn(i).getWidth();
        }
        return widths;
    }

    /*public*/ void dispose() {
        engineManager.removePropertyChangeListener(this);
        EnginesTableModel::dispose();
        if (f != NULL) {
            f.dispose();
        }
        super.dispose();
    }
#endif
    /*public*/ void EnginesTableFrame::propertyChange(PropertyChangeEvent* e) {
        if (Control::SHOW_PROPERTY) {
         log->debug(tr("Property change: (%1) old: ({%2) new: (%3)").arg( e->getPropertyName().arg( e->getOldValue().toString()).arg(e->getNewValue().toString())));
        }
        if (e->getPropertyName()==(EngineManager::LISTLENGTH_CHANGED_PROPERTY)) {
            numEngines->setText(QString::number(engineManager->getNumEntries()));
        }
    }

    /*public*/ QString EnginesTableFrame::getClassName()
    {
     return "jmri.jmrit.operations.rollingstock.engines.EnginesTableFrame";
    }


}
