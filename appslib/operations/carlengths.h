#ifndef CARLENGTHS_H
#define CARLENGTHS_H
#include "rollingstockattribute.h"
#include "appslib_global.h"

class QDomElement;
namespace Operations
{
 class APPSLIBSHARED_EXPORT CarLengths : public RollingStockAttribute
 {
  Q_OBJECT
 public:
  /*public*/ CarLengths(QObject* parent = 0);
  /*private*/ static /*final*/ QString LENGTHS;// = Bundle.getMessage("carLengths");
  /*public*/ static /*final*/ QString CARLENGTHS_CHANGED_PROPERTY;// = "CarLengths"; // NOI18N
  /*public*/ static /*final*/ QString CARLENGTHS_NAME_CHANGED_PROPERTY;// = "CarLengthsName"; // NOI18N
  /*public*/ static /*synchronized*/ CarLengths* instance();
  /*public*/ void setNames(QStringList lengths);
  /*public*/ void addName(QString length);
  /*public*/ void deleteName(QString length);
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ void store(QDomElement root, QDomDocument doc) ;
  /*public*/ void load(QDomElement root) ;

 private:
  /*private*/ static CarLengths* _instance;// = null;
 protected:
  /*protected*/ QString getDefaultNames();
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
}
#endif // CARLENGTHS_H
