#include "carcolors.h"
#include "carmanagerxml.h"
#include "xml.h"
#include "control.h"

namespace Operations
{
/**
 * Represents the colors that cars can have.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class CarColors extends RollingStockAttribute {

 /*private*/ /*static*/ /*final*/ QString CarColors::COLORS = tr("Black,Blue,Brown,Gray,Yellow,Green,Orange,Purple,Red,Silver,Tuscan,White");
 /*public*/ /*static*/ /*final*/ QString CarColors::CARCOLORS_CHANGED_PROPERTY = "CarColors"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString CarColors::CARCOLORS_NAME_CHANGED_PROPERTY = "CarColorsName"; // NOI18N

 /*public*/ CarColors::CarColors(QObject* parent) :RollingStockAttribute(parent)
 {
 setProperty("InstanceManagerAutoDefault", "yes");

 }

 /**
  * record the single instance *
  */
 /*private*/ /*static*/ CarColors* CarColors::_instance = NULL;

 /*public*/ /*static*/ /*synchronized*/ CarColors* CarColors::instance() {
  Logger* log = new Logger("CarColors");
     if (_instance == NULL) {
         if (log->isDebugEnabled()) {
             log->debug("CarColors creating instance");
         }
         // create and load
         _instance = new CarColors();
     }
     if (Control::showInstance) {
         log->debug(tr("CarColors returns instance %1").arg(_instance->metaObject()->className()));
     }
     return _instance;
 }

 /*protected*/ QString CarColors::getDefaultNames() {
     return COLORS;
 }

 /*public*/ void CarColors::addName(QString color) {
     RollingStockAttribute::addName(color);
     setDirtyAndFirePropertyChange(CARCOLORS_CHANGED_PROPERTY, QVariant(), color);
 }

 /*public*/ void CarColors::deleteName(QString color) {
     RollingStockAttribute::deleteName(color);
     setDirtyAndFirePropertyChange(CARCOLORS_CHANGED_PROPERTY, color, QVariant());
 }

 /*public*/ void CarColors::replaceName(QString oldName, QString newName) {
     RollingStockAttribute::addName(newName);
     setDirtyAndFirePropertyChange(CARCOLORS_NAME_CHANGED_PROPERTY, oldName, newName);
     // need to keep old name so location manager can replace properly
     RollingStockAttribute::deleteName(oldName);
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-cars.dtd.
  *
  */
 /*public*/ void CarColors::store(QDomElement root, QDomDocument doc) {
     RollingStockAttribute::store(root, Xml::COLORS, Xml::COLOR, Xml::CAR_COLORS, doc);
 }

 /*public*/ void CarColors::load(QDomElement root) {
     RollingStockAttribute::load(root, Xml::COLORS, Xml::COLOR, Xml::CAR_COLORS);
 }

 /*protected*/ void CarColors::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // Set dirty
     CarManagerXml::instance()->setDirty(true);
     RollingStockAttribute::firePropertyChange(p, old, n);
 }
}
