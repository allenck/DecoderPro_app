#ifndef DEFAULTSTRINGACTIONMANAGERXML_H
#define DEFAULTSTRINGACTIONMANAGERXML_H

#include "abstractmanagerxml.h"
#include "threadingutil.h"
#include "jmriconfigurationmanager.h"
#include "instancemanager.h"
#include "defaultstringactionmanager.h"

class DefaultStringActionManagerXml : public AbstractManagerXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultStringActionManagerXml(QObject *parent = nullptr);
  ~DefaultStringActionManagerXml() {}
  DefaultStringActionManagerXml(const DefaultStringActionManagerXml&) : AbstractManagerXml() {}
  /*public*/  QDomElement store(QObject *o);
  /*public*/  void setStoreElementClass(QDomElement actions);
  /*public*/  bool load(QDomElement sharedAction, QDomElement perNodeAction);
  /*public*/  void loadActions(QDomElement actions);

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<QString, Class/*<?>*/*> xmlClasses = QMap<QString, Class/*<?>*/*>();
  /*public*/  int loadOrder()const override;

 protected:
  /*protected*/ void replaceActionManager();

};
Q_DECLARE_METATYPE(DefaultStringActionManagerXml)

class DSA_ThreadingUtil : public ThreadAction
{
 Q_OBJECT
 public:
  void run()
  {
   // register new one with InstanceManager
   DefaultStringActionManager* pManager = DefaultStringActionManager::instance();
   InstanceManager::store(pManager, "StringActionManager");
   // register new one for configuration
   ConfigureManager* cmOD = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
   if (cmOD != nullptr) {
       cmOD->registerConfig(pManager, Manager::LOGIXNG_STRING_ACTIONS);
   }

  }
};
#endif // DEFAULTSTRINGACTIONMANAGERXML_H
