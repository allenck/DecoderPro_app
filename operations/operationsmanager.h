#ifndef OPERATIONSMANAGER_H
#define OPERATIONSMANAGER_H

#include "quietshutdowntask.h"
#include <QObject>
#include "appslib_global.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"


class File;
class Logger;
namespace Operations
{
 class APPSLIBSHARED_EXPORT OperationsManager : public QObject, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)

 public:
  Q_INVOKABLE explicit OperationsManager(QObject *parent = 0);
   ~OperationsManager() {}
   OperationsManager(const OperationsManager&) : QObject() {}
  /*public*/ ShutDownTask* getDefaultShutDownTask();
  /*public*/ QString getPath();
  /*public*/ QString getPath(QString name) ;
  /*public*/ File* getFile(QString name);
  /*public*/ void setShutDownTask(ShutDownTask* shutDownTask);
  /*public*/ QString getOperationsFolderName();

 signals:

 public slots:
 private:
  /*private*/ ShutDownTask* shutDownTask;// = null;
  Logger* log;
  Q_INVOKABLE void initialize();

  class MyQuietShutdownTask : public QuietShutDownTask
  {
  public:
   MyQuietShutdownTask(QString name);
   /*public*/ bool execute();
  };

 protected:
  /*protected*/ /*final*/ QString operationsFolderName;

 };
}
Q_DECLARE_METATYPE(Operations::OperationsManager)
#endif // OPERATIONSMANAGER_H
