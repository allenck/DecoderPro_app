#ifndef EXPRESSIONSIGNALMASTXML_H
#define EXPRESSIONSIGNALMASTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionSignalMastXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ExpressionSignalMastXml(QObject *parent = nullptr);
    ~ExpressionSignalMastXml() {}
    ExpressionSignalMastXml(const ExpressionSignalMastXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;

private:
    static Logger* log;
};
Q_DECLARE_METATYPE(ExpressionSignalMastXml)
#endif // EXPRESSIONSIGNALMASTXML_H
