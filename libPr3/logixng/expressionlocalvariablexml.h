#ifndef EXPRESSIONLOCALVARIABLEXML_H
#define EXPRESSIONLOCALVARIABLEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionLocalVariableXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ExpressionLocalVariableXml(QObject *parent = nullptr);
  ~ExpressionLocalVariableXml() {}
  ExpressionLocalVariableXml(const ExpressionLocalVariableXml&) :AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(ExpressionLocalVariableXml)
#endif // EXPRESSIONLOCALVARIABLEXML_H
