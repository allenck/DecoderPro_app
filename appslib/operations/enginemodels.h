#ifndef ENGINEMODELS_H
#define ENGINEMODELS_H
#include "rollingstockattribute.h"
#include <QHash>
#include "appslib_global.h"

class QDomElement;
namespace Operations
{
 class APPSLIBSHARED_EXPORT EngineModels : public RollingStockAttribute
 {
  Q_OBJECT
 public:
  explicit EngineModels(QObject *parent = 0);
  /*public*/ static /*final*/ QString ENGINEMODELS_CHANGED_PROPERTY;// = "EngineModels"; // NOI18N
  /*public*/ static /*final*/ QString ENGINEMODELS_NAME_CHANGED_PROPERTY;// = "EngineModelsName"; // NOI18N
  /*public*/ static  /*synchronized*/ EngineModels* instance();
  /*protected*/ QString getDefaultNames();
  /*public*/ void addName(QString model);
  /*public*/ void deleteName(QString model);
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
  /*private*/ static  EngineModels* _instance;// = null;
  /*private*/ void loadDefaults();
 Logger* log;
 protected:
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ QHash<QString, QString> _engineHorsepowerHashTable;// = new Hashtable<String, String>();
  /*protected*/ QHash<QString, QString>_engineLengthHashTable;// = new Hashtable<String, String>();
  /*protected*/ QHash<QString, QString>_engineTypeHashTable;// = new Hashtable<String, String>();
  /*protected*/ QHash<QString, QString>_engineWeightHashTable;// = new Hashtable<String, String>();

 };
}
#endif // ENGINEMODELS_H
