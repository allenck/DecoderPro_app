#ifndef SLIPTURNOUTICONXML_H
#define SLIPTURNOUTICONXML_H
#include "positionablelabelxml.h"

class SlipTurnoutIcon;
class SlipTurnoutIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit SlipTurnoutIconXml(QObject *parent = 0);
 ~SlipTurnoutIconXml() {}
 SlipTurnoutIconXml(const SlipTurnoutIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    QDomElement storeIcon(QString elemName, NamedIcon* icon, QString text);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
 private:
    /*private*/ QString loadTurnout(QDomElement element, QString turn);
    /*private*/ void loadTurnoutIcon(QString state, int rotation, SlipTurnoutIcon* l,
                                     QDomElement element, Editor* ed);
 Logger* log;
};

#endif // SLIPTURNOUTICONXML_H
