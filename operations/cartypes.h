#ifndef CARTYPES_H
#define CARTYPES_H
#include "rollingstockattribute.h"
#include "appslib_global.h"
#include "instancemanagerautodefault.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT CarTypes : public RollingStockAttribute, public InstanceManagerAutoDefault
 {
  Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  explicit CarTypes(QObject *parent = 0);
   ~CarTypes() {}
   CarTypes(const CarTypes&) : RollingStockAttribute() {}
  /*public*/ static /*final*/ QString CARTYPES_CHANGED_PROPERTY;// = "CarTypes Length"; // NOI18N
  /*public*/ static /*final*/ QString CARTYPES_NAME_CHANGED_PROPERTY;// = "CarTypes Name"; // NOI18N
  /*public*/ void changeDefaultNames(QString type);
  /*public*/ void addName(QString type);
  /*public*/ void deleteName(QString type);
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ int getMaxNameLength();
  /*public*/ int getMaxFullNameLength() ;
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);

 signals:

 public slots:

 private:
  Logger* log;
  /*private*/ static /*final*/ QString TYPES;// = Bundle.getMessage("carTypeNames");
  /*private*/ static /*final*/ QString CONVERT_TYPES;// = Bundle.getMessage("carTypeConvert"); // Used to convert from ARR to
  // Descriptive
  /*private*/ static /*final*/ QString ARR_TYPES;// = Bundle.getMessage("carTypeARR");
  // for property change
  /**
   * record the single instance *
   */
  /*private*/ static CarTypes* _instance;// = null;
   /*private*/ int maxNameLengthSubType;// = 0;

protected:
  /*protected*/ QString getDefaultNames() override;
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
Q_DECLARE_METATYPE(Operations::CarTypes)
#endif // CARTYPES_H
