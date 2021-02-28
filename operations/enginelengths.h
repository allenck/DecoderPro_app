#ifndef ENGINELENGTHS_H
#define ENGINELENGTHS_H
#include "rollingstockattribute.h"
#include "appslib_global.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

class QDomDocument;
class QDomElement;
namespace Operations
{
 class APPSLIBSHARED_EXPORT EngineLengths : public RollingStockAttribute, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)
 public:
  Q_INVOKABLE EngineLengths(QObject* parent = 0);
   ~EngineLengths() {}
   EngineLengths(const EngineLengths&) : RollingStockAttribute() {}
  /*public*/ static /*final*/ QString ENGINELENGTHS_CHANGED_PROPERTY;// = "EngineLengths"; // NOI18N
  /*public*/ static /*final*/ QString ENGINELENGTHS_NAME_CHANGED_PROPERTY;// = "EngineLengthsName"; // NOI18N
  /*public*/ static /*synchronized*/ EngineLengths* instance();
  /*public*/ void setNames(QStringList lengths);
  /*public*/ void addName(QString length);
  /*public*/ void deleteName(QString length);
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);
 Q_INVOKABLE /*public*/ void initialize() override;

 private:
  /*private*/ static /*final*/ QString LENGTHS;// = Bundle.getMessage("engineDefaultLengths");
  /*private*/ static EngineLengths* _instance;// = null;

 protected:
  /*protected*/ QString getDefaultNames();

  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
Q_DECLARE_METATYPE(Operations::EngineLengths)
#endif // ENGINELENGTHS_H
