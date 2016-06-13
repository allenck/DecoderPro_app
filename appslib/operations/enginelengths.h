#ifndef ENGINELENGTHS_H
#define ENGINELENGTHS_H
#include "rollingstockattribute.h"
#include "appslib_global.h"

class QDomDocument;
class QDomElement;
namespace Operations
{
 class APPSLIBSHARED_EXPORT EngineLengths : public RollingStockAttribute
 {
  Q_OBJECT
 public:
  EngineLengths(QObject* parent = 0);
  /*public*/ static /*final*/ QString ENGINELENGTHS_CHANGED_PROPERTY;// = "EngineLengths"; // NOI18N
  /*public*/ static /*final*/ QString ENGINELENGTHS_NAME_CHANGED_PROPERTY;// = "EngineLengthsName"; // NOI18N
  /*public*/ static /*synchronized*/ EngineLengths* instance();
  /*public*/ void setNames(QStringList lengths);
  /*public*/ void addName(QString length);
  /*public*/ void deleteName(QString length);
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);

 private:
  /*private*/ static /*final*/ QString LENGTHS;// = Bundle.getMessage("engineDefaultLengths");
  /*private*/ static EngineLengths* _instance;// = null;

 protected:
  /*protected*/ QString getDefaultNames();

  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // ENGINELENGTHS_H
