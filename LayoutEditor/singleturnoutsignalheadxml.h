#ifndef SINGLETURNOUTSIGNALHEADXML_H
#define SINGLETURNOUTSIGNALHEADXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"
#include "namedbeanhandle.h"

class Turnout;
class SingleTurnoutSignalHeadXML : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit SingleTurnoutSignalHeadXML(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*private*/ int loadAppearance(QDomNodeList l, QString state);
    NamedBeanHandle<Turnout*>* loadTurnout(/*QObject o*/QDomElement e);
    /*public*/ void load(QDomElement element, QObject* o)throw (Exception);


signals:

public slots:
private:
    /*private*/ QString getSignalColour(int mAppearance);
    /*private*/ int getIntFromColour(QString colour);
    Logger* log;
};

#endif // SINGLETURNOUTSIGNALHEADXML_H
