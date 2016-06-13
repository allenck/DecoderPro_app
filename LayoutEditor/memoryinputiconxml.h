#ifndef MEMORYINPUTICONXML_H
#define MEMORYINPUTICONXML_H
#include "positionablelabelxml.h"
#include "liblayouteditor_global.h"

class MemoryInputIcon;
class LIBLAYOUTEDITORSHARED_EXPORT MemoryInputIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit MemoryInputIconXml(QObject *parent = 0);
 ~MemoryInputIconXml() {}
 MemoryInputIconXml(const MemoryInputIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o)throw (Exception);
    MemoryInputIcon* getIcon();
signals:

public slots:
private:
    Logger* log;
    MemoryInputIcon* l;
};
Q_DECLARE_METATYPE(MemoryInputIconXml)
#endif // MEMORYINPUTICONXML_H
