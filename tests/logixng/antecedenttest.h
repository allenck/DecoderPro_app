#ifndef ANTECEDENTTEST_H
#define ANTECEDENTTEST_H

#include "abstractdigitalexpressiontestbase.h"
#include "femalesocketlistener.h"

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

 private:
  /*private*/ static /*final*/ bool EXPECT_SUCCESS;// = true;
  /*private*/ static /*final*/ bool EXPECT_FAILURE;// = false;
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ Antecedent* expressionAntecedent;
  /*private*/ ActionAtomicBoolean* actionAtomicBoolean;
  /*private*/ AtomicBoolean* atomicBoolean;
  /*private*/ static int beanID;// = 901;


};

#endif // ANTECEDENTTEST_H
