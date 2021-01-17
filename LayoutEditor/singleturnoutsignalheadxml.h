#ifndef SINGLETURNOUTSIGNALHEADXML_H
#define SINGLETURNOUTSIGNALHEADXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"
#include "namedbeanhandle.h"

class Turnout;
class SingleTurnoutSignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SingleTurnoutSignalHeadXml(QObject *parent = 0);
    ~SingleTurnoutSignalHeadXml() {}
    SingleTurnoutSignalHeadXml(const SingleTurnoutSignalHeadXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception);
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
Q_DECLARE_METATYPE(SingleTurnoutSignalHeadXml)
#endif // SINGLETURNOUTSIGNALHEADXML_H
