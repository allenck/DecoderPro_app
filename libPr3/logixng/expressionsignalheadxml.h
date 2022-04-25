#ifndef EXPRESSIONSIGNALHEADXML_H
#define EXPRESSIONSIGNALHEADXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionSignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit ExpressionSignalHeadXml(QObject *parent = nullptr);
  ~ExpressionSignalHeadXml() {}
  ExpressionSignalHeadXml(const ExpressionSignalHeadXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(ExpressionSignalHeadXml)
#endif // EXPRESSIONSIGNALHEADXML_H
