#ifndef TRAINSCHEDULE_H
#define TRAINSCHEDULE_H

#include <QObject>
#include <QStringList>

class QDomDocument;
class QDomElement;
class Logger;
class QStringList;
class SwingPropertyChangeSupport;
class PropertyChangeEvent;
namespace Operations
{
 class TrainSchedule : public QObject
 {
  Q_OBJECT
 public:
  /*public*/ TrainSchedule(QString id, QString name, QObject *parent = 0);
  SwingPropertyChangeSupport* pcs;// = new java.beans.SwingPropertyChangeSupport(this,this);
  /*public*/ QString NONE;// = "";
  /*public*/ static /*final*/ QString NAME_CHANGED_PROPERTY;// = "trainScheduleName"; // NOI18N
  /*public*/ static /*final*/ QString SCHEDULE_CHANGED_PROPERTY;// = "trainScheduleChanged"; // NOI18N
  /*public*/ QString getId() ;
  /*public*/ void setName(QString name) ;
  /*public*/ QString toString();
  /*public*/ QString getName();
  /*public*/ void setComment(QString comment);
  /*public*/ QString getComment();
  /*public*/ void addTrainId(QString id);
  /*public*/ void removeTrainId(QString id) ;
  /*public*/ bool containsTrainId(QString id);
  /*public*/ TrainSchedule(QDomElement e);
  /*public*/ QDomElement store(QDomDocument doc);


 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
 protected:
  /*protected*/ QString _id;// = NONE;
  /*protected*/ QString _name;// = NONE;
  /*protected*/ QString _comment;// = NONE;
  /*protected*/ QStringList _trainIds;// = new ArrayList<String>();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // TRAINSCHEDULE_H
