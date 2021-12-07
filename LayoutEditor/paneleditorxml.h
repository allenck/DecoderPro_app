#ifndef PANELEDITORXML_H
#define PANELEDITORXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"


class LIBLAYOUTEDITORSHARED_EXPORT PanelEditorXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PanelEditorXml(QObject *parent = 0);
 ~PanelEditorXml() override {}
 PanelEditorXml(const PanelEditorXml&) :AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception) override;
    /*public*/ int loadOrder() const override;

signals:

public slots:
private:
 Logger* log;
};
Q_DECLARE_METATYPE(PanelEditorXml)
#endif // PANELEDITORXML_H
