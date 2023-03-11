#ifndef DEFAULTANALOGACTIONMANAGERXML_H
#define DEFAULTANALOGACTIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include <QMainWindow>
#include "threadingutil.h"
#include "instancemanager.h"
#include "defaultanalogactionmanager.h"
#include "jmriconfigurationmanager.h"

class DefaultAnalogActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT

 public:
  Q_INVOKABLE explicit DefaultAnalogActionManagerXml(QObject *parent = nullptr);
  ~DefaultAnalogActionManagerXml() {}
  DefaultAnalogActionManagerXml(const DefaultAnalogActionManagerXml&) : AbstractManagerXml(){}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement actions);
  /*public*/  void loadActions(QDomElement actions);
  /*public*/ bool load(QDomElement sharedAction, QDomElement perNodeAction)override;
  /*public*/  int loadOrder() const override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceActionManager();

};
Q_DECLARE_METATYPE(DefaultAnalogActionManagerXml)

class DAAM_ThreadingUtil : public ThreadAction
{
  Q_OBJECT
  DefaultAnalogActionManagerXml* daam;
 public:
  DAAM_ThreadingUtil(DefaultAnalogActionManagerXml* daam){
   this->daam = daam;
  }
  void run()
  {
   // register new one with InstanceManager
   DefaultAnalogActionManager* pManager = DefaultAnalogActionManager::instance();
   InstanceManager::store(pManager, "AnalogActionManager");
   // register new one for configuration
   ConfigureManager* cmOD = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
   if (cmOD != nullptr) {
       cmOD->registerConfig(pManager, Manager::LOGIXNG_ANALOG_ACTIONS);
   }

  }
};
#endif // DEFAULTANALOGACTIONMANAGERXML_H
