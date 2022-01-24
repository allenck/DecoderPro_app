#include "engine.h"
#include "logger.h"
#include "consist.h"
#include "QtXml"
#include "xml.h"
#include "enginemodels.h"
#include "exceptions.h"
#include "enginemanager.h"
#include "enginetypes.h"
#include "enginemanagerxml.h"
#include "rollingstock.h"
#include "enginelengths.h"
#include "swingpropertychangesupport.h"
#include "train.h"
#include "instancemanager.h"
#include "consistmanager.h"

//Engine::Engine(QObject *parent) :
//  RollingStock(parent)
//{
//}
namespace Operations
{
/**
 * Represents a locomotive on the layout
 *
 * @author Daniel Boudreau (C) Copyright 2008
 * @version $Revision: 29278 $
 */
///*public*/ class Engine extends RollingStock {

 /*public*/ /*static*/ /*final*/ int Engine::NCE_REAR_BLOCK_NUMBER = 8;
 /*public*/ /*static*/ /*final*/ int Engine::B_UNIT_BLOCKING = 10; // block B Units after NCE Consists
 /*public*/ /*static*/ /*final*/ QString Engine::HP_CHANGED_PROPERTY = "hp"; // NOI18N

 /*public*/ Engine::Engine(QString road, QString number, QObject *parent) :
   RollingStock(road, number, parent)
 {
 common();
 log->debug(tr("New engine (%1 %2)").arg(road).arg(number));

}
 /*private*/ void Engine::common()
 {
   log = new Logger("Engine");
     //super(road, number);
     addPropertyChangeListeners();
     _consist = NULL;
     _model = NONE;
     verboseStore = false;
     engineModels = (EngineModels*)InstanceManager::getDefault("EngineModels");
 }

 /**
  * Set the locomotive's model. Note a model has only one length, type, and
  * horsepower rating.
  *
  * @param model
  */
 /*public*/ void Engine::setModel(QString model) {
     QString old = _model;
     _model = model;
     if (old!=(model)) {
         setDirtyAndFirePropertyChange("engine model", old, model); // NOI18N
     }
 }

 /*public*/ QString Engine::getModel() {
     return _model;
 }

 /**
  * Set the locomotive type for this locomotive's model
  *
  * @param type Locomotive type: Steam, Diesel, Gas Turbine, etc.
  */
 /*public*/ void Engine::setTypeName(QString type) {
     if (getModel() == NULL || getModel()==(NONE)) {
         return;
     }
     QString old = getTypeName();
     engineModels->setModelType(getModel(), type);
     if (old!=(type)) {
         setDirtyAndFirePropertyChange(TYPE_CHANGED_PROPERTY, old, type);
     }
 }

 /*public*/ QString Engine::getTypeName() {
     QString type = engineModels->getModelType(getModel());
     if (type == NULL) {
         type = RollingStock::getTypeName();
     }
     return type;
 }

 /**
  * Set the locomotive horsepower rating for this locomotive's model
  *
  * @param hp locomotive horsepower
  */
 /*public*/ void Engine::setHp(QString hp) {
     if (getModel()==(NONE)) {
         return;
     }
     QString old = getHp();
     engineModels->setModelHorsepower(getModel(), hp);
     if (old!=(hp)) {
         setDirtyAndFirePropertyChange(HP_CHANGED_PROPERTY, old, hp); // NOI18N
     }
 }

 /*public*/ QString Engine::getHp() {
     QString hp = engineModels->getModelHorsepower(getModel());
     if (hp == NULL) {
         hp = NONE;
     }
     return hp;
 }

 /*public*/ int Engine::getHpInteger() {
     //try {
 bool bok;
         return getHp().toInt();
         if(!bok)
         {
         log->warn(tr("Locomotive (%1) horsepower (%2) isn't a number").arg(toString()).arg(getHp()));
         return 0;
     }
 }

 /**
  * Set the locomotive length for this locomotive's model
  *
  * @param length locomotive length
  */
 /*public*/ void Engine::setLength(QString length) {
     RollingStock::setLength(length);

        if(getModel() == NULL)
        {
       // failed, but the model may not have been set.
       log->debug(tr("NPE setting length for Engine (%1)").arg(toString()));
       return;
     }
        engineModels->setModelLength(getModel(), length);
           if (getModel()==(NONE)) {
               return;
           }
     return;
 }

 /*public*/ QString Engine::getLength() {
     try {
         QString length = RollingStock::getLength();
         if (getModel() != NULL && getModel()!=(NONE)) {
             length = engineModels->getModelLength(getModel());
         }
         if (length == NULL) {
             length = NONE;
         }
         if (length!=(_length)) {
             if (_lengthChange) // return "old" length, used for track reserve changes
             {
                 return _length;
             }
             log->debug(tr("Loco (%1) length has been modified").arg(toString()));
             RollingStock::setLength(length); // adjust track lengths
         }
         return length;
     } catch (NullPointerException* npe) {
         log->debug(tr("NPE setting length for Engine (%1)").arg(toString()));
     }
     return NONE;
 }

 /**
  * Set the locomotive weight for this locomotive's model
  *
  * @param weight locomotive weight
  */
 /*public*/ void Engine::setWeightTons(QString weight) {
     try {
        if (getModel()==(NONE)) {
            return;
        }
        QString old = getWeightTons();
        RollingStock::setWeightTons(weight);
        engineModels->setModelWeight(getModel(), weight);
        if (old!=(weight)) {
           setDirtyAndFirePropertyChange("Engine Weight Tons", old, weight); // NOI18N
        }
     } catch(NullPointerException* npe) {
        // this failed, was the model set?
        log->debug(tr("NPE setting Weight Tons for Engine (%1)").arg(toString()));
     }
 }

 /*public*/ QString Engine::getWeightTons() {
     QString weight = NULL;
     try{
        weight = engineModels->getModelWeight(getModel());
        if (weight == NULL) {
            weight = NONE;
        }
    } catch(NullPointerException* npe){
       log->debug(tr("NPE getting Weight Tons for Engine (%1)").arg(toString()));
       weight = NONE;
    }
    return weight;
 }

/*public*/ void Engine::setBunit(bool bUnit) {
    if (getModel() == (NONE)) {
        return;
    }
    bool old = isBunit();
    engineModels->setModelBunit(getModel(), bUnit);
    if (old != bUnit) {
        setDirtyAndFirePropertyChange(TYPE_CHANGED_PROPERTY, old, bUnit);
    }
}

/*public*/ bool Engine::isBunit() {
    try {
        return engineModels->isModelBunit(getModel());
    } catch (NullPointerException* npe) {
        log->debug(tr("NPE getting is B unit for Engine (%1)").arg(toString()));
    }
    return false;
}

 /**
  * Place locomotive in a consist
  *
  * @param consist
  */
 /*public*/ void Engine::setConsist(Consist* consist) {
     if (_consist == consist) {
         return;
     }
     QString old = "";
     if (_consist != NULL) {
         old = _consist->getName();
         _consist->_delete(this);
     }
     _consist = consist;
     QString newName = "";
     if (_consist != NULL) {
         _consist->add(this);
         newName = _consist->getName();
     }

     if (old!=(newName)) {
         setDirtyAndFirePropertyChange("consist", old, newName); // NOI18N
     }
 }

 /**
  * Get the consist for this locomotive
  *
  * @return NULL if locomotive isn't in a consist
  */
 /*public*/ Consist* Engine::getConsist() {
     return _consist;
 }

 /*public*/ QString Engine::getConsistName() {
     if (_consist != NULL) {
         return _consist->getName();
     }
     return NONE;
 }

 /**
  * Used to check destination track to see if it will accept locomotive
  *
  * @return status, see RollingStock.java
  */
 /*public*/ QString Engine::testDestination(Location* destination, Track* track) {
     return RollingStock::testDestination(destination, track);
 }

 /*protected*/ void Engine::moveRollingStock(RouteLocation* old, RouteLocation* next) {
     if (old == getRouteLocation()) {
         if (getConsist() == NULL || (getConsist() != NULL && getConsist()->isLead(this))) {
             if (getTrain() != NULL && getRouteLocation() != getRouteDestination()
                     && getTrain()->getLeadEngine() != this) {
                 log->debug(tr("New lead locomotive (%1) for train (%2)").arg(toString()).arg(getTrain()->getName()));
                 getTrain()->setLeadEngine(this);
                 getTrain()->createTrainIcon();
             }
         }
     }
     RollingStock::moveRollingStock(old, next);
 }

 /*public*/ void Engine::dispose() {
     setConsist(NULL);
     ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->removePropertyChangeListener(this);
     ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->removePropertyChangeListener(this);
     RollingStock::dispose();
 }

 /**
  * Construct this Entry from XML. This member has to remain synchronized
  * with the detailed DTD in operations-engines.dtd
  *
  * @param e Engine XML element
  */
 /*public*/ Engine::Engine(QDomElement e) :
     RollingStock(e) // MUST create the rolling stock first!
 {
  common();
     QString a;
     // must set _model first so locomotive hp, length, type and weight is set properly
     if ((a = e.attribute (Xml::MODEL)) != NULL) {
         _model = a;
     }
     if ((a = e.attribute (Xml::HP)) != NULL) {
         setHp(a);
     }
     if ((a = e.attribute (Xml::LENGTH)) != NULL) {
         setLength(a);
     }
     if ((a = e.attribute (Xml::TYPE)) != NULL) {
         setTypeName(a);
     }
     if ((a = e.attribute (Xml::WEIGHT_TONS)) != NULL) {
         setWeightTons(a);
     }
     if ((a = e.attribute(Xml::B_UNIT)) != "") {
         setBunit(a == (Xml::_TRUE));
     }
     if ((a = e.attribute (Xml::CONSIST)) != "") {
         Consist* c = ((ConsistManager*)InstanceManager::getDefault("Operations::ConsistManager"))->getConsistByName(a);
         if (c != NULL) {
             setConsist(c);
             if ((a = e.attribute (Xml::LEAD_CONSIST)) != NULL && a==(Xml::_TRUE)) {
                 _consist->setLead(this);
             }
             if ((a = e.attribute (Xml::CONSIST_NUM)) != NULL) {
                 _consist->setConsistNumber(a.toInt());
             }
         } else {
             log->error("Consist " + a + " does not exist");
         }
     }
     addPropertyChangeListeners();
 }


 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-engines.dtd.
  *
  * @return Contents in a JDOM Element
  */
 /*public*/ QDomElement Engine::store(QDomDocument doc)
 {
  QDomElement e = doc.createElement(Xml::ENGINE);
//  QDomElement e = QDomElement();
//  e.setTagName(Xml::ENGINE);
  RollingStock::store(e);
  e.setAttribute(Xml::MODEL, getModel());
  e.setAttribute(Xml::HP, getHp());
  e.setAttribute(Xml::B_UNIT, (isBunit() ? Xml::_TRUE : Xml::_FALSE));
  if (getConsist() != NULL)
  {
   e.setAttribute(Xml::CONSIST, getConsistName());
   if (getConsist()->isLead(this))
   {
    e.setAttribute(Xml::LEAD_CONSIST, Xml::_TRUE);
    if (getConsist()->getConsistNumber() > 0)
    {
     e.setAttribute(Xml::CONSIST_NUM,
                    getConsist()->getConsistNumber());
    }
   }
  }
  return e;
 }

 /*protected*/ void Engine::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // Set dirty
   ((EngineManagerXml*)InstanceManager::getDefault("EngineManagerXml"))->setDirty(true);
   RollingStock::setDirtyAndFirePropertyChange(p, old, n);
 }

 /*private*/ void Engine::addPropertyChangeListeners() {
  ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->SwingPropertyChangeSupport::addPropertyChangeListener(this);
  ((EngineLengths*)InstanceManager::getDefault("EngineLengths"))->SwingPropertyChangeSupport::addPropertyChangeListener(this);
 }

 /*public*/ void Engine::propertyChange(PropertyChangeEvent* e)
 {
  RollingStock::propertyChange(e);

  if (e->getPropertyName()==(EngineTypes::ENGINETYPES_NAME_CHANGED_PROPERTY)) {
      if (e->getOldValue()==(getTypeName())) {
          if (log->isDebugEnabled()) {
              log->debug(tr("Loco (%1 %2) sees type name change old: (%3) new: (%4)").arg(toString()).arg(e->getOldValue().toString()).arg(e
                      ->getNewValue().toString())); // NOI18N
          }
          setTypeName(e->getNewValue().toString());
      }
  }
  if (e->getPropertyName()==(EngineLengths::ENGINELENGTHS_NAME_CHANGED_PROPERTY)) {
      if (e->getOldValue().toString()==(getLength())) {
          if (log->isDebugEnabled()) {
              log->debug(tr("Loco (%1) sees length name change old: %2 new: %3").arg(toString()).arg(e->getOldValue().toString()).arg(e
                      ->getNewValue().toString())); // NOI18N
          }
          setLength( e->getNewValue().toString());
      }
  }
 }
} // end namespace
