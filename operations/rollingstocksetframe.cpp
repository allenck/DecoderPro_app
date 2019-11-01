#include "rollingstocksetframe.h"
#include "rollingstock.h"
#include "rollingstockmanager.h"
#include "locationmanager.h"
#include "trainmanager.h"
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QScrollArea>
#include <QBoxLayout>
#include <QGroupBox>
#include "logger.h"
#include "routelocation.h"
#include "rosterentry.h"
#include "location.h"
#include <QMessageBox>
#include "track.h"
#include "train.h"
#include "setup.h"
#include "gridbaglayout.h"
#include "control.h"
#include "routelocation.h"
#include "route.h"
#include <QList>

//RollingStockFrame::RollingStockFrame()
//{

//}
namespace Operations
{
 /**
 * Frame for user to place RollingStock on the layout
 *
 * @author Dan Boudreau Copyright (C) 2010, 2011, 2012, 2013
 * @version $Revision: 29499 $
 */
 ///*public*/ class RollingStockSetFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 7073826254938983591L;

 ///*protected*/ static final ResourceBundle rb = ResourceBundle
//         .getBundle("jmri.jmrit.operations.rollingstock.cars->JmritOperationsCarsBundle");



 // Auto checkbox states
 /*private*/ /*static*/ bool RollingStockSetFrame::autoTrackCheckBoxSelected = false;
 /*private*/ /*static*/ bool RollingStockSetFrame::autoDestinationTrackCheckBoxSelected = false;
 /*private*/ /*static*/ bool RollingStockSetFrame::autoFinalDestTrackCheckBoxSelected = false;
 /*private*/ /*static*/ bool RollingStockSetFrame::autoTrainCheckBoxSelected = false;

 /*public*/ RollingStockSetFrame::RollingStockSetFrame(QWidget* parent) : OperationsFrame(parent)
 {
  //super();
  common();
 }

 /*public*/ RollingStockSetFrame::RollingStockSetFrame(QString title, QWidget* parent) : OperationsFrame(title, parent)
 {
  //super(title);
  common();
 }
void RollingStockSetFrame::common()
{
 log = new Logger("RollingStockSetFrame");
 setObjectName("RollingStockSetFrame");
 locationManager = LocationManager::instance();
 trainManager = TrainManager::instance();
 _disableComboBoxUpdate = false;

 // labels
 textRoad = new QLabel();
 textType = new QLabel();

 // major buttons
 saveButton = new QPushButton(tr("Save"));
 ignoreAllButton = new QPushButton(tr("IgnoreAll"));

 // combo boxes
 locationBox = LocationManager::instance()->getComboBox();
 trackLocationBox = new QComboBox();
 destinationBox = LocationManager::instance()->getComboBox();
 trackDestinationBox = new QComboBox();
 finalDestinationBox = LocationManager::instance()->getComboBox();
 finalDestTrackBox = new QComboBox();
 trainBox = TrainManager::instance()->getTrainComboBox();

 // check boxes
 autoTrackCheckBox = new QCheckBox(tr("Auto"));
 autoDestinationTrackCheckBox = new QCheckBox(tr("Auto"));
 autoFinalDestTrackCheckBox = new QCheckBox(tr("Auto"));
 autoTrainCheckBox = new QCheckBox(tr("Auto"));

 locationUnknownCheckBox = new QCheckBox(tr("Location Unknown"));
 outOfServiceCheckBox = new QCheckBox(tr("Out Of Service"));

 ignoreStatusCheckBox = new QCheckBox(tr("Ignore"));
 ignoreLocationCheckBox = new QCheckBox(tr("Ignore"));
 ignoreDestinationCheckBox = new QCheckBox(tr("Ignore"));
 ignoreFinalDestinationCheckBox = new QCheckBox(tr("Ignore"));
 ignoreTrainCheckBox = new QCheckBox(tr("Ignore"));

 // optional panels
 pOptional = new QGroupBox();
 pOptional->setLayout(new QVBoxLayout);
 paneOptional = new QScrollArea(/*pOptional*/);
 pOptional->layout()->addWidget(paneOptional);
 pFinalDestination = new QGroupBox();
}

 /*public*/ void RollingStockSetFrame::initComponents() {
     // the following code sets the frame's initial state
     // create panel
     QWidget* pPanel = new QWidget();
     //pPanel->setLayout(new BoxLayout(pPanel, BoxLayout.Y_AXIS));
     QVBoxLayout* pPanelLayout = new QVBoxLayout(pPanel);
     // Layout the panel by rows
     // row 1
     QWidget* pRow1 = new QWidget();
     //pRow1->setLayout(new BoxLayout(pRow1, BoxLayout.X_AXIS));
     QHBoxLayout* pRow1Layout = new QHBoxLayout(pRow1);

     // row 1a
     QGroupBox* pRs = new QGroupBox();
     pRs->setLayout(new GridBagLayout());
     //prs->setBorder(BorderFactory.createTitledBorder(getRb().getString("rsType")));
     pRs->setStyleSheet(gbStyleSheet);
     pRs->setTitle("Rolling Stock");
     addItem(pRs, textRoad, 1, 0);
     pRow1Layout->addWidget(pRs);

     // row 1b
     QGroupBox* pType = new QGroupBox();
     pType->setLayout(new GridBagLayout());
     //pType->setBorder(BorderFactory.createTitledBorder(tr("Type")));
     pType->setStyleSheet(gbStyleSheet);
     pType->setTitle("Type");

     addItem(pType, textType, 1, 0);
     pRow1Layout->addWidget(pType);

     // row 1c
     QGroupBox*pStatus = new QGroupBox();
     pStatus->setLayout(new GridBagLayout());
     //pStatus->setBorder(BorderFactory.createTitledBorder(tr("Status")));
     pStatus->setStyleSheet(gbStyleSheet);
     pStatus->setTitle("Status");

     addItemLeft(pStatus, ignoreStatusCheckBox, 0, 0);
     addItemLeft(pStatus, locationUnknownCheckBox, 1, 1);
     addItemLeft(pStatus, outOfServiceCheckBox, 1, 0);
     pRow1Layout->addWidget(pStatus);

     pPanelLayout->addWidget(pRow1);

     // row 2
     QGroupBox* pLocation = new QGroupBox();
     pLocation->setLayout(new GridBagLayout());
     //pLocation->setBorder(BorderFactory.createTitledBorder(tr("LocationAndTrack")));
     pLocation->setStyleSheet(gbStyleSheet);
     pLocation->setTitle("Location and Track");
     addItemLeft(pLocation, ignoreLocationCheckBox, 0, 1);
     addItem(pLocation, locationBox, 1, 1);
     addItem(pLocation, trackLocationBox, 2, 1);
     addItem(pLocation, autoTrackCheckBox, 3, 1);
     pPanelLayout->addWidget(pLocation);

     // optional panel 2
     QGroupBox* pOptionalFrame = new QGroupBox("Optional -- Normally Set by Program --");
     pOptionalFrame->setLayout(new QVBoxLayout);
     pOptionalFrame->setStyleSheet(gbStyleSheet);
     pOptionalFrame->setTitle(tr("Optional -- Normally Set by Program --"));
     QWidget* pOptional2 = new QWidget();
     QVBoxLayout* paneOptional2Layout = new QVBoxLayout(pOptional2);
     QScrollArea* paneOptional2 = new QScrollArea(/*pOptional2*/);
     pOptionalFrame->layout()->addWidget(paneOptional2);
     paneOptional2->setWidget(pOptional2);
     paneOptional2->setWidgetResizable(true);
     //pOptional2->setLayout(new BoxLayout(pOptional2, BoxLayout.Y_AXIS));
//TODO:     paneOptional2->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutOptionalProgram")));

     // row 6
     QGroupBox* pDestination = new QGroupBox();
     pDestination->setLayout(new GridBagLayout());
     //pDestination->setBorder(BorderFactory.createTitledBorder(tr("DestinationAndTrack")));
     pDestination->setStyleSheet(gbStyleSheet);
     pDestination->setTitle("Destination and Track");
     addItemLeft(pDestination, ignoreDestinationCheckBox, 0, 1);
     addItem(pDestination, destinationBox, 1, 1);
     addItem(pDestination, trackDestinationBox, 2, 1);
     addItem(pDestination, autoDestinationTrackCheckBox, 3, 1);
     paneOptional2Layout->addWidget(pDestination);

     // row 7
     pFinalDestination->setLayout(new GridBagLayout());
//     pFinalDestination->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("FinalDestinationAndTrack")));
     pFinalDestination->setStyleSheet(gbStyleSheet);
     pFinalDestination->setTitle("Final Destination And Track");
     addItemLeft(pFinalDestination, ignoreFinalDestinationCheckBox, 0, 1);
     addItem(pFinalDestination, finalDestinationBox, 1, 1);
     addItem(pFinalDestination, finalDestTrackBox, 2, 1);
     addItem(pFinalDestination, autoFinalDestTrackCheckBox, 3, 1);
     paneOptional2Layout->addWidget(pFinalDestination);

     // row 8
     QGroupBox*pTrain = new QGroupBox();
     pTrain->setLayout(new GridBagLayout());
     //pTrain->setBorder(BorderFactory.createTitledBorder(tr("Train")));
     pTrain->setStyleSheet(gbStyleSheet);
     pTrain->setTitle("Train");
     addItemLeft(pTrain, ignoreTrainCheckBox, 0, 0);
     addItem(pTrain, trainBox, 1, 0);
     addItem(pTrain, autoTrainCheckBox, 2, 0);
     paneOptional2Layout->addWidget(pTrain);

     // button panel
     QWidget*pButtons = new QWidget();
     pButtons->setLayout(new GridBagLayout());
     addItem(pButtons, ignoreAllButton, 1, 0);
     addItem(pButtons, saveButton, 2, 0);

     // add panels
     //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     thisLayout->addWidget(pPanel);
     thisLayout->addWidget(/*paneOptional*/pOptional);
     thisLayout->addWidget(pOptionalFrame);
     thisLayout->addWidget(pButtons);

     // Don't show ignore buttons
     ignoreStatusCheckBox->setVisible(false);
     ignoreLocationCheckBox->setVisible(false);
     ignoreDestinationCheckBox->setVisible(false);
     ignoreFinalDestinationCheckBox->setVisible(false);
     ignoreTrainCheckBox->setVisible(false);
     ignoreAllButton->setVisible(false);

     // setup buttons
     addButtonAction(ignoreAllButton);
     addButtonAction(saveButton);

     // setup combobox
     addComboBoxAction(locationBox);
     addComboBoxAction(destinationBox);
     addComboBoxAction(finalDestinationBox);
     addComboBoxAction(trainBox);

     // setup checkbox
     addCheckBoxAction(locationUnknownCheckBox);
     addCheckBoxAction(outOfServiceCheckBox);
     addCheckBoxAction(autoTrackCheckBox);
     addCheckBoxAction(autoDestinationTrackCheckBox);
     addCheckBoxAction(autoFinalDestTrackCheckBox);
     addCheckBoxAction(autoTrainCheckBox);

     addCheckBoxAction(ignoreStatusCheckBox);
     addCheckBoxAction(ignoreLocationCheckBox);
     addCheckBoxAction(ignoreDestinationCheckBox);
     addCheckBoxAction(ignoreFinalDestinationCheckBox);
     addCheckBoxAction(ignoreTrainCheckBox);

     // set auto check box selected
     autoTrackCheckBox->setChecked(autoTrackCheckBoxSelected);
     autoDestinationTrackCheckBox->setChecked(autoDestinationTrackCheckBoxSelected);
     autoFinalDestTrackCheckBox->setChecked(autoFinalDestTrackCheckBoxSelected);
     autoTrainCheckBox->setChecked(autoTrainCheckBoxSelected);

     // add tool tips
     autoTrackCheckBox->setToolTip(tr("NOT USED! Only here for eliminate warnings from i18n consistency check"));
     autoDestinationTrackCheckBox->setToolTip(tr("rsTipAutoTrack"));
     autoFinalDestTrackCheckBox->setToolTip(tr("rsTipAutoTrack"));
     autoTrainCheckBox->setToolTip(tr("rsTipAutoTrain"));
     locationUnknownCheckBox->setToolTip(tr("TipLocationUnknown"));

     ignoreStatusCheckBox->setToolTip(tr("When checked, ignore this set of fields during change"));
     ignoreLocationCheckBox->setToolTip(tr("When checked, ignore this set of fields during change"));
     ignoreDestinationCheckBox->setToolTip(tr("When checked, ignore this set of fields during change"));
     ignoreFinalDestinationCheckBox->setToolTip(tr("When checked, ignore this set of fields during change"));
     ignoreTrainCheckBox->setToolTip(tr("When checked, ignore this set of fields during change"));

     // get notified if combo box gets modified
     //LocationManager::instance().addPropertyChangeListener(this);
     connect(LocationManager::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     // get notified if train combo box gets modified
     //trainManager.addPropertyChangeListener(this);
     connect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     setMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
 }

 /*public*/ void RollingStockSetFrame::load(RollingStock* rs) {
     _rs = rs;
     textRoad->setText(_rs->getRoadName() + " " + _rs->getNumber());
     textType->setText(_rs->getTypeName());
     locationUnknownCheckBox->setChecked(_rs->isLocationUnknown());
     outOfServiceCheckBox->setChecked(_rs->isOutOfService());
     updateComboBoxes();		// load the location, destination, and final destination combo boxes
     updateTrainComboBox();	// load the train combo box
     enableComponents(!locationUnknownCheckBox->isChecked());
     // has the program generated a pick up and set out for this rolling stock?
     if (_rs->getRouteLocation() != NULL || _rs->getRouteDestination() != NULL) {
         if (_rs->getRouteLocation() != NULL) {
             log->debug(tr("rs (%1) has a pick up location (%2)").arg(_rs->toString()).arg(_rs->getRouteLocation()->getName()));
         }
         if (_rs->getRouteDestination() != NULL) {
             log->debug(tr("rs (%1) has a destination (%2)").arg(_rs->toString()).arg(_rs->getRouteDestination()->getName()));
         }
         //if (getClass() == CarsSetFrame.class) {
         if(this->metaObject()->className() == "CarSetFrame")
         {
//             JOptionPane.showMessageDialog(this, getRb().getString("rsPressChangeWill"), getRb().getString(
//                     "rsInRoute"), JOptionPane.WARNING_MESSAGE);
          QMessageBox::warning(this, tr("Car has been assigned a destination and train"), tr("Pressing the Change button will release the car or cars from the train"));
         } else {
//             JOptionPane.showMessageDialog(this, getRb().getString("Pressing the Save button will release the car from the train"), getRb().getString(
//                     "rsInRoute"), JOptionPane.WARNING_MESSAGE);
          QMessageBox::warning(this, tr("Car has been assigned a destination and train"), tr(""));
         }
     }
     //_rs->addPropertyChangeListener(this);
     connect(rs->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 // Save button
 /*public*/ void RollingStockSetFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == saveButton) {
         _disableComboBoxUpdate = true; // need to stop property changes while we update
         save();
         _disableComboBoxUpdate = false;
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

// /*protected*/ ResourceBundle getRb() {
//     return rb;
// }

 /*protected*/ bool RollingStockSetFrame::save() {
     return change(_rs);
 }


 /*protected*/ bool RollingStockSetFrame::change(RollingStock* rs)
 {
  log->debug(tr("Change button action for rs (%1)").arg(rs->toString()));
  // save the auto buttons
  autoTrackCheckBoxSelected = autoTrackCheckBox->isChecked();
  autoDestinationTrackCheckBoxSelected = autoDestinationTrackCheckBox->isChecked();
  autoFinalDestTrackCheckBoxSelected = autoFinalDestTrackCheckBox->isChecked();
  autoTrainCheckBoxSelected = autoTrainCheckBox->isChecked();

  // save the statuses
  if (!ignoreStatusCheckBox->isChecked())
  {
   rs->setLocationUnknown(locationUnknownCheckBox->isChecked());
   rs->setOutOfService(outOfServiceCheckBox->isChecked());
  }
  // update location
  if (!changeLocation(rs))
  {
   return false;
  }
  // check to see if rolling stock is in staging and out of service (also location unknown)
  if (outOfServiceCheckBox->isChecked() && rs->getTrack() != NULL
          && rs->getTrack()->getTrackType()==(Track::STAGING))
  {
//         JOptionPane.showMessageDialog(this, getRb().getString("rsNeedToRemoveStaging"), getRb()
//                 .getString("rsInStaging"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(this, tr("Loco on staging track!"), tr("Can not have an \"Out of Service\" loco in staging"));
      // clear the rolling stock's location
      rs->setLocation(NULL, NULL);
  }

  loadTrain(rs);

  // update destination
  if (!changeDestination(rs))
  {
   return false;
  }

  if (!ignoreTrainCheckBox->isChecked())
  {
   Train* train = rs->getTrain();
   if (train != NULL)
   {
    // determine if train services this rs's type
    if (!train->acceptsTypeName(rs->getTypeName())) {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(getRb().getString(
//                         "rsTrainNotServType"), new Object[]{rs->getTypeName(), train->getName()}), getRb()
//                         .getString("rsNotMove"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Locomotive will not move!"), tr("Loco''s type (%1) is not serviced by train ({%2)").arg(rs->getTypeName()).arg(train->getName()));

        return false;
    }
    // determine if train services this rs's road
    if (!train->acceptsRoadName(rs->getRoadName())) {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(getRb().getString(
//                         "rsTrainNotServRoad"), new Object[]{rs->getRoadName(), train->getName()}), getRb()
//                         .getString("rsNotMove"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Locomotive will not move!"), tr(""));
        return false;
    }
    // determine if train services this rs's built date
    if (!train->acceptsBuiltDate(rs->getBuilt())) {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(getRb().getString(
//                         "rsTrainNotServBuilt"), new Object[]{rs->getBuilt(), train->getName()}), getRb()
//                         .getString("rsNotMove"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Locomotive will not move!"), tr(""));
        return false;
    }
    // determine if train services this rs's built date
    if (!train->acceptsOwnerName(rs->getOwner())) {
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(getRb().getString(
//                         "rsTrainNotServOwner"), new Object[]{rs->getOwner(), train->getName()}), getRb()
//                         .getString("rsNotMove"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Locomotive will not move!"), tr("Loco''s owner (%1) is not serviced by train (%2)").arg(rs->getOwner()).arg(train->getName()));
        return false;
    }
    // determine if train services the location and destination selected by user
    rl = NULL;
    rd = NULL;
    if (rs->getLocation() != NULL)
    {
     Route* route = train->getRoute();
     if (route != NULL) {
         rl = route->getLastLocationByName(rs->getLocationName());
         rd = route->getLastLocationByName(rs->getDestinationName());
     }
     if (rl == NULL) {
//                     JOptionPane.showMessageDialog(this, MessageFormat.format(getRb().getString(
//                             "rsLocNotServ"), new Object[]{rs->getLocationName(), train->getName()}),
//                             getRb().getString("rsNotMove"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Locomotive will not move!"), tr("Loco''s location (%1) not serviced by train ({%2)").arg(rs->getLocationName()).arg(train->getName()));
         return false;
     }
     if (rd == NULL && rs->getDestinationName()!=(RollingStock::NONE)) {
//                     JOptionPane.showMessageDialog(this, MessageFormat.format(getRb().getString(
//                             "rsDestNotServ"), new Object[]{rs->getDestinationName(), train->getName()}),
//                             getRb().getString("rsNotMove"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Locomotive will not move!"), tr("Loco''s destination (%1) not serviced by train (%2)"));
         return false;
     }
     if (rd != NULL && route != NULL)
     {
      // now determine if destination is after location
      QList<RouteLocation*>* routeSequence = route->getLocationsBySequenceList();
      bool foundLoc = false; // when true, found the rs's location in the route
      bool foundDes = false;
      foreach (RouteLocation* rlocation, *routeSequence)
      {
       if (rs->getLocationName()==(rlocation->getName()))
       {
        rl = rlocation;
        foundLoc = true;
       }
       if (rs->getDestinationName()==(rlocation->getName())
               && foundLoc)
       {
        rd = rlocation;
        foundDes = true;
        if (rs->getDestinationTrack() != NULL && (rlocation->getTrainDirection() & rs->getDestinationTrack()->getTrainDirections()) == 0) {
            continue; // destination track isn't serviced by the train's direction
        }
        break;
       }
      }
      if (!foundDes)
      {
//                         JOptionPane.showMessageDialog(this, MessageFormat.format(getRb().getString(
//                                 "rsLocOrder"), new Object[]{rs->getDestinationName(),
//                                     rs->getLocationName(), train->getName()}), getRb().getString("rsNotMove"),
//                                 JOptionPane.ERROR_MESSAGE);
       QMessageBox::critical(this, tr("Locomotive will not move!"), tr("Loco''s destination (%1) is before location (%2) when serviced by train (%3)").arg(rs->getDestinationName()).arg(rs->getLocationName()).arg(train->getName()) );
          return false;
      }
     }
    }
   }
  }
  return true;
 }

 /*private*/ bool RollingStockSetFrame::changeLocation(RollingStock* rs)
 {
  if (!ignoreLocationCheckBox->isChecked())
  {
   if (locationBox->currentText() == NULL)
   {
    rs->setLocation(NULL, NULL);
   }
   else
   {
    if (trackLocationBox->currentText() == NULL) {
//                 JOptionPane.showMessageDialog(this, getRb().getString("rsFullySelect"), getRb()
//                         .getString("rsCanNotLoc"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Can not update locomotive location"), tr("To place a locomotive, you must select the location and track"));
        return false;
    }
    // update location only if it has changed
    if (rs->getLocation() == NULL || rs->getLocation()!=VPtr<Location>::asPtr(locationBox->itemData(locationBox->currentIndex()))
            || rs->getTrack() == NULL || rs->getTrack()!=VPtr<Track>::asPtr(trackLocationBox->itemData(trackLocationBox->currentIndex())))
    {
     QString status = rs->setLocation((Location*) VPtr<Location>::asPtr(locationBox->itemData(locationBox->currentIndex())),
             (Track*) VPtr<Track>::asPtr(trackLocationBox->currentData(/*trackLocationBox->currentIndex()*/)));
     rs->setSavedRouteId(RollingStock::NONE); // clear last route id
     if (status!=(Track::OKAY))
     {
      log->debug(tr("Can't set rs's location because of %1").arg(status));
//                     JOptionPane.showMessageDialog(this, MessageFormat.format(getRb().getString(
//                             "rsCanNotLocMsg"), new Object[]{rs->toString(), status}), getRb()
//                             .getString("rsCanNotLoc"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not update locomotive location"), tr("Can't set locomotive (%1) location due to %2").arg(rs->toString()).arg(status));
      // does the user want to force the rolling stock to this track?
//                     int results = JOptionPane.showOptionDialog(this, MessageFormat.format(getRb()
//                             .getString("rsForce"), new Object[]{rs->toString(),
//                                 (Track) trackLocationBox.getSelectedItem()}), MessageFormat.format(getRb()
//                                     .getString("rsOverride"), new Object[]{status}),
//                             JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, NULL, NULL, NULL);
//                     if (results == JOptionPane.YES_OPTION) {
      int results = QMessageBox::question(this, tr("Do you want to override track''s %1?").arg(status), tr("Do you want to force locomotive (%1) to track (%2)?").arg(rs->toString()).arg(trackLocationBox->currentText()), QMessageBox::Yes | QMessageBox::No);
      if(results == QMessageBox::Yes)
      {
       log->debug("Force rolling stock to track");
       rs->setLocation((Location*) VPtr<Location>::asPtr(locationBox->itemData(locationBox->currentIndex())), (Track*) VPtr<Track>::asPtr(trackLocationBox
                  ->itemData(locationBox->currentIndex())), true);
      }
      else
      {
       return false;
      }
     }
     else
     {
      updateTrainComboBox();
     }
    }
   }
  }
  return true;
 }

 /*private*/ void RollingStockSetFrame::loadTrain(RollingStock* rs) {
     if (!ignoreTrainCheckBox->isChecked()) {
         if (trainBox->currentText() == NULL) {
             if (rs->getTrain() != NULL) {
                 // prevent rs from being picked up and delivered
                 setRouteLocationAndDestination(rs, rs->getTrain(), NULL, NULL);
             }
             rs->setTrain(NULL);
         } else {
             Train* train = (Train*) VPtr<Train>::asPtr(trainBox->itemData(trainBox->currentIndex()));
             if (rs->getTrain() != NULL && rs->getTrain()!=(train)) // prevent rs from being picked up and delivered
             {
                 setRouteLocationAndDestination(rs, rs->getTrain(), NULL, NULL);
             }
             rs->setTrain(train);
         }
     }
 }

 /*private*/ bool RollingStockSetFrame::changeDestination(RollingStock* rs) {
     if (!ignoreDestinationCheckBox->isChecked()) {
         if (destinationBox->currentText() == NULL) {
             rs->setDestination(NULL, NULL);
         } else {
             Track* destTrack = NULL;
             if (trackDestinationBox->currentText() != NULL) {
                 destTrack = (Track*) VPtr<Track>::asPtr(trackDestinationBox->itemData(trackDestinationBox->currentIndex()));
             }
             if (destTrack != NULL && rs->getDestinationTrack() != destTrack
                     && destTrack->getTrackType()==(Track::STAGING)
                     && (rs->getTrain() == NULL || !rs->getTrain()->isBuilt())) {
                 log->debug(tr("Destination track (%1) is staging").arg(destTrack->getName()));
//                 JOptionPane.showMessageDialog(this, getRb().getString("rsDoNotSelectStaging"), getRb()
//                         .getString("rsCanNotDest"), JOptionPane.ERROR_MESSAGE);
                 QMessageBox::critical(this, tr("Can not update locomotive destination"), tr("rsDoNotSelectStaging"));
                 return false;
             }
             QString status = rs->setDestination((Location*) VPtr<Location>::asPtr(destinationBox->itemData(destinationBox->currentIndex())), destTrack);
             if (status!=(Track::OKAY)) {
                 log->debug(tr("Can't set rs's destination because of %1").arg(status));
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(getRb().getString(
//                         "rsCanNotDestMsg"), new Object[]{rs->toString(), status}), getRb().getString(
//                                 "rsCanNotDest"), JOptionPane.ERROR_MESSAGE);
                 QMessageBox::critical(this, tr("Can not update locomotive destination"), tr("Can't set locomotive (%1) destination due to %2").arg(rs->toString()).arg(status));
                 return false;
             } else {
                 updateTrainComboBox();
             }
         }
     }
     return true;
 }

 /*protected*/ void RollingStockSetFrame::checkTrain(RollingStock* rs) {
     // determine if train is built and car is part of train or wants to be part of the train
     Train* train = rs->getTrain();
     if (train != NULL && train->isBuilt()) {
         if (rs->getRouteLocation() != NULL
                 && rs->getRouteDestination() != NULL
                 && rl != NULL
                 && rd != NULL
                 && (rs->getRouteLocation()->getName()!=(rl->getName())
                 || rs->getRouteDestination()->getName()!=(rd->getName()) || rs
                 ->getDestinationTrack() == NULL)) {
             // user changed rolling stock location or destination or no destination track
             setRouteLocationAndDestination(rs, train, NULL, NULL);
         }
         if (rs->getRouteLocation() != NULL || rs->getRouteDestination() != NULL) {
//             if (JOptionPane.showConfirmDialog(this, MessageFormat.format(getRb().getString(
//                     "rsRemoveRsFromTrain"), new Object[]{rs->toString(), train->getName()}), getRb()
//                     .getString("rsInRoute"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
          if(QMessageBox::question(this, tr("Locomotive has been assigned a destination and train"), tr("Do you really want to remove loco (%1) from train (%2)?").arg(rs->toString()).arg(train->getName())))
          {
                 // prevent rs from being picked up and delivered
                 setRouteLocationAndDestination(rs, train, NULL, NULL);
             }
         } else if (rl != NULL && rd != NULL && rs->getDestinationTrack() != NULL
                 && !train->isTrainInRoute()) {
             if (rs->getDestinationTrack()->getLocation()->isStaging()
                     && rs->getDestinationTrack()!=(train->getTerminationTrack())) {
                 log->debug("Rolling stock destination track is staging and not the same as train");
//                 JOptionPane.showMessageDialog(this, MessageFormat.format(
//                         tr("rsMustSelectSameTrack"), new Object[]{train.getTerminationTrack()
//                             ->getName()}), tr("rsStagingTrackError"), JOptionPane.ERROR_MESSAGE);
                 QMessageBox::critical(this, tr("Staging track error!"), tr("You must select the same termination staging track (%1) as train").arg(train->getTerminationTrack()->getName()));
             } else if (/*JOptionPane.showConfirmDialog(this, MessageFormat.format(
                     getRb().getString("rsAddRsToTrain"), new Object[]{rs->toString(), train->getName()}), getRb()
                     .getString("rsAddManuallyToTrain"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {*/
                        QMessageBox::question(this, tr("Manually add locomotive to train?"), tr("Do you want to add loco (%1) to train (%2)?").arg(rs->toString()).arg(train->getName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
                 // set new pick up and set out locations
                 setRouteLocationAndDestination(rs, train, rl, rd);
                 log->debug(tr("Add rolling stock (*1) to train (%2) route pick up %3 drop %4").arg(rs->toString()).arg(train
                         ->getName()).arg(rl->getId()).arg(rd->getId())); // NOI18N
             }
         }
     }
 }

 /*protected*/ void RollingStockSetFrame::setRouteLocationAndDestination(RollingStock* rs, Train* train, RouteLocation* rl,
         RouteLocation* rd) {
     if (rs->getRouteLocation() != NULL || rl != NULL) {
         train->setModified(true);
     }
     rs->setRouteLocation(rl);
     rs->setRouteDestination(rd);
 }

 /*protected*/ void RollingStockSetFrame::updateComboBoxes() {
     log->debug("update combo boxes");
     locationManager->updateComboBox(locationBox);
     locationManager->updateComboBox(destinationBox);
     locationManager->updateComboBox(finalDestinationBox);

     updateLocationComboBoxes();
     updateDestinationComboBoxes();
 }

 /*protected*/ bool RollingStockSetFrame::updateGroup(QList<RollingStock*> list) {
     foreach (RollingStock* rs, list) {
         if (rs == _rs) {
             continue;
         }
         // Location status and out of service
         if (!ignoreStatusCheckBox->isChecked()) {
             rs->setLocationUnknown(locationUnknownCheckBox->isChecked());
             rs->setOutOfService(outOfServiceCheckBox->isChecked());
         }
         // update location and destination
         if (!changeLocation(rs)) {
             return false;
         }
         if (!changeDestination(rs)) {
             return false;
         }

         if (!ignoreTrainCheckBox->isChecked()) {
             if (trainBox->currentText() == NULL) {
                 rs->setTrain(NULL);
             } else {
                 rs->setTrain((Train*) VPtr<Train>::asPtr(trainBox->itemData(trainBox->currentIndex())));
             }
         }
         // set the route location and destination to match
         rs->setRouteLocation(_rs->getRouteLocation());
         rs->setRouteDestination(_rs->getRouteDestination());
     }
     return true;
 }

 /*public*/ void RollingStockSetFrame::checkBoxActionPerformed(QWidget* ae) {
     log->debug("checkbox action ");
     QCheckBox* source = (QCheckBox*)ae;
     if (source == locationUnknownCheckBox) {
         outOfServiceCheckBox->setChecked(locationUnknownCheckBox->isChecked());
         enableComponents(!locationUnknownCheckBox->isChecked());
     }
     if (source == autoTrackCheckBox) {
         updateLocationTrackComboBox();
     }
     if (source == autoDestinationTrackCheckBox) {
         updateDestinationTrackComboBox();
     }
     if (source == ignoreStatusCheckBox) {
         locationUnknownCheckBox->setEnabled(!ignoreStatusCheckBox->isChecked());
         outOfServiceCheckBox->setEnabled(!ignoreStatusCheckBox->isChecked());
     }
     if (source == ignoreLocationCheckBox) {
         locationBox->setEnabled(!ignoreLocationCheckBox->isChecked());
         trackLocationBox->setEnabled(!ignoreLocationCheckBox->isChecked());
         autoTrackCheckBox->setEnabled(!ignoreLocationCheckBox->isChecked());
     }
     if (source == ignoreDestinationCheckBox) {
         destinationBox->setEnabled(!ignoreDestinationCheckBox->isChecked());
         trackDestinationBox->setEnabled(!ignoreDestinationCheckBox->isChecked());
         autoDestinationTrackCheckBox->setEnabled(!ignoreDestinationCheckBox->isChecked());
     }
     if (source == ignoreFinalDestinationCheckBox) {
         finalDestinationBox->setEnabled(!ignoreFinalDestinationCheckBox->isChecked());
         finalDestTrackBox->setEnabled(!ignoreFinalDestinationCheckBox->isChecked());
         autoFinalDestTrackCheckBox->setEnabled(!ignoreFinalDestinationCheckBox->isChecked());
     }
     if (source == ignoreTrainCheckBox) {
         trainBox->setEnabled(!ignoreTrainCheckBox->isChecked());
         autoTrainCheckBox->setEnabled(!ignoreTrainCheckBox->isChecked());
     }
 }

 /*protected*/ void RollingStockSetFrame::enableComponents(bool enabled) {
     // combo boxes
     locationBox->setEnabled(!ignoreLocationCheckBox->isChecked() & enabled);
     trackLocationBox->setEnabled(!ignoreLocationCheckBox->isChecked() & enabled);
     destinationBox->setEnabled(!ignoreDestinationCheckBox->isChecked() & enabled);
     trackDestinationBox->setEnabled(!ignoreDestinationCheckBox->isChecked() & enabled);
     finalDestinationBox->setEnabled(!ignoreFinalDestinationCheckBox->isChecked() & enabled);
     finalDestTrackBox->setEnabled(!ignoreFinalDestinationCheckBox->isChecked() & enabled);
     trainBox->setEnabled(!ignoreTrainCheckBox->isChecked() & enabled);
     // checkboxes
     autoTrackCheckBox->setEnabled(!ignoreLocationCheckBox->isChecked() & enabled);
     autoDestinationTrackCheckBox->setEnabled(!ignoreDestinationCheckBox->isChecked() & enabled);
     autoFinalDestTrackCheckBox->setEnabled(!ignoreFinalDestinationCheckBox->isChecked() & enabled);
     autoTrainCheckBox->setEnabled(!ignoreTrainCheckBox->isChecked() & enabled);
     locationUnknownCheckBox->setEnabled(!ignoreStatusCheckBox->isChecked());
     outOfServiceCheckBox->setEnabled(!ignoreStatusCheckBox->isChecked() & enabled);

     ignoreStatusCheckBox->setEnabled(enabled);
     ignoreLocationCheckBox->setEnabled(enabled);
     ignoreDestinationCheckBox->setEnabled(enabled);
     ignoreFinalDestinationCheckBox->setEnabled(Setup::isCarRoutingEnabled() & enabled);
     ignoreTrainCheckBox->setEnabled(enabled);
 }

 // location combo box
 /*public*/ void RollingStockSetFrame::comboBoxActionPerformed(QWidget* ae)
 {
  QComboBox* source = (QComboBox*)ae;
     if (source == locationBox) {
         updateLocationTrackComboBox();
     }
     if (source == destinationBox || source == trainBox) {
         updateDestinationTrackComboBox();
     }
 }

 /*protected*/ void RollingStockSetFrame::updateLocationComboBoxes() {
     log->debug("update location combo boxes");
     if (_rs != NULL) {
         locationBox->setCurrentIndex(locationBox->findData(VPtr<Location>::asQVariant(_rs->getLocation())));
     }
     // now update track combo boxes
     updateLocationTrackComboBox();
 }

 /*protected*/ void RollingStockSetFrame::updateLocationTrackComboBox() {
     log->debug("update location track combobox");
     if (locationBox->currentText() == NULL) {
         trackLocationBox->clear();
     } else {
         log->debug(tr("RollingStockFrame sees location: %1").arg(locationBox->currentText()));
         Location* l =  VPtr<Location>::asPtr(locationBox->itemData(locationBox->currentIndex()));
         l->updateComboBox(trackLocationBox, _rs, autoTrackCheckBox->isChecked(), false);
         if (_rs != NULL && _rs->getLocation() != NULL && _rs->getLocation()==(l)
                 && _rs->getTrack() != NULL) {
             trackLocationBox->setCurrentIndex(trackLocationBox->findData(VPtr<Track>::asQVariant(_rs->getTrack())));
         }
     }
 }

 /*protected*/ void RollingStockSetFrame::updateDestinationComboBoxes() {
     log->debug("update destination combo boxes");
     if (_rs != NULL) {
         destinationBox->setCurrentIndex(destinationBox->findData(VPtr<Location>::asQVariant(_rs->getDestination())));
     }
     // now update track combo boxes
     updateDestinationTrackComboBox();
 }

 /*protected*/ void RollingStockSetFrame::updateDestinationTrackComboBox() {
     log->debug("update destination track combobox");
     if (destinationBox->currentText() == NULL) {
         trackDestinationBox->clear();
     } else {
         log->debug(tr("RollingStockFrame sees destination: %1").arg(destinationBox->currentText()));
         Location* loc = VPtr<Location>::asPtr(destinationBox->itemData(destinationBox->currentIndex()));
         Track* track = NULL;
         if (trackDestinationBox->currentText() != NULL) {
             track =  VPtr<Track>::asPtr(trackDestinationBox->itemData(trackDestinationBox->currentIndex()));
         }
         loc->updateComboBox(trackDestinationBox, _rs, autoDestinationTrackCheckBox->isChecked(), true);
         // check for staging, add track if train is built and terminates into staging
         if (autoDestinationTrackCheckBox->isChecked() && trainBox->itemData(trainBox->currentIndex()) != QVariant())
         {
             Train* train = VPtr<Train>::asPtr(trainBox->itemData(trainBox->currentIndex()));
             if (train->isBuilt() && train->getTerminationTrack() != NULL
                     && train->getTerminationTrack()->getLocation() == loc) {
                 trackDestinationBox->addItem(train->getTerminationTrack()->getName(),VPtr<Track>::asQVariant(train->getTerminationTrack()));
             }
         }
         if (_rs != NULL && _rs->getDestination() != NULL && _rs->getDestination()==(loc)) {
             if (_rs->getDestinationTrack() != NULL) {
                 trackDestinationBox->setCurrentIndex(trackDestinationBox->findData(VPtr<Track>::asQVariant(_rs->getDestinationTrack())));
             } else if (track != NULL) {
                 trackDestinationBox->setCurrentIndex(trackDestinationBox->findData( VPtr<Track>::asQVariant(track)));
             }
         }
     }
 }

 /*protected*/ void RollingStockSetFrame::updateTrainComboBox() {
     log->debug("update train combo box");
     trainManager->updateTrainComboBox(trainBox);
     if (_rs != NULL) {
         trainBox->setCurrentIndex(trainBox->findData(VPtr<Train>::asQVariant(_rs->getTrain())));
     }
 }

 /*protected*/ void RollingStockSetFrame::packFrame() {
     adjustSize();
     setVisible(true);
 }

 /*public*/ void RollingStockSetFrame::dispose() {
     if (_rs != NULL) {
         //_rs->removePropertyChangeListener(this);
      disconnect(_rs->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     //LocationManager.instance().removePropertyChangeListener(this);
     disconnect(LocationManager::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     //trainManager.removePropertyChangeListener(this);
     disconnect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     OperationsFrame::dispose();
 }

 /*public*/ void RollingStockSetFrame::propertyChange(PropertyChangeEvent* e) {
     log->debug(tr("PropertyChange (%1) new: (%2)").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateComboBoxes();
     }
     if (e->getPropertyName()==(TrainManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateTrainComboBox();
     }
     if (e->getPropertyName()==(RollingStock::TRACK_CHANGED_PROPERTY)) {
         updateLocationComboBoxes();
     }
     if (e->getPropertyName()==(RollingStock::DESTINATION_TRACK_CHANGED_PROPERTY)) {
         updateDestinationComboBoxes();
     }
     if (e->getPropertyName()==(RollingStock::TRAIN_CHANGED_PROPERTY)) {
         if (_rs != NULL) {
             trainBox->setCurrentIndex(trainBox->findData(VPtr<Train>::asQVariant(_rs->getTrain())));
         }
     }
 }

}
