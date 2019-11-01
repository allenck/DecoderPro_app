#ifndef POOL_H
#define POOL_H

#include <QObject>
#include "appslib_global.h"

class Logger;
class PropertyChangeSupport;
namespace Operations
{
 class Track;
 class APPSLIBSHARED_EXPORT Pool : public QObject
 {
  Q_OBJECT
 public:
  //explicit Pool(QObject *parent = 0);
  /*public*/ static /*final*/ QString LISTCHANGE_CHANGED_PROPERTY;// = "poolListChange"; // NOI18N
  /*public*/ static /*final*/ QString DISPOSE;// = "poolDispose"; // NOI18N
  /*public*/ QString getId();
  /*public*/ QString getName();
  /*public*/ void setName(QString name);
  /*public*/ int getSize();
  /*public*/ QString toString();
  /*public*/ Pool(QString id, QString name,QObject *parent = 0) ;
  /*public*/ void dispose();
  /*public*/ void add(Track* track);
  /*public*/ void remove(Track* track);
  /*public*/ QList<Track*> getTracks();
  /*public*/ int getTotalLengthTracks() ;
  /*public*/ bool requestTrackLength(Track* track, int length);
  PropertyChangeSupport* propertyChangeSupport;

 signals:

 public slots:

 private:
  Logger* log;
 protected:
  /*protected*/ QList<Track*> _tracks;// = new ArrayList<Track>();

  /*protected*/ QString _id;// = "";
  /*protected*/ QString _name;// = "";

 };
}
#endif // POOL_H
