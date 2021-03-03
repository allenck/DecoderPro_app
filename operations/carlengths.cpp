#include "carlengths.h"
#include "logger.h"
#include "control.h"
#include "xml.h"
#include <QDomElement>
#include "carmanagerxml.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Represents the lengths that cars can have.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class CarLengths extends RollingStockAttribute {

 /*private*/ /*static*/ /*final*/ QString CarLengths::LENGTHS = tr("32,34,36,38,40,42,50,51,52,54,60,70");
 /*public*/ /*static*/ /*final*/ QString CarLengths::CARLENGTHS_CHANGED_PROPERTY = "CarLengths"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString CarLengths::CARLENGTHS_NAME_CHANGED_PROPERTY = "CarLengthsName"; // NOI18N

 /*public*/ CarLengths::CarLengths(QObject* parent) : RollingStockAttribute(parent)
 {
 setProperty("InstanceManagerAutoDefault", "yes");

 }

 /**
  * record the single instance *
  */
 /*private*/ /*static*/ CarLengths* CarLengths::_instance = NULL;

 /*public*/ /*static*/ /*synchronized*/ CarLengths* CarLengths::instance()
{
 Logger* log = new Logger("CarLengths");
     if (_instance == NULL)
     {
         if (log->isDebugEnabled()) {
             log->debug("CarLengths creating instance");
         }
         // create and load
         _instance = new CarLengths();
     }
     if (Control::showInstance) {
         log->debug(tr("CarLengths returns instance %1").arg(_instance->metaObject()->className()));
     }
     return _instance;
 }

 /*protected*/ QString CarLengths::getDefaultNames() {
     return LENGTHS;
 }

 // override, need to perform a number sort
 /*public*/ void CarLengths::setNames(QStringList lengths) {
     setValues(lengths);
 }

 /*public*/ void CarLengths::addName(QString length) {
     RollingStockAttribute::addName(length);
     setDirtyAndFirePropertyChange(CARLENGTHS_CHANGED_PROPERTY, QVariant(), length);
 }

 /*public*/ void CarLengths::deleteName(QString length) {
     RollingStockAttribute::deleteName(length);
     setDirtyAndFirePropertyChange(CARLENGTHS_CHANGED_PROPERTY, length, QVariant());
 }

 /*public*/ void CarLengths::replaceName(QString oldName, QString newName) {
     RollingStockAttribute::addName(newName);
     setDirtyAndFirePropertyChange(CARLENGTHS_NAME_CHANGED_PROPERTY, oldName, newName);
     // need to keep old name so location manager can replace properly
     RollingStockAttribute::deleteName(oldName);
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-cars.dtd.
  *
  */
 /*public*/ void CarLengths::store(QDomElement root, QDomDocument doc) {
     RollingStockAttribute::store(root, Xml::LENGTHS, Xml::LENGTH, Xml::CAR_LENGTHS, doc);
 }

 /*public*/ void CarLengths::load(QDomElement root) {
     RollingStockAttribute::load(root, Xml::LENGTHS, Xml::LENGTH, Xml::CAR_LENGTHS);
 }

 /*protected*/ void CarLengths::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // Set dirty
     ((CarManagerXml*)InstanceManager::getDefault("CarManagerXml"))->setDirty(true);
     RollingStockAttribute::firePropertyChange(p, old, n);
 }
}
