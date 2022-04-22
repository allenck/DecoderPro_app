#ifndef ANALOGEXPRESSIONMEMORYXML_H
#define ANALOGEXPRESSIONMEMORYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AnalogExpressionMemoryXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit AnalogExpressionMemoryXml(QObject *parent = nullptr);
  ~AnalogExpressionMemoryXml() {}
  AnalogExpressionMemoryXml(const AnalogExpressionMemoryXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(AnalogExpressionMemoryXml)
#endif // ANALOGEXPRESSIONMEMORYXML_H
