#ifndef DEFAULTMEMORYMANAGERTEST_H
#define DEFAULTMEMORYMANAGERTEST_H
#include "abstractprovidingmemorymanagertestbase.h"

class DefaultMemoryManagerTest : public AbstractProvidingMemoryManagerTestBase
{
 Q_OBJECT
public:
 DefaultMemoryManagerTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

public slots:
 /*public*/ void testIMthrows();
 /*public*/ void testBlankThrows();
 /*public*/ void testCreatesiM();

};

#endif // DEFAULTMEMORYMANAGERTEST_H
