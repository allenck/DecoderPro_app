#ifndef DEFAULTDIGITALACTIONMANAGERXML_H
#define DEFAULTDIGITALACTIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include <QMainWindow>
#include "threadingutil.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "jmriconfigurationmanager.h"


class DefaultDigitalActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultDigitalActionManagerXml(QObject *parent = nullptr);
  ~DefaultDigitalActionManagerXml() {}
  DefaultDigitalActionManagerXml(const DefaultDigitalActionManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement actions);
  /*public*/  bool load(QDomElement sharedAction, QDomElement perNodeAction)override;
  /*public*/  void loadActions(QDomElement actions);
  /*public*/  int loadOrder() const override;

 private:
  static Logger* log;
  /*private*/ /*final*/QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();

 protected:
  /*protected*/ void replaceActionManager();

};
Q_DECLARE_METATYPE(DefaultDigitalActionManagerXml)

class DDAM_ThreadingUtil : public ThreadAction
{
  Q_OBJECT
 public:
  DDAM_ThreadingUtil() {}
  void run()
  {
   // register new one with InstanceManager
   DefaultDigitalActionManager* pManager = DefaultDigitalActionManager::instance();
   InstanceManager::store(pManager, "DigitalActionManager");
   // register new one for configuration
   ConfigureManager* cmOD = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
   if (cmOD != nullptr) {
       cmOD->registerConfig(pManager, Manager::LOGIXNG_DIGITAL_ACTIONS);
   }

  }
};
#endif // DEFAULTDIGITALACTIONMANAGERXML_H
