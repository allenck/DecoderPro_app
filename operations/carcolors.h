#ifndef CARCOLORS_H
#define CARCOLORS_H
#include "rollingstockattribute.h"
#include "appslib_global.h"
#include "instancemanagerautodefault.h"

class Logger;
namespace Operations
{
 class APPSLIBSHARED_EXPORT CarColors : public RollingStockAttribute, public InstanceManagerAutoDefault
 {
     Q_OBJECT
     Q_INTERFACES(InstanceManagerAutoDefault)

 public:
  Q_INVOKABLE CarColors(QObject* parent = nullptr);
  ~CarColors() {}
  CarColors(const CarColors&) : RollingStockAttribute(){}
  /*public*/ void addName(QString color) override;
  /*public*/ void deleteName(QString color) override;
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ int getMaxNameLength() override;
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);
  /*public*/ static /*final*/ QString CARCOLORS_CHANGED_PROPERTY;// = "CarColors"; // NOI18N
  /*public*/ static /*final*/ QString CARCOLORS_NAME_CHANGED_PROPERTY;// = "CarColorsName"; // NOI18Nprotected:

 private:
  /*private*/ static /*final*/ QString COLORS;// = Bundle.getMessage("carColors");
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ QString getDefaultNames() override;
  static Logger* log;
 };
}
Q_DECLARE_METATYPE(Operations::CarColors)
#endif // CARCOLORS_H
