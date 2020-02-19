#include "settrainiconpositionframe.h"
#include "routemanager.h"
#include "trainicon.h"
#include <QLabel>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include "locationmanager.h"
#include "setup.h"
#include <QGroupBox>
#include <QMessageBox>
#include "control.h"
#include "operationsxml.h"
#include "vptr.h"
#include "location.h"
#include "logger.h"
#include "editor.h"
#include "panelmenu.h"
#include "route.h"
#include "routelocation.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Frame for setting train icon coordinates for a location.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2010
 * @version $Revision$
 */
///*public*/ class SetTrainIconPositionFrame extends OperationsFrame {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -6408476815508585050L;


 /*public*/ SetTrainIconPositionFrame::SetTrainIconPositionFrame(QWidget* parent)
     : OperationsFrame(tr("Set Train Icon"), parent)
 {
  //super(tr("MenuSetTrainIcon"));
  log = new Logger("SetTrainIconPositionFrame");
  routeManager = RouteManager::instance();

     // labels
     textEastX = new QLabel("   X  ");
     textEastY = new QLabel("   Y  ");
     textWestX = new QLabel("   X  ");
     textWestY = new QLabel("   Y  ");
     textNorthX = new QLabel("   X  ");
     textNorthY = new QLabel("   Y  ");
     textSouthX = new QLabel("   X  ");
     textSouthY = new QLabel("   Y  ");

     // text field
     // check boxes
     // major buttons
     placeButton = new QPushButton(tr("Place Test Icon"));
     applyButton = new QPushButton(tr("Update Routes"));
     saveButton = new QPushButton(tr("Save"));

     // combo boxes
     locationBox = LocationManager::instance()->getComboBox();

     //Spinners
     spinTrainIconEastX = new QSpinBox(/*new SpinnerNumberModel(0, 0, 10000, 1)*/);
     spinTrainIconEastX->setMinimum(0);
     spinTrainIconEastX->setMaximum(10000);
     spinTrainIconEastX->setSingleStep(1);
     spinTrainIconEastX->setValue(0);
     spinTrainIconEastY = new QSpinBox(/*new SpinnerNumberModel(0, 0, 10000, 1)*/);
     spinTrainIconEastY->setMinimum(0);
     spinTrainIconEastY->setMaximum(10000);
     spinTrainIconEastY->setSingleStep(1);
     spinTrainIconEastY->setValue(0);
     spinTrainIconWestX = new QSpinBox(/*new SpinnerNumberModel(0, 0, 10000, 1)*/);
     spinTrainIconWestX->setMinimum(0);
     spinTrainIconWestX->setMaximum(10000);
     spinTrainIconWestX->setSingleStep(1);
     spinTrainIconWestX->setValue(0);
     spinTrainIconWestY = new QSpinBox(/*new SpinnerNumberModel(0, 0, 10000, 1)*/);
     spinTrainIconWestY->setMinimum(0);
     spinTrainIconWestY->setMaximum(10000);
     spinTrainIconWestY->setSingleStep(1);
     spinTrainIconWestY->setValue(0);
     spinTrainIconNorthX = new QSpinBox(/*new SpinnerNumberModel(0, 0, 10000, 1)*/);
     spinTrainIconNorthX->setMinimum(0);
     spinTrainIconNorthX->setMaximum(10000);
     spinTrainIconNorthX->setSingleStep(1);
     spinTrainIconNorthX->setValue(0);
     spinTrainIconNorthY = new QSpinBox(/*new SpinnerNumberModel(0, 0, 10000, 1)*/);
     spinTrainIconNorthY->setMinimum(0);
     spinTrainIconNorthY->setMaximum(10000);
     spinTrainIconNorthY->setSingleStep(1);
     spinTrainIconNorthY->setValue(0);
     spinTrainIconSouthX = new QSpinBox(/*new SpinnerNumberModel(0, 0, 10000, 1)*/);
     spinTrainIconSouthX->setMinimum(0);
     spinTrainIconSouthX->setMaximum(10000);
     spinTrainIconSouthX->setSingleStep(1);
     spinTrainIconSouthX->setValue(0);
     spinTrainIconSouthY = new QSpinBox(/*new SpinnerNumberModel(0, 0, 10000, 1)*/);
     spinTrainIconSouthY->setMinimum(0);
     spinTrainIconSouthY->setMaximum(10000);
     spinTrainIconSouthY->setSingleStep(1);
     spinTrainIconSouthY->setValue(0);

     // Four test train icons
     _tIonEast =NULL;
     _tIonWest = NULL;
     _tIonNorth = NULL;
     _tIonSouth = NULL;
     // general GUI config
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     // set tool tips
     placeButton->setToolTip(tr("Places a set of train icons on panel") + " \"" + Setup::getPanelName()  + "\"");
     applyButton->setToolTip(tr("Updates all routes with the new coordinates"));
     saveButton->setToolTip(tr("Saves the train icon coordinates for the selected location"));

     //      Set up the panels
     QGroupBox* pLocation = new QGroupBox();
     pLocation->setLayout(new QVBoxLayout);
     //pLocation->setBorder(BorderFactory.createTitledBorder(tr("Location")));
     pLocation->setStyleSheet(gbStyleSheet);
     pLocation->setTitle(tr("Location"));
     pLocation->layout()->addWidget(locationBox);

     QGroupBox* pEast = new QGroupBox();
     pEast->setLayout(new GridBagLayout());
     //pEast->setBorder(BorderFactory.createTitledBorder(tr("EastTrainIcon")));
     pEast->setStyleSheet(gbStyleSheet);
     pEast->setTitle(tr("East Train Icon"));
     addItem(pEast, textEastX, 0, 0);
     addItem(pEast, spinTrainIconEastX, 1, 0);
     addItem(pEast, textEastY, 2, 0);
     addItem(pEast, spinTrainIconEastY, 3, 0);

     QGroupBox* pWest = new QGroupBox();
     pWest->setLayout(new GridBagLayout());
     //pWest->setBorder(BorderFactory.createTitledBorder(tr("WestTrainIcon")));
     pWest->setStyleSheet(gbStyleSheet);
     pWest->setTitle(tr("West Train Icon"));
     addItem(pWest, textWestX, 0, 0);
     addItem(pWest, spinTrainIconWestX, 1, 0);
     addItem(pWest, textWestY, 2, 0);
     addItem(pWest, spinTrainIconWestY, 3, 0);

     QGroupBox* pNorth = new QGroupBox();
     pNorth->setLayout(new GridBagLayout());
     //pNorth->setBorder(BorderFactory.createTitledBorder(tr("NorthTrainIcon")));
     pNorth->setStyleSheet(gbStyleSheet);
     pNorth->setTitle(tr("North Train Icon"));
     addItem(pNorth, textNorthX, 0, 0);
     addItem(pNorth, spinTrainIconNorthX, 1, 0);
     addItem(pNorth, textNorthY, 2, 0);
     addItem(pNorth, spinTrainIconNorthY, 3, 0);

     QGroupBox* pSouth = new QGroupBox();
     pSouth->setLayout(new GridBagLayout());
     //pSouth->setBorder(BorderFactory.createTitledBorder(tr("SouthTrainIcon")));
     pSouth->setStyleSheet(gbStyleSheet);
     pSouth->setTitle(tr("South Train Icon"));
     addItem(pSouth, textSouthX, 0, 0);
     addItem(pSouth, spinTrainIconSouthX, 1, 0);
     addItem(pSouth, textSouthY, 2, 0);
     addItem(pSouth, spinTrainIconSouthY, 3, 0);

     QWidget* pControl = new QWidget();
     pControl->setLayout(new GridBagLayout());
     //pControl->setBorder(BorderFactory.createTitledBorder(""));
     addItem(pControl, placeButton, 0, 0);
     addItem(pControl, applyButton, 1, 0);
     addItem(pControl, saveButton, 2, 0);

     // only show valid directions
     pEast->setVisible((Setup::getTrainDirection() & Setup::EAST) == Setup::EAST);
     pWest->setVisible((Setup::getTrainDirection() & Setup::WEST) == Setup::WEST);
     pNorth->setVisible((Setup::getTrainDirection() & Setup::NORTH) == Setup::NORTH);
     pSouth->setVisible((Setup::getTrainDirection() & Setup::SOUTH) == Setup::SOUTH);

     thisLayout->addWidget(pLocation);
     thisLayout->addWidget(pNorth);
     thisLayout->addWidget(pSouth);
     thisLayout->addWidget(pEast);
     thisLayout->addWidget(pWest);
     thisLayout->addWidget(pControl);

     // add help menu to window
     addHelpMenu("package.jmri.jmrit.operations.Operations_SetTrainIconCoordinates", true); // NOI18N

     // setup buttons
     addButtonAction(placeButton);
     addButtonAction(applyButton);
     addButtonAction(saveButton);

     // setup combo box
     addComboBoxAction(locationBox);

     // setup spinners
     spinnersEnable(false);
     addSpinnerChangeListerner(spinTrainIconEastX);
     addSpinnerChangeListerner(spinTrainIconEastY);
     addSpinnerChangeListerner(spinTrainIconWestX);
     addSpinnerChangeListerner(spinTrainIconWestY);
     addSpinnerChangeListerner(spinTrainIconNorthX);
     addSpinnerChangeListerner(spinTrainIconNorthY);
     addSpinnerChangeListerner(spinTrainIconSouthX);
     addSpinnerChangeListerner(spinTrainIconSouthY);

     initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight400));

 }

 //@Override
 /*public*/ void SetTrainIconPositionFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     // check to see if a location has been selected
     if (locationBox->currentText() == NULL) {
         //JOptionPane.showMessageDialog(this, tr("SelectLocationToEdit"), tr("NoLocationSelected"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("No Location Selected!"), tr("Select a location to edit"));
         return;
     }
     Location* l = (Location*) VPtr<Location>::asPtr(locationBox->currentData());
     if (l == NULL) {
         return;
     }
     if (source == placeButton) {
         placeTestIcons();
     }
     if (source == applyButton) {
         // update all routes?
//         int value = JOptionPane.showConfirmDialog(NULL,
//                 MessageFormat.format(tr("UpdateTrainIcon"), new Object[]{l->getName()}),
//                 tr("DoYouWantAllRoutes"),
//                 JOptionPane.YES_NO_OPTION);
         int value = QMessageBox::critical(this, tr("Do you want to update all routes?"), tr("Update train icon coordinates for %1?").arg(l->getName()), QMessageBox::Yes | QMessageBox::No);
         if (value == QMessageBox::Yes) {
             saveSpinnerValues(l);
             updateTrainIconCoordinates(l);
         }
     }
     if (source == saveButton) {
//         int value = JOptionPane.showConfirmDialog(NULL,
//                 MessageFormat.format(tr("UpdateTrainIcon"), new Object[]{l->getName()}),
//                 tr("UpdateDefaults"),
//                 JOptionPane.YES_NO_OPTION);
         int value = QMessageBox::critical(this, tr("Update the defaults for this location?"), tr("Update train icon coordinates for %1?").arg(l->getName()), QMessageBox::Yes | QMessageBox::No);
         if (value == QMessageBox::Yes) {
             saveSpinnerValues(l);
         }
         OperationsXml::save(); // save location and route files
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

 //@Override
 /*public*/ void SetTrainIconPositionFrame::comboBoxActionPerformed(QWidget* /*ae*/)
 {
  //QComboBox* source = (QComboBox*)ae;
     if (locationBox->currentText() == NULL) {
         resetSpinners();
         removeIcons();
     } else {
         Location* l = (Location*) VPtr<Location>::asPtr(locationBox->currentData());
         loadSpinners(l);
     }
 }

 //@Override
 /*public*/ void SetTrainIconPositionFrame::spinnerChangeEvent(QWidget* ae)
 {
  QSpinBox* source = (QSpinBox*)ae;
     if (source == spinTrainIconEastX && _tIonEast != NULL) { // Note: are these locations Positionable or Widget?
         ((Positionable*)_tIonEast)->setLocation((int) spinTrainIconEastX->value(),(int) ((Positionable*)_tIonEast)->getLocation().y());
     }
     if (source == spinTrainIconEastY && _tIonEast != NULL) {
         ((Positionable*)_tIonEast)->setLocation((int)((Positionable*)_tIonEast)->getLocation().x(), (int) spinTrainIconEastY->value());
     }
     if (source == spinTrainIconWestX && _tIonWest != NULL) {
         ((Positionable*)_tIonWest)->setLocation((int) spinTrainIconWestX->value(),(int) ((Positionable*)_tIonWest)->getLocation().y());
     }
     if (source == spinTrainIconWestY && _tIonWest != NULL) {
         ((Positionable*)_tIonWest)->setLocation((int)((Positionable*)_tIonWest)->getLocation().x(), (int) spinTrainIconWestY->value());
     }
     if (source == spinTrainIconNorthX && _tIonNorth != NULL) {
         ((Positionable*)_tIonNorth)->setLocation((int) spinTrainIconNorthX->value(),(int) ((Positionable*)_tIonNorth)->getLocation().y());
     }
     if (source == spinTrainIconNorthY && _tIonNorth != NULL) {
         ((Positionable*)_tIonNorth)->setLocation((int)((Positionable*)_tIonNorth)->getLocation().x(), (int) spinTrainIconNorthY->value());
     }
     if (source == spinTrainIconSouthX && _tIonSouth != NULL) {
         ((Positionable*)_tIonSouth)->setLocation((int) spinTrainIconSouthX->value(), (int) ((Positionable*)_tIonSouth)->getLocation().y());
     }
     if (source == spinTrainIconSouthY && _tIonSouth != NULL) {
         ((Positionable*)_tIonSouth)->setLocation((int)((Positionable*)_tIonSouth)->getLocation().x(), (int) spinTrainIconSouthY->value());
     }
 }

 /*private*/ void SetTrainIconPositionFrame::resetSpinners() {
     spinnersEnable(false);
     spinTrainIconEastX->setValue(0);
     spinTrainIconEastY->setValue(0);
     spinTrainIconWestX->setValue(0);
     spinTrainIconWestY->setValue(0);
     spinTrainIconNorthX->setValue(0);
     spinTrainIconNorthY->setValue(0);
     spinTrainIconSouthX->setValue(0);
     spinTrainIconSouthY->setValue(0);
 }

 /*private*/ void SetTrainIconPositionFrame::loadSpinners(Location* l) {
     log->debug(tr("Load spinners location %1").arg(l->getName()));
     spinnersEnable(true);
     spinTrainIconEastX->setValue(l->getTrainIconEast().x());
     spinTrainIconEastY->setValue(l->getTrainIconEast().y());
     spinTrainIconWestX->setValue(l->getTrainIconWest().x());
     spinTrainIconWestY->setValue(l->getTrainIconWest().y());
     spinTrainIconNorthX->setValue(l->getTrainIconNorth().x());
     spinTrainIconNorthY->setValue(l->getTrainIconNorth().y());
     spinTrainIconSouthX->setValue(l->getTrainIconSouth().x());
     spinTrainIconSouthY->setValue(l->getTrainIconSouth().y());
 }

 /*private*/ void SetTrainIconPositionFrame::spinnersEnable(bool enable) {
     spinTrainIconEastX->setEnabled(enable);
     spinTrainIconEastY->setEnabled(enable);
     spinTrainIconWestX->setEnabled(enable);
     spinTrainIconWestY->setEnabled(enable);
     spinTrainIconNorthX->setEnabled(enable);
     spinTrainIconNorthY->setEnabled(enable);
     spinTrainIconSouthX->setEnabled(enable);
     spinTrainIconSouthY->setEnabled(enable);
 }

 /*private*/ void SetTrainIconPositionFrame::saveSpinnerValues(Location* l) {
     log->debug(tr("Save train icons coordinates for location %1").arg(l->getName()));
     l->setTrainIconEast(QPoint( spinTrainIconEastX->value(),  spinTrainIconEastY->value()));
     l->setTrainIconWest(QPoint( spinTrainIconWestX->value(),  spinTrainIconWestY->value()));
     l->setTrainIconNorth(QPoint( spinTrainIconNorthX->value(),  spinTrainIconNorthY->value()));
     l->setTrainIconSouth(QPoint( spinTrainIconSouthX->value(),  spinTrainIconSouthY->value()));
 }

 // place test markers on panel
 /*private*/ void SetTrainIconPositionFrame::placeTestIcons() {
     removeIcons();
     if (locationBox->currentText() == NULL) {
         return;
     }
     Editor* editor = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getEditorByName(Setup::getPanelName());
     if (editor == NULL) {
//         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("LoadPanel"), new Object[]{Setup::getPanelName()}),
//                 tr("PanelNotFound"), JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(this, tr("Panel not found!"), tr("You need to load panel \"%1\"").arg(Setup::getPanelName()));
         return;
     }
     Location* l = (Location*) VPtr<Location>::asPtr(locationBox->currentData());
     if (l != NULL) {
         // East icon
         if ((Setup::getTrainDirection() & Setup::EAST) == Setup::EAST) {
             _tIonEast = editor->addTrainIcon(tr("East"));
//             _tIonEast->toolTip()->setText(l->getName());
//             _tIonEast->toolTip()->setBackgroundColor(Color.white);
             _tIonEast->setLocoColor(Setup::getTrainIconColorEast());
             _tIonEast->setLocation((int) spinTrainIconEastX->value(), (int) spinTrainIconEastY->value());
             addIconListener(_tIonEast);
         }
         // West icon
         if ((Setup::getTrainDirection() & Setup::WEST) == Setup::WEST) {
             _tIonWest = editor->addTrainIcon(tr("West"));
//             _tIonWest->toolTip()->setText(l->getName());
//             _tIonWest->toolTip()->setBackgroundColor(Color.white);
             _tIonWest->setLocoColor(Setup::getTrainIconColorWest());
             _tIonWest->setLocation((int) spinTrainIconWestX->value(), (int) spinTrainIconWestY->value());
             addIconListener(_tIonWest);
         }
         // North icon
         if ((Setup::getTrainDirection() & Setup::NORTH) == Setup::NORTH) {
             _tIonNorth = editor->addTrainIcon(tr("North"));
//             _tIonNorth.getTooltip()->setText(l->getName());
//             _tIonNorth.getTooltip()->setBackgroundColor(Color.white);
             _tIonNorth->setLocoColor(Setup::getTrainIconColorNorth());
             _tIonNorth->setLocation((int) spinTrainIconNorthX->value(), (int) spinTrainIconNorthY->value());
             addIconListener(_tIonNorth);
         }
         // South icon
         if ((Setup::getTrainDirection() & Setup::SOUTH) == Setup::SOUTH) {
             _tIonSouth = editor->addTrainIcon(tr("South"));
//             _tIonSouth.getTooltip()->setText(l->getName());
//             _tIonSouth.getTooltip()->setBackgroundColor(Color.white);
             _tIonSouth->setLocoColor(Setup::getTrainIconColorSouth());
             _tIonSouth->setLocation((int) spinTrainIconSouthX->value(), (int) spinTrainIconSouthY->value());
             addIconListener(_tIonSouth);
         }
     }
 }

 /*public*/ void SetTrainIconPositionFrame::updateTrainIconCoordinates(Location* l) {
     foreach (Route* route, RouteManager::instance()->getRoutesByIdList()) {
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             if (rl->getName()==(l->getName())) {
                 log->debug(tr("Updating train icon for route location %1 in route %2").arg(rl->getName()).arg(route->getName()));
                 rl->setTrainIconCoordinates();
             }
         }
     }
 }

 /*private*/ void SetTrainIconPositionFrame::removeIcons() {
     if (_tIonEast != NULL) {
         _tIonEast->remove();
     }
     if (_tIonWest != NULL) {
         _tIonWest->remove();
     }
     if (_tIonNorth != NULL) {
         _tIonNorth->remove();
     }
     if (_tIonSouth != NULL) {
         _tIonSouth->remove();
     }
 }

 /*private*/ void SetTrainIconPositionFrame::addIconListener(TrainIcon* /*tI*/)
 {
#if 0 //TODO: Need to define CoponentEvent
     tI.addComponentListener(new ComponentListener() {
         @Override
         /*public*/ void componentHidden(java.awt.event.ComponentEvent e) {
         }

         @Override
         /*public*/ void componentShown(java.awt.event.ComponentEvent e) {
         }

         @Override
         /*public*/ void componentMoved(java.awt.event.ComponentEvent e) {
             trainIconMoved(e);
         }

         @Override
         /*public*/ void componentResized(java.awt.event.ComponentEvent e) {
         }
     });
#endif
 }
#if 0
 /*protected*/ void SetTrainIconPositionFrame::trainIconMoved(ComponentEvent* ae) {
     if (source == _tIonEast) {
         log->debug(tr("East train icon X: %1 Y: %2").arg(_tIonEast->getLocation().x()).arg( _tIonEast->getLocation().y()));
         spinTrainIconEastX->setValue(_tIonEast->getLocation().x());
         spinTrainIconEastY->setValue(_tIonEast->getLocation().y());
     }
     if (source == _tIonWest) {
         log->debug("West train icon X: {} Y: {}", _tIonWest.getLocation().x, _tIonWest.getLocation().y);
         spinTrainIconWestX->setValue(_tIonWest.getLocation().x);
         spinTrainIconWestY->setValue(_tIonWest.getLocation().y);
     }
     if (source == _tIonNorth) {
         log.debug("North train icon X: {} Y: {}", _tIonNorth.getLocation().x, _tIonNorth.getLocation().y);
         spinTrainIconNorthX->setValue(_tIonNorth.getLocation().x);
         spinTrainIconNorthY->setValue(_tIonNorth.getLocation().y);
     }
     if (source == _tIonSouth) {
         log.debug("South train icon X: {} Y: {}", _tIonSouth.getLocation().x, _tIonSouth.getLocation().y);
         spinTrainIconSouthX->setValue(_tIonSouth.getLocation().x);
         spinTrainIconSouthY->setValue(_tIonSouth.getLocation().y);
     }
 }
#endif
 //@Override
 /*public*/ void SetTrainIconPositionFrame::dispose() {
     removeIcons();
     OperationsFrame::dispose();
 }
/*public*/ QString SetTrainIconPositionFrame::getClassName()
{
 return "jmri.jmrit.operations.routes.tools.SetTrainIconPositionFrame";
}

}
