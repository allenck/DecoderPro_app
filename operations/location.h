#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>
#include "propertychangesupport.h"
#include <QPoint>
#include "physicallocation.h"
#include <QtXml>
#include "appslib_global.h"

class PhysicalLocation;
class QComboBox;
class Reporter;
namespace Operations {
 class RollingStock;
 class Pool;
 class Track;
 class APPSLIBSHARED_EXPORT Location : public QObject
 {
  Q_OBJECT
 public:
  //explicit Location(QObject *parent = 0);
  PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
  /*public*/ Location(QString id, QString name,QObject *parent = 0);
  /*public*/ static /*final*/ QString NONE;// = "";
  /*public*/ static /*final*/ int NORMAL; //=1; // types of track allowed at this location
  /*public*/ static /*final*/ int STAGING; //=2; // staging only

  /*public*/ static /*final*/ int EAST; //=1; // train direction serviced by this location
  /*public*/ static /*final*/ int WEST; //=2;
  /*public*/ static /*final*/ int NORTH; //=4;
  /*public*/ static /*final*/ int SOUTH; //=8;

  // Switch list status
  /*public*/ static /*final*/ QString UNKNOWN; //="";
  /*public*/ static /*final*/ QString PRINTED; //=Bundle.getMessage("Printed");
  /*public*/ static /*final*/ QString CSV_GENERATED; //=Bundle.getMessage("CsvGenerated");
  /*public*/ static /*final*/ QString MODIFIED; //=Bundle.getMessage("Modified");
  /*public*/ static /*final*/ QString UPDATED; //=Bundle.getMessage("Updated");

  // Switch list states
  /*public*/ static /*final*/ int SW_CREATE; //=0; // create new switch list
  /*public*/ static /*final*/ int SW_APPEND; //=1; // append train into to switch list
  /*public*/ static /*final*/ int SW_PRINTED; //=2; // switch list printed

  // For property change
  /*public*/ static /*final*/ QString TRACK_LISTLENGTH_CHANGED_PROPERTY; //="trackListLength"; // NOI18N
  /*public*/ static /*final*/ QString TYPES_CHANGED_PROPERTY; //="locationTypes"; // NOI18N
  /*public*/ static /*final*/ QString TRAINDIRECTION_CHANGED_PROPERTY; //="locationTrainDirection"; // NOI18N
  /*public*/ static /*final*/ QString LENGTH_CHANGED_PROPERTY; //="locationTrackLengths"; // NOI18N
  /*public*/ static /*final*/ QString USEDLENGTH_CHANGED_PROPERTY; //="locationUsedLength"; // NOI18N
  /*public*/ static /*final*/ QString NAME_CHANGED_PROPERTY; //="locationName"; // NOI18N
  /*public*/ static /*final*/ QString SWITCHLIST_CHANGED_PROPERTY; //="switchList"; // NOI18N
  /*public*/ static /*final*/ QString DISPOSE_CHANGED_PROPERTY; //="locationDispose"; // NOI18N
  /*public*/ static /*final*/ QString STATUS_CHANGED_PROPERTY; //="locationStatus"; // NOI18N
  /*public*/ static /*final*/ QString POOL_LENGTH_CHANGED_PROPERTY; //="poolLengthChanged"; // NOI18N
  /*public*/ static /*final*/ QString SWITCHLIST_COMMENT_CHANGED_PROPERTY; //="switchListComment";// NOI18N
  /*public*/ static /*final*/ QString TRACK_BLOCKING_ORDER_CHANGED_PROPERTY; //="locationTrackBlockingOrder";// NOI18N
  /*public*/ QString getId();
  /*public*/ void setName(QString name) ;
  /*public*/ QString toString() ;
  /*public*/ QString getName() ;
  /*public*/ void copyLocation(Location* newLocation) ;
  /*public*/ void copyTracksLocation(Location* location);
  /*public*/ PhysicalLocation* getPhysicalLocation();
  /*public*/ void setPhysicalLocation(PhysicalLocation* l);
  /*public*/ void setLength(int length);
  /*public*/ int getLength();
  /*public*/ void setUsedLength(int length);
  /*public*/ int getUsedLength();
  /*public*/ void setLocationOps(int ops);
  /*public*/ int getLocationOps();
  /*public*/ bool isStaging();
  /*public*/ void setComment(QString comment) ;
  /*public*/ QString getComment() ;
  /*public*/ void setSwitchListComment(QString comment);
  /*public*/ void setDefaultPrinterName(QString name);
  /*public*/ QString getDefaultPrinterName();
  /*public*/ QString getSwitchListComment();
  /*public*/ bool acceptsTypeName(QString type);
  /*public*/ void addTypeName(QString type);
  /*public*/ void deleteTypeName(QString type);
  /*public*/ Track* addTrack(QString name, QString type);
  /*public*/ void resetMoves();
  /*public*/ Track* getTrackByName(QString name, QString type);
  /*public*/ void _register(Track* track);
  /*public*/ void deleteTrack(Track* track);
  /*public*/ QList<Track*> getTrackList();
  /*public*/ Location(QDomElement e);
  /*public*/ int getSwitchListState();
  /*public*/ void setStatusModified();
  /*public*/ void setStatus(QString status);
  /*public*/ QString getStatus();
  /*public*/ QDomElement store(QDomDocument doc);
  /*public*/ void setTrainIconEast(QPoint point);
  /*public*/ QPoint getTrainIconEast();
  /*public*/ void setTrainIconWest(QPoint point);
  /*public*/ QPoint getTrainIconWest();
  /*public*/ void setTrainIconNorth(QPoint point);
  /*public*/ QPoint getTrainIconNorth();
  /*public*/ void setTrainIconSouth(QPoint point);
  /*public*/ QPoint getTrainIconSouth() ;
  /*public*/ void addRS(RollingStock* rs) ;
#define POINTSTRING(p) "Point[x=" + QString::number(p.x()) + ",y=" + QString::number(p.y()) + "]"
  /*public*/ void setNumberRS(int number);
  /*public*/ int getNumberRS();
  /*public*/ int getNumberCars();
  /*public*/ int getNumberEngines();
  /*public*/ bool isTrackAtLocation(Track* track);
  /*public*/ void deleteRS(RollingStock* rs);
  /*public*/ void addPickupRS();
  /*public*/ void deletePickupRS();
  /*public*/ void addDropRS();
  /*public*/ void deleteDropRS();
  /*public*/ Track* getTrackById(QString id);
  /*public*/ Reporter* getReporter();
  /*public*/ void updateComboBox(QComboBox* box);
  /*public*/ QList<Track*> getTrackByNameList(QString type);
  /*public*/ QList<Track*> getTrackByIdList();
  /*public*/ QStringList getTrackIdsByIdList();
  /*public*/ void dispose();
  /*public*/ int getTrainDirections();
  /*public*/ void setSwitchListEnabled(bool switchList);
  /*public*/ bool isSwitchListEnabled();
  /*public*/ Pool* addPool(QString name);
  /*public*/ void removePool(Pool* pool);
  /*public*/ Pool* getPoolByName(QString name);
  /*public*/ void _register(Pool* pool);
  /*public*/ void updateComboBox(QComboBox* box, RollingStock* rs, bool filter, bool destination);
  /*public*/ bool hasSpurs();
  /*public*/ bool hasInterchanges();
  /*public*/ bool hasYards();
  /*public*/ bool hasTrackType(QString trackType);
  /*public*/ int getPickupRS();
  /*public*/ int getDropRS();
  /*public*/ bool hasPools();
  /*public*/ int getNumberOfTracks();
  /*public*/ void setTrainDirections(int direction);
  /*public*/ bool hasPlannedPickups();
  /*public*/ bool hasLoadRestrications();
  /*public*/ bool hasShipLoadRestrications();
  /*public*/ bool hasRoadRestrications();
  /*public*/ bool hasDestinationRestrications();
  /*public*/ bool hasAlternateTracks();
  /*public*/ QList<Track*> getTrackByMovesList(QString type);
  /*public*/ void setSwitchListState(int state);
  /*public*/ void updatePoolComboBox(QComboBox* box);
  /*public*/ QList<Pool*> getPoolsByNameList();
  /*public*/ QList<Track*> getTracksByBlockingOrderList(QString type);
  /*public*/ void resetTracksByBlockingOrder();
  /*public*/ void resequnceTracksByBlockingOrder();
  /*public*/ void changeTrackBlockingOrderEarlier(Track* track);
  /*public*/ void changeTrackBlockingOrderLater(Track* track);
  /*private*/ Track* getTrackByBlockingOrder(int order);

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
  /*private*/ QStringList getTypeNames();
  /*private*/ void setTypeNames(QStringList types);
  /*private*/ void setNumberEngines(int number);
  /*private*/ void setNumberCars(int number);
  /*private*/ void addPropertyChangeListeners();
  /*private*/ void replaceRoad(QString oldRoad, QString newRoad);
  /*private*/ void replaceType(QString oldType, QString newType);
  void common();

 protected:
  /*protected*/ QString _id; //=NONE;
  /*protected*/ QString _name; //=NONE;
  /*protected*/ int _IdNumber; //=0;
  /*protected*/ int _numberRS; //=0; // number of cars and engines (total rolling stock)
  /*protected*/ int _numberCars; //=0; // number of cars
  /*protected*/ int _numberEngines; //=0; // number of engines
  /*protected*/ int _pickupRS; //=0;
  /*protected*/ int _dropRS; //=0;
  /*protected*/ int _locationOps; //=NORMAL; // type of operations at this location
  /*protected*/ int _trainDir; //=EAST + WEST + NORTH + SOUTH; // train direction served by this location
  /*protected*/ int _length; //=0; // length of all tracks at this location
  /*protected*/ int _usedLength; //=0; // length of track filled by cars and engines
  /*protected*/ QString _comment; //=NONE;
  /*protected*/ QString _switchListComment; //=NONE; // optional switch list comment
  /*protected*/ bool _switchList; //=true; // when true print switchlist for this location
  /*protected*/ QString _defaultPrinter; //=NONE; // the default printer name when printing a switchlist
  /*protected*/ QString _status; //=UNKNOWN; // print switch list status
  /*protected*/ int _switchListState; //=SW_CREATE; // switch list state, saved between sessions
  /*protected*/ QPoint _trainIconEast; //=new QPoint(); // coordinates of east bound train icons
  /*protected*/ QPoint _trainIconWest; //=new QPoint();
  /*protected*/ QPoint _trainIconNorth; //=new QPoint();
  /*protected*/ QPoint _trainIconSouth; //=new QPoint();
  /*protected*/ QHash<QString, Track*> _trackHashTable; //=new Hashtable<QString, Track>();
  /*protected*/ PhysicalLocation* _physicalLocation; //=new PhysicalLocation();
  /*protected*/ QStringList _listTypes; //=new ArrayList<String>();

  // IdTag reader associated with this location.
  /*protected*/ Reporter* reader; //=null;

  // Pool
  /*protected*/ int _idPoolNumber; //=0;
  /*protected*/ QHash<QString, Pool*> _poolHashTable; //=new Hashtable<QString, Pool>();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ void setReporter(Reporter* r);
 friend class LocationEditFrame;
 };
}
#endif // LOCATION_H
