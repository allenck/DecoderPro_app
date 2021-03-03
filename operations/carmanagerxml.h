#ifndef CARMANAGERXML_H
#define CARMANAGERXML_H
#include "operationsxml.h"
#include "appslib_global.h"
#include "instancemanagerautoinitialize.h"
class Logger;
namespace Operations
{
 class APPSLIBSHARED_EXPORT CarManagerXml : public OperationsXml, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoInitialize)
 public:
  Q_INVOKABLE explicit CarManagerXml(QObject *parent = 0);
   ~CarManagerXml() {}
   CarManagerXml(const CarManagerXml&) : OperationsXml() {}
  /*public*/ void writeFile(QString name); //throws java.io.FileNotFoundException, java.io.IOException {
  /*public*/ void readFile(QString name); //throws org.jdom2.JDOMException, java.io.IOException
  /*public*/ void setOperationsFileName(QString name) ;
  /*public*/ QString getOperationsFileName() ;
  /*public*/ void dispose();
  Q_INVOKABLE /*public*/ void initialize();

 signals:

 public slots:

 private:
  /**
  * record the single instance *
  */
  Logger* log;
 };
}
Q_DECLARE_METATYPE(Operations::CarManagerXml)
#endif // CARMANAGERXML_H
