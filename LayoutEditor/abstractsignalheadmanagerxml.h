#ifndef ABSTRACTSIGNALHEADMANAGERXML_H
#define ABSTRACTSIGNALHEADMANAGERXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT AbstractSignalHeadManagerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit AbstractSignalHeadManagerXml(QObject *parent = 0);
    ~AbstractSignalHeadManagerXml();
 AbstractSignalHeadManagerXml(const AbstractSignalHeadManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ void setStoreElementClass(QDomElement turnouts);
    /*public*/ bool load(QDomElement signalheads)  throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ void loadSignalHeads(QDomElement signalheads) ;
    /*protected*/ void replaceSignalHeadManager();
    /*public*/ int loadOrder();
signals:

public slots:
private:
Logger* log;
};
Q_DECLARE_METATYPE(AbstractSignalHeadManagerXml)
#endif // ABSTRACTSIGNALHEADMANAGERXML_H
