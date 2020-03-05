#ifndef LAYOUTTURNOUTXML_H
#define LAYOUTTURNOUTXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LayoutTurnoutXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit LayoutTurnoutXml(QObject *parent = 0);
 ~LayoutTurnoutXml() override{}
 LayoutTurnoutXml(const LayoutTurnoutXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o) override;
 /*public*/ bool load(QDomElement element) throw (Exception) override;
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;

signals:

public slots:
private:
 QString getElement(QDomElement el, QString child);
 static Logger* log;

};
Q_DECLARE_METATYPE(LayoutTurnoutXml)
#endif // LAYOUTTURNOUTXML_H
