#ifndef ABSTRACTSIGNALHEADMANAGERXML_H
#define ABSTRACTSIGNALHEADMANAGERXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT AbstractSignalHeadManagerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AbstractSignalHeadManagerXml(QObject *parent = 0);
    ~AbstractSignalHeadManagerXml() override;
 AbstractSignalHeadManagerXml(const AbstractSignalHeadManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ void setStoreElementClass(QDomElement turnouts);
    /*public*/ bool load(QDomElement shared, QDomElement pernode)  throw (Exception) override;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    /*public*/ void loadSignalHeads(QDomElement shared, QDomElement perNode) ;
    /*protected*/ void replaceSignalHeadManager();
    /*public*/ int loadOrder() const override;
signals:

public slots:
private:
Logger* log;
};
Q_DECLARE_METATYPE(AbstractSignalHeadManagerXml)
#endif // ABSTRACTSIGNALHEADMANAGERXML_H
