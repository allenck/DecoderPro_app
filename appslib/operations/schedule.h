#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QHash>

class QDomDocument;
class QDomElement;
class Logger;
class PropertyChangeSupport;
class PropertyChangeEvent;
namespace Operations
{
 class ScheduleItem;
 class Schedule : public QObject
 {
  Q_OBJECT
 public:
  explicit Schedule(QString id, QString name, QObject *parent = 0);
  PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
  /*public*/ static /*final*/ QString LISTCHANGE_CHANGED_PROPERTY;// = "scheduleListChange"; // NOI18N
  /*public*/ static /*final*/ QString DISPOSE;// = "scheduleDispose"; // NOI18N
  /*public*/ QString getId();
  /*public*/ void setName(QString name);
  /*public*/ QString toString();
  /*public*/ QString getName();
  /*public*/ int getSize();
  /*public*/ void setComment(QString comment);
  /*public*/ QString getComment();
  /*public*/ void dispose();
  /*public*/ void resetHitCounts() ;
  /*public*/ ScheduleItem* addItem(QString type);
  /*public*/ QList<ScheduleItem*> getItemsBySequenceList();
  /*public*/ ScheduleItem* getItemById(QString id);
  /*public*/ Schedule(QDomElement e);
  /*public*/ QDomElement store(QDomDocument doc);
  /*public*/ void _register(ScheduleItem* si);
  /*public*/ void moveItemUp(ScheduleItem* si);
  /*public*/ void moveItemDown(ScheduleItem* si);
  /*public*/ ScheduleItem* getItemBySequenceId(int sequenceId);
  /*public*/ void deleteItem(ScheduleItem* si);
  /*public*/ ScheduleItem* addItem(QString item, int sequence);

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
  void common();
  /*private*/ QList<ScheduleItem*> getItemsByIdList();
  /*private*/ void resequenceIds();

 protected:
  /*protected*/ QString _id;// = "";
  /*protected*/ QString _name;// = "";
  /*protected*/ QString _comment;// = "";

  // stores ScheduleItems for this schedule
  /*protected*/ QHash<QString, ScheduleItem*> _scheduleHashTable;// = new Hashtable<String, ScheduleItem>();
  /*protected*/ int _IdNumber;// = 0; // each item in a schedule gets its own id
  /*protected*/ int _sequenceNum;// = 0; // each item has a unique sequence number
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // SCHEDULE_H
