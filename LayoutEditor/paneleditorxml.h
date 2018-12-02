#ifndef PANELEDITORXML_H
#define PANELEDITORXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"


class LIBLAYOUTEDITORSHARED_EXPORT PanelEditorXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PanelEditorXml(QObject *parent = 0);
 ~PanelEditorXml() {}
 PanelEditorXml(const PanelEditorXml&) :AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ int loadOrder();

signals:

public slots:
private:
 Logger* log;
};
Q_DECLARE_METATYPE(PanelEditorXml)
#endif // PANELEDITORXML_H
