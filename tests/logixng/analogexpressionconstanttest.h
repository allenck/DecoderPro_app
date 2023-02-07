#ifndef ANALOGEXPRESSIONCONSTANTTEST_H
#define ANALOGEXPRESSIONCONSTANTTEST_H

#include "abstractanalogexpressiontestbase.h"

class DefaultConditionalNG;
class AnalogExpressionConstant;
class Memory;
class AnalogActionMemory;
class AnalogExpressionConstantTest : public AbstractAnalogExpressionTestBase
{
  Q_OBJECT
 public:
  AnalogExpressionConstantTest();
  Q_INVOKABLE /*public*/  void setUp() /*throws SocketAlreadyConnectedException*/;
  Q_INVOKABLE /*public*/  void tearDown();

  /*public*/  ConditionalNG* getConditionalNG() override;
  /*public*/  LogixNG* getLogixNG() override;
  /*public*/  MaleSocket* getConnectableChild()  override;
  /*public*/  QString getExpectedPrintedTree() override;
  /*public*/  QString getExpectedPrintedTreeFromRoot() override;
  /*public*/  NamedBean* createNewBean(QString systemName) override;
  /*public*/  bool addNewSocket() override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testSetValueWithListenersRegistered();/*throws SocketAlreadyConnectedException, SocketAlreadyConnectedException*/
  /*public*/  void testEvaluate() ;
  /*public*/  void testEvaluateAndAction() /*throws SocketAlreadyConnectedException, SocketAlreadyConnectedException */;
  /*public*/  void testCategory();
  /*public*/  void testShortDescription();
  /*public*/  void testLongDescription();
  /*public*/  void testChild();

 private:
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ AnalogExpressionConstant* expressionConstant;
  /*private*/ Memory* _memoryOut;
  /*private*/ AnalogActionMemory* actionMemory;

};

#endif // ANALOGEXPRESSIONCONSTANTTEST_H
