#ifndef ANALOGEXPRESSIONCONSTANTXML_H
#define ANALOGEXPRESSIONCONSTANTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AnalogExpressionConstantXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit AnalogExpressionConstantXml(QObject *parent = nullptr);
  ~AnalogExpressionConstantXml() {}
  AnalogExpressionConstantXml(const AnalogExpressionConstantXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException */override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(AnalogExpressionConstantXml)
#endif // ANALOGEXPRESSIONCONSTANTXML_H
