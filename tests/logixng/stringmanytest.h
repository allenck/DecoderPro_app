#ifndef STRINGMANYTEST_H
#define STRINGMANYTEST_H

#include "abstractstringactiontestbase.h"

class StringManyTest : public AbstractStringActionTestBase
{
  Q_OBJECT
 public:
  explicit StringManyTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp() /*throws SocketAlreadyConnectedException*/;
  Q_INVOKABLE /*public*/  void tearDown();
  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  LogixNG* getLogixNG() override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot() override;
  /*public*/  NamedBean* createNewBean(QString systemName) override;
  /*public*/  bool addNewSocket() /*throws SocketAlreadyConnectedException */override;
 public slots:
  /*public*/  void testCtor();
  /*public*/  void testCtorAndSetup1();
  /*public*/  void testCtorAndSetup2();
  /*public*/  void testCtorAndSetup3();
  /*public*/  void testGetChild();
  /*public*/  void testCategory();
  /*public*/  void testConnected_getActionSystemName();
  /*public*/  void testDescription();

 private:
  LogixNG* logixNG;
  ConditionalNG* conditionalNG;

 protected:

};

#endif // STRINGMANYTEST_H
