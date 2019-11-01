#ifndef OPERATIONSROUTE_H
#define OPERATIONSROUTE_H

#include <QObject>
#include <QHash>
#include "logger.h"
#include "propertychangesupport.h"
#include <QtXml>
#include "appslib_global.h"

class QComboBox;
namespace Operations
{
 class Location;
 class RouteLocation;
 class APPSLIBSHARED_EXPORT Route : public QObject
 {
  Q_OBJECT
 public:
  //explicit Route(QObject *parent = 0);
  /*public*/ Route(QString id, QString name, QObject* parent = 0);
  /*public*/ Route(QDomElement e);

  PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
  /*public*/ static /*final*/ QString NONE;// = "";
  /*public*/ static /*final*/ int EAST;// = 1; // train direction
  /*public*/ static /*final*/ int WEST;// = 2;
  /*public*/ static /*final*/ int NORTH;// = 4;
  /*public*/ static /*final*/ int SOUTH;// = 8;

  /*public*/ static /*final*/ QString LISTCHANGE_CHANGED_PROPERTY;// = "routeListChange"; // NOI18N
  /*public*/ static /*final*/ QString DISPOSE;// = "routeDispose"; // NOI18N

  /*public*/ static /*final*/ QString OKAY;// = tr("Okay");
  /*public*/ static /*final*/ QString ORPHAN;// = tr("Orphan");
  /*public*/ static /*final*/ QString ERROR;// = tr("Error");
  /*public*/ QString getId();
  /*public*/ void setName(QString name);
  // for combo boxes
  /*public*/ QString toString();
  /*public*/ QString getName();
  /*public*/ void setComment(QString comment);
  /*public*/ QString getComment() ;
  /*public*/ void dispose();
  /*public*/ RouteLocation* getLocationById(QString id);
  /*public*/ RouteLocation* getDepartsRouteLocation();
  /*public*/ RouteLocation* getTerminatesRouteLocation();
  /*public*/ QList<RouteLocation*>* getLocationsBySequenceList();
  /*public*/ int size();
  /*public*/ RouteLocation* getLastLocationByName(QString name);
  /*public*/ QDomElement store(QDomDocument);
  /*public*/ void _register(RouteLocation* rl);
  /*public*/ QString getStatus();
  /*public*/ RouteLocation* addLocation(Location* location);
  /*public*/ RouteLocation* addLocation(Location* location, int sequence);
  /*public*/ void moveLocationUp(RouteLocation* rl);
  /*public*/ RouteLocation* getItemBySequenceId(int sequenceId);
  /*public*/ void moveLocationDown(RouteLocation* rl);
  /*public*/ void deleteLocation(RouteLocation* rl);
  /*public*/ RouteLocation* getNextRouteLocation(RouteLocation* rl);
  /*public*/ QComboBox* getComboBox();
  /*public*/ void updateComboBox(QComboBox* box);

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
  /*private*/ QList<RouteLocation*> getLocationsByIdList();
 void common();
 /*private*/ void resequenceIds();

 protected:
  /*protected*/ QString _id;// = NONE;
  /*protected*/ QString _name;// = NONE;
  /*protected*/ QString _comment;// = NONE;
  // stores location names for this route
  /*protected*/ QHash<QString, RouteLocation*> _routeHashTable;// = newQHash<String, RouteLocation>();
  /*protected*/ int _IdNumber;// = 0; // each location in a route gets its own id
  /*protected*/ int _sequenceNum;// = 0; // each location has a unique sequence number
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
} // end namespace
#endif // OPERATIONSROUTE_H
