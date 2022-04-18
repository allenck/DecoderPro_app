#ifndef ANTECEDENTTEST_H
#define ANTECEDENTTEST_H

#include "abstractdigitalexpressiontestbase.h"
#include "femalesocketlistener.h"
#include "atomicboolean.h"

class DigitalExpressionBean;
class Antecedent;
class ActionAtomicBoolean;
class AtomicBoolean;
class AntecedentTest : public AbstractDigitalExpressionTestBase, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  explicit AntecedentTest(QObject *parent = nullptr);
  /*public*/  ConditionalNG* getConditionalNG() override;
  /*public*/  LogixNG* getLogixNG()override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot()override;
  /*public*/  NamedBean* createNewBean(QString systemName) /*throws Exception*/override;
  /*public*/  bool addNewSocket() /*throws SocketAlreadyConnectedException*/override;
  Q_INVOKABLE /*public*/  void setUp() /*throws Exception*/;
  Q_INVOKABLE /*public*/  void tearDown();
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;

 public slots:
  /*public*/  void testCtor() /*throws Exception*/;
  /*public*/  void testCtorAndSetup1();
  /*public*/  void testCtorAndSetup2();
  /*public*/  void testCtorAndSetup3();
  /*public*/  void testSetChildCount();
  /*public*/  void testGetChild();
  /*public*/  void testCategory();
  /*public*/  void testConnected_getExpressionSystemName();
  /*public*/  void testDescription();
  /*public*/  void testValidate();
  /*public*/  void testCalculate();

 private:
  /*private*/ static /*final*/ bool EXPECT_SUCCESS;// = true;
  /*private*/ static /*final*/ bool EXPECT_FAILURE;// = false;
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ Antecedent* expressionAntecedent;
  /*private*/ ActionAtomicBoolean* actionAtomicBoolean;
  /*private*/ AtomicBoolean* atomicBoolean;
  /*private*/ static int beanID;// = 901;
  /*private*/ void testValidate(bool expectedResult, QString antecedent, QList<DigitalExpressionBean*> conditionalVariablesList);
  /*private*/ void testCalculate(int expectedResult, QString antecedent,
          QList<DigitalExpressionBean*> conditionalVariablesList, QString errorMessage);

  friend class AntecedentTest_PropertyChangeListener;
};
class AntecedentTest_PropertyChangeListener :public QObject, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
  AtomicBoolean* ab;
 public:
  AntecedentTest_PropertyChangeListener(AtomicBoolean* ab) {this->ab = ab;}
  QObject* pself() override {return (QObject*)this;}
 public slots:
  void propertyChange(PropertyChangeEvent*) override
  {
   ab->set(true);
  }
};

#endif // ANTECEDENTTEST_H
