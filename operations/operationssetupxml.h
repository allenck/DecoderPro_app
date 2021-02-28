#ifndef OPERATIONSSETUPXML_H
#define OPERATIONSSETUPXML_H
#include "operationsxml.h"
#include "appslib_global.h"
#include "exceptions.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

class FileNotFoundException;
class IOException;
class JDOMException;
namespace Operations
{

 class Control;
 class APPSLIBSHARED_EXPORT OperationsSetupXml : public OperationsXml, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)

 public:
  Q_INVOKABLE explicit OperationsSetupXml(QObject *parent = 0);
  ~OperationsSetupXml() {}
  OperationsSetupXml(const OperationsSetupXml&) : OperationsXml() {}
  /*public*/ void writeFile(QString name) override;// throw (FileNotFoundException, IOException);
  /*public*/ void readFile(QString name)override;// throw (JDOMException, IOException);
  /*public*/ void setOperationsFileName(QString name) override;
  /*public*/ QString getOperationsFileName()override;
  /*public*/ void dispose();
  Q_INVOKABLE /*public*/ void initialize() override;

 signals:

 public slots:
 private:
//  /*private*/ static OperationsSetupXml* _instance;// = NULL;
  /*private*/ QString operationsFileName;// = "Operations.xml"; // NOI18N
  Logger * log;
  static OperationsSetupXml* _instance;
 };

}
Q_DECLARE_METATYPE(Operations::OperationsSetupXml)
#endif // OPERATIONSSETUPXML_H
