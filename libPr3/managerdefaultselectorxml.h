#ifndef MANAGERDEFAULTSELECTORXML_H
#define MANAGERDEFAULTSELECTORXML_H
#include "abstractxmladapter.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ManagerDefaultSelectorXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    explicit ManagerDefaultSelectorXml(QObject *parent = 0);
    ~ManagerDefaultSelectorXml() {}
    ManagerDefaultSelectorXml(const ManagerDefaultSelectorXml&) :AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o) /*throw (Exception)*/;
    /*public*/ bool load(QDomElement e) /*throw (Exception)*/;
    /*public*/ void load(QDomElement element, QObject* o) /*throw (Exception)*/;

signals:

public slots:

};
Q_DECLARE_METATYPE(ManagerDefaultSelectorXml)
#endif // MANAGERDEFAULTSELECTORXML_H
