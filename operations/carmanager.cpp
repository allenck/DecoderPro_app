#include "carmanager.h"
#include "control.h"
#include "operationssetupxml.h"
#include "carmanagerxml.h"
#include "xml.h"
#include "car.h"
#include "kernel.h"
#include "stringutil.h"
#include "train.h"
#include "routelocation.h"
#include "route.h"
#include "location.h"
#include "track.h"
#include "carload.h"
#include "carloads.h"
#include "jcombobox.h"
#include "instancemanager.h"

//CarManager::CarManager(QObject *parent) :
//  RollingStockManager(parent)
//{
//}
namespace Operations
{
/**
 * Manages the cars.
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 29493 $
 */
///*public*/ class CarManager extends RollingStockManager {


 /*public*/ /*static*/ /*final*/ QString CarManager::KERNEL_LISTLENGTH_CHANGED_PROPERTY = "KernelListLength"; // NOI18N

 /*public*/ CarManager::CarManager(QObject *parent) :
RollingStockManager(parent)
 {
  log = new Logger("CarManager");
  _kernelHashTable = QHash<QString, Kernel*>();
  setProperty("InstanceManagerAutoDefault", "true");
  setProperty("InstanceManagerAutoInitialize", "true");

 }

 /**
  * Finds an existing Car* or creates a new Car* if needed requires car's road
  * and number
  *
  * @param road   car road
  * @param number car number
  * @return new car or existing Car
  */
 /*public*/ RollingStock* CarManager::newRS(QString road, QString number) {
     Car* car = getByRoadAndNumber(road, number);
     if (car == NULL) {
         car = new Car(road, number);
         _register(car);
     }
     return car;
 }

 //@Override
 /*public*/ void CarManager::deregister(RollingStock* car) {
     RollingStockManager::deregister(car);
     ((CarManagerXml*)InstanceManager::getDefault("CarManagerXml"))->setDirty(true);
 }

 /**
  * @return requested Car* object or NULL if none exists
  */
 /*public*/ Car* CarManager::getById(QString id) {
     return (Car*) RollingStockManager::getById(id);
 }

 /**
  * Get Car* by road and number
  *
  * @param road   Car* road
  * @param number Car* number
  * @return requested Car* object or NULL if none exists
  */
 /*public*/ Car* CarManager::getByRoadAndNumber(QString road, QString number) {
     return (Car*) RollingStockManager::getByRoadAndNumber(road, number);
 }

 /**
  * Get a Car* by type and road. Used to test that a car with a specific type
  * and road exists.
  *
  * @param type car type.
  * @param road car road.
  * @return the first car found with the specified type and road.
  */
 /*public*/ Car* CarManager::getByTypeAndRoad(QString type, QString road) {
     return (Car*) RollingStockManager::getByTypeAndRoad(type, road);
 }

 /**
  * Create a new Kernel
  *
  * @param name
  * @return Kernel
  */
 /*public*/ Kernel* CarManager::newKernel(QString name) {
     Kernel* kernel = getKernelByName(name);
     if (kernel == NULL) {
         kernel = new Kernel(name);
         int oldSize = (_kernelHashTable.size());
         _kernelHashTable.insert(name, kernel);
         setDirtyAndFirePropertyChange(KERNEL_LISTLENGTH_CHANGED_PROPERTY, oldSize, (_kernelHashTable
                 .size()));
     }
     return kernel;
 }

 /**
  * Delete a Kernel by name
  *
  * @param name
  */
 /*public*/ void CarManager::deleteKernel(QString name) {
     Kernel* kernel = getKernelByName(name);
     if (kernel != NULL) {
         kernel->dispose();
         int oldSize = (_kernelHashTable.size());
         _kernelHashTable.remove(name);
         setDirtyAndFirePropertyChange(KERNEL_LISTLENGTH_CHANGED_PROPERTY, oldSize, (_kernelHashTable
                 .size()));
     }
 }

 /**
  * Get a Kernel by name
  *
  * @param name
  * @return named Kernel
  */
 /*public*/ Kernel* CarManager::getKernelByName(QString name) {
     return _kernelHashTable.value(name);
 }

 /*public*/ void CarManager::replaceKernelName(QString oldName, QString newName) {
     Kernel* oldKernel = getKernelByName(oldName);
     if (oldKernel != NULL) {
         Kernel* _newKernel = newKernel(newName);
         // keep the lead car
         Car* leadCar = (Car*) oldKernel->getLead();
         if (leadCar != NULL) {
             leadCar->setKernel(_newKernel);
         }
         foreach (Car* car, oldKernel->getCars()) {
             car->setKernel(_newKernel);
         }
     }
 }

 /**
  * Get a comboBox loaded with current Kernel names
  *
  * @return comboBox with Kernel names.
  */
 /*public*/ JComboBox* CarManager::getKernelComboBox() {
     JComboBox* box = new JComboBox();
     box->addItem(NONE);
     foreach (QString kernelName, getKernelNameList()) {
         box->addItem(kernelName);
     }
     return box;
 }

 /**
  * Update an existing comboBox with the current kernel names
  *
  * @param box comboBox requesting update
  */
 /*public*/ void CarManager::updateKernelComboBox(JComboBox* box) {
     box->clear();
     box->addItem(NONE);
     foreach (QString kernelName, getKernelNameList()) {
         box->addItem(kernelName);
     }
 }

 /**
  * Get a list of kernel names
  *
  * @return ordered list of kernel names
  */
 /*public*/ QStringList CarManager::getKernelNameList() {
     QVector<QString> names = QVector<QString>(_kernelHashTable.size());
     QStringList out = QStringList();
     QStringListIterator en(_kernelHashTable.keys());
     int i = 0;
     while (en.hasNext()) {
         names.replace(i++, en.next());
     }
     StringUtil::sort(names.toList());
     foreach (QString name, names) {
         out.append(name);
     }
     return out;
 }

 /*public*/ int CarManager::getKernelMaxNameLength() {
     int maxLength = 0;
     foreach (QString name, getKernelNameList()) {
         if (name.length() > maxLength) {
             maxLength = name.length();
         }
     }
     return maxLength;
 }
 /**
  * Sort by rolling stock location
  *
  * @return list of cars ordered by the RollingStock's location
  */
 //@Override
 /*public*/ QList<RollingStock*>* CarManager::getByLocationList() {
     return getByList(getByKernelList(), BY_LOCATION);
 }

 /**
  * Sort by car kernel names
  *
  * @return list of cars ordered by car kernel
  */
 /*public*/ QList<RollingStock*>* CarManager::getByKernelList() {
     QList<RollingStock*>* byBlocking = getByList(getByNumberList(), BY_BLOCKING);
     return getByList(byBlocking, BY_KERNEL);
 }

 /**
  * Sort by car loads
  *
  * @return list of cars ordered by car loads
  */
 /*public*/ QList<RollingStock*>* CarManager::getByLoadList() {
     return getByList(getByLocationList(), BY_LOAD);
 }

 /**
  * Sort by car return when empty location and track
  *
  * @return list of cars ordered by car return when empty
  */
 /*public*/ QList<RollingStock*>* CarManager::getByRweList() {
     return getByList(getByLocationList(), BY_RWE);
 }

 /*public*/ QList<RollingStock*>* CarManager::getByFinalDestinationList() {
     return getByList(getByDestinationList(), BY_FINAL_DEST);
 }

 /**
  * Sort by car wait count
  *
  * @return list of cars ordered by wait count
  */
 /*public*/ QList<RollingStock*>* CarManager::getByWaitList() {
     return getByList(getByIdList(), BY_WAIT);
 }

 /*public*/ QList<RollingStock*>* CarManager::getByPickupList() {
     return getByList(getByIdList(), BY_PICKUP);
 }

#if 1
 // add car options to sort comparator
 //@Override
// /*protected*/ Comparator<RollingStock*> CarManager::getComparator(int attribute)
 /*static*/ bool CarManager::lessthan(RollingStock* r1, RollingStock* r2, SORTBY attribute)
 {
     switch (attribute) {
         case BY_LOAD:
             return (((Car*)r1)->getLoadName().compare(((Car*) r2)->getLoadName(), Qt::CaseInsensitive))< 0;
         case BY_KERNEL:
             return (((Car*)r1)->getKernelName().compare(((Car*)r2)->getKernelName(), Qt::CaseInsensitive))< 0;
         case BY_RWE:
             return (((Car*)r1)->getReturnWhenEmptyDestName().compare(((Car*)r2)->getReturnWhenEmptyDestName(), Qt::CaseInsensitive))< 0;
         case BY_FINAL_DEST:
             return (((Car*)r1)->getFinalDestinationName().compare(((Car*)r2)->getFinalDestinationName(), Qt::CaseInsensitive))< 0;
         case BY_WAIT:
             return (((Car*)r1)->getWait() - ((Car*)r2)->getWait()) < 0;
         case BY_PICKUP:
             return ((((Car*)r1)->getPickupScheduleName().compare(((Car*)r2)->getPickupScheduleName(), Qt::CaseInsensitive)))< 0;
         default:
             return RollingStockManager::lessthan(r1, r2, (RollingStockManager::SORTBY)attribute);
     }
 }
 /*public*/ void CarManager::sortOut(QList<RollingStock*>* out, SORTBY attribute){
  switch (attribute)
  {
   case BY_LOAD:
   case BY_KERNEL:
   case BY_RWE:
   case BY_FINAL_DEST:
   case BY_WAIT:
   case BY_PICKUP:
    break;
   default:
    return RollingStockManager::sortOut(out, attribute);
  }

  auto property = attribute;
  auto sortRuleLambda = [property] (RollingStock const* r1, RollingStock const* r2) -> bool
  {
   switch(property) {
   case BY_LOAD:
       return (((Car*)r1)->getLoadName().compare(((Car*) r2)->getLoadName(), Qt::CaseInsensitive))< 0;
   case BY_KERNEL:
       return (((Car*)r1)->getKernelName().compare(((Car*)r2)->getKernelName(), Qt::CaseInsensitive))< 0;
   case BY_RWE:
       return (((Car*)r1)->getReturnWhenEmptyDestName().compare(((Car*)r2)->getReturnWhenEmptyDestName(), Qt::CaseInsensitive))< 0;
   case BY_FINAL_DEST:
       return (((Car*)r1)->getFinalDestinationName().compare(((Car*)r2)->getFinalDestinationName(), Qt::CaseInsensitive))< 0;
   case BY_WAIT:
       return (((Car*)r1)->getWait() - ((Car*)r2)->getWait()) < 0;
   case BY_PICKUP:
       return ((((Car*)r1)->getPickupScheduleName().compare(((Car*)r2)->getPickupScheduleName(), Qt::CaseInsensitive)))< 0;
   default:
    return (r1->getRoadName() + r1->getNumber()).compare( (r2->getRoadName() +
            r2->getNumber()),Qt::CaseInsensitive) < 0;

   }
  };
  std::sort ( out->begin(), out->end(), sortRuleLambda);
 }

#endif

 /**
  * Return a list available cars (no assigned train or car already assigned
  * to this train) on a route, cars are ordered least recently moved to most
  * recently moved.
  *
  * @param train
  * @return List of cars with no assigned train on a route
  */
 /*public*/ QList<Car*>* CarManager::getAvailableTrainList(Train* train) {
     QList<Car*>* out = new QList<Car*>();
     Route* route = train->getRoute();
     if (route == NULL) {
         return out;
     }
     // get a list of locations served by this route
     QList<RouteLocation*>* routeList = route->getLocationsBySequenceList();
     // don't include RollingStock at route destination
     RouteLocation* destination = NULL;
     if (routeList->size() > 1) {
         destination = routeList->at(routeList->size() - 1);
         // However, if the destination is visited more than once, must
         // include all cars
         for (int i = 0; i < routeList->size() - 1; i++) {
             if (destination->getName()==(routeList->at(i)->getName())) {
                 destination = NULL; // include cars at destination
                 break;
             }
         }
         // pickup allowed at destination? Don't include cars in staging
         if (destination != NULL && destination->isPickUpAllowed()
                 && !destination->getLocation()->isStaging()) {
             destination = NULL; // include cars at destination
         }
     }
     // get rolling stock by priority and then by moves
     QList<RollingStock*>* _sortByPriority = sortByPriority(getByMovesList());
     // now build list of available RollingStock for this route
     foreach (RollingStock* rs, *_sortByPriority) {
         // only use RollingStock with a location
         if (rs->getLocation() == NULL) {
             continue;
         }
         RouteLocation* rl = route->getLastLocationByName(rs->getLocationName());
         // get RollingStock that don't have an assigned train, or the
         // assigned train is this one
         if (rl != NULL && rl != destination && (rs->getTrain() == NULL || train==(rs->getTrain()))) {
             out->append((Car*) rs);
         }
     }
     return out;
 }

 // sorts the high priority cars to the start of the list
 /*protected*/ QList<RollingStock*>* CarManager::sortByPriority(QList<RollingStock*>* list) {
     QList<RollingStock*>* out = new QList<RollingStock*>();
     // move high priority cars to the start
     for (int i = 0; i < list->size(); i++) {
         RollingStock* rs = list->at(i);
         if (rs->getLoadPriority()==(CarLoad::PRIORITY_HIGH)) {
             out->append(list->at(i));
             list->removeAt(i--);
         }
     }
     // now load all of the remaining low priority cars
     foreach (RollingStock* rs, *list) {
         out->append(rs);
     }
     return out;
 }

 /**
  * Get a list of Cars assigned to a train sorted by destination track blocking order
  * or by track names. If a train is to be blocked by track blocking order, all of
  * the tracks at that location need a blocking number greater than 0.
  * Passenger cars will be placed at the end of the list. Caboose or car with
  * FRED will be the last car(s) in the list. Kernels are placed together by
  * blocking number.
  *
  * @param train
  * @return Ordered list of Cars assigned to the train
  */
 /*public*/ QList<Car*>* CarManager::getByTrainDestinationList(Train* train) {
     QList<RollingStock*>* byFinal = getByList(getList(train), BY_FINAL_DEST);
     QList<RollingStock*>* byLocation = getByList(byFinal, BY_LOCATION);
     QList<RollingStock*>* byDestination = getByList(byLocation, BY_DESTINATION);
     // now place cabooses, cars with FRED, and passenger cars at the rear of the train
     QList<Car*>* out = new QList<Car*>();
     int lastCarsIndex = 0; // incremented each time a car is added to the end of the list
     foreach (RollingStock* rs, *byDestination) {
         Car* car = (Car*) rs;
         if (car->getKernel() != NULL && !car->getKernel()->isLead(car)) {
             continue; // not the lead car, skip for now.
         }
         if (!car->isCaboose() && !car->hasFred() && !car->isPassenger()) {
             // sort order based on train direction when serving track, low to high if West or North bound trains
             if (car->getDestinationTrack() != NULL && car->getDestinationTrack()->getBlockingOrder() > 0) {
                 for (int j = 0; j < out->size(); j++) {
                     if (car->getRouteDestination() != NULL &&
                             (car->getRouteDestination()->getTrainDirectionString()==(RouteLocation::WEST_DIR)
                             || car->getRouteDestination()->getTrainDirectionString()==(RouteLocation::NORTH_DIR))) {
                         if (car->getDestinationTrack()->getBlockingOrder() < out->at(j)->getDestinationTrack()->getBlockingOrder()) {
                             out->insert(j, car);
                             break;
                         }
                     } else {
                         if (car->getDestinationTrack()->getBlockingOrder() > out->at(j)->getDestinationTrack()->getBlockingOrder()) {
                             out->insert(j, car);
                             break;
                         }
                     }
                 }
             }
             if (!out->contains(car)) {
                 out->insert(out->size() - lastCarsIndex, car);
             }
         } else if (car->isCaboose() || car->hasFred()) {
             out->append(car); // place at end of list
             lastCarsIndex++;
         } else if (car->isPassenger()) {
             // block passenger cars at end of list
             int index;
             for (index = 0; index < lastCarsIndex; index++) {
                 Car* carTest = out->at(out->size() - 1 - index);
                 log->debug(tr("Car* (%1) has blocking number: {%2").arg(carTest->toString()).arg(carTest->getBlocking()));
                 if (carTest->isPassenger() && !carTest->isCaboose() && !carTest->hasFred()
                         && carTest->getBlocking() < car->getBlocking()) {
                     break;
                 }
             }
             out->insert(out->size() - index, car);
             lastCarsIndex++;
         }
         // group the cars in the kernel together
         if (car->getKernel() != NULL && car->getKernel()->isLead(car)) {
             int index = out->indexOf(car);
             int numberOfCars = 1; // already added the lead car to the list
             foreach (Car* kcar, car->getKernel()->getCars()) {
                 if (car != kcar) {
                     // Block cars in kernel
                     for (int j = 0; j < numberOfCars; j++) {
                         if (kcar->getBlocking() < out->at(index + j)->getBlocking()) {
                             out->insert(index + j, kcar);
                             break;
                         }
                     }
                     if (!out->contains(kcar)) {
                         out->insert(index + numberOfCars, kcar);
                     }
                     numberOfCars++;
                     if (car->hasFred() || car->isCaboose() || car->isPassenger()) {
                         lastCarsIndex++; // place entire kernel at the end of list
                     }
                 }
             }
         }
     }
     return out;
 }

 /**
  * Get a list of car road names where the car was flagged as a caboose.
  *
  * @return List of caboose road names.
  */
 /*public*/ QStringList CarManager::getCabooseRoadNames() {
     QStringList names = QStringList();
     QStringListIterator en(_hashTable.keys());
     while (en.hasNext()) {
         Car* car = getById(en.next());
         if (car->isCaboose() && !names.contains(car->getRoadName())) {
             names.append(car->getRoadName());
         }
     }
//     Collections.sort(names);
     return names;
 }

 /**
  * Get a list of car road names where the car was flagged with FRED
  *
  * @return List of road names of cars with FREDs
  */
 /*public*/ QStringList CarManager::getFredRoadNames() {
     QStringList names =  QStringList();
     QStringListIterator en(_hashTable.keys());
     while (en.hasNext()) {
         Car* car = getById(en.next());
         if (car->hasFred() && !names.contains(car->getRoadName())) {
             names.append(car->getRoadName());
         }
     }
//     Collections.sort(names);
     return names;
 }

 /**
  * Replace car loads
  *
  * @param type        type of car
  * @param oldLoadName old load name
  * @param newLoadName new load name
  */
 /*public*/ void CarManager::replaceLoad(QString type, QString oldLoadName, QString newLoadName) {
     QList<RollingStock*>* cars = getList();
     foreach (RollingStock* rs, *cars) {
         Car* car = (Car*) rs;
         if (car->getTypeName()==(type) && car->getLoadName()==(oldLoadName)) {
             if (newLoadName != NULL) {
                 car->setLoadName(newLoadName);
             } else {
                 car->setLoadName(((CarLoads*)InstanceManager::getDefault("Operations::CarLoads"))->getDefaultEmptyName());
             }
         }
     }
 }

 /*public*/ QList<Car*>* CarManager::getCarsLocationUnknown() {
     QList<Car*>* mias = new QList<Car*>();
     QList<RollingStock*>* cars = getByIdList();
     foreach (RollingStock* rs, *cars) {
         Car* car = (Car*) rs;
         if (car->isLocationUnknown()) {
             mias->append(car); // return unknown location car
         }
     }
     return mias;
 }

 /*public*/ void CarManager::load(QDomElement root)
 {
  // new format using elements starting version 3.3.1
  if (root.firstChildElement(Xml::NEW_KERNELS) != QDomElement())
  {
   //@SuppressWarnings("unchecked")
   QDomNodeList eKernels = root.firstChildElement(Xml::NEW_KERNELS).elementsByTagName(Xml::KERNEL);
   if (log->isDebugEnabled())
   {
    log->debug(tr("Car* manager sees %1 kernels").arg(eKernels.size()));
   }
   QString a;
   for(int i = 0; i < eKernels.count(); i++)
   {
    QDomElement eKernel= eKernels.at(i).toElement();
    if ((a = eKernel.attribute(Xml::NAME)) != NULL)
    {
        newKernel(a);
    }
   }
  } // old format
  else if (root.firstChildElement(Xml::KERNELS) != QDomElement())
  {
   QString names = root.firstChildElement(Xml::KERNELS).text();
   if (names!=("")) {
       QStringList kernelNames = names.split("%%"); // NOI18N
       if (log->isDebugEnabled()) {
           log->debug(tr("kernels: %1").arg(names));
       }
       foreach (QString name, kernelNames) {
           newKernel(name);
       }
   }
  }

  // if (root.firstChildElement(Xml::OPTIONS) != NULL) {
  // Element options = root.firstChildElement(Xml::OPTIONS);
  // if (log->isDebugEnabled())
  // log->debug("ctor from element " + options);
  // }
  if (root.firstChildElement(Xml::CARS) != QDomElement()) {
      //@SuppressWarnings("unchecked")
      QDomNodeList eCars = root.firstChildElement(Xml::CARS).elementsByTagName(Xml::CAR);
      if (log->isDebugEnabled()) {
          log->debug(tr("readFile sees %1 cars").arg(eCars.size()));
      }
      //for (Element eCar* : eCars) {
      for(int i =0; i < eCars.count(); i++)
      {
       QDomElement eCar = eCars.at(i).toElement();
       QString id = eCar.attribute(Xml::ID);
       _register(new Car(eCar));
      }
     }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-cars.dtd.
  */
 /*public*/ void CarManager::store(QDomElement root, QDomDocument doc)
{
 root.appendChild(doc.createElement(Xml::OPTIONS)); // nothing to save under
// QDomElement options = QDomElement();
// options.setTagName(Xml::OPTIONS);
// root.appendChild(options);
     // options
     //log->debug("store doc " + doc.nodeName());
     QDomElement values;
     QStringList names = getKernelNameList();
     if (Control::backwardCompatible) {
     root.appendChild(values = doc.createElement(Xml::KERNELS));
//      values = QDomElement();
//      values.setTagName(Xml::KERNELS);
      root.appendChild(values);
         foreach (QString name, names) {
             QString kernelNames = name + "%%"; // NOI18N
//             QDomText t = QDomText();
//             t. setData(kernelNames);
             QDomText t = doc.createTextNode(kernelNames);
             values.appendChild(t);
         }
     }
     // new format using elements
     QDomElement kernels = doc.createElement(Xml::NEW_KERNELS);
//     QDomElement kernels = QDomElement();
//     kernels.setTagName(Xml::NEW_KERNELS);
     root.appendChild(kernels);
     foreach (QString name, names)
     {
       QDomElement kernel = doc.createElement(Xml::KERNEL);
//      QDomElement kernel = QDomElement();
//      kernel.setTagName(Xml::KERNEL);
         kernel.setAttribute(Xml::NAME, name);
         kernels.appendChild(kernel);
     }
     root.appendChild(kernels);
     root.appendChild(values = doc.createElement(Xml::CARS));
//     values = QDomElement();
//     values.setTagName(Xml::CARS);
//     root.appendChild(values);
     // add entries
     QList<RollingStock*>* carList = getByIdList();
     //log->debug("store doc " + doc.nodeName());

     foreach (RollingStock* rs, *carList) {
         Car* car = (Car*) rs;
         values.appendChild(car->store(doc));
     }
 }

 /*protected*/ void CarManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // Set dirty
     ((CarManagerXml*)InstanceManager::getDefault("CarManagerXml"))->setDirty(true);
     RollingStockManager::firePropertyChange(p, old, n);
 }

//Override
   /*public*/ void CarManager::initialize() {
       InstanceManager::getDefault("OperationsSetupXml"); // load setup
       // create manager to load cars and their attributes
       InstanceManager::getDefault("CarManagerXml");
   }

}
