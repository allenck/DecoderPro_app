#ifndef OPERATIONS_DIVISION_H
#define OPERATIONS_DIVISION_H

#include "swingpropertychangesupport.h"
#include <QtXml>

class Logger;
namespace Operations {
 class Division :public SwingPropertyChangeSupport
 {
   Q_OBJECT
  public:
   Division(QString id, QString name, QObject* parent = nullptr);
   /*public*/ static /*final*/ QString NONE;// = "";
   /*public*/ static /*final*/ QString NAME_CHANGED_PROPERTY;// = "divisionName"; // NOI18N
   /*public*/ QString getId();
   /*public*/ void setName(QString name);
   /*public*/ QString toString();
   /*public*/ QString getName();
   /*public*/ void setComment(QString comment);
   /*public*/ QString getComment();
   /*public*/ Division(QDomElement e);
   /*public*/ QDomElement store(QDomDocument doc);

  private:
   static Logger* log;
  protected:
   /*protected*/ QString _id = NONE;
   /*protected*/ QString _name = NONE;
   /*protected*/ QString _comment = NONE;
   /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };

} // namespace Operations

#endif // OPERATIONS_DIVISION_H
