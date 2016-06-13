#ifndef POSITIONABLECIRCLEXML_H
#define POSITIONABLECIRCLEXML_H
#include "positionableshapexml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT PositionableCircleXml : public PositionableShapeXml
{
    Q_OBJECT
public:
    explicit PositionableCircleXml(QObject *parent = 0);
 ~PositionableCircleXml() {}
 PositionableCircleXml(const PositionableCircleXml&) :PositionableShapeXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
signals:

public slots:
private:
    Logger * log;
};
Q_DECLARE_METATYPE(PositionableCircleXml)
#endif // POSITIONABLECIRCLEXML_H
