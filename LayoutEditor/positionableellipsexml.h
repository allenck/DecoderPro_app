#ifndef POSITIONABLEELLIPSEXML_H
#define POSITIONABLEELLIPSEXML_H
#include "positionableshapexml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT PositionableEllipseXml : public PositionableShapeXml
{
    Q_OBJECT
public:
    explicit PositionableEllipseXml(QObject *parent = 0);
 ~PositionableEllipseXml() {}
 PositionableEllipseXml(const PositionableEllipseXml&) :PositionableShapeXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element)throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(PositionableEllipseXml)
#endif // POSITIONABLEELLIPSEXML_H
