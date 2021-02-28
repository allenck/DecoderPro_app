#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <QObject>
#include <QHash>
#include "schedule.h"
#include "propertychangelistener.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

class QDomDocument;
class QDomElement;
class JComboBox;
class Logger;
class PropertyChangeSupport;
class PropertyChangeEvent;
namespace Operations
{
 class Schedule;
 class ScheduleManager : public QObject, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize, public PropertyChangeListener
 {
  Q_OBJECT
     Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize PropertyChangeListener)
 public:
  explicit ScheduleManager(QObject *parent = 0);
  PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
  /*public*/ static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "scheduleListLength"; // NOI18N
  /*public*/ static /*synchronized*/ ScheduleManager* instance();
  /*public*/ void dispose();
  /*public*/ int numEntries();
  /*public*/ Schedule* getScheduleByName(QString name);
  /*public*/ Schedule* getScheduleById(QString id);
  /*public*/ Schedule* newSchedule(QString name) ;
  /*public*/ void _register(Schedule* schedule);
  /*public*/ void deregister(Schedule* schedule);
  /*public*/ QList<Schedule*> getSchedulesByNameList();
  /*public*/ QList<Schedule*> getSchedulesByIdList();
  /*public*/ Schedule* copySchedule (Schedule* schedule, QString newScheduleName);
  /*public*/ void resetHitCounts();
  /*public*/ JComboBox* getComboBox() ;
  /*public*/ void updateComboBox(JComboBox* box);
  /*public*/ void replaceType(QString oldType, QString newType);
  /*public*/ void replaceRoad(QString oldRoad, QString newRoad);
  /*public*/ void replaceLoad(QString type, QString oldLoad, QString newLoad);
  /*public*/ JComboBox* getSpursByScheduleComboBox(Schedule* schedule);
  /*public*/ void load(QDomElement root);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  Q_INVOKABLE /*public*/ void initialize();

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
  /*private*/ static ScheduleManager* _instance;// = null;
  /*private*/ int _id;// = 0;
  /*private*/ QList<Schedule*> getList();


 protected:
   // stores known Schedule instances by id
   /*protected*/ QHash<QString, Schedule*> _scheduleHashTable;// = new Hashtable<String, Schedule>();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // SCHEDULEMANAGER_H
