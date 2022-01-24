#ifndef ENGINEMANAGERXML_H
#define ENGINEMANAGERXML_H
#include "operationsxml.h"
#include "appslib_global.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT EngineManagerXml : public OperationsXml, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)
 public:
  Q_INVOKABLE explicit EngineManagerXml(QObject *parent = 0);
  ~EngineManagerXml() {}
  EngineManagerXml(const EngineManagerXml&) : OperationsXml() {}
  /*public*/ void writeFile(QString name) override; //throws java.io.FileNotFoundException, java.io.IOException
  /*public*/ void readFile(QString name) override; //throws org.jdom2.JDOMException, java.io.IOException
  /*public*/ void setOperationsFileName(QString name) override;
  /*public*/ QString getOperationsFileName() override;
  /*public*/ void dispose();
  Q_INVOKABLE  /*public*/ void initialize() override;

 signals:

 public slots:
 private:
//  /*private*/ static EngineManagerXml* _instance;// = null;
  Logger* log;
  /*private*/ QString operationsFileName;// = "OperationsEngineRoster.xml"; // NOI18N
 };
}
Q_DECLARE_METATYPE(Operations::EngineManagerXml)
#endif // ENGINEMANAGERXML_H
