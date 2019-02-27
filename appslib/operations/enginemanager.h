#ifndef ENGINEMANAGER_H
#define ENGINEMANAGER_H
#include "rollingstockmanager.h"
#include <QtXml>
#include "appslib_global.h"

class QComboBox;
class QDomElement;
class Logger;
namespace Operations
{
 class Consist;
 class Engine;
 class APPSLIBSHARED_EXPORT EngineManager : public RollingStockManager
 {
  Q_OBJECT
 public:
  explicit EngineManager(QObject *parent = 0);
  ~EngineManager() {}
  EngineManager(const EngineManager&) : RollingStockManager() {}
  /*public*/ static /*final*/ QString CONSISTLISTLENGTH_CHANGED_PROPERTY;// = "ConsistListLength"; // NOI18N
  QT_DEPRECATED /*public*/ static /*synchronized*/ EngineManager* instance() ;
  /*public*/ Engine* getById(QString id);
  /*public*/ Engine* getByRoadAndNumber(QString engineRoad, QString engineNumber) ;
  /*public*/ Engine* newEngine(QString engineRoad, QString engineNumber);
  /*public*/ Consist* newConsist(QString name);
  /*public*/ void deleteConsist(QString name);
  /*public*/ Consist* getConsistByName(QString name);
  /*public*/ void replaceConsistName(QString oldName, QString newName);
  /*public*/ void load(QDomElement  root);
  /*public*/ void store(QDomElement  root, QDomDocument doc);
  /*public*/ QStringList getConsistNameList();
  /*public*/ QList<RollingStock*>* getByModelList() ;
  /*public*/ QList<RollingStock*>* getByConsistList();
  /*public*/ QList<RollingStock*>* getByHpList();
  /*public*/ QComboBox* getConsistComboBox();
  /*public*/ void updateConsistComboBox(QComboBox* box);
  /*public*/ QList<Engine*>* getByTrainBlockingList(Train* train);
  /*public*/ QStringList getEngineRoadNames(QString model);
  /*public*/ void dispose();
  /*public*/ int getConsistMaxNameLength();
  /*public*/ QList<Engine*> getAvailableTrainList(Train* train);
  Q_INVOKABLE  /*public*/ void initialize();


 signals:

 public slots:

 private:
  /**
   * record the single instance *
   */
  /*private*/ static EngineManager* _instance;// = null;
  Logger* log;
  // The special sort options for engines
  /*private*/ static /*final*/ int BY_MODEL;// = 4;
  /*private*/ static /*final*/ int BY_CONSIST;// = 5;
  /*private*/ static /*final*/ int BY_HP;// = 13;
  /*private*/ QList<Engine*>* castListToEngine(QList<RollingStock*>* list);

 protected:
  /*public*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*public*/ QHash<QString, Consist*> _consistHashTable;// = new Hashtable<String, Consist>();   	// stores Consists by number

 };

}
Q_DECLARE_METATYPE(Operations::EngineManager)
#endif // ENGINEMANAGER_H
