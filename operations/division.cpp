#include "division.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "xml.h"
#include "operationsxml.h"
#include "locationmanagerxml.h"

namespace Operations {

 /**
  * Represents a railroad division
  *
  * @author Daniel Boudreau Copyright (C) 2021
  */
  // /*public*/ class Division extends PropertyChangeSupport implements Identifiable {

      /*public*/ /*static*/ /*final*/ QString Division::NONE = "";


      /*public*/ /*static*/ /*final*/ QString Division::NAME_CHANGED_PROPERTY = "divisionName"; // NOI18N

      /*public*/ Division::Division(QString id, QString name, QObject* parent) : PropertyChangeSupport(parent){
         log->debug(tr("New division (%1) id: %2").arg(name, id));
         _name = name;
         _id = id;
     }

     //@Override
      /*public*/ QString Division::getId() {
         return _id;
     }

     /**
      * Sets the division's name.
      *
      * @param name The string name for this division.
      *
      */
      /*public*/ void Division::setName(QString name) {
         QString old = _name;
         _name = name;
         if (old != (name)) {
             setDirtyAndFirePropertyChange(NAME_CHANGED_PROPERTY, old, name);
         }
     }

     // for combo boxes
     //@Override
      /*public*/ QString Division::toString() {
         return _name;
     }

      /*public*/ QString Division::getName() {
         return _name;
     }

      /*public*/ void Division::setComment(QString comment) {
         QString old = _comment;
         _comment = comment;
         if (old!=(comment)) {
             setDirtyAndFirePropertyChange("divisionComment", old, comment); // NOI18N
         }
     }

      /*public*/ QString Division::getComment() {
         return _comment;
     }

     /**
      * Construct this Entry from XML. This member has to remain synchronized with
      * the detailed DTD in operations-locations.dtd
      *
      * @param e Consist XML element
      */
     //@SuppressWarnings("deprecation") // until there's a replacement for convertFromXmlComment()
      /*public*/ Division::Division(QDomElement e) : PropertyChangeSupport(this){
         QString a;
         if ((a = e.attribute(Xml::ID)) != "") {
             _id = a;
         } else {
             log->warn("no id attribute in location element when reading operations");
         }
         if ((a = e.attribute(Xml::NAME)) != "") {
             _name = a;
         }
         if ((a = e.attribute(Xml::COMMENT)) != "") {
             _comment = OperationsXml::convertFromXmlComment(a);
         }
     }

     /**
      * Create an XML element to represent this Entry. This member has to remain
      * synchronized with the detailed DTD in operations-locations.dtd.
      *
      * @return Contents in a JDOM Element
      */
      /*public*/ QDomElement Division::store(QDomDocument doc) {
         QDomElement e = doc.createElement(Xml::DIVISION);
         e.setAttribute(Xml::ID, getId());
         e.setAttribute(Xml::NAME, getName());
         e.setAttribute(Xml::COMMENT, getComment());
         return e;
     }

     /*protected*/ void Division::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
         ((LocationManagerXml*)InstanceManager::getDefault("LocationManagerXml"))->setDirty(true);
         firePropertyChange(p, old, n);
     }

    /*private*/ /*final*/ /*static*/ Logger* Division::log = LoggerFactory::getLogger("Division");

} // namespace Operations
