#ifndef DEFAULTFEMALEANALOGACTIONSOCKETTEST_H
#define DEFAULTFEMALEANALOGACTIONSOCKETTEST_H
#include "femalesockettestbase.h"

class Memory;
class MyAnalogActionMemory;

class DefaultFemaleAnalogActionSocketTest : public FemaleSocketTestBase
{
    Q_OBJECT
public:
    DefaultFemaleAnalogActionSocketTest(QObject* parent = nullptr);

private:
    /*private*/ QString _memorySystemName;
    /*private*/ Memory* _memory;
    /*private*/ MyAnalogActionMemory* _action;

};

#endif // DEFAULTFEMALEANALOGACTIONSOCKETTEST_H
