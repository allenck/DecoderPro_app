#ifndef CONTROLPANELEDITORXML_H
#define CONTROLPANELEDITORXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class Editor;
class NamedIcon;
class LIBLAYOUTEDITORSHARED_EXPORT ControlPanelEditorXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ControlPanelEditorXml(QObject *parent = 0);
    ~ControlPanelEditorXml() override;
 ControlPanelEditorXml(const ControlPanelEditorXml&) :AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o) ;
    /*public*/ void load(QDomElement element, QObject* o)throw (Exception)  override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode)throw (JmriConfigureXmlException) override ;
    /*public*/ int loadOrder() const override;
 /*public*/ QDomElement storeIcon(QString elemName, NamedIcon* icon);
 /*public*/ NamedIcon* loadIcon(QString key, QDomElement element, Editor* ed);

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(ControlPanelEditorXml)
#endif // CONTROLPANELEDITORXML_H
