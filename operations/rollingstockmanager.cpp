#include "rollingstockmanager.h"
#include "propertychangesupport.h"
#include "rollingstock.h"
#include <QVariant>
#include "stringutil.h"
#include "xml.h"

//RollingStockManager::RollingStockManager(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations
{
/**
 * Base class for rolling stock managers car and engine.
 *
 * @author Daniel Boudreau Copyright (C) 2010, 2011
 * @version $Revision: 29268 $
 */
///*public*/ class RollingStockManager {

 /*public*/ /*static*/ /*final*/ QString RollingStockManager::NONE = "";


 /*public*/ /*static*/ /*final*/ QString RollingStockManager::LISTLENGTH_CHANGED_PROPERTY = "RollingStockListLength"; // NOI18N

 /*public*/ RollingStockManager::RollingStockManager(QObject *parent) :
   RollingStock(parent)
 {
  // RollingStock
  _hashTable = QHash<QString, RollingStock*>();

 }

 /**
  * Get the number of items in the roster
  *
  * @return Number of rolling stock in the Roster
  */
 /*public*/ int RollingStockManager::getNumEntries() {
     return _hashTable.size();
 }

 /*public*/ void RollingStockManager::dispose() {
     deleteAll();
 }

 /**
  * Get rolling stock by id
  *
  * @return requested RollingStock object or null if none exists
  */
 /*public*/ RollingStock* RollingStockManager::getById(QString id) {
     return _hashTable.value(id);
 }

 /**
  * Get rolling stock by road and number
  *
  * @param road RollingStock road
  * @param number RollingStock number
  * @return requested RollingStock object or null if none exists
  */
 /*public*/ RollingStock* RollingStockManager::getByRoadAndNumber(QString road, QString number) {
     QString id = RollingStock::createId(road, number);
     return getById(id);
 }

    /**
     * Get a rolling stock by type and road. Used to test that rolling stock
     * with a specific type and road exists.
     *
     * @param type RollingStock type.
     * @param road RollingStock road.
     * @return the first RollingStock found with the specified type and road.
     */
    /*public*/ RollingStock* RollingStockManager::getByTypeAndRoad(QString type, QString road) {
 QStringListIterator en( _hashTable.keys());
        while (en.hasNext()) {
            RollingStock* rs = getById(en.next());
            if (rs->getTypeName()==(type) && rs->getRoadName()==(road)) {
                return rs;
            }
        }
        return NULL;
    }

    /**
     * Get a rolling stock by Radio Frequency Identification (RFID)
     *
     * @param rfid RollingStock's RFID.
     * @return the RollingStock with the specific RFID, or null if not found
     */
    /*public*/ RollingStock* RollingStockManager::getByRfid(QString rfid) {
        QStringListIterator en(_hashTable.keys());
        while (en.hasNext()) {
            RollingStock* rs = getById(en.next());
            if (rs->getRfid()==(rfid)) {
                return rs;
            }
        }
        return NULL;
    }

    /**
     * Load RollingStock.
     */
    /*public*/ void RollingStockManager::_register(RollingStock* rs) {
        int oldSize = (_hashTable.size());
        _hashTable.insert(rs->getId(), rs);
        firePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_hashTable.size()));
    }

    /**
     * Unload RollingStock.
     */
    /*public*/ void RollingStockManager::deregister(RollingStock* rs) {
        rs->dispose();
        int oldSize = (_hashTable.size());
        _hashTable.remove(rs->getId());
        firePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_hashTable.size()));
    }

    /*public*/ void RollingStockManager::changeId(RollingStock* rs, QString road, QString number) {
        _hashTable.remove(rs->getId());
        rs->_id = RollingStock::createId(road, number);
        _register(rs);
    }

 /**
  * Remove all RollingStock from roster
  */
 /*public*/ void RollingStockManager::deleteAll() {
     int oldSize =_hashTable.size();
     QStringListIterator en( _hashTable.keys());
     while (en.hasNext()) {
         RollingStock* rs = getById(en.next());
         rs->dispose();
         _hashTable.remove(rs->getId());
     }
     firePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_hashTable.size()));
 }

    /*public*/ void RollingStockManager::resetMoves() {
        QStringListIterator en(_hashTable.keys());
        while (en.hasNext()) {
            RollingStock* rs = getById(en.next());
            rs->setMoves(0);
        }
    }

    /**
     * Returns a list (no order) of RollingStock.
     *
     * @return list of RollingStock
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getList() {
 QListIterator<RollingStock*> en(_hashTable.values());
        QList<RollingStock*>* out = new QList<RollingStock*>();
        while (en.hasNext()) {
            out->append(en.next());
        }
        return out;
    }

    /**
     * Sort by rolling stock id
     *
     * @return list of RollingStock ordered by id
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByIdList() {
 QStringListIterator en( _hashTable.keys());
        QVector<QString> arr = QVector<QString>(_hashTable.size());
        QList<RollingStock*>* out = new QList<RollingStock*>();
        int i = 0;
        while (en.hasNext()) {
            arr.replace(i, en.next());
            i++;
        }
        StringUtil::sort(arr.toList());
        for (i = 0; i < arr.size(); i++) {
            out->append(getById(arr[i]));
        }
        return out;
    }

    /**
     * Sort by rolling stock road name
     *
     * @return list of RollingStock ordered by road name
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByRoadNameList() {
        return getByList(getByIdList(), BY_ROAD);
    }

    /**
     * Sort by rolling stock number, number can be alphanumeric.
     * RollingStock number can also be in the format of nnnn-N, where
     * the "-N" allows the user to enter RollingStock with similar numbers.
     *
     * @return list of RollingStock ordered by number
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByNumberList() {
        // first get by road list
        QList<RollingStock*>* sortIn = getByRoadNameList();
        // now re-sort
        QList<RollingStock*>* out = new QList<RollingStock*>();
        int rsNumber = 0;
        int outRsNumber = 0;
        int notInteger = -999999999; // flag when rolling stock number isn't an
        // integer
        QStringList number;
        bool rsAdded = false;

        foreach (RollingStock* rs, *sortIn) {
            rsAdded = false;
            //try {
                rsNumber = rs->getNumber().toInt();
                rs->number = rsNumber;
//            } catch (NumberFormatException* e) {
//                // maybe rolling stock number in the format nnnn-N
//                try {
//                    number = rs.getNumber().split("-");
//                    rsNumber = Integer.parseInt(number[0]);
//                    rs.number = rsNumber;
//                    // two possible exceptions, ArrayIndexOutOfBoundsException on split, and NumberFormatException on
//                    // parseInt
//                } catch (Exception e2) {
//                    rs.number = notInteger;
//                    // sort alphanumeric numbers at the end of the out list
//                    String numberIn = rs.getNumber();
//                    // log.debug("rolling stock in road number ("+numberIn+") isn't a number");
//                    for (int k = (out.size() - 1); k >= 0; k--) {
//                        String numberOut = out.get(k).getNumber();
//                        try {
//                            Integer.parseInt(numberOut);
//                            // done, place rolling stock with alphanumeric
//                            // number after rolling stocks with real numbers.
//                            out.add(k + 1, rs);
//                            rsAdded = true;
//                            break;
//                        } catch (NumberFormatException* e3) {
//                            if (numberIn.compareToIgnoreCase(numberOut) >= 0) {
//                                out.add(k + 1, rs);
//                                rsAdded = true;
//                                break;
//                            }
//                        }
//                    }
//                    if (!rsAdded) {
//                        out.add(0, rs);
//                    }
//                    continue;
//                }
//            }

            int start = 0;
            // page to improve sort performance.
            int divisor = out->size() / pageSize;
            for (int k = divisor; k > 0; k--) {
                outRsNumber = out->at((out->size() - 1) * k / divisor)->number;
                if (outRsNumber == notInteger) {
                    continue;
                }
                if (rsNumber >= outRsNumber) {
                    start = (out->size() - 1) * k / divisor;
                    break;
                }
            }
            for(int j = start; j < out->size(); j++) {
                outRsNumber = out->at(j)->number;
                if (outRsNumber == notInteger) {
                    //try {
                 bool ok;
                        outRsNumber = out->at(j)->getNumber().toInt(&ok);
                    if(!ok) {
                        //try {
                            number = out->at(j)->getNumber().split("-");
                            outRsNumber = number[0].toInt(&ok);
                        if(!ok) {
                            // force add
                            outRsNumber = rsNumber + 1;
                        }
                    }
                }
                if (rsNumber < outRsNumber) {
                    out->insert(j, rs);
                    rsAdded = true;
                    break;
                }
            }
            if (!rsAdded) {
                out->append(rs);
            }
        }
        // log.debug("end rolling stock sort by number list");
        return out;
    }

    /**
     * Sort by rolling stock type names
     *
     * @return list of RollingStock ordered by RollingStock type
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByTypeList() {
        return getByList(getByRoadNameList(), BY_TYPE);
    }

    /**
     * Return rolling stock of a specific type
     *
     * @param type type of rolling stock
     * @return list of RollingStock that are specific type
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByTypeList(QString type) {
        QList<RollingStock*>* typeList = getByTypeList();
        QList<RollingStock*>* out = new QList<RollingStock*>();
        foreach (RollingStock* rs, *typeList) {
            if (rs->getTypeName()==(type)) {
                out->append(rs);
            }
        }
        return out;
    }

    /**
     * Sort by rolling stock color names
     *
     * @return list of RollingStock ordered by RollingStock color
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByColorList() {
        return getByList(getByTypeList(), BY_COLOR);
    }

    /**
     * Sort by rolling stock location
     *
     * @return list of RollingStock ordered by RollingStock location
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByLocationList() {
        return getByList(getList(), BY_LOCATION);
    }

    /**
     * Sort by rolling stock destination
     *
     * @return list of RollingStock ordered by RollingStock destination
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByDestinationList() {
        return getByList(getByLocationList(), BY_DESTINATION);
    }

    /**
     * Sort by rolling stocks in trains
     *
     * @return list of RollingStock ordered by trains
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByTrainList() {
        QList<RollingStock*>* byDest = getByList(getByIdList(), BY_DESTINATION);
        QList<RollingStock*>* byLoc = getByList(byDest, BY_LOCATION);
        return getByList(byLoc, BY_TRAIN);
    }

    /**
     * Sort by rolling stock moves
     *
     * @return list of RollingStock ordered by RollingStock moves
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByMovesList() {
        return getByList(getList(), BY_MOVES);
    }

    /**
     * Sort by when rolling stock was built
     *
     * @return list of RollingStock ordered by RollingStock built date
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByBuiltList() {
        return getByList(getByIdList(), BY_BUILT);
    }

    /**
     * Sort by rolling stock owner
     *
     * @return list of RollingStock ordered by RollingStock owner
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByOwnerList() {
        return getByList(getByIdList(), BY_OWNER);
    }

    /**
     * Sort by rolling stock value
     *
     * @return list of RollingStock ordered by value
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByValueList() {
        return getByList(getByIdList(), BY_VALUE);
    }

    /**
     * Sort by rolling stock RFID
     *
     * @return list of RollingStock ordered by RFIDs
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByRfidList() {
        return getByList(getByIdList(), BY_RFID);
    }

    /**
     * Get a list of all rolling stock sorted last date used
     *
     * @return list of RollingStock ordered by last date
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByLastDateList() {
        return getByList(getByIdList(), BY_LAST);
    }

    /**
     * Sort a specific list of rolling stock last date used
     *
     * @param inList list of rolling stock to sort.
     * @return list of RollingStock ordered by last date
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByLastDateList(QList<RollingStock*>* inList) {
        return getByList(inList, BY_LAST);
    }

    /*private*/ /*static*/ /*final*/ int RollingStockManager::pageSize = 64;

    /*protected*/ QList<RollingStock*>* RollingStockManager::getByList(QList<RollingStock*>* sortIn, int attribute) {
        QList<RollingStock*>* out = new QList<RollingStock*>();
        //sortIn.forEach(n -> out.add(n));
        foreach(RollingStock* rs, *sortIn)
         out->append(rs);
#if 0 // TODO:
        Collections.sort(out, getComparator(attribute));
#endif
        return out;
    }

    // The various sort options for RollingStock
    // see CarManager and EngineManger for other values
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_NUMBER = 0;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_ROAD = 1;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_TYPE = 2;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_COLOR = 3;
    // BY_LOAD = 4
    // BY_MODEL = 4
    // BY_KERNEL = 5
    // BY_CONSIST = 5
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_LOCATION = 6;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_DESTINATION = 7;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_TRAIN = 8;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_MOVES = 9;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_BUILT = 10;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_OWNER = 11;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_RFID = 12;
    // BY_RWE = 13
    // BY_HP = 13
    // BY_FINAL_DEST = 14
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_VALUE = 15;
    // BY_WAIT = 16
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_LAST = 17;
    /*protected*/ /*static*/ /*final*/ int RollingStockManager::BY_BLOCKING = 18;

    // BY_PICKUP = 19
#if 0
    /*protected*/ java.util.Comparator<RollingStock> getComparator(int attribute) {
        switch (attribute) {
            case BY_NUMBER:
                return (r1, r2) -> (r1.getNumber().compareToIgnoreCase(r2.getNumber()));
            case BY_ROAD:
                return (r1, r2) -> (r1.getRoadName().compareToIgnoreCase(r2.getRoadName()));
            case BY_TYPE:
                return (r1, r2) -> (r1.getTypeName().compareToIgnoreCase(r2.getTypeName()));
            case BY_COLOR:
                return (r1, r2) -> (r1.getColor().compareToIgnoreCase(r2.getColor()));
            case BY_LOCATION:
                return (r1, r2) -> (r1.getStatus() + r1.getLocationName() + r1.getTrackName()).compareToIgnoreCase(r2.getStatus() +
                        r2.getLocationName() +
                        r2.getTrackName());
            case BY_DESTINATION:
                return (r1, r2) -> (r1.getDestinationName() + r1.getDestinationTrackName()).compareToIgnoreCase(r2.getDestinationName() +
                        r2.getDestinationTrackName());
            case BY_TRAIN:
                return (r1, r2) -> (r1.getTrainName().compareToIgnoreCase(r2.getTrainName()));
            case BY_MOVES:
                return (r1, r2) -> (r1.getMoves() - r2.getMoves());
            case BY_BUILT:
                return (r1, r2) -> (convertBuildDate(r1.getBuilt()).compareToIgnoreCase(convertBuildDate(r2.getBuilt())));
            case BY_OWNER:
                return (r1, r2) -> (r1.getOwner().compareToIgnoreCase(r2.getOwner()));
            case BY_RFID:
                return (r1, r2) -> (r1.getRfid().compareToIgnoreCase(r2.getRfid()));
            case BY_VALUE:
                return (r1, r2) -> (r1.getValue().compareToIgnoreCase(r2.getValue()));
            case BY_LAST:
                return (r1, r2) -> (r1.getLastMoveDate().compareTo(r2.getLastMoveDate()));
            case BY_BLOCKING:
                return (r1, r2) -> (r1.getBlocking() - r2.getBlocking());
            default:
                return (r1, r2) -> ((r1.getRoadName() + r1.getNumber()).compareToIgnoreCase(r2.getRoadName() +
                        r2.getNumber()));
        }
    }

    private String convertBuildDate(String date) {
        String[] built = date.split("-");
        if (built.length > 1) {
            try {
                int d = Integer.parseInt(built[1]);
                if (d < 100) {
                    d = d + 1900;
                }
                return Integer.toString(d);
            } catch (NumberFormatException* e2) {
                log.debug("Unable to parse car built date {}", date);
            }
        }
        return date;
    }
#endif
    /**
     * Get a list of rolling stocks assigned to a train ordered by location
     *
     * @param train
     * @return List of RollingStock assigned to the train ordered by location
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getByTrainList(Train* train) {
        // QList<RollingStock*>* shuffle = shuffle(getList(train));
        QList<RollingStock*>* out = getByList(getList(train), BY_LOCATION);
        return out;
    }

    /**
     * Returns a list (no order) of RollingStock in a train.
     *
     * @return list of RollingStock
     */
    /*public*/ QList<RollingStock*>* RollingStockManager::getList(Train* train) {
 QListIterator<RollingStock*> en(_hashTable.values());
        QList<RollingStock*>* out = new QList<RollingStock*>();
        while (en.hasNext()) {
            RollingStock* rs = en.next();
            if (rs->getTrain() == train) {
                out->append(rs);
            }
        }
        return out;
    }
#if 1
    /**
     * Returns a list (no order) of RollingStock at a location.
     *
     * @param location location to search for.
     * @return list of RollingStock
     */
    /*public*/ QList<RollingStock*> RollingStockManager::getList(Location* location) {
        QList<RollingStock*> out = QList<RollingStock*>();
        //_hashTable.forEach((key, rs) -> {
        foreach(RollingStock* rs, _hashTable.values())
        {
            if (rs->getLocation() == location)
                out.append(rs);
        }//);
        return out;
    }

    /**
     * Returns a list (no order) of RollingStock at a location.
     *
     * @param track Track to search for.
     * @return list of RollingStock
     */
    /*public*/ QList<RollingStock*> RollingStockManager::getList(Track* track) {
        QList<RollingStock*> out = QList<RollingStock*>();
        //_hashTable.forEach((key, rs) ->
        foreach(RollingStock* rs, _hashTable.values())
        {
            if (rs->getTrack() == track)
                out.append(rs);
        }//);
        return out;
    }

#endif
 //@Override
 //@OverridingMethodsMustInvokeSuper
 /*public*/ void RollingStockManager::propertyChange(PropertyChangeEvent* evt) {
     if (evt->getPropertyName() ==(Xml::ID)) {
         //@SuppressWarnings("unchecked")
         RollingStock* rs = /*(T)*/ (RollingStock*)evt->getSource(); // unchecked cast to T
         _hashTable.remove(evt->getOldValue().toString());
         _hashTable.insert(rs->getId(), rs);
         // fire so listeners that rebuild internal lists get signal of change in id, even without change in size
         firePropertyChange(LISTLENGTH_CHANGED_PROPERTY, _hashTable.size(), _hashTable.size());
     }
 }
}
