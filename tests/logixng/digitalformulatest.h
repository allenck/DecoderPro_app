#ifndef DIGITALFORMULATEST_H
#define DIGITALFORMULATEST_H

#include "abstractdigitalexpressiontestbase.h"

class AtomicBoolean;
class DigitalFormula;
class ActionAtomicBoolean;
class DigitalFormulaTest : public AbstractDigitalExpressionTestBase
{
  Q_OBJECT
 public:
  explicit DigitalFormulaTest(QObject *parent = nullptr);
  /*public*/   ConditionalNG* getConditionalNG()override;
  /*public*/   LogixNG* getLogixNG()override;
  /*public*/   MaleSocket* getConnectableChild()override;
  /*public*/   QString getExpectedPrintedTree()override;
  /*public*/   QString getExpectedPrintedTreeFromRoot()override;
  /*public*/   NamedBean* createNewBean(QString systemName) /*throws Exception*/override;
  /*public*/   bool addNewSocket() /*throws SocketAlreadyConnectedException*/override;
  Q_INVOKABLE /*public*/ void setUp();
  Q_INVOKABLE /*public*/ void tearDown();

 public slots:
  /*public*/   void testCtor();
  /*public*/   void testCtorAndSetup1();

 private:
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ DigitalFormula* expressionFormula;
  /*private*/ ActionAtomicBoolean* actionAtomicBoolean;
  /*private*/ AtomicBoolean* atomicBoolean;
  /*private*/ static int beanID;// = 901;

};

#endif // DIGITALFORMULATEST_H
