#include "routecopyframe.h"
#include "routemanager.h"
#include <QLabel>
#include <QCheckBox>
#include "jtextfield.h"
#include "jcombobox.h"
#include <QBoxLayout>
#include <gridbaglayout.h>
#include "route.h"
#include "jbutton.h"
#include "control.h"
#include "logger.h"
#include "vptr.h"
#include <QMessageBox>
#include "routeeditframe.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * Frame for copying a route for operations.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2008, 2010
  * @version $Revision: 29261 $
  */
 ///*public*/ class RouteCopyFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = 4478401682355496019L;


 /*public*/ RouteCopyFrame::RouteCopyFrame(Route* route, QWidget* parent) : OperationsFrame(tr("Copy Route"),parent) {
     //super(tr("TitleRouteCopy"));
 log = new Logger("RouteCopyFrame");
 routeManager = ((RouteManager*)InstanceManager::getDefault("Operations::RouteManager"));

  // labels
  textCopyRoute = new QLabel(tr("Copy Route"));
  textRouteName = new QLabel(tr("Route Name"));

  // text field
  routeNameTextField = new JTextField(Control::max_len_string_route_name);

  // check boxes
  invertCheckBox = new QCheckBox(tr("Invert"));

  // major buttons
  copyButton = new JButton(tr("Copy"));

  // combo boxes
  routeBox = ((RouteManager*)InstanceManager::getDefault("Operations::RouteManager"))->getComboBox();
  // general GUI config

  //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Set up the panels
  JPanel* p1 = new JPanel();
  p1->setLayout(new GridBagLayout());

  // Layout the panel by rows
  // row 1 textRouteName
  addItem(p1, textRouteName, 0, 1);
  addItemWidth(p1, routeNameTextField, 3, 1, 1);

  // row 2
  addItem(p1, textCopyRoute, 0, 2);
  addItemWidth(p1, routeBox, 3, 1, 2);

  // row 4
  addItem(p1, invertCheckBox, 0, 4);
  addItem(p1, copyButton, 1, 4);

  thisLayout->addWidget(p1);

  // add help menu to window
  addHelpMenu("package.jmri.jmrit.operations.Operations_CopyRoute", true); // NOI18N

  initMinimumSize(QSize(Control::panelWidth600, Control::panelHeight200));

  // setup buttons
  addButtonAction(copyButton);

  routeBox->setSelectedItem(route->getName());

 }

 /*public*/ void RouteCopyFrame::setRouteName(QString routeName) {
     routeBox->setCurrentIndex(routeBox->findData(VPtr<Route>::asQVariant(routeManager->getRouteByName(routeName))));
 }

 /*public*/ void RouteCopyFrame::buttonActionPerformed(QWidget* ae) {
 JButton* source = (JButton*)ae;
     if (source == copyButton) {
         log->debug("copy route button activated");
         if (!checkName()) {
             return;
         }

         Route* newRoute = routeManager->getRouteByName(routeNameTextField->text());
         if (newRoute != NULL) {
             reportRouteExists(tr("add"));
             return;
         }
         if (routeBox->currentText() == NULL) {
             reportRouteDoesNotExist();
             return;
         }
         Route* oldRoute = (Route*) VPtr<Route>::asPtr(routeBox->currentData());
         if (oldRoute == NULL) {
             reportRouteDoesNotExist();
             return;
         }

         // now copy
         newRoute = routeManager->copyRoute(oldRoute, routeNameTextField->text(),
                 invertCheckBox->isChecked());

         RouteEditFrame* f = new RouteEditFrame();
         f->initComponents(newRoute);
     }
 }

 /*private*/ void RouteCopyFrame::reportRouteExists(QString s) {
     log->info("Can not " + s + ", route already exists");
//     JOptionPane.showMessageDialog(this, tr("ReportExists"),
//             MessageFormat.format(tr("CanNotRoute"), new Object[]{s}),
//             JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Can not %1 route!").arg(s), tr("Route with this name already exists "));
 }

 /*private*/ void RouteCopyFrame::reportRouteDoesNotExist() {
     log->debug("route does not exist");
//     JOptionPane.showMessageDialog(this, tr("CopyRoute"),
//             tr("CopyRoute"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Select Route to Copy"), tr("Select Route to Copy"));
 }

 /**
  *
  * @return true if name length is okay
  */
 /*private*/ bool RouteCopyFrame::checkName() {
     if (routeNameTextField->text().trimmed()==("")) {
//         JOptionPane.showMessageDialog(this, tr("EnterRouteName"),
//                 tr("EnterRouteName"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Enter New Route Name"), tr("Enter New Route Name"));
         return false;
     }
     if (routeNameTextField->text().length() > Control::max_len_string_route_name) {
//         JOptionPane.showMessageDialog(this, MessageFormat.format(
//                 tr("RouteNameLess"),
//                 new Object[]{Control.max_len_string_route_name + 1}), Bundle
//                 .getMessage("CanNotAddRoute"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not add route!"), tr("Route name must be less than %1 characters").arg(Control::max_len_string_route_name + 1));
         return false;
     }
     return true;
 }

 /*public*/ void RouteCopyFrame::dispose() {
     OperationsFrame::dispose();
 }
 /*public*/ QString RouteCopyFrame::getClassName()
 {
  return "jmri.jmrit.operations.routes.tools.RouteCopyFrame";
 }

}
