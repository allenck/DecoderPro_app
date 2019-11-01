#ifndef ENGINETYPES_H
#define ENGINETYPES_H
#include "rollingstockattribute.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT EngineTypes : public RollingStockAttribute
 {
  Q_OBJECT
 public:
  explicit EngineTypes(QObject *parent = 0);
  /*public*/ static /*final*/ QString ENGINETYPES_CHANGED_PROPERTY;// = "EngineTypesLength"; // NOI18N
  /*public*/ static /*final*/ QString ENGINETYPES_NAME_CHANGED_PROPERTY;// = "EngineTypesName"; // NOI18N
  /*public*/ static /*synchronized*/ EngineTypes* instance();
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
#endif // ENGINETYPES_H
