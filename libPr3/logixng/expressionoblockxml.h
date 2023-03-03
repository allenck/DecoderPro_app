#ifndef EXPRESSIONOBLOCKXML_H
#define EXPRESSIONOBLOCKXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionOBlockXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionOBlockXml(QObject *parent = nullptr);
    ~ExpressionOBlockXml() {}
    ExpressionOBlockXml(const ExpressionOBlockXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(ExpressionOBlockXml)
#endif // EXPRESSIONOBLOCKXML_H
