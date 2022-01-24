#include "enginetypes.h"
#include "logger.h"
#include "control.h"
#include "xml.h"
#include "enginemanagerxml.h"
#include "instancemanager.h"

//EngineTypes::EngineTypes(QObject *parent) :
//  RollingStockAttribute(parent)
//{
//}
namespace Operations
{
 /**
  * Represents the types of engines a railroad can have.
  *
  * @author Daniel Boudreau Copyright (C) 2008, 2014
  * @version $Revision: 29493 $
  */
///*public*/ class EngineTypes extends RollingStockAttribute {

 /*private*/ /*static*/ /*final*/ QString EngineTypes::TYPES = tr("Electric,Engine,Diesel,Gas Turbine,Steam,Steam-light,Steam-heavy,Steam-pass,Steam-mixed,Switcher");

 // for property change
 /*public*/ /*static*/ /*final*/ QString EngineTypes::ENGINETYPES_CHANGED_PROPERTY = "EngineTypesLength"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString EngineTypes::ENGINETYPES_NAME_CHANGED_PROPERTY = "EngineTypesName"; // NOI18N

 /*public*/ EngineTypes::EngineTypes(QObject *parent) :
RollingStockAttribute(parent) {
  log = new Logger("EngineTypes");
  setProperty("InstanceManagerAutoDefault", "yes");

 }

 /*protected*/ QString EngineTypes::getDefaultNames() {
     return TYPES;
 }

 /*public*/ void EngineTypes::addName(QString type) {
     RollingStockAttribute::addName(type);
     setDirtyAndFirePropertyChange(ENGINETYPES_CHANGED_PROPERTY, QVariant(), type);
 }

 /*public*/ void EngineTypes::deleteName(QString type) {
     RollingStockAttribute::deleteName(type);
     setDirtyAndFirePropertyChange(ENGINETYPES_CHANGED_PROPERTY, type, QVariant());
 }

 /*public*/ void EngineTypes::replaceName(QString oldName, QString newName) {
     RollingStockAttribute::addName(newName);
     setDirtyAndFirePropertyChange(ENGINETYPES_NAME_CHANGED_PROPERTY, oldName, newName);
     // need to keep old name so location manager can replace properly
     RollingStockAttribute::deleteName(oldName);
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-engines.dtd.
  *
  */
 /*public*/ void EngineTypes::store(QDomElement root, QDomDocument doc) {
     RollingStockAttribute::store(root, Xml::TYPES, Xml::TYPE, Xml::ENGINE_TYPES, doc);
 }

 /*public*/ void EngineTypes::load(QDomElement root) {
     RollingStockAttribute::load(root, Xml::TYPES, Xml::TYPE, Xml::ENGINE_TYPES);
 }

 /*protected*/ void EngineTypes::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // Set dirty
     ((Operations::EngineManagerXml*)InstanceManager::getDefault("EngineManagerXml"))->setDirty(true);
     RollingStockAttribute::firePropertyChange(p, old, n);
 }
}
