#ifndef LAYOUTEDITORXML_H
#define LAYOUTEDITORXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LayoutEditorXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit LayoutEditorXml(QObject *parent = 0);
 ~LayoutEditorXml() override {}
 LayoutEditorXml(const LayoutEditorXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o) override;
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception) override;
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
 /*public*/ int loadOrder() const  override;

signals:

public slots:
private:
 Logger* log;
 /*private*/ bool getBooleanValue(QString txt);
};
Q_DECLARE_METATYPE(LayoutEditorXml)
#endif // LAYOUTEDITORXML_H
