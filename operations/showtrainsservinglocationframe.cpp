#include "showtrainsservinglocationframe.h"
#include "routelocation.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "location.h"
#include "track.h"
#include "train.h"
#include "control.h"
#include <QGroupBox>
#include <QScrollArea>
#include <QCheckBox>
#include "jcombobox.h"
#include "trainmanager.h"
#include "route.h"
#include "cartypes.h"
#include <QLabel>

namespace Operations
{
 /**
  * Frame to show which trains can service this location
  *
  * @author Dan Boudreau Copyright (C) 2014
  * @version $Revision: 24984 $
  */
 ///*public*/ class ShowTrainsServingLocationFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 2234885033768829476L;
 // location
 /*private*/ /*static*/ bool ShowTrainsServingLocationFrame::isShowAllTrains = true;

 /*public*/ ShowTrainsServingLocationFrame::ShowTrainsServingLocationFrame(QWidget* parent)
    : OperationsFrame(parent)
 {
  //super();
  log = new Logger("ShowTrainsServingLocationFrame");
 }

 /*public*/ void ShowTrainsServingLocationFrame::initComponents(Location* location, Track* track) {

     _location = location;
     _track = track;

     // general GUI config
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     // Set up the panels
     QGroupBox* pOptions = new QGroupBox();
     pOptions->setLayout(new GridBagLayout());
     //pOptions.setBorder(BorderFactory.createTitledBorder(tr("Options")));
     pOptions->setStyleSheet(gbStyleSheet);
     pOptions->setTitle(tr("Options"));

     addItem(pOptions, showAllTrainsCheckBox, 0, 0);

     QGroupBox* pCarType = new QGroupBox();
     pCarType->setLayout(new GridBagLayout());
     //pCarType.setBorder(BorderFactory.createTitledBorder(tr("Type")));
     pCarType->setStyleSheet(gbStyleSheet);
     pCarType->setTitle(tr("Type"));
     pCarType->setMaximumSize(QSize(2000, 50));

     addItem(pCarType, typeComboBox, 0, 0);

     pTrains->setLayout(new GridBagLayout());
     QScrollArea* trainsPane = new QScrollArea(/*pTrains*/);
     //trainsPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
     //trainsPane.setBorder(BorderFactory.createTitledBorder(tr("Trains")));
     pTrains->setStyleSheet(gbStyleSheet);
     pTrains->setTitle(tr("Trains"));

     thisLayout->addWidget(pOptions);
     thisLayout->addWidget(pCarType);
     thisLayout->addWidget(trainsPane);
     trainsPane->setWidget(pTrains);

     // show all trains
     showAllTrainsCheckBox->setToolTip
       (tr("When unselected, only show trains that can work this location"));
     addCheckBoxAction(showAllTrainsCheckBox);
     showAllTrainsCheckBox->setChecked(isShowAllTrains);

     // setup combo box
     updateComboBox();
     typeComboBox->setCurrentIndex(typeComboBox->findText(NONE));
     addComboBoxAction(typeComboBox);

     // increase width of combobox so large text names display properly
     QSize boxsize = QSize(typeComboBox->minimumWidth(), typeComboBox->minimumHeight()); //typeComboBox->getMinimumSize();
     if (boxsize != QSize()) {
         //boxsize.setSize(boxsize.width() + 10, boxsize.height());
      boxsize.setWidth(boxsize.width() + 10);
         typeComboBox->setMinimumSize(boxsize);
     }

     updateTrainPane();

     //location.addPropertyChangeListener(this);
     connect(location, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     addPropertyChangeAllTrains();

     if (_track != NULL) {
         //_track.addPropertyChangeListener(this);
      connect(_track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

         setTitle(tr("Show Trains Servicing %1").arg(_track->getName()));
     } else {
         setTitle(tr("Show Trains Servicing %1").arg(_location->getName()));
     }

//     setPreferredSize(NULL);

     initMinimumSize();
 }

 /*private*/ void ShowTrainsServingLocationFrame::updateTrainPane()
 {
  //pTrains.removeAll();
  QLayoutItem* item;
  while ( ( item = pTrains->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }
  int y = 0;
  foreach (Train* train, TrainManager::instance()->getTrainsByNameList())
  {
   Route* route = train->getRoute();
   if (route == NULL) {
       continue;
   }
   foreach (RouteLocation* rl, *route->getLocationsBySequenceList())
   {
    if (rl->getName()==(_location->getName()))
    {
     bool pickup = false;
     bool setout = false;
     // monitor move count in the route for this location
     //train.getRoute().removePropertyChangeListener(this);
     disconnect(train->getRoute(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //train.getRoute().addPropertyChangeListener(this);
     connect(train->getRoute(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     if(rl->isPickUpAllowed()
             && rl->getMaxCarMoves() > 0
             && !train->skipsLocation(rl->getId())
             && (typeComboBox->currentText() == NULL || typeComboBox->currentText()==(NONE) || train
             ->acceptsTypeName( typeComboBox->currentText()))
             && (train->isLocalSwitcher() || (rl->getTrainDirection() & _location->getTrainDirections()) > 0)
             && (train->isLocalSwitcher() || _track == NULL || ((rl->getTrainDirection() & _track
             ->getTrainDirections()) > 0))
             && (_track == NULL || _track->acceptsPickupTrain(train))) {
         pickup = true;
     }
     if (rl->isDropAllowed()
             && rl->getMaxCarMoves() > 0
             && !train->skipsLocation(rl->getId())
             && (typeComboBox->currentText() == NULL || typeComboBox->currentText()==(NONE) || train
             ->acceptsTypeName( typeComboBox->currentText()))
             && (train->isLocalSwitcher() || (rl->getTrainDirection() & _location->getTrainDirections()) > 0)
             && (train->isLocalSwitcher() || _track == NULL || ((rl->getTrainDirection() & _track
             ->getTrainDirections()) > 0)) && (_track == NULL || _track->acceptsDropTrain(train))) {
         setout = true;
     }
     // now display results
     if (showAllTrainsCheckBox->isChecked() || pickup || setout)
     {
         addItemLeft(pTrains, new QLabel(train->getName()), 0, y);
         if (pickup) {
             addItem(pTrains, new QLabel(tr("Okay pick up")), 1, y);
         } else {
             addItem(pTrains, new QLabel(tr("No pick up")), 1, y);
         }
         if (setout) {
             addItem(pTrains, new QLabel(tr("Okay Set Out")), 2, y);
         } else {
             addItem(pTrains, new QLabel(tr("No Set Out")), 2, y);
         }
     }
     y++;
    }
   }
  }
  //pTrains->repaint();
  pTrains->update();
 }

 //edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*public*/ void ShowTrainsServingLocationFrame::checkBoxActionPerformed(QWidget* ae) {
     log->debug("check box action");
     isShowAllTrains = showAllTrainsCheckBox->isChecked();
     updateTrainPane();
 }

 /*public*/ void ShowTrainsServingLocationFrame::comboBoxActionPerformed(QWidget* ae) {
     log->debug("combo box action");
     if (typeComboBox->isEnabled() && ae==(typeComboBox)) {
         updateTrainPane();
         if (typeComboBox->currentText() != NULL) {
             comboBoxSelect =  typeComboBox->currentText();
         }
     }
 }

 /*private*/ void ShowTrainsServingLocationFrame::updateComboBox() {
     log->debug("update combobox");
     typeComboBox->setEnabled(false);
     CarTypes::instance()->updateComboBox(typeComboBox);
     // remove car types not serviced by this location and track
     for (int i = typeComboBox->count() - 1; i >= 0; i--) {
         QString type = typeComboBox->itemText(i);
         if (_location != NULL && !_location->acceptsTypeName(type)) {
             typeComboBox->removeItem(typeComboBox->findText(type));
         }
         if (_track != NULL && !_track->acceptsTypeName(type)) {
             typeComboBox->removeItem(typeComboBox->findText(type));
         }
     }
     typeComboBox->insertItem(0, NONE);

     if (comboBoxSelect == NULL) {
         typeComboBox->setCurrentIndex(typeComboBox->findText(NONE));
     } else {
         typeComboBox->setCurrentIndex(typeComboBox->findText(comboBoxSelect));
         if (typeComboBox->currentText() != NULL && typeComboBox->currentText()!=(comboBoxSelect)) {
          typeComboBox->setCurrentIndex(typeComboBox->findText(NONE)); // selected object has been removed
         }
         updateTrainPane();
     }
     typeComboBox->setEnabled(true);
 }

 /*public*/ void ShowTrainsServingLocationFrame::dispose() {
     //_location.removePropertyChangeListener(this);
 disconnect(_location, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     if (_track != NULL) {
         //_track->removePropertyChangeListener(this);
      disconnect(_track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }

     //CarTypes.instance().removePropertyChangeListener(this);
     disconnect(CarTypes::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     removePropertyChangeAllTrains();
     OperationsFrame::dispose();
 }

 /*public*/ void ShowTrainsServingLocationFrame::addPropertyChangeAllTrains()
 {
  //TrainManager::instance().addPropertyChangeListener(this);
  connect(TrainManager::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     foreach (Train* train, TrainManager::instance()->getTrainsByNameList()) {
         //train.addPropertyChangeListener(this);
      connect(train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*public*/ void ShowTrainsServingLocationFrame::removePropertyChangeAllTrains() {
     //TrainManager.instance().removePropertyChangeListener(this);
 disconnect(TrainManager::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     foreach (Train* train, TrainManager::instance()->getTrainsByNameList()) {
         //train.removePropertyChangeListener(this);
      disconnect(train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         if (train->getRoute() != NULL) {
             //train.getRoute().removePropertyChangeListener(this);
          connect(train->getRoute(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     }
 }

 /*public*/ void ShowTrainsServingLocationFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("PropertyChange (%1) new ({%2)").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
     }
     if (e->getPropertyName()==(Location::TYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::TYPES_CHANGED_PROPERTY)) {
         updateComboBox();
     }
     if (e->getPropertyName()==(Location::TRAINDIRECTION_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::TRAINDIRECTION_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::DROP_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::PICKUP_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::TRAIN_ROUTE_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::TYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::STOPS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Route::LISTCHANGE_CHANGED_PROPERTY)) {
         updateTrainPane();
     }
     if (e->getPropertyName()==(TrainManager::LISTLENGTH_CHANGED_PROPERTY)) {
         removePropertyChangeAllTrains();
         addPropertyChangeAllTrains();
     }
 }
/*public*/ QString ShowTrainsServingLocationFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.tools.ShowTrainsServingLocationFrame";
}


}
