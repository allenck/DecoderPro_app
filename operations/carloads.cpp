#include "carloads.h"
#include "logger.h"
#include "control.h"
#include "carload.h"
#include "xml.h"
#include "carmanagerxml.h"
#include "cartypes.h"
#include "stringutil.h"

//CarLoads::CarLoads()
//{

//}
namespace Operations
{
/**
 * Represents the loads that cars can have.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class CarLoads extends RollingStockAttribute {


 /*public*/ /*static*/ /*final*/ QString CarLoads::NONE = ""; // NOI18N

 // for property change
 /*public*/ /*static*/ /*final*/ QString CarLoads::LOAD_CHANGED_PROPERTY = "CarLoads_Load"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString CarLoads::LOAD_TYPE_CHANGED_PROPERTY = "CarLoads_Load_Type"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString CarLoads::LOAD_PRIORITY_CHANGED_PROPERTY = "CarLoads_Load_Priority"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString CarLoads::LOAD_NAME_CHANGED_PROPERTY = "CarLoads_Name"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString CarLoads::LOAD_COMMENT_CHANGED_PROPERTY = "CarLoads_Load_Comment"; // NOI18N

 /*public*/ CarLoads::CarLoads(QObject* parent)
      : RollingStockAttribute(parent)
 {
  list = new QHash<QString, QList<CarLoad*>*>();
  _emptyName = tr("E");
  _loadName = tr("L");
  log = new Logger("CarLoads");
  setProperty("InstanceManagerAutoDefault", "yes");

 }

/**
 * record the single instance *
 */
/*private*/ /*static*/ CarLoads* CarLoads::_instance = NULL;

 /*public*/ /*static*/ /*synchronized*/ CarLoads* CarLoads::instance()
{
 Logger* log = new Logger("");
 if (_instance == NULL)
 {
  if (log->isDebugEnabled()) {
      log->debug("CarLoads creating instance");
  }
  // create and load
  _instance = new CarLoads();
 }
 if (Control::showInstance)
 {
  log->debug(tr("CarLoads returns instance %1").arg(_instance->metaObject()->className()));
 }
 return _instance;
 }

 /**
  * Add a car type with specific loads
  *
  * @param type car type
  */
 /*public*/ void CarLoads::addType(QString type) {
     list->insert(type, new QList<CarLoad*>());
 }

 /**
  * Replace a car type. Transfers load priority, drop and load comments.
  *
  * @param oldType old car type
  * @param newType new car type
  */
 /*public*/ void CarLoads::replaceType(QString oldType, QString newType) {
     QStringList names = getNames(oldType);
     addType(newType);
     foreach (QString name, names) {
         addName(newType, name);
         setPriority(newType, name, getPriority(oldType, name));
         setDropComment(newType, name, getDropComment(oldType, name));
         setPickupComment(newType, name, getPickupComment(oldType, name));
     }
     list->remove(oldType);
 }

 /**
  * Gets the appropriate car loads for the car's type.
  *
  * @param type
  * @return JComboBox with car loads starting with empty string.
  */
 /*public*/ JComboBox* CarLoads::getSelectComboBox(QString type) {
     JComboBox* box = new JComboBox();
     box->addItem(NONE);
     foreach (QString load, getNames(type)) {
         box->addItem(load);
     }
     return box;
 }

 /**
  * Gets the appropriate car loads for the car's type.
  *
  * @param type
  * @return JComboBox with car loads.
  */
 /*public*/ JComboBox* CarLoads::getComboBox(QString type) {
     JComboBox* box = new JComboBox();
     updateComboBox(type, box);
     return box;

 }

 /**
  * Gets a combobox with the available priorities
  *
  * @return JComboBox with car priorities.
  */
 /*public*/ JComboBox* CarLoads::getPriorityComboBox() {
     JComboBox* box = new JComboBox();
     box->addItem(CarLoad::PRIORITY_LOW);
     box->addItem(CarLoad::PRIORITY_HIGH);
     return box;
 }

 /**
  * Gets a combobox with the available load types: empty and load
  *
  * @return JComboBox with load types: LOAD_TYPE_EMPTY and LOAD_TYPE_LOAD
  */
 /*public*/ JComboBox* CarLoads::getLoadTypesComboBox() {
     JComboBox*box = new JComboBox();
     box->addItem(CarLoad::LOAD_TYPE_EMPTY);
     box->addItem(CarLoad::LOAD_TYPE_LOAD);
     return box;
 }

 /**
  * Gets the load names for a given car type
  *
  * @param type car type
  * @return list of load names
  */
 /*public*/ QStringList CarLoads::getNames(QString type)
 {
  QStringList names =  QStringList();
  if (type == NULL)
  {
   names.append(getDefaultEmptyName());
   names.append(getDefaultLoadName());
   return names;
  }
  QList<CarLoad*>* loads = list->value(type);
  if (loads == NULL)
  {
   addType(type);
   loads = list->value(type);
  }
  if (loads->size() == 0)
  {
   loads->append(new CarLoad(getDefaultEmptyName()));
   loads->append(new CarLoad(getDefaultLoadName()));
  }
  foreach (CarLoad* carLoad, *loads)
  {
   names.append(carLoad->getName());
  }
  return names;
 }

 /**
  * Add a load name for the car type.
  *
  * @param type car type.
  * @param name load name.
  */
 /*public*/ void CarLoads::addName(QString type, QString name) {
     // don't add if name already exists
     if (containsName(type, name)) {
         return;
     }
     QList<CarLoad*>* loads = list->value(type);
     if (loads == NULL) {
         log->debug(tr("car type (%1) does not exist").arg(type));
         return;
     }
     loads->insert(0, new CarLoad(name));
     maxNameLength = 0; // reset maximum name length
     setDirtyAndFirePropertyChange(LOAD_CHANGED_PROPERTY, QVariant(), name);
 }

 /*public*/ void CarLoads::deleteName(QString type, QString name) {
     QList<CarLoad*>* loads = list->value(type);
     if (loads->isEmpty()) {
         log->debug(tr("car type (%1) does not exist").arg(type));
         return;
     }
     foreach (CarLoad* cl, *loads) {
         if (cl->getName()==(name)) {
             loads->removeOne(cl);
             break;
         }
     }
     maxNameLength = 0; // reset maximum name length
     setDirtyAndFirePropertyChange(LOAD_CHANGED_PROPERTY, name, QVariant());
 }

 /**
  * Determines if a car type can have a specific load name.
  *
  * @param type car type.
  * @param name load name.
  * @return true if car can have this load name.
  */
 /*public*/ bool CarLoads::containsName(QString type, QString name) {
     QStringList names = getNames(type);
     return names.contains(name);
 }

 /*public*/ void CarLoads::updateComboBox(QString type, JComboBox* box) {
     box->clear();
     QStringList loads = getNames(type);
     foreach (QString name, loads) {
         box->addItem(name);
     }
 }

 /*public*/ void CarLoads::updateRweComboBox(QString type, JComboBox* box) {
     box->clear();
     QStringList loads = getNames(type);
     foreach (QString name, loads) {
         if (getLoadType(type, name)==(CarLoad::LOAD_TYPE_EMPTY)) {
             box->addItem(name);
         }
     }
     // must return with at least one load name
     if (box->count() == 0) {
         box->addItem(getDefaultEmptyName());
     }
 }

 /*public*/ void CarLoads::replaceName(QString type, QString oldName, QString newName) {
     addName(type, newName);
     deleteName(type, oldName);
     setDirtyAndFirePropertyChange(LOAD_NAME_CHANGED_PROPERTY, oldName, newName);
 }

 /*public*/ QString CarLoads::getDefaultLoadName() {
     return _loadName;
 }

 /*public*/ void CarLoads::setDefaultLoadName(QString name) {
     QString old = _loadName;
     _loadName = name;
     setDirtyAndFirePropertyChange(LOAD_NAME_CHANGED_PROPERTY, old, name);
 }

 /*public*/ QString CarLoads::getDefaultEmptyName() {
     return _emptyName;
 }

 /*public*/ void CarLoads::setDefaultEmptyName(QString name) {
     QString old = _emptyName;
     _emptyName = name;
     setDirtyAndFirePropertyChange(LOAD_NAME_CHANGED_PROPERTY, old, name);
 }

 /**
  * Sets the load type, empty or load.
  *
  * @param type     car type.
  * @param name     load name.
  * @param loadType load type: LOAD_TYPE_EMPTY or LOAD_TYPE_LOAD.
  */
 /*public*/ void CarLoads::setLoadType(QString type, QString name, QString loadType)
 {
  QList<CarLoad*>* loads = list->value(type);
  foreach (CarLoad* cl, *loads)
  {
   if (cl->getName()==(name))
   {
    QString oldType = cl->getLoadType();
    cl->setLoadType(loadType);
    if (oldType!=(loadType))
    {
     setDirtyAndFirePropertyChange(LOAD_TYPE_CHANGED_PROPERTY, oldType, loadType);
    }
   }
  }
 }

 /**
  * Get's the load type, empty or load.
  *
  * @param type car type.
  * @param name load name.
  * @return load type, LOAD_TYPE_EMPTY or LOAD_TYPE_LOAD.
  */
 /*public*/ QString CarLoads::getLoadType(QString type, QString name) {
     if (!containsName(type, name)) {
         if (name != NULL && name==(getDefaultEmptyName())) {
             return CarLoad::LOAD_TYPE_EMPTY;
         }
         return CarLoad::LOAD_TYPE_LOAD;
     }
     QList<CarLoad*>* loads = list->value(type);
     foreach (CarLoad* cl, *loads) {
         if (cl->getName()==(name)) {
             return cl->getLoadType();
         }
     }
     return "error"; // NOI18N
 }

 /**
  * Sets a loads priority.
  *
  * @param type     car type.
  * @param name     load name.
  * @param priority load priority, PRIORITY_LOW or PRIORITY_HIGH.
  */
 /*public*/ void CarLoads::setPriority(QString type, QString name, QString priority) {
     QList<CarLoad*>* loads = list->value(type);
     foreach (CarLoad* cl, *loads) {
         if (cl->getName()==(name)) {
             QString oldPriority = cl->getPriority();
             cl->setPriority(priority);
             if (oldPriority!=(priority)) {
                 setDirtyAndFirePropertyChange(LOAD_PRIORITY_CHANGED_PROPERTY, oldPriority, priority);
             }
         }
     }
 }

 /**
  * Get's a load's priority.
  *
  * @param type car type.
  * @param name load name.
  * @return load priority, PRIORITY_LOW or PRIORITY_HIGH.
  */
 /*public*/ QString CarLoads::getPriority(QString type, QString name)
{
  if (!containsName(type, name)) {
      return CarLoad::PRIORITY_LOW;
  }
  QList<CarLoad*>* loads = list->value(type);
  if(loads == NULL)
   return "error";
  foreach (CarLoad* cl, *loads)
  {
      if (cl->getName()==(name))
      {
          return cl->getPriority();
      }
  }
  return "error"; // NOI18N
 }

 /*public*/ void CarLoads::setPickupComment(QString type, QString name, QString comment) {
     if (!containsName(type, name)) {
         return;
     }
     QList<CarLoad*>* loads = list->value(type);
     foreach (CarLoad* cl, *loads) {
         if (cl->getName()==(name)) {
             QString oldComment = cl->getPickupComment();
             cl->setPickupComment(comment);
             if (oldComment!=(comment)) {
                 setDirtyAndFirePropertyChange(LOAD_COMMENT_CHANGED_PROPERTY, oldComment, comment);
             }
         }
     }
 }

 /*public*/ QString CarLoads::getPickupComment(QString type, QString name) {
     if (!containsName(type, name)) {
         return NONE;
     }
     QList<CarLoad*>* loads = list->value(type);
     foreach (CarLoad* cl, *loads) {
         if (cl->getName()==(name)) {
             return cl->getPickupComment();
         }
     }
     return NONE;
 }

 /*public*/ void CarLoads::setDropComment(QString type, QString name, QString comment) {
     if (!containsName(type, name)) {
         return;
     }
     QList<CarLoad*>* loads = list->value(type);
     foreach (CarLoad* cl, *loads) {
         if (cl->getName()==(name)) {
             QString oldComment = cl->getDropComment();
             cl->setDropComment(comment);
             if (oldComment!=(comment)) {
                 setDirtyAndFirePropertyChange(LOAD_COMMENT_CHANGED_PROPERTY, oldComment, comment);
             }
         }
     }
 }

 /*public*/ QString CarLoads::getDropComment(QString type, QString name) {
     if (!containsName(type, name)) {
         return NONE;
     }
     QList<CarLoad*>* loads = list->value(type);
     foreach (CarLoad* cl, *loads) {
         if (cl->getName()==(name)) {
             return cl->getDropComment();
         }
     }
     return NONE;
 }
#if 0
 /*public*/ int getMaxNameLength() {
     if (maxNameLength == 0) {
         maxNameLength = MIN_NAME_LENGTH;
         Enumeration<String> en = list.keys();
         while (en.hasMoreElements()) {
             String key = en.nextElement();
             List<CarLoad> loads = list.get(key);
             for (CarLoad load : loads) {
                 if (load.getName().length() > maxNameLength) {
                     maxNameLength = load.getName().length();
                 }
             }
         }
     }
     return maxNameLength;
 }
#endif
 /*private*/ QList<CarLoad*>* CarLoads::getSortedList(QString type) {
     QList<CarLoad*>* loads = list->value(type);
     QList<CarLoad*>* out = new QList<CarLoad*>();

     // Sort load names
     QVector<QString> loadNames = QVector<QString>(loads->size());
     for (int i = 0; i < loads->size(); i++) {
         loadNames.replace(i, loads->at(i)->getName());
     }
     StringUtil::sort(loadNames.toList());
     // return a list sorted by load name
     for (int i = loadNames.size() - 1; i >= 0; i--) {
         for (int j = 0; j < loads->size(); j++) {
             if (loadNames[i]==(loads->at(j)->getName())) {
                 out->append(loads->at(j));
                 break;
             }
         }
     }
     return out;
 }

 //@SuppressWarnings("unchecked")
 /*public*/ QHash<QString, QList<CarLoad*>*>* CarLoads::getList() {
     //return (QHash<QString, QList<CarLoad*>*>) list->clone();
  QHash<QString, QList<CarLoad*>*>* out = new QHash<QString, QList<CarLoad*>*>();
  QHashIterator<QString, QList<CarLoad*>*> iter(*list);
  while (iter.hasNext())
  {
   out->insert(iter.key(), iter.value());
  }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-cars.dtd.
  *
  */
 /*public*/ void CarLoads::store(QDomElement root, QDomDocument doc)
 {
  QDomElement values = doc.createElement(Xml::LOADS);
//  QDomElement values = QDomElement();
//  values.setTagName(Xml::LOADS);

  // store default load and empty
  QDomElement defaults = doc.createElement(Xml::DEFAULTS);
//  QDomElement defaults = QDomElement();
//  defaults.setTagName(Xml::DEFAULTS);
  defaults.setAttribute(Xml::EMPTY, getDefaultEmptyName());
  defaults.setAttribute(Xml::LOAD, getDefaultLoadName());
  values.appendChild(defaults);
  // store loads based on car types
  QStringListIterator en(list->keys());
  while (en.hasNext()) {
      QString carType = en.next();
      // check to see if car type still exists
      if (!CarTypes::instance()->containsName(carType)) {
          continue;
      }
      QList<CarLoad*>* loads = getSortedList(carType);
      QDomElement xmlLoad = doc.createElement(Xml::LOAD);
//      QDomElement xmlLoad = QDomElement();
//      xmlLoad.setTagName(Xml::LOAD);
      xmlLoad.setAttribute(Xml::TYPE, carType);
      bool mustStore = false;  // only store loads that aren't the defaults
      foreach (CarLoad* load, *loads) {
          // don't store the defaults / low priority / no comment
          if ((load->getName()==(getDefaultEmptyName()) || load->getName()==(getDefaultLoadName()))
                  && load->getPriority()==(CarLoad::PRIORITY_LOW)
                  && load->getPickupComment()==(CarLoad::NONE)
                  && load->getDropComment()==(CarLoad::NONE))
              continue;
          QDomElement xmlCarLoad = doc.createElement(Xml::CAR_LOAD);
//          QDomElement xmlCarLoad = QDomElement();
//          xmlCarLoad.setTagName(Xml::CAR_LOAD);
          xmlCarLoad.setAttribute(Xml::NAME, load->getName());
          if (load->getPriority()!=(CarLoad::PRIORITY_LOW)) {
              xmlCarLoad.setAttribute(Xml::PRIORITY, load->getPriority());
              mustStore = true; // must store
          }
          if (load->getPickupComment()!=(CarLoad::NONE)) {
              xmlCarLoad.setAttribute(Xml::PICKUP_COMMENT, load->getPickupComment());
              mustStore = true; // must store
          }
          if (load->getDropComment()!=(CarLoad::NONE)) {
              xmlCarLoad.setAttribute(Xml::DROP_COMMENT, load->getDropComment());
              mustStore = true; // must store
          }
          xmlCarLoad.setAttribute(Xml::LOAD_TYPE, load->getLoadType());
          xmlLoad.appendChild(xmlCarLoad);
      }
      if (loads->size() > 2 || mustStore) {
          values.appendChild(xmlLoad);
      }
  }
  root.appendChild(values);
 }

 /*public*/ void CarLoads::load(QDomElement e) {
     if (e.firstChildElement(Xml::LOADS) == QDomElement()) {
         return;
     }
     QString a;
     QDomElement defaults = e.firstChildElement(Xml::LOADS).firstChildElement(Xml::DEFAULTS);
     if (defaults != QDomElement())
     {
      if ((a = defaults.attribute(Xml::LOAD)) != "")
      {
       _loadName = a;
      }
      if ((a = defaults.attribute(Xml::EMPTY)) != "")
      {
       _emptyName = a;
      }
     }
     //@SuppressWarnings("unchecked")
     QDomNodeList eLoads = e.firstChildElement(Xml::LOADS).elementsByTagName(Xml::LOAD);
     if (log->isDebugEnabled()) {
         log->debug(tr("readFile sees &1 car loads").arg(eLoads.size()));
     }
     for (int i=0; i < eLoads.size(); i++)
{
          QDomElement  eLoad = eLoads.at(i).toElement();
         if ((a = eLoad.attribute(Xml::TYPE)) != NULL) {
             QString type = a;
             addType(type);
             // old style had a list of names
             if ((a = eLoad.attribute(Xml::NAMES)) != NULL) {
                 QString names = a;
                 QStringList loadNames = names.split("%%");// NOI18N
                 StringUtil::sort(loadNames);
                 if (log->isDebugEnabled()) {
                     log->debug(tr("Car load type: %1 loads: %2").arg(type).arg(names));
                 }
                 // addName puts new items at the start, so reverse load
                 for (int j = loadNames.length(); j > 0;) {
                     addName(type, loadNames[--j]);
                 }
             }
             // new style load and comments
             //@SuppressWarnings("unchecked")
             QDomNodeList eCarLoads = eLoad.elementsByTagName(Xml::CAR_LOAD);
             if (log->isDebugEnabled()) {
                 log->debug(tr("%1 car loads for type: %2").arg(eCarLoads.size()).arg(type));
             }
             for (int i=0; i < eCarLoads.size(); i++)
             {
              QDomElement eCarLoad = eCarLoads.at(i).toElement();
                 if ((a = eCarLoad.attribute(Xml::NAME)) != NULL) {
                     QString name = a;
                     addName(type, name);
                     if ((a = eCarLoad.attribute(Xml::PRIORITY)) != NULL) {
                         setPriority(type, name, a);
                     }
                     if ((a = eCarLoad.attribute(Xml::PICKUP_COMMENT)) != NULL) {
                         setPickupComment(type, name, a);
                     }
                     if ((a = eCarLoad.attribute(Xml::DROP_COMMENT)) != NULL) {
                         setDropComment(type, name, a);
                     }
                     if ((a = eCarLoad.attribute(Xml::LOAD_TYPE)) != NULL) {
                         setLoadType(type, name, a);
                     }
                 }
             }
         }
     }
 }

 /*protected*/ void CarLoads::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // Set dirty
     CarManagerXml::instance()->setDirty(true);
     RollingStockAttribute::firePropertyChange(p, old, n);
 }

 JComboBox* CarLoads::getComboBox()
 {
  return RollingStockAttribute::getComboBox();
 }
}
