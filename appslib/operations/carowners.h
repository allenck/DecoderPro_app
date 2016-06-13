#ifndef CAROWNERS_H
#define CAROWNERS_H
#include "rollingstockattribute.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT CarOwners : public RollingStockAttribute
 {
 public:
  CarOwners(QObject* parent = 0);
  /*public*/ static /*final*/ QString CAROWNERS_NAME_CHANGED_PROPERTY;// = "CarOwners Name"; // NOI18N
  /*public*/ static /*final*/ QString CAROWNERS_CHANGED_PROPERTY;// = "CarOwners Length"; // NOI18N
  /*public*/ static /*synchronized*/ CarOwners* instance();
  /*public*/ void addName(QString owner);
  /*public*/ void deleteName(QString owner);
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);
 private:
  /*private*/ static CarOwners* _instance;// = null;

 protected:
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ QString getDefaultNames();

 };
}
#endif // CAROWNERS_H
