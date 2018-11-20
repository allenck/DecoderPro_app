#ifndef ENGINEMANAGERXML_H
#define ENGINEMANAGERXML_H
#include "operationsxml.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT EngineManagerXml : public OperationsXml
 {
  Q_OBJECT
 public:
  explicit EngineManagerXml(QObject *parent = 0);
  /*public*/ static /*synchronized*/ EngineManagerXml* instance();
  /*public*/ void writeFile(QString name); //throws java.io.FileNotFoundException, java.io.IOException
  /*public*/ void readFile(QString name); //throws org.jdom2.JDOMException, java.io.IOException
  /*public*/ void setOperationsFileName(QString name);
  /*public*/ QString getOperationsFileName();
  /*public*/ void dispose();
  Q_INVOKABLE  /*public*/ void initialize();

 signals:

 public slots:
 private:
//  /*private*/ static EngineManagerXml* _instance;// = null;
  Logger* log;
  /*private*/ QString operationsFileName;// = "OperationsEngineRoster.xml"; // NOI18N

 };
}
#endif // ENGINEMANAGERXML_H
