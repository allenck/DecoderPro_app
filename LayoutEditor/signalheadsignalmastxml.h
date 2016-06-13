#ifndef SIGNALHEADSIGNALMASTXML_H
#define SIGNALHEADSIGNALMASTXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"


class SignalHeadSignalMast;
class SignalHeadSignalMastXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit SignalHeadSignalMastXml(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
 private:
    Logger* log;
};

#endif // SIGNALHEADSIGNALMASTXML_H
