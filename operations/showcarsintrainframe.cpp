#include "showcarsintrainframe.h"
#include <QLabel>
#include "train.h"
#include "car.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "flowlayout.h"
#include <QScrollArea>
#include "traincommon.h"
#include "control.h"
#include "carmanager.h"
#include <QGroupBox>
#include "htmltextedit.h"
#include "routelocation.h"
#include "trainmanifesttext.h"
#include "setup.h"
#include "location.h"
#include "route.h"
#include <QCheckBox>
#include <QThread>
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
/**
 * Show Cars In Train Frame. This frame lists all cars assigned to a train in
 * the correct blocking order. Also show which cars are to be picked up and set
 * out at each location in the train's route.
 *
 * @author Dan Boudreau Copyright (C) 2012
 * @version $Revision: 18630 $
 */
///*public*/ class ShowCarsInTrainFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -6230722380444056252L;
 /*public*/ ShowCarsInTrainFrame::ShowCarsInTrainFrame(QWidget* parent) : OperationsFrame(parent) {
     //super();
 log = new Logger("ShowCarsInTrainFrame");
     _train = NULL;
     carManager = ((CarManager*)InstanceManager::getDefault("Operations::CarManager"));
     trainCommon = new TrainCommon();

     // labels
     textTrainName = new QLabel();
     textLocationName = new QLabel();
     textNextLocationName = new QLabel();
     textStatus = new HtmlTextEdit();
     textPickUp = new QLabel(tr("Pick up"));
     textInTrain = new QLabel(tr("In Train"));
     textSetOut = new QLabel(tr("Set out"));

     // major buttons
     // radio buttons
     // text field
     // combo boxes
     // panels
     pCars = new JPanel();
 }

 /*public*/ void ShowCarsInTrainFrame::initComponents(Train* train) {
     _train = train;

     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     JPanel* carPaneFrame = new JPanel;
     carPaneFrame->setLayout(new QVBoxLayout);
     carPane = new QScrollArea(/*pCars*/);
     carPane->setWidgetResizable(true);
     carPaneFrame->layout()->addWidget(carPane);
     carPaneFrame->setBorder(BorderFactory::createTitledBorder(tr("Cars")));
     //carPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
// carPane.setPreferredSize(new Dimension(200, 300));

     // Set up the panels
     // Layout the panel by rows
     // row 2
     QWidget* pRow2 = new QWidget();
     pRow2->setLayout(new QVBoxLayout);//(pRow2, BoxLayout.X_AXIS));

     // row 2a (train name)
     JPanel* pTrainName = new JPanel();
     pTrainName->setLayout(new QHBoxLayout);
     pTrainName->setBorder(BorderFactory::createTitledBorder(tr("Train")));
     pTrainName->layout()->addWidget(textTrainName);

     pRow2->layout()->addWidget(pTrainName);

     // row 6
     QWidget* pRow6 = new QWidget();
     pRow6->setLayout(new QHBoxLayout);//(pRow6, BoxLayout.X_AXIS));

     // row 10
     QWidget* pRow10 = new QWidget();
     pRow10->setLayout(new QHBoxLayout);//(pRow10, BoxLayout.X_AXIS));

     // row 10a (location name)
     JPanel* pLocationName = new JPanel();
     pLocationName->setBorder(BorderFactory::createTitledBorder("Location"));
     pLocationName->layout()->addWidget(textLocationName);

     // row 10c (next location name)
     JPanel* pNextLocationName = new JPanel();
     pNextLocationName->setBorder(BorderFactory::createTitledBorder(tr("Next Location")));
     pNextLocationName->layout()->addWidget(textNextLocationName);

     pRow10->layout()->addWidget(pLocationName);
     pRow10->layout()->addWidget(pNextLocationName);

     // row 12
     QWidget* pRow12 = new QWidget();
     pRow12->setLayout(new QHBoxLayout);//(pRow12, BoxLayout.X_AXIS));

     pCars->setLayout(new GridBagLayout());
     carPane->setWidget(pCars);
     pRow12->layout()->addWidget(carPaneFrame);

     // row 13
//		JPanel pStatus = new JPanel();
//		pStatus.setLayout(new GridBagLayout());
     //textStatus.setBorder(BorderFactory.createTitledBorder(""));
     JPanel* textStatusFrame = new JPanel;
     textStatusFrame->setLayout(new QVBoxLayout);
     textStatusFrame->setBorder(BorderFactory::createTitledBorder(""));
     textStatusFrame->layout()->addWidget(textStatus);
//		addItem(pStatus, textStatus, 0, 0);
     //textStatus.setBackground(NULL);
     textStatus->setEditable(false);

     thisLayout->addWidget(pRow2);
     thisLayout->addWidget(pRow6);
     thisLayout->addWidget(pRow10);
     thisLayout->addWidget(pRow12);
     thisLayout->addWidget(textStatusFrame);

     update();

     if (_train != NULL) {
         setTitle(tr("TitleShowCarsInTrain") + " (" + _train->getName() + ")");

         // listen for train changes
         //_train->SwingPropertyChangeSupport::addPropertyChangeListener(this);
         connect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }

     // // build menu
     // JMenuBar menuBar = new JMenuBar();
     // JMenu toolMenu = new JMenu(tr("Tools"));
     // menuBar.add(toolMenu);
     // setJMenuBar(menuBar);
     // addHelpMenu("package.jmri.jmrit.operations.Operations_Trains", true);
     packFrame();
     setVisible(true);

 }

 /*private*/ void ShowCarsInTrainFrame::update()
{
 log->debug("queue update");
  // use invokeLater to prevent deadlock
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
   log->debug("update");
   if (_train == NULL || _train->getRoute() == NULL) {
       return;
   }
   textTrainName->setText(_train->getIconName());
   //pCars.removeAll();
   QLayoutItem* item;
   while ( ( item = pCars->layout()->takeAt( 0 ) ) != NULL )
   {
       delete item->widget();
       delete item;
   }
   RouteLocation* rl = _train->getCurrentLocation();
   if (rl != NULL)
   {
    textLocationName->setText(rl->getLocation()->getName());
    textNextLocationName->setText(_train->getNextLocationName());
    // add header
    int i = 0;
    addItemLeft(pCars, textPickUp, 0, 0);
    addItemLeft(pCars, textInTrain, 1, 0);
    addItemLeft(pCars, textSetOut, 2, i++);
    // block cars by destination
    foreach (RouteLocation* rld, *_train->getRoute()->getLocationsBySequenceList())
    {
     foreach (Car* car, *carManager->getByTrainDestinationList(_train))
     {
      if ((car->getTrack() == NULL || car->getRouteLocation() == rl)
              && car->getRouteDestination() == rld)
      {
       log->debug(tr("car (%1) routelocation (%2) track (%3) route destination (%4)").arg(car->toString()).arg(car
               ->getRouteLocation()->getName()).arg(car->getTrackName()).arg(car->getRouteDestination()->getName()));
       QCheckBox* checkBox = new QCheckBox(car->toString());
       if (car->getRouteDestination() == rl)
       {
           addItemLeft(pCars, checkBox, 2, i++); // set out
       } else if (car->getRouteLocation() == rl && car->getTrack() != NULL) {
           addItemLeft(pCars, checkBox, 0, i++); // pick up
       } else {
           addItemLeft(pCars, checkBox, 1, i++); // in train
       }
      }
     }
    }

    textStatus->setText(getStatus(rl));
   }
   else
   {
    textStatus->setText(TrainManifestText::getStringTrainTerminates().arg(
               _train->getTrainTerminatesName()));
   }
   pCars->update();
//  }
//     });

#if 1
  SCITFWorker* worker = new SCITFWorker(this);
  QThread* thread = new QThread();
  connect(thread, SIGNAL(started()), worker, SLOT(process()));
  connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
  connect(worker, SIGNAL(finished()), thread, SLOT(deleteLater()));
  worker->moveToThread(thread);
  thread->start();
 }

 SCITFWorker::SCITFWorker(ShowCarsInTrainFrame* scitf)
 {
  this->scitf = scitf;
 }
 void SCITFWorker::process()
 {
  scitf->log->debug("update");
  if (scitf->_train == NULL || scitf->_train->getRoute() == NULL) {
      return;
  }
  scitf->textTrainName->setText(scitf->_train->getIconName());
  //scitf->pCars->removeAll();
  if(scitf->pCars!= NULL && scitf->pCars->layout()!= NULL)
  {
   QObjectList ol = scitf->pCars->layout()->children();
   foreach (QObject* o, ol) {
    if(qobject_cast<QWidget*>(o) != NULL)
    {
     scitf->pCars->layout()->removeWidget((QWidget*)o);
     delete o;
    }
   }
  }RouteLocation* rl = scitf->_train->getCurrentLocation();
  if (rl != NULL) {
      scitf->textLocationName->setText(rl->getLocation()->getName());
      scitf->textNextLocationName->setText(scitf->_train->getNextLocationName());
      // add header
      int i = 0;
      scitf->addItemLeft(scitf->pCars, scitf->textPickUp, 0, 0);
      scitf->addItemLeft(scitf->pCars, scitf->textInTrain, 1, 0);
      scitf->addItemLeft(scitf->pCars, scitf->textSetOut, 2, i++);
      // block cars by destination
      for (RouteLocation* rld : *scitf->_train->getRoute()->getLocationsBySequenceList()) {
          for (Car* car : *scitf->carManager->getByTrainDestinationList(scitf->_train)) {
              if ((car->getTrack() == NULL || car->getRouteLocation() == rl)
                      && car->getRouteDestination() == rld) {
                  scitf->log->debug(tr("car (%1) routelocation (%2) track (%3) route destination (%4)").arg(car->toString()).arg(car
                          ->getRouteLocation()->toString()).arg(scitf->getName()).arg(car->getTrackName()).arg(car->getRouteDestination()->getName()));
                  QCheckBox* checkBox = new QCheckBox(car->toString());
                  if (car->getRouteDestination() == rl) {
                      scitf->addItemLeft(scitf->pCars, checkBox, 2, i++); // set out
                  } else if (car->getRouteLocation() == rl && car->getTrack() != NULL) {
                      scitf->addItemLeft(scitf->pCars, checkBox, 0, i++); // pick up
                  } else {
                      scitf->addItemLeft(scitf->pCars, checkBox, 1, i++); // in train
                  }
              }
          }
      }

      scitf->textStatus->setText(scitf->getStatus(rl));
  } else {
      scitf->textStatus->setText(TrainManifestText::getStringTrainTerminates().arg(
              scitf->_train->getTrainTerminatesName()));
  }
  scitf->pCars->update();
 }
#endif
 /*private*/ QString ShowCarsInTrainFrame::getStatus(RouteLocation* rl) {
     if (Setup::isPrintLoadsAndEmptiesEnabled()) {
         int emptyCars = _train->getNumberEmptyCarsInTrain(rl);
         return TrainManifestText::getStringTrainDepartsLoads().arg(
             TrainCommon::splitString(rl->getName())).arg(rl->getTrainDirectionString()).arg(
             _train->getNumberCarsInTrain(rl) - emptyCars).arg(emptyCars).arg(_train->getTrainLength(rl)).arg(
             Setup::getLengthUnit().toLower()).arg(_train->getTrainWeight(rl));
     } else {
         return TrainManifestText::getStringTrainDepartsCars().arg(
                 rl->getName()).arg(rl->getTrainDirectionString()).arg(_train->getNumberCarsInTrain()).arg(
                     _train->getTrainLength(rl)).arg(Setup::getLengthUnit().toLower()).arg(
                     _train->getTrainWeight(rl));
     }
 }

 /*private*/ void ShowCarsInTrainFrame::packFrame() {
     setVisible(false);
     adjustSize();
     if (width() < 300) {
         resize(300, height());
     }
     if (height() < Control::panelHeight500) {
         resize(width(), Control::panelHeight500);
     }
     setMinimumSize(QSize(Control::panelWidth300, Control::panelHeight500));
     setVisible(true);
 }

 /*public*/ void ShowCarsInTrainFrame::dispose() {
     if (_train != NULL) {
         //_train->removePropertyChangeListener(this);
      disconnect(_train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     OperationsFrame::dispose();
 }

 /*public*/ void ShowCarsInTrainFrame::propertyChange(PropertyChangeEvent* e) {
     // if (Control.showProperty && log->isDebugEnabled())
 log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
         ->getNewValue().toString()));
     if (e->getPropertyName()==(Train::BUILT_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::TRAIN_MOVE_COMPLETE_CHANGED_PROPERTY)) {
         update();
     }
 }
 /*public*/ QString ShowCarsInTrainFrame::getClassName()
 {
  return "jmri.jmrit.operations.trains.tools.ShowCarsInTrainFrame";
 }

}
