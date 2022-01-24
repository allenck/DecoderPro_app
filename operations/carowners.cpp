#include "carowners.h"
#include "control.h"
#include "setup.h"
#include "xml.h"
#include "carmanagerxml.h"
#include "logger.h"
#include "instancemanager.h"
//CarOwners::CarOwners()
//{

//}
namespace Operations
{
/**
 * Represents the owner names that cars can have.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class CarOwners extends RollingStockAttribute {

 /*public*/ /*static*/ /*final*/ QString CarOwners::CAROWNERS_NAME_CHANGED_PROPERTY = "CarOwners Name"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString CarOwners::CAROWNERS_CHANGED_PROPERTY = "CarOwners Length"; // NOI18N

 /*public*/ CarOwners::CarOwners(QObject* parent) : RollingStockAttribute(parent)
 {
 setProperty("InstanceManagerAutoDefault", "yes");

 }

 /*protected*/ QString CarOwners::getDefaultNames() {
     return ""; // there aren't any
 }

 /*public*/ void CarOwners::addName(QString owner) {
     RollingStockAttribute::addName(owner);
     setDirtyAndFirePropertyChange(CAROWNERS_CHANGED_PROPERTY, QVariant(), owner);
 }

 /*public*/ void CarOwners::deleteName(QString owner) {
     RollingStockAttribute::deleteName(owner);
     setDirtyAndFirePropertyChange(CAROWNERS_CHANGED_PROPERTY, owner, QVariant());
 }

 /*public*/ void CarOwners::replaceName(QString oldName, QString newName) {
     RollingStockAttribute::addName(newName);
     setDirtyAndFirePropertyChange(CAROWNERS_NAME_CHANGED_PROPERTY, oldName, newName);
     RollingStockAttribute::deleteName(newName);
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-cars.dtd.
  *
  */
 /*public*/ void CarOwners::store(QDomElement root, QDomDocument doc) {
     RollingStockAttribute::store(root, Xml::OWNERS, Xml::OWNER, Xml::CAR_OWNERS, doc);
 }

 /*public*/ void CarOwners::load(QDomElement root) {
     RollingStockAttribute::load(root, Xml::OWNERS, Xml::OWNER, Xml::CAR_OWNERS);
 }

 /*protected*/ void CarOwners::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // Set dirty
     ((CarManagerXml*)InstanceManager::getDefault("CarManagerXml"))->setDirty(true);
     RollingStockAttribute::firePropertyChange(p, old, n);
 }
}
