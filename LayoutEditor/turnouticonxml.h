#ifndef TURNOUTICONXML_H
#define TURNOUTICONXML_H
#include "positionablelabelxml.h"

class TurnoutIcon;
class LIBLAYOUTEDITORSHARED_EXPORT TurnoutIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TurnoutIconXml(QObject *parent = 0);
 ~TurnoutIconXml() {}
 TurnoutIconXml(const TurnoutIconXml&) : PositionableLabelXml() {}
    static /*final*/ QMap<QString,QString>* _nameMap;// = new QMap<QString,QString>();
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    TurnoutIcon* getIcon();

signals:

public slots:
private:
 Logger* log;
 /*private*/ NamedIcon* loadTurnoutIcon(QString state, int rotation, TurnoutIcon* l, QDomElement element, QString name, Editor* ed);
 TurnoutIcon* l;

};
Q_DECLARE_METATYPE(TurnoutIconXml)
#endif // TURNOUTICONXML_H
