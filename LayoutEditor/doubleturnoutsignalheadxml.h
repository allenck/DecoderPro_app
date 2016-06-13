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
    /*public*/ DoubleTurnoutSignalHeadXml(QObject* parent = 0);
    /*public*/ QDomElement store(QObject* o);
    QDomElement addTurnoutElement(NamedBeanHandle<Turnout*>* to, QString which);
    QDomElement addTurnoutElement(Turnout* to);
    /*public*/ bool load(QDomElement element) throw (Exception);
    NamedBeanHandle<Turnout*>* loadTurnout(QDomElement e);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
private:
    Logger * log;

};

#endif // DOUBLETURNOUTSIGNALHEADXML_H
