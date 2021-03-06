#ifndef ENGINETYPES_H
#define ENGINETYPES_H
#include "rollingstockattribute.h"
#include "appslib_global.h"
#include "instancemanagerautodefault.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT EngineTypes : public RollingStockAttribute, public InstanceManagerAutoDefault
 {
  Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  Q_INVOKABLE explicit EngineTypes(QObject *parent = 0);
   ~EngineTypes() {}
   EngineTypes(const EngineTypes&) : RollingStockAttribute() {}
  /*public*/ static /*final*/ QString ENGINETYPES_CHANGED_PROPERTY;// = "EngineTypesLength"; // NOI18N
  /*public*/ static /*final*/ QString ENGINETYPES_NAME_CHANGED_PROPERTY;// = "EngineTypesName"; // NOI18N
  /*public*/ void addName(QString type) ;
  /*public*/ void deleteName(QString type) ;
  /*public*/ void replaceName(QString oldName, QString newName) ;
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);

 signals:

 public slots:
 private:
  /*private*/ static /*final*/ QString TYPES;// = Bundle.getMessage("engineDefaultTypes");
  /**
   * record the single instance *
   */
  /*private*/ static EngineTypes* _instance;// = null;
  Logger* log;
 protected:
  /*protected*/ QString getDefaultNames();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
Q_DECLARE_METATYPE(Operations::EngineTypes)
#endif // ENGINETYPES_H
