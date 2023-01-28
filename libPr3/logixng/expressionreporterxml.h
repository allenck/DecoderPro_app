#ifndef EXPRESSIONREPORTERXML_H
#define EXPRESSIONREPORTERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionReporterXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  ExpressionReporterXml(QObject* parent = nullptr);
  ~ExpressionReporterXml() {}
  ExpressionReporterXml(const ExpressionReporterXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/   QDomElement store(QObject* o)override;
  /*public*/  bool load( QDomElement shared,  QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ExpressionReporterXml)
#endif // EXPRESSIONREPORTERXML_H
