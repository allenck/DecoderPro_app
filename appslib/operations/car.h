#ifndef CAR_H
#define CAR_H
#include "rollingstock.h"
#include <QtXml>
#include "appslib_global.h"

namespace Operations
{
 class CarLoads;
 class Kernel;
 class APPSLIBSHARED_EXPORT Car : public RollingStock
 {
  Q_OBJECT
 public:
  Car(QObject* parent = 0);
  /*public*/ Car(QString road, QString number,QObject* parent =0);
  /*public*/ Car* copy();
  /*public*/ static /*final*/ QString LOAD_CHANGED_PROPERTY; //="Car load changed"; // NOI18N property change descriptions
  /*public*/ static /*final*/ QString WAIT_CHANGED_PROPERTY; //="Car wait changed"; // NOI18N
  /*public*/ static /*final*/ QString NEXT_WAIT_CHANGED_PROPERTY; //="Car next wait changed"; // NOI18N
  /*public*/ static /*final*/ QString FINAL_DESTINATION_CHANGED_PROPERTY; //="Car final destination changed"; // NOI18N
  /*public*/ static /*final*/ QString FINAL_DESTINATION_TRACK_CHANGED_PROPERTY; //="Car final destination track changed"; // NOI18N
  /*public*/ static /*final*/ QString RETURN_WHEN_EMPTY_CHANGED_PROPERTY; //="Car return when empty changed"; // NOI18N
  /*public*/ static /*final*/ QString SCHEDULE_ID_CHANGED_PROPERTY; //="car schedule id changed"; // NOI18N
  /*public*/ static /*final*/ QString KERNEL_NAME_CHANGED_PROPERTY; //="kernel name changed"; // NOI18N
  /*public*/ void setHazardous(bool hazardous);
  /*public*/ bool isHazardous();
  /*public*/ void setPassenger(bool passenger);
  /*public*/ bool isPassenger();
  /*public*/ void setCaboose(bool caboose) ;
  /*public*/ bool isCaboose();
  /*public*/ void setUtility(bool utility);
  /*public*/ bool isUtility();
  /*public*/ void dispose();
  /*public*/ Car(QDomElement e, QObject* parent = 0);
  /*public*/ QDomElement store(QDomDocument doc);
  /*public*/ void setKernel(Kernel* kernel);
  /*public*/ Kernel* getKernel();
  /*public*/ QString getKernelName();
  /*public*/ void updateKernel();
  /*public*/ Location* getFinalDestination();
  /*public*/ QString getFinalDestinationName();
  /*public*/ void setFinalDestinationTrack(Track* track);
  /*public*/ void setScheduleItemId(QString id);
  /*public*/ QString getScheduleItemId();
  /*public*/ void setFinalDestination(Location* destination);
  /*public*/ Track* getFinalDestinationTrack();
  /*public*/ QString getFinalDestinationTrackName();
  /*public*/ void setFred(bool fred);
  /*public*/ bool hasFred();
  /*public*/ void setLoadName(QString load) ;
  /*public*/ QString getLoadName();
  /*public*/ void setReturnWhenEmptyLoadName(QString load);
  /*public*/ QString getReturnWhenEmptyLoadName();
  /*public*/ QString getLoadPriority() ;
  /*public*/ QString getLoadType();
  /*public*/ QString getPickupComment();
  /*public*/ QString getDropComment();
  /*public*/ void setLoadGeneratedFromStaging(bool fromStaging);
  /*public*/ bool isLoadGeneratedFromStaging();
  /*public*/ QString getReturnWhenEmptyDestName();
  /*public*/ int getWait();
  /*public*/ QString getPickupScheduleName();
  /*public*/ Location* getReturnWhenEmptyDestination();
  /*public*/ QString getReturnWhenEmptyDestinationName();
  /*public*/ QString getReturnWhenEmptyDestTrackName();
  /*public*/ Track* getReturnWhenEmptyDestTrack();
  /*public*/ int getNextWait();
  /*public*/ void setWait(int count);
  /*public*/ void setNextWait(int count);
  /*public*/ void setPickupScheduleId(QString id);
  /*public*/ QString getPickupScheduleId() ;
  /*public*/ void setNextPickupScheduleId(QString id);
  /*public*/ QString getNextPickupScheduleId();
  /*public*/ void setNextLoadName(QString load);
  /*public*/ QString getNextLoadName();
  /*public*/ QString getWeightTons();
  /*public*/ int getAdjustedWeightTons();
  /*public*/ void setPreviousFinalDestination(Location* location);
  /*public*/ Location* getPreviousFinalDestination() ;
  /*public*/ void setPreviousFinalDestinationTrack(Track* track);
  /*public*/ Track* getPreviousFinalDestinationTrack();
  /*public*/ void setPreviousScheduleId(QString id);
  /*public*/ QString getPreviousScheduleId();
  /*public*/ void setReturnWhenEmptyDestination(Location* destination);
  /*public*/ void setReturnWhenEmptyDestTrack(Track* track);
  /*public*/ void updateLoad();
  /*public*/ void reset();
  /*public*/ QString testDestination(Location* destination, Track* track);
  /*public*/ void loadNext(Track* destTrack);
  /*public*/ QString setDestination(Location* destination, Track* track);
  /*public*/ QString setDestination(Location* destination, Track* track, bool force);

public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
  void common();
  CarLoads* carLoads;// = CarLoads::instance();
  bool loaded;
  /*private*/ void addPropertyChangeListeners();
  /*private*/ void setLoadEmpty();
  /*private*/ void setReturnWhenEmpty();

 protected:
  /*protected*/ bool _passenger; //=false;
  /*protected*/ bool _hazardous; //=false;
  /*protected*/ bool _caboose; //=false;
  /*protected*/ bool _fred; //=false;
  /*protected*/ bool _utility; //=false;
  /*protected*/ bool _loadGeneratedByStaging; //=false;
  /*protected*/ Kernel* _kernel; //=null;
  /*protected*/ QString _loadName; //=carLoads.getDefaultEmptyName();
  /*protected*/ int _wait; //=0;

  /*protected*/ Location* _rweDestination; //=null; // return when empty destination
  /*protected*/ Track* _rweDestTrack; //=null; // return when empty track
  /*protected*/ QString _rweLoadName; //=carLoads.getDefaultEmptyName();

  // schedule items
  /*protected*/ QString _scheduleId; //=NONE; // the schedule id assigned to this car
  /*protected*/ QString _nextLoadName; //=NONE; // next load by schedule
  /*protected*/ int _nextWait; //=0; // next wait by schedule
  /*protected*/ Location* _finalDestination; //=null; // final destination by schedule or router
  /*protected*/ Track* _finalDestTrack; //=null; // final track by schedule or router
  /*protected*/ Location* _previousFinalDestination; //=null; // previous final destination (for train resets)
  /*protected*/ Track* _previousFinalDestTrack; //=null; // previous final track (for train resets)
  /*protected*/ QString _previousScheduleId; //=NONE; // previous schedule id (for train resets)
  /*protected*/ QString _pickupScheduleId; //=NONE;
  /*protected*/ QString _nextPickupScheduleId; //=NONE; // when the car needs to be pulled
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // CAR_H
