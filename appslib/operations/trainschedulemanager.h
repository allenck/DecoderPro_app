#ifndef TRAINSCHEDULEMANAGER_H
#define TRAINSCHEDULEMANAGER_H

#include <QObject>
#include <QHash>

class PropertyChangeSupport;
class PropertyChangeEvent;
class QDomDocument;
class QDomElement;
class QComboBox;
class Logger;
namespace Operations
{
 class TrainSchedule;
 class TrainScheduleManager : public QObject
 {
  Q_OBJECT
 public:
  explicit TrainScheduleManager(QObject *parent = 0);
  PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
  /*public*/ static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "trainScheduleListLength"; // NOI18N
  /*public*/ static /*synchronized*/ TrainScheduleManager* instance();
  /*public*/ void dispose();
  /*public*/ int numEntries();
  /*public*/ TrainSchedule* getScheduleByName(QString name);
  /*public*/ TrainSchedule* getScheduleById(QString id);
  /*public*/ TrainSchedule* newSchedule(QString name);
  /*public*/ void _register(TrainSchedule* schedule);
  /*public*/ void deregister(TrainSchedule* schedule);
  /*public*/ QList<TrainSchedule*> getSchedulesByNameList();
  /*public*/ QList<TrainSchedule*> getSchedulesByIdList();
  /*public*/ QComboBox* getComboBox();
  /*public*/ QComboBox* getSelectComboBox();
  /*public*/ void updateComboBox(QComboBox* box);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);
  /*public*/ void createDefaultSchedules();
  Q_INVOKABLE     /*public*/ void initialize();

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
//  /*private*/ static TrainScheduleManager* _instance;// = null;
  /*private*/ int _id;// = 0;
  /*private*/ QList<TrainSchedule*> getList();

 protected:
  // stores known TrainSchedule instances by id
  /*protected*/ QHash<QString, TrainSchedule*> _scheduleHashTable;// = new Hashtable<String, TrainSchedule>();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // TRAINSCHEDULEMANAGER_H
