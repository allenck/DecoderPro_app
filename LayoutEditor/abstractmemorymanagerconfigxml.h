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
    ~AbstractMemoryManagerConfigXML()override;
    /*public*/ QDomElement store(QObject* o)override;
    /*abstract*/ /*public*/ virtual void setStoreElementClass(QDomElement memories) = 0;
    /*public*/ bool load(QDomElement sharedMemories, QDomElement perNodeMemories) =0;
    /*public*/ void loadMemories(QDomElement memories);
    /*public*/ int loadOrder() const override;
    void loadValue(QDomElement memory, Memory* m);

signals:

public slots:
private:
    Logger* log;
};

#endif // ABSTRACTMEMORYMANAGERCONFIGXML_H
