#include "divisionmanager.h"
#include "division.h"
#include "vptr.h"
#include "loggerfactory.h"
#include "xml.h"
#include "locationmanagerxml.h"
#include "instancemanager.h"

namespace Operations {

 /**
  * Manages divisions.
  *
  * @author Bob Jacobsen Copyright (C) 2003
  * @author Daniel Boudreau Copyright (C) 2021
  */
 ///*public*/  class DivisionManager extends SwingPropertyChangeSupport implements InstanceManagerAutoDefault, InstanceManagerAutoInitialize {

     /*public*/  /*static*/ /*final*/ QString DivisionManager::LISTLENGTH_CHANGED_PROPERTY = "divisionsListLength"; // NOI18N

     /*public*/  DivisionManager::DivisionManager(QObject* parent): SwingPropertyChangeSupport(this, parent){
     }


     /*public*/  void DivisionManager::dispose() {
         _divisionHashTable.clear();
         _id = 0;
     }

     /**
      * @return Number of divisions
      */
     /*public*/  int DivisionManager::getNumberOfdivisions() {
         return _divisionHashTable.size();
     }

     /**
      * @param name The string name of the Division to get.
      * @return requested Division object or null if none exists
      */
     /*public*/  Division* DivisionManager::getDivisionByName(QString name) {
         Division* division;
         //Enumeration<Division> en = _divisionHashTable.elements();
         QListIterator<Division*> en (_divisionHashTable.values());
         while (en.hasNext()) {
             division = en.next();
             if (division->getName() == (name)) {
                 return division;
             }
         }
         return nullptr;
     }

     /*public*/  Division* DivisionManager::getDivisionById(QString id) {
         return _divisionHashTable.value(id);
     }

     /**
      * Finds an existing Division or creates a new Division if needed requires
      * Division's name creates a unique id for this Division
      *
      * @param name The string name for a new Division.
      *
      *
      * @return new Division or existing Division
      */
     /*public*/  Division* DivisionManager::newDivision(QString name) {
         Division* division = getDivisionByName(name);
         if (division == nullptr) {
             _id++;
             division = new Division(QString::number(_id), name);
             int oldSize = _divisionHashTable.size();
             _divisionHashTable.insert(division->getId(), division);
             setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize,
                     (_divisionHashTable.size()));
         }
         return division;
     }

     /**
      * Remember a NamedBean Object created outside the manager.
      *
      * @param division The Division to add.
      */
     /*public*/  void DivisionManager::_register(Division* division) {
         int oldSize = (_divisionHashTable.size());
         _divisionHashTable.insert(division->getId(), division);
         // find last id created
         int id = division->getId().toInt();
         if (id > _id) {
             _id = id;
         }
         setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_divisionHashTable.size()));
     }

     /**
      * Forget a NamedBean Object created outside the manager.
      *
      * @param division The Division to delete.
      */
     /*public*/  void DivisionManager::deregister(Division* division) {
         if (division == nullptr) {
             return;
         }
         int oldSize = (_divisionHashTable.size());
         _divisionHashTable.remove(division->getId());
         setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_divisionHashTable.size()));
     }

     /**
      * Sort by Division name
      *
      * @return list of divisions ordered by name
      */
     /*public*/  QList<Division*> DivisionManager::getDivisionsByNameList() {
         // first get id list
         QList<Division*> sortList = getList();
         // now re-sort
         QList<Division*> out = QList<Division*>();
         for (Division* division : sortList) {
             for (int j = 0; j < out.size(); j++) {
                 if (division->getName().compare(out.value(j)->getName()) < 0) {
                     out.insert(j, division);
                     break;
                 }
             }
             if (!out.contains(division)) {
                 out.append(division);
             }
         }
         return out;

     }

     /**
      * Sort by Division id
      *
      * @return list of divisions ordered by id numbers
      */
     /*public*/  QList<Division*> DivisionManager::getDivisionsByIdList() {
         QList<Division*> sortList = getList();
         // now re-sort
         QList<Division*> out = QList<Division*>();
         for (Division* division : sortList) {
             for (int j = 0; j < out.size(); j++) {
                 try {
                     if (division->getId().toInt() < out.value(j)->getId()) {
                         out.insert(j, division);
                         break;
                     }
                 } catch (NumberFormatException e) {
                     log->debug("list id number isn't a number");
                 }
             }
             if (!out.contains(division)) {
                 out.append(division);
             }
         }
         return out;
     }

     /**
      * Gets an unsorted list of all divisions.
      *
      * @return All divisions.
      */
     /*public*/  QList<Division*> DivisionManager::getList() {
         QList<Division*> out = QList<Division*>();
         QListIterator<Division*> en (_divisionHashTable.values());
         while (en.hasNext()) {
             out.append(en.next());
         }
         return out;
     }

     /**
      *
      * @return ComboBox with divisions for this railroad
      */
     /*public*/  JComboBox/*<Division>*/* DivisionManager::getComboBox() {
         JComboBox/*<Division>*/* box = new JComboBox();
         updateComboBox(box);
         return box;
     }

     /*public*/  void DivisionManager::updateComboBox(JComboBox/*<Division>*/* box) {
         box->clear();
         box->addItem("");
         for (Division* division : getDivisionsByNameList()) {
             box->addItem(division->getName(),VPtr<Division>::asQVariant(division));
         }
     }

     /*public*/  void DivisionManager::load(QDomElement root) {
         if (!root.firstChildElement(Xml::DIVISIONS).isNull()) {
             QDomNodeList divisions = root.firstChildElement(Xml::DIVISIONS).elementsByTagName(Xml::DIVISION);
             log->debug(tr("readFile sees %1 divisions").arg(divisions.size()));
             for (int i = 0; i< divisions.count(); i++) {
              QDomElement division = divisions.at(i).toElement();
                 _register(new Division(division));
             }
         }
     }

     /*public*/  void DivisionManager::store(QDomElement root, QDomDocument doc) {
         QDomElement values;
         root.appendChild(values = doc.createElement(Xml::DIVISIONS));
         // add entries
         QList<Division*> divisionList = getDivisionsByNameList();
         for (Division* division : divisionList) {
             values.appendChild(division->store(doc));
         }
     }

     /*protected*/ void DivisionManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
         // set dirty
         ((LocationManagerXml*)InstanceManager::getDefault("Operations::LocationManagerXml"))->setDirty(true);
         firePropertyChange(p, old, n);
     }

     /*private*/ /*final*/ /*static*/ Logger* DivisionManager::log = LoggerFactory::getLogger("DivisionManager");

     //@Override
     /*public*/  void DivisionManager::initialize() {
         // do nothing
     }
} // namespace Operations
