#ifndef CREATEBUTTONPANELXML_H
#define CREATEBUTTONPANELXML_H

#include "abstractxmladapter.h"
#include "appslib_global.h"


class APPSLIBSHARED_EXPORT CreateButtonPanelXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    explicit CreateButtonPanelXml(QObject *parent = 0);
 ~CreateButtonPanelXml() {}
 CreateButtonPanelXml(const CreateButtonPanelXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement /*e*/)  throw (Exception);
    /*public*/ void load(QDomElement /*element*/, QObject* /*o*/)throw (Exception);

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(CreateButtonPanelXml)
#endif // CREATEBUTTONPANELXML_H
