#ifndef ACTIONSIGNALMASTXML_H
#define ACTIONSIGNALMASTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionSignalMastXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionSignalMastXml(QObject *parent = nullptr);
    ~ActionSignalMastXml() {}
    ActionSignalMastXml(const ActionSignalMastXml&) :AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;

private:
    static Logger* log;
};
Q_DECLARE_METATYPE(ActionSignalMastXml)
#endif // ACTIONSIGNALMASTXML_H
