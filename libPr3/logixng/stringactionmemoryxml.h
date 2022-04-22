#ifndef STRINGACTIONMEMORYXML_H
#define STRINGACTIONMEMORYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class StringActionMemoryXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit StringActionMemoryXml(QObject *parent = nullptr);
  ~StringActionMemoryXml() {}
  StringActionMemoryXml(const StringActionMemoryXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;
};
Q_DECLARE_METATYPE(StringActionMemoryXml)
#endif // STRINGACTIONMEMORYXML_H
