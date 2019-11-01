#ifndef CARMANAGERXML_H
#define CARMANAGERXML_H
#include "operationsxml.h"
#include "appslib_global.h"

class Logger;
namespace Operations
{
 class APPSLIBSHARED_EXPORT CarManagerXml : public OperationsXml
 {
  Q_OBJECT
 public:
  explicit CarManagerXml(QObject *parent = 0);
  /*public*/ static CarManagerXml* instance();
  /*public*/ void writeFile(QString name); //throws java.io.FileNotFoundException, java.io.IOException {
  /*public*/ void readFile(QString name); //throws org.jdom2.JDOMException, java.io.IOException
  /*public*/ void setOperationsFileName(QString name) ;
  /*public*/ QString getOperationsFileName() ;
  /*public*/ void dispose();

 signals:

 public slots:

 private:
  /**
  * record the single instance *
  */
 /*private*/ static CarManagerXml* _instance;// = NULL;
  Logger* log;
 };
}
#endif // CARMANAGERXML_H
