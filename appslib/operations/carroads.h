#ifndef CARROADS_H
#define CARROADS_H
#include "rollingstockattribute.h"
#include <QtXml>
#include "appslib_global.h"

class Logger;
namespace Operations
{
 class APPSLIBSHARED_EXPORT CarRoads : public RollingStockAttribute
 {
  Q_OBJECT
 public:
  explicit CarRoads(QObject *parent = 0);
  /*public*/ static /*synchronized*/ CarRoads* instance();
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
  /**
   * record the single instance *
   */
  /*private*/ static CarRoads* _instance;// = NULL;
  /*private*/ static /*final*/ QString ROADS;// = Bundle.getMessage("carRoadNames");

 protected:
  /*protected*/ QString getDefaultNames();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // CARROADS_H
