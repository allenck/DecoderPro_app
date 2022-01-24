#ifndef CARLENGTHS_H
#define CARLENGTHS_H
#include "rollingstockattribute.h"
#include "appslib_global.h"
#include "instancemanagerautodefault.h"

class QDomElement;
namespace Operations
{
 class APPSLIBSHARED_EXPORT CarLengths : public RollingStockAttribute, public InstanceManagerAutoDefault
 {
  Q_OBJECT
     Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  Q_INVOKABLE/*public*/ CarLengths(QObject* parent = 0);
     ~CarLengths() {}
     CarLengths(const CarLengths&) : RollingStockAttribute() {}
  /*private*/ static /*final*/ QString LENGTHS;// = Bundle.getMessage("carLengths");
  /*public*/ static /*final*/ QString CARLENGTHS_CHANGED_PROPERTY;// = "CarLengths"; // NOI18N
  /*public*/ static /*final*/ QString CARLENGTHS_NAME_CHANGED_PROPERTY;// = "CarLengthsName"; // NOI18N
  /*public*/ void setNames(QStringList lengths);
  /*public*/ void addName(QString length);
  /*public*/ void deleteName(QString length);
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ void store(QDomElement root, QDomDocument doc) ;
  /*public*/ void load(QDomElement root) ;

 private:
 protected:
  /*protected*/ QString getDefaultNames();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
Q_DECLARE_METATYPE(Operations::CarLengths)

#endif // CARLENGTHS_H
