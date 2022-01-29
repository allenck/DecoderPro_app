#ifndef FUNCTIONMANAGER_H
#define FUNCTIONMANAGER_H
#include "constant.h"
#include "function.h"
#include <QObject>
#include "instancemanagerautodefault.h"

class FunctionManager : public QObject, public InstanceManagerAutoDefault
{
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  FunctionManager();
  /*public*/  QMap<QString, Function*> getFunctions();
      /*public*/  Function* get(QString name);
      /*public*/  Function* put(QString name, Function* function);
      /*public*/  Constant* getConstant(QString name);
      /*public*/  void put(QString name, Constant* constant);
 private:
  /*private*/ /*final*/ QMap<QString, Constant*> _constants =  QMap<QString, Constant*>();
  /*private*/ /*final*/ QMap<QString, Function*> _functions = QMap<QString, Function*>();

};

#endif // FUNCTIONMANAGER_H
