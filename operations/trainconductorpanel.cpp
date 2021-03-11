#include "trainconductorpanel.h"
#include "train.h"
#include "control.h"
#include <QBoxLayout>
#include <QGroupBox>
#include "gridbaglayout.h"
#include <QLabel>
#include "jtextarea.h"
#include "route.h"
#include "setup.h"
#include "logger.h"
#include "routelocation.h"
#include "rollingstock.h"
#include "car.h"
#include "traincommon.h"
#include "location.h"
#include <QPushButton>
#include "htmltextedit.h"
#include <QScrollArea>
#include "jpanel.h"
#include "borderfactory.h"

namespace Operations
{
/**
 * Conductor Panel. Shows work for a train one location at a time.
 *
 * @author Dan Boudreau Copyright (C) 2011, 2013
 * @version $Revision: 18630 $
 */
//public class TrainConductorPanel extends CommonConductorYardmasterPanel {

 /**
  *
  */
 //private static final long serialVersionUID = 7149077790256321679L;

 /*protected*/ /*static*/ /*final*/ bool TrainConductorPanel::IS_MANIFEST = true;


 // major buttons
 /**
  * Default constructor required to use as JavaBean.
  */
 /*public*/ TrainConductorPanel::TrainConductorPanel(QWidget* parent)
     :  CommonConductorYardmasterPanel(parent)
 {
  common(NULL);
 }

 /*public*/ TrainConductorPanel::TrainConductorPanel(Train* train, QWidget* parent)
 :  CommonConductorYardmasterPanel(parent)
 {
     //super();
  common(train);
 }

 void TrainConductorPanel::common(Train *train)
 {
  log = new Logger("TrainConductorPanel");
  textTrainName = new QLabel();
  textTrainDepartureTime = new QLabel();
  textNextLocationName = new QLabel();

  // panels
  pTrainDepartureTime = new JPanel();

  initComponents();

  _train = train;

  // row 2
  QWidget* pRow2 = new QWidget();
  pRow2->setLayout(new QHBoxLayout); //(pRow2, BoxLayout.X_AXIS));

  // row 2a (train name)
  JPanel* pTrainName = new JPanel();
  pTrainName->setLayout(new QVBoxLayout);
  pTrainName->setBorder(BorderFactory::createTitledBorder(tr("Train")));
  pTrainName->layout()->addWidget(textTrainName);

  pRow2->layout()->addWidget(pTrainName);
  pRow2->layout()->addWidget(pTrainDescription);
  pRow2->layout()->addWidget(pRailRoadName);

  QWidget* pLocation = new QWidget();
  pLocation->setLayout(new QHBoxLayout);//(pLocation, BoxLayout.X_AXIS));

  // row 10b (train departure time)
  pTrainDepartureTime->setLayout(new QVBoxLayout);
  pTrainDepartureTime->setBorder(BorderFactory::createTitledBorder(tr("Departure Time (hh:mm)")));
  pTrainDepartureTime->layout()->addWidget(textTrainDepartureTime);

  // row 10c (next location name)
  JPanel* pNextLocationName = new JPanel();
  pNextLocationName->setBorder(BorderFactory::createTitledBorder(tr("Next Location")));
  pNextLocationName->setLayout(new QHBoxLayout);
  pNextLocationName->layout()->addWidget(textNextLocationName);

  pLocation->layout()->addWidget(pLocationName); // location name
  pLocation->layout()->addWidget(pTrainDepartureTime);
  pLocation->layout()->addWidget(pNextLocationName);

  // row 14
  QWidget* pRow14 = new QWidget();
  pRow14->setLayout(new QHBoxLayout); //(pRow14, BoxLayout.X_AXIS));
  pRow14->setMaximumSize(QSize(2000, 200));

  // row 14b
  JPanel* pMoveButton = new JPanel();
  pMoveButton->setLayout(new GridBagLayout());
  pMoveButton->setBorder(BorderFactory::createTitledBorder(tr("Train")));
  addItem(pMoveButton, moveButton, 1, 0);

  pRow14->layout()->addWidget(pButtons);
  pRow14->layout()->addWidget(pMoveButton);

  update();

  thisLayout->addWidget(pRow2);
  thisLayout->addWidget(pLocation);
  thisLayout->addWidget(textTrainCommentPane);
  thisLayout->addWidget(textTrainRouteCommentPane); // train route comment
  thisLayout->addWidget(textTrainRouteLocationCommentPane); // train route location comment
  thisLayout->addWidget(textLocationCommentPane);
  thisLayout->addWidget(locoPane);
  thisLayout->addWidget(pWorkPanes);
  thisLayout->addWidget(movePane);
  thisLayout->addWidget(pStatus);
  thisLayout->addWidget(pRow14);

  // setup buttons
  addButtonAction(moveButton);

  if (_train != NULL)
  {
   textTrainDescription->setText(_train->getDescription());
   // show train comment box only if there's a comment
   if (_train->getComment()==(Train::NONE)) {
       textTrainCommentPane->setVisible(false);
   } else {
       textTrainCommentPane->setText(_train->getComment());
   }
   // show route comment box only if there's a route comment
   if (_train->getRoute() != NULL) {
       textTrainRouteCommentPane->setVisible(_train->getRoute()->getComment()!=(Route::NONE)
               && Setup::isPrintRouteCommentsEnabled());
       textTrainRouteCommentPane->setText(_train->getRoute()->getComment());
   }

   // Does this train have a unique railroad name?
   if (_train->getRailroadName()!=(Train::NONE)) {
       textRailRoadName->setText(_train->getRailroadName());
   } else {
       textRailRoadName->setText(Setup::getRailroadName());
   }

   // listen for train changes
   //_train.addPropertyChangeListener(this);
   connect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }

  setVisible(true);

 }

 // Save, Delete, Add
 //@Override
 /*public*/ void TrainConductorPanel::buttonActionPerformed(QWidget* ae) {
     if (((QPushButton*)ae) == moveButton) {
         _train->move();
         return;
     }
     CommonConductorYardmasterPanel::buttonActionPerformed(ae);
     update();
 }

 /*private*/ void TrainConductorPanel::clearAndUpdate() {
     trainCommon->clearUtilityCarTypes(); // reset the utility car counts
     checkBoxes.clear();
     isSetMode = false;
     update();
 }

 /*private*/ void TrainConductorPanel::update()
 {
  log->debug("queue update");
  // use invokeLater to prevent deadlock
//     SwingUtilities.invokeLater(new Runnable() {
//         public void run() {
  log->debug(tr("update, setMode ") + (isSetMode?"true":"false"));
  initialize();
  if (_train != NULL && _train->getRoute() != NULL)
  {
   textTrainName->setText(_train->getIconName());
   RouteLocation* rl = _train->getCurrentLocation();
   if (rl != NULL)
   {
    textTrainRouteLocationCommentPane->setVisible(rl->getComment()!=(RouteLocation::NONE));
    textTrainRouteLocationCommentPane->setText(rl->getComment());
    textLocationName->setText(rl->getLocation()->getName());
    pTrainDepartureTime->setVisible(_train->isShowArrivalAndDepartureTimesEnabled()
            && rl->getDepartureTime()!=(RouteLocation::NONE));
    textTrainDepartureTime->setText(rl->getFormatedDepartureTime());
    textLocationCommentPane->setVisible(rl->getLocation()->getComment()!=(Location::NONE)
            && Setup::isPrintLocationCommentsEnabled());
    textLocationCommentPane->setText(rl->getLocation()->getComment());
    textNextLocationName->setText(_train->getNextLocationName());

    // check for locos
    updateLocoPanes(rl);

    // now update the car pick ups and set outs
    blockCars(rl, IS_MANIFEST);

    textStatus->setText(getStatus(rl, IS_MANIFEST));

   }
   else {
       moveButton->setEnabled(false);
       modifyButton->setEnabled(false);
   }
   updateComplete();
  }
//         }
//     });
 }

 //@Override
 /*public*/ void TrainConductorPanel::dispose() {
     removePropertyChangeListerners();
     if (_train != NULL) {
         //_train.removePropertyChangeListener(this);
      disconnect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 //@Override
 /*public*/ void TrainConductorPanel::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(Train::TRAIN_MOVE_COMPLETE_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::BUILT_CHANGED_PROPERTY)) {
         clearAndUpdate();
     }
     if ((e->getPropertyName()==(RollingStock::ROUTE_LOCATION_CHANGED_PROPERTY) && e->getNewValue() == QVariant())
             || (e->getPropertyName()==(RollingStock::ROUTE_DESTINATION_CHANGED_PROPERTY) && e
             ->getNewValue() == QVariant())
             || e->getPropertyName()==(RollingStock::TRAIN_CHANGED_PROPERTY)) {
         // remove car from list
         if (e->getSource()->metaObject()->className()==("Car")) {
             Car* car = (Car*) e->getSource();
             checkBoxes.remove("p" + car->getId());
             checkBoxes.remove("s" + car->getId());
             checkBoxes.remove("m" + car->getId());
             log->debug(tr("Car (%1) removed from list").arg(car->toString()));
         }
         this->update();
     }
 }

}
