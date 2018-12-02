#ifndef INTERNALTURNOUTMANAGERXML_H
#define INTERNALTURNOUTMANAGERXML_H
#include "abstractturnoutmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT InternalTurnoutManagerXml : public AbstractTurnoutManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit InternalTurnoutManagerXml(QObject *parent = 0);
 ~InternalTurnoutManagerXml() {}
 InternalTurnoutManagerXml(const InternalTurnoutManagerXml&) : AbstractTurnoutManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement turnouts);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ bool load(QDomElement turnouts) throw (Exception);

signals:

public slots:
private:
 Logger* log;
};
Q_DECLARE_METATYPE(InternalTurnoutManagerXml)
#endif // INTERNALTURNOUTMANAGERXML_H
