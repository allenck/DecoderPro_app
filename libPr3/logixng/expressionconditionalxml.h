#ifndef EXPRESSIONCONDITIONALXML_H
#define EXPRESSIONCONDITIONALXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionConditionalXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionConditionalXml(QObject *parent = nullptr);
    ~ExpressionConditionalXml() {}
    ExpressionConditionalXml(const ExpressionConditionalXml&) :AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;

};
Q_DECLARE_METATYPE(ExpressionConditionalXml)
#endif // EXPRESSIONCONDITIONALXML_H
