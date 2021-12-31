#include "routestableframe.h"
#include "routestablemodel.h"
#include <QLabel>
#include "jbutton.h"
#include <QRadioButton>
#include <QBoxLayout>
#include <QSortFilterProxyModel>
#include "flowlayout.h"
#include "control.h"
#include <QMenu>
#include <QMenuBar>
#include "operationsmenu.h"
#include "jtable.h"
#include "routeeditframe.h"
#include "routecopyaction.h"
#include "settrainiconpositionaction.h"
#include "printroutesaction.h"

namespace Operations
{
/**
 * Frame for adding and editing the route roster for operations.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008, 2009
 * @version $Revision: 28746 $
 */
///*public*/ class RoutesTableFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = -5308632111456022575L;


 /*public*/ RoutesTableFrame::RoutesTableFrame(QWidget* parent )
    : OperationsFrame(tr("Routes Table"),parent)
 {
     //super(tr("TitleRoutesTable"));
  log = new Logger(tr("RoutesTableFrame"));
  routesModel = new RoutesTableModel();

  // labels
  textSort = new QLabel(tr("Sort By"));
  textSep = new QLabel("          ");

  // radio buttons
  sortByName = new QRadioButton(tr("Name"));
  sortById = new QRadioButton(tr("Id"));

  // major buttons
  addButton = new JButton(tr("Add"));

  // general GUI config

  //thisLayout->addWidgetsetLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Set up the jtable in a Scroll Pane..
  QSortFilterProxyModel* sorter = new QSortFilterProxyModel(/*routesModel*/);
  sorter->setSourceModel(routesModel);
  JTable* routesTable = new JTable(sorter);
  //sorter.setTableHeader(routesTable.getTableHeader());
  //JScrollPane routesPane = new JScrollPane(routesTable);
  //routesPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  routesModel->initTable(routesTable);
  thisLayout->addWidget(/*routesPane*/routesTable);

  // Set up the control panel
  QWidget* controlPanel = new QWidget();
  FlowLayout* controlPanelLayout;
  controlPanel->setLayout(controlPanelLayout = new FlowLayout());

  controlPanelLayout->addWidget(textSort);
  controlPanelLayout->addWidget(sortByName);
  controlPanelLayout->addWidget(sortById);
  controlPanelLayout->addWidget(textSep);
  controlPanelLayout->addWidget(addButton);
  controlPanel->setMaximumSize(QSize(Control::panelWidth1025, 50));

  thisLayout->addWidget(controlPanel);

  sortByName->setChecked(true);

  // setup buttons
  addButtonAction(addButton);

  addRadioButtonAction(sortByName);
  addRadioButtonAction(sortById);

  // build menu
  QMenuBar* menuBar = new QMenuBar();
  QMenu* toolMenu = new QMenu(tr("Tools"));

  toolMenu->addAction(new RouteCopyAction(this));
  toolMenu->addAction(new SetTrainIconPositionAction(this));
  toolMenu->addAction(new PrintRoutesAction(false,this));
  toolMenu->addAction(new PrintRoutesAction( true,this));
  menuBar->addMenu(toolMenu);
  menuBar->addMenu(new OperationsMenu());
  setMenuBar(menuBar);

  // add help menu to window
  addHelpMenu("package.jmri.jmrit.operations.Operations_Routes", true); // NOI18N

  initMinimumSize();
  // make panel a bit wider than minimum if the very first time opened
  if (width() == Control::panelWidth500) {
      resize(730, height());
  }
  setLocation(10,20);

  // create ShutDownTasks
  createShutDownTask();
 }

 /*public*/ void RoutesTableFrame::radioButtonActionPerformed(QWidget* ae)
 {
  QRadioButton* source = (QRadioButton*)ae;
     log->debug("radio button activated");
     if (source == sortByName) {
         sortByName->setChecked(true);
         sortById->setChecked(false);
         routesModel->setSort(routesModel->SORTBYNAME);
     }
     if (source == sortById) {
         sortByName->setChecked(false);
         sortById->setChecked(true);
         routesModel->setSort(routesModel->SORTBYID);
     }
 }

 // add button
 /*public*/ void RoutesTableFrame::buttonActionPerformed(QWidget* ae) {
     // log->debug("route button activated");
 JButton* source = (JButton*)ae;
     if (source == addButton) {
         RouteEditFrame* f = new RouteEditFrame();
         f->initComponents(NULL);
         f->setTitle(tr("Add Route"));
     }
 }

 /*public*/ void RoutesTableFrame::dispose() {
     routesModel->dispose();
     OperationsFrame::dispose();
 }

 /*public*/ QString RoutesTableFrame::getClassName()
 {
  return "jmri.jmrit.operations.routes.RoutesTableFrame";
 }
}
