#include "abstractoperationsserver.h"
#include "trainmanager.h"
#include "train.h"
#include "locationmanager.h"
#include "location.h"
#include "logger.h"
#include "engine.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * Abstract interface between the JMRI operations and a network connection
  *
  * @author Paul Bender Copyright (C) 2010
  * @author Dan Boudreau Copyright (C) 2012 (added checks for NULL train)
  * @author Rodney Black Copyright (C) 2012
  * @author Randall Wood Copyright (C) 2012, 2014
  * @version $Revision$
  */
 //abstract /*public*/ class AbstractOperationsServer implements PropertyChangeListener {

/*private*/ /*static*/ bool AbstractOperationsServer::exactLocationName = true;

 //@SuppressWarnings("LeakingThisInConstructor")
 /*public*/ AbstractOperationsServer::AbstractOperationsServer(QObject *parent) : QObject(parent)
 {
  log = new Logger("AbstractOperationsServer");
  exactLocationName = true;

     tm = ((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"));
     //tm.addPropertyChangeListener(this);
     connect(tm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(propertyChangeEvent*)));
     lm = ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"));
     //lm.addPropertyChangeListener(this);
     connect(lm, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     addPropertyChangeListeners();
     trains = QMap<QString, TrainListener*>();
 }

 /*public*/ /*abstract*/ void AbstractOperationsServer::sendTrainList() {}

 /*public*/ /*abstract*/ void AbstractOperationsServer::sendLocationList(){}

 /**
  * constructs a String containing the status of a train
  *
  * @param trainName is the name of the train. If not found in Operations, an
  *                  error message is sent to the client.
  * @return the train's status as known by Operations
  * @throws IOException on failure to send an error message to the client
  */
 /*public*/ QString AbstractOperationsServer::constructTrainStatus(QString trainName) //throws IOException
 {
     Train* train = tm->getTrainByName(trainName);
     if (train != NULL) {
         return train->getStatus();
     }
     sendErrorStatus("ERROR train name doesn't exist " + trainName);
     return NULL;
 }

 /**
  * constructs a String containing the location of a train
  *
  * @param trainName is the name of the desired train. If not found in
  *                  Operations, an error message is sent to the client
  * @return the train's location, as known by Operations
  * @throws IOException on failure to send an error message to the client
  */
 /*public*/ QString AbstractOperationsServer::constructTrainLocation(QString trainName) //throws IOException
{
     Train* train = tm->getTrainByName(trainName);
     if (train != NULL) {
         return train->getCurrentLocationName();
     }
     sendErrorStatus("ERROR train name doesn't exist " + trainName);
     return NULL;
 }

 /**
  * constructs a String containing the location of a train
  *
  * @param trainName    is the name of the desired train. If not found in
  *                     Operations, an error message is sent to the client
  * @param locationName
  * @return the train's location, as known by Operations
  * @throws IOException on failure to send an error message ot the client
  */
 /*public*/ QString AbstractOperationsServer::setTrainLocation(QString trainName, QString locationName)
         //throws IOException
 {
     log->debug("Set train " + trainName + " Location " + locationName);
     Train* train = tm->getTrainByName(trainName);
     if (train != NULL) {
         if (!exactLocationName && train->move(locationName)
                 || exactLocationName && train->moveToNextLocation(locationName)) {
             return constructTrainLocation(trainName);
         } else {
             sendErrorStatus("WARNING move of " + trainName + " to location " + locationName
                     + " failed. Train's current location " + train->getCurrentLocationName()
                     + " next location " + train->getNextLocationName());
         }
     } else {
         sendErrorStatus("ERROR train name doesn't exist " + trainName);
     }
     return NULL;
 }


 /*public*/ /*static*/ void AbstractOperationsServer::setExactLocationName(bool enabled) {
     exactLocationName = enabled;
 }

 /*public*/ /*static*/ bool AbstractOperationsServer::isExactLoationNameEnabled() {
     return exactLocationName;
 }

 /**
  * constructs a String containing the length of a train
  *
  * @param trainName is the name of the desired train. If not found in
  *                  Operations, an error message is sent to the client
  * @return the train's length, as known by Operations
  * @throws IOException on failure to send an error message to the client
  */
 /*public*/ QString AbstractOperationsServer::constructTrainLength(QString trainName) //throws IOException
{
     Train* train = tm->getTrainByName(trainName);
     if (train != NULL) {
         return QString::number(train->getTrainLength());
     }
     sendErrorStatus("ERROR train name doesn't exist " + trainName);
     return NULL;
 }

 /**
  * constructs a String containing the tonnage of a train
  *
  * @param trainName is the name of the desired train. If not found in
  *                  Operations, an error message is sent to the client
  * @return the train's tonnage, as known by Operations
  * @throws IOException on failure to send an error message to the client
  */
 /*public*/ QString AbstractOperationsServer::constructTrainWeight(QString trainName) //throws IOException
{
     Train* train = tm->getTrainByName(trainName);
     if (train != NULL) {
         return QString::number(train->getTrainWeight());
     }
     sendErrorStatus("ERROR train name doesn't exist " + trainName);
     return NULL;
 }

 /**
  * constructs a String containing the number of cars in a train
  *
  * @param trainName is the name of the desired train. If not found in
  *                  Operations, an error message is sent to the client
  * @return the number of cars in a train, as known by Operations
  * @throws IOException on failure to send an error message to the client
  */
 /*public*/ QString AbstractOperationsServer::constructTrainNumberOfCars(QString trainName) //throws IOException
{
     Train* train = tm->getTrainByName(trainName);
     if (train != NULL) {
         return QString::number(train->getNumberCarsInTrain());
     }
     sendErrorStatus("ERROR train name doesn't exist " + trainName);
     return NULL;
 }

 /**
  * Constructs a String containing the road and number of lead loco, if
  * there's one assigned to the train.
  *
  * @param trainName is the name of the desired train. If not found in
  *                  Operations, an error message is sent to the client
  * @return the lead loco
  * @throws IOException on failure to send an error message to the client
  */
 /*public*/ QString AbstractOperationsServer::constructTrainLeadLoco(QString trainName) //throws IOException
{
     Train* train = tm->getTrainByName(trainName);
     if (train != NULL) {
         Engine* leadEngine = train->getLeadEngine();
         if (leadEngine != NULL) {
             return leadEngine->toString();
         }
     }
     sendErrorStatus("ERROR train name doesn't exist " + trainName);
     return NULL;
 }

 /**
  * constructs a String containing the caboose on a train
  *
  * @param trainName is the name of the desired train. If not found in
  *                  Operations, an error message is sent to the client
  * @return the caboose on a train, as known by Operations
  * @throws IOException on failure to send an error message to the client
  */
 /*public*/ QString AbstractOperationsServer::constructTrainCaboose(QString trainName) //throws IOException
{
     Train* train = tm->getTrainByName(trainName);
     if (train != NULL) {
         return train->getCabooseRoadAndNumber();
     }
     sendErrorStatus("ERROR train name doesn't exist " + trainName);
     return NULL;
 }

 /**
  * tells Operations that a train has terminated. If not found in Operations,
  * an error message is sent to the client
  *
  * @param trainName is the name of the train
  * @return the termination String
  * @throws IOException on failure to send an error message to the client
  */
 /*public*/ QString AbstractOperationsServer::terminateTrain(QString trainName) //throws IOException
{
     Train* train = tm->getTrainByName(trainName);
     if (train != NULL) {
         train->terminate();
         return constructTrainStatus(trainName);
     }
     sendErrorStatus("ERROR train name doesn't exist " + trainName);
     return NULL;
 }

 /**
  * sends the full status for a train to a client
  *
  * @param train is the name of the desired train. If not found, an error
  *                  is sent to the client
  * @throws IOException on failure to send an error message
  */
  ///*public*/ void sendFullStatus(String trainName) throws IOException {
  //   Train train = tm.getTrainByName(trainName);
  //       if (train != NULL) {
  //           sendFullStatus(train);
  //       } else {
  //           sendErrorStatus("ERROR train name doesn't exist " + trainName);
  //       }
  //}

 /**
  * sends the full status for a train to a client
  *
  * @param train is the Train object we are sending information about.
  * @throws IOException on failure to send an error message
  */
 /*public*/ /*abstract*/ void AbstractOperationsServer::sendFullStatus(Train* train){}  //throws IOException;

 /*private*/ void AbstractOperationsServer::addPropertyChangeListeners() {
     QList<Train*> trainList = tm->getTrainsByNameList();
     foreach (Train* train, trainList) {
         //train.addPropertyChangeListener(this);
         connect(train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*private*/ void AbstractOperationsServer::removePropertyChangeListeners() {
     QList<Train*> trainList = tm->getTrainsByNameList();
     foreach (Train* train, trainList) {
         //train.removePropertyChangeListener(this);
      disconnect(train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*public*/ /*abstract*/ void AbstractOperationsServer::propertyChange(PropertyChangeEvent* e) {}

 /*synchronized*/ /*protected*/ void AbstractOperationsServer::addTrainToList(QString trainId) {
     if (!trains.contains(trainId)) {
         trains.insert(trainId, new TrainListener(trainId, this));
         //TrainManager::instance()->getTrainById(trainId).addPropertyChangeListener(trains.get(trainId));
         connect(((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->getTrainById(trainId)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*synchronized*/ /*protected*/ void AbstractOperationsServer::removeTrainFromList(QString trainId) {
     if (trains.contains(trainId)) {
         //TrainManager::instance().getTrainById(trainId).removePropertyChangeListener(trains.get(trainId));
      disconnect(((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->getTrainById(trainId)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         trains.remove(trainId);
     }
 }

 /*protected*/ TrainListener* AbstractOperationsServer::getListener(QString trainId) {
     return new TrainListener(trainId, this);
 }

 /*public*/ void AbstractOperationsServer::dispose() {
     if (tm != NULL) {
         //tm.removePropertyChangeListener(this);
      disconnect(tm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         removePropertyChangeListeners();
     }
     if (lm != NULL) {
         //lm.removePropertyChangeListener(this);
      disconnect(lm, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     //for (Map.Entry<String, TrainListener> train : this.trains.entrySet()) {
     QMapIterator<QString, TrainListener*> it(this->trains);
     while(it.hasNext())
     {
      it.next();
      //TrainManager::instance()->getTrainById(train->getKey()).removePropertyChangeListener(train.getValue());
      disconnect(((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->getTrainById(it.key())->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     this->trains.clear();
 }

 /*
  * Protocol Specific Abstract Functions
  */
 /*abstract*/ /*public*/ void AbstractOperationsServer::sendMessage(QList<QString> contents) {} //throws IOException;

 /*abstract*/ /*public*/ void AbstractOperationsServer::sendErrorStatus(QString errorStatus){} //throws IOException;

 /*abstract*/ /*public*/ void AbstractOperationsServer::parseStatus(QString statusString){} //throws JmriException, IOException;

 ///*private*/ /*final*/ static Logger log = LoggerFactory.getLogger(AbstractOperationsServer.class.getName());

 /*
  * This isn't currently used for operations
  */
// /*protected*/ class TrainListener implements PropertyChangeListener {

//     private /*final*/ Train train;

     /*protected*/ TrainListener::TrainListener(QString trainId, AbstractOperationsServer* parent) {
         this->train = ((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->getTrainById(trainId);
      log = new Logger("TrainListener");
      this->parent = parent;
     }

     //@Override
     /*public*/ void TrainListener::propertyChange(PropertyChangeEvent* e) {
         try {
             parent->sendFullStatus(this->train);
         } catch (IOException* ie) {
             log->debug("Error Sending Status");
             // if we get an error, de-register
             //this->train.removePropertyChangeListener(this);
             disconnect(this->train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             parent->removeTrainFromList(this->train->getId());
         }
     }
 //}

}
