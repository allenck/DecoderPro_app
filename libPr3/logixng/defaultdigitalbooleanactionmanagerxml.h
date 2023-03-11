#ifndef DEFAULTDIGITALBOOLEANACTIONMANAGERXML_H
#define DEFAULTDIGITALBOOLEANACTIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include "jmriconfigurationmanager.h"
#include "threadingutil.h"
#include "instancemanager.h"
#include "defaultdigitalbooleanactionmanager.h"

class DefaultDigitalBooleanActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultDigitalBooleanActionManagerXml(QObject *parent = nullptr);
  ~DefaultDigitalBooleanActionManagerXml() {}
  DefaultDigitalBooleanActionManagerXml(const DefaultDigitalBooleanActionManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement actions);
  /*public*/  bool load(QDomElement sharedAction, QDomElement perNodeAction)override;
  /*public*/  void loadActions(QDomElement actions);

  /*public*/  int loadOrder()const override;

 private:
  static Logger* log;
 private:
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceActionManager();

};
Q_DECLARE_METATYPE(DefaultDigitalBooleanActionManagerXml)

class DDBAM_ThreadingUtil : public ThreadAction
{
  Q_OBJECT
 public:
  DDBAM_ThreadingUtil() {}
  void run()
  {
   // register new one with InstanceManager
   DefaultDigitalBooleanActionManager* pManager = DefaultDigitalBooleanActionManager::instance();
   InstanceManager::store(pManager, "DigitalBooleanActionManager");
   // register new one for configuration
   ConfigureManager* cmOD = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
   if (cmOD != nullptr) {
       cmOD->registerConfig(pManager, Manager::LOGIXNG_DIGITAL_BOOLEAN_ACTIONS);
   }

  }

};
#endif // DEFAULTDIGITALBOOLEANACTIONMANAGERXML_H
