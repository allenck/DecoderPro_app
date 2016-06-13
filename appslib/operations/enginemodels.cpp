#include "enginemodels.h"
#include "control.h"
#include <QVariant>
#include "xml.h"
#include <QDomElement>
#include "logger.h"
#include "enginemanagerxml.h"
#include "rollingstockattribute.h"
#include <QVariant>

//EngineModels::EngineModels(QObject *parent) :
//  RollingStockAttribute(parent)
//{
//}
namespace Operations {
/**
 * Represents the various engine models a railroad can have. Each model has a
 * type, horsepower rating and length that is kept here. The program provides
 * some default models for the user. These values can be overridden by the user.
 *
 * Model Horsepower Length Type E8 2250 70 Diesel FT 1350 50 Diesel F3 1500 50
 * Diesel F7 1500 50 Diesel F9 1750 50 Diesel GP20 2000 56 Diesel GP30 2250 56
 * Diesel GP35 2500 56 Diesel GP38 2000 59 Diesel GP40 3000 59 Diesel RS1 1000
 * 51 Diesel RS2 1500 52 Diesel RS3 1600 51 Diesel RS11 1800 53 Diesel RS18 1800
 * 52 Diesel RS27 2400 57 Diesel RSD4 1600 52 Diesel SD26 2650 61 Diesel SD45
 * 3600 66 Diesel SW1200 1200 45 Diesel SW1500 1500 45 Diesel SW8 800 44 Diesel
 * TRAINMASTER 2400 66 Diesel U28B 2800 60 Diesel
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 29493 $
 */
///*public*/ class EngineModels extends RollingStockAttribute {

 /*private*/ /*static*/  /*final*/ QString EngineModels::MODELS = tr("E8,FT,F3,F7,F9,GG1,GP20,GP30,GP35,GP38,GP40,GTEL,RS1,RS2,RS3,RS11,RS18,RS27,RSD4,Shay,SD26,SD45,SW1200,SW1500,SW8,TRAINMASTER,U28B");
 // Horsepower, length, and type have a one to one correspondence with the above MODELS
 /*private*/ /*static*/  /*final*/ QString EngineModels::HORSEPOWER = tr("2250,1350,1500,1500,1750,4620,2000,2250,2500,2000,3000,4500,1000,1500,1600,1800,1800,2400,1600,70,2650,3600,1200,1500,800,2400,2800");
 /*private*/ /*static*/  /*final*/ QString EngineModels::ENGINELENGTHS = tr("70,50,50,50,50,80,56,56,56,59,59,80,51,52,51,53,52,57,52,50,61,66,45,45,44,66,60");
 /*private*/ /*static*/  /*final*/ QString EngineModels::ENGINETYPES = tr("Diesel,Diesel,Diesel,Diesel,Diesel,Electric,Diesel,Diesel,Diesel,Diesel,Diesel,Gas Turbine,Diesel,Diesel,Diesel,Diesel,Diesel,Diesel,Diesel,Steam,Diesel,Diesel,Diesel,Diesel,Diesel,Diesel,Diesel");
 /*private*/ /*static*/  /*final*/ QString EngineModels::ENGINEWEIGHTS = tr("158,115,115,115,115,238,120,130,130,125,122,204,124,115,114,125,118,132,179,50,164,195,124,124,115,188,126");

 /*public*/ /*static*/  /*final*/ QString EngineModels::ENGINEMODELS_CHANGED_PROPERTY = "EngineModels"; // NOI18N
 /*public*/ /*static*/  /*final*/ QString EngineModels::ENGINEMODELS_NAME_CHANGED_PROPERTY = "EngineModelsName"; // NOI18N

 // /*protected*/ List<String> _list = new ArrayList<String>();

 /*public*/ EngineModels::EngineModels(QObject *parent) :
  RollingStockAttribute(parent)
 {

 _engineHorsepowerHashTable = QHash<QString, QString>();
 _engineLengthHashTable = QHash<QString, QString>();
 _engineTypeHashTable = QHash<QString, QString>();
 _engineWeightHashTable = QHash<QString, QString>();

 }
/**
 * record the single instance *
 */
/*private*/ /*static*/  EngineModels* EngineModels::_instance = NULL;


 /*public*/ /*static*/  /*synchronized*/ EngineModels* EngineModels::instance()
 {
 Logger* log = new Logger("EngineModels");
     if (_instance == NULL) {
         if (log->isDebugEnabled()) {
             log->debug("EngineModels creating instance");
         }
         // create and load
         _instance = new EngineModels();
         _instance->loadDefaults();
     }
     if (Control::showInstance) {
         log->debug(tr("EngineModels returns instance %1").arg(_instance->metaObject()->className()));
     }
     return _instance;
 }

 /*protected*/ QString EngineModels::getDefaultNames() {
     return MODELS;
 }

 /*public*/ void EngineModels::dispose() {
     _engineHorsepowerHashTable.clear();
     _engineLengthHashTable.clear();
     _engineTypeHashTable.clear();
     _engineWeightHashTable.clear();
     RollingStockAttribute::dispose();
     loadDefaults();
 }

 /*public*/ void EngineModels::addName(QString model) {
     RollingStockAttribute::addName(model);
     setDirtyAndFirePropertyChange(ENGINEMODELS_CHANGED_PROPERTY, QVariant(), model);
 }

 /*public*/ void EngineModels::deleteName(QString model) {
     RollingStockAttribute::deleteName(model);
     setDirtyAndFirePropertyChange(ENGINEMODELS_CHANGED_PROPERTY, model, QVariant());
 }

 /*public*/ void EngineModels::replaceName(QString oldName, QString newName) {
     RollingStockAttribute::addName(newName);
     setDirtyAndFirePropertyChange(ENGINEMODELS_NAME_CHANGED_PROPERTY, oldName, newName);
     RollingStockAttribute::deleteName(oldName);
 }

 /*public*/ void EngineModels::setModelHorsepower(QString model, QString horsepower) {
     _engineHorsepowerHashTable.insert(model, horsepower);
 }

 /*public*/ QString EngineModels::getModelHorsepower(QString model) {
     return _engineHorsepowerHashTable.value(model);
 }

 /*public*/ void EngineModels::setModelLength(QString model, QString horsepower) {
     _engineLengthHashTable.insert(model, horsepower);
 }

 /*public*/ QString EngineModels::getModelLength(QString model) {
     return _engineLengthHashTable.value(model);
 }

 /*public*/ void EngineModels::setModelType(QString model, QString type) {
     _engineTypeHashTable.insert(model, type);
 }

 /*public*/ QString EngineModels::getModelType(QString model) {
     return _engineTypeHashTable.value(model);
 }

 /*public*/ void EngineModels::setModelWeight(QString model, QString type) {
     _engineWeightHashTable.insert(model, type);
 }

 /**
  *
  * @param model The engine model (example GP20)
  * @return This model's weight in tons
  */
 /*public*/ QString EngineModels::getModelWeight(QString model) {
     return _engineWeightHashTable.value(model);
 }

 /*private*/ void EngineModels::loadDefaults() {
     QStringList models = MODELS.split(","); // NOI18N
     QStringList hps = HORSEPOWER.split(","); // NOI18N
     QStringList lengths = ENGINELENGTHS.split(","); // NOI18N
     QStringList types = ENGINETYPES.split(","); // NOI18N
     QStringList weights = ENGINEWEIGHTS.split(","); // NOI18N
     if (models.length() != hps.length() || models.length() != lengths.length() || models.length() != types.length()
         || models.length() != weights.length()) {
      log->error(tr("Defaults do not have the right number of items, ") + "models=" + QString::number(models.length()) + " hps="
                    + QString::number(hps.length()) + " lengths=" + QString::number(lengths.length()) // NOI18N
                    + " types=" + QString::number(types.length())); // NOI18N
         return;
     }

     for (int i = 0; i < models.length(); i++) {
         setModelHorsepower(models[i], hps[i]);
         setModelLength(models[i], lengths[i]);
         setModelType(models[i], types[i]);
         setModelWeight(models[i], weights[i]);
     }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-engines.dtd.
  *
  */
 /*public*/ void EngineModels::store(QDomElement root, QDomDocument doc)
 {
  RollingStockAttribute::store(root, Xml::MODELS, Xml::MODEL, Xml::ENGINE_MODELS, doc);
 }

 /*public*/ void EngineModels::load(QDomElement root)
 {
     RollingStockAttribute::load(root, Xml::MODELS, Xml::MODEL, Xml::ENGINE_MODELS);
 }

 /*protected*/ void EngineModels::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n)
 {
     // Set dirty
     EngineManagerXml::instance()->setDirty(true);
     RollingStockAttribute::firePropertyChange(p, old, n);
 }
}
