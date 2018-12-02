#ifndef POSITIONABLEROUNDRECTXML_H
#define POSITIONABLEROUNDRECTXML_H
#include "positionableshapexml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT PositionableRoundRectXml : public PositionableShapeXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PositionableRoundRectXml(QObject *parent = 0);
 ~PositionableRoundRectXml() {}
 PositionableRoundRectXml(const PositionableRoundRectXml&) : PositionableShapeXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(PositionableRoundRectXml)
#endif // POSITIONABLEROUNDRECTXML_H
