#ifndef LAYOUTEDITORXML_H
#define LAYOUTEDITORXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LayoutEditorXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit LayoutEditorXml(QObject *parent = 0);
 ~LayoutEditorXml() {}
 LayoutEditorXml(const LayoutEditorXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
 /*public*/ int loadOrder();

signals:

public slots:
private:
 Logger* log;
};
Q_DECLARE_METATYPE(LayoutEditorXml)
#endif // LAYOUTEDITORXML_H
