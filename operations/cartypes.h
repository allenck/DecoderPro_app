#ifndef CARTYPES_H
#define CARTYPES_H
#include "rollingstockattribute.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT CarTypes : public RollingStockAttribute
 {
  Q_OBJECT
 public:
  explicit CarTypes(QObject *parent = 0);
  /*public*/ static /*final*/ QString CARTYPES_CHANGED_PROPERTY;// = "CarTypes Length"; // NOI18N
  /*public*/ static /*final*/ QString CARTYPES_NAME_CHANGED_PROPERTY;// = "CarTypes Name"; // NOI18N
  /*public*/ static /*synchronized*/ CarTypes* instance();
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
  /*protected*/ QString getDefaultNames();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // CARTYPES_H
