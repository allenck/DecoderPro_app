#include "yardmasterpanel.h"
#include "control.h"
#include <QComboBox>
#include <QPushButton>
#include "route.h"
#include "train.h"
#include "rollingstock.h"
#include "car.h"
#include <QBoxLayout>
#include "htmltextedit.h"
#include <QGroupBox>
#include <QLabel>
#include "location.h"
#include "setup.h"
#include "trainmanager.h"
#include "traincommon.h"
#include "rosterentry.h"
#include "routelocation.h"
#include "htmltextedit.h"
#include <QScrollArea>
#include "instancemanager.h"
#include "borderfactory.h"
#include "jpanel.h"

namespace Operations
{
/**
 * Yardmaster Frame. Shows work at one location.
 *
 * @author Dan Boudreau Copyright (C) 2013
 * @version $Revision: 18630 $
 */
///*public*/ class YardmasterQWidget* extends CommonConductorYardmasterQWidget* {

 /**
  *
  */
 //private static final long serialVersionUID = -88218348551032298L;

 /*protected*/ /*static*/ /*final*/ bool YardmasterPanel::IS_MANIFEST = false;


 /*public*/ YardmasterPanel::YardmasterPanel(QWidget* parent)
  : CommonConductorYardmasterPanel(parent)
 {
  //this(NULL);
  common(NULL);
 }

 /*public*/ YardmasterPanel::YardmasterPanel(Location* location ,QWidget* parent)
  : CommonConductorYardmasterPanel(parent) {
     //super();
     common(location);

 }
 void YardmasterPanel::common(Location* location)
 {
  log = new Logger("log");
  _visitNumber = 1;

    // text panes
  textSwitchListComment = new HtmlTextEdit();

      // combo boxes
  trainComboBox = new JComboBox();
  trainVisitComboBox = new JComboBox();

      // buttons
  nextButton = new QPushButton(tr("Next"));

   // panels
   pTrainVisit = new JPanel();
  initComponents();
  _location = location;

  // row 2
  QWidget* pRow2 = new QWidget();
  //pRow2->setLayout(new BoxLayout(pRow2, BoxLayout.X_AXIS));
  pRow2->setLayout(new QHBoxLayout);

  pRow2->layout()->addWidget(pLocationName); // row 2a (location name)
  pRow2->layout()->addWidget(pRailRoadName); // row 2b (railroad name)

  // row 5 (switch list comment)
  //textSwitchListComment->setBorder(BorderFactory.createTitledBorder(tr("Comment")));
  //textSwitchListComment->setBackground(NULL);
  textSwitchListComment->setReadOnly(true);
  textSwitchListComment->setMaximumSize(QSize(2000, 200));

  // row 6
  QWidget* pRow6 = new QWidget();
  //pRow6->setLayout(new BoxLayout(pRow6, BoxLayout.X_AXIS));
  pRow6->setLayout(new QHBoxLayout);

  // row 6a (train name)
  JPanel* pTrainName = new JPanel();
  pTrainName->setBorder(BorderFactory::createTitledBorder(tr("Train")));
  pTrainName->setLayout(new QHBoxLayout);
  pTrainName->layout()->addWidget(trainComboBox);
  // add next button for web server
  pTrainName->layout()->addWidget(nextButton);

  // row 6b (train visit)
  pTrainVisit->setBorder(BorderFactory::createTitledBorder(tr("Visit")));
  pTrainVisit->setLayout(new QHBoxLayout);
  pTrainVisit->layout()->addWidget(trainVisitComboBox);

  pRow6->layout()->addWidget(pTrainName);
  pRow6->layout()->addWidget(pTrainVisit);
  pRow6->layout()->addWidget(pTrainDescription); // row 6c (train description)

  pButtons->setMaximumSize(QSize(2000, 200));

  thisLayout->addWidget(pRow2);
  thisLayout->addWidget(pRow6);
  thisLayout->addWidget(textLocationCommentGB);
  thisLayout->addWidget(textSwitchListComment);
  thisLayout->addWidget(textTrainCommentGB);
  thisLayout->addWidget(textTrainRouteCommentGB);
  thisLayout->addWidget(textTrainRouteLocationCommentGB);
  locoPane->setWidget(pLocos);
  thisLayout->addWidget(locoPaneFrame);
  thisLayout->addWidget(pWorkPanes);
  movePane->setWidget(pMoves);
  thisLayout->addWidget(movePaneFrame);
  thisLayout->addWidget(pStatus);
  thisLayout->addWidget(pButtons);

  if (_location != NULL) {
      textLocationName->setText(_location->getName());
      textLocationCommentPane->setHtml(_location->getComment());
      textLocationCommentGB->setVisible(_location->getComment()!=(Location::NONE)
              && Setup::isPrintLocationCommentsEnabled());
      textSwitchListComment->setText(_location->getSwitchListComment());
      textSwitchListComment->setVisible(_location->getSwitchListComment()!=(Location::NONE));
      updateTrainsComboBox();
  }

  this->update();

  addComboBoxAction(trainComboBox);
  addComboBoxAction(trainVisitComboBox);

  addButtonAction(nextButton);

  // listen for trains being built
  addTrainListeners();

  setVisible(true);

 }

 // Select, Clear, and Set Buttons
 //@Override
 /*public*/ void YardmasterPanel::buttonActionPerformed(QWidget* ae)
 {
  QPushButton* source = (QPushButton*)ae;
     if (source == nextButton) {
         nextButtonAction();
     }
     CommonConductorYardmasterPanel::buttonActionPerformed(ae);
     update();
 }

 /*private */ void YardmasterPanel::nextButtonAction()
 {
  log->debug("next button activated");
  if (trainComboBox->count() > 1)
  {
   if (pTrainVisit->isVisible())
   {
    int index = trainVisitComboBox->currentIndex() + 1;
    if (index < trainVisitComboBox->count())
    {
     trainVisitComboBox->setCurrentIndex(index);
     return; // done
    }
   }
   int index = trainComboBox->currentIndex();
   // index = -1 if first item (NULL) in trainComboBox
   if (index == -1) {
       index = 1;
   } else {
       index++;
   }
   if (index >= trainComboBox->count()) {
       index = 0;
   }
   trainComboBox->setCurrentIndex(index);
  }
 }

 // Select Train and Visit
 //@Override
 /*protected*/ void YardmasterPanel::comboBoxActionPerformed(QWidget* ae)
 {
  QComboBox* source = (QComboBox*)ae;
     // made the combo box not visible during updates, so ignore if not visible
     if (source == trainComboBox && trainComboBox->isVisible()) {
         _train = NULL;
         if (trainComboBox->currentText() != NULL) {
             _train = (Train*) VPtr<Train>::asPtr(trainComboBox->currentData());
             _visitNumber = 1;
         }
         clearAndUpdate();
     }
     // made the combo box not visible during updates, so ignore if not visible
     if (source == trainVisitComboBox && trainVisitComboBox->isVisible()) {
         if (trainVisitComboBox->currentText() != NULL) {
             _visitNumber =  trainVisitComboBox->currentData().toInt();
             clearAndUpdate();
         }
     }
 }

 /*private*/ void YardmasterPanel::clearAndUpdate() {
     trainCommon->clearUtilityCarTypes(); // reset the utility car counts
     checkBoxes.clear();
     isSetMode = false;
     update();
 }

 /*private*/ void YardmasterPanel::update()
 {
     log->debug("queue update");
     // use invokeLater to prevent deadlock
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
             log->debug(tr("update, setMode: %1").arg(isSetMode));
             initialize();

             // turn everything off and re-enable if needed
             pButtons->setVisible(false);
             pTrainVisit->setVisible(false);
             trainVisitComboBox->setVisible(false); // Use visible as a flag to ignore updates
             textTrainCommentGB->setVisible(false);
             textTrainRouteCommentGB->setVisible(false);
             textTrainRouteLocationCommentGB->setVisible(false);

             textTrainDescription->setText("");
             textStatus->setText("");

             if (_train != NULL && _train->getRoute() != NULL) {
                 Route* route = _train->getRoute();
                 pButtons->setVisible(true);
                 textTrainDescription->setText(_train->getDescription());
                 // show train comment box only if there's a comment
                 textTrainCommentPane->setVisible(_train->getComment()!=(Train::NONE));
                 textTrainCommentPane->setText(_train->getComment());
                 // show route comment box only if there's a route comment
                 textTrainRouteCommentPane->setVisible(route->getComment()!=(Route::NONE) && Setup::isPrintRouteCommentsEnabled());
                 textTrainRouteCommentPane->setText(route->getComment());
                 // Does this train have a unique railroad name?
                 if (_train->getRailroadName()!=(Train::NONE)) {
                     textRailRoadName->setText(_train->getRailroadName());
                 } else {
                     textRailRoadName->setText(Setup::getRailroadName());
                 }

                 // determine how many times this train visits this location and if it is the last stop
                 RouteLocation* rl = NULL;
                 QList<RouteLocation*>* routeList = route->getLocationsBySequenceList();
                 int visitNumber = 0;
                 for (int i = 0; i < routeList->size(); i++) {
                     if (TrainCommon::splitString(routeList->at(i)->getName())==(
                             TrainCommon::splitString(_location->getName()))) {
                         visitNumber++;
                         if (visitNumber == _visitNumber) {
                             rl = routeList->at(i);
                         }
                     }
                 }

                 if (rl != NULL) {
                     // update visit numbers
                     if (visitNumber > 1) {
                         trainVisitComboBox->clear(); // this fires an action change!
                         for (int i = 0; i < visitNumber; i++) {
                             trainVisitComboBox->addItem(QString::number(i + 1), i+1);
                         }
                         trainVisitComboBox->setCurrentIndex(trainVisitComboBox->findData(_visitNumber));
                         trainVisitComboBox->setVisible(true); // now pay attention to changes
                         pTrainVisit->setVisible(true); // show the visit panel
                     }

                     // update comment and location name
                     textTrainRouteLocationCommentPane->setVisible(rl->getComment()!=(RouteLocation::NONE)
                             && Setup::isSwitchListRouteLocationCommentEnabled());
                     textTrainRouteLocationCommentPane->setHtml(rl->getComment());
                     textLocationName->setText(rl->getLocation()->getName()); // show name including hyphen and number

                     // check for locos
                     updateLocoPanes(rl);

                     // now update the car pick ups and set outs
                     blockCars(rl, IS_MANIFEST);

                     textStatus->setText(getStatus(rl, IS_MANIFEST));
                 }
                 updateComplete();
             }
//         }
//     });
 }

 /*private*/ void YardmasterPanel::updateTrainsComboBox() {
     QVariant selectedItem = trainComboBox->currentData();
     trainComboBox->setVisible(false); // used as a flag to ignore updates
     trainComboBox->clear();
     trainComboBox->addItem(NULL);
     if (_location != NULL) {
         QList<Train*> trains = trainManager->getTrainsArrivingThisLocationList(_location);
//         trains.stream().filter((train) -> (TrainCommon::isThereWorkAtLocation(train, _location))).forEach(
//                 (train) -> {
//                     trainComboBox.addItem(train);
//                 });
         foreach (Train* train, trains)
         {
          if(TrainCommon::isThereWorkAtLocation(train, _location))
          {
           trainComboBox->addItem(train->getName(), VPtr<Train>::asQVariant(train));
          }
         }
     }
     if (selectedItem != QVariant()) {
         trainComboBox->setCurrentIndex(trainComboBox->findData(selectedItem));
     }
     trainComboBox->setVisible(true);
 }

 /*private*/ void YardmasterPanel::addTrainListeners() {
     log->debug("Adding train listerners");
     QList<Train*> trains = ((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->getTrainsByIdList();
//     trains.stream().forEach((train) -> {
//         Train::addPropertyChangeListener(this);
//     });
     foreach(Train* train, trains)
     {
      connect(train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }

     // listen for new trains being added
     //TrainManager::instance().addPropertyChangeListener(this);
     connect(((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->pcs,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
#if 0
 private void removeTrainListeners() {
     log->debug("Removing train listerners");
     List<Train> trains = TrainManager.instance().getTrainsByIdList();
     trains.stream().forEach((train) -> {
         Train::removePropertyChangeListener(this);
     });
     TrainManager.instance().removePropertyChangeListener(this);
 }

 /*public*/ void dispose() {
     removeTrainListeners();
     removePropertyChangeListerners();
 }
#endif
 //@Override
 /*public*/ void YardmasterPanel::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
      ->getNewValue().toString()));
     }
     if ((e->getPropertyName()==(RollingStock::ROUTE_LOCATION_CHANGED_PROPERTY) && e->getNewValue().toString() == NULL)
             || (e->getPropertyName()==(RollingStock::ROUTE_DESTINATION_CHANGED_PROPERTY) && e->getNewValue().toString() == NULL)
             || e->getPropertyName()==(RollingStock::TRAIN_CHANGED_PROPERTY)) {
         // remove car from list
         if (e->getSource()->metaObject()->className()==("Car")) {
             Car* car = (Car*) e->getSource();
             removeCarFromList(car);
         }
         update();
     }
     if (e->getPropertyName()==(Train::BUILT_CHANGED_PROPERTY)) {
         updateTrainsComboBox();
     }
 }
}
