#ifndef LOCATIONMANAGERXML_H
#define LOCATIONMANAGERXML_H
#include "operationsxml.h"
#include "logger.h"
#include <QtXml>
#include "appslib_global.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT LocationManagerXml : public OperationsXml, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
     Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)
 public:
  Q_INVOKABLE explicit LocationManagerXml(QObject *parent = 0);
   ~LocationManagerXml() {}
   LocationManagerXml(const LocationManagerXml&) : OperationsXml() {}
  /*public*/ void writeFile(QString name) throw (FileNotFoundException, IOException);
  /*public*/ void readFile(QString name) throw (JDOMException, IOException);
  /*public*/ void setOperationsFileName(QString name);
  /*public*/ QString getOperationsFileName() ;
  Q_INVOKABLE /*public*/ void initialize();
  /*public*/ void dispose();

 signals:

 public slots:

 private:
  // /*private*/ static LocationManagerXml* _instance;// = null;
  /*private*/ QString operationsFileName;// = "OperationsLocationRoster.xml"; // NOI18N
  Logger* log;

 };
}
Q_DECLARE_METATYPE(Operations::LocationManagerXml)
#endif // LOCATIONMANAGERXML_H
