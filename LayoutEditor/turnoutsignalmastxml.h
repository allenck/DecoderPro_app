#ifndef TURNOUTSIGNALMASTXML_H
#define TURNOUTSIGNALMASTXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT TurnoutSignalMastXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit TurnoutSignalMastXml(QObject *parent = 0);
 ~TurnoutSignalMastXml() {}
 TurnoutSignalMastXml(const TurnoutSignalMastXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
signals:

public slots:
private:
 Logger* log;
};
Q_DECLARE_METATYPE(TurnoutSignalMastXml)
#endif // TURNOUTSIGNALMASTXML_H
