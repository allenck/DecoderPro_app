#ifndef EXPRESSIONMEMORYXML_H
#define EXPRESSIONMEMORYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionMemoryXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit ExpressionMemoryXml(QObject *parent = nullptr);
  ~ExpressionMemoryXml(){}
  ExpressionMemoryXml(const ExpressionMemoryXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException */override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ExpressionMemoryXml)
#endif // EXPRESSIONMEMORYXML_H
