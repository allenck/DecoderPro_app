#ifndef CARLOAD_H
#define CARLOAD_H
#include "qobject.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT CarLoad : public QObject
 {
  Q_OBJECT
 public:
  explicit CarLoad(QString name, QObject *parent = 0);
  /*public*/ static /*final*/ QString NONE;// = "";

  /*public*/ static /*final*/ QString PRIORITY_LOW;// = Bundle.getMessage("Low");
  /*public*/ static /*final*/ QString PRIORITY_HIGH;// = Bundle.getMessage("High");

  /*public*/ static /*final*/ QString LOAD_TYPE_EMPTY;// = Bundle.getMessage("Empty");
  /*public*/ static /*final*/ QString LOAD_TYPE_LOAD;// = Bundle.getMessage("Load");

  /*public*/ static /*final*/ QString SPLIT_CHAR;// = " & "; // used to combine car type and load in tracks and trains
  /*public*/ QString getName();
  /*public*/ void setName(QString name);
  /*public*/ QString getPriority();
  /*public*/ void setPriority(QString priority) ;
  /*public*/ QString getPickupComment() ;
  /*public*/ void setPickupComment(QString comment);
  /*public*/ QString getDropComment();
  /*public*/ void setDropComment(QString comment);
  /*public*/ QString getLoadType();
  /*public*/ void setLoadType(QString type);

 signals:

 public slots:
 private:
  QString _name;
  QString _priority;// = PRIORITY_LOW;
  QString _pickupComment;// = NONE;
  QString _dropComment;// = NONE;
  QString _loadType;// = LOAD_TYPE_LOAD;

 };
}
#endif // CARLOAD_H
