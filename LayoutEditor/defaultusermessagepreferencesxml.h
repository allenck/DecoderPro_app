#ifndef DEFAULTUSERMESSAGEPREFERENCESXML_H
#define DEFAULTUSERMESSAGEPREFERENCESXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT DefaultUserMessagePreferencesXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    explicit DefaultUserMessagePreferencesXml(QObject *parent = 0);
    ~DefaultUserMessagePreferencesXml() {}
    DefaultUserMessagePreferencesXml(const DefaultUserMessagePreferencesXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ void setStoreElementClass(QDomElement messages);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ bool load(QDomElement messages) throw (Exception);

signals:

public slots:
private:
    Logger* log;
};

#endif // DEFAULTUSERMESSAGEPREFERENCESXML_H
