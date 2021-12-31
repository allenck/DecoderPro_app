#ifndef OROUTEMANAGER_H
#define OROUTEMANAGER_H

#include <QObject>
#include <QHash>
#include "logger.h"
#include "propertychangesupport.h"
#include <QtXml>
#include "appslib_global.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

class JComboBox;
namespace Operations {
 class RouteLocation;
 class Route;
 class APPSLIBSHARED_EXPORT RouteManager : public PropertyChangeSupport, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)
 public:
  Q_INVOKABLE explicit RouteManager(QObject *parent = 0);
   ~RouteManager() {}
   RouteManager(const RouteManager&) : PropertyChangeSupport(nullptr) {}
  /*public*/ static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "routesListLengthChanged"; // NOI18N
  //PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
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
  Q_INVOKABLE /*public*/ void initialize() override;
  //virtual /*public*/ Route* provide(QString /*name*/)const  /*throw (IllegalArgumentException)*/ =0;
  //QObject* self() {return (QObject*)this;}
  QString getNamedBeanClass() const {return "RouteManager";}

 signals:
 
 public slots:
 private:
  /*private*/ static RouteManager* _instance;// = null;
  /*private*/ int _id;// = 0;
  static Logger* log;
  /*private*/ QList<Route*> getList();
  /*private*/ void copyRouteLocation(Route* newRoute, RouteLocation* rl, RouteLocation* rlNext, bool invert);

 protected:
  // stores known Route instances by id
  /*protected*/ QHash<QString, Route*> _routeHashTable = QHash<QString, Route*>();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
Q_DECLARE_METATYPE(Operations::RouteManager)
#endif // OROUTEMANAGER_H
