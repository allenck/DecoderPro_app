#ifndef ANALOGFORMULATEST_H
#define ANALOGFORMULATEST_H

#include "abstractanalogexpressiontestbase.h"
#include "atomicboolean.h"

class AnalogFormula;
class Memory;
class AnalogActionMemory;
class AnalogFormulaTest : public AbstractAnalogExpressionTestBase
{
  Q_OBJECT
 public:
  explicit AnalogFormulaTest(QObject *parent = nullptr) : AbstractAnalogExpressionTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp() /*throws Exception*/;
  Q_INVOKABLE /*public*/  void tearDown();
  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  LogixNG* getLogixNG()override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot()override;
  /*public*/  NamedBean* createNewBean(QString systemName) /*throws Exception*/override;
  /*public*/  bool addNewSocket() /*throws SocketAlreadyConnectedException */override;


 public slots:
  /*public*/  void testCtor() /*throws Exception*/;
  /*public*/  void testCtorAndSetup1();
  /*public*/  void testCtorAndSetup2();
  /*public*/  void testCtorAndSetup3() /*throws NoSuchMethodException, IllegalAccessException, IllegalArgumentException*/;
  /*public*/  void testSetChildCount() /*throws SocketAlreadyConnectedException*/;
  /*public*/  void testFormula() /*throws ParserException, SocketAlreadyConnectedException*/;
  /*public*/  void testGetChild() /*throws Exception*/;
  /*public*/  void testCategory();
  /*public*/  void testConnected_getExpressionSystemName() /*throws SocketAlreadyConnectedException */;
  /*public*/  void testDescription();
  /*public*/  void testEvaluateEmptyFormula() /*throws ParserException, JmriException*/ ;

 private:
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ AnalogFormula* expressionFormula;
  /*private*/ AnalogActionMemory* analogActionMemory;
  /*private*/ Memory* analogMemory;
  /*private*/ static int beanID;// = 901;

};
class AFTPropertyChangeListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  AtomicBoolean* ab;
 public:
  AFTPropertyChangeListener(AtomicBoolean* ab) {this->ab = ab;}

 public slots:
  void propertyChange(PropertyChangeEvent* evt) override
  {
   ab->set(true);
  }
  QObject* pself() override {return (QObject*)this;}
};

#endif // ANALOGFORMULATEST_H
