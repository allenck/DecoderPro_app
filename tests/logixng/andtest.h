#ifndef ANDTEST_H
#define ANDTEST_H

#include "abstractdigitalexpressiontestbase.h"

class AndTest : public AbstractDigitalExpressionTestBase
{
  Q_OBJECT
 public:
  explicit AndTest(QObject *parent = nullptr);
  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  LogixNG* getLogixNG()override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot()override;
  /*public*/  NamedBean* createNewBean(QString systemName)override;
  /*public*/  bool addNewSocket() /*throws SocketAlreadyConnectedException*/override;
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();


 public slots:
  /*public*/  void testCtor();
  /*public*/  void testCtorAndSetup1();
  /*public*/  void testCtorAndSetup2();
  /*public*/  void testCtorAndSetup3();
  /*public*/  void testGetChild();
  /*public*/  void testCategory();
  /*public*/  void testConnected_getExpressionSystemName();
  /*public*/  void testDescription();

 private:
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;

};

#endif // ANDTEST_H
