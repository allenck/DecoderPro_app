#ifndef ROSTERCONFIGPANEXML_H
#define ROSTERCONFIGPANEXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT RosterConfigPaneXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 explicit RosterConfigPaneXml(QObject *parent = 0);
 ~RosterConfigPaneXml() {}
 RosterConfigPaneXml(const RosterConfigPaneXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
  /*public*/ bool load(QDomElement element) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
  private:
  Logger* log;

};
Q_DECLARE_METATYPE(RosterConfigPaneXml)
#endif // ROSTERCONFIGPANEXML_H
