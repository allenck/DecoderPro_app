#ifndef ACTIONSENSORTEST_H
#define ACTIONSENSORTEST_H

#include "abstractdigitalactiontestbase.h"

class Sensor;
class ActionSensor;
class ActionSensorTest : public AbstractDigitalActionTestBase
{
  Q_OBJECT
 public:
  explicit ActionSensorTest(QObject *parent = nullptr) : AbstractDigitalActionTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp() /*throws SocketAlreadyConnectedException */;
  Q_INVOKABLE /*public*/  void tearDown();
  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  LogixNG* getLogixNG()override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  QString getExpectedPrintedTree() override;
  /*public*/  QString getExpectedPrintedTreeFromRoot()override;
  /*public*/  NamedBean* createNewBean(QString systemName)override;
  /*public*/  bool addNewSocket()override;

 public slots:
  /*public*/  void testSensorState();
  /*public*/  void testCtor() /*throws JmriException*/;
  /*public*/  void testGetChild();
  /*public*/  void testSetSensor();
  /*public*/  void testAction() /*throws SocketAlreadyConnectedException, JmriException*/;
  /*public*/  void testIndirectAddressing() /*throws JmriException*/;
  /*public*/  void testIndirectStateAddressing() /*throws JmriException*/;
  /*public*/  void testVetoableChange() /*throws PropertyVetoException*/;
  /*public*/  void testCategory();
  /*public*/  void testShortDescription();
  /*public*/  void testLongDescription();
  /*public*/  void testChild();


 private:
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;
  /*private*/ ActionSensor* actionSensor;
  /*private*/ Sensor* sensor;

};

#endif // ACTIONSENSORTEST_H
