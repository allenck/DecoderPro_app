#ifndef ABSTRACTPROVIDINGMEMORYMANAGERTESTBASE_H
#define ABSTRACTPROVIDINGMEMORYMANAGERTESTBASE_H

#include "abstractmanagertestbase.h"

class Logger;
class MemoryManager;
class AbstractProvidingMemoryManagerTestBase : public AbstractManagerTestBase
{
  Q_OBJECT
public:
    AbstractProvidingMemoryManagerTestBase();
    virtual ~AbstractProvidingMemoryManagerTestBase() {}
    /*public*/ void testRegisterDuplicateSystemName(MemoryManager* m, QString s1, QString s2)
            /*throw (PropertyVetoException, NoSuchFieldException,
            NoSuchFieldException IllegalArgumentException, IllegalAccessException)*/;


public slots:
    /*public*/ void testProvideEmpty() /*throw (IllegalArgumentException)*/;
    /*public*/ void testRegisterDuplicateSystemName() /*throw (PropertyVetoException, NoSuchFieldException,
                    NoSuchFieldException, IllegalArgumentException, IllegalAccessException )*/;

private:
    static Logger* log;

};

#endif // ABSTRACTPROVIDINGMEMORYMANAGERTESTBASE_H
