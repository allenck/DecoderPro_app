#ifndef ANALOGACTIONMEMORYXML_H
#define ANALOGACTIONMEMORYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AnalogActionMemoryXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit AnalogActionMemoryXml(QObject *parent = nullptr);
  ~AnalogActionMemoryXml() {}
  AnalogActionMemoryXml(const AnalogActionMemoryXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(AnalogActionMemoryXml)
#endif // ANALOGACTIONMEMORYXML_H
