#ifndef SIGNALHEADSIGNALMASTXML_H
#define SIGNALHEADSIGNALMASTXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"


class SignalHeadSignalMast;
class SignalHeadSignalMastXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SignalHeadSignalMastXml(QObject *parent = 0);
    ~SignalHeadSignalMastXml()  override{}
    SignalHeadSignalMastXml(const SignalHeadSignalMastXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ bool load(QDomElement element) throw (Exception) override;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;

signals:

public slots:
 private:
    Logger* log;
};
Q_DECLARE_METATYPE(SignalHeadSignalMastXml)
#endif // SIGNALHEADSIGNALMASTXML_H
