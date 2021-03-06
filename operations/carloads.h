#ifndef CARLOADS_H
#define CARLOADS_H
#include "rollingstockattribute.h"
#include "appslib_global.h"
#include "jcombobox.h"
#include "instancemanagerautodefault.h"

namespace Operations
{
 class CarLoad;
 class APPSLIBSHARED_EXPORT CarLoads : public RollingStockAttribute, public InstanceManagerAutoDefault
 {
  Q_OBJECT
     Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  Q_INVOKABLE /*public*/ CarLoads(QObject* parent =0);
  ~CarLoads() {}
  CarLoads(const CarLoads&) : RollingStockAttribute() {}
  /*public*/ static /*final*/ QString NONE;// = ""; // NOI18N

  // for property change
  /*public*/ static /*final*/ QString LOAD_CHANGED_PROPERTY;// = "CarLoads_Load"; // NOI18N
  /*public*/ static /*final*/ QString LOAD_TYPE_CHANGED_PROPERTY;// = "CarLoads_Load_Type"; // NOI18N
  /*public*/ static /*final*/ QString LOAD_PRIORITY_CHANGED_PROPERTY;// = "CarLoads_Load_Priority"; // NOI18N
  /*public*/ static /*final*/ QString LOAD_NAME_CHANGED_PROPERTY;// = "CarLoads_Name"; // NOI18N
  /*public*/ static /*final*/ QString LOAD_COMMENT_CHANGED_PROPERTY;// = "CarLoads_Load_Comment"; // NOI18N
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
  /*public*/ void updateComboBox(QString type, JComboBox* box);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement e);
  /*public*/ void setLoadType(QString type, QString name, QString loadType);
  /*public*/ QString getLoadType(QString type, QString name);
  /*public*/ QHash<QString, QList<CarLoad*>*>* getList();
  /*public*/ void updateRweComboBox(QString type, JComboBox* box);
  /*public*/ JComboBox* getComboBox(QString type);
  /*public*/ JComboBox* getPriorityComboBox();
  JComboBox* getComboBox();
  /*public*/ void deleteName(QString type, QString name);
  /*public*/ void replaceName(QString type, QString oldName, QString newName);
  /*public*/ JComboBox* getLoadTypesComboBox();
  /*public*/ JComboBox* getSelectComboBox(QString type);

 private:
  /**
   * record the single instance *
   */
  Logger* log;
  /*private*/ QList<CarLoad*>* getSortedList(QString type);

 protected:
  /*protected*/ QHash<QString, QList<CarLoad*>*>* list;// = new Hashtable<QString, QList<CarLoad*>*>();
  /*protected*/ QString _emptyName;// = Bundle.getMessage("EmptyCar");
  /*protected*/ QString _loadName;// = Bundle.getMessage("LoadedCar");
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
Q_DECLARE_METATYPE(Operations::CarLoads)
#endif // CARLOADS_H
