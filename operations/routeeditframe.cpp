#include "routeeditframe.h"
#include "control.h"
#include "routemanager.h"
#include "routemanagerxml.h"
#include "route.h"
#include "locationmanager.h"
#include "routelocation.h"
#include "train.h"
#include "jbutton.h"
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include "jtextfield.h"
#include "jcombobox.h"
#include <QGroupBox>
#include <QScrollArea>
#include <QBoxLayout>
#include "jtextfield.h"
#include "routeedittablemodel.h"
#include "gridbaglayout.h"
#include <QMenu>
#include <QMenuBar>
#include "operationsmenu.h"
#include "logger.h"
#include "jtable.h"
#include <QScrollBar>
#include <QMessageBox>
#include "vptr.h"
#include "location.h"
#include "setup.h"
#include "routecopyaction.h"
#include "settrainiconrouteaction.h"
#include "printrouteaction.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
/**
 * Frame for user edit of route
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class RouteEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 8328598758571366786L;

 /*public*/ /*static*/ /*final*/ QString RouteEditFrame::NAME = tr("Name");
 /*public*/ /*static*/ /*final*/ QString RouteEditFrame::DISPOSE = "dispose"; // NOI18N

 /*public*/ RouteEditFrame::RouteEditFrame(QWidget* parent)
     : OperationsFrame(tr("Edit Route"), parent)
 {
  log = new Logger("RouteEditFrame");
     //super(tr("TitleRouteEdit"));
  routeModel = new RouteEditTableModel();
  routeTable = new JTable(routeModel);
  locationManager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));

  _route = NULL;
  _routeLocation = NULL;
  _train = NULL;

  // major buttons
  addLocationButton = new JButton(tr("Add Location"));
  saveRouteButton = new JButton(tr("Save Route"));
  deleteRouteButton = new JButton(tr("Delete Route"));
  addRouteButton = new JButton(tr("Add Route"));

  // check boxes
  checkBox = new QCheckBox();

  // radio buttons
  addLocAtTop = new QRadioButton(tr("Top"));
  addLocAtBottom = new QRadioButton(tr("Bottom"));
  group = new QButtonGroup();

  showWait = new QRadioButton(tr("Wait"));
  showDepartTime = new QRadioButton(tr("DepartTime"));
  groupTime = new QButtonGroup();

  // text field
  routeNameTextField = new JTextField(Control::max_len_string_route_name);
  commentTextField = new JTextField(35);

  // combo boxes
  locationBox = ((LocationManager*)InstanceManager::getDefault("LocationManager"))->getComboBox();

 }

 /*public*/ void RouteEditFrame::initComponents(Route* route, Train* train) {
     _train = train;
     initComponents(route);
 }

 /*public*/ void RouteEditFrame::initComponents(Route* route) {

     _route = route;
     QString routeName = NULL;

     // load managers
     routeManager = ((RouteManager*)InstanceManager::getDefault("RouteManager"));

     // Set up the jtable in a Scroll Pane..
     routePane = new JPanel();
     //routePane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
     routePane->setBorder(BorderFactory::createTitledBorder(""));
     QVBoxLayout* routePaneLayout = new QVBoxLayout(routePane);
     routePaneLayout->addWidget(routeTable);

     if (_route != NULL) {
         routeName = _route->getName();
         routeNameTextField->setText(routeName);
         commentTextField->setText(_route->getComment());
         routeModel->initTable(this, routeTable, route);
         enableButtons(true);
     } else {
         setTitle(tr("Add Route"));
         enableButtons(false);
     }

     //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     // Set up the panels
     QWidget* p1 = new QWidget();
     p1->setLayout(new QHBoxLayout); //(p1, BoxLayout.X_AXIS));
     QScrollArea* p1Pane = new QScrollArea(/*p1*/);
//     p1Pane->setWidgetResizable(true);
//     p1Pane->setWidget(p1);
     //p1Pane->setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
     p1Pane->setMinimumSize(QSize(300, 3 * routeNameTextField->sizeHint().height()));
     p1Pane->setMaximumSize(QSize(2000, 200));
     //p1Pane->setBorder(BorderFactory.createTitledBorder(""));
     p1Pane->setFrameStyle(QFrame::Panel | QFrame::Plain);

     // name panel
     JPanel* pName = new JPanel();
     pName->setLayout(new GridBagLayout());
     pName->setBorder(BorderFactory::createTitledBorder(tr("Name")));
     addItem(pName, routeNameTextField, 0, 0);

     // comment panel
     JPanel* pComment = new JPanel();
     pComment->setLayout(new GridBagLayout());
     pComment->setBorder(BorderFactory::createTitledBorder(tr("Comment")));
     addItem(pComment, commentTextField, 0, 0);

     p1->layout()->addWidget(pName);
     p1->layout()->addWidget(pComment);
     p1Pane->setWidgetResizable(true);
     p1Pane->setWidget(p1);

     QWidget* p2 = new QWidget();
     p2->setLayout(new QHBoxLayout); //(p2, BoxLayout.X_AXIS));
     QScrollArea* p2Pane = new QScrollArea(/*p2*/);
     //p2Pane->setWidget(p2);
     //p2Pane->setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
     p2Pane->verticalScrollBar()->setEnabled(false);
     p2Pane->setMinimumSize(QSize(300, 3 * routeNameTextField->sizeHint().height()));
     p2Pane->setMaximumSize(QSize(2000, 200));
     //p2Pane->setBorder(BorderFactory:createTitledBorder(""));
     p2Pane->setFrameStyle(QFrame::Panel | QFrame::Plain);

     // location panel
     JPanel* pLoc = new JPanel();
     pLoc->setLayout(new GridBagLayout());
     pLoc->setBorder(BorderFactory::createTitledBorder(tr("Location")));
     addItem(pLoc, locationBox, 0, 1);
     addItem(pLoc, addLocationButton, 1, 1);
     addItem(pLoc, addLocAtTop, 2, 1);
     addItem(pLoc, addLocAtBottom, 3, 1);
     group->addButton(addLocAtTop);
     group->addButton(addLocAtBottom);
     addLocAtBottom->setChecked(true);

     // Wait or Depart Time panel
     JPanel* pWait = new JPanel();
     pWait->setLayout(new GridBagLayout());
     pWait->setBorder(BorderFactory::createTitledBorder(tr("Display")));
     addItem(pWait, showWait, 0, 1);
     addItem(pWait, showDepartTime, 1, 1);
     groupTime->addButton(showWait);
     groupTime->addButton(showDepartTime);

     p2->layout()->addWidget(pLoc);
     p2->layout()->addWidget(pWait);
     p2Pane->setWidget(p2);
     p2Pane->setWidgetResizable(true);

     // row 12 buttons
     JPanel* pB = new JPanel();
     pB->setLayout(new GridBagLayout());
     QScrollArea* pBPane = new QScrollArea(/*pB*/);
     //pBPane->setWidget(pB);
     //pBPane->setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
     pBPane->verticalScrollBar()->setEnabled(false);
     pBPane->setMinimumSize(QSize(300, 3 * routeNameTextField->sizeHint().height()));
     pBPane->setMaximumSize(QSize(2000, 200));
     //pBPane->setBorder(BorderFactory.createTitledBorder(""));
     pBPane->setFrameStyle(QFrame::Panel | QFrame::Plain);

     addItem(pB, deleteRouteButton, 0, 0);
     addItem(pB, addRouteButton, 1, 0);
     addItem(pB, saveRouteButton, 3, 0);
     pBPane->setWidget(pB);
     pBPane->setWidgetResizable(true);

     thisLayout->addWidget(p1Pane);
     thisLayout->addWidget(routePane);
     thisLayout->addWidget(p2Pane);
     thisLayout->addWidget(pBPane);

     // setup buttons
     addButtonAction(addLocationButton);
     addButtonAction(deleteRouteButton);
     addButtonAction(addRouteButton);
     addButtonAction(saveRouteButton);

     // setup radio buttons
     addRadioButtonAction(showWait);
     addRadioButtonAction(showDepartTime);
     setTimeWaitRadioButtons();

     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));

     toolMenu->addAction(new RouteCopyAction(tr("Copy Route"), routeName ,this));
     toolMenu->addAction(new SetTrainIconRouteAction(tr("Set Train Icons Coordinates for this Route"), routeName,this));
     toolMenu->addAction(new PrintRouteAction(tr("Print"), false, _route,this));
     toolMenu->addAction(new PrintRouteAction(tr("Preview"), true, _route,this));
     menuBar->addMenu(toolMenu);
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_EditRoute", true); // NOI18N

     // get notified if combo box gets modified
     //((LocationManager*)InstanceManager::getDefault("LocationManager")).addPropertyChangeListener(this);
     connect(((LocationManager*)InstanceManager::getDefault("LocationManager")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     // set frame size and route for display
     initMinimumSize(QSize(Control::panelWidth700, Control::panelHeight400));
 }

 // Save, Delete, Add
 /*public*/ void RouteEditFrame::buttonActionPerformed(QWidget* ae) {
 JButton* source = (JButton*)ae;
     if (source == addLocationButton) {
         log->debug("route add location button activated");
         if (locationBox->currentText() != NULL) {
             addNewRouteLocation();
         }
     }
     if (source == saveRouteButton) {
         log->debug("route save button activated");
         Route* route = routeManager->getRouteByName(routeNameTextField->text());
         if (_route == NULL && route == NULL) {
             saveNewRoute();
         } else {
             if (route != NULL && route != _route) {
                 reportRouteExists(tr("save"));
                 return;
             }
             saveRoute();
         }
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
     if (source == deleteRouteButton) {
         log->debug("route delete button activated");
//         if (JOptionPane.showConfirmDialog(this, MessageFormat.format(tr("AreYouSure?"),
//                 new Object[]{routeNameTextField.getText()}), tr("DeleteRoute?"),
//                 JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
         if(QMessageBox::question(this, tr("Delete Route?"), tr("Do you really want to delete route %1?").arg(routeNameTextField->text()),QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
         {
             return;
         }
         Route* route = routeManager->getRouteByName(routeNameTextField->text());
         if (route == NULL) {
             return;
         }

         routeManager->deregister(route);
         _route = NULL;

         enableButtons(false);
         routeModel->dispose();
         // save route file
         OperationsXml::save();
     }
     if (source == addRouteButton) {
         Route* route = routeManager->getRouteByName(routeNameTextField->text());
         if (route != NULL) {
             reportRouteExists(tr("add"));
             return;
         }
         saveNewRoute();
     }
 }

 /*public*/ void RouteEditFrame::radioButtonActionPerformed(QWidget* ae) {
     routeModel->setWait(showWait->isChecked());
 }

 /*private*/ void RouteEditFrame::addNewRouteLocation() {
//     if (routeTable->isEditing()) {
//         log->debug("route table edit true");
//         routeTable.getCellEditor().stopCellEditing();
//     }
     // add location to this route
     Location* l = (Location*) VPtr<Location>::asPtr(locationBox->currentData());
     RouteLocation* rl;
     if (addLocAtTop->isChecked()) {
         rl = _route->addLocation(l, 0);
     } else {
         rl = _route->addLocation(l);
     }
     rl->setTrainDirection(routeModel->getLastTrainDirection());
     rl->setMaxTrainLength(routeModel->getLastMaxTrainLength());
     if (rl->getLocation()->isStaging()) {
         rl->setMaxCarMoves(50);
     } else {
         rl->setMaxCarMoves(routeModel->getLastMaxTrainMoves());
     }
     // set train icon location
     rl->setTrainIconCoordinates();
 }

 /*private*/ void RouteEditFrame::saveNewRoute() {
     if (!checkName(tr("add"))) {
         return;
     }
     Route* route = routeManager->newRoute(routeNameTextField->text());
     routeModel->initTable(this, routeTable, route);
     _route = route;
     // enable checkboxes
     enableButtons(true);
     // assign route to a train?
     if (_train != NULL) {
         _train->setRoute(route);
     }
     saveRoute();
 }

 /*private*/ void RouteEditFrame::saveRoute() {
     if (!checkName(tr("save"))) {
         return;
     }
     _route->setName(routeNameTextField->text());
     _route->setComment(commentTextField->text());

//     if (routeTable->isEditing()) {
//         log->debug("route table edit true");
//         routeTable.getCellEditor().stopCellEditing();
//     }

     saveTableDetails(routeTable);

     // save route file
     OperationsXml::save();
 }

 /**
  *
  * @return true if name is length is okay
  */
 /*private*/ bool RouteEditFrame::checkName(QString s) {
     if (routeNameTextField->text().trimmed()==("")) {
         log->debug("Must enter a name for the route");
//         JOptionPane.showMessageDialog(this, tr("MustEnterName"), MessageFormat.format(Bundle
//                 .getMessage("CanNotRoute"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(this, tr("Can not %1 route!").arg(s),tr("Enter a name for this route"));
         return false;
     }
     if (routeNameTextField->text().length() > Control::max_len_string_route_name) {
//      JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle.getMessage("RouteNameLess"),
//              new Object[]{Control.max_len_string_route_name + 1}), MessageFormat.format(Bundle
//                      .getMessage("CanNotRoute"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 route!").arg(s),tr("Route name must be less than %1 characters").arg(Control::max_len_string_route_name + 1));
         return false;
     }
     return true;
 }

 /*private*/ void RouteEditFrame::reportRouteExists(QString s) {
     log->info("Can not " + s + ", route already exists");
//     JOptionPane.showMessageDialog(this, tr("ReportExists"), MessageFormat.format(Bundle
//             .getMessage("CanNotRoute"), new Object[]{s}), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Can not %1 route!").arg(s),tr("Route with this name already exists "));
 }

 /*private*/ void RouteEditFrame::enableButtons(bool enabled) {
     locationBox->setEnabled(enabled);
     addLocationButton->setEnabled(enabled);
     addLocAtTop->setEnabled(enabled);
     addLocAtBottom->setEnabled(enabled);
     saveRouteButton->setEnabled(enabled);
     deleteRouteButton->setEnabled(enabled);
     routeTable->setEnabled(enabled);
     // the inverse!
     addRouteButton->setEnabled(!enabled);
 }

 /*public*/ void RouteEditFrame::dispose() {
     routeModel->dispose();
     OperationsFrame::dispose();
 }

 /*private*/ void RouteEditFrame::updateComboBoxes() {
     locationManager->updateComboBox(locationBox);
 }

 // if the route has a departure time in the first location set the showDepartTime radio button
 /*private*/ void RouteEditFrame::setTimeWaitRadioButtons() {
     showWait->setChecked(true);
     if (_route != NULL) {
         RouteLocation* rl = _route->getDepartsRouteLocation();
         if (rl != NULL && rl->getDepartureTime()!=(RouteLocation::NONE)) {
             showDepartTime->setChecked(true);
         }
         routeModel->setWait(showWait->isChecked());
     }
 }

 /*public*/ void RouteEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateComboBoxes();
     }
 }

 /*public*/ QString RouteEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.trains.RouteEditFrame";
 }

}
