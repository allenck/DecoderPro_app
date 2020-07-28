#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H

#include <QObject>
#include <QHash>
#include "logger.h"
#include "propertychangesupport.h"
#include <QtXml>
#include "appslib_global.h"

class JComboBox;
namespace Operations {
 class RouteLocation;
 class Route;
 class APPSLIBSHARED_EXPORT RouteManager : public QObject
 {
  Q_OBJECT
 public:
  explicit RouteManager(QObject *parent = 0);
  /*public*/ static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "routesListLengthChanged"; // NOI18N
  PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
  /*public*/ static /*synchronized*/ RouteManager* instance();
  /*public*/ void dispose();
  /*public*/ Route* getRouteByName(QString name);
  /*public*/ Route* getRouteById(QString id);
  /*public*/ Route* newRoute(QString name);
  /*public*/ void _register(Route* route);
  /*public*/ void deregister(Route* route);
  /*public*/ QList<Route*> getRoutesByNameList();
  /*public*/ QList<Route*> getRoutesByIdList();
  /*public*/ JComboBox* getComboBox();
  /*public*/ void updateComboBox(JComboBox* box);
  /*public*/ int numEntries();
  /*public*/ void load(QDomElement root);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ Route* copyRoute(Route* route, QString routeName, bool invert);
  Q_INVOKABLE /*public*/ void initialize();
  virtual /*public*/ Route* provide(QString name) throw (IllegalArgumentException) = 0;
 signals:
 
 public slots:
 private:
  /*private*/ static RouteManager* _instance;// = null;
  /*private*/ int _id;// = 0;
  Logger* log;
  /*private*/ QList<Route*> getList();
  /*private*/ void copyRouteLocation(Route* newRoute, RouteLocation* rl, RouteLocation* rlNext, bool invert);

 protected:
  // stores known Route instances by id
  /*protected*/ QHash<QString, Route*> _routeHashTable;// = new QHash<QString, Route*>();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // ROUTEMANAGER_H
