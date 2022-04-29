#ifndef ANALOGEXPRESSIONMEMORYTEST_H
#define ANALOGEXPRESSIONMEMORYTEST_H

#include "abstractanalogexpressiontestbase.h"

class AnalogActionMemory;
class AnalogExpressionMemory;
class Memory;
class AnalogExpressionMemoryTest : public AbstractAnalogExpressionTestBase
{
  Q_OBJECT
 public:
  explicit AnalogExpressionMemoryTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();
  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  LogixNG* getLogixNG() override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot()override;
  /*public*/  NamedBean* createNewBean(QString systemName)override;
  /*public*/  bool addNewSocket()override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testEvaluate();
  /*public*/  void testEvaluateAndAction();
  /*public*/  void testMemory();
  /*public*/  void testRegisterListeners();
  /*public*/  void testVetoableChange() /*throws PropertyVetoException*/;
  /*public*/  void testCategory();
  /*public*/  void testShortDescription();
  /*public*/  void testLongDescription();
  /*public*/  void testChild();

 private:
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ AnalogExpressionMemory* expressionMemory;
  /*private*/ Memory* _memoryOut;
  /*private*/ AnalogActionMemory* actionMemory;

 protected:
  /*protected*/ Memory* _memory;

};

#endif // ANALOGEXPRESSIONMEMORYTEST_H
