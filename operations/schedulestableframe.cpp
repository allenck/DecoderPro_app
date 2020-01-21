#include "schedulestableframe.h"
#include "schedulestablemodel.h"
#include "jtable.h"
#include <QLabel>
#include <QRadioButton>
#include <QBoxLayout>
#include "flowlayout.h"
#include "control.h"
#include <QMenu>
#include <QMenuBar>
#include "logger.h"
#include "printlocationsaction.h"
#include "schedulesresethitsaction.h"
#include "schedulesbyloadaction.h"
#include "schedulecopyaction.h"

namespace Operations
{
/**
 * Frame for adding and editing the Schedule roster for operations.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2009, 2012
 * @version $Revision: 29636 $
 */
///*public*/ class SchedulesTableFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = -3345422286868959830L;

 // major buttons
 // javax.swing.JButton addButton = new javax.swing.JButton();
 /*public*/ SchedulesTableFrame::SchedulesTableFrame(QWidget* parent)
     : OperationsFrame(tr("Schedules"), parent)
 {
     //super(tr("TitleSchedulesTable"));
  log = new Logger("SchedulesTableFrame");
  schedulesModel = new SchedulesTableModel();
  schedulesTable = new JTable(schedulesModel);
  schedulesTable->setObjectName("SchedulesTable");
 //JScrollPane schedulesPane;

 // labels
  textSort = new QLabel();
  textSep = new QLabel();

 // radio buttons
  sortByName = new QRadioButton(tr("Name"));
  sortById = new QRadioButton(tr("Id"));

  // general GUI config

  //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
  // Set up the jtable in a Scroll Pane..
//        schedulesPane = new JScrollPane(schedulesTable);
//        schedulesPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//        schedulesPane
//                .setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
  schedulesModel->initTable(this, schedulesTable);
  thisLayout->addWidget(/*schedulesPane*/schedulesTable);

  // Set up the control panel
  QWidget* controlPanel = new QWidget();
  controlPanel->setLayout(new FlowLayout());

  textSort->setText(tr("SortBy"));
  controlPanel->layout()->addWidget(textSort);
  controlPanel->layout()->addWidget(sortByName);
  sortByName->setChecked(true);
  controlPanel->layout()->addWidget(sortById);
  textSep->setText("          ");
  controlPanel->layout()->addWidget(textSep);

  // TODO allow user to add schedule to a spur
  // addButton.setText(tr("Add"));
  // addButton.setVisible(true);
  // controlPanel.add (addButton);
  controlPanel->setMaximumSize(QSize(Control::panelWidth1025, 50));
  thisLayout->addWidget(controlPanel);

  // setup buttons
  // addButtonAction(addButton);
  addRadioButtonAction(sortByName);
  addRadioButtonAction(sortById);

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu("Tools");
  toolMenu->addAction(new ScheduleCopyAction(this));
  toolMenu->addAction(new SchedulesByLoadAction(tr("Show Schedules By Load"),this));
  toolMenu->addAction(new SchedulesResetHitsAction(tr("Reset Hit Counts"),this));
  toolMenu->addAction(new PrintLocationsAction(tr("Print"), false,this));
  toolMenu->addAction(new PrintLocationsAction(tr("Preview"), true,this));

  menuBar->addMenu(toolMenu);
  setMenuBar(menuBar);
  addHelpMenu("package.jmri.jmrit.operations.Operations_LocationSchedules", true); // NOI18N

  initMinimumSize();
  // make panel a bit wider than minimum if the very first time opened
  if (width() == Control::panelWidth500)
  {
   resize(Control::panelWidth1025, height());
  }
  setLocation(10,20);

 }

 /*public*/ void SchedulesTableFrame::radioButtonActionPerformed(QWidget* ae)
{
     log->debug("radio button activated");
     QRadioButton* source = (QRadioButton*)ae;
     if (source== sortByName) {
         sortByName->setChecked(true);
         sortById->setChecked(false);
         schedulesModel->setSort(schedulesModel->SORTBYNAME);
     }
     if (source== sortById) {
         sortByName->setChecked(false);
         sortById->setChecked(true);
         schedulesModel->setSort(schedulesModel->SORTBYID);
     }
 }

 // add button
 // /*public*/ void buttonActionPerformed(java.awt.event.ActionEvent ae) {
 // log.debug("add schedule button activated");
 // if (source== addButton){
 // ScheduleEditFrame f = new ScheduleEditFrame();
 // f.setTitle(MessageFormat.format(tr("TitleScheduleAdd"), new Object[]{"Track Name"}));
 // f.initComponents(null, null, null);
 // }
 // }
 /*public*/ void SchedulesTableFrame::dispose() {
     saveTableDetails(schedulesTable);
     schedulesModel->dispose();
     OperationsFrame::dispose();
 }

 /*public*/ QString SchedulesTableFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.schedules.SchedulesTableFrame";
 }

}
