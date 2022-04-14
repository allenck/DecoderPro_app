#ifndef ANALOGACTIONMEMORYTEST_H
#define ANALOGACTIONMEMORYTEST_H

#include "abstractanalogactiontestbase.h"

class LogixNG;
class ConditionalNG;
class Memory;
class AnalogActionMemoryTest : public AbstractAnalogActionTestBase
{
  Q_OBJECT
 public:
  explicit AnalogActionMemoryTest(QObject *parent = nullptr) : AbstractAnalogActionTestBase(parent) {setObjectName("AnalogActionMemoryTest");}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();
  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  LogixNG* getLogixNG() override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot()override;
  /*public*/  NamedBean* createNewBean(QString systemName) override;
  /*public*/  bool addNewSocket()override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testAction() /*throws SocketAlreadyConnectedException, SocketAlreadyConnectedException, JmriException*/ ;
  /*public*/  void testMemory();
  /*public*/  void testVetoableChange() /*throws PropertyVetoException*/;
  /*public*/  void testCategory();
  /*public*/  void testShortDescription();
  /*public*/  void testLongDescription();
  /*public*/  void testChild();


  private:
    LogixNG* logixNG;
    ConditionalNG* conditionalNG;
 protected:
    /*protected*/ Memory* _memory;

};

#endif // ANALOGACTIONMEMORYTEST_H
