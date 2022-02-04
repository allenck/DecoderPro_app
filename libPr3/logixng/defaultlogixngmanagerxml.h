#ifndef DEFAULTLOGIXNGMANAGERXML_H
#define DEFAULTLOGIXNGMANAGERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class DefaultLogixNGManagerXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit DefaultLogixNGManagerXml(QObject *parent = nullptr);
  ~DefaultLogixNGManagerXml() {}
  DefaultLogixNGManagerXml(const DefaultLogixNGManagerXml&) : AbstractNamedBeanManagerConfigXML() {}  /*public*/ QDomElement store(QObject* o) override;
  /*public*/ void setStoreElementClass(QDomElement logixngs);
  /*public*/ bool load(QDomElement sharedLogixNG, QDomElement perNodeLogixNG)override;
  /*public*/ int loadOrder()const override;
  /*public*/ void loadThreads(QDomElement sharedLogixNG);
  /*public*/ void loadLogixNGs(QDomElement sharedLogixNG);
  /*public*/ void loadInitializationTable(QDomElement sharedLogixNG);
  /*public*/ void loadClipboard(QDomElement sharedLogixNG);

 private:
  static Logger* log;

 protected:
  /*protected*/ void replaceLogixNGManager();

};

#endif // DEFAULTLOGIXNGMANAGERXML_H
