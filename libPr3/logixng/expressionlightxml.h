#ifndef EXPRESSIONLIGHTXML_H
#define EXPRESSIONLIGHTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionLightXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit ExpressionLightXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};

#endif // EXPRESSIONLIGHTXML_H
