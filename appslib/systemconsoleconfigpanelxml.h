#ifndef SYSTEMCONSOLECONFIGPANELXML_H
#define SYSTEMCONSOLECONFIGPANELXML_H
#include "abstractxmladapter.h"
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT SystemConsoleConfigPanelXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 explicit SystemConsoleConfigPanelXml(QObject *parent = 0);
 ~SystemConsoleConfigPanelXml() {}
 SystemConsoleConfigPanelXml(const SystemConsoleConfigPanelXml&) : AbstractXmlAdapter() {}
 /*public*/  QDomElement store(QObject* o);
 /*public*/  bool loadDeferred();
 /*public*/  bool load(QDomElement e) throw(Exception);
 /*public*/  void load(QDomElement element, QObject* o) throw(Exception);

signals:

public slots:
private:
 Logger* log;

};
Q_DECLARE_METATYPE(SystemConsoleConfigPanelXml)
#endif // SYSTEMCONSOLECONFIGPANELXML_H
