#ifndef ROUTEEXPORTLOGIX_H
#define ROUTEEXPORTLOGIX_H

#include <QObject>
#include "logixmanager.h"
#include "routemanager.h"
#include "conditionalmanager.h"

class Logger;
class RouteExportToLogix : public QObject
{
  Q_OBJECT
 public:
  explicit RouteExportToLogix(QString systemName,QObject *parent = nullptr);
  RouteExportToLogix(QString systemName, RouteManager* routeManager,LogixManager* logixManager,ConditionalManager* conditionalManager, QObject* parent);
  /*public*/ void _export();

 signals:

 public slots:

 private:
  static Logger* log;
  void common();

/*private*/ /*final*/ QString logixSysName;
/*private*/ /*final*/ QString conditionalSysPrefix;
/*private*/ /*final*/ QString systemName;
/*private*/ /*final*/ RouteManager* routeManager;
/*private*/ /*final*/ LogixManager* logixManager;
/*private*/ /*final*/ ConditionalManager* conditionalManager;

};
#endif // ROUTEEXPORTLOGIX_H
