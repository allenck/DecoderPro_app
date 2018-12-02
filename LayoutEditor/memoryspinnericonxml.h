#ifndef MEMORYSPINNERICONXML_H
#define MEMORYSPINNERICONXML_H
#include "positionablelabelxml.h"
#include "liblayouteditor_global.h"

class MemorySpinnerIcon;
class LIBLAYOUTEDITORSHARED_EXPORT MemorySpinnerIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MemorySpinnerIconXml(QObject *parent = 0);
 ~MemorySpinnerIconXml() {}
 MemorySpinnerIconXml(const MemorySpinnerIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    MemorySpinnerIcon* getIcon();
signals:

public slots:
private:
    Logger* log;
    MemorySpinnerIcon* l;
};
Q_DECLARE_METATYPE(MemorySpinnerIconXml)
#endif // MEMORYSPINNERICONXML_H
