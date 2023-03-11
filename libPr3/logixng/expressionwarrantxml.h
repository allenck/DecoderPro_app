#ifndef EXPRESSIONWARRANTXML_H
#define EXPRESSIONWARRANTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionWarrantXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionWarrantXml(QObject *parent = nullptr);
    ~ExpressionWarrantXml() {}
    ExpressionWarrantXml(const ExpressionWarrantXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;

};
Q_DECLARE_METATYPE(ExpressionWarrantXml)
#endif // EXPRESSIONWARRANTXML_H
