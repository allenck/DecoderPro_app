#ifndef SE8CSIGNALHEADXML_H
#define SE8CSIGNALHEADXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "namedbeanhandlemanager.h"

class Turnout;
class SE8cSignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit SE8cSignalHeadXml(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    NamedBeanHandle<Turnout*>* loadTurnout(QDomElement o);

signals:

public slots:
private:
    QDomElement addTurnoutElement(NamedBeanHandle<Turnout*>* to, QString which);
    QDomElement addTurnoutElement(Turnout* to);
    Logger* log;

};

#endif // SE8CSIGNALHEADXML_H
