#include "enginelengths.h"
#include "xml.h"
#include "logger.h"
#include "control.h"
#include "enginemanagerxml.h"
#include "instancemanager.h"

//EngineLengths::EngineLengths()
//{

//}
namespace Operations
{
/**
 * Represents the lengths that engines can have.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class EngineLengths extends RollingStockAttribute {

 /*private*/ /*static*/ /*final*/ QString EngineLengths::LENGTHS = tr("20,30,40,50,60,70,80");
 /*public*/ /*static*/ /*final*/ QString EngineLengths::ENGINELENGTHS_CHANGED_PROPERTY = "EngineLengths"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString EngineLengths::ENGINELENGTHS_NAME_CHANGED_PROPERTY = "EngineLengthsName"; // NOI18N

 /*public*/ EngineLengths::EngineLengths(QObject* parent) : RollingStockAttribute(parent)
 {
 setProperty("InstanceManagerAutoDefault", "yes");

 }

 /*protected*/ QString EngineLengths::getDefaultNames() {
     return LENGTHS;
 }

 // override, need to perform a number sort
 /*public*/ void EngineLengths::setNames(QStringList lengths) {
     setValues(lengths);
 }

 /*public*/ void EngineLengths::addName(QString length) {
     RollingStockAttribute::addName(length);
     setDirtyAndFirePropertyChange(ENGINELENGTHS_CHANGED_PROPERTY, QVariant(), length);
 }

 /*public*/ void EngineLengths::deleteName(QString length) {
     RollingStockAttribute::deleteName(length);
     setDirtyAndFirePropertyChange(ENGINELENGTHS_CHANGED_PROPERTY, length, QVariant());
 }

 /*public*/ void EngineLengths::replaceName(QString oldName, QString newName) {
     RollingStockAttribute::addName(newName);
     setDirtyAndFirePropertyChange(ENGINELENGTHS_NAME_CHANGED_PROPERTY, oldName, newName);
     // need to keep old name so location manager can replace properly
     RollingStockAttribute::deleteName(oldName);
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-engines.dtd.
  *
  */
 /*public*/ void EngineLengths::store(QDomElement root, QDomDocument doc) {
     RollingStockAttribute::store(root, Xml::LENGTHS, Xml::LENGTH, Xml::ENGINE_LENGTHS, doc);
 }

 /*public*/ void EngineLengths::load(QDomElement root) {
     RollingStockAttribute::load(root, Xml::LENGTHS, Xml::LENGTH, Xml::ENGINE_LENGTHS);
 }

 /*protected*/ void EngineLengths::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // Set dirty
     ((EngineManagerXml*)InstanceManager::getDefault("EngineManagerXml"))->setDirty(true);
     RollingStockAttribute::firePropertyChange(p, old, n);
 }

 //@Override
    /*public*/ void EngineLengths::initialize() {
        InstanceManager::getDefault("OperationsSetupXml"); // load setup
        // create manager to load engines and their attributes
        InstanceManager::getDefault("EngineManagerXml");
    }

}
