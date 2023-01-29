#ifndef EXPRESSIONENTRYEXITXML_H
#define EXPRESSIONENTRYEXITXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionEntryExitXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE ExpressionEntryExitXml(QObject* parent =nullptr);
  ~ExpressionEntryExitXml() {}
  ExpressionEntryExitXml(const ExpressionEntryExitXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(ExpressionEntryExitXml)
#endif // EXPRESSIONENTRYEXITXML_H
