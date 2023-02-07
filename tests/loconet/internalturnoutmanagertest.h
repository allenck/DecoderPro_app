#ifndef INTERNALTURNOUTMANAGERTEST_H
#define INTERNALTURNOUTMANAGERTEST_H

#include <abstractturnoutmgrtestbase.h>

class InternalTurnoutManagerTest : public AbstractTurnoutMgrTestBase
{
  Q_OBJECT
 public:
  InternalTurnoutManagerTest(QObject* parent = nullptr) : AbstractTurnoutMgrTestBase(parent) {}
  Q_INVOKABLE /*public*/  void setUp()override;
  Q_INVOKABLE /*public*/  void tearDown();
  /*public*/  QString getSystemName(int i)override;

 public slots:
  /*public*/  void testAsAbstractFactory();
  /*public*/  void testCaseMatters();
  /*public*/  void testFollowingTurnouts();
  /*public*/  void testSetAndGetOutputInterval()override;
  /*public*/  void testMakeSystemNameWithNoPrefixNotASystemName()override;
  /*public*/  void testMakeSystemNameWithPrefixNotASystemName()override;
  /*public*/  void testIncorrectGetNextValidAddress();


 protected:
  /*protected*/ QString getASystemNameWithNoPrefix();

};

#endif // INTERNALTURNOUTMANAGERTEST_H
