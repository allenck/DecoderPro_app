#ifndef ANALOGEXPRESSIONANALOGIOXML_H
#define ANALOGEXPRESSIONANALOGIOXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AnalogExpressionAnalogIOXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit AnalogExpressionAnalogIOXml(QObject *parent = nullptr);
  ~AnalogExpressionAnalogIOXml() {}
  AnalogExpressionAnalogIOXml(const AnalogExpressionAnalogIOXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(AnalogExpressionAnalogIOXml)
#endif // ANALOGEXPRESSIONANALOGIOXML_H
