#ifndef CARROADS_H
#define CARROADS_H
#include "rollingstockattribute.h"
#include <QtXml>
#include "appslib_global.h"
#include "instancemanagerautodefault.h"

class Logger;
namespace Operations
{
 class APPSLIBSHARED_EXPORT CarRoads : public RollingStockAttribute, public InstanceManagerAutoDefault
 {
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  Q_INVOKABLE explicit CarRoads(QObject *parent = 0);
  ~CarRoads() {}
  CarRoads(const CarRoads&) : RollingStockAttribute() {}
  /*public*/ static /*final*/ QString CARROADS_CHANGED_PROPERTY;// = "CarRoads Length"; // NOI18N
  /*public*/ static /*final*/ QString CARROADS_NAME_CHANGED_PROPERTY;// = "CarRoads Name"; // NOI18N
  /*public*/ void addName(QString road);
  /*public*/ void deleteName(QString road) ;
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ int getMaxNameLength();
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);

 signals:

 public slots:
 private:
  /*private*/ int maxNameLengthSubType;// = 0;
  Logger* log;
  /*private*/ static /*final*/ QString ROADS;// = Bundle.getMessage("carRoadNames");

 protected:
  /*protected*/ QString getDefaultNames();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
Q_DECLARE_METATYPE(Operations::CarRoads)
#endif // CARROADS_H
