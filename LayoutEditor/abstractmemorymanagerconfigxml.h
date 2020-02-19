#ifndef ABSTRACTMEMORYMANAGERCONFIGXML_H
#define ABSTRACTMEMORYMANAGERCONFIGXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class Memory;
class LIBLAYOUTEDITORSHARED_EXPORT AbstractMemoryManagerConfigXML : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit AbstractMemoryManagerConfigXML(QObject *parent = 0);
    ~AbstractMemoryManagerConfigXML();
    /*public*/ QDomElement store(QObject* o);
    /*abstract*/ /*public*/ virtual void setStoreElementClass(QDomElement memories) = 0;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*abstract*/ /*public*/ virtual bool load(QDomElement sharedMemories, QDomElement perNodeMemories) throw (JmriConfigureXmlException) = 0;
    /*public*/ void loadMemories(QDomElement memories);
    /*public*/ int loadOrder();
    void loadValue(QDomElement memory, Memory* m);

signals:

public slots:
private:
    Logger* log;
};

#endif // ABSTRACTMEMORYMANAGERCONFIGXML_H
