#ifndef JMRIXCONFIGPANEXML_H
#define JMRIXCONFIGPANEXML_H
#include "abstractxmladapter.h"
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT JmrixConfigPaneXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 explicit JmrixConfigPaneXml(QObject *parent = 0);
 ~JmrixConfigPaneXml() {}
 JmrixConfigPaneXml(const JmrixConfigPaneXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement e)  throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:

private:
 Logger* log;

};

#endif // JMRIXCONFIGPANEXML_H
