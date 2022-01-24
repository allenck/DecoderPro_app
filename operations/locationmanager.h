#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include <QObject>
#include <QHash>
#include "logger.h"
#include <QtXml>
#include "appslib_global.h"
#include "propertychangelistener.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"
#include "swingpropertychangesupport.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

class Reporter;
class JComboBox;
namespace Operations
{
 class Track;
 class Location;
 class APPSLIBSHARED_EXPORT LocationManager : public SwingPropertyChangeSupport, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
     Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)
 public:
  Q_INVOKABLE explicit LocationManager(QObject *parent = 0);
   ~LocationManager(){}
   LocationManager(const LocationManager&) : SwingPropertyChangeSupport(nullptr, this) {}
  /*public*/ static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "locationsListLength"; // NOI18N
  /*public*/ void dispose();
  /*public*/ int getNumberOfLocations() ;
  /*public*/ Location* getLocationByName(QString name);
  /*public*/ Location* getLocationById(QString id);
  /*public*/ void load(QDomElement root);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ QList<Location*> getLocationsByIdList();
  /*public*/ QList<Location*> getList();
  /*public*/ void _register(Location* location);
   /*public*/ bool hasDivisions();
   /*public*/ bool hasWork();
   /*public*/ bool hasReporters();
  /*public*/ Location* getLocationByReporter(Reporter* r);
  /*public*/ Track* getTrackByReporter(Reporter* r);
  /*public*/ Location* newLocation(QString name);
  /*public*/ JComboBox* getComboBox();
  /*public*/ void updateComboBox(JComboBox *box);
  /*public*/ QList<Location*> getLocationsByNameList();
  /*public*/ void deregister(Location* location);
  /*public*/ void replaceLoad(QString type, QString oldLoadName,QString newLoadName);
  /*public*/ int getMaxLocationNameLength() ;
  /*public*/ int getMaxTrackNameLength();
  /*public*/ void resetNameLengths();
  /*public*/ int getMaxLocationAndTrackNameLength();
  /*public*/ QList<Track*> getTracks(QString type);
  /*public*/ QList<Track*> getTracksByMoves(QString type);
  /*public*/ void resetMoves();
  Q_INVOKABLE/*public*/ void initialize();

 signals:

 public slots:
 private:
  /*private*/ int _id = 0;
  static Logger* log;
  /*private*/ void calculateMaxNameLengths();

 protected:
  /*protected*/ QHash<QString, Location*> _locationHashTable = QHash<QString, Location*>();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ int _maxLocationNameLength = 0;
  /*protected*/ int _maxTrackNameLength = 0;
  /*protected*/ int _maxLocationAndTrackNameLength = 0;

 };
}
Q_DECLARE_METATYPE(Operations::LocationManager)
#endif // LOCATIONMANAGER_H
