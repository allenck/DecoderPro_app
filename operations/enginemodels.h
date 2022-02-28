#ifndef ENGINEMODELS_H
#define ENGINEMODELS_H
#include "rollingstockattribute.h"
#include <QHash>
#include "appslib_global.h"
#include "instancemanagerautodefault.h"
#include "abstractinstanceinitializer.h"

class QDomElement;
namespace Operations
{
 class APPSLIBSHARED_EXPORT EngineModels : public RollingStockAttribute, public InstanceManagerAutoDefault
 {
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  Q_INVOKABLE explicit EngineModels(QObject *parent = 0);
   ~EngineModels() {}
   EngineModels(const EngineModels&) : RollingStockAttribute() {}
  /*public*/ static /*final*/ QString ENGINEMODELS_CHANGED_PROPERTY;// = "EngineModels"; // NOI18N
  /*public*/ static /*final*/ QString ENGINEMODELS_NAME_CHANGED_PROPERTY;// = "EngineModelsName"; // NOI18N
  /*protected*/ QString getDefaultNames() override;
  /*public*/ void addName(QString model)override;
  /*public*/ void deleteName(QString model)override;
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ void setModelHorsepower(QString model, QString horsepower);
  /*public*/ QString getModelHorsepower(QString model);
  /*public*/ void setModelLength(QString model, QString horsepower) ;
  /*public*/ QString getModelLength(QString model);
  /*public*/ void setModelType(QString model, QString type) ;
  /*public*/ QString getModelType(QString model) ;
  /*public*/ void setModelWeight(QString model, QString type);
  /*public*/ QString getModelWeight(QString model) ;
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);
  /*public*/ void dispose();
  /*public*/ void setModelBunit(QString model, bool bUnit);
  /*public*/ bool isModelBunit(QString model);

   //@ServiceProvider(service = InstanceInitializer.class)
   /*public*/ /*static*/ class Initializer : public AbstractInstanceInitializer {

       //@Override
       //@Nonnull
       /*public*/ /*<T>*/ QObject* getDefault(QString type) const override{
           if (type == ("EngineModels")) {
            EngineModels* instance = new EngineModels();
            instance->loadDefaults();
            return instance;
           }
           return AbstractInstanceInitializer::getDefault(type);
       }

       //@Override
       //@Nonnull
       /*public*/ QSet</*Class<?>*/QString>* getInitalizes()override {
           QSet</*Class<?>*/QString>* set = AbstractInstanceInitializer::getInitalizes();
           set->insert("EngineModels");
           return set;
       }

   };
 signals:

 public slots:
 private:
  /*private*/ static /*final*/ QString MODELS; //=Bundle.getMessage("engineDefaultModels");
  // Horsepower, length, and type have a one to one correspondence with the above MODELS
  /*private*/ static /*final*/ QString HORSEPOWER; //=Bundle.getMessage("engineModelHorsepowers");
  /*private*/ static /*final*/ QString ENGINELENGTHS; //=Bundle.getMessage("engineModelLengths");
  /*private*/ static /*final*/ QString ENGINETYPES; //=Bundle.getMessage("engineModelTypes");
  /*private*/ static /*final*/ QString ENGINEWEIGHTS; //=Bundle.getMessage("engineModelWeights");
  /**
   * record the single instance *
   */
  /*private*/ void loadDefaults();
 Logger* log;
 protected:
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ QHash<QString, QString> _engineHorsepowerHashTable;// = new Hashtable<String, String>();
  /*protected*/ QHash<QString, QString>_engineLengthHashTable;// = new Hashtable<String, String>();
  /*protected*/ QHash<QString, QString>_engineTypeHashTable;// = new Hashtable<String, String>();
  /*protected*/ QHash<QString, QString>_engineWeightHashTable;// = new Hashtable<String, String>();
  /*protected*/ QHash<QString, bool> _engineBunitHashTable;// = new Hashtable<>();

 };
}
Q_DECLARE_METATYPE(Operations::EngineModels)
#endif // ENGINEMODELS_H
