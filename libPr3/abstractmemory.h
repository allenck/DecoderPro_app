#ifndef ABSTRACTMEMORY_H
#define ABSTRACTMEMORY_H
//#include "abstractnamedbean.h"
#include "memory.h"

class LIBPR3SHARED_EXPORT AbstractMemory : public Memory
{
public:
    AbstractMemory(QString systemName, QString userName="", QObject* parent = 0);
    /*public*/ virtual QVariant getValue();

    /**
     * Provide a general method for updating the report.
     */
    /*public*/ void setValue(QVariant v);
signals:
    //void propertyChange( QString propertyName, QVariant o, QVariant n);
private:
    // internal data members
    /*private*/ QVariant _current;// = NULL;

};

#endif // ABSTRACTMEMORY_H
