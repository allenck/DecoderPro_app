#ifndef POSITIONABLEPOLYGONXML_H
#define POSITIONABLEPOLYGONXML_H
#include "positionableshapexml.h"

class PositionablePolygon;
class PositionablePolygonXml : public PositionableShapeXml
{
 Q_OBJECT
public:
 Q_INVOKABLE PositionablePolygonXml();
 ~PositionablePolygonXml() {}
 PositionablePolygonXml(const PositionablePolygonXml&) : PositionableShapeXml() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ void load(QDomElement element, QObject* o) throw(Exception);

private:
 /*private*/ QDomElement storeVertex(int type, QVector<float>* coord);

protected:
 /*protected*/ QDomElement storePath(PositionablePolygon* p);

};
Q_DECLARE_METATYPE(PositionablePolygonXml)
#endif // POSITIONABLEPOLYGONXML_H
