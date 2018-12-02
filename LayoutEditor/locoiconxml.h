#ifndef LOCOICONXML_H
#define LOCOICONXML_H
#include "positionablelabelxml.h"

class LIBLAYOUTEDITORSHARED_EXPORT LocoIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LocoIconXml(QObject *parent = 0);
 ~LocoIconXml() {}
 LocoIconXml(const LocoIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
private:
 Logger* log;
};
Q_DECLARE_METATYPE(LocoIconXml)
#endif // LOCOICONXML_H
