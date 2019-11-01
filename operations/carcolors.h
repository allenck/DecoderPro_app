#ifndef CARCOLORS_H
#define CARCOLORS_H
#include "rollingstockattribute.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT CarColors : public RollingStockAttribute
 {
 public:
  CarColors(QObject* parent = 0);
  /*public*/ static /*synchronized*/ CarColors* instance();
  /*public*/ void addName(QString color);
  /*public*/ void deleteName(QString color);
  /*public*/ void replaceName(QString oldName, QString newName);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ void load(QDomElement root);
  /*public*/ static /*final*/ QString CARCOLORS_CHANGED_PROPERTY;// = "CarColors"; // NOI18N
  /*public*/ static /*final*/ QString CARCOLORS_NAME_CHANGED_PROPERTY;// = "CarColorsName"; // NOI18Nprotected:

 private:
  /*private*/ static CarColors* _instance;// = null;
  /*private*/ static /*final*/ QString COLORS;// = Bundle.getMessage("carColors");
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ QString getDefaultNames();

 };
}
#endif // CARCOLORS_H
