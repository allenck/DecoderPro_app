#ifndef EXPRESSIONCLOCKXML_H
#define EXPRESSIONCLOCKXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionClockXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionClockXml(QObject *parent = nullptr);
    ~ExpressionClockXml() {}
    ExpressionClockXml(const ExpressionClockXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) override;

private:
    static Logger* log;
};
Q_DECLARE_METATYPE(ExpressionClockXml)
#endif // EXPRESSIONCLOCKXML_H
