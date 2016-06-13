#ifndef OPERATIONSSETUPXML_H
#define OPERATIONSSETUPXML_H
#include "operationsxml.h"
#include "appslib_global.h"

namespace Operations
{

 class Control;
 class APPSLIBSHARED_EXPORT OperationsSetupXml : public OperationsXml
 {
  Q_OBJECT
 public:
  explicit OperationsSetupXml(QObject *parent = 0);
  /*public*/ static /*synchronized*/ OperationsSetupXml* instance();
  /*public*/ void writeFile(QString name) throw (FileNotFoundException, IOException);
  /*public*/ void readFile(QString name) throw (JDOMException, IOException);
  /*public*/ void setOperationsFileName(QString name) ;
  /*public*/ QString getOperationsFileName();
  /*public*/ void dispose();

 signals:

 public slots:
 private:
  /*private*/ static OperationsSetupXml* _instance;// = NULL;
  /*private*/ QString operationsFileName;// = "Operations.xml"; // NOI18N
  Logger * log;
 };
}
#endif // OPERATIONSSETUPXML_H
