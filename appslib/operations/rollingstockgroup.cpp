#include "rollingstockgroup.h"
#include "rollingstock.h"
#include "propertychangesupport.h"

//RollingStockGroup::RollingStockGroup(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * A group of rolling stock that is managed as one unit.
 *
 * @author Daniel Boudreau Copyright (C) 2010, 2013
 * @version $Revision: 28746 $
 */
// /*public*/ class RollingStockGroup {

namespace Operations
{
 /*public*/ RollingStockGroup::RollingStockGroup(QString name, QObject *parent) :
    QObject(parent)
{
 _name = name;
 pcs = new PropertyChangeSupport(this);
 log = new Logger("RollingStockGroup");

 }

 /*public*/ QString RollingStockGroup::getName() {
     return _name;
 }

 // for combo boxes
 /*public*/ QString RollingStockGroup::toString() {
     return _name;
 }

 /*public*/ void RollingStockGroup::add(RollingStock* rs) {
     if (_group.contains(rs)) {
         log->debug(tr("rs (%1) already part of group (%2)").arg(rs->toString()).arg(getName()));
         return;
     }
     if (_group.size() <= 0) {
         _lead = rs;
     }
     int oldSize = _group.size();
     _group.append(rs);
     firePropertyChange("grouplistLength", QString::number(oldSize), (_group.size())); // NOI18N
 }

 /*public*/ void RollingStockGroup::_delete(RollingStock* rs) {
     if (!_group.contains(rs)) {
         log->debug(tr("rs (%1) not part of group (%2)").arg(rs->getId()).arg(getName()));
         return;
     }
     int oldSize = _group.size();
     _group.removeOne(rs);
     // need a new lead rs?
     removeLead(rs);
     firePropertyChange("grouplistLength", QString::number(oldSize), (_group.size())); // NOI18N
 }

 /*public*/ QList<RollingStock*> RollingStockGroup::getGroup() {
     return _group;
 }

 /*public*/ int RollingStockGroup::getTotalLength() {
     int length = 0;
     foreach (RollingStock* rs, _group) {
         length = length + rs->getTotalLength();
     }
     return length;
 }

 /**
  * Get a group's adjusted weight
  *
  * @return group's weight
  */
 /*public*/ int RollingStockGroup::getAdjustedWeightTons() {
     int weightTons = 0;
     foreach (RollingStock* rs, _group) {
         weightTons = weightTons + rs->getAdjustedWeightTons();
     }
     return weightTons;
 }

 /*public*/ bool RollingStockGroup::isLead(RollingStock* rs) {
     if (rs == _lead) {
         return true;
     }
     return false;
 }

 /*public*/ RollingStock* RollingStockGroup::getLead() {
     return _lead;
 }

 /**
  * Gets the number of rolling stock in this group
  *
  * @return number of elements in this group
  */
 /*public*/ int RollingStockGroup::getSize() {
     return _group.size();
 }

 /**
  * Sets the lead for this group. RollingStock must be part of the group. The
  * rolling stock that make up this group will have the attributes of the
  * lead. However, the length attribute is the sum of all unit lengths plus
  * the coupler lengths.
  *
  * @param rs lead for this group.
  */
 /*public*/ void RollingStockGroup::setLead(RollingStock* rs) {
     if (_group.contains(rs)) {
         _lead = rs;
     }
 }

 /*public*/ void RollingStockGroup::removeLead(RollingStock* rs) {
     if (isLead(rs) && _group.size() > 0) {
         setLead(_group.at(0));
     }
 }

 /*public*/ void RollingStockGroup::dispose() {

 }
#if 0

 /*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.removePropertyChangeListener(l);
 }
#endif
 /*protected*/ void RollingStockGroup::firePropertyChange(QString p, QVariant old, QVariant n) {
     pcs->firePropertyChange(p, old, n);
 }
}
