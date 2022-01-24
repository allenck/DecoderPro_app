#include "consistmanager.h"
#include "loggerfactory.h"
#include "consist.h"
#include "engine.h"
#include "xml.h"
#include "enginemanagerxml.h"
#include "instancemanager.h"

namespace Operations {

 /**
  * Manages Consists.
  *
  * @author Daniel Boudreau Copyright (C) 2021
  */
 // /*public*/  class ConsistManager extends RollingStockGroupManager implements InstanceManagerAutoDefault {
 
     /*public*/  ConsistManager::ConsistManager(QObject* parent) : RollingStockGroupManager(parent){
     }
 
     /**
      * Create a new Consist
      *
      * @param name string name for this Consist
      *
      * @return Consist
      */
     /*public*/  Consist* ConsistManager::newConsist(QString name) {
         Consist* consist = getConsistByName(name);
         if (consist == nullptr && name != (NONE)) {
             consist = new Consist(name);
             int oldSize = _groupHashTable.size();
             _groupHashTable.insert(name, consist);
             setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, _groupHashTable
                     .size());
         }
         return consist;
     }
 
     /**
      * Delete a Consist by name
      *
      * @param name string name for the Consist
      *
      */
     /*public*/  void ConsistManager::deleteConsist(QString name) {
         Consist* consist = getConsistByName(name);
         if (consist != nullptr) {
             consist->dispose();
             int oldSize = (_groupHashTable.size());
             _groupHashTable.remove(name);
             setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_groupHashTable.size()));
         }
     }
 
     /**
      * Get a Consist by name
      *
      * @param name string name for the Consist
      *
      * @return named Consist
      */
     /*public*/  Consist* ConsistManager::getConsistByName(QString name) {
         return (Consist*) _groupHashTable.value(name);
     }
 
     /*public*/  void ConsistManager::replaceConsistName(QString oldName, QString newName) {
         Consist* oldConsist = getConsistByName(oldName);
         if (oldConsist != nullptr) {
             Consist* _newConsist = newConsist(newName);
             // keep the lead engine
             Engine* leadEngine = (Engine*)oldConsist->getLead();
             if (leadEngine != nullptr) {
                 leadEngine->setConsist(_newConsist);
             }
             for (Engine* engine : oldConsist->getEngines()) {
                 engine->setConsist(_newConsist);
             }
         }
     }
  
     /*public*/  void ConsistManager::load(QDomElement root) {
         // new format using elements starting version 3.3.1
         if (root.firstChildElement(Xml::NEW_CONSISTS) != QDomElement()) {
             QDomNodeList eConsists = root.firstChildElement(Xml::NEW_CONSISTS).elementsByTagName(Xml::CONSIST);
             log->debug(tr("Consist manager sees %1 consists").arg(eConsists.size()));
             QString a;
             for (int i=0; i <  eConsists.size(); i++) {
              QDomElement eConsist = eConsists.at(i).toElement();
                 if ((a = eConsist.attribute(Xml::NAME)) != "") {
                     newConsist(a);
                 }
             }
         } // old format
         else if (root.firstChildElement(Xml::CONSISTS) != QDomElement()) {
             QString names = root.firstChildElement(Xml::CONSISTS).text();
             if (!names.isEmpty()) {
                 QStringList consistNames = names.split("%%"); // NOI18N
                 log->debug(tr("consists: %1").arg(names));
                 for (QString name : consistNames) {
                     newConsist(name);
                 }
             }
         }
     }
 
     /**
      * Create an XML element to represent this Entry. This member has to remain
      * synchronized with the detailed DTD in operations-engines.dtd.
      *
      * @param root The common Element for operations-engines.dtd.
      */
     /*public*/  void ConsistManager::store(QDomElement root, QDomDocument doc) {
         QList<QString> names = getNameList();
         QDomElement consists = doc.createElement(Xml::NEW_CONSISTS);
         for (QString name : names) {
             QDomElement consist = doc.createElement(Xml::CONSIST);
             consist.setAttribute(Xml::NAME, name);
             consists.appendChild(consist);
         }
         root.appendChild(consists);
     }
 
     /*protected*/ void ConsistManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
         // Set dirty
         ((EngineManagerXml*)InstanceManager::getDefault("EngineManagerXml"))->setDirty(true);
         RollingStockGroupManager::firePropertyChange(p, old, n);
     }
 
     /*private*/ /*final*/ /*static*/ Logger* ConsistManager::log = LoggerFactory::getLogger("ConsistManager");

} // namespace Operations
