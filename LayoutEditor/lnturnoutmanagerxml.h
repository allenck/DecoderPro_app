#ifndef LNTURNOUTMANAGERXML_H
#define LNTURNOUTMANAGERXML_H
#include "abstractturnoutmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LnTurnoutManagerXml : public AbstractTurnoutManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LnTurnoutManagerXml(QObject *parent = 0);
 ~LnTurnoutManagerXml() {}
 LnTurnoutManagerXml(const LnTurnoutManagerXml&) : AbstractTurnoutManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement turnouts) ;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ bool load(QDomElement turnouts) throw (Exception);

signals:

public slots:
private:
 Logger* log;
};
Q_DECLARE_METATYPE(LnTurnoutManagerXml)
#endif // LNTURNOUTMANAGERXML_H
