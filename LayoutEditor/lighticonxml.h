#ifndef LIGHTICONXML_H
#define LIGHTICONXML_H
#include "positionablelabelxml.h"

class LightIcon;
class LightIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit LightIconXml(QObject *parent = 0);
 ~LightIconXml() {}
 LightIconXml(const LightIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
LightIcon* getIcon();
signals:

public slots:
private:
 Logger* log;
 LightIcon* l;
};
Q_DECLARE_METATYPE(LightIconXml)
#endif // LIGHTICONXML_H
