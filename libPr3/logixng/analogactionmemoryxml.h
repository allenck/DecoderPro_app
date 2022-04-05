#ifndef ANALOGACTIONMEMORYXML_H
#define ANALOGACTIONMEMORYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AnalogActionMemoryXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit AnalogActionMemoryXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

};

#endif // ANALOGACTIONMEMORYXML_H
