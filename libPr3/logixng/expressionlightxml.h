#ifndef EXPRESSIONLIGHTXML_H
#define EXPRESSIONLIGHTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionLightXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ExpressionLightXml(QObject *parent = nullptr);
  ~ExpressionLightXml() {}
  ExpressionLightXml(const ExpressionLightXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(ExpressionLightXml)
#endif // EXPRESSIONLIGHTXML_H
