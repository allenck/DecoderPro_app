#ifndef MEMORYCOMBOICONXML_H
#define MEMORYCOMBOICONXML_H
#include "positionablelabelxml.h"
#include "liblayouteditor_global.h"

class MemoryComboIcon;
class LIBLAYOUTEDITORSHARED_EXPORT MemoryComboIconXml : public PositionableLabelXml
{
    Q_OBJECT
public:
    explicit MemoryComboIconXml(QObject *parent = 0);
 ~MemoryComboIconXml() {}
 MemoryComboIconXml(const MemoryComboIconXml&) : PositionableLabelXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    MemoryComboIcon* getIcon();
signals:

public slots:
private:
    Logger * log;
    MemoryComboIcon* l;
};
Q_DECLARE_METATYPE(MemoryComboIconXml)
#endif // MEMORYCOMBOICONXML_H
