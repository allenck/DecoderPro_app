#ifndef ABSTRACTDEBUGGERMALESOCKETXML_H
#define ABSTRACTDEBUGGERMALESOCKETXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class MaleSocket;
class AbstractDebuggerMaleSocketXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit AbstractDebuggerMaleSocketXml(QObject *parent = nullptr);
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) override;
    /*public*/ bool load(QDomElement maleSocketElement, MaleSocket* maleSocket);

    QString virtual getClass() =0;
};

#endif // ABSTRACTDEBUGGERMALESOCKETXML_H
