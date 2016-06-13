#ifndef VIRTUALSIGNALMASTXML_H
#define VIRTUALSIGNALMASTXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"

class VirtualSignalMastXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit VirtualSignalMastXml(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o)  throw (Exception);

signals:

public slots:
private:
 Logger* log;
};

#endif // VIRTUALSIGNALMASTXML_H
