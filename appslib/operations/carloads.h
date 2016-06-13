#ifndef CARLOADS_H
#define CARLOADS_H
#include "rollingstockattribute.h"
#include "appslib_global.h"

namespace Operations
{
 class CarLoad;
 class APPSLIBSHARED_EXPORT CarLoads : public RollingStockAttribute
 {
  Q_OBJECT
 public:
  /*public*/ CarLoads(QObject* parent =0);
  /*public*/ static /*final*/ QString NONE;// = ""; // NOI18N

  // for property change
  /*public*/ static /*final*/ QString LOAD_CHANGED_PROPERTY;// = "CarLoads_Load"; // NOI18N
  /*public*/ static /*final*/ QString LOAD_TYPE_CHANGED_PROPERTY;// = "CarLoads_Load_Type"; // NOI18N
  /*public*/ static /*final*/ QString LOAD_PRIORITY_CHANGED_PROPERTY;// = "CarLoads_Load_Priority"; // NOI18N
  /*public*/ static /*final*/ QString LOAD_NAME_CHANGED_PROPERTY;// = "CarLoads_Name"; // NOI18N
  /*public*/ static /*final*/ QString LOAD_COMMENT_CHANGED_PROPERTY;// = "CarLoads_Load_Comment"; // NOI18N
  /*public*/ static /*synchronized*/ CarLoads* instance();
  /*public*/ void addType(QString type);
  /*public*/ void replaceType(QString oldType, QString newType);
  /*public*/ QString getDefaultEmptyName();
  /*public*/ void setDefaultEmptyName(QString name);
  /*public*/ QStringList getNames(QString type);
  /*public*/ void addName(QString type, QString name);
  /*public*/ void setPriority(QString type, QString name, QString priority);
  /*public*/ QString getPriority(QString type, QString name);
  /*public*/ void setDropComment(QString type, QString name, QString comment);
  /*public*/ QString getDropComment(QString type, QString name);
  /*public*/ bool containsName(QString type, QString name);
  /*public*/ void setPickupComment(QString type, QString name, QString comment);
  /*public*/ QString getPickupComment(QString type, QString name);
  /*public*/ QString getDefaultLoadName();
  /*public*/ void setDefaultLoadName(QString name);
  /*public*/ void updateComboBox(QString type, QComboBox* box);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement e);
  /*public*/ void setLoadType(QString type, QString name, QString loadType);
  /*public*/ QString getLoadType(QString type, QString name);
  /*public*/ QHash<QString, QList<CarLoad*>*>* getList();
  /*public*/ void updateRweComboBox(QString type, QComboBox* box);
  /*public*/ QComboBox* getComboBox(QString type);
  /*public*/ QComboBox* getPriorityComboBox();
  QComboBox* getComboBox();
  /*public*/ void deleteName(QString type, QString name);
  /*public*/ void replaceName(QString type, QString oldName, QString newName);
  /*public*/ QComboBox* getLoadTypesComboBox();
  /*public*/ QComboBox* getSelectComboBox(QString type);

 private:
  /**
   * record the single instance *
   */
  /*private*/ static CarLoads* _instance;// = null;
  Logger* log;
  /*private*/ QList<CarLoad*>* getSortedList(QString type);

 protected:
  /*protected*/ QHash<QString, QList<CarLoad*>*>* list;// = new Hashtable<QString, QList<CarLoad*>*>();
  /*protected*/ QString _emptyName;// = Bundle.getMessage("EmptyCar");
  /*protected*/ QString _loadName;// = Bundle.getMessage("LoadedCar");
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // CARLOADS_H
