#ifndef DEFAULTUSERMESSAGEPREFERENCESXML_H
#define DEFAULTUSERMESSAGEPREFERENCESXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT DefaultUserMessagePreferencesXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DefaultUserMessagePreferencesXml(QObject *parent = 0);
    ~DefaultUserMessagePreferencesXml() {}
    DefaultUserMessagePreferencesXml(const DefaultUserMessagePreferencesXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ void setStoreElementClass(QDomElement messages);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ bool load(QDomElement shared, QDomElement perNode)throw (JmriConfigureXmlException);

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(DefaultUserMessagePreferencesXml)
#endif // DEFAULTUSERMESSAGEPREFERENCESXML_H
