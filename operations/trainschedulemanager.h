#ifndef TRAINSCHEDULEMANAGER_H
#define TRAINSCHEDULEMANAGER_H

#include <QObject>
#include <QHash>
#include "propertychangesupport.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

class PropertyChangeSupport;
class PropertyChangeEvent;
class QDomDocument;
class QDomElement;
class JComboBox;
class Logger;
namespace Operations
{
 class TrainSchedule;
 class TrainScheduleManager : public PropertyChangeSupport, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)

 public:
   /*public*/ static /*final*/ QString NONE;// = "";
  Q_INVOKABLE explicit TrainScheduleManager(QObject *parent = 0);
   ~TrainScheduleManager() {}
   TrainScheduleManager(const TrainScheduleManager&) : PropertyChangeSupport(this) {}
   PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
  /*public*/ static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "trainScheduleListLength"; // NOI18N
   /*public*/ static /*final*/ QString SCHEDULE_ID_CHANGED_PROPERTY;// = "ActiveTrainScheduleId"; // NOI18N
  /*public*/ void dispose();
  /*public*/ int numEntries();
  /*public*/ TrainSchedule* getScheduleByName(QString name);
  /*public*/ TrainSchedule* getScheduleById(QString id);
  /*public*/ TrainSchedule* newSchedule(QString name);
  /*public*/ void _register(TrainSchedule* schedule);
  /*public*/ void deregister(TrainSchedule* schedule);
  /*public*/ QList<TrainSchedule*> getSchedulesByNameList();
  /*public*/ QList<TrainSchedule*> getSchedulesByIdList();
  /*public*/ JComboBox* getComboBox();
  /*public*/ JComboBox* getSelectComboBox();
  /*public*/ void updateComboBox(JComboBox* box);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);
  /*public*/ void createDefaultSchedules();
   /*public*/ void setTrainScheduleActiveId(QString id);
   /*public*/ QString getTrainScheduleActiveId();
   /*public*/ TrainSchedule* getActiveSchedule();

  Q_INVOKABLE     /*public*/ void initialize();

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
//  /*private*/ static TrainScheduleManager* _instance;// = null;
  /*private*/ int _id;// = 0;
  /*private*/ QList<TrainSchedule*> getList();
  /*private*/ QString _trainScheduleActiveId = NONE;

 protected:
  // stores known TrainSchedule instances by id
  /*protected*/ QHash<QString, TrainSchedule*> _scheduleHashTable;// = new Hashtable<String, TrainSchedule>();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
Q_DECLARE_METATYPE(Operations::TrainScheduleManager)
#endif // TRAINSCHEDULEMANAGER_H
