#ifndef MANAGERDEFAULTSCONFIGPANEXML_H
#define MANAGERDEFAULTSCONFIGPANEXML_H

#include <abstractxmladapter.h>
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT ManagerDefaultsConfigPaneXml : public AbstractXmlAdapter

{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ManagerDefaultsConfigPaneXml(QObject *parent = 0);
    ~ManagerDefaultsConfigPaneXml() {}
    ManagerDefaultsConfigPaneXml(const ManagerDefaultsConfigPaneXml&) :AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement e) throw (Exception);
    /*public*/ void load(QDomElement e, QObject* o) throw (Exception);

signals:

public slots:

};
Q_DECLARE_METATYPE(ManagerDefaultsConfigPaneXml)
#endif // MANAGERDEFAULTSCONFIGPANEXML_H
