#ifndef CAR_H
#define CAR_H
#include "rollingstock.h"
#include <QtXml>
#include "appslib_global.h"
#include "carloads.h"
#include "instancemanager.h"

namespace Operations
{
 class CarLoads;
 class Kernel;
 class APPSLIBSHARED_EXPORT Car : public RollingStock//, public PropertyChangeListener
 {
  Q_OBJECT
   //Q_INTERFACES(PropertyChangeListener)
 public:
  Car(QObject* parent = 0);
  /*public*/ Car(QString road, QString number,QObject* parent =0);
  /*public*/ Car* copy();
  /*public*/ static /*final*/ QString EXTENSION_REGEX;// =" ";
  /*public*/ static /*final*/ QString CABOOSE_EXTENSION;// =Bundle.getMessage("(C)");
  /*public*/ static /*final*/ QString FRED_EXTENSION;// =Bundle.getMessage("(F)");
  /*public*/ static /*final*/ QString PASSENGER_EXTENSION;// =Bundle.getMessage("(P)");
  /*public*/ static /*final*/ QString UTILITY_EXTENSION;// =Bundle.getMessage("(U)");
  /*public*/ static /*final*/ QString HAZARDOUS_EXTENSION;// =Bundle.getMessage("(H)");

  /*public*/ static /*final*/ QString LOAD_CHANGED_PROPERTY; //="Car load changed"; // NOI18N property change descriptions
  /*public*/ static /*final*/ QString RWE_LOAD_CHANGED_PROPERTY;// = "Car RWE load changed"; // NOI18N
  /*public*/ static /*final*/ QString RWL_LOAD_CHANGED_PROPERTY;// = "Car RWL load changed"; // NOI18N
  /*public*/ static /*final*/ QString WAIT_CHANGED_PROPERTY; //="Car wait changed"; // NOI18N
  /*public*/ static /*final*/ QString NEXT_WAIT_CHANGED_PROPERTY; //="Car next wait changed"; // NOI18N
  /*public*/ static /*final*/ QString FINAL_DESTINATION_CHANGED_PROPERTY; //="Car final destination changed"; // NOI18N
  /*public*/ static /*final*/ QString FINAL_DESTINATION_TRACK_CHANGED_PROPERTY; //="Car final destination track changed"; // NOI18N
  /*public*/ static /*final*/ QString RETURN_WHEN_EMPTY_CHANGED_PROPERTY; //="Car return when empty changed"; // NOI18N
  /*public*/ static /*final*/ QString RETURN_WHEN_LOADED_CHANGED_PROPERTY;// = "Car return when loaded changed"; // NOI18N
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
  /*public*/ void setReturnWhenLoadedLoadName(QString load);
  /*public*/ QString getReturnWhenLoadedLoadName();
  /*public*/ QString getLoadPriority() ;
  /*public*/ QString getLoadType();
  /*public*/ QString getPickupComment();
  /*public*/ QString getDropComment();
  /*public*/ void setLoadGeneratedFromStaging(bool fromStaging);
  /*public*/ bool isLoadGeneratedFromStaging();
  /*public*/ QString getReturnWhenEmptyDestName();
  /*public*/ void setReturnWhenLoadedDestination(Location* destination);
  /*public*/ Location* getReturnWhenLoadedDestination();
  /*public*/ QString getReturnWhenLoadedDestinationName();
  /*public*/ QString getReturnWhenLoadedDestName();
  /*public*/ void setReturnWhenLoadedDestTrack(Track* track);
  /*public*/ Track* getReturnWhenLoadedDestTrack();
  /*public*/ QString getReturnWhenLoadedDestTrackName();
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
  /*public*/ QString getTypeExtensions();
  /*public*/ void reset();
  /*public*/ QString testDestination(Location* destination, Track* track)override;
  /*public*/ void loadNext(Track* destTrack);
  /*public*/ QString setDestination(Location* destination, Track* track);
  /*public*/ QString setDestination(Location* destination, Track* track, bool force);
  QObject* pself() override {return (QObject*)this; }

public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
  static Logger* log;
  void common();
  CarLoads* carLoads = (CarLoads*)InstanceManager::getDefault("Operations::CarLoads");
  bool loaded;
  /*private*/ void addPropertyChangeListeners();
  /*private*/ void setLoadEmpty();
  /*private*/ void setReturnWhenEmpty();

 protected:
  /*protected*/ bool _passenger=false;
  /*protected*/ bool _hazardous=false;
  /*protected*/ bool _caboose=false;
  /*protected*/ bool _fred=false;
  /*protected*/ bool _utility=false;
  /*protected*/ bool _loadGeneratedByStaging=false;
  /*protected*/ Kernel* _kernel=nullptr;
  /*protected*/ QString _loadName=carLoads->getDefaultEmptyName();
  /*protected*/ int _wait=0;

  /*protected*/ Location* _rweDestination=nullptr; // return when empty destination
  /*protected*/ Track* _rweDestTrack=nullptr; // return when empty track
  /*protected*/ QString _rweLoadName=carLoads->getDefaultEmptyName();

  /*protected*/ Location* _rwlDestination = nullptr; // return when loaded destination
  /*protected*/ Track* _rwlDestTrack = nullptr; // return when loaded track
  /*protected*/ QString _rwlLoadName = carLoads->getDefaultLoadName();

  // schedule items
  /*protected*/ QString _scheduleId=NONE; // the schedule id assigned to this car
  /*protected*/ QString _nextLoadName=NONE; // next load by schedule
  /*protected*/ int _nextWait=0; // next wait by schedule
  /*protected*/ Location* _finalDestination=nullptr; // final destination by schedule or router
  /*protected*/ Track* _finalDestTrack=nullptr; // final track by schedule or router
  /*protected*/ Location* _previousFinalDestination=nullptr; // previous final destination (for train resets)
  /*protected*/ Track* _previousFinalDestTrack=nullptr; // previous final track (for train resets)
  /*protected*/ QString _previousScheduleId=NONE; // previous schedule id (for train resets)
  /*protected*/ QString _pickupScheduleId=NONE;
  /*protected*/ QString _nextPickupScheduleId=NONE; // when the car needs to be pulled
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n)override;
  /*protected*/ bool isRwlEnabled();

 };
}
#endif // CAR_H
