#ifndef LOCONETSYSTEMCONNECTIONMEMOTEST_H
#define LOCONETSYSTEMCONNECTIONMEMOTEST_H
#include "systemconnectionmemotestbase.h"

class LocoNetSystemConnectionMemo;
class LoconetSystemConnectionMemoTest : public SystemConnectionMemoTestBase
{
 Q_OBJECT
public:
 LoconetSystemConnectionMemoTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();


private:
 /*private*/ LocoNetSystemConnectionMemo* memo;

};

#endif // LOCONETSYSTEMCONNECTIONMEMOTEST_H
