#ifndef PROGRAMMERCONFIGPANEXML_H
#define PROGRAMMERCONFIGPANEXML_H

#include "abstractxmladapter.h"
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT ProgrammerConfigPaneXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ProgrammerConfigPaneXml(QObject *parent = 0);
    ~ProgrammerConfigPaneXml() {}
    ProgrammerConfigPaneXml(const ProgrammerConfigPaneXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:
private:
    Logger * log;
public slots:

};

#endif // PROGRAMMERCONFIGPANEXML_H
