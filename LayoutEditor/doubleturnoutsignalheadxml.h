#ifndef DOUBLETURNOUTSIGNALHEADXML_H
#define DOUBLETURNOUTSIGNALHEADXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"
#include "namedbeanhandlemanager.h"

class Turnout;
class DoubleTurnoutSignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    //explicit DoubleTurnoutSignalHeadXml(QObject *parent = 0);
    Q_INVOKABLE /*public*/ DoubleTurnoutSignalHeadXml(QObject* parent = 0);
    ~DoubleTurnoutSignalHeadXml() override {}
    DoubleTurnoutSignalHeadXml(const DoubleTurnoutSignalHeadXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    QDomElement addTurnoutElement(NamedBeanHandle<Turnout*>* to, QString which);
    QDomElement addTurnoutElement(Turnout* to);
    /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException) override;
    NamedBeanHandle<Turnout*>* loadTurnout(QDomElement e);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;

signals:

public slots:
private:
    Logger * log;

};
Q_DECLARE_METATYPE(DoubleTurnoutSignalHeadXml)
#endif // DOUBLETURNOUTSIGNALHEADXML_H
