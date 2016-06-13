#ifndef ROLLINGSTOCKGROUP_H
#define ROLLINGSTOCKGROUP_H

#include <QObject>
#include "appslib_global.h"

class Logger;
class PropertyChangeSupport;
namespace Operations
{
class RollingStock;
 class APPSLIBSHARED_EXPORT RollingStockGroup : public QObject
 {
  Q_OBJECT
 public:
  RollingStockGroup(QString name, QObject *parent = 0);
  PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
  /*public*/ QString getName();
  /*public*/ QString toString();
  /*public*/ void add(RollingStock* rs);
  /*public*/ void _delete(RollingStock* rs) ;
  /*public*/ QList<RollingStock*> getGroup() ;
  /*public*/ int getTotalLength();
  /*public*/ int getAdjustedWeightTons();
  /*public*/ bool isLead(RollingStock* rs);
  /*public*/ RollingStock* getLead();
  /*public*/ int getSize();
  /*public*/ void setLead(RollingStock* rs) ;
  /*public*/ void removeLead(RollingStock* rs);
  /*public*/ void dispose();


 signals:

 public slots:

 private:
  Logger* log;
 protected:
  /*protected*/ QString _name;// = "";
  /*protected*/ RollingStock* _lead;// = null;
  /*protected*/ QList<RollingStock*> _group;// = new ArrayList<RollingStock>();
  /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // ROLLINGSTOCKGROUP_H
