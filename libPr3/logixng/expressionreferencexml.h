#ifndef EXPRESSIONREFERENCEXML_H
#define EXPRESSIONREFERENCEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionReferenceXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit ExpressionReferenceXml(QObject *parent = nullptr);
  ~ExpressionReferenceXml() {}
  ExpressionReferenceXml(const ExpressionReferenceXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(ExpressionReferenceXml)
#endif // EXPRESSIONREFERENCEXML_H
