#ifndef DEFAULTCONDITIONALNGMANAGERXML_H
#define DEFAULTCONDITIONALNGMANAGERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>
#include "threadingutil.h"
#include "defaultconditionalngmanager.h"
#include "instancemanager.h"
#include "appsconfigurationmanager.h"

class DefaultConditionalNGManagerXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultConditionalNGManagerXml(QObject *parent = nullptr);
  ~DefaultConditionalNGManagerXml() {}
  DefaultConditionalNGManagerXml(const DefaultConditionalNGManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  void setStoreElementClass(QDomElement logixngs);
  /*public*/  bool load(QDomElement sharedConditionalNG, QDomElement perNodeConditionalNG)override;
  /*public*/  void loadConditionalNGs(QDomElement conditionalNGs);
  /*public*/  int loadOrder()const override;

 private:
  static Logger* log;

 protected:
  /*protected*/ void replaceConditionalNGManager();

};
Q_DECLARE_METATYPE(DefaultConditionalNGManagerXml)

class DefaultConditionalNGManagerXml_run1 : public ThreadAction
{
  Q_OBJECT
  DefaultConditionalNGManagerXml* xml;
 public:
  DefaultConditionalNGManagerXml_run1(DefaultConditionalNGManagerXml* xml) {this->xml = xml;}
  void run()
  {
   DefaultConditionalNGManager* pManager = DefaultConditionalNGManager::instance();
   InstanceManager::store(pManager, "ConditionalNG_Manager");
   // register new one for configuration
   ConfigureManager* cmOD = (AppsConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
   if (cmOD != nullptr) {
       cmOD->registerConfig(pManager, Manager::LOGIXNGS);
   }
  }
};

#endif // DEFAULTCONDITIONALNGMANAGERXML_H
