#ifndef ROUTEMANAGERXML_H
#define ROUTEMANAGERXML_H
#include "operationsxml.h"
#include "appslib_global.h"

namespace Operations
{
class APPSLIBSHARED_EXPORT RouteManagerXml : public OperationsXml
{
 Q_OBJECT
public:
 explicit RouteManagerXml(QObject *parent = 0);
 /*public*/ static /*synchronized*/ RouteManagerXml* instance();
 /*public*/ void writeFile(QString name);
 /*public*/ void readFile(QString name) throw (JDOMException, IOException) ;
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
#endif // ROUTEMANAGERXML_H
