#ifndef EXPRESSIONTURNOUTXML_H
#define EXPRESSIONTURNOUTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionTurnoutXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ExpressionTurnoutXml(QObject *parent = nullptr);
  ~ExpressionTurnoutXml() {}
  ExpressionTurnoutXml(const ExpressionTurnoutXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ExpressionTurnoutXml)
#endif // EXPRESSIONTURNOUTXML_H
