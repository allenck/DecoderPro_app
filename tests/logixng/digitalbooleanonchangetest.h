#ifndef DIGITALBOOLEANONCHANGETEST_H
#define DIGITALBOOLEANONCHANGETEST_H
#include "abstractdigitalbooleanactiontestbase.h"

class DigitalBooleanOnChange;
class ActionTurnout;
class DigitalBooleanOnChangeTest : public AbstractDigitalBooleanActionTestBase
{
  Q_OBJECT

 public:
  DigitalBooleanOnChangeTest(QObject* parent=nullptr) : AbstractDigitalBooleanActionTestBase(parent)  {}
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

  /*public*/  ConditionalNG* getConditionalNG()override;
  /*public*/  LogixNG* getLogixNG() override;
  /*public*/  MaleSocket* getConnectableChild()override;
  /*public*/  NamedBean* createNewBean(QString systemName)override;
  /*public*/  QString getExpectedPrintedTree()override;
  /*public*/  QString getExpectedPrintedTreeFromRoot()override;
  /*public*/  bool addNewSocket()override;

 public slots:
  /*public*/  void testCtor();
  /*public*/  void testCtorAndSetup1();
  /*public*/  void testCtorAndSetup2();
  /*public*/  void testCtorAndSetup3();
  /*public*/  void testGetChild();
  /*public*/  void testCategory();
  /*public*/  void testGetShortDescription();
  /*public*/  void testGetLongDescription();
  /*public*/  void testTrigger();
  /*public*/  void testExecute() /*throws JmriException*/;

 private:
  LogixNG* logixNG;
  ConditionalNG* conditionalNG;
  DigitalBooleanOnChange* _actionOnChange;
  ActionTurnout* _actionTurnout;

};

#endif // DIGITALBOOLEANONCHANGETEST_H
