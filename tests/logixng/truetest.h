#ifndef TRUETEST_H
#define TRUETEST_H

#include "abstractdigitalexpressiontestbase.h"

class True;
class ActionAtomicBoolean;
class AtomicBoolean;
class TrueTest : public AbstractDigitalExpressionTestBase
{
  Q_OBJECT
 public:
  explicit TrueTest(QObject *parent = nullptr);
  /*public*/  ConditionalNG* getConditionalNG() override;
  /*public*/  LogixNG* getLogixNG() override;
  /*public*/  MaleSocket* getConnectableChild() override;
  /*public*/  QString getExpectedPrintedTree()  override;
  /*public*/  QString getExpectedPrintedTreeFromRoot() override;
  /*public*/  NamedBean* createNewBean(QString systemName) override;
  /*public*/  bool addNewSocket()override;
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/ void tearDown();

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testGetChild();
  /*public*/  void testCategory();
  /*public*/  void testDescription();
  /*public*/  void testExpression();

 private:
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ True* expressionTrue;
  /*private*/ ActionAtomicBoolean* actionAtomicBoolean;
  /*private*/ AtomicBoolean* atomicBoolean;

};

#endif // TRUETEST_H
