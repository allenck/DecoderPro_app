#ifndef STRINGFORMULATEST_H
#define STRINGFORMULATEST_H

#include "abstractstringexpressiontestbase.h"
#include "atomicboolean.h"

class StringActionMemory;
class StringFormula;
class Memory;
class StringFormulaTest : public AbstractStringExpressionTestBase
{
  Q_OBJECT
 public:
  explicit StringFormulaTest(QObject *parent = nullptr) : AbstractStringExpressionTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();
  /*public*/  ConditionalNG* getConditionalNG() override;
  /*public*/  LogixNG* getLogixNG()override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot()override;
  /*public*/  NamedBean* createNewBean(QString systemName) /*throws Exception*/override;
  /*public*/  bool addNewSocket() /*throws SocketAlreadyConnectedException*/override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testCtorAndSetup1();
  /*public*/  void testCtorAndSetup2();
  /*public*/  void testCtorAndSetup3();
  /*public*/  void testSetChildCount();
  /*public*/  void testFormula();
  /*public*/  void testGetChild();
  /*public*/  void testCategory();
  /*public*/  void testConnected_getExpressionSystemName();
  /*public*/  void testDescription();
  /*public*/  void testEvaluateEmptyFormula();

 private:
  /*private*/ static int beanID;// = 901;
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ StringFormula* expressionFormula;
  /*private*/ StringActionMemory* stringActionMemory;
  /*private*/ Memory* stringMemory;

};
class PropertyChangeListener01 : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
  AtomicBoolean* ab;
 public:
  PropertyChangeListener01(AtomicBoolean* ab) {this->ab =ab;}
  QObject* pself() override{return(QObject*)this;}
 public slots:
  void propertyChange(PropertyChangeEvent*)
  {
   ab->set(true);
  }
};

class RWI02 : public RunnableWithIndex
{
  Q_OBJECT
  StringFormula* expression;
 public:
  RWI02(StringFormula* expression) { this->expression = expression;}
  void run(int index)
  {

  }
};
#endif // STRINGFORMULATEST_H
