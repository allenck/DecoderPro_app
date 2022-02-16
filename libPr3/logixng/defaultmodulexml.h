#ifndef DEFAULTMODULEXML_H
#define DEFAULTMODULEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class DefaultModuleXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit DefaultModuleXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode);

 private:
  static Logger* log;
};

#endif // DEFAULTMODULEXML_H
