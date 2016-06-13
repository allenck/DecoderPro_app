#ifndef POSITIONABLERECTANGLEXML_H
#define POSITIONABLERECTANGLEXML_H
#include "positionableshapexml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LIBLAYOUTEDITORSHARED_EXPORT PositionableRectangleXml : public PositionableShapeXml
{
    Q_OBJECT
public:
    explicit PositionableRectangleXml(QObject *parent = 0);
 ~PositionableRectangleXml() {}
 PositionableRectangleXml(const PositionableRectangleXml&) : PositionableShapeXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
signals:

public slots:
private:
    Logger * log;
};
Q_DECLARE_METATYPE(PositionableRectangleXml)
#endif // POSITIONABLERECTANGLEXML_H
