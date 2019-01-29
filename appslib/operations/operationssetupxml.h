#ifndef OPERATIONSSETUPXML_H
#define OPERATIONSSETUPXML_H
#include "operationsxml.h"
#include "appslib_global.h"
#include "exceptions.h"

class FileNotFoundException;
class IOException;
class JDOMException;
namespace Operations
{

 class Control;
 class APPSLIBSHARED_EXPORT OperationsSetupXml : public OperationsXml
 {
  Q_OBJECT
 public:
  explicit OperationsSetupXml(QObject *parent = 0);
  ~OperationsSetupXml() {}
  OperationsSetupXml(const OperationsSetupXml&) : OperationsXml() {}
  /*public*/ static /*synchronized*/ OperationsSetupXml* instance();
  /*public*/ void writeFile(QString name);// throw (FileNotFoundException, IOException);
  /*public*/ void readFile(QString name);// throw (JDOMException, IOException);
  /*public*/ void setOperationsFileName(QString name) ;
  /*public*/ QString getOperationsFileName();
  /*public*/ void dispose();
  Q_INVOKABLE /*public*/ void initialize();

 signals:

 public slots:
 private:
//  /*private*/ static OperationsSetupXml* _instance;// = NULL;
  /*private*/ QString operationsFileName;// = "Operations.xml"; // NOI18N
  Logger * log;
 };

}
Q_DECLARE_METATYPE(Operations::OperationsSetupXml)
#endif // OPERATIONSSETUPXML_H
