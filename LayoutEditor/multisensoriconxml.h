#ifndef MULTISENSORICONXML_H
#define MULTISENSORICONXML_H
#include "positionablelabelxml.h"
#include "liblayouteditor_global.h"

class MultiSensorIcon;
class LIBLAYOUTEDITORSHARED_EXPORT MultiSensorIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
 Q_INVOKABLE explicit MultiSensorIconXml(QObject *parent = 0);
 ~MultiSensorIconXml() {}
 MultiSensorIconXml(const MultiSensorIconXml&) : PositionableLabelXml() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    MultiSensorIcon* getIcon();
signals:

public slots:
private:
 Logger* log;
 /*private*/ NamedIcon* loadSensorIcon(QString state, int rotation, MultiSensorIcon* l, QDomElement element, Editor* ed);
MultiSensorIcon* l;
};
Q_DECLARE_METATYPE(MultiSensorIconXml)
#endif // MULTISENSORICONXML_H
