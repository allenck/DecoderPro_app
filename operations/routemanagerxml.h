#ifndef ROUTEMANAGERXML_H
#define ROUTEMANAGERXML_H
#include "operationsxml.h"
#include "appslib_global.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT RouteManagerXml : public OperationsXml, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)
 public:
  Q_INVOKABLE explicit RouteManagerXml(QObject *parent = 0);
   ~RouteManagerXml(){}
   RouteManagerXml(const RouteManagerXml&) : OperationsXml() {}
  /*public*/ void writeFile(QString name);
  /*public*/ void readFile(QString name) /*throw (JDOMException, IOException)*/ ;
  /*public*/ void setOperationsFileName(QString name) ;
  /*public*/ QString getOperationsFileName() ;
  /*public*/ void dispose();
  Q_INVOKABLE /*public*/ void initialize();

 signals:

 public slots:
 private:
 // /*private*/ static RouteManagerXml* _instance;// = null;
  Logger* log;
  /*private*/ QString operationsFileName;// = "OperationsRouteRoster.xml"; // NOI18N

 };
}
Q_DECLARE_METATYPE(Operations::RouteManagerXml)
#endif // ROUTEMANAGERXML_H
