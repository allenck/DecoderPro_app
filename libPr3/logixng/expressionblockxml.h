#ifndef EXPRESSIONBLOCKXML_H
#define EXPRESSIONBLOCKXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionBlockXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionBlockXml(QObject *parent = nullptr);
    ~ExpressionBlockXml() {}
    ExpressionBlockXml(const ExpressionBlockXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;


};
Q_DECLARE_METATYPE(ExpressionBlockXml)
#endif // EXPRESSIONBLOCKXML_H
