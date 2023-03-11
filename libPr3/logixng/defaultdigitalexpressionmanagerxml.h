#ifndef DEFAULTDIGITALEXPRESSIONMANAGERXML_H
#define DEFAULTDIGITALEXPRESSIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include "threadingutil.h"
#include "jmriconfigurationmanager.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanagerxml.h"
#include "defaultdigitalexpressionmanager.h"


class DefaultDigitalExpressionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultDigitalExpressionManagerXml(QObject *parent = nullptr);
  ~DefaultDigitalExpressionManagerXml() {}
  DefaultDigitalExpressionManagerXml(const DefaultDigitalExpressionManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement expressions);
  /*public*/  bool load(QDomElement sharedExpression, QDomElement perNodeExpression)override;
  /*public*/  void loadExpressions(QDomElement expressions);
  /*public*/  int loadOrder()const override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>>*/*> xmlClasses = QMap<QString, Class/*<?>>*/*>();

 protected:
  /*protected*/ void replaceExpressionManager();

};
Q_DECLARE_METATYPE(DefaultDigitalExpressionManagerXml)

class DDEM_ThreadingUtil : public ThreadAction
{
  Q_OBJECT
 public:
  DDEM_ThreadingUtil() {}
  void run()
  {
   // register new one with InstanceManager
   DefaultDigitalExpressionManager* pManager = DefaultDigitalExpressionManager::instance();
   InstanceManager::store(pManager, "DigitalExpressionManager");
   // register new one for configuration
   ConfigureManager* cmOD = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
   if (cmOD != nullptr) {
       cmOD->registerConfig(pManager, Manager::LOGIXNG_DIGITAL_EXPRESSIONS);
   }

  }
};
#endif // DEFAULTDIGITALEXPRESSIONMANAGERXML_H
