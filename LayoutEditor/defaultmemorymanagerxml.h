#ifndef DEFAULTMEMORYMANAGERXML_H
#define DEFAULTMEMORYMANAGERXML_H
#include "abstractmemorymanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT DefaultMemoryManagerXml : public AbstractMemoryManagerConfigXML
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit DefaultMemoryManagerXml(QObject *parent = 0);
 ~DefaultMemoryManagerXml() {}
 DefaultMemoryManagerXml(const DefaultMemoryManagerXml&) : AbstractMemoryManagerConfigXML() {}
 /*public*/ void setStoreElementClass(QDomElement memories) override;
 /*public*/ bool load(QDomElement shareMemories, QDomElement perNodeMemories) throw (JmriConfigureXmlException) override;

signals:

public slots:

};
Q_DECLARE_METATYPE(DefaultMemoryManagerXml)
#endif // DEFAULTMEMORYMANAGERXML_H
