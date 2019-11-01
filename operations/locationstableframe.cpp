#include "locationstableframe.h"
#include "operationsframe.h"
#include <QLabel>
#include "jtable.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QBoxLayout>
#include "flowlayout.h"
#include <QMenuBar>
#include <QMenu>
#include "operationsmenu.h"
#include "control.h"
#include "logger.h"
#include "locationstablemodel.h"
#include "locationeditframe.h"
#include "schedulestableaction.h"
#include "locationcopyaction.h"
#include "modifylocationsaction.h"
#include "showcarsbylocationaction.h"
#include "printlocationsaction.h"
#include "modifylocationscarloadsaction.h"

//LocationsTableFrame::LocationsTableFrame()
//{

//}
namespace Operations
{
/**
 * Frame for adding and editing the location roster for operations.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 29638 $
 */
///*public*/ class LocationsTableFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = 4984202877113842727L;

 /*public*/ LocationsTableFrame::LocationsTableFrame(QWidget* parent) : OperationsFrame(tr("Locations Table"), parent) {
     //super(tr("TitleLocationsTable"));
  locationsModel = new LocationsTableModel();
  locationsTable = new JTable(/*locationsModel*/);
  locationsTable->setModel(locationsModel);
  log = new Logger("LocationsTableFrame");
  setObjectName("LocationsTableFrame");

  // labels
  textSort = new QLabel(tr("Sort By"));
  textSep = new QLabel("          ");

  // radio buttons
  sortByName = new QRadioButton(tr("Name"));
  sortById = new QRadioButton(tr("Id"));

  // major buttons
  addButton = new QPushButton(tr("Add"));
//	JButton printTableButton = new JButton("Print Table");

     // general GUI config

     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     // Set up the jtable in a Scroll Pane..
     //locationsPane = new QScrollArea(locationsTable);
//     locationsPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//     locationsPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
     locationsModel->initTable(locationsTable);
     thisLayout->addWidget(/*locationsPane*/locationsTable);

     // Set up the control panel
     QWidget* controlPanel = new QWidget();
     //controlPanel.setLayout(new FlowLayout());
     FlowLayout* controlPanelLayout = new FlowLayout(controlPanel);

     controlPanelLayout->addWidget(textSort);
     controlPanelLayout->addWidget(sortByName);
     controlPanelLayout->addWidget(sortById);
     controlPanelLayout->addWidget(textSep);
     controlPanelLayout->addWidget(addButton);
//		controlPanelLayout->addWidget (printTableButton);
     controlPanel->setMaximumSize(QSize(Control::panelWidth1025, 50));

     thisLayout->addWidget(controlPanel);

     sortByName->setChecked(true);

     // setup buttons
     addButtonAction(addButton);
//		addButtonAction(printTableButton);

     addRadioButtonAction(sortByName);
     addRadioButtonAction(sortById);

     //	build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));

     toolMenu->addAction(new LocationCopyAction(this));
     toolMenu->addAction(new SchedulesTableAction(tr("Schedules"),this));
     toolMenu->addAction(new ModifyLocationsAction(tr("Modify Locations by Car Type"),this));
     toolMenu->addAction(new ModifyLocationsCarLoadsAction(this));
     toolMenu->addAction(new ShowCarsByLocationAction(false, NULL, NULL,this));
#if 0
     if (Setup::isVsdPhysicalLocationEnabled()) {
         toolMenu.add(new SetPhysicalLocationAction(tr("MenuSetPhysicalLocation"), null));
     }
#endif
     toolMenu->addAction(new PrintLocationsAction(tr("Print"), false,this));
     toolMenu->addAction(new PrintLocationsAction(tr("Preview"), true, this));
     menuBar->addMenu(toolMenu);
     menuBar->addMenu(new OperationsMenu());
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_Locations", true);	// NOI18N

     initMinimumSize();
     // make panel a bit wider than minimum if the very first time opened
     if (width() == Control::panelWidth500) {
         resize(850, height());
     }
     setLocation(10,20);
     // create ShutDownTasks
     createShutDownTask();
 }

 /*public*/ void LocationsTableFrame::radioButtonActionPerformed(QWidget* ae) {
     log->debug("radio button activated");
     QRadioButton* source = (QRadioButton*)ae;
     if (source == sortByName) {
         sortByName->setChecked(true);
         sortById->setChecked(false);
         locationsModel->setSort(LocationsTableModel::SORTBYNAME);
     }
     if (source == sortById) {
         sortByName->setChecked(false);
         sortById->setChecked(true);
         locationsModel->setSort(LocationsTableModel::SORTBYID);
     }
 }

 // add button
 /*public*/ void LocationsTableFrame::buttonActionPerformed(QWidget* ae) {
//		log.debug("location button activated");
 QPushButton* source = (QPushButton*)ae;
     if (source == addButton) {

         LocationEditFrame* f = new LocationEditFrame(NULL);
         f->setTitle(tr("Add Location"));

     }
//		if (source() == printTableButton){
//			printTable();
//		}
 }

//	/*public*/ void printTable() {
//		try {
//			locationsTable.print();
//		} catch (PrinterException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//	}
 /*public*/ void LocationsTableFrame::dispose() {
     locationsModel->dispose();
     OperationsFrame::dispose();
 }

}
