#ifndef ACTIONMEMORYTEST_H
#define ACTIONMEMORYTEST_H

#include "abstractdigitalactiontestbase.h"

class ActionMemory;
class Memory;
class ActionMemoryTest : public AbstractDigitalActionTestBase
{
  Q_OBJECT
 public:
  explicit ActionMemoryTest(QObject *parent = nullptr);
  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  LogixNG* getLogixNG()override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot() override;
  /*public*/  NamedBean* createNewBean(QString systemName)override;
  /*public*/  bool addNewSocket()override;
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testGetChild();
  /*public*/  void testSetMemory();
  /*public*/  void testAction();
  /*public*/  void testVetoableChange();
  /*public*/  void testCategory();
  /*public*/  void testShortDescription();
  /*public*/  void testLongDescription();
  /*public*/  void testChild();

 private:
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ ActionMemory* actionMemory;
  /*private*/ Memory* memory;

};

#endif // ACTIONMEMORYTEST_H
