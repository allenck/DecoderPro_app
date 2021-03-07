#ifndef ROLLINGSTOCKMANAGER_H
#define ROLLINGSTOCKMANAGER_H

#include <QObject>
#include <QHash>
#include "appslib_global.h"
#include "rollingstock.h"

class PropertyChangeSupport;
class PropertyChangeListener;
namespace Operations
{

 class RollingStock;
 class Train;
 class APPSLIBSHARED_EXPORT RollingStockManager : public RollingStock//, public PropertyChangeListener
 {
  Q_OBJECT
  //Q_INTERFACES(PropertyChangeListener)
  public:
  explicit RollingStockManager(QObject *parent = 0);
  /*public*/ static /*final*/ QString NONE;// = "";
  /*public*/ static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "RollingStockListLength"; // NOI18N
  /*public*/ int getNumEntries() ;
  /*public*/ void dispose();
  /*public*/ RollingStock* getById(QString id);
  /*public*/ RollingStock* getByRoadAndNumber(QString road, QString number);
  /*public*/ void deleteAll();
  /*public*/ void _register(RollingStock* rs);
  /*public*/ void deregister(RollingStock* rs);
  /*public*/ void changeId(RollingStock* rs, QString road, QString number);
  /*public*/ QList<RollingStock*>* getByRoadNameList();
  /*public*/ QList<RollingStock*>* getByIdList();
  /*public*/ QList<RollingStock*>* getList(Train* train);
  /*public*/ QList<RollingStock*>* getList();
  /*public*/ RollingStock* getByTypeAndRoad(QString type, QString road);
  /*public*/ RollingStock* getByRfid(QString rfid);
  /*public*/ QList<RollingStock*>* getByNumberList();
  /*public*/ QList<RollingStock*>* getByTypeList();
  /*public*/ QList<RollingStock*>* getByTypeList(QString type);
  /*public*/ QList<RollingStock*>* getByColorList();
  /*public*/ QList<RollingStock*>* getByLocationList();
  /*public*/ QList<RollingStock*>* getByDestinationList() ;
  /*public*/ QList<RollingStock*>* getByTrainList();
  /*public*/ QList<RollingStock*>* getByMovesList();
  /*public*/ QList<RollingStock*>* getByBuiltList();
  /*public*/ QList<RollingStock*>* getByOwnerList();
  /*public*/ QList<RollingStock*>* getByValueList();
  /*public*/ QList<RollingStock*>* getByRfidList() ;
  /*public*/ QList<RollingStock*>* getByLastDateList() ;
  /*public*/ QList<RollingStock*>* getByLastDateList(QList<RollingStock*>* inList);
  /*public*/ QList<RollingStock*>* getByTrainList(Train* train);
  /*public*/ void resetMoves();
  /*public*/ QList<RollingStock*> getList(Location* location);
  /*public*/ QList<RollingStock *> getList(Track* track);
  QObject* self() override {return (QObject*)this; }
  /*abstract*/ virtual /*public*/ RollingStock* newRS(QString road, QString number) =0;

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* evt) override;

 private:
  /*private*/ static /*final*/ int pageSize;// = 64;


 protected:
  // RollingStock
  /*protected*/ QHash<QString, RollingStock*> _hashTable;// = new Hashtable<String, RollingStock>();
  ///*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ QList<RollingStock*>* getByList(QList<RollingStock*>* sortIn, int attribute);
  // The various sort options for RollingStock
  // see CarManager and EngineManger for other values
  /*protected*/ static /*final*/ int BY_NUMBER ; //=0;
  /*protected*/ static /*final*/ int BY_ROAD; //=1;
  /*protected*/ static /*final*/ int BY_TYPE; //=2;
  /*protected*/ static /*final*/ int BY_COLOR; //=3;
  // BY_LOAD; //=4
  // BY_MODEL; //=4
  // BY_KERNEL; //=5
  // BY_CONSIST; //=5
  /*protected*/ static /*final*/ int BY_LOCATION; //=6;
  /*protected*/ static /*final*/ int BY_DESTINATION; //=7;
  /*protected*/ static /*final*/ int BY_TRAIN; //=8;
  /*protected*/ static /*final*/ int BY_MOVES; //=9;
  /*protected*/ static /*final*/ int BY_BUILT; //=10;
  /*protected*/ static /*final*/ int BY_OWNER;//= 11;
  /*protected*/ static /*final*/ int BY_RFID;// = 12;
  // BY_RWE = 13
  // BY_HP = 13
  // BY_FINAL_DEST = 14
  /*protected*/ static /*final*/ int BY_VALUE; //=15;
  // BY_WAIT = 16
  /*protected*/ static /*final*/ int BY_LAST; //=17;
  /*protected*/ static /*final*/ int BY_BLOCKING; //=18;
  ///*protected*/ Comparator<RollingStock*> getComparator(int attribute);

  // BY_PICKUP = 19


 };
}
#endif // ROLLINGSTOCKMANAGER_H
