#ifndef WEBBROWSERXML_H
#define WEBBROWSERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class WebBrowserXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit WebBrowserXml(QObject *parent = nullptr);
    ~WebBrowserXml() {}
    WebBrowserXml(const WebBrowserXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o)override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) override;

};
Q_DECLARE_METATYPE(WebBrowserXml)
#endif // WEBBROWSERXML_H
